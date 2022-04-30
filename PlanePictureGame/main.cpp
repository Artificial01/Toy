#include <cmath>
#include <ctime>
#include "acllib.h"

#define NONE 0
#define LEFT_KNIGHT 1
#define RIGHT_KNIGHT 2
#define MASK 3
#define ITEM_MASK 4
#define ITEM_STRENGTH 5
#define ITEM_NAIL 6
#define BULLET 7
#define THE_DASH 8
#define THE_EMIT 9
#define BACKGROUND 10
#define DIE 11
#define WIN 12
#define WINDOWS_SIZE_X 1200
#define WINDOWS_SIZE_Y 600
#define PICTURE_SIZE_X1 100
#define PICTURE_SIZE_Y1 100
#define PICTURE_SIZE_X2 50
#define PICTURE_SIZE_Y2 50
#define PICTURE_GAP 25
#define OBJECT_NUMBER_ALL_TIME_MAX 20
#define OBJECT_NUMBER_ONE_TIME_MAX 5

const char * pictureFile[13]={nullptr,
        "pic/leftKnight.bmp","pic/rightKnight.bmp","pic/mask.bmp",
        "pic/itemMask.bmp","pic/itemStrength.bmp","pic/itemNail.bmp",
        "pic/bullet.bmp","pic/theDash.bmp","pic/theEmit.bmp",
        "pic/background.bmp","pic/die.bmp","pic/win.bmp",
};

int time_world;
bool die;
bool win;

class Picture{
protected:
    bool visible;
    int positionX,positionY;
    int sizeX,sizeY;
    int pictureFileIndex;
    ACL_Image picture;
public:
    Picture(int px,int py,int sx,int sy,int pfi){
        visible=true;
        positionX=px;
        positionY=py;
        sizeX=sx;
        sizeY=sy;
        pictureFileIndex=pfi;
    }
    int getPositionX(){
        return positionX;
    }
    int getPositionY(){
        return positionY;
    }
    int getSizeX(){
        return sizeX;
    }
    int getSizeY(){
        return sizeY;
    }
    void setVisible(bool v){
        visible=v;
    }
    bool getVisible(){
        return visible;
    }
    bool pile(Picture * p){
        return ((positionX-p->sizeX)<p->positionX)&&(p->positionX<(positionX+sizeX))&&((positionY-p->sizeY)<p->positionY)&&(p->positionY<(positionY+sizeY));
    }
    virtual void display(){
        if(visible){
            loadImage(pictureFile[pictureFileIndex],&picture);
            beginPaint();
            putImageScale(&picture,positionX,positionY,sizeX,sizeY);
            endPaint();
        }
    }
};
class Creature{
protected:
    int life;
    int hit;
public:
    Creature(int l,int h){
        life=l;
        hit=h;
    }
    void setLife(int l){
        life=l;
    }
    int getLife(){
        return life;
    }
    void setHit(int h){
        hit=h;
    }
    int getHit(){
        return hit;
    }
};

class Knight:public Picture,public Creature{
    int pictureFileIndex2Index;
    int pictureFileIndex2[2];
    int speed;
public:
    Knight(int px,int py):Picture(px,py,PICTURE_SIZE_X1,PICTURE_SIZE_Y1,NONE),Creature(5,5){
        pictureFileIndex2Index=1;
        pictureFileIndex2[0]=LEFT_KNIGHT;
        pictureFileIndex2[1]=RIGHT_KNIGHT;
        speed=3;
    }
    void setSpeed(int s){
        speed=s;
    }
    int getSpeed(){
        return speed;
    }
    void display() override{
        loadImage(pictureFile[pictureFileIndex2[pictureFileIndex2Index]],&picture);
        beginPaint();
        putImageScale(&picture,positionX,positionY,sizeX,sizeY);
        endPaint();
        loadImage(pictureFile[MASK],&picture);
        beginPaint();
        for(int i=0;i<life;i++){
            putImageScale(&picture,PICTURE_GAP+i*PICTURE_SIZE_X2,PICTURE_GAP,PICTURE_SIZE_X2,PICTURE_SIZE_Y2);
        }
        endPaint();
    }
    void move(int k){
        switch (k){
            case 'A':
                positionX-=speed;
                if(positionX<PICTURE_GAP){
                    positionX=PICTURE_GAP;
                }
                pictureFileIndex2Index=0;
                break;
            case 'D':
                positionX+=speed;
                if(positionX>(WINDOWS_SIZE_X-PICTURE_GAP-sizeX)){
                    positionX=(WINDOWS_SIZE_X-PICTURE_GAP-sizeX);
                }
                pictureFileIndex2Index=1;
                break;
            case 'W':
                positionY-=speed;
                if(positionY<PICTURE_GAP){
                    positionY=PICTURE_GAP;
                }
                break;
            case 'S':
                positionY+=speed;
                if(positionY>(WINDOWS_SIZE_Y-PICTURE_GAP-sizeY)){
                    positionY=(WINDOWS_SIZE_Y-PICTURE_GAP-sizeY);
                }
                break;
            default:
                break;
        }
    }
};

class Item:public Picture{
public:
    Item(int px,int py,int pfi):Picture(px,py,PICTURE_SIZE_X2,PICTURE_SIZE_Y2,pfi){}
    virtual void function(Knight * k)=0;
    bool gain(Knight * k){
        if(visible && pile(k)){
            function(k);
            visible=false;
            return true;
        }else{
            return false;
        }
    }
};
class TheMask:public Item{
public:
    TheMask(int px,int py):Item(px,py,ITEM_MASK){}
    void function(Knight * k) override{
        k->setLife(k->getLife()+1);
    }
};
class TheStrength:public Item{
public:
    TheStrength(int px,int py):Item(px,py,ITEM_STRENGTH){}
    void function(Knight * k) override{
        k->setHit(k->getHit()+1);
    }
};
class TheNail:public Item{
public:
    TheNail(int px,int py):Item(px,py,ITEM_NAIL){}
    void function(Knight * k) override{
        k->setSpeed(k->getSpeed()+1);
    }
};

class Bullet:public Picture{
    int time_birth;
    int time_tag;
    int centerX,centerY;
    int radius;
    int hit;
public:
    Bullet(int cx,int cy,int r):Picture(cx+r,cy,PICTURE_SIZE_X2,PICTURE_SIZE_Y2,BULLET){
        time_birth=time_world;
        time_tag=time_world;
        centerX=cx;
        centerY=cy;
        radius=r;
        hit=2;
    }
    void encounter(Knight * k){
        if(pile(k) &&((time_world-time_tag)>50)){
            k->setLife(k->getLife()-hit);
            time_tag=time_world;
        }
    }
    void move(Knight * k){
        positionX=centerX+(int)(radius*cos((time_world-time_birth)/60.0));
        positionY=centerY+(int)(radius*sin((time_world-time_birth)/60.0));
    }
};
class Monster:public Picture,public Creature{
protected:
    int rate1,rate2,rate3;
public:
    Monster(int px,int py,int sx,int sy,int pfi,int l,int h,int r1,int r2,int r3):Picture(px,py,sx,sy,pfi),Creature(l,h){
        rate1=r1;
        rate2=r2;
        rate3=r3;
    }
    int getRate1(){
        return rate1;
    }
    int getRate2(){
        return rate2;
    }
    int getRate3(){
        return rate3;
    }
    virtual void encounter(Knight * k)=0;
    virtual void move(Knight * k)=0;
};
class SmallMonster:public Monster{
public:
    SmallMonster(int px,int py,int pfi,int l,int h,int r1,int r2,int r3):Monster(px,py,PICTURE_SIZE_X1,PICTURE_SIZE_Y1,pfi,l,h,r1,r2,r3){}
};
class TheDash:public SmallMonster{
    int speed;
    int speedX,speedY;
    int directX,directY;
public:
    TheDash(int px,int py):SmallMonster(px,py,THE_DASH,5,0,20,40,0){
        speed=2;
        speedX=rand()%(speed+1);
        speedY=speed-speedX;
        directX=(rand()%2)*2-1;
        directY=(rand()%2)*2-1;
    }
    void encounter(Knight * k) override{
        if(visible && pile(k)){
            life-=k->getHit();
        }
    }
    void move(Knight * k) override{
        if(visible){
            int deltaX=(positionX-k->getPositionX()),deltaY=(positionY-k->getPositionY());
            int deltaL=(abs(deltaX)+abs(deltaY));
            if(deltaL<200){
                speedX=(int)(speed*((double)abs(deltaX)/(double)deltaL));
                speedY=speed-speedX;
                if(deltaX>0){
                    directX=1;
                }else{
                    directX=-1;
                }
                if(deltaY>0){
                    directY=1;
                }else{
                    directY=-1;
                }
            }
            if(positionX<PICTURE_GAP){
                directX=1;
            }
            if(positionX>(WINDOWS_SIZE_X-PICTURE_GAP-sizeX)){
                directX=-1;
            }
            if(positionY<PICTURE_GAP){
                directY=1;
            }
            if(positionY>(WINDOWS_SIZE_Y-PICTURE_GAP-sizeY)){
                directY=-1;
            }
            positionX+=(directX*speedX);
            positionY+=(directY*speedY);
        }
    }
};
class TheEmit:public SmallMonster{
    Bullet * bullet;
public:
    TheEmit(int px,int py):SmallMonster(px,py,THE_EMIT,5,0,20,0,40){
        bullet=new Bullet(px,py,(rand()%2+1)*100);
    }
    void encounter(Knight * k) override{
        if(visible){
            bullet->encounter(k);
            if(pile(k)){
                life-=k->getHit();
            }
        }
    }
    void move(Knight * k) override{
        if(visible){
            bullet->move(k);
        }
    }
    void display() override{
        if(visible){
            loadImage(pictureFile[pictureFileIndex],&picture);
            beginPaint();
            putImageScale(&picture,positionX,positionY,sizeX,sizeY);
            endPaint();
            bullet->display();
        }
    }
};

class Area{
    int objectNumberAllTime[5];
    int objectNumberOneTime[5];
    TheMask * masks[OBJECT_NUMBER_ALL_TIME_MAX];
    TheStrength * strengths[OBJECT_NUMBER_ALL_TIME_MAX];
    TheNail * nails[OBJECT_NUMBER_ALL_TIME_MAX];
    TheDash * dashs[OBJECT_NUMBER_ALL_TIME_MAX];
    TheEmit * emits[OBJECT_NUMBER_ALL_TIME_MAX];
    ACL_Image picture;
public:
    Area(){
        for(int i=0;i<5;i++){
            objectNumberAllTime[i]=0;
        }
        for(int i=0;i<5;i++){
            objectNumberOneTime[i]=0;
        }
        for(int i=0;i<OBJECT_NUMBER_ALL_TIME_MAX;i++){
            masks[i]=nullptr;
        }
        for(int i=0;i<OBJECT_NUMBER_ALL_TIME_MAX;i++){
            strengths[i]=nullptr;
        }
        for(int i=0;i<OBJECT_NUMBER_ALL_TIME_MAX;i++){
            nails[i]=nullptr;
        }
        for(int i=0;i<OBJECT_NUMBER_ALL_TIME_MAX;i++){
            dashs[i]=nullptr;
        }
        for(int i=0;i<OBJECT_NUMBER_ALL_TIME_MAX;i++){
            emits[i]=nullptr;
        }
    }
    void display(){
        loadImage(pictureFile[BACKGROUND],&picture);
        beginPaint();
        putImageScale(&picture,0,0,WINDOWS_SIZE_X,WINDOWS_SIZE_Y);
        endPaint();
        for(int i=0;i<objectNumberAllTime[0];i++){
            masks[i]->display();
        }
        for(int i=0;i<objectNumberAllTime[1];i++){
            strengths[i]->display();
        }
        for(int i=0;i<objectNumberAllTime[2];i++){
            nails[i]->display();
        }
        for(int i=0;i<objectNumberAllTime[3];i++){
            dashs[i]->display();
        }
        for(int i=0;i<objectNumberAllTime[4];i++){
            emits[i]->display();
        }
    }
    void generateObject(int i,int px,int py){
        if((objectNumberAllTime[i]<OBJECT_NUMBER_ALL_TIME_MAX)&&(objectNumberOneTime[i]<OBJECT_NUMBER_ONE_TIME_MAX)){
            switch (i){
                case 0:
                    masks[objectNumberAllTime[i]]=new TheMask(px,py);
                    break;
                case 1:
                    strengths[objectNumberAllTime[i]]=new TheStrength(px,py);
                    break;
                case 2:
                    nails[objectNumberAllTime[i]]=new TheNail(px,py);
                    break;
                case 3:
                    dashs[objectNumberAllTime[i]]=new TheDash(px,py);
                    break;
                case 4:
                    emits[objectNumberAllTime[i]]=new TheEmit(px,py);
                    break;
                default:
                    break;
            }
            objectNumberAllTime[i]++;
            objectNumberOneTime[i]++;
        }
    }
    bool dieMonster(Monster * m,Knight * k){
        if(m->getVisible() &&(m->getLife()<=0)){
            m->setVisible(false);
            int n=rand()%100;
            if(n<m->getRate1()){
                generateObject(0,m->getPositionX()+m->getSizeX(),m->getPositionY()+m->getSizeY());
            }else if(n<(m->getRate1()+m->getRate2())){
                generateObject(1,m->getPositionX()+m->getSizeX(),m->getPositionY()+m->getSizeY());
            }else if(n<(m->getRate1()+m->getRate2()+m->getRate3())){
                generateObject(2,m->getPositionX()+m->getSizeX(),m->getPositionY()+m->getSizeY());
            }
            return true;
        }else{
            return false;
        }
    }
    void run(Knight * k){
        if((time_world%50)==0){
            generateObject(3,rand()%(WINDOWS_SIZE_X/2)+(WINDOWS_SIZE_X/4),rand()%(WINDOWS_SIZE_Y/2)+(WINDOWS_SIZE_Y/4));
            generateObject(4,rand()%(WINDOWS_SIZE_X/2)+(WINDOWS_SIZE_X/4),rand()%(WINDOWS_SIZE_Y/2)+(WINDOWS_SIZE_Y/4));
        }
        for(int i=0;i<objectNumberAllTime[3];i++){
            dashs[i]->move(k);
        }
        for(int i=0;i<objectNumberAllTime[4];i++){
            emits[i]->move(k);
        }
    }
    void event(Knight * k){
        for(int i=0;i<objectNumberAllTime[0];i++){
            if(masks[i]->gain(k)){
                objectNumberOneTime[0]--;
            }
        }
        for(int i=0;i<objectNumberAllTime[1];i++){
            if(strengths[i]->gain(k)){
                objectNumberOneTime[1]--;
            }
        }
        for(int i=0;i<objectNumberAllTime[2];i++){
            if(nails[i]->gain(k)){
                objectNumberOneTime[2]--;
            }
        }
        for(int i=0;i<objectNumberAllTime[3];i++){
            dashs[i]->encounter(k);
            if(dieMonster(dashs[i],k)){
                objectNumberOneTime[3]--;
            }
        }
        for(int i=0;i<objectNumberAllTime[4];i++){
            emits[i]->encounter(k);
            if(dieMonster(emits[i],k)){
                objectNumberOneTime[4]--;
            }
        }
        if(k->getLife()<=0){
            die=true;
            cancelTimer(0);
        }else{
            for(int i=3;i<5;i++){
                if(objectNumberAllTime[i]!=OBJECT_NUMBER_ALL_TIME_MAX){
                    return;
                }
            }
            for(int i=3;i<5;i++){
                if(objectNumberOneTime[i]!=0){
                    return;
                }
            }
            win=true;
            cancelTimer(0);
        }
    }
};

Knight * knight;
Area * area;

void display(){
    beginPaint();
    clearDevice();
    endPaint();
    if(!(die||win)){
        area->display();
        knight->display();
    }else if(die){
        ACL_Image picture;
        loadImage(pictureFile[DIE],&picture);
        beginPaint();
        putImageScale(&picture,0,0,WINDOWS_SIZE_X,WINDOWS_SIZE_Y);
        endPaint();
    }else if(win){
        ACL_Image picture;
        loadImage(pictureFile[WIN],&picture);
        beginPaint();
        putImageScale(&picture,0,0,WINDOWS_SIZE_X,WINDOWS_SIZE_Y);
        endPaint();
    }
}
void TimerEvent(int id){
    if(!(die||win)){
        time_world++;
        area->run(knight);
        area->event(knight);
        display();
    }
}
void KeyBoardEvent(int k,int e){
    if(!(die||win)){
        switch(k){
            case 'A':
                knight->move('A');
                break;
            case 'D':
                knight->move('D');
                break;
            case 'W':
                knight->move('W');
                break;
            case 'S':
                knight->move('S');
                break;
            default:
                break;
        }
        area->event(knight);
        display();
    }
    if(k==27){
        exit(0);
    }
}
void init(){
    time_world=0;
    die=false;
    win=false;
    knight=new Knight(PICTURE_GAP,(WINDOWS_SIZE_Y-PICTURE_SIZE_Y1)/2);
    area=new Area();
    srand((unsigned)time(nullptr));
    startTimer(0,20);
    display();
}

int Setup(){
    initWindow("Knight:Role Play Game",DEFAULT,DEFAULT,WINDOWS_SIZE_X,WINDOWS_SIZE_Y);
    registerKeyboardEvent(KeyBoardEvent);
    registerTimerEvent(TimerEvent);
    init();
    return 0;
}

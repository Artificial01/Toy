#ifndef RUN_BASE
#define RUN_BASE

#include <ctime>

#include "acllib.h"

enum TIMER_ID{RUNNER,ROAD,END};

#define WINDOW_SIZE_X 1200
#define WINDOW_SIZE_Y 650

ACL_Sound sound_background;
ACL_Sound sound_jump;
ACL_Sound sound_score;
ACL_Sound sound_end;

class Picture{
protected:
    bool visible;
    int positionX,positionY;
    int sizeX,sizeY;
    ACL_Image picture{};
public:
    Picture(int px,int py,int sx,int sy,const char * p){
        visible=true;
        positionX=px;
        positionY=py;
        sizeX=sx;
        sizeY=sy;
        loadImage(p,&picture);
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

    bool pile(Picture * p){
        return ((positionX-p->sizeX)<=p->positionX)&&(p->positionX<=(positionX+sizeX))&&((positionY-p->sizeY)<=p->positionY)&&(p->positionY<=(positionY+sizeY));
    }

    virtual void display(){
        if(visible){
            beginPaint();
            putImageScale(&picture,positionX,positionY,sizeX,sizeY);
            endPaint();
        }
    }
};

#endif

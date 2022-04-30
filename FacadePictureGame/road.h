#ifndef RUN_ROAD
#define RUN_ROAD

#include "base.h"

typedef enum ROAD_TERRAIN{TERRAIN_GROUND,TERRAIN_CHUNK,TERRAIN_HOLLOW,TERRAIN_PLANT,TERRAIN_GOLD,TERRAIN_DESTINATION} ROAD_TERRAIN;

#define ROAD_GROUND_POSITION_Y 450
#define ROAD_CHUNK_SIZE_X 50
#define ROAD_CHUNK_SIZE_Y 50
#define ROAD_HOLLOW_SIZE_X 100
#define ROAD_PLANT_SIZE_X 50
#define ROAD_PLANT_SIZE_Y 50
#define ROAD_GOLD_SIZE_X 50
#define ROAD_GOLD_SIZE_Y 50
#define ROAD_GOLD_HANG 80
#define ROAD_DESTINATION_SIZE_X 150
#define ROAD_DESTINATION_SIZE_Y 150
#define ROAD_TERRAIN_SPACE_INTERVAL 500
#define ROAD_TERRAIN_COUNT_MAX 15

#define ROAD_STAR_SIZE_X 70
#define ROAD_STAR_SIZE_Y 70
#define ROAD_STAR_INIT_POSITION_X 30
#define ROAD_STAR_INIT_POSITION_Y 30
#define ROAD_STAR_GAP 10

class Chunk:public Picture{
private:
    int moveSpaceInterval;
public:
    Chunk(int px,int py,int msi):Picture(px,py,ROAD_CHUNK_SIZE_X,ROAD_CHUNK_SIZE_Y,"data/pic/chunk.bmp"){
        moveSpaceInterval=msi;
    }

    void tick(){
        positionX-=moveSpaceInterval;
        visible=(-sizeX<positionX)&&(positionX<WINDOW_SIZE_X);
    }

    bool check(Picture * p){
        return visible && pile(p);
    }
};

class Hollow:public Picture{
private:
    int moveSpaceInterval;
public:
    Hollow(int px,int py,int msi):Picture(px,py,ROAD_HOLLOW_SIZE_X,WINDOW_SIZE_Y-ROAD_GROUND_POSITION_Y,"data/pic/hollow.bmp"){
        moveSpaceInterval=msi;
    }

    void tick(){
        positionX-=moveSpaceInterval;
        visible=(-sizeX<positionX)&&(positionX<WINDOW_SIZE_X);
    }

    bool check(Picture * p){
        return visible && pile(p) && (p->getPositionX()>=positionX) && (p->getPositionX()<=(positionX+sizeX-p->getSizeX()));
    }
};

class Plant:public Picture{
private:
    int moveSpaceInterval;
    int runnerLastPositionBottomY;
    bool dying;
    bool alive;
public:
    Plant(int px,int py,int msi):Picture(px,py,ROAD_PLANT_SIZE_X,ROAD_PLANT_SIZE_Y,"data/pic/plant.bmp"){
        moveSpaceInterval=msi;
        runnerLastPositionBottomY=ROAD_GROUND_POSITION_Y;
        dying=false;
        alive=true;
    }

    void tick(){
        positionX-=moveSpaceInterval;
        visible=(-sizeX<positionX)&&(positionX<WINDOW_SIZE_X)&&alive;
    }

    bool check(Picture * p,int & score){
        int runnerNowPositionBottomY=(p->getPositionY()+p->getSizeY());
        if(dying){
            if(alive){
                positionY=runnerNowPositionBottomY;
                sizeY=ROAD_GROUND_POSITION_Y-positionY;
                if(sizeY<=0){
                    alive=false;
                    visible=false;
                    score++;
                }
            }
            return false;
        }else{
            if(visible && pile(p)){
                if(runnerLastPositionBottomY<=positionY){
                    dying=true;
                    playSound(sound_score,0);
                    return false;
                }else{
                    runnerLastPositionBottomY=runnerNowPositionBottomY;
                    return true;
                }
            }else{
                runnerLastPositionBottomY=runnerNowPositionBottomY;
                return false;
            }
        }
    }
};

class Gold:public Picture{
private:
    int moveSpaceInterval;
    bool gained;
public:
    Gold(int px,int py,int msi):Picture(px,py,ROAD_GOLD_SIZE_X,ROAD_GOLD_SIZE_Y,"data/pic/gold.bmp"){
        moveSpaceInterval=msi;
        gained=false;
    }

    void tick(){
        positionX-=moveSpaceInterval;
        visible=(-sizeX<positionX)&&(positionX<WINDOW_SIZE_X)&&(!gained);
    }

    void check(Picture * p,int & score){
        if(visible && pile(p)){
            gained=true;
            visible=false;
            score++;
            playSound(sound_score,0);
        }
    }
};

class Destination:public Picture{
private:
    int moveSpaceInterval;
public:
    Destination(int px,int msi):Picture(px,ROAD_GROUND_POSITION_Y-ROAD_DESTINATION_SIZE_Y,ROAD_DESTINATION_SIZE_X,ROAD_DESTINATION_SIZE_Y,"data/pic/destination.bmp"){
        moveSpaceInterval=msi;
    }

    void tick(){
        positionX-=moveSpaceInterval;
        visible=(-sizeX<positionX)&&(positionX<WINDOW_SIZE_X);
    }

    bool check(Picture * p){
        return visible && pile(p);
    }
};

class Road{
private:
    int moveSpaceInterval;
    int timeInterval;
    int terrainCount;
    Chunk * chunk[ROAD_TERRAIN_COUNT_MAX]{};
    int chunkCount;
    Hollow * hollow[ROAD_TERRAIN_COUNT_MAX]{};
    int hollowCount;
    Plant * plant[ROAD_TERRAIN_COUNT_MAX]{};
    int plantCount;
    Gold * gold[ROAD_TERRAIN_COUNT_MAX]{};
    int goldCount;
    Destination * destination;
    ROAD_TERRAIN terrain[ROAD_TERRAIN_COUNT_MAX]{};
    int score;
    ACL_Image background{};
    ACL_Image ground{};
    ACL_Image star{};
public:
    Road(int msi,int tc){
        moveSpaceInterval=msi;
        timeInterval=30;
        terrainCount=tc;
        chunkCount=0;
        hollowCount=0;
        plantCount=0;
        goldCount=0;
        for(int i=0;i<terrainCount;i++){
            int k=rand();
            if(k%7==0 || k%7==1){
                terrain[i]=TERRAIN_CHUNK;
                chunk[chunkCount]=new Chunk(i*ROAD_TERRAIN_SPACE_INTERVAL+WINDOW_SIZE_X,ROAD_GROUND_POSITION_Y-ROAD_CHUNK_SIZE_Y,moveSpaceInterval);
                chunkCount++;
            }else if(k%7==2 || k%7==3){
                terrain[i]=TERRAIN_HOLLOW;
                hollow[hollowCount]=new Hollow(i*ROAD_TERRAIN_SPACE_INTERVAL+WINDOW_SIZE_X,ROAD_GROUND_POSITION_Y,moveSpaceInterval);
                hollowCount++;
            }else if(k%7==4 || k%7==5){
                terrain[i]=TERRAIN_PLANT;
                plant[plantCount]=new Plant(i*ROAD_TERRAIN_SPACE_INTERVAL+WINDOW_SIZE_X,ROAD_GROUND_POSITION_Y-ROAD_PLANT_SIZE_Y,moveSpaceInterval);
                plantCount++;
            }else if(k%7==6){
                terrain[i]=TERRAIN_GOLD;
                gold[goldCount]=new Gold(i*ROAD_TERRAIN_SPACE_INTERVAL+WINDOW_SIZE_X,ROAD_GROUND_POSITION_Y-ROAD_GOLD_SIZE_Y-ROAD_GOLD_HANG,moveSpaceInterval);
                goldCount++;
            }
        }
        destination=new Destination(terrainCount*ROAD_TERRAIN_SPACE_INTERVAL+WINDOW_SIZE_X,moveSpaceInterval);
        score=0;
        loadImage("data/pic/background.bmp",&background);
        loadImage("data/pic/ground.bmp",&ground);
        loadImage("data/pic/star.bmp",&star);
        startTimer(ROAD,timeInterval);
    }

    void tick(){
        for(int i=0;i<chunkCount;i++){
            chunk[i]->tick();
        }
        for(int i=0;i<hollowCount;i++){
            hollow[i]->tick();
        }
        for(int i=0;i<plantCount;i++){
            plant[i]->tick();
        }
        for(int i=0;i<goldCount;i++){
            gold[i]->tick();
        }
        destination->tick();
    }

    ROAD_TERRAIN check(Picture * p){
        for(int i=0;i<chunkCount;i++){
            if(chunk[i]->check(p)){
                return TERRAIN_CHUNK;
            }
        }
        for(int i=0;i<hollowCount;i++){
            if(hollow[i]->check(p)){
                return TERRAIN_HOLLOW;
            }
        }
        for(int i=0;i<plantCount;i++){
            if(plant[i]->check(p,score)){
                return TERRAIN_PLANT;
            }
        }
        for(int i=0;i<goldCount;i++){
            gold[i]->check(p,score);
        }
        if(destination->check(p)){
            return TERRAIN_DESTINATION;
        }
        return TERRAIN_GROUND;
    }

    void display(){
        beginPaint();
        putImageScale(&background,0,0,WINDOW_SIZE_X,WINDOW_SIZE_Y);
        putImageScale(&ground,0,ROAD_GROUND_POSITION_Y,WINDOW_SIZE_X,WINDOW_SIZE_Y-ROAD_GROUND_POSITION_Y);
        for(int i=0;i<score;i++){
            putImageScale(&star,ROAD_STAR_INIT_POSITION_X+i*ROAD_STAR_SIZE_X+i*ROAD_STAR_GAP,ROAD_STAR_INIT_POSITION_Y,ROAD_STAR_SIZE_X,ROAD_STAR_SIZE_Y);
        }
        endPaint();
        for(int i=0;i<chunkCount;i++){
            chunk[i]->display();
        }
        for(int i=0;i<hollowCount;i++){
            hollow[i]->display();
        }
        for(int i=0;i<plantCount;i++){
            plant[i]->display();
        }
        for(int i=0;i<goldCount;i++){
            gold[i]->display();
        }
        destination->display();
    }
};

#endif

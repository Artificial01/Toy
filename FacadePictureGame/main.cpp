#include "runner.h"
#include "road.h"

enum STATE_END_INDEX{END_WIN,END_CHUNK,END_HOLLOW,END_PLANT,END_COUNT};

#define PICTURE_END_SIZE_X 200
#define PICTURE_END_SIZE_Y 100

Runner * runner;
Road * road;

bool stateEnd[END_COUNT];
bool stateRun;
bool stateInit;

int timeEnd;
int level;

void displayInit();
void display();
void displayEnd();
void check();
void init();

void displayInit(){
    ACL_Image picture;
    switch(level){
        case 1:
            loadImage("data/pic/initLevel1.bmp",&picture);
            break;
        case 2:
            loadImage("data/pic/initLevel2.bmp",&picture);
            break;
        case 3:
            loadImage("data/pic/initLevel3.bmp",&picture);
            break;
        default:
            break;
    }
    beginPaint();
    putImageScale(&picture,0,0,WINDOW_SIZE_X,WINDOW_SIZE_Y);
    endPaint();
}

void display(){
    beginPaint();
    clearDevice();
    endPaint();

    road->display();
    runner->display();
}

void displayEnd(){
    display();
    ACL_Image picture;
    int pictureEndPositionY;
    if(timeEnd+50<WINDOW_SIZE_Y/4){
        pictureEndPositionY=timeEnd+50;
    }else{
        pictureEndPositionY=WINDOW_SIZE_Y/4;
    }
    beginPaint();
    if(stateEnd[END_WIN]){
        loadImage("data/pic/endWin.bmp",&picture);
        runner->endWin();
    }else if(stateEnd[END_CHUNK]){
        loadImage("data/pic/endChunk.bmp",&picture);
        runner->endChunk(timeEnd);
    }else if(stateEnd[END_HOLLOW]){
        loadImage("data/pic/endHollow.bmp",&picture);
        runner->endHollow();
    }else if(stateEnd[END_PLANT]){
        loadImage("data/pic/endPlant.bmp",&picture);
        runner->endPlant(timeEnd);
    }
    putImageScale(&picture,(WINDOW_SIZE_X-PICTURE_END_SIZE_X)/2,pictureEndPositionY,PICTURE_END_SIZE_X,PICTURE_END_SIZE_Y);
    endPaint();
}

void check(){
    switch (road->check(runner)){
        case TERRAIN_DESTINATION:
            stateEnd[END_WIN]=true;
            break;
        case TERRAIN_CHUNK:
            stateEnd[END_CHUNK]=true;
            break;
        case TERRAIN_HOLLOW:
            stateEnd[END_HOLLOW]=true;
            break;
        case TERRAIN_PLANT:
            stateEnd[END_PLANT]=true;
            break;
        default:
            break;
    }
    if(stateEnd[END_WIN]){
        stateRun=false;
        cancelTimer(RUNNER);
        cancelTimer(ROAD);
        startTimer(END,30);
        if(level<3){
            level++;
        }
        stopSound(sound_background);
        playSound(sound_end,0);
    }else if(stateEnd[END_CHUNK]||stateEnd[END_HOLLOW]||stateEnd[END_PLANT]){
        stateRun=false;
        cancelTimer(RUNNER);
        cancelTimer(ROAD);
        startTimer(END,30);
        stopSound(sound_background);
        playSound(sound_end,0);
    }
}

void keyBoardEvent(int k,int e){
    if(stateInit){
        stateInit=false;
        runner=new Runner(WINDOW_SIZE_X/5,ROAD_GROUND_POSITION_Y-RUNNER_SIZE_Y);
        road=new Road(1+level,5*level);
        stateRun=true;
    }else if(stateRun){
        if(e==KEY_DOWN){
            runner->move(k);
            display();
            check();
        }
    }
}

void timerEvent(int id){
    switch(id){
        case RUNNER:
            runner->tick();
            display();
            check();
            break;
        case ROAD:
            road->tick();
            display();
            check();
            break;
        case END:
            if(timeEnd>200){
                cancelTimer(END);
                init();
            }else{
                timeEnd++;
                displayEnd();
            }
            break;
        default:
            break;
    }
}

void init(){
    for(int i=0;i<END_COUNT;i++){
        stateEnd[i]=false;
    }
    stateRun=false;
    stateInit=true;
    timeEnd=0;
    playSound(sound_background,1);
    displayInit();
}

int Setup(){
    level=1;
    loadSound("data/mus/background.wav",&sound_background);
    loadSound("data/mus/jump.wav",&sound_jump);
    loadSound("data/mus/score.wav",&sound_score);
    loadSound("data/mus/end.wav",&sound_end);
    srand((unsigned)time(nullptr));

    initWindow("RUN",0,0,WINDOW_SIZE_X,WINDOW_SIZE_Y);
    registerKeyboardEvent(keyBoardEvent);
    registerTimerEvent(timerEvent);
    init();

    return 0;
}

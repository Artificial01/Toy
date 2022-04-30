#ifndef RUN_RUNNER
#define RUN_RUNNER

#include "base.h"

#define RUNNER_SIZE_X 50
#define RUNNER_SIZE_Y 50

#define RUNNER_MOVE_SPACE_INTERVAL 3
#define RUNNER_ACCELERATE_SPACE_INTERVAL_COUNT 50
#define RUNNER_TIME_INTERVAL 15
#define RUNNER_JUMP_TIME_INTERVAL_COUNT 81
#define RUNNER_WALK_TIME_INTERVAL_COUNT 6

class Runner:public Picture{
private:
    int timeMario;
    int stateJump;
    int timeTagJump;
    int jumpTimeInterval[RUNNER_JUMP_TIME_INTERVAL_COUNT]{};
    int stateWalk[2]{};
    int timeTagWalk;
    int walkTimeInterval[RUNNER_WALK_TIME_INTERVAL_COUNT]{};
    int stateAccelerate;
    int accelerateSpaceInterval[RUNNER_ACCELERATE_SPACE_INTERVAL_COUNT]{};
    bool hurt;
public:
    Runner(int px,int py):Picture(px,py,RUNNER_SIZE_X,RUNNER_SIZE_Y,"data/pic/runner.bmp"){
        timeMario=0;
        stateJump=0;
        timeTagJump=0;
        jumpTimeInterval[0]=0;
        for(int i=1;i<RUNNER_JUMP_TIME_INTERVAL_COUNT/4;i++){
            jumpTimeInterval[i]=1;
        }
        for(int i=RUNNER_JUMP_TIME_INTERVAL_COUNT/4;i<RUNNER_JUMP_TIME_INTERVAL_COUNT*3/8;i++){
            jumpTimeInterval[i]=1+i%2;
        }
        for(int i=RUNNER_JUMP_TIME_INTERVAL_COUNT*3/8;i<RUNNER_JUMP_TIME_INTERVAL_COUNT*7/16;i++){
            jumpTimeInterval[i]=2;
        }
        for(int i=RUNNER_JUMP_TIME_INTERVAL_COUNT*7/16;i<RUNNER_JUMP_TIME_INTERVAL_COUNT*15/32;i++){
            jumpTimeInterval[i]=3;
        }
        for(int i=RUNNER_JUMP_TIME_INTERVAL_COUNT*15/32;i<=RUNNER_JUMP_TIME_INTERVAL_COUNT/2;i++){
            jumpTimeInterval[i]=4;
        }
        for(int i=1;i<=RUNNER_JUMP_TIME_INTERVAL_COUNT/2;i++){
            jumpTimeInterval[RUNNER_JUMP_TIME_INTERVAL_COUNT-i]=jumpTimeInterval[i];
        }
        stateWalk[0]=0;
        stateWalk[1]=0;
        timeTagWalk=0;
        walkTimeInterval[0]=0;
        walkTimeInterval[1]=2;
        walkTimeInterval[2]=2;
        walkTimeInterval[3]=3;
        walkTimeInterval[4]=3;
        walkTimeInterval[5]=4;
        stateAccelerate=0;
        accelerateSpaceInterval[0]=0;
        for(int i=1;i<RUNNER_ACCELERATE_SPACE_INTERVAL_COUNT/6;i++){
            accelerateSpaceInterval[i]=1;
        }
        for(int i=RUNNER_ACCELERATE_SPACE_INTERVAL_COUNT/6;i<RUNNER_ACCELERATE_SPACE_INTERVAL_COUNT/3;i++){
            accelerateSpaceInterval[i]=i%2;
        }
        for(int i=RUNNER_ACCELERATE_SPACE_INTERVAL_COUNT/3;i<RUNNER_ACCELERATE_SPACE_INTERVAL_COUNT/2;i++){
            accelerateSpaceInterval[i]=2;
        }
        accelerateSpaceInterval[RUNNER_ACCELERATE_SPACE_INTERVAL_COUNT/2]=3;
        for(int i=1;i<RUNNER_ACCELERATE_SPACE_INTERVAL_COUNT/2;i++){
            accelerateSpaceInterval[RUNNER_ACCELERATE_SPACE_INTERVAL_COUNT-i]=accelerateSpaceInterval[i];
        }
        hurt=false;
        startTimer(RUNNER,RUNNER_TIME_INTERVAL);
    }

    bool isStateJumpDown(){
        return stateJump>RUNNER_JUMP_TIME_INTERVAL_COUNT/2;
    }

    void tick(){
        timeMario++;
        if(stateJump && (timeMario-timeTagJump)>=jumpTimeInterval[stateJump]){
            if(isStateJumpDown()){
                positionY+=RUNNER_MOVE_SPACE_INTERVAL;
            }else{
                positionY-=RUNNER_MOVE_SPACE_INTERVAL;
            }
            timeTagJump=timeMario;
            stateJump=(stateJump+1)%RUNNER_JUMP_TIME_INTERVAL_COUNT;
        }
        if(stateWalk[0] && (timeMario-timeTagWalk)>=walkTimeInterval[stateWalk[0]]){
            positionX-=RUNNER_MOVE_SPACE_INTERVAL;
            timeTagWalk=timeMario;
            if(positionX<0){
                positionX=0;
                stateWalk[0]=0;
            }
            if(!stateJump){
                stateWalk[0]=(stateWalk[0]+1)%RUNNER_WALK_TIME_INTERVAL_COUNT;
            }
        }
        if(stateWalk[1] && (timeMario-timeTagWalk)>=walkTimeInterval[stateWalk[1]]){
            positionX=positionX+RUNNER_MOVE_SPACE_INTERVAL+accelerateSpaceInterval[stateAccelerate];
            timeTagWalk=timeMario;
            if(positionX>(WINDOW_SIZE_X-sizeX)){
                positionX=(WINDOW_SIZE_X-sizeX);
                stateWalk[1]=0;
            }
            if(!stateJump){
                if(stateAccelerate){
                    if(stateWalk[1]>1){
                        stateWalk[1]--;
                    }
                    if(stateAccelerate!=(RUNNER_ACCELERATE_SPACE_INTERVAL_COUNT/2)){
                        stateAccelerate=(stateAccelerate+1)%RUNNER_ACCELERATE_SPACE_INTERVAL_COUNT;
                    }
                }else{
                    stateWalk[1]=(stateWalk[1]+1)%RUNNER_WALK_TIME_INTERVAL_COUNT;
                }
            }
        }
    }

    void move(int key){
        switch (key){
            case 'A':
                stateWalk[0]=1;
                stateWalk[1]=0;
                stateAccelerate=0;
                break;
            case 'D':
                stateWalk[0]=0;
                stateWalk[1]=1;
                break;
            case 'W':
                if(!stateJump){
                    stateJump=1;
                    playSound(sound_jump,0);
                }
                break;
            case ' ':
                if(!stateJump && stateWalk[1]){
                    if(stateAccelerate==0||stateAccelerate==(RUNNER_ACCELERATE_SPACE_INTERVAL_COUNT/2)){
                        stateAccelerate++;
                    }else{
                        stateAccelerate=(RUNNER_ACCELERATE_SPACE_INTERVAL_COUNT-stateAccelerate);
                    }
                }
                break;
            default:
                break;
        }
    }

    void endWin(){
        if(sizeX>0 && sizeY>0){
            positionX+=(RUNNER_SIZE_X/50);
            positionY+=(RUNNER_SIZE_Y/50);
            sizeX-=(RUNNER_SIZE_X/50);
            sizeY-=(RUNNER_SIZE_Y/50);
        }
    }
    void endChunk(int t){
        if(t%7==0){
            if(hurt){
                loadImage("data/pic/runnerHurt.bmp",&picture);
                hurt=false;
            }else{
                loadImage("data/pic/runner.bmp",&picture);
                hurt=true;
            }
        }
    }
    void endHollow(){
        if(positionY<WINDOW_SIZE_Y){
            positionY+=5;
        }
    }
    void endPlant(int t){
        if(t%7==0){
            if(hurt){
                loadImage("data/pic/runnerHurt.bmp",&picture);
                hurt=false;
            }else{
                loadImage("data/pic/runner.bmp",&picture);
                hurt=true;
            }
        }
    }
};

#endif

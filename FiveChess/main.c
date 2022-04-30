#include <stdio.h>
#include <windows.h>
#include <locale.h>

#define DEPTH 6

int add[4][2][2]={{{1,0},{-1,0}},{{1,1},{-1,-1}},{{0,1},{0,-1}},{{-1,1},{1,-1}}};
int boardData[17][17];
int player;
int chessX,chessY;
int win;

void initBoard();
void endBoard();
void switchPlayer();
void placeChess();
void updateBoard();
void checkWin();
int basicCount(int positionX,int positionY,int addX,int addY,int count);
void AI();
int maxLayer(int depth,int alpha,int beta,int positionX,int positionY);
int minLayer(int depth,int alpha,int beta,int positionX,int positionY);
void predictChess(int predictedChess[150][2]);
int fastCheckWin(int positionX,int positionY);
int evaluate();
int hasNeighbor(int positionX,int positionY);
void fastCount(int positionX,int positionY,int addX,int addY,int count[2]);

int main(){
    initBoard();
    while(!win){
        switchPlayer();
        placeChess();
        updateBoard();
        checkWin();
    }
    endBoard();
}

void initBoard(){
    for(int i=0;i<17;i++){
        for(int j=0;j<17;j++){
            boardData[i][j]=0;
        }
    }
    player=-1;
    chessX=0;
    chessY=0;
    win=0;
    system("cls");
    setlocale(LC_ALL, "chs");
    wchar_t noChess=L'·';
    puts("");
    for(int i=0;i<10;i++){
        printf(" 0%d",i);
    }
    for(int i=10;i<17;i++){
        printf(" %d",i);
    }
    puts("");
    for(int i=1;i<10;i++){
        printf(" 0%d",i);
        for(int j=1;j<=15;j++){
            wprintf(L" %c",noChess);
        }
        printf(" 0%d\n",i);
    }
    for(int i=10;i<16;i++){
        printf(" %d",i);
        for(int j=1;j<=15;j++){
            wprintf(L" %c",noChess);
        }
        printf(" %d\n",i);
    }
    for(int i=0;i<10;i++){
        printf(" 0%d",i);
    }
    for(int i=10;i<17;i++){
        printf(" %d",i);
    }
    puts("");
    puts("");
}
void endBoard(){
    if(boardData[chessX][chessY]==1){
        puts("You win!");
    }else{
        puts("Computer win!");
    }
    Sleep(7000);
}
void switchPlayer(){
    if(player==1){
        player=-1;
    }else{
        player=1;
    }
}
void placeChess(){
    if(player==1){
        puts("It is turn to you!");
        do{
            scanf(" %d %d",&chessX,&chessY);
        }while((chessX<1)||(chessX>15)||(chessY<1)||(chessY>15)||boardData[chessX][chessY]);
    }else{
        puts("It is turn to computer!");
        AI();
    }
    puts("");
    puts("");
    boardData[chessX][chessY]=player;
}
void updateBoard() {
    system("cls");
    setlocale(LC_ALL,"chs");
    wchar_t blackChess=L'○',whiteChess=L'●',noChess=L'·';
    puts("");
    for(int i=0;i<10;i++){
        printf(" 0%d",i);
    }
    for(int i=10;i<17;i++){
        printf(" %d",i);
    }
    puts("");
    for(int i=1;i<10;i++){
        printf(" 0%d",i);
        for(int j=1;j<=15;j++){
            if(boardData[i][j]==1){
                wprintf(L" %c",blackChess);
            }else if(boardData[i][j]==-1){
                wprintf(L" %c",whiteChess);
            }else{
                wprintf(L" %c",noChess);
            }
        }
        printf(" 0%d\n",i);
    }
    for(int i=10;i<16;i++){
        printf(" %d",i);
        for(int j=1;j<=15;j++){
            if(boardData[i][j]==1){
                wprintf(L" %c",blackChess);
            }else if(boardData[i][j]==-1){
                wprintf(L" %c",whiteChess);
            }else{
                wprintf(L" %c",noChess);
            }
        }
        printf(" %d\n",i);
    }
    for(int i=0;i<10;i++){
        printf(" 0%d",i);
    }
    for(int i=10;i<17;i++){
        printf(" %d",i);
    }
    puts("");
    puts("");
}
void checkWin(){
    for(int i=0;i<4;i++){
        if((basicCount(chessX,chessY,add[i][0][0],add[i][0][1],0)+basicCount(chessX,chessY,add[i][1][0],add[i][1][1],0))>3){
            win=1;
            break;
        }
    }
}
int basicCount(int positionX,int positionY,int addX,int addY,int count){
    if(boardData[positionX+addX][positionY+addY]==boardData[positionX][positionY]){
        count++;
        return basicCount(positionX+addX,positionY+addY,addX,addY,count);
    }else{
        return count;
    }
}
void AI(){
    int bestScore=10000000;
    int predictedChess[150][2];
    predictChess(predictedChess);
    for(int i=1;i<predictedChess[0][0];i++){
        boardData[predictedChess[i][0]][predictedChess[i][1]]=-1;
        int score=maxLayer(DEPTH-1,bestScore,-10000000,predictedChess[i][0],predictedChess[i][1]);
        boardData[predictedChess[i][0]][predictedChess[i][1]]=0;
        if(score<bestScore){
            chessX=predictedChess[i][0];
            chessY=predictedChess[i][1];
            bestScore=score;
        }
    }
}
int maxLayer(int depth,int alpha,int beta,int positionX,int positionY){
    if((depth==0)||(fastCheckWin(positionX,positionY))){
        return evaluate();
    }else{
        int bestScore=-10000000;
        int predictedChess[150][2];
        predictChess(predictedChess);
        for(int i=1;i<predictedChess[0][0];i++){
            boardData[predictedChess[i][0]][predictedChess[i][1]]=1;
            int score;
            if(bestScore>beta){
                score=minLayer(depth-1,alpha,bestScore,predictedChess[i][0],predictedChess[i][1]);
            }else{
                score=minLayer(depth-1,alpha,beta,predictedChess[i][0],predictedChess[i][1]);
            }
            boardData[predictedChess[i][0]][predictedChess[i][1]]=0;
            if(score>alpha){
                return score;
            }
            if(score>bestScore){
                bestScore=score;
            }
        }
        return bestScore;
    }
}
int minLayer(int depth,int alpha,int beta,int positionX,int positionY){
    if((depth==0)||(fastCheckWin(positionX,positionY))){
        return evaluate();
    }else{
        int bestScore=10000000;
        int predictedChess[150][2];
        predictChess(predictedChess);
        for(int i=1;i<predictedChess[0][0];i++){
            boardData[predictedChess[i][0]][predictedChess[i][1]]=-1;
            int score;
            if(bestScore<alpha){
                score=maxLayer(depth-1,bestScore,beta,predictedChess[i][0],predictedChess[i][1]);
            }else{
                score=maxLayer(depth-1,alpha,beta,predictedChess[i][0],predictedChess[i][1]);
            }
            boardData[predictedChess[i][0]][predictedChess[i][1]]=0;
            if(score<beta){
                return score;
            }
            if(score<bestScore){
                bestScore=score;
            }
        }
        return bestScore;
    }
}
void predictChess(int predictedChess[150][2]){
    int chess[5][50][2];
    int chessCount[5]={0,0,0,0,0};
    for(int i=1;i<=15;i++){
        for(int j=1;j<=15;j++){
            if(boardData[i][j]==0){
                int level=hasNeighbor(i,j)-1;
                if(level>=0){
                    if(level<4){
                        chess[level][chessCount[level]][0]=i;
                        chess[level][chessCount[level]][1]=j;
                        chessCount[level]++;
                    }else{
                        chess[4][chessCount[4]][0]=i;
                        chess[4][chessCount[4]][1]=j;
                        chessCount[4]++;
                    }
                }
            }
        }
    }
    int predictedChessCount=1;
    for(int i=4;i>=0;i--){
        for(int j=0;j<chessCount[i];j++){
            predictedChess[predictedChessCount][0]=chess[i][j][0];
            predictedChess[predictedChessCount][1]=chess[i][j][1];
            predictedChessCount++;
        }
    }
    predictedChess[0][0]=predictedChessCount;
}
int fastCheckWin(int positionX,int positionY){
    for(int i=0;i<4;i++){
        int count=0;
        for(int j=0;j<2;j++){
            int tempChessX=positionX,tempChessY=positionY;
            while(boardData[tempChessX][tempChessY]==boardData[tempChessX+add[i][j][0]][tempChessY+add[i][j][1]]){
                count++;
                tempChessX+=add[i][j][0];
                tempChessY+=add[i][j][1];
            }
        }
        if(count>3){
            return 1;
        }
    }
    return 0;
}
int evaluate(){
    int score=0;
    for(int i=1;i<=15;i++){
        for(int j=1;j<=15;j++){
            if(boardData[i][j]){
                for(int k=0;k<4;k++){
                    int count1[2]={0,1},count2[2]={0,1};
                    fastCount(i,j,add[k][0][0],add[k][0][1],count1);
                    fastCount(i,j,add[k][1][0],add[k][1][1],count2);
                    if(count1[1]+count2[1]==0){
                        switch(count1[0]+count2[0]){
                            case 0:
                                score+=boardData[i][j];
                                break;
                            case 1:
                                score+=boardData[i][j]*5;
                                break;
                            case 2:
                                score+=boardData[i][j]*400;
                                break;
                            default:
                                score+=boardData[i][j]*4000;
                                break;
                        }
                    }else if(count1[1]+count2[1]==1){
                        switch(count1[0]+count2[0]){
                            case 0:
                                break;
                            case 1:
                                score+=boardData[i][j];
                                break;
                            case 2:
                                score+=boardData[i][j]*3;
                                break;
                            case 3:
                                score+=boardData[i][j]*200;
                                break;
                            default:
                                score+=boardData[i][j]*4000;
                                break;
                        }
                    }else if(count1[0]+count2[0]>3){
                        score+=4000*boardData[i][j];
                    }
                }
            }
        }
    }
    return score;
}
int hasNeighbor(int positionX,int positionY){
    int level=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<2;j++){
            if(boardData[positionX+add[i][j][0]][positionY+add[i][j][1]]){
                boardData[positionX][positionY]=boardData[positionX+add[i][j][0]][positionY+add[i][j][1]];
                int count1[2]={0,1},count2[2]={0,1};
                fastCount(positionX,positionY,add[i][0][0],add[i][0][1],count1);
                fastCount(positionX,positionY,add[i][1][0],add[i][1][1],count2);
                boardData[positionX][positionY]=0;
                int sum=count1[0]+count2[0]-count1[1]-count2[1]+2;
                if(sum>level){
                    level=sum;
                }
            }
        }
    }
    return level;
}
void fastCount(int positionX,int positionY,int addX,int addY,int count[2]){
    while(boardData[positionX+addX][positionY+addY]==boardData[positionX][positionY]){
        count[0]++;
        positionX+=addX;
        positionY+=addY;
    }
    if((positionX+addX>0)&&(positionX+addX<16)&&(positionY+addY>0)&&(positionY+addY<16)&&(boardData[positionX+addX][positionY+addY]==0)){
        count[1]=0;
    }
}

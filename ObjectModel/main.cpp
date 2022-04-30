#include <GL/glut.h>
#include <cmath>

#define DEPTH0 0.15
#define DEPTH1 0.3
#define DEPTH2 0.7
#define DEPTH3 0.85

enum VARY_MODE{NONE,TRANSLATE,ROTATE,SCALE};

typedef struct Point{
    GLfloat x,y,z;
    GLfloat r,g,b;
}Point;

typedef struct Clause{
    const char * label;
    char key;
}Clause;

int windowsSizeX,windowsSizeY;

int lastPositionX,lastPositionY;
enum VARY_MODE varyMode;
GLfloat varyAngle;
GLfloat varyX,varyY,varyZ;
GLfloat pastMatrix[4][4];

Point points[40]={
        {1.0,0.5,1.0,DEPTH1,DEPTH1,DEPTH1},
        {0.5,1.0,1.0,DEPTH1,DEPTH1,DEPTH1},
        {1.0,1.0,0.5,DEPTH1,DEPTH1,DEPTH1},
        {-0.5,-1.0,1.0,DEPTH2,DEPTH2,DEPTH2},
        {-1.0,-0.5,1.0,DEPTH2,DEPTH2,DEPTH2},
        {-1.0,-1.0,0.5,0.0,0.0,DEPTH3},
        {1.0,-1.0,-0.5,DEPTH2,DEPTH2,DEPTH2},
        {0.5,-1.0,-1.0,0.0,DEPTH3,0.0},
        {1.0,-0.5,-1.0,DEPTH2,DEPTH2,DEPTH2},
        {-1.0,1.0,-0.5,DEPTH2,DEPTH2,DEPTH2},
        {-1.0,0.5,-1.0,DEPTH3,0.0,0.0},
        {-0.5,1.0,-1.0,DEPTH2,DEPTH2,DEPTH2},
        {0.0,-1.0,1.0,0.0,DEPTH2,DEPTH2},
        {1.0,0.0,1.0,DEPTH1,DEPTH1,DEPTH1},
        {1.0,-1.0,0.0,0.0,DEPTH2,DEPTH2},
        {0.0,1.0,1.0,DEPTH1,DEPTH1,DEPTH1},
        {-1.0,0.0,1.0,DEPTH2,0.0,DEPTH2},
        {-1.0,1.0,0.0,DEPTH2,0.0,DEPTH2},
        {-1.0,-1.0,0.0,0.0,0.0,DEPTH3},
        {0.0,-1.0,-1.0,0.0,DEPTH3,0.0},
        {-1.0,0.0,-1.0,DEPTH3,0.0,0.0},
        {1.0,1.0,0.0,DEPTH1,DEPTH1,DEPTH1},
        {1.0,0.0,-1.0,DEPTH2,DEPTH2,0.0},
        {0.0,1.0,-1.0,DEPTH2,DEPTH2,0.0},

        {1.5,1.5,1.5,DEPTH0,DEPTH0,DEPTH0},
        {1.5,1.5,0.0,DEPTH1,DEPTH1,DEPTH1},
        {1.5,0.0,1.5,DEPTH1,DEPTH1,DEPTH1},
        {0.0,1.5,1.5,DEPTH1,DEPTH1,DEPTH1},
        {-1.5,-1.5,1.5,0.0,0.0,DEPTH3},
        {-1.5,-1.5,0.0,0.0,0.0,DEPTH3},
        {-1.5,0.0,1.5,DEPTH2,0.0,DEPTH2},
        {0.0,-1.5,1.5,0.0,DEPTH2,DEPTH2},
        {-1.5,1.5,-1.5,DEPTH3,0.0,0.0},
        {-1.5,1.5,0.0,DEPTH2,0.0,DEPTH2},
        {-1.5,0.0,-1.5,DEPTH3,0.0,0.0},
        {0.0,1.5,-1.5,DEPTH2,DEPTH2,0.0},
        {1.5,-1.5,-1.5,0.0,DEPTH3,0.0},
        {1.5,-1.5,0.0,0.0,DEPTH2,DEPTH2},
        {1.5,0.0,-1.5,DEPTH2,DEPTH2,0.0},
        {0.0,-1.5,-1.5,0.0,DEPTH3,0.0},
};

GLfloat initialMatrix[4][4]={
        {1.0,0.0,0.0,0.0},
        {0.0,1.0,0.0,0.0},
        {0.0,0.0,1.0,0.0},
        {0.0,0.0,0.0,1.0},
};

Clause menu[5]={
        {"Reset",'0'},
        {"Translate",'t'},
        {"Rotate",'r'},
        {"Scale",'s'},
        {"Exit",27},
};

void pointColor(int point){
    glColor3fv((GLfloat *)(points+point)+3);
    glVertex3fv((GLfloat *)(points+point));
}
void polygon8(int point1,int point2,int point3,int point4,int point5,int point6,int point7,int point8){
    glBegin(GL_POLYGON);
    pointColor(point1);
    pointColor(point2);
    pointColor(point3);
    pointColor(point4);
    pointColor(point5);
    pointColor(point6);
    pointColor(point7);
    pointColor(point8);
    glEnd();
}
void polygon3(int point1,int point2,int point3){
    glBegin(GL_POLYGON);
    pointColor(point1);
    pointColor(point2);
    pointColor(point3);
    glEnd();
}
void module(){
    polygon8(0,13,14,6,8,22,21,2);
    polygon8(1,15,16,4,3,12,13,0);
    polygon8(2,21,23,11,9,17,15,1);
    polygon8(10,20,18,5,4,16,17,9);
    polygon8(7,19,20,10,11,23,22,8);
    polygon8(5,18,19,7,6,14,12,3);
    for(int k=0;k<=21;k+=3){
        polygon3(k,k+1,k+2);
    }

    for(int k=0;k<=12;k+=4){
        polygon3(k+24,k+25,k+26);
        polygon3(k+24,k+27,k+25);
        polygon3(k+24,k+26,k+27);
        polygon3(k+25,k+27,k+26);
    }
}

void userEventAction(char key){
    switch(key){
        case '0':
            varyMode=NONE;
            varyAngle=0.0;
            varyX=0.0;
            varyY=0.0;
            varyZ=0.0;
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    pastMatrix[i][j]=initialMatrix[i][j];
                }
            }
            break;
        case 't':
            varyMode=TRANSLATE;
            break;
        case 'r':
            varyMode=ROTATE;
            break;
        case 's':
            varyMode=SCALE;
            break;
        case 27:
            exit(0);
        default:
            break;
    }
    glutPostRedisplay();
}
void keyBoard(unsigned char key,int x,int y){
    userEventAction((char)key);
}
void selectMenu(int choice){
    userEventAction(menu[choice].key);
}

void MouseButton(int button,int state,int x,int y){
    if((button==GLUT_LEFT_BUTTON)&&(state==GLUT_DOWN)){
        lastPositionX=x;
        lastPositionY=y;
    }else if((button==GLUT_LEFT_BUTTON)&&(state==GLUT_UP)){
        varyAngle=0.0;
        varyX=0.0;
        varyY=0.0;
        varyZ=0.0;
    }
}
void MouseMotion(int x,int y){
    GLfloat dx=(GLfloat)(x-lastPositionX)/(GLfloat)windowsSizeX;
    GLfloat dy=(GLfloat)(y-lastPositionY)/(GLfloat)windowsSizeY;
    switch(varyMode){
        case TRANSLATE:
            varyX=(dx*10.0);
            varyY=(-dy*10.0);
            varyZ=0.0;
            break;
        case ROTATE:
            varyAngle=(sqrt(pow(dx,2)+pow(dy,2))*300.0);
            varyX=dy;
            varyY=dx;
            varyZ=0.0;
            break;
        case SCALE:
            varyX=(dx*3.0);
            varyY=(dy*3.0);
            varyZ=0.0;
            break;
        default:
            break;
    }
    lastPositionX=x;
    lastPositionY=y;
    glutPostRedisplay();
}

void init(){
    windowsSizeX=1;
    windowsSizeY=1;
    lastPositionX=0;
    lastPositionY=0;
    varyMode=NONE;
    varyAngle=0.0;
    varyX=0.0;
    varyY=0.0;
    varyZ=0.0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            pastMatrix[i][j]=initialMatrix[i][j];
        }
    }

    for(int i=0;i<sizeof(menu)/sizeof(Clause);i++){
        glutAddMenuEntry(menu[i].label,i);
    }

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glClearColor(DEPTH0,DEPTH0,DEPTH0,0.0);
}

void reshape(int width,int height){
    windowsSizeX=width;
    windowsSizeY=height;
    GLdouble rate=(GLdouble)height/(GLdouble)width;

    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0,5.0,-rate*5.0,rate*5.0,-5.0,5.0);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    switch(varyMode){
        case TRANSLATE:
            glTranslatef(varyX,varyY,varyZ);
            break;
        case ROTATE:
            glRotatef(varyAngle,varyX,varyY,varyZ);
            break;
        case SCALE:
            glScalef(varyX+1.0,varyY+1.0,varyZ+1.0);
            break;
        default:
            break;
    }
    glMultMatrixf((GLfloat *)pastMatrix);
    glGetFloatv(GL_MODELVIEW_MATRIX,(GLfloat *)pastMatrix);

    module();

    glFlush();
    glutSwapBuffers();
}

int main(int argc,char ** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Fading:3D Module");

    glutKeyboardFunc(keyBoard);
    glutCreateMenu(selectMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMouseFunc(MouseButton);
    glutMotionFunc(MouseMotion);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    init();

    glutMainLoop();

    return 0;
}

#include <GL/glut.h>

#define S 50
#define L 150

GLubyte image1[4][4][3]={
        {{S,S,S},{L,L,L},{L,L,L},{S,S,S}},
        {{L,L,L},{S,S,S},{S,S,S},{L,L,L}},
        {{L,L,L},{S,S,S},{S,S,S},{L,L,L}},
        {{S,S,S},{L,L,L},{L,L,L},{S,S,S}},
};
GLubyte image2[4][4][3]={
        {{S,S,S},{S,S,S},{L,L,L},{L,L,L}},
        {{S,S,S},{L,L,L},{S,S,S},{L,L,L}},
        {{L,L,L},{S,S,S},{L,L,L},{S,S,S}},
        {{L,L,L},{L,L,L},{S,S,S},{S,S,S}},
};

GLfloat lightPosition[4]={1,1,1,1};
GLfloat lightReflectedPosition[4]={1,-5,1,1};
GLfloat room[8][3]={{2,2,2},{2,2,-2},{2,-2,2},{2,-2,-2},{-2,2,2},{-2,2,-2},{-2,-2,2},{-2,-2,-2}};

GLfloat dx[3]={4,0,0};
GLfloat dy[3]={0,4,0};
GLfloat dz[3]={0,0,4};

void polygon(GLfloat origin[3],const GLfloat ds[3],const GLfloat dt[3]){
    GLfloat ps[3]={ds[0]/16,ds[1]/16,ds[2]/16};
    GLfloat pt[3]={dt[0]/16,dt[1]/16,dt[2]/16};
    for(int s=0;s<16;s++){
        for(int t=0;t<16;t++){
            glBegin(GL_POLYGON);
            glTexCoord2f(0.0,0.0);
            glVertex3f(origin[0]+(GLfloat)s*ps[0]+(GLfloat)t*pt[0],origin[1]+(GLfloat)s*ps[1]+(GLfloat)t*pt[1],origin[2]+(GLfloat)s*ps[2]+(GLfloat)t*pt[2]);
            glTexCoord2f(1.0,0.0);
            glVertex3f(origin[0]+(GLfloat)(s+1)*ps[0]+(GLfloat)t*pt[0],origin[1]+(GLfloat)(s+1)*ps[1]+(GLfloat)t*pt[1],origin[2]+(GLfloat)(s+1)*ps[2]+(GLfloat)t*pt[2]);
            glTexCoord2f(1.0,1.0);
            glVertex3f(origin[0]+(GLfloat)(s+1)*ps[0]+(GLfloat)(t+1)*pt[0],origin[1]+(GLfloat)(s+1)*ps[1]+(GLfloat)(t+1)*pt[1],origin[2]+(GLfloat)(s+1)*ps[2]+(GLfloat)(t+1)*pt[2]);
            glTexCoord2f(0.0,1.0);
            glVertex3f(origin[0]+(GLfloat)s*ps[0]+(GLfloat)(t+1)*pt[0],origin[1]+(GLfloat)s*ps[1]+(GLfloat)(t+1)*pt[1],origin[2]+(GLfloat)s*ps[2]+(GLfloat)(t+1)*pt[2]);
            glEnd();
        }
    }
}

void top(){
    glBindTexture(GL_TEXTURE_2D,1);
    GLfloat matDiffuse[4]={0.7,0.7,0.3,1.0};
    glMaterialfv(GL_FRONT,GL_DIFFUSE,matDiffuse);
    glNormal3f(0.0,-1.0,0.0);
    polygon(room[5],dx,dz);
}
void around(){
    glBindTexture(GL_TEXTURE_2D,2);
    GLfloat matDiffuse[4]={0.3,0.3,0.7,1.0};
    glMaterialfv(GL_FRONT,GL_DIFFUSE,matDiffuse);
    glNormal3f(0.0,0.0,1.0);
    polygon(room[7],dx,dy);
    glNormal3f(1.0,0.0,0.0);
    polygon(room[7],dy,dz);
    glNormal3f(-1.0,0.0,0.0);
    polygon(room[3],dz,dy);
}
void object(){
    glBindTexture(GL_TEXTURE_2D,0);
    GLfloat matDiffuse[4]={0.7,0.3,0.3,1.0};
    glMaterialfv(GL_FRONT,GL_DIFFUSE,matDiffuse);
    glutSolidSphere(0.5,32,32);
}
void bottom(){
    glBindTexture(GL_TEXTURE_2D,0);
    glColor4f(0.3,0.3,0.3,0.7);
    glNormal3f(0.0,1.0,0.0);
    polygon(room[7],dz,dx);
}
void roomExceptBottom(){
    GLfloat matSpecular[4]={0.5,0.5,0.5,1.0};
    glMaterialfv(GL_FRONT,GL_SPECULAR,matSpecular);
    glMaterialf(GL_FRONT,GL_SHININESS,100);
    top();
    around();
    glPushMatrix();
    glTranslatef(-0.5,-1.5,-0.5);
    object();
    glPopMatrix();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,3,0,0,0,0,1,0);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
    roomExceptBottom();
    glLightfv(GL_LIGHT0,GL_POSITION,lightReflectedPosition);
    glPushMatrix();
    glTranslatef(0,-4,0);
    glScalef(1,-1,1);
    roomExceptBottom();
    glPopMatrix();
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    bottom();
    glFlush();
}
void reshape(int width,int height){
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120,(GLfloat)width/(GLfloat)height,1,6);
}
void init(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHT0);
    glBindTexture(GL_TEXTURE_2D,1);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,4,4,0,GL_RGB,GL_UNSIGNED_BYTE,image1);
    glBindTexture(GL_TEXTURE_2D,2);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,4,4,0,GL_RGB,GL_UNSIGNED_BYTE,image2);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glClearColor(0,0,0,0);
}

int main(int argc,char ** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("MIRROR");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}

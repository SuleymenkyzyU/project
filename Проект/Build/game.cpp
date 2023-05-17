#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <GL/glut.h>
#include <math.h>
#include <string>
#include <sstream>
using namespace std;

#define M_PI 3.14159265358979323846


float corZ=-60;

//for moving
float corMovingTowerX=0;
float corMovingTowerSpeed=0.015;
float corMovingTowerBorder1=10;
float corMovingTowerBorder2=-10;
//Translate Screen
float windowSpeed=0.05;
float timeWindow=0;
//pushtower
float corPushTowerX=NULL;
bool pushState=false;
bool firstPush=false;
//choosescreen
int  activeScreen=1;
//menu
int activeButton=1;
//towers
int endTower=0;
int towerArray[][2]={{0,5}};
//for finish screen
bool finishScreen=false;
float totalScore=0;
float calculateScore(float score){
    totalScore=totalScore+score;
    return totalScore/endTower+1;
}
//initials
void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);}
 //Drawing text 2D screen.
void drawText(const char *text, int length, int x, int y){
     glMatrixMode(GL_PROJECTION); // change the current matrix to PROJECTION
     double matrix[16]; // allocate 16-byte in memory (thanks to BlueByteGames about memory-leak warning comment on YouTube)
     glGetDoublev(GL_PROJECTION_MATRIX, matrix); // get the values from PROJECTION matrix to local variable
     glLoadIdentity(); // reset PROJECTION matrix to identity matrix
     glOrtho(0, 800, 0, 600, -5, 5); // orthographic perspective
     glMatrixMode(GL_MODELVIEW); // change current matrix to MODELVIDE matrix again
     glLoadIdentity(); // reset it to identity matrix
     glPushMatrix(); // push current state of MODELVIEW matrix to stack
     glLoadIdentity(); // reset it again. (may not be required, but it my convention
     glRasterPos2i(x, y); // raster position in 2D
     for(int i=0; i<length; i++){
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]); // generation of characters in our text with 9 by 15 GLU font
     }
     glPopMatrix(); // get MODELVIEW matrix value from stack
     glMatrixMode(GL_PROJECTION); // change current matrix mode to PROJECTION
     glLoadMatrixd(matrix); // reset
     glMatrixMode(GL_MODELVIEW); // change current matrix mode to MODELVIEW
}
void drawFloor(){

    glBegin(GL_QUADS);
        glColor3f(0,0.4,0);
		glVertex3f(100,-20, corZ);
		glVertex3f(-100,-20, corZ);
		glColor3f(0.5,0.8,0);
		glVertex3f(-100,-35, corZ);
		glVertex3f(100,-35, corZ);

    glEnd();
}
void drawTower(int positionOfX,int positionOfY){

    glBegin(GL_QUADS);
        glColor3f(0.2,0.26,0.13);
		glVertex3f(positionOfX+4,positionOfY-4.0, corZ);
		glVertex3f(positionOfX-4,positionOfY-4.0, corZ);
		glColor3f(1,0.56,0.13);
		glVertex3f(positionOfX-4,positionOfY+4.0, corZ);
		glVertex3f(positionOfX+4,positionOfY+4.0, corZ);
        glEnd();
    glColor3f(0.17,0.1,0.5);
    	glBegin(GL_QUADS);
		glVertex3f(positionOfX+5,positionOfY-5.0, corZ);
		glVertex3f(positionOfX-5,positionOfY-5.0, corZ);
		glVertex3f(positionOfX-5,positionOfY+5.0, corZ);
		glVertex3f(positionOfX+5,positionOfY+5.0, corZ);
        glEnd();

}
void drawSky(){
    	glBegin(GL_QUADS);
    	glColor3f(0.0,1.0,1);
		glVertex3f(100.0, -100.0, corZ);
		glVertex3f(100.0,100.0, corZ);
		glColor3f(0.0,1.0,0.5);
		glVertex3f(-100.0,100.0, corZ);
		glVertex3f(-100.0,-100.0, corZ);
        glEnd();

}
void drawHook(){
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
        glVertex3f(corMovingTowerX,38.0, corZ);
        glVertex3f(corMovingTowerX,38.0, corZ);
        glVertex3f(10,100,corZ);
        glVertex3f(-10,100,corZ);
        glEnd();

        glColor3f(0,0,0);
        glBegin(GL_QUADS);
        glVertex3f(corMovingTowerX+7.3,36,corZ);
        glVertex3f(corMovingTowerX+5.1,30,corZ);
        glVertex3f(corMovingTowerX+5.1,35,corZ);
        glVertex3f(corMovingTowerX,38, corZ);
        glEnd();
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
        glVertex3f(corMovingTowerX-7.3,36,corZ);
        glVertex3f(corMovingTowerX-5.1,30,corZ);
        glVertex3f(corMovingTowerX-5.1,35,corZ);
        glVertex3f(corMovingTowerX,38, corZ);
        glEnd();
        if(!pushState || firstPush){
            glBegin(GL_QUADS);
            glColor3f(0.2,0.26,0.13);
            glVertex3f(corMovingTowerX+4.0,26.0, corZ);
            glVertex3f(corMovingTowerX-4.0,26.0, corZ);
            glColor3f(1,0.56,0.13);
            glVertex3f(corMovingTowerX-4.0,34.0, corZ);
            glVertex3f(corMovingTowerX+4.0,34.0, corZ);
            glEnd();
            glBegin(GL_QUADS);
            glColor3f(0.17,0.1,0.5);
            glVertex3f(corMovingTowerX+5.0,25.0, corZ);
            glVertex3f(corMovingTowerX-5.0,25.0, corZ);
            glColor3f(0.17,0.1,1);
            glVertex3f(corMovingTowerX-5.0,35.0, corZ);
            glVertex3f(corMovingTowerX+5.0,35.0, corZ);
            glEnd();}
    }
void drawMovingTower(){
    if(pushState || firstPush){
    	glBegin(GL_QUADS);
    	glColor3f(0.2,0.26,0.13);
		glVertex3f(corPushTowerX+4.0,-timeWindow+26.0, corZ);
		glVertex3f(corPushTowerX-4.0,-timeWindow+26.0, corZ);
		glColor3f(1,0.56,0.13);
		glVertex3f(corPushTowerX-4.0,-timeWindow+34.0, corZ);
		glVertex3f(corPushTowerX+4.0,-timeWindow+34.0, corZ);
        glEnd();
    glColor3f(0.17,0.1,0.5);
    	glBegin(GL_QUADS);
		glVertex3f(corPushTowerX+5.0,-timeWindow+25.0, corZ);
		glVertex3f(corPushTowerX-5.0,-timeWindow+25.0, corZ);
		glVertex3f(corPushTowerX-5.0,-timeWindow+35.0, corZ);
		glVertex3f(corPushTowerX+5.0,-timeWindow+35.0, corZ);
        glEnd();
}

}
void drawBestScore(){
     glColor3f(1,0,1);
    	glBegin(GL_QUADS);
		glVertex3f(100.0, 0.0, corZ);
		glVertex3f(100.0,100.0, corZ);
		glVertex3f(-100.0,100.0, corZ);
		glVertex3f(-100.0,0.0, corZ);
        glEnd();
        if(activeScreen==3){
            std::string bestScore;
            bestScore = "Best Score";
            glColor3f(0, 0, 0);
            drawText(bestScore.data(),bestScore.size(),358,320);
        }
}
void drawScore(){
    if(activeScreen==2){
                glBegin(GL_QUADS);
                    glVertex3f(-25, 50, corZ);
                    glColor3f(0.8,1,1);
                    glVertex3f(-25,40, corZ);
                    glColor3f(0,1,1);
                    glVertex3f(-40.0,40, corZ);
                    glColor3f(0.8,0,1);
                    glVertex3f(-40.0,50, corZ);
                glEnd();
                std::string textBestScores;
                textBestScores = std::to_string(endTower);
                glColor3f(0, 0, 0);
                drawText(textBestScores.data(),textBestScores.size(),40,550);
    }
}
void drawGame(){
    drawHook();
    drawMovingTower();
    for(int i=0;i<=endTower;i++){
            drawTower(towerArray[i][0],towerArray[i][1]);

    }
    drawScore();
    if(endTower<2 && activeScreen==2){
        drawFloor();
    }
    drawSky();

}
void drawMenu(){
                if(activeButton==1){
                    glBegin(GL_QUADS);
                    glVertex3f(10.0, 30.5, corZ);
                    glColor3f(0.7,0,1);
                    glVertex3f(10.0,26.5, corZ);
                    glVertex3f(-10.0,26.5, corZ);
                    glColor3f(1,1,1);
                    glVertex3f(-10.0,30.5, corZ);
                    glEnd();
                }else if(activeButton==2){
                    glBegin(GL_QUADS);
                    glVertex3f(10.0, 25.5, corZ);
                    glColor3f(1,1,1);
                    glVertex3f(10.0,21.5, corZ);
                    glVertex3f(-10.0,21.5, corZ);
                    glColor3f(0.7,0,1);
                    glVertex3f(-10.0,25.5, corZ);
                    glEnd();
                }

       glBegin(GL_QUADS);
    	glColor3f(0.0,1.0,1);
		glVertex3f(100.0, -100.0, corZ);
		glVertex3f(100.0,100.0, corZ);
		glColor3f(0.0,1.0,0.5);
		glVertex3f(-100.0,100.0, corZ);
		glVertex3f(-100.0,-100.0, corZ);
        glEnd();


        std::string textStartGame;
        textStartGame = "Start Game";
        glColor3f(0, 0, 0);
        drawText(textStartGame.data(), textStartGame.size(), 340, 380);

        std::string textBestScores;
        textBestScores = "Best Score";
        glColor3f(0, 0, 0);
        drawText(textBestScores.data(),textBestScores.size(),338,320);

}
void drawScoreScreen(){
    glBegin(GL_QUADS);
    	glColor3f(1.0,1.0,1);
		glVertex3f(100.0, -100.0, corZ);
		glVertex3f(100.0,100.0, corZ);
		glColor3f(1.0,1.0,0.5);
		glVertex3f(-100.0,100.0, corZ);
		glVertex3f(-100.0,-100.0, corZ);
        glEnd();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,-21,0);

    switch(activeScreen){
        case 1:
            drawMenu();
        case 2:
            drawGame();
        case 3:
            drawBestScore();
        case 4:
            drawScoreScreen();
    }
}


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    int loop=1;
    SDL_Event myevent;
    init();
    while (loop==1)
    {
        //Keyboard Functions
        while (SDL_PollEvent(&myevent))
        {
            switch(myevent.type)
            {
                case SDL_QUIT:
                loop=0;
                break;

                case SDL_KEYDOWN:
                    switch(activeScreen){
                        case 1:
                            if(myevent.key.keysym.sym==SDLK_UP){
                                if(activeButton!=1){
                                    activeButton--;
                                }
                            }
                            if(myevent.key.keysym.sym==SDLK_DOWN){
                                if(activeButton!=2){
                                    activeButton++;
                                }
                            }
                            if(myevent.key.keysym.sym==SDLK_RSHIFT){
                                    activeScreen=activeButton+1;

                            }

                        case 2:
                            if(myevent.key.keysym.sym==SDLK_ESCAPE){
                                corMovingTowerX=0;
                                corMovingTowerSpeed=0.02;
                                corMovingTowerBorder1=15;
                                corMovingTowerBorder2=-15;
                                //Translate Screen
                                timeWindow=0;
                            }
                            if(myevent.key.keysym.sym==SDLK_SPACE){
                                firstPush=true;
                                timeWindow=0;
                                corPushTowerX=corMovingTowerX;
                                pushState?pushState=false:pushState=true;
                                endTower++;
                                towerArray[endTower+1][0]=corPushTowerX;
                                towerArray[endTower+1][1]=15;
                                if(endTower>1){
                                     for(int i=0;i<=endTower;i++){
                                    towerArray[i][1]=towerArray[i][1]-10;}
                                }



                            }
                        case 3:
                            if(myevent.key.keysym.sym==SDLK_ESCAPE){
                                activeScreen=1;
                            }

                    }

                break;
            }
        }
        //Screen Function
        if(activeScreen==2){
            int hit=-1;
            if(1){
                corMovingTowerX=corMovingTowerSpeed+corMovingTowerX;
            }
            if(corMovingTowerX>corMovingTowerBorder1){
                corMovingTowerSpeed=corMovingTowerSpeed*hit;
            }
            if(corMovingTowerX<corMovingTowerBorder2){
                corMovingTowerSpeed=corMovingTowerSpeed*hit;
            }

            if(firstPush==true && timeWindow<=15){
                timeWindow=timeWindow+windowSpeed;
            }
        }


        display();
        SDL_GL_SwapBuffers();

    }
    SDL_Quit();
    return 0;
}



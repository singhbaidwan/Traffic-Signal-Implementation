#ifdef __APPLE__
#include <GLUT/glut.h>
#include <stdlib.h>
#else
#include <GL/glut.h>
#endif
#include<math.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include<vector>
#include <iostream>
using namespace std;
#define SPEED 40        //speed of traffic
float x=0.0;//movement of car
float x_bird = 0;
float x_cloud= 0;
int light=1;        //1 for green-light, 0 for red-light
int day=1;        //1 for day, 0 for night
int d,flag=0;
int rain = 0;
int birdFrameNumber = 0;
void drawBird()
{
    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2f(203+x_bird,602);
    glVertex2f(200+x_bird,600);
    glVertex2f(197+x_bird,602);
    glVertex2f(200+x_bird,598);
    glEnd();
}

void showDird()
{
    int xPos = 0;
    for(int i=0; i<3; i++)
    {
        glPushMatrix();
        glTranslatef(xPos, 0, 0);
        glTranslated(-10+birdFrameNumber,30,0);
        drawBird();
        glPopMatrix();
        xPos=xPos+10;
    }
    xPos = 5;
    for(int i=0; i<2; i++)
    {
        glPushMatrix();
        glTranslatef(xPos, -10, 0);
        glTranslated(-10+birdFrameNumber,30,0);
        drawBird();
        glPopMatrix();
        xPos=xPos+10;
    }

    xPos = -70;
    for(int i=0; i<3; i++)
    {
        glPushMatrix();
        glTranslatef(xPos, -30, 0);
        glTranslated(-10+birdFrameNumber,30,0);
        drawBird();
        glPopMatrix();
        xPos=xPos+10;
    }
    xPos = -65;
    for(int i=0; i<2; i++)
    {
        glPushMatrix();
        glTranslatef(xPos, -40, 0);
        glTranslated(-10+birdFrameNumber,30,0);
        drawBird();
        glPopMatrix();
        xPos=xPos+10;
    }
}

int snowX,snowY;
float snowWX,snowWY;

void snow()
{
    for(int i=1;i<=1000;i++)
    {
        snowX=rand(),snowY=rand();
        snowX%=2000; snowY%=2000;
        glColor3f(1,1,1);
        glBegin(GL_LINES);
        glLineWidth(12);
        glVertex2d(snowX,snowY);
        glVertex2d(snowX+2,snowY);
        glEnd();
    }
}
void drawSnow()
{
    snowWX -= 0.5;
    snowWY -= 0.5;
    if(snowWX == -600 || snowWY == -600)
    {
        snowWX = 6;
        snowWY = 300;
    }
    glPushMatrix();
    glTranslatef(snowWX, snowWY, 0);
    snow();
    glPopMatrix();
}
void draw_pixel(GLint cx,GLint cy)
{
    glBegin(GL_POINTS);
    glVertex2i(cx,cy);
    glEnd();
}


void plotpixels(GLint h,GLint k,GLint x,GLint y)
{
    draw_pixel(x+h,y+k);
    draw_pixel(-x+h,y+k);
    draw_pixel(x+h,-y+k);
    draw_pixel(-x+h,-y+k);
    draw_pixel(y+h,x+k);
    draw_pixel(-y+h,x+k);
    draw_pixel(y+h,-x+k);
    draw_pixel(-y+h,-x+k);
}


void draw_circle(GLint h,GLint k,GLint r)
{
    GLint D=1-r , x=0 , y=r;
    while(y>x)
    {
        plotpixels(h,k,x,y);
        if(D<0)
            D+=2*x+3;
        else
        {
            D+=2*(x-y)+5;
            --y;
        }
        ++x;
    }
    plotpixels(h,k,x,y);
}


void draw_object()
{
    //int d;
    if(day==1)
    {
        //int d;
        //day sky
        glColor3f(0.15,0.86,0.88);
        glBegin(GL_POLYGON);
        glVertex2f(0,400);
        glVertex2f(0,700);
        glVertex2f(1000,700);
        glVertex2f(1000,400);
        glEnd();


        //sun
        for(d=0;d<=30;d++)
        {
            glColor3f(0.96,0.27,0.13);
            draw_circle(875,625,d);
        }


        //clouds
        if(x_cloud+75>1000)
            x_cloud = 0;
        for(int val = 0;val<1000;val+=300){
        for(d=0;d<=25;d++)
        {
            
            glColor3f(1.0,1.0,1.0);
            draw_circle(75+val+x_cloud,615,d);
            draw_circle(115+val+x_cloud,635,d);
            draw_circle(100+val+x_cloud,590,d);
            draw_circle(130+val+x_cloud,590,d);
            draw_circle(160+val+x_cloud,615,d);
        }
        
        }
        
        //sun
        for(d=0;d<=30;d++)
        {
            glColor3f(1.0,1.0,0);
            draw_circle(875,625,d);
        }


    }
    else if(day==2)
    {
        //night sky
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glVertex2f(0,400);
        glVertex2f(0,700);
        glVertex2f(1000,700);
        glVertex2f(1000,400);
        glEnd();


        //moon
        for(d=0;d<=30;d++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(100,625,d);
        }
        //star
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(520,630);
        glVertex2f(534,630);
        glVertex2f(527,644);
        glVertex2f(520,639);
        glVertex2f(534,639);
        glVertex2f(527,625);
        glEnd();


        //star
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(250,550);
        glVertex2f(264,550);
        glVertex2f(257,564);
        glVertex2f(250,559);
        glVertex2f(264,559);
        glVertex2f(257,545);
        glEnd();


        //star
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(320,680);
        glVertex2f(334,680);
        glVertex2f(327,694);
        glVertex2f(320,689);
        glVertex2f(334,689);
        glVertex2f(327,675);
        glEnd();


        //star
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(640,600);
        glVertex2f(654,600);
        glVertex2f(647,614);
        glVertex2f(640,609);
        glVertex2f(654,609);
        glVertex2f(647,595);
        glEnd();


        //star
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(770,520);
        glVertex2f(784,520);
        glVertex2f(777,534);
        glVertex2f(770,529);
        glVertex2f(784,529);
        glVertex2f(777,515);
        glEnd();


        //star
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(900,590);
        glVertex2f(914,590);
        glVertex2f(907,604);
        glVertex2f(900,599);
        glVertex2f(914,599);
        glVertex2f(907,585);
        glEnd();
    }
    else if(day==3)
    {
        //night sky
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glVertex2f(0,400);
        glVertex2f(0,700);
        glVertex2f(1000,700);
        glVertex2f(1000,400);
        glEnd();
        
        if(x_cloud+75>1000)
            x_cloud = 0;
        for(int val = 0;val<1000;val+=300){
        for(d=0;d<=25;d++)
        {
            
            glColor3f(1.0f, 1.0f, 1.0f);
            draw_circle(75+val+x_cloud,615,d);
            draw_circle(115+val+x_cloud,635,d);
            draw_circle(100+val+x_cloud,590,d);
            draw_circle(130+val+x_cloud,590,d);
            draw_circle(160+val+x_cloud,615,d);
        }
        
        }

    }
    //road
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(0,200);
    glVertex2f(1000,200);
    glVertex2f(1000,0);
    glEnd();


    //divider on the road
    for(d=0;d<1000;d+=200)
    {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_POLYGON);
        glVertex2f(d,90);
        glVertex2f(d,110);
        glVertex2f(125+d,110);
        glVertex2f(125+d,90);
        glEnd();
    }


    //building 1
    glColor3f(0.81,0.60,0.28);
    glBegin(GL_POLYGON);
    glVertex2f(0,200);
    glVertex2f(0,500);
    glVertex2f(325,500);
    glVertex2f(325,200);
    glEnd();
        
    //window 1
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(25,400);
    glVertex2f(25,475);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(100,475);
    glVertex2f(100,400);
    glEnd();
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(25,400);
    glVertex2f(25,475);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(100,400);
    glVertex2f(100,475);
    glEnd();
    
    //window 2
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(125,400);
    glVertex2f(125,475);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(200,475);
    glVertex2f(200,400);
    glEnd();
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(125,400);
    glVertex2f(125,475);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(200,475);
    glVertex2f(200,400);
    glEnd();
    
    //window 3
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(225,400);
    glVertex2f(225,475);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(300,475);
    glVertex2f(300,400);
    glEnd();
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(225,400);
    glVertex2f(225,475);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(300,475);
    glVertex2f(300,400);
    glEnd();
    
    //window 4
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(25,300);
    glVertex2f(25,375);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(100,375);
    glVertex2f(100,300);
    glEnd();
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(25,300);
    glVertex2f(25,375);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(100,300);
    glVertex2f(100,375);
    glEnd();
    
    //window 5
    
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(225,300);
    glVertex2f(225,375);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(300,375);
    glVertex2f(300,300);
    glEnd();
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(225,300);
    glVertex2f(225,375);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(300,375);
    glVertex2f(300,300);
    glEnd();
    
    //window 7
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(225,220);
    glVertex2f(225,275);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(300,275);
    glVertex2f(300,220);
    glEnd();
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(225,220);
    glVertex2f(225,275);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(300,275);
    glVertex2f(300,220);
    glEnd();
    // window 6
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(25,220);
    glVertex2f(25,275);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(100,275);
    glVertex2f(100,220);
    glEnd();
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(25,220);
    glVertex2f(25,275);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(100,220);
    glVertex2f(100,275);
    glEnd();
    
    
    //door
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(125,200);
    glVertex2f(125,350);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(200,350);
    glVertex2f(200,200);
    glEnd();


    //building 2
    glColor3f(0.55,0.14,0.14);
    glBegin(GL_POLYGON);
    glVertex2f(325,200);
    glVertex2f(325,575);
    glVertex2f(750,575);
    glVertex2f(750,200);
    glEnd();


    //window 1,2,3
    for(d=375;d<=625;d+=125)
    {
        glColor3f(0.52,0.63,0.60);
        glBegin(GL_POLYGON);
        glVertex2f(d,475);
        glVertex2f(d,550);
        glColor3f(0.19,0.29,0.26);
        glVertex2f(75+d,550);
        glVertex2f(75+d,475);
        glEnd();
    }
    
    for(d=375;d<=625;d+=125)
    {
        glColor3f(0.52,0.63,0.60);
        glBegin(GL_POLYGON);
        glVertex2f(d,375);
        glVertex2f(d,450);
        glColor3f(0.19,0.29,0.26);
        glVertex2f(75+d,450);
        glVertex2f(75+d,375);
        glEnd();
    }

    //window 4
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(375,275);
    glVertex2f(375,350);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(450,350);
    glVertex2f(450,275);
    glEnd();
    
    //window 4
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(625,275);
    glVertex2f(625,350);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(700,350);
    glVertex2f(700,275);
    glEnd();
    //door
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(490,200);
    glVertex2f(490,350);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(585,350);
    glVertex2f(585,200);
    glEnd();
    
    
    //building 3
   
    glColor3f(0.81,0.60,0.28);
    glBegin(GL_POLYGON);
    glVertex2f(750,200);
    glVertex2f(750,500);
    glVertex2f(1000,500);
    glVertex2f(1000,200);
    glEnd();
    
    // window 1
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(775,400);
    glVertex2f(775,475);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(850,475);
    glVertex2f(850,400);
    glEnd();
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(775,400);
    glVertex2f(775,475);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(850,475);
    glVertex2f(850,400);
    glEnd();
    
    // window 2
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(775,300);
    glVertex2f(775,375);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(850,375);
    glVertex2f(850,300);
    glEnd();
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(775,300);
    glVertex2f(775,375);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(850,375);
    glVertex2f(850,300);
    glEnd();
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(775,210);
    glVertex2f(775,275);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(850,275);
    glVertex2f(850,210);
    glEnd();
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(775,210);
    glVertex2f(775,275);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(850,275);
    glVertex2f(850,210);
    glEnd();
    
    // window 1
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(900,400);
    glVertex2f(900,475);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(1000,475);
    glVertex2f(1000,400);
    glEnd();
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(900,400);
    glVertex2f(900,475);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(1000,475);
    glVertex2f(1000,400);
    glEnd();
    
    // window 2
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(900,300);
    glVertex2f(900,375);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(1000,375);
    glVertex2f(1000,300);
    glEnd();
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(900,300);
    glVertex2f(900,375);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(1000,375);
    glVertex2f(1000,300);
    glEnd();
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(900,210);
    glVertex2f(900,275);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(1000,275);
    glVertex2f(1000,210);
    glEnd();
    
    glColor3f(0.52,0.63,0.60);
    glBegin(GL_POLYGON);
    glVertex2f(900,210);
    glVertex2f(900,275);
    glColor3f(0.19,0.29,0.26);
    glVertex2f(1000,275);
    glVertex2f(1000,210);
    glEnd();
    
    //signal
    glColor3f(0.40,0.21,0.17);
    glBegin(GL_POLYGON);
    glVertex2f(920,200);
    glVertex2f(920,325);
    glVertex2f(945,325);
    glVertex2f(945,200);
    glEnd();

    glColor3f(0.87,0.82,0.81);
    glBegin(GL_POLYGON);
    glVertex2f(895,325);
    glVertex2f(895,475);
    glVertex2f(970,475);
    glVertex2f(970,325);
    glEnd();


    for(d=0;d<=20;d++)
    {
        glColor3f(0.0,0.0,0.0);
        draw_circle(932.5,450,d);
        glColor3f(1.0,1.0,0.0);
        draw_circle(932.5,400,d);
        glColor3f(0.0,1.0,0.0);
        draw_circle(932.5,350,d);
    }
    
    
//
//    if(480+x>1050)
//    {
//        x=0;
//    }
    if(x_bird+197>1000)
        x_bird=0;
    if(day==3)
    {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_POLYGON);
        glVertex2f(900, 200);
        glVertex2f(900,250);
        glVertex2f(920,250);
        glVertex2f(920,200);
        glEnd();

    }
    //car1
    glColor3f(0.70,0.10,0.25);
    glBegin(GL_POLYGON);
    glVertex2f(50+x,150);
    glVertex2f(35+x,165);
    glVertex2f(35+x,200);
    glVertex2f(125+x,250);
    glVertex2f(250+x,250);
    glVertex2f(300+x,200);
    glVertex2f(400+x,175);
    glVertex2f(400+x,160);
    glVertex2f(380+x,150);
    glEnd();


    //car1 window1
    glColor3f(0.4,0.4,0.4);
    glBegin(GL_POLYGON);
    glVertex2f(200+x,200);
    glColor3f(0.1,0.1,0.1);
    glVertex2f(200+x,235);
    glColor3f(0.4,0.4,0.4);
    glVertex2f(240+x,235);
    glColor3f(0.1,0.1,0.1);
    glVertex2f(275+x,200);
    glEnd();
    
    //car1 window2
    glColor3f(0.4,0.4,0.4);
    glBegin(GL_POLYGON);
    glVertex2f(75+x,200);
    glColor3f(0.1,0.1,0.1);
    glVertex2f(140+x,235);
    glColor3f(0.4,0.4,0.4);
    glVertex2f(180+x,235);
    glColor3f(0.1,0.1,0.1);
    glVertex2f(180+x,200);
    glEnd();


    //car1-lights
    //rear
    glColor3f(0.89,0.47,0.20);
    glBegin(GL_POLYGON);
    glVertex2f(35+x,175);
    glVertex2f(35+x,200);
    glColor3f(1.0,1.0,0.0);
    glVertex2f(50+x,200);
    glVertex2f(50+x,175);
    glEnd();


    //front
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(380+x,165);
    glVertex2f(380+x,175);
    glColor3f(0.89,0.47,0.20);
    glVertex2f(400+x,175);
    glVertex2f(400+x,165);
    glEnd();


    //car2
    glColor3f(0.14,0.42,0.55);
    glBegin(GL_POLYGON);
    glVertex2f(480+x,150);
    glVertex2f(480+x,200);
    glVertex2f(530+x,300);
    glVertex2f(705+x,300);
    glVertex2f(770+x,225);
    glVertex2f(830+x,190);
    glVertex2f(830+x,150);
    glEnd();


    //car2-window1
    glColor3f(0.4,0.4,0.4);
    glBegin(GL_POLYGON);
    glVertex2f(630+x,225);
    glColor3f(0.1,0.1,0.1);
    glVertex2f(630+x,285);
    glColor3f(0.4,0.4,0.4);
    glVertex2f(695+x,285);
    glColor3f(0.1,0.1,0.1);
    glVertex2f(725+x,225);
    glEnd();
    
    //car2-window2
    glColor3f(0.4,0.4,0.4);
    glBegin(GL_POLYGON);
    glVertex2f(530+x,225);
    glColor3f(0.1,0.1,0.1);
    glVertex2f(555+x,285);
    glColor3f(0.4,0.4,0.4);
    glVertex2f(615+x,285);
    glColor3f(0.1,0.1,0.1);
    glVertex2f(615+x,225);
    glEnd();
    
    //car2-lights
    //front
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(805+x,175);
    glVertex2f(805+x,195);
    glColor3f(0.89,0.47,0.20);
    glVertex2f(830+x,190);
    glVertex2f(830+x,175);
    glEnd();


    //rear
    glColor3f(0.89,0.47,0.20);
    glBegin(GL_POLYGON);
    glVertex2f(480+x,175);
    glVertex2f(480+x,200);
    glColor3f(1.0,1.0,0.0);
    glVertex2f(505+x,200);
    glVertex2f(505+x,175);
    glEnd();


    //car1-wheels
    for(d=0;d<=30;d++)
    {
        glColor3f(0.075,0.075,0.075);
        draw_circle(125+x,150,d);
        glColor3f(0.075,0.075,0.075);
        draw_circle(275+x,150,d);
    }


    //car2-wheels
    for(d=0;d<=40;d++)
    {
        glColor3f(0.075,0.075,0.075);
        draw_circle(565+x,150,d);
        glColor3f(0.075,0.075,0.075);
        draw_circle(730+x,150,d);
    }
    
    drawBird();
    showDird();
    if(day==3)
    {


        snow();
        drawSnow();
    }
}


void signal()
{
    if(light==0)
    {
        for(d=0;d<=20;d++)
        {
            glColor3f(1.0,0.0,0.0);
            draw_circle(932.5,450,d);
            glColor3f(0.0,0.0,0.0);
            draw_circle(932.5,350,d);
        }
    }
    else
    {
        for(d=0;d<=20;d++)
        {
            glColor3f(0.0,0.0,0.0);
                draw_circle(932.5,450,d);
            glColor3f(0.0,1.0,0.0);
            draw_circle(932.5,350,d);
        }
    }
}


void keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 'r':
        case 'R': light=0;
                  break;
        case 'g':
        case 'G': light=1;
                  break;
        case 13 : flag=1;
                   break;
        case 'm':
        case 'M':day=1;
                 break;
        case 'k':
        case 'K':day=2;
                 break;
        case 'n':
        case 'N':
            day = 3;
            break;
    }
}


void idle()
{
    if(flag==1)
    {
        x_bird+=SPEED/12;
        x_cloud+=SPEED/24;
        glClearColor(1.0,1.0,1.0,1.0);
        if(light==0 && (x>=100 && x<=500))
        {
            x+=SPEED/4;
        }
        if(light==0 && (x>=530 && x<=1020))
        {
            x+=SPEED/4;
        }
        if(light==1)
        {
            x+=SPEED/4;
        }
        glutPostRedisplay();
    }
}


void main_menu(int index)
{
    switch(index)
    {
    case 1: day=1;
                break;


        case 2: day=0;
                break;


        case 3: exit(0);
                break;
    }
}


void myinit()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,1.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1000.0,0.0,700.0);
}


void drawstring(int x,int y,char *string)
{
    char *str;
    glRasterPos2f(x,y);
    for(str=string;*str!='\0';str++)
    {
        glColor3f(1.0,1.0,1.0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*str);
    }
}


void frontscreen()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    drawstring(280,670,"Thapar Institute of Engineering and Technology");
    drawstring(365,560,"A PROJECT ON");
    drawstring(330,510,"TRAFFIC SIGNAL");
    drawstring(330,350,"BY :");
    drawstring(330,300,"Dalveer Singh [101903193]");
    drawstring(330,250,"Pavneet Bedi  [101903181]");
    drawstring(330,200,"APRUM PAL SINGH [102083062]");
    drawstring(330,120,"PRESS  ENTER  TO  START");
    drawstring(345,90,"Press R for vehicles to stop");
    drawstring(335,60,"Press G for vehicles to move");
    glFlush();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(flag==0)
        frontscreen();
    if(flag==1)
    {
        draw_object();
        signal();
    }
    glFlush();
}




int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1000.0,700.0);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Traffic Signal");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    myinit();
    glutCreateMenu(main_menu);
    glutAddMenuEntry("Day",1);
    glutAddMenuEntry("Night",2);
    glutAddMenuEntry("Quit",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
}

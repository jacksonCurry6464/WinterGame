//Final Project Polar Highway
//Jackson Curry


#include "CSCIx229.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//MY VARIABLES
int orbit=0;
//END MY VARIABLES
int axes=1;       //  Display axes
int mode=1;       //  Projection mode
int move=1;       //  Move light
int th=-245;         //  Azimuth of view angle
int ph=10;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int obj=0;        //  Scene/opbject selection
double asp=1;     //  Aspect ratio
double dim=16;     //  Size of world
// Light values
int light     =   1;  // Lighting
int one       =   1;  // Unit value
int distance  =   10;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   =  50;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   9;  // Elevation of light
static float Position[4];  //defining the position of the light as an array of 4 values last one is for directional
int snowStorm =0;              //this variable defines whether or not there is a foggy snowstorm!
float myFogColor[3] = {0.8f,0.8f,0.8f};   //color of the fog
typedef struct {float x,y,z;} vtx;
typedef struct {int A,B,C;} tri;
#define n 500
vtx is[n];


unsigned int texture[35];
int rep = 1;

double notCreated = 1;




//This is a function that will return the normal vector for a surface containing 3 points (it is stored in the normal vector)  NOTE THAT THE POINTS MUST BE GIVEN IN COUNTER CLOCKWISE ORDER!!
void jacksonNormal(float *normal,float*point1,float*point2,float*point3)
{
      //printf("%8.3f", point1[0]);
      float vec1[] = {point2[0]-point1[0],point2[1]-point1[1],point2[2]-point1[2]};
      float vec2[] = {point3[0]-point1[0],point3[1]-point1[1],point3[2]-point1[2]};
      normal[0] = vec1[1]*vec2[2]-vec1[2]*vec2[1];
      normal[1] = -(vec1[0]*vec2[2]-vec1[2]*vec2[0]);
      normal[2] = vec1[0]*vec2[1]-vec1[1]*vec2[0];
}



void jacksonCylinder(double x, double y, double z, double height, double radius, double rotation, int roundnessVar, double currTexture)
{
  //glTranslated(x,y,z);
  glPushMatrix();
  glRotated(rotation,1,0,0);

   //first drawing circle on top
  float jacksP1[3] = {x,y,z};
  float jacksP2[3] = {x,y,z+1};
  float jacksP3[3] = {x+1,y,z};
  float myNormalVec[3] = {0};
  jacksonNormal(myNormalVec,jacksP1,jacksP2,jacksP3);
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(1,1,1);
  glNormal3f(myNormalVec[0],myNormalVec[1],myNormalVec[2]);
  glVertex3f(x,y,z);
  //int currAngle = 0;
  for (int i=0;i<roundnessVar;i+=1)
  {
    //currAngle = roundnessVar%360;
    glVertex3f(x+radius*Sin(i),y,z+radius*Cos(i));
  }
  glEnd();

  //done with the top of the cylinder
  //now doing bottom of the cylinder
  float BjacksP1[3] = {x,y-height,z};
  float BjacksP2[3] = {x+1,y-height,z};
  float BjacksP3[3] = {x,y-height,z+1};
  float BmyNormalVec[3] = {0};
  jacksonNormal(BmyNormalVec,BjacksP1,BjacksP2,BjacksP3);
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(1,1,1);
  glNormal3f(BmyNormalVec[0],BmyNormalVec[1],BmyNormalVec[2]);
  glVertex3f(x,y-height,z);
  for (int i=0;i<roundnessVar;i+=1)
  {
    glVertex3f(x+radius*Sin(i),y-height,z+radius*Cos(i));
  }
  glEnd();


  //now doing sides of cylinder
  glBegin(GL_QUADS);
  for(int i=0;i<roundnessVar;i+=1)
  {
    jacksP1[0] = x+radius*Sin(i);
    jacksP1[1] = y;
    jacksP1[2] = z+radius*Cos(i);

    jacksP2[0] = x+radius*Sin(i);
    jacksP2[1] = y-height;
    jacksP2[2] = z+radius*Cos(i);

    jacksP3[0] = x+radius*Sin(i+1);
    jacksP3[1] = y-height;
    jacksP3[2] = z+radius*Cos(i+1);

    jacksonNormal(myNormalVec,jacksP1,jacksP2,jacksP3);

    glNormal3f(myNormalVec[0],myNormalVec[1],myNormalVec[2]);
    glVertex3f(x+radius*Sin(i), y, z+radius*Cos(i));
    glVertex3f(x+radius*Sin(i),y-height,z+radius*Cos(i));
    glVertex3f(x+radius*Sin(i+1),y-height,z+radius*Cos(i+1));
    glVertex3f(x+radius*Sin(i+1),y,z+radius*Cos(i+1));
  }
  glEnd();
  glPopMatrix();

}

void jacksonCylinder2(double x, double y, double z, double xRotation, double yRotation, double zRotation, double dx, double dy, double dz, double height, double radius, int roundnessVar, int currTexture)
{
  //glTranslated(x,y,z);
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(xRotation,1,0,0);
  glRotated(yRotation,0,1,0);
  glRotated(zRotation,0,0,1);
  glScaled(dx,dy,dz);

   //first drawing circle on top
  float jacksP1[3] = {0,0,0};
  float jacksP2[3] = {0,0,1};
  float jacksP3[3] = {1,0,0};
  float myNormalVec[3] = {0};
  jacksonNormal(myNormalVec,jacksP1,jacksP2,jacksP3);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture[currTexture]);
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(1,1,1);
  glNormal3f(myNormalVec[0],myNormalVec[1],myNormalVec[2]);

  glTexCoord2f(0.5,0.5);
  glVertex3f(0,0,0);
  //int currAngle = 0;
  for (int i=0;i<=roundnessVar;i+=1)
  {
    //currAngle = roundnessVar%360;
    glTexCoord2f(0.5+0.5*Sin(i),0.5+0.5*Cos(i));
    glVertex3f(radius*Sin(i),0,radius*Cos(i));
  }
  //glTexCoord2f(0.5,1);
  //glVertex3f(radius*Sin())
  glEnd();

  //done with the top of the cylinder
  //now doing bottom of the cylinder
  float BjacksP1[3] = {0,-height,0};
  float BjacksP2[3] = {1,height,0};
  float BjacksP3[3] = {0,height,1};
  float BmyNormalVec[3] = {0};
  jacksonNormal(BmyNormalVec,BjacksP1,BjacksP2,BjacksP3);

  glBindTexture(GL_TEXTURE_2D,texture[currTexture]);
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(1,1,1);
  glNormal3f(BmyNormalVec[0],BmyNormalVec[1],BmyNormalVec[2]);
  glTexCoord2f(0.5,0.5);
  glVertex3f(0,-height,0);
  for (int i=0;i<roundnessVar;i+=1)
  {
    glTexCoord2f(0.5+0.5*Sin(i),0.5+0.5*Cos(i));
    glVertex3f(radius*Sin(i),-height,radius*Cos(i));
  }
  glEnd();


  //now doing sides of cylinder

  glBindTexture(GL_TEXTURE_2D,texture[currTexture]);
  glBegin(GL_QUADS);
  for(int i=0;i<roundnessVar;i+=1)
  {
    jacksP1[0] = radius*Sin(i);
    jacksP1[1] = 0;
    jacksP1[2] = radius*Cos(i);

    jacksP2[0] = radius*Sin(i);
    jacksP2[1] = -height;
    jacksP2[2] = radius*Cos(i);

    jacksP3[0] = radius*Sin(i+1);
    jacksP3[1] = -height;
    jacksP3[2] = radius*Cos(i+1);

    jacksonNormal(myNormalVec,jacksP1,jacksP2,jacksP3);

    /*
    glNormal3f(myNormalVec[0],myNormalVec[1],myNormalVec[2]);
    glTexCoord2f(i*1/roundnessVar,1);
    glVertex3f(radius*Sin(i), 0, radius*Cos(i));
    glTexCoord2f(i*1/roundnessVar,0);
    glVertex3f(radius*Sin(i),-height,radius*Cos(i));
    glTexCoord2f((i*1+1)/roundnessVar,0);
    glVertex3f(radius*Sin(i+1),-height,radius*Cos(i+1));
    glTexCoord2f((i*1+1)/roundnessVar,0);
    glVertex3f(radius*Sin(i+1),0,radius*Cos(i+1));
    */

    glNormal3f(myNormalVec[0],myNormalVec[1],myNormalVec[2]);
    glTexCoord2f(i/360,1);
    glVertex3f(radius*Sin(i), 0, radius*Cos(i));
    glTexCoord2f(i/360,0);
    glVertex3f(radius*Sin(i),-height,radius*Cos(i));
    //glTexCoord2f((i*1+1)/roundnessVar,0);
    glTexCoord2f(i+1/360,0);
    glVertex3f(radius*Sin(i+1),-height,radius*Cos(i+1));
    //glTexCoord2f((i*1+1)/roundnessVar,0);
    glTexCoord2f(i+1/360,1);
    glVertex3f(radius*Sin(i+1),0,radius*Cos(i+1));
    //if(i==359)
    //{
    //  printf("%s\n","made it!");
    //}
  }


  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

}


static void jacksonCone(double x, double y, double z, double xRotation, double yRotation, double zRotation, double dx, double dy, double dz, double height, double radius, int roundnessVar, int currTexture)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(xRotation,1,0,0);
  glRotated(yRotation,0,1,0);
  glRotated(zRotation,0,0,1);
  glScaled(dx,dy,dz);

  //first drawing circle on top
  float jacksP1[3] = {0,0,0};
  float jacksP2[3] = {0,0,1};
  float jacksP3[3] = {1,0,0};
  float myNormalVec[3] = {0};
  jacksonNormal(myNormalVec,jacksP1,jacksP2,jacksP3);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture[currTexture]);
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(1,1,1);
  glNormal3f(myNormalVec[0],myNormalVec[1],myNormalVec[2]);
  glTexCoord2f(0.5,0.5);
  glVertex3f(0,0,0);
  //int currAngle = 0;
  for (int i=0;i<roundnessVar;i+=1)
  {
    //currAngle = roundnessVar%360;
    glTexCoord2f(0.5+0.5*Sin(i),0.5+0.5*Cos(i));
    glVertex3f(radius*Sin(i),0,radius*Cos(i));
  }
  glEnd();

  //NOW I NEED TO DO THE SIDES OF THE CONE
  glBegin(GL_TRIANGLES);
  for(int i=0;i<roundnessVar; i+=1)
  {
    //first point is the top of the cone which will be used in every triangle
    jacksP1[0] = 0;
    jacksP1[1] = height;
    jacksP1[2] = 0;

    jacksP2[0] = radius*Sin(i);
    jacksP2[1] = 0;
    jacksP2[2] = radius*Cos(i);

    jacksP3[0] = radius*Sin(i+1);
    jacksP3[1] = 0;
    jacksP3[2] = radius*Cos(i+1);

    jacksonNormal(myNormalVec,jacksP1,jacksP2,jacksP3);

    glNormal3f(myNormalVec[0],myNormalVec[1],myNormalVec[2]);
    glTexCoord2f(1,1);
    glVertex3f(0,height,0);
    glTexCoord2f((i+1)/roundnessVar,0); 
    glVertex3f(radius*Sin(i+1),0,radius*Cos(i+1));
    glTexCoord2f(i/roundnessVar,0);
    glVertex3f(radius*Sin(i),0,radius*Cos(i));
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glPopMatrix();
}



static void jacksonBackgroundMountains(double myDim)
{
   glPushMatrix();
   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D);

   //  Sides
   glBindTexture(GL_TEXTURE_2D,texture[14]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0.2); glVertex3f(-myDim, -myDim, -myDim);
   glTexCoord2f(1,0.2); glVertex3f(+myDim, -myDim, -myDim);
   glTexCoord2f(1,1); glVertex3f(+myDim, +myDim, -myDim);
   glTexCoord2f(0,1); glVertex3f(-myDim, +myDim, -myDim);
   glEnd();


   glBindTexture(GL_TEXTURE_2D,texture[16]);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0.2); glVertex3f(+myDim, -myDim, -myDim);
   glTexCoord2f(1,0.2); glVertex3f(+myDim, -myDim, +myDim);
   glTexCoord2f(1,1); glVertex3f(+myDim, +myDim, +myDim);
   glTexCoord2f(0,1); glVertex3f(+myDim, +myDim, -myDim);
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[17]);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0.2); glVertex3f(+myDim, -myDim, +myDim);
   glTexCoord2f(1,0.2); glVertex3f(-myDim, -myDim, +myDim);
   glTexCoord2f(1,1); glVertex3f(-myDim, +myDim, +myDim);
   glTexCoord2f(0,1); glVertex3f(+myDim, +myDim, +myDim);
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[13]);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0.2); glVertex3f(-myDim, -myDim, +myDim);
   glTexCoord2f(1,0.2); glVertex3f(-myDim, -myDim, -myDim);
   glTexCoord2f(1,1); glVertex3f(-myDim, +myDim, -myDim);
   glTexCoord2f(0,1); glVertex3f(-myDim, +myDim, +myDim);
   glEnd();

   //  Top and bottom
   glBindTexture(GL_TEXTURE_2D,texture[18]);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0,0); glVertex3f(+myDim, +myDim, -myDim);
   glTexCoord2f(1,0); glVertex3f(+myDim, +myDim, +myDim);
   glTexCoord2f(1,1); glVertex3f(-myDim, +myDim, +myDim);
   glTexCoord2f(0,1); glVertex3f(-myDim, +myDim, -myDim);
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[15]);
   glBegin(GL_QUADS);
   glTexCoord2f(0,1); glVertex3f(-myDim, -myDim, +myDim);
   glTexCoord2f(1,0); glVertex3f(+myDim, -myDim, +myDim);
   glTexCoord2f(1,1); glVertex3f(+myDim, -myDim, -myDim);
   glTexCoord2f(0,1); glVertex3f(-myDim, -myDim, -myDim);
   glEnd();

   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}







//THIS IS MY VERSION OF A CUBE USED TO TEST MY NORMAL VECTOR FINDING FUNCTION!!
static void jacksonCube(double x,double y,double z,double xRotation, double yRotation, double zRotation, double dx,double dy,double dz, int currTex, double repititions)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   //glMaterialfv(GL_FRONT_AND_BACK,{1,1,1,1},white);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(xRotation,1,0,0);
   glRotated(yRotation,0,1,0);
   glRotated(zRotation,0,0,1);
   glScaled(dx,dy,dz);
   //  Cube

   //PUTTING IN MY TEXTURES
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[currTex]);



   float jacksP1[3] = {-1,-1,1};
   float jacksP2[3] = {1,-1,1};
   float jacksP3[3] = {1,1,1};
   float myNormalVec[3] = {0};
   jacksonNormal(myNormalVec,jacksP1,jacksP2,jacksP3);

   glBegin(GL_QUADS);
   //  Front
   glColor3f(1,1,1);
   glNormal3f(myNormalVec[0],myNormalVec[1],myNormalVec[2]);
   glTexCoord2f(0,0);glVertex3f(-1,-1, 1);
   glTexCoord2f(repititions,0);glVertex3f(+1,-1, 1);                       //I HAVE TO MULTIPLY MY TEXTURE COORDINATES BY THE AMOUNT I AM STRETCHING EACH OF THE DIMENSIONS TO KEEP THINGS LOOKING GOOD
   glTexCoord2f(repititions,repititions);glVertex3f(+1,+1, 1);
   glTexCoord2f(0,repititions);glVertex3f(-1,+1, 1);
   glEnd();

   //glDisable(GL_TEXTURE_2D);

   float newjacksP1[3] = {1,-1,-1};
   float newjacksP2[3] = {-1,-1,-1};
   float newjacksP3[3] = {-1,1,-1};
   float newNormalVec[3] = {0};
   jacksonNormal(newNormalVec,newjacksP1,newjacksP2,newjacksP3);

   glBegin(GL_QUADS);
   //  Back
   glColor3f(1,1,1);
   glNormal3f(newNormalVec[0],newNormalVec[1],newNormalVec[2]);
   glTexCoord2f(0,0);glVertex3f(+1,-1,-1);
   glTexCoord2f(repititions,0);glVertex3f(-1,-1,-1);
   glTexCoord2f(repititions,repititions);glVertex3f(-1,+1,-1);
   glTexCoord2f(0,repititions);glVertex3f(+1,+1,-1);
   glEnd();

  

   glBegin(GL_QUADS);
   //  Right
   glColor3f(1,1,1);
   glNormal3f(+4, 0, 0);
   glTexCoord2f(0,0);glVertex3f(+1,-1,+1);
   glTexCoord2f(repititions,0);glVertex3f(+1,-1,-1);
   glTexCoord2f(repititions,repititions);glVertex3f(+1,+1,-1);
   glTexCoord2f(0,repititions);glVertex3f(+1,+1,+1);
   glEnd();
   //  Left
   glBegin(GL_QUADS);
   glColor3f(1,1,1);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0);glVertex3f(-1,-1,-1);
   glTexCoord2f(repititions,0);glVertex3f(-1,-1,+1);
   glTexCoord2f(repititions,repititions);glVertex3f(-1,+1,+1);
   glTexCoord2f(0,repititions);glVertex3f(-1,+1,-1);
   glEnd();
   //  Top
   glBegin(GL_QUADS);
   glColor3f(1,1,1);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0);glVertex3f(-1,+1,+1);
   glTexCoord2f(repititions,0);glVertex3f(+1,+1,+1);
   glTexCoord2f(repititions,repititions);glVertex3f(+1,+1,-1);
   glTexCoord2f(0,repititions);glVertex3f(-1,+1,-1);
   glEnd();
   //  Bottom
   glBegin(GL_QUADS);
   glColor3f(1,1,1);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(0,0);glVertex3f(-1,-1,-1);
   glTexCoord2f(repititions,0);glVertex3f(+1,-1,-1);
   glTexCoord2f(repititions,repititions);glVertex3f(+1,-1,+1);
   glTexCoord2f(0,repititions);glVertex3f(-1,-1,+1);
   //  End
   glEnd();
   //  Undo transofrmations
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}

//THIS VERSIOIN OF THE CUBE WILL MAKE THE REPITITIONS OF TEXTURE EQUAL TO THE AMOUNT IT IS BEING SCALED BY
static void jacksonAutoTextureCube(double x,double y,double z,double xRotation, double yRotation, double zRotation, double dx,double dy,double dz, int currTex, double repititions)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   //glMaterialfv(GL_FRONT_AND_BACK,{1,1,1,1},white);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(xRotation,1,0,0);
   glRotated(yRotation,0,1,0);
   glRotated(zRotation,0,0,1);
   glScaled(dx,dy,dz);
   //  Cube

   //PUTTING IN MY TEXTURES
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[currTex]);



   float jacksP1[3] = {-1,-1,1};
   float jacksP2[3] = {1,-1,1};
   float jacksP3[3] = {1,1,1};
   float myNormalVec[3] = {0};
   jacksonNormal(myNormalVec,jacksP1,jacksP2,jacksP3);

   glBegin(GL_QUADS);
   //  Front
   glColor3f(1,1,1);
   glNormal3f(myNormalVec[0],myNormalVec[1],myNormalVec[2]);
   glTexCoord2f(0,0);glVertex3f(-1,-1, 1);
   glTexCoord2f(repititions*dx,0);glVertex3f(+1,-1, 1);                       //I HAVE TO MULTIPLY MY TEXTURE COORDINATES BY THE AMOUNT I AM STRETCHING EACH OF THE DIMENSIONS TO KEEP THINGS LOOKING GOOD
   glTexCoord2f(repititions*dx,repititions*dy);glVertex3f(+1,+1, 1);
   glTexCoord2f(0,repititions*dy);glVertex3f(-1,+1, 1);
   glEnd();

   //glDisable(GL_TEXTURE_2D);

   float newjacksP1[3] = {1,-1,-1};
   float newjacksP2[3] = {-1,-1,-1};
   float newjacksP3[3] = {-1,1,-1};
   float newNormalVec[3] = {0};
   jacksonNormal(newNormalVec,newjacksP1,newjacksP2,newjacksP3);

   glBegin(GL_QUADS);
   //  Back
   glColor3f(1,1,1);
   glNormal3f(newNormalVec[0],newNormalVec[1],newNormalVec[2]);
   glTexCoord2f(0,0);glVertex3f(+1,-1,-1);
   glTexCoord2f(repititions*dx,0);glVertex3f(-1,-1,-1);
   glTexCoord2f(repititions*dx,repititions*dx);glVertex3f(-1,+1,-1);
   glTexCoord2f(0,repititions*dy);glVertex3f(+1,+1,-1);
   glEnd();

  

   glBegin(GL_QUADS);
   //  Right
   glColor3f(1,1,1);
   glNormal3f(+4, 0, 0);
   glTexCoord2f(0,0);glVertex3f(+1,-1,+1);
   glTexCoord2f(repititions*dz,0);glVertex3f(+1,-1,-1);
   glTexCoord2f(repititions*dz,repititions*dy);glVertex3f(+1,+1,-1);
   glTexCoord2f(0,repititions*dy);glVertex3f(+1,+1,+1);
   glEnd();
   //  Left
   glBegin(GL_QUADS);
   glColor3f(1,1,1);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0);glVertex3f(-1,-1,-1);
   glTexCoord2f(repititions*dz,0);glVertex3f(-1,-1,+1);
   glTexCoord2f(repititions*dz,repititions*dy);glVertex3f(-1,+1,+1);
   glTexCoord2f(0,repititions*dy);glVertex3f(-1,+1,-1);
   glEnd();
   //  Top
   glBegin(GL_QUADS);
   glColor3f(1,1,1);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0);glVertex3f(-1,+1,+1);
   glTexCoord2f(repititions*dx,0);glVertex3f(+1,+1,+1);
   glTexCoord2f(repititions*dx,repititions*dz);glVertex3f(+1,+1,-1);
   glTexCoord2f(0,repititions*dz);glVertex3f(-1,+1,-1);
   glEnd();
   //  Bottom
   glBegin(GL_QUADS);
   glColor3f(1,1,1);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(0,0);glVertex3f(-1,-1,-1);
   glTexCoord2f(repititions*dx,0);glVertex3f(+1,-1,-1);
   glTexCoord2f(repititions*dx,repititions*dz);glVertex3f(+1,-1,+1);
   glTexCoord2f(0,repititions*dz);glVertex3f(-1,-1,+1);
   //  End
   glEnd();
   //  Undo transofrmations
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}


/*
static void jacksonMansion(double x, double y, double z, double xRotation, double yRotation, double zRotation, double dx, double dy, double dz)
{
	glPushMatrix();
	glTranslated(x,y,z);
    glRotated(xRotation,1,0,0);
    glRotated(yRotation,0,1,0);
    glRotated(zRotation,0,0,1);
    glScaled(dx,dy,dz);
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);


    glPopMatrix();

}
*/

//Current texture should be 7
static void jacksonsStar(double x, double y, double z, double xRotation, double yRotation, double zRotation, double dx, double dy, double dz,int currTexture)
{
  glPushMatrix();

  glTranslated(x,y,z);
  glRotated(xRotation,1,0,0);
  glRotated(yRotation,0,1,0);
  glRotated(zRotation,0,0,1);
  glScaled(dx,dy,dz);
  float white[] = {1,1,1,1};
  float black[] = {0,0,0,1};
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

  //glBegin(GL_LINE_LOOP);
  //glColor3f(0,1,1);
  //glVertex3f(x,y,z);
  //glVertex3f(x+0.55,y+0.4,z);
  //glVertex3f(x+1.1,y,z);
  //glVertex3f(x+1,y+0.8,z);
  //glVertex3f(x+1.55,y+1.15,z);
  //glVertex3f(x+0.8,y+1.15,z);
  //glVertex3f(x+0.55,y+1.8,z);
  //glVertex3f(x+0.30,y+1.15,z);
  //glVertex3f(x-0.45,y+1.15,z);
  //glVertex3f(x+0.1,y+0.8,z);
  //glEnd();                        //NEED THIS OTHERWISE IT GETS WONKY!!

  float AjacksP1[3] = {0,0,0};
  float AjacksP2[3] = {2,3,0};
  float AjacksP3[3] = {2,3,0};
  float AmyNormalVec[3] = {0};
  jacksonNormal(AmyNormalVec,AjacksP1,AjacksP2,AjacksP3);

  //HERE I AM PUTTING IN MY TEXTURES FOR THE STAR
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glBindTexture(GL_TEXTURE_2D,texture[currTexture]);


  glColor3f(1,1,0);
  glBegin(GL_TRIANGLES);
  glNormal3f(-AmyNormalVec[0],-AmyNormalVec[1],-AmyNormalVec[2]);

  //front face
  //triangle 1
  glTexCoord2f(0.5,1);glVertex3f(0,0,0);
  glTexCoord2f(0,0);glVertex3f(-2,-3,0);
  glTexCoord2f(0,1);glVertex3f(2,-3,0);
  glEnd();

  //triangle 2
  float BjacksP1[3] = {0,-4,0};
  float BjacksP2[3] = {-2,-1,0};
  float BjacksP3[3] = {2,-1,0};
  float BmyNormalVec[3] = {0};
  jacksonNormal(BmyNormalVec,BjacksP1,BjacksP2,BjacksP3);
  glBegin(GL_TRIANGLES);
  glNormal3f(BmyNormalVec[0],BmyNormalVec[1],BmyNormalVec[2]);
  glTexCoord2f(0.5,-1);glVertex3f(0,-4,0);
  glTexCoord2f(0,0);glVertex3f(-2,-1,0);
  glTexCoord2f(0,1);glVertex3f(2,-1,0);
  glEnd();

  //back face

  //triangle 1
  float CjacksP1[3] = {0,0,1};
  float CjacksP2[3] = {-2,-3,1};
  float CjacksP3[3] = {2,-3,1};
  float CmyNormalVec[3] = {0};
  jacksonNormal(CmyNormalVec,CjacksP1,CjacksP2,CjacksP3);
  glBegin(GL_TRIANGLES);
  glNormal3f(CmyNormalVec[0],CmyNormalVec[1],CmyNormalVec[2]);
  glTexCoord2f(0.5,1);glVertex3f(0,0,1);
  glTexCoord2f(0,0);glVertex3f(-2,-3,1);
  glTexCoord2f(0,1);glVertex3f(2,-3,1);
  glEnd();

  //triangle 2
  float DjacksP1[3] = {0,-4,1};
  float DjacksP2[3] = {-2,-1,1};
  float DjacksP3[3] = {2,-1,1};
  float DmyNormalVec[3] = {0};
  jacksonNormal(DmyNormalVec,DjacksP1,DjacksP2,DjacksP3);
  glBegin(GL_TRIANGLES);
  glNormal3f(-DmyNormalVec[0],-DmyNormalVec[1],-DmyNormalVec[2]);
  glTexCoord2f(0.5,-1);glVertex3f(0,-4,1);
  glTexCoord2f(0,0);glVertex3f(-2,-1,1);
  glTexCoord2f(0,1);glVertex3f(2,-1,1);
  glEnd();

  //Now I must do the sides to close the surface
  float EjacksP1[3] = {0,0,0};
  float EjacksP2[3] = {0,0,1};
  float EjacksP3[3] = {-2,-3,1};
  float EmyNormalVec[3] = {0};
  jacksonNormal(EmyNormalVec,EjacksP1,EjacksP2,EjacksP3);
  glBegin(GL_QUADS);
  glNormal3f(-EmyNormalVec[0],-EmyNormalVec[1],-EmyNormalVec[2]);
  glColor3f(1,1,0);

  //3 rectangles needed to seal off triangle 1
  glTexCoord2f(0,0);glVertex3f(0,0,0);
  glTexCoord2f(1,0);glVertex3f(0,0,1);
  glTexCoord2f(1,1);glVertex3f(-2,-3,1);
  glTexCoord2f(0,1);glVertex3f(-2,-3,0);
  glEnd();


  //glColor3f(1,0,0);
  float FjacksP1[3] = {0,0,0};
  float FjacksP2[3] = {0,0,1};
  float FjacksP3[3] = {2,-3,1};
  float FmyNormalVec[3] = {0};
  jacksonNormal(FmyNormalVec,FjacksP1,FjacksP2,FjacksP3);
  glBegin(GL_QUADS);
  glNormal3f(FmyNormalVec[0],FmyNormalVec[1],FmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(0,0,0);
  glTexCoord2f(1,0);glVertex3f(0,0,1);
  glTexCoord2f(1,1);glVertex3f(2,-3,1);
  glTexCoord2f(0,1);glVertex3f(2,-3,0);
  glEnd();

  float GjacksP1[3] = {-2,-3,0};
  float GjacksP2[3] = {-2,-3,1};
  float GjacksP3[3] = {2,-3,1};
  float GmyNormalVec[3] = {0};
  jacksonNormal(GmyNormalVec,GjacksP1,GjacksP2,GjacksP3);
  glBegin(GL_QUADS);
  glNormal3f(-GmyNormalVec[0],-GmyNormalVec[1],-GmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(-2,-3,0);
  glTexCoord2f(1,0);glVertex3f(-2,-3,1);
  glTexCoord2f(1,1);glVertex3f(2,-3,1);
  glTexCoord2f(0,1);glVertex3f(2,-3,0);
  glEnd();

  //3 rectangles needed to seal off triangle 2
  float HjacksP1[3] = {0,-4,0};
  float HjacksP2[3] = {0,-4,1};
  float HjacksP3[3] = {-2,-1,1};
  float HmyNormalVec[3] = {0};
  jacksonNormal(HmyNormalVec,HjacksP1,HjacksP2,HjacksP3);
  glBegin(GL_QUADS);
  glNormal3f(HmyNormalVec[0],HmyNormalVec[1],HmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(0,-4,0);
  glTexCoord2f(1,0);glVertex3f(0,-4,1);
  glTexCoord2f(1,1);glVertex3f(-2,-1,1);
  glTexCoord2f(0,1);glVertex3f(-2,-1,0);
  glEnd();

  float IjacksP1[3] = {0,-4,0};
  float IjacksP2[3] = {0,-4,1};
  float IjacksP3[3] = {2,-1,1};
  float ImyNormalVec[3] = {0};
  jacksonNormal(ImyNormalVec,IjacksP1,IjacksP2,IjacksP3);
  glBegin(GL_QUADS);
  glNormal3f(-ImyNormalVec[0],-ImyNormalVec[1],-ImyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(0,-4,0);
  glTexCoord2f(1,0);glVertex3f(0,-4,1);
  glTexCoord2f(1,1);glVertex3f(2,-1,1);
  glTexCoord2f(0,1);glVertex3f(2,-1,0);
  glEnd();


  float JjacksP1[3] = {-2,-1,0};
  float JjacksP2[3] = {-2,-1,1};
  float JjacksP3[3] = {2,-1,1};
  float JmyNormalVec[3] = {0};
  jacksonNormal(JmyNormalVec,JjacksP1,JjacksP2,JjacksP3);
  glBegin(GL_QUADS);
  glNormal3f(JmyNormalVec[0],JmyNormalVec[1],JmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(-2,-1,0);
  glTexCoord2f(1,0);glVertex3f(-2,-1,1);
  glTexCoord2f(1,1);glVertex3f(2,-1,1);
  glTexCoord2f(0,1);glVertex3f(2,-1,0);
  glEnd();


  //ENDING MY TEXTURES FOR THIS OBJECT
  glDisable(GL_TEXTURE_2D);


  glPopMatrix();
}



//END OF MY DRAWINGS
/*
 *  Draw vertex in polar coordinates with normal
 */
static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glTexCoord2f(th/360.0,ph/180+0.5);
   glVertex3d(x,y,z);

}



static void jacksonBall2(double x,double y,double z,double xRotation, double yRotation, double zRotation, double xstretch, double ystretch, double zstretch, int latBegin, int latEnd, int currTex)
{
   int thA,phA;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(xRotation,1,0,0);
   glRotated(yRotation,0,1,0);
   glRotated(zRotation,0,0,1);
   glScaled(xstretch,ystretch,zstretch);

   //  White ball
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[currTex]);
   //  Bands of latitude
   for (phA=latBegin;phA<latEnd;phA+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (thA=0;thA<=360;thA+=2*inc)
      {
         Vertex(thA,phA);
         Vertex(thA,phA+inc);
      }
      glEnd();
   }
   glDisable(GL_TEXTURE_2D);
   //  Undo transofrmations
   glPopMatrix();
}


//This one allows you to adjust how see through the balls are
static void jacksonBall3(double x,double y,double z,double xRotation, double yRotation, double zRotation, double xstretch, double ystretch, double zstretch, int latBegin, int latEnd, int currTex, double currAlpha)
{
   int thA,phA;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(xRotation,1,0,0);
   glRotated(yRotation,0,1,0);
   glRotated(zRotation,0,0,1);
   glScaled(xstretch,ystretch,zstretch);

   //  White ball
   glEnable(GL_BLEND);
   glColor4f(1,1,1,currAlpha);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

   //glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[currTex]);
   //  Bands of latitude
   for (phA=latBegin;phA<latEnd;phA+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (thA=0;thA<=360;thA+=2*inc)
      {
         Vertex(thA,phA);
         Vertex(thA,phA+inc);
      }
      glEnd();
   }
   glDisable(GL_TEXTURE_2D);
   //  Undo transofrmations
   glDisable(GL_BLEND);
   glPopMatrix();
}


/*  RIP failed function
//this function expects you to input an array that is divisible by 3
static void drawTriangles(float *arrayPoints,int numTriangles, int currTex)
{
  glColor3f(1,1,1);
  float yellow[] = {1.0,1.0,0.0,1.0};
  float Emission[]  = {0.0,0.0,0.01*emission,1.0};
  glMaterialf(GL_FRONT,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
  glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

  float myNormalVec[3] = {1,2,3};
  float jacksP1[3] = {0,0,0};
  float jacksP2[3] = {2,2,2};
  float jacksP3[3] ={-3,-3,-3};
  for(int i=0; i<numTriangles;i++)
  {
    jacksP1[0] = arrayPoints[9*i+0];
    jacksP1[1] = arrayPoints[9*i+1];
    jacksP1[2] = arrayPoints[9*i+2];

    jacksP2[0] = arrayPoints[9*i+3];
    jacksP2[1] = arrayPoints[9*i+4];
    jacksP2[2] = arrayPoints[9*i+5];

    jacksP3[0] = arrayPoints[9*i+6];
    jacksP3[1] = arrayPoints[9*i+7];
    jacksP3[2] = arrayPoints[9*i+8];
    jacksonNormal(myNormalVec, jacksP1, jacksP2, jacksP3);

    glBegin(GL_TRIANGLES);
    for(int j=0;j<9;j++){
      printf("%f\n", arrayPoints[j]);
      printf("%u\n",i);
    }
    glVertex3f(arrayPoints[9*i], arrayPoints[9*i+1], arrayPoints[9*i+2]);
    glVertex3f(arrayPoints[9*i+3], arrayPoints[9*i+4], arrayPoints[9*i+5]);
    glVertex3f(arrayPoints[9*i+6], arrayPoints[9*i+7], arrayPoints[9*i+8]);
    glEnd();
    glDisable(GL_TEXTURE_2D);


    glPopMatrix();
    
    //glVertex3f(0,0,0);
    //glVertex3f(arrayPoints[3],arrayPoints[4],arrayPoints[5]);
    //glVertex3f(arrayPoints[6],8,arrayPoints[8]);
  
  }

  

  glBegin(GL_TRIANGLES);
  glVertex3f(0,0,0);
  glVertex3f(arrayPoints[3],arrayPoints[4],arrayPoints[5]);
  glVertex3f(arrayPoints[6],8,arrayPoints[8]);

  glVertex3f(0,0,0);
  glVertex3f(arrayPoints[5],arrayPoints[4],arrayPoints[5]);
  glVertex3f(7,arrayPoints[7],arrayPoints[8]);

  glVertex3f(0,0,0);
  glVertex3f(-1,-1,-1);
  glVertex3f(-5,arrayPoints[7],arrayPoints[8]);
  glEnd();


  float myNormalVec[3] = {0};
  float jacksP1[3] = {0};
  float jacksP2[3] = {0};
  float jacksP3[3] ={0};


  float yellow[] = {1.0,1.0,0.0,1.0};
  float Emission[]  = {0.0,0.0,0.01*emission,1.0};
  glColor3f(1,1,1);
  glMaterialf(GL_FRONT,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
  glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
  
  //glEnable(GL_TEXTURE_2D);
  //glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  //glBindTexture(GL_TEXTURE_2D,texture[currTex]);

  
  //glVertex3f(arrayPoints[8],1,1);
  //glVertex3f(0,0,0);
  //glVertex3f(2,2,2);
  for(int i = 0;i<currentSize;i++)
  {
    jacksP1[0] = arrayPoints[i+0];
    jacksP1[1] = arrayPoints[i+1];
    jacksP1[2] = arrayPoints[i+2];

    jacksP2[0] = arrayPoints[i+3];
    jacksP2[1] = arrayPoints[i+4];
    jacksP2[2] = arrayPoints[i+5];

    jacksP3[0] = arrayPoints[i+6];
    jacksP3[1] = arrayPoints[i+7];
    jacksP3[2] = arrayPoints[i+8];

    jacksonNormal(myNormalVec, jacksP1, jacksP2, jacksP3);
    glBegin(GL_TRIANGLES);
    glNormal3f(myNormalVec[0], myNormalVec[1], myNormalVec[2]);
    glVertex3f(jacksP1[0], jacksP2[1], jacksP3[2]);
    glVertex3f(jacksP2[0], jacksP2[1], jacksP3[2]);
    glVertex3f(jacksP3[0], jacksP2[1], jacksP3[2]);


    glVertex3f(arrayPoints[0],arrayPoints[1],arrayPoints[2]);
    glVertex3f(arrayPoints[3],arrayPoints[4],arrayPoints[5]);
    glVertex3f(arrayPoints[6],arrayPoints[7],arrayPoints[8]);

    glEnd();
    //printf("%f\n", arrayPoints[i]);
  }

  
}
*/


static void Penguin(double x,double y, double z, double dx, double dy, double dz, double xRotation, double yRotation, double zRotation, int wave)
{
  if (wave==1)
  {
        //BEGINNING GOOD STUFF
    glPushMatrix();
    glTranslated(x,y,z);
    glRotated(xRotation,1,0,0);
    glRotated(yRotation,0,1,0);
    glRotated(zRotation,0,0,1);
    glScaled(dx,dy,dz);

    //start body
    jacksonBall2(0,0,0, 0,0,0, 3,4,3, -90, 40, 2);
    jacksonBall2(0,0,0, 0,0,0, 3,4,3, 40, 90, 21);
    //head
    jacksonBall2(0,6.15,0, 0,0,0, 2,2.3,2, -90, 40, 2);
    jacksonBall2(0,6.15,0, 0,0,0, 2,2.3,2, 40, 90, 21);
    //neck
    jacksonCylinder2(0,6.8,0, 0,0,0, 1,1,1, 4,0.8, 360, 21);

    //eyes
    jacksonBall2(0.6,6.65,1.3, -100,0,15, 0.6,0.6,0.6, -90, 90, 5);
    jacksonBall2(-0.6,6.65,1.3, -100,0,-15, 0.6,0.6,0.6, -90, 90, 5);

    //wings
    jacksonBall2(3,0,0, -30,0,45, 1,3.5,0.4, -90,40, 2);
    jacksonBall2(3,0,0, -30,0,45, 1,3.5,0.4, 40,90, 21);

    jacksonBall2(-3,1.5,0, 0,0,-155, 1,3.5,0.4, -90,40, 2);
    jacksonBall2(-3,1.5,0, 0,0,-155, 1,3.5,0.4, 40,90, 21);

    //legs and feet
    jacksonCube(1,-4,0, 0,0,0, 0.5,1,0.5, 11,1);
    jacksonCube(-1,-4,0, 0,0,0, 0.5,1,0.5, 11,1);

    //feet
    jacksonCube(1,-5,0.7, 0,0,0, 0.7,0.4,1.3, 11,1);
    jacksonCube(-1,-5,0.7, 0,0,0, 0.7,0.4,1.3, 11,1);
    //toes
    jacksonCone(0.6,-5,1.5, 90,0,0, 1,1,1, 1,0.3, 360, 21);
    jacksonCone(1,-5,1.5, 90,0,0, 1,1,1, 1,0.3, 360, 21);
    jacksonCone(1.4,-5,1.5, 90,0,0, 1,1,1, 1,0.3, 360, 21);
    
    jacksonCone(-0.6,-5,1.5, 90,0,0, 1,1,1, 1,0.3, 360, 21);
    jacksonCone(-1,-5,1.5, 90,0,0, 1,1,1, 1,0.3, 360, 21);
    jacksonCone(-1.4,-5,1.5, 90,0,0, 1,1,1, 1,0.3, 360, 21);


    //tail
    jacksonBall2(0,-0.35,-2, 30,0,0, 1,3.5,0.4, -90,40, 2);
    jacksonBall2(0,-0.35,-2, 30,0,0, 1,3.5,0.4, 40,90, 21);


    //Lips
    jacksonBall2(0,5.8,1.3, 0,0,0, 0.5,0.2,1.5, -90,90, 22);
    jacksonBall2(0,5.4,1.3, 0,0,0, 0.5,0.3,1.1, -90,90, 22);

    //Cone(double x, double y, double z, double xRotation, double yRotation, double zRotation, double dx, double dy, double dz, double height, double radius, int roundnessVar, double currTexture)


    //(double x,double y,double z,double xRotation, double yRotation, double zRotation, double dx,double dy,double dz, int currTex)

    glPopMatrix();

  }
  else if (wave == 0)
  {
        //BEGINNING GOOD STUFF
    glPushMatrix();
    glTranslated(x,y,z);
    glRotated(xRotation,1,0,0);
    glRotated(yRotation,0,1,0);
    glRotated(zRotation,0,0,1);
    glScaled(dx,dy,dz);

    //start body
    jacksonBall2(0,0,0, 0,0,0, 3,4,3, -90, 40, 2);
    jacksonBall2(0,0,0, 0,0,0, 3,4,3, 40, 90, 21);
    //head
    jacksonBall2(0,6.15,0, 0,0,0, 2,2.3,2, -90, 40, 2);
    jacksonBall2(0,6.15,0, 0,0,0, 2,2.3,2, 40, 90, 21);
    //neck
    jacksonCylinder2(0,6.8,0, 0,0,0, 1,1,1, 4,0.8, 360, 2);

    //eyes
    jacksonBall2(0.6,6.65,1.3, -100,0,15, 0.6,0.6,0.6, -90, 90, 5);
    jacksonBall2(-0.6,6.65,1.3, -100,0,-15, 0.6,0.6,0.6, -90, 90, 5);

    //wings
                        //first controls spinning flippers horizontally, then third axis makes the flipper rotate up or down
    jacksonBall2(2.7,0.5,0, 30,0,30, 1,3.5,0.4, -90,40, 2);
    jacksonBall2(2.7,0.5,0, 30,0,30, 1,3.5,0.4, 40,90, 21);

    jacksonBall2(-2.7,0.5,0, 30,0,-30, 1,3.5,0.4, -90,40, 2);
    jacksonBall2(-2.7,0.5,0, 30,0,-30, 1,3.5,0.4, 40,90, 21);

     //legs and feet
    jacksonCube(1,-4,0, 0,0,0, 0.5,1,0.5, 11,1);
    jacksonCube(-1,-4,0, 0,0,0, 0.5,1,0.5, 11,1);

    //feet
    jacksonCube(1,-5,0.7, 0,0,0, 0.7,0.4,1.3, 11,1);
    jacksonCube(-1,-5,0.7, 0,0,0, 0.7,0.4,1.3, 11,1);
     //toes
    jacksonCone(0.6,-5,1.5, 90,0,0, 1,1,1, 1,0.3, 360, 21);
    jacksonCone(1,-5,1.5, 90,0,0, 1,1,1, 1,0.3, 360, 21);
    jacksonCone(1.4,-5,1.5, 90,0,0, 1,1,1, 1,0.3, 360, 21);
    
    jacksonCone(-0.6,-5,1.5, 90,0,0, 1,1,1, 1,0.3, 360, 21);
    jacksonCone(-1,-5,1.5, 90,0,0, 1,1,1, 1,0.3, 360, 21);
    jacksonCone(-1.4,-5,1.5, 90,0,0, 1,1,1, 1,0.3, 360, 21);

    //tail
    jacksonBall2(0,-0.35,-2, 30,0,0, 1,3.5,0.4, -90,40, 2);
    jacksonBall2(0,-0.35,-2, 30,0,0, 1,3.5,0.4, 40,90, 21);

    //beak
    jacksonBall2(0,5.8,1.3, 0,0,0, 0.5,0.2,1.5, -90,90, 22);
    jacksonBall2(0,5.4,1.3, 0,0,0, 0.5,0.3,1.1, -90,90, 22);

    glPopMatrix();
  }

}


static void Lamp2(double x, double y, double z, double dx, double dy, double dz, double xRotation, double yRotation, double zRotation)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(xRotation,1,0,0);
  glRotated(yRotation,0,1,0);
  glRotated(zRotation,0,0,1);
  glScaled(dx,dy,dz);

  for(int i=0;i<5;i++)
  {
    jacksonCylinder2(0,-i,0, 0,0,0, 1,1,1, 1,i, 360, 20);
  }
  //vertical body
  jacksonCylinder2(0,20,0, 0,0,0, 1,1,1, 22,1, 360,20);
  //horizontal body
  jacksonCylinder2(0,19.5,0.5, 90,0,0, 1,1,1, 6.5,1, 360,20);
  jacksonBall2(0,19.5,0, 0,0,0, 1.2,1.2,1.2, -90,90, 20);

  //light bulb and cover
  jacksonBall2(0,19.5,-6.5, 90,0,0, 1.4,2.4,1.4, -90,0, 19);
  jacksonBall2(0,19.5,-6.5, 90,0,0, 0.8,1.2,0.8, 0,90, 22);

  glPopMatrix();
}

static void Tree(double x, double y, double z, double dx, double dy, double dz, double xRotation, double yRotation, double zRotation)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(xRotation,1,0,0);
  glRotated(yRotation,0,1,0);
  glRotated(zRotation,0,0,1);
  glScaled(dx,dy,dz);

  jacksonCylinder2(0,4,0, 0,0,0, 1,1,1, 5,1, 360,1);
  for(int i=0;i<7;i++)
  {
    jacksonCone(0,i+3,0, 0,0,0, 1,1,1, 2,7-i, 360, 4);
  }
  jacksonsStar(0,11.5,-0.3, 0,0,0, 0.2*(1/dx),0.2*(1/dy),0.2*(1/dz), 22);

  glPopMatrix();
}

static void Igloo(double x, double y, double z, double dx, double dy, double dz, double xRotation, double yRotation, double zRotation)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(xRotation,1,0,0);
  glRotated(yRotation,0,1,0);
  glRotated(zRotation,0,0,1);
  glScaled(dx,dy,dz);

  jacksonBall2(0,0,0, 90,0,0, 5,5,5, -90,0, 6);

  //edges of entrance
  jacksonCube(4,1.25,-1.25, 0,0,0, 3,1.25,0.2, 6,1);
  jacksonCube(4,1.25,1.25, 0,0,0, 3,1.25,0.2, 6,1);

  //top
  jacksonCube(4,2.5,0, 0,0,0, 3,0.2,1.45, 6,1);

  //inside cube dark
  jacksonCube(4,1.27,0, 0,0,0, 2.1,1.3,1.2, 2,1);

  glPopMatrix();

}


static void jacksonLake(double backLeftX, double backLeftY, double backLeftZ, int currTexture)
{
  glDisable(GL_LIGHTING);       //disabling the lighting so that I can get the see through effect in order to get the reflection on my lake surface!
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture[currTexture]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0);
  glVertex3f(backLeftX,backLeftY,backLeftZ);

  glTexCoord2f(0,1);
  glVertex3f(backLeftX,backLeftY,backLeftZ+20);

  glTexCoord2f(1,1);
  glVertex3f(backLeftX+20,backLeftY,backLeftZ+20);

  glTexCoord2f(1,0);
  glVertex3f(backLeftX+20,backLeftY,backLeftZ+0);
  glEnd();

  glEnable(GL_LIGHTING);       //reneabling the lighting for the rest of the scene

  //other versions of my lake
  /*

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture[currTexture]);
  glBegin(GL_POLYGON);

  glTexCoord2f(0,0);
  glVertex3f(0,0,0);

  glTexCoord2f(0,1);
  glVertex3f(0,0,1);

  glTexCoord2f(0.1,1);
  glVertex3f(0.2,0,1);

  glTexCoord2f(0.9,0.25);
  glVertex3f(0.3,0,0.95);

  glVertex3f(0.35,0, 0.8);
  glVertex3f(0.4,0, 0.5);

  glVertex3f(0.45,0, 0.1);
  glVertex3f(0.45,0,0);

  glTexCoord2f(0,0);
  glVertex3f(0,0,0);

  

  glEnd();

  glPushMatrix();

  glScalef(-1.0, 1.0, 1.0);    //reflecting across 
  glBegin(GL_POLYGON);

  glTexCoord2f(0,0);
  glVertex3f(0,0,0);

  glTexCoord2f(0,1);
  glVertex3f(0,0,1);

  glTexCoord2f(0.1,1);
  glVertex3f(0.2,0,1);

  glTexCoord2f(0.9,0.25);
  glVertex3f(0.3,0,0.95);

  glVertex3f(0.35,0, 0.8);
  glVertex3f(0.4,0, 0.5);

  glVertex3f(0.45,0, 0.1);
  glVertex3f(0.45,0,0);

  glTexCoord2f(0,0);
  glVertex3f(0,0,0);


  glEnd();
  glPopMatrix();
  glEnable(GL_LIGHTING);       //reneabling the lighting for the rest of the scene
  glPopMatrix();
  */
}


//THIS IS MY HOUSE DRAWING          //texture 1 should be 8       and texture 2 should be 9
static void jacksonsHouse(double x, double y, double z, double xRotation, double yRotation, double zRotation, double dx, double dy, double dz, int texture1, int texture2, double repititions)
{
   //  Set specular color to white
  float white[] = {1,1,1,1};
  float black[] = {0,0,0,1};
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

  glPushMatrix();
  //Below I must scale, rotate, and then translate my house object
  glTranslated(x,y,z);
  glRotated(xRotation,1,0,0);
  glRotated(yRotation,0,1,0);
  glRotated(zRotation,0,0,1);
  glScaled(dx,dy,dz);

  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glBindTexture(GL_TEXTURE_2D,texture[texture1]);

  //front and back ends of the house
  //back
  float AjacksP1[3] = {0,0,0};
  float AjacksP2[3] = {1,0,0};
  float AjacksP3[3] = {1,0.8,0};
  float AmyNormalVec[3] = {0};
  jacksonNormal(AmyNormalVec,AjacksP1,AjacksP2,AjacksP3);


  glColor3f(1,1,1);
  glBegin(GL_POLYGON);
  glNormal3f(-AmyNormalVec[0],-AmyNormalVec[1],-AmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(0,0,0);
  glTexCoord2f(repititions,0);glVertex3f(1,0,0);
  glTexCoord2f(repititions,repititions);glVertex3f(1,0.8,0);
  glTexCoord2f(repititions*0.5,repititions*1.5);glVertex3f(0.5,1.2,0);
  glTexCoord2f(0,repititions);glVertex3f(0,0.8,0);
  glVertex3f(0,0,0);
  glEnd();



//front
  float BjacksP1[3] = {0,0,2};
  float BjacksP2[3] = {1,0,2};
  float BjacksP3[3] = {1,0.8,2};
  float BmyNormalVec[3] = {0};
  jacksonNormal(BmyNormalVec,BjacksP1,BjacksP2,BjacksP3);


  glColor3f(1,1,1);
  glBegin(GL_POLYGON);
  glNormal3f(BmyNormalVec[0],BmyNormalVec[1],BmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(0,0,2);
  glTexCoord2f(repititions,0);glVertex3f(1,0,2);
  glTexCoord2f(repititions,repititions);glVertex3f(1,0.8,2);
  glTexCoord2f(repititions*0.5,repititions*1.5);glVertex3f(0.5,1.2,2);
  glTexCoord2f(0,repititions);glVertex3f(0,0.8,2);
  glTexCoord2f(0,repititions);glVertex3f(0,0,2);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,texture[texture2]);

  //roof
  //glColor3f(1,0,0);
  float CjacksP1[3] = {0.5,1.2,0};
  float CjacksP2[3] = {1,0.8,0};
  float CjacksP3[3] = {1,0.8,2};
  float CmyNormalVec[3] = {0};
  jacksonNormal(CmyNormalVec,CjacksP1,CjacksP2,CjacksP3);
  glBegin(GL_QUADS);
  glNormal3f(-CmyNormalVec[0],-CmyNormalVec[1],-CmyNormalVec[2]);
  glColor3f(1,1,1);
  glTexCoord2f(0,0);glVertex3f(0.5,1.2,0);
  glTexCoord2f(0,repititions);glVertex3f(1,0.8,0);
  glTexCoord2f(repititions,repititions);glVertex3f(1,0.8,2);
  glTexCoord2f(repititions,0);glVertex3f(0.5,1.2,2);
  glEnd();

  float DjacksP1[3] = {0.5,1.2,0};
  float DjacksP2[3] = {0,0.8,0};
  float DjacksP3[3] = {0,0.8,2};
  float DmyNormalVec[3] = {0};
  jacksonNormal(DmyNormalVec,DjacksP1,DjacksP2,DjacksP3);
  glColor3f(1,1,1);
  glBegin(GL_POLYGON);
  glNormal3f(DmyNormalVec[0],DmyNormalVec[1],DmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(0.5,1.2,0);
  glTexCoord2f(0,repititions);glVertex3f(0,0.8,0);
  glTexCoord2f(repititions,repititions);glVertex3f(0,0.8,2);
  glTexCoord2f(repititions,0);glVertex3f(0.5,1.2,2);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,texture[8]);

  //sides
  float EjacksP1[3] = {0,0,0};
  float EjacksP2[3] = {0,0,2};
  float EjacksP3[3] = {0,0.8,2};
  float EmyNormalVec[3] = {0};
  jacksonNormal(EmyNormalVec,EjacksP1,EjacksP2,EjacksP3);
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glNormal3f(EmyNormalVec[0],EmyNormalVec[1],EmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(0,0,0);
  glTexCoord2f(repititions,0);glVertex3f(0,0,2);
  glTexCoord2f(repititions,repititions);glVertex3f(0,0.8,2);
  glTexCoord2f(0,repititions);glVertex3f(0,0.8,0);
  glEnd();

  float FjacksP1[3] = {1,0,0};
  float FjacksP2[3] = {1,0,2};
  float FjacksP3[3] = {1,0.8,2};
  float FmyNormalVec[3] = {0};
  jacksonNormal(FmyNormalVec,FjacksP1,FjacksP2,FjacksP3);
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glNormal3f(-FmyNormalVec[0],-FmyNormalVec[1],-FmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(1,0,0);
  glTexCoord2f(repititions,0);glVertex3f(1,0,2);
  glTexCoord2f(repititions,repititions);glVertex3f(1,0.8,2);
  glTexCoord2f(0,repititions);glVertex3f(1,0.8,0);
  glEnd();

  //bottom
  float GjacksP1[3] = {0,0,0};
  float GjacksP2[3] = {1,0,0};
  float GjacksP3[3] = {1,0,2};
  float GmyNormalVec[3] = {0};
  jacksonNormal(GmyNormalVec,GjacksP1,GjacksP2,GjacksP3);
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glNormal3f(GmyNormalVec[0],GmyNormalVec[1],GmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(0,0,0);
  glTexCoord2f(0,repititions);glVertex3f(1,0,0);
  glTexCoord2f(repititions,repititions);glVertex3f(1,0,2);
  glTexCoord2f(repititions,0);glVertex3f(0,0,2);
  glEnd();


  //Side bushes
  jacksonAutoTextureCube(-0.15,0.1,0.9, 0,0,0, 0.15,0.12,1.1, 34,3);
  jacksonAutoTextureCube(1.15,0.1,0.9, 0,0,0, 0.15,0.12,1.1, 34,3);
  //back bush
  jacksonAutoTextureCube(0.5,0.1,-0.112, 0,0,0, 0.5,0.12,0.1, 34, 3);
  //front bushes
  jacksonBall2(-0.1,0,2.2, 0,0,0, 0.17,0.3,0.17, -90, 90, 34);
  jacksonBall2(1.1,0,2.2, 0,0,0, 0.17,0.3,0.17, -90, 90, 34);
  //front steps
  jacksonAutoTextureCube(0.5,0.03,2.2, 0,0,0, 0.3,0.03,0.3, 27, 1);
  jacksonAutoTextureCube(0.5,0.08,2.05, 0,0,0, 0.3,0.03,0.3, 27, 1);
  //Front door
  jacksonCube(0.5,0.33,1.72, 0,0,0, 0.17,0.25,0.3, 29, 1);
  //clock above door
  jacksonCylinder2(0.5,0.9,2.02, 90,0,0, 0.1,0.1,0.1, 1, 1, 360, 30);

  //chimney
  jacksonCube(0.2,0.9,0.6, 0,0,0, 0.1,0.3,0.1, 27, 1);
  jacksonCube(0.2,1.22,0.6, 0,0,0, 0.12,0.03,0.12, 27, 1);

  //smoke out of chimney
  jacksonBall3(0.2,1.4,0.6, 0,0,0, 0.1,0.13,0.1, -90, 90, 32,0.9);
  jacksonBall3(0.24,1.7,0.6, 0,35,0, 0.09,0.098,0.09, -90, 90, 32,0.7);
  jacksonBall3(0.28,2,0.6, 0,70,0, 0.08,0.085,0.08, -90, 90, 32,0.5);
  jacksonBall3(0.32,2.2,0.6, 0,105,0, 0.07,0.071,0.07, -90, 90, 32,0.3);



  //double x,double y,double z,double xRotation, double yRotation, double zRotation, double dx,double dy,double dz, int currTex, double repititions)
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}



//BELOW I GENERATE SNOW FOR THE SCENE 
struct snowflake
{
	double inAir;    
	double x;
	double y;
	double z;
};
//defining an array of all of my snowflakes
struct snowflake myArr[2000];


double generateRandomNumberInRange(double upperBound)
{
	double currNum = (rand()%(100-1+1)+1);
	//printf("%f", currNum);
	double randNum = currNum/100;
	randNum = randNum*upperBound;
	//printf("%s", "bastards");
	//printf("%f", randNum);
	//printf("%s", "wankers");
	return randNum;
}

void createSnowflake(int i)      //create snowflake object at the ith index of the struct
{
	double currValue=generateRandomNumberInRange(80);         //creating particle at random location within the dimensions of the scene at the time
	double currValue2=generateRandomNumberInRange(30);
	double currValue3=generateRandomNumberInRange(80);
	myArr[i].inAir = 1;
	myArr[i].x = currValue-40;
	myArr[i].y = currValue2;
	myArr[i].z = currValue3-40;
}

//END OF MY OBJECTS, FUNCTIONS, AND STRUCTS NEEDED TO CREATE THE SCENE!


/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   const double len=2.0;  //  Length of axes
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (mode)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }

   //  Flat or smooth shading
   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   //  Light switch
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light position
      Position[0] = distance*Cos(zh);
      Position[1] = distance*Sin(zh);
      Position[2] = ylight;
      Position[3] =1;
      //float Position[]  = {distance*Cos(zh),distance*Sin(zh),ylight,1.0};   //HERE I SWITCHED THE AXES THAT THE LIGHT IS ROTATING AROUND
      if(orbit)
      {
         Position[1] = ylight;
         Position[2] = distance*Sin(zh);
      }
      

      //
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      //jacksonBall(Position[0],Position[1],Position[2] , 0.1, 0.1, 0.1, -90, 90, 7);    //drawing a white ball at the location of the light
      if(obj==0)
      {
      	if (Position[1]>0.5)
      	{
      		jacksonsStar(Position[0],Position[1],Position[2], 0,0,0, 0.7,0.7,0.7, 7);
      	}

      }
      else
      {
      	jacksonsStar(Position[0],Position[1],Position[2], 0,0,0, 0.7,0.7,0.7, 7);
      }

      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  Location of viewer for specular calculations
      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);    //setting position of the light
   }
   else
      glDisable(GL_LIGHTING);

   //  Draw individual objects
   if (obj==1)
   {
            
      glPushMatrix();
      glScalef(1.0, -1.0, 1.0);                       //here I scale all the proceding elements in the matrix to be scaled so they are upside down (under the y plane)
      glLightfv(GL_LIGHT0, GL_POSITION, Position);    //here I need to update the location of the light so that all my normals work correctly 


      Penguin(10,2,0, 0.2,0.2,0.2, 90,180,180, 1);
      Penguin(0,1,0, 0.2,0.2,0.2, 0,0,0, 1);

      glPopMatrix();

      glPushMatrix();
      glLightfv(GL_LIGHT0, GL_POSITION, Position);    //replacing the lighting location now that the rest of the scene needs to not be flipped
      //glDisable(GL_STENCIL_TEST);

      glEnable(GL_BLEND);                                //I need to add blending so that I can get my ice blended with the reflection of the penguin below
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    //this was the best blending function from what I looked up
      glColor4f(1.0,1.0,1.0,0.3);    //30 percent of white floor
      //jacksonLake(-2,0,0, 2,0,0, 0,0,0,8,9);

      glDisable(GL_BLEND);


      Penguin(10,2,0, 0.2,0.2,0.2, 90,180,180, 1);
      Penguin(0,1.1,0, 0.2,0.2,0.2, 0,0,0, 1);
      glPopMatrix();

      //jacksonBall2(0,0,0, 90,0,0, 5,5,5, -90,0, 6);
      //Penguin(10,2,0, 0.2,0.2,0.2, 0,180,0, 1);




        /* Now, only render where stencil is set to 1. */
      //glStencilFunc(GL_EQUAL, 1, 0xffffffff);  /* draw if ==1 */
      //glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);


      //##################DONE WITH NEW STUFF

      /*
      jacksonBackgroundMountains(8*dim);
      for(int i=0;i<3;i++)
      {
        jacksonsHouse(i*10,1,5, 0,0,0, i*1+1,4,2, 8,9, 1);
      }

      jacksonsStar(0,20*Cos(zh),20*Sin(zh), 0,90,0, 0.7,0.7,0.7, 7);
      Lamp2(5,2,0, 0.2,0.2,0.2, 0,0,0);
      Lamp2(15,2,-10, 0.2,0.2,0.2, 0,180,0);

      Penguin(10,2,0, 0.2,0.2,0.2, 0,180,0, 1);
      Penguin(10,2,-10, 0.2,0.2,0.2, 0,0,0, 0);

      Tree(0,2,-10, 0.4,0.8,0.4, 0,0,0);
      Tree(-5,2,10, 0.5,0.5,0.5, 0,0,0);

      //Igloo(25,2,-15, 0.7, 0.7, 0.7, 0,-90,0);
      Igloo(-10,2,10, 0.7, 0.7, 0.7, 0,90,0);
      */


      //Current texture should be 7
      //static void jacksonsStar(double x, double y, double z, double xRotation, double yRotation, double zRotation, double dx, double dy, double dz,int currTexture)
      

   }
   else if (obj==2)
   {

      //This is where I keep objects currently in the works

      //Penguin(0,0,0, 1,1,1, 0,0,0, 1);
      //Penguin(0,0,0, 1,1,1, 0,0,0, 0);
      //Tree(0,0,0, 1,1,1, 0,0,0);
      //Lamp(0,0,0, 1,1,1, 0,0,0);
      //Tree();
      //Igloo(0,0,0, 0.2, 0.2, 0.2, 0,0,0);
      //Lamp2(0,0,0, 1,1,1, 0,0,0);
      jacksonsHouse(0,0,0, 0,0,0, 1,1,1, 8,9, 1);


      //jacksonCone(double x, double y, double z, double xRotation, double yRotation, double zRotation, double dx, double dy, double dz, double height, double radius, int roundnessVar, double currTexture)

   }
     
   else if (obj==3)
   {
      //THIS IS WHERE I KEEP OLDER OBJECTS TO LOOK AT
      //Lamp(0,0,0, 0.2,0.2,0.2, 5,5,5);
      //jacksonCone(2,0,0, 0,0,0, 1,1,1, 1,1, 360, 7);
      //Lamp(0,0,0, 1,1,1, 0,0,0);
      //Igloo(0,0,0, 0.2, 0.2, 0.2, 0,0,0);


      jacksonsStar(0,0,0, 0,0,0, 0.7,0.7,0.7, 7);
      //jacksonsStar(0,0,0, 45,0,0, 0.7,0.7,0.7, 7);
      //jacksonsStar(0,0,0, 90,0,0, 0.7,0.7,0.7, 7);
      //jacksonsStar(0,0,0, 135,0,0, 0.7,0.7,0.7, 7);
      //jacksonsStar(0,0,0, 180,0,0, 0.7,0.7,0.7, 7);
      //jacksonsStar(0,0,0, 225,0,0, 0.7,0.7,0.7, 7);
      //jacksonsStar(0,0,0, 270,0,0, 0.7,0.7,0.7, 7);
      //jacksonsStar(0,0,0, 315,0,0, 0.7,0.7,0.7, 7);
      //jacksonsStar(0,0,0, 360,0,0, 0.7,0.7,0.7, 7);
 

      //jacksonCube(0,0,0 , 1,1,1 , 0,12);
      //jacksonCubeStack(3);
      //ball(0,2,0,1);
   }
   else      //MAIN SCENE
   {
   	  if(snowStorm==1)
   	  {
   	  	glEnable(GL_FOG);
   	  	glFogfv(GL_FOG_COLOR, myFogColor);
   	  	glFogi(GL_FOG_MODE, GL_LINEAR);
   	  	glFogf(GL_FOG_START, 10.f);
   	  	glFogf(GL_FOG_END, 50.f);
   	  }
   	  else
   	  {
   	  	glDisable(GL_FOG);
   	  }

      //Building the street
      for(int i=0;i<8;i++)
      {
          jacksonCube(0,0,-30+10*i, 0,0,0, 5,0.5,5, 23,1);
      }
      //Building the sidewalks
      for(int i=0;i<22;i++)
      {
          jacksonCube(7,0.4,-38+4*i, 0,0,0, 2,0.5,2, 24,1);
          jacksonCube(-7,0.4,-38+4*i, 0,0,0, 2,0.5,2, 24,1);
      }
      for(int i=0;i<8;i++)
      {
          jacksonCube(14,0.5,-30+10*i, 0,0,0, 5,0.5,5, 12, 2);
          //jacksonCube(-14,0.5,-30+10*i, 0,0,0, 5,0.5,5, 12, 2);     //taking these out to make room for the frozen lake
          jacksonCube(24,0.5,-30+10*i, 0,0,0, 5,0.5,5, 12, 2);
          //jacksonCube(-24,0.5,-30+10*i, 0,0,0, 5,0.5,5, 12, 2);
          jacksonCube(34,0.5,-30+10*i, 0,0,0, 5,0.5,5, 12, 2);
          jacksonCube(-34,0.5,-30+10*i, 0,0,0, 5,0.5,5, 12, 2);
      }
      jacksonCube(-14,0.5,-30, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-14,0.5,-30+10, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-14,0.5,-30+40, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-14,0.5,-30+50, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-14,0.5,-30+60, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-14,0.5,-30+70, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-11.5,0.5,-30+25, 0,0,0, 2.5,0.5,10, 12, 2);    //this is the cube separating from the sidewalk

      
      jacksonCube(-24,0.5,-30, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-24,0.5,-30+10, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-24,0.5,-30+40, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-24,0.5,-30+50, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-24,0.5,-30+60, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-24,0.5,-30+70, 0,0,0, 5,0.5,5, 12, 2);



      //putting in my skybox of background mountains
      jacksonBackgroundMountains(3*dim);
     

      //putting in frozen lake
      glPushMatrix();
      glScalef(1.0, -1.0, 1.0);                       //here I scale all the proceding elements in the matrix to be scaled so they are upside down (under the y plane)
      glLightfv(GL_LIGHT0, GL_POSITION, Position);    //here I need to update the location of the light so that all my normals work correctly 


      Penguin(-20,1.07,-10, 0.2,0.2,0.2, 0,0,0, 0);
      Penguin(-20,1.07,-4, 0.2,0.2,0.2, 0,180,0, 1);
      if (Position[1]>1)
      {
        jacksonsStar(Position[0],Position[1],Position[2], 0,0,0, 0.7,0.7,0.7, 7);
      }
      jacksonsHouse(-16.5,1,10, 0,90,0, 3,4,3, 8,9, 1);
      jacksonsHouse(21.7,1,-2, 0,270,0, 5,5,5, 8,9, 1);
      Tree(-13,1.1,15, 0.4,0.8,0.4, 0,0,0);
      Tree(13,1.1,10, 0.5,0.5,0.5, 0,0,0);
      Igloo(16,1,-10, 0.7, 0.7, 0.7, 0,180,0);
      Igloo(16,1,25, 0.7,0.7,0.7, 0,180, 0);
      Igloo(-16,1,30,0.7,0.7,0.7, 0,0,0);
      for(int i=0;i<2;i++)
      {
        Lamp2(-6,2,-10+20*i, 0.2,0.2,0.2, 0,-90,0);
        Lamp2(6,2,20*i, 0.2,0.2,0.2, 0,90,0);
        if (i==1)
        {
          Lamp2(-6,2,10+20*i, 0.2,0.2,0.2, 0,-90,0);
        }
      }
      jacksonCube(-14,0.5,-30, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-14,0.5,-30+10, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-14,0.5,-30+40, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-14,0.5,-30+50, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-14,0.5,-30+60, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-14,0.5,-30+70, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-11.5,0.5,-30+25, 0,0,0, 2.5,0.5,10, 12, 2);    //this is the cube separating from the sidewalk

      
      jacksonCube(-24,0.5,-30, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-24,0.5,-30+10, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-24,0.5,-30+40, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-24,0.5,-30+50, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-24,0.5,-30+60, 0,0,0, 5,0.5,5, 12, 2);
      jacksonCube(-24,0.5,-30+70, 0,0,0, 5,0.5,5, 12, 2);

      //putting in penguins
      //first standing penguins
      Penguin(6,2,-15, 0.2,0.2,0.2, 0,-90,0, 1);
      Penguin(-6,2,-15, 0.2,0.2,0.2, 0,90,0, 1);
      Penguin(-8,2,-5, 0.2,0.2,0.2, 0,180,0, 0);
      //next sliding penguins
      Penguin(2.5,1.1,-9, 0.2,0.2,0.2, 990,180,0, 0);
      Penguin(-2.5,1.1,5, 0.2,0.2,0.2, -90,180,180, 0);
      Penguin(-2.5,1.1,-18, 0.2,0.2,0.2, -90,180,180, 0);

      glPopMatrix();

      glPushMatrix();
      glLightfv(GL_LIGHT0, GL_POSITION, Position);    //replacing the lighting location now that the rest of the scene needs to not be flipped
      //glDisable(GL_STENCIL_TEST);

      glEnable(GL_BLEND);                                //I need to add blending so that I can get my ice blended with the reflection of the penguin below
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    //this was the best blending function from what I looked up
      glColor4f(1.0,1.0,1.0,0.3);    //30 percent of white floor
      jacksonLake(-29,0,-15,25);
      
      //-24,0.5,-30+20

      glDisable(GL_BLEND);


      Penguin(-20,1.07,-10, 0.2,0.2,0.2, 0,0,0, 0);
      Penguin(-20,1.07,-4, 0.2,0.2,0.2, 0,180,0, 1);
      jacksonsHouse(-16.5,1,10, 0,90,0, 3,4,3, 8,9, 1);
      jacksonsHouse(21.6,1,-2, 0,270,0, 5,5,5, 8,9, 1);
      Tree(-13,1.1,15, 0.4,0.8,0.4, 0,0,0);
      Tree(13,1.1,10, 0.5,0.5,0.5, 0,0,0);
      Igloo(16,1,-10, 0.7, 0.7, 0.7, 0,180,0);
      Igloo(16,1,25, 0.7,0.7,0.7, 0,180, 0);
      Igloo(-16,1,30,0.7,0.7,0.7, 0,0,0);
      for(int i=0;i<2;i++)
      {
        Lamp2(-6,2,-10+20*i, 0.2,0.2,0.2, 0,-90,0);
        Lamp2(6,2,20*i, 0.2,0.2,0.2, 0,90,0);
        if (i==1)
        {
          Lamp2(-6,2,10+20*i, 0.2,0.2,0.2, 0,-90,0);
        }
      }

      //putting in penguins
      //first standing penguins
      Penguin(6,2,-15, 0.2,0.2,0.2, 0,-90,0, 1);
      Penguin(-6,2,-15, 0.2,0.2,0.2, 0,90,0, 1);
      Penguin(-8,2,-5, 0.2,0.2,0.2, 0,180,0, 0);
      //next sliding penguins
      Penguin(2.5,1.1,-9, 0.2,0.2,0.2, 990,180,0, 0);
      Penguin(-2.5,1.1,5, 0.2,0.2,0.2, -90,180,180, 0);
      Penguin(-2.5,1.1,-18, 0.2,0.2,0.2, -90,180,180, 0);
      glPopMatrix();


      //NOW CREATING THE SNOW PARTICLES!!
      if(notCreated == 1)         //creating the snowflakes on the first pass through
      {
      	for(int i=0;i<2000;i++)
	  	{
			createSnowflake(i);
	  	}
	  	notCreated=0;
      }

      else                     //otherwise I have to go through and check for each flake if it is above the ground and if not then I recreate a snowflake there
      {
      	for(int i=0;i<2000;i++)
	  	{
			if(myArr[i].y>-1)             //if the current snowflake is above the ground then decrease its height by 0.1
			{
				myArr[i].y=myArr[i].y-0.05;
			}
			else
			{
				createSnowflake(i);        //create a snowflake if the current snowflake is below the ground
			}
	  	}

      }

      //Now I actually draw each of the snowflakes
      for(int i=0;i<2000;i++)
      {
      	double newX = myArr[i].x;
      	double newY = myArr[i].y;
      	double newZ = myArr[i].z;
      	glColor3f(1,1,1);
      	glPushMatrix();
      	glTranslated(newX,newY,newZ);
      	glutSolidSphere(0.08, 16, 16);
      	glPopMatrix();
      }


   }

   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }

   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s Light=%s",
     th,ph,dim,fov,mode?"Perpective":"Orthogonal",light?"On":"Off");
   if (light)
   {
      glWindowPos2i(5,45);
      Print("Model=%s LocalViewer=%s Distance=%d Elevation=%.1f",smooth?"Smooth":"Flat",local?"On":"Off",distance,ylight);
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }

   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
   {
    if(ph>5)
    {
      ph -= 5;
    }
   }
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
   	{
   		if(dim<20)
   		{
      		dim += 0.5;
   		}
   	}
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.5;
   //  Smooth color model
   else if (key == GLUT_KEY_F1)
      smooth = 1-smooth;
   //  Local Viewer
   else if (key == GLUT_KEY_F2)
      local = 1-local;
   else if (key == GLUT_KEY_F3)
      distance = (distance==1) ? 5 : 1;
   //  Toggle ball increment
   else if (key == GLUT_KEY_F8)
      inc = (inc==10)?3:10;
   //  Flip sign
   else if (key == GLUT_KEY_F9)
      one = -one;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(mode?fov:0,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Switch projection mode
   else if (ch == 'p' || ch == 'P')
      mode = 1-mode;
   //  Toggle light movement
   else if (ch == 'm' || ch == 'M')
      move = 1-move;
   //  Move light
   else if (ch == '<')
      zh += 1;
   else if (ch == '>')
      zh -= 1;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   //  Ambient level
   else if (ch=='a' && ambient>0)
      ambient -= 5;
   else if (ch=='A' && ambient<100)
      ambient += 5;
   //  Diffuse level
   else if (ch=='d' && diffuse>0)
      diffuse -= 5;
   else if (ch=='D' && diffuse<100)
      diffuse += 5;
   //  Specular level
   else if (ch=='f' && specular>0)
      specular -= 5;
   else if (ch=='F' && specular<100)
      specular += 5;
   //  Emission level
   else if (ch=='e' && emission>0)
      emission -= 5;
   else if (ch=='E' && emission<100)
      emission += 5;
   //  Shininess level
   else if (ch=='n' && shininess>-1)
      shininess -= 1;
   else if (ch=='N' && shininess<7)
      shininess += 1;
   //  Switch scene/object
   else if (ch == 'o' || ch=='O')
   {
      //printf("%d",obj);
      obj = (obj+1)%4;
      //printf("%d",obj);
      if (obj==1)
         dim=16;
      else if (obj==2)
         dim=16;
      else if (obj==3)
         dim=16;
      else
         dim=16;
   }

   //MY CONTROLS
   else if (ch=='s' || ch=='S')				//turn on and off the fog snowstorm
   {
   	snowStorm=1-snowStorm;
   }
   else if (ch == 'c' || ch=='C')
      orbit = 1-orbit;
   //  Light elevation
   else if (ch=='u')
      ylight -= 0.5;
   else if (ch=='U')
      ylight += 0.5;

   else if (ch=='R')
      rep+=1;

   else if (ch=='r')
      if (rep>1)
        rep-=1;
   //END MY CONTROLS


   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(mode?fov:0,asp,dim);
   //  Animate if requested
   glutIdleFunc(move?idle:NULL);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(mode?fov:0,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   printf("hello");
   float jacksP1[3] = {-1,-1,1};
   float jacksP2[3] = {1,-1,1};
   float jacksP3[3] = {1,1,1};
   float myNormalVec[3] = {0};
   jacksonNormal(myNormalVec,jacksP1,jacksP2,jacksP3);

   printf("%.6f %.2f %.3f", myNormalVec[0],myNormalVec[1],myNormalVec[2]);
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(400,400);
   glutCreateWindow("Jackson_Curry_HW5");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //LOADING MY TEXTURES
   texture[0] = LoadTexBMP("bark.bmp");
   texture[1] = LoadTexBMP("bark2.bmp");
   texture[2] = LoadTexBMP("blackFur.bmp");
   texture[3] = LoadTexBMP("evergreen.bmp");
   texture[4] = LoadTexBMP("evergreen2.bmp");
   texture[5] = LoadTexBMP("eyeball2.bmp");
   texture[6] = LoadTexBMP("igloo.bmp");
   texture[7] = LoadTexBMP("secondTrySun.bmp");
   texture[8] = LoadTexBMP("brickwall.bmp");
   texture[9] = LoadTexBMP("roofing.bmp");
   texture[10] = LoadTexBMP("finalSnowImage.bmp");
   texture[11] = LoadTexBMP("penguinFoot.bmp");
   texture[12] = LoadTexBMP("tuesdaySnow.bmp");

   //skybox textures do not touch!!
   texture[13] = LoadTexBMP("skybox2.bmp");
   texture[14] = LoadTexBMP("skybox2B.bmp");
   texture[15] = LoadTexBMP("skybox2D.bmp");
   texture[16] = LoadTexBMP("skybox2L.bmp");
   texture[17] = LoadTexBMP("skybox2R.bmp");
   texture[18] = LoadTexBMP("skybox2U.bmp");
   //end skybox
   texture[19] = LoadTexBMP("red-rust.bmp");
   texture[20] = LoadTexBMP("rust.bmp");
   texture[21] = LoadTexBMP("whiteFur.bmp");
   texture[22] = LoadTexBMP("yellowGlitter.bmp");
   texture[23] = LoadTexBMP("road.bmp");
   texture[24] = LoadTexBMP("sidewalk.bmp");
   texture[25] = LoadTexBMP("blueIce.bmp");

   texture[26] = LoadTexBMP("bush.bmp");
   texture[27] = LoadTexBMP("cement.bmp");
   texture[28] = LoadTexBMP("mySmoke.bmp");
   texture[29] = LoadTexBMP("myDoorway.bmp");
   texture[30] = LoadTexBMP("myClock.bmp");

   texture[31] = LoadTexBMP("hedge.bmp");
   texture[32] = LoadTexBMP("smoke2.bmp");
   texture[33] = LoadTexBMP("smoke3.bmp");
   texture[34] = LoadTexBMP("roseBush.bmp");

   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}

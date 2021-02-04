/*
 *  Lighting and Textures Jackson Curry
 *
 *  Demonstrates basic lighting using a cube, sphere and icosahedron.
 *
 *  Key bindings:
 

 *  c          Change orbits of the light
 *  u          Change elevation of the light
 *  U          Change elevation of the light the opposite way
 *  o/O        Change the object/scene you are viewing
 *  arrow keys Manipulate angle at which the scene is being viewed
 *  PgDn/PgUp  Zoom in and out



 *  l          Toggles lighting
 *  a/A        Decrease/increase ambient light
 *  d/D        Decrease/increase diffuse light
 *  s/S        Decrease/increase specular light
 *  e/E        Decrease/increase emitted light
 *  n/N        Decrease/increase shininess
 *  F1         Toggle smooth/flat shading
 *  F2         Toggle local viewer mode
 *  F3         Toggle light distance (1/5)
 *  F8         Change ball increment
 *  F9         Invert bottom normal
 *  m          Toggles light movement
 *  []         Lower/rise light
 *  p          Toggles ortogonal/perspective projection
 *  o          Cycles through objects
 *  +/-        Change field of view of perspective
 *  x          Toggle axes
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"
//MY VARIABLES
int orbit=0;
//END MY VARIABLES
int axes=1;       //  Display axes
int mode=1;       //  Projection mode
int move=1;       //  Move light
int th=-40;         //  Azimuth of view angle
int ph=15;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int obj=0;        //  Scene/opbject selection
double asp=1;     //  Aspect ratio
double dim=14;     //  Size of world
// Light values
int light     =   1;  // Lighting
int one       =   1;  // Unit value
int distance  =   8;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  10;  // Ambient intensity (%)
int diffuse   =  50;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   2;  // Elevation of light
typedef struct {float x,y,z;} vtx;
typedef struct {int A,B,C;} tri;
#define n 500
vtx is[n];


unsigned int texture[10];
int rep = 1;




//This is a function that will return the cross product of 2 vectors that are passed to it
/*
float *jacksonCross(float*vec1, float*vec2)
{
      float myAnswer[] = {vec1[1]*vec2[2]-vec1[2]*vec2[1],-(vec1[0]*vec2[2]-vec1[2]*vec2[0]),vec1[0]*vec2[1]-vec1[1]*vec2[0]};
      return myAnswer;
}
*/

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

//float jacksP1[3] = {0.0,1.0,0.0};
//float jacksP2[3] = {0.0,0.0,0.0};
//float jacksP3[3] = {1.0,0.0,0.0};
//float *myNormalVec = jacksonNormal(jacksP1,jacksP2,jacksP3);

//THIS IS MY VERSION OF A CUBE USED TO TEST MY NORMAL VECTOR FINDING FUNCTION!!
static void jacksonsCube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Cube

   //PUTTING IN MY TEXTURES
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[7]);



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
   glTexCoord2f(1,0);glVertex3f(+1,-1, 1);
   glTexCoord2f(1,1);glVertex3f(+1,+1, 1);
   glTexCoord2f(0,1);glVertex3f(-1,+1, 1);
   glEnd();

   //glDisable(GL_TEXTURE_2D);

   float newjacksP1[3] = {1,-1,-1};
   float newjacksP2[3] = {-1,-1,-1};
   float newjacksP3[3] = {-1,1,-1};
   float newNormalVec[3] = {0};
   jacksonNormal(newNormalVec,newjacksP1,newjacksP2,newjacksP3);

   glBindTexture(GL_TEXTURE_2D,texture[2]);

   glBegin(GL_QUADS);
   //  Back
   glColor3f(1,1,1);
   glNormal3f(newNormalVec[0],newNormalVec[1],newNormalVec[2]);
   glTexCoord2f(0,0);glVertex3f(+1,-1,-1);
   glTexCoord2f(1,0);glVertex3f(-1,-1,-1);
   glTexCoord2f(1,1);glVertex3f(-1,+1,-1);
   glTexCoord2f(0,1);glVertex3f(+1,+1,-1);
   glEnd();

   glDisable(GL_TEXTURE_2D);

   glBegin(GL_QUADS);
   //  Right
   glColor3f(1,1,0);
   glNormal3f(+4, 0, 0);
   glVertex3f(+1,-1,+1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,+1,-1);
   glVertex3f(+1,+1,+1);
   glEnd();
   //  Left
   glBegin(GL_QUADS);
   glColor3f(0,1,0);
   glNormal3f(-1, 0, 0);
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,-1,+1);
   glVertex3f(-1,+1,+1);
   glVertex3f(-1,+1,-1);
   glEnd();
   //  Top
   glBegin(GL_QUADS);
   glColor3f(0,1,1);
   glNormal3f( 0,+1, 0);
   glVertex3f(-1,+1,+1);
   glVertex3f(+1,+1,+1);
   glVertex3f(+1,+1,-1);
   glVertex3f(-1,+1,-1);
   glEnd();
   //  Bottom
   glBegin(GL_QUADS);
   glColor3f(1,0,1);
   glNormal3f( 0,-one, 0);
   glVertex3f(-1,-1,-1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,-1,+1);
   glVertex3f(-1,-1,+1);
   //  End
   glEnd();
   //  Undo transofrmations
   glPopMatrix();
}



//BEGINNING OF MY OBJECT DRAWINGS
static void jacksonsHouse(double x, double y, double z,
                          double dx, double dy, double dz,
                          double th)
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
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glBindTexture(GL_TEXTURE_2D,texture[8]);

  //front and back ends of the house
  //back
  float AjacksP1[3] = {x,y,z};
  float AjacksP2[3] = {x+1,y,z};
  float AjacksP3[3] = {x+1,y+0.8,z};
  float AmyNormalVec[3] = {0};
  jacksonNormal(AmyNormalVec,AjacksP1,AjacksP2,AjacksP3);


  glColor3f(1,1,1);
  glBegin(GL_POLYGON);
  glNormal3f(-AmyNormalVec[0],-AmyNormalVec[1],-AmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(x,y,z);
  glTexCoord2f(rep,0);glVertex3f(x+1,y,z);
  glTexCoord2f(rep,rep);glVertex3f(x+1,y+0.8,z);
  glTexCoord2f(rep*0.5,rep*1.5);glVertex3f(x+0.5,y+1.2,z);
  glTexCoord2f(0,rep);glVertex3f(x,y+0.8,z);
  glVertex3f(x,y,z);
  glEnd();



//front
  float BjacksP1[3] = {x,y,z+2};
  float BjacksP2[3] = {x+1,y,z+2};
  float BjacksP3[3] = {x+1,y+0.8,z+2};
  float BmyNormalVec[3] = {0};
  jacksonNormal(BmyNormalVec,BjacksP1,BjacksP2,BjacksP3);


  glColor3f(1,1,1);
  glBegin(GL_POLYGON);
  glNormal3f(BmyNormalVec[0],BmyNormalVec[1],BmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(x,y,z+2);
  glTexCoord2f(rep,0);glVertex3f(x+1,y,z+2);
  glTexCoord2f(rep,rep);glVertex3f(x+1,y+0.8,z+2);
  glTexCoord2f(rep*0.5,rep*1.5);glVertex3f(x+0.5,y+1.2,z+2);
  glTexCoord2f(0,rep);glVertex3f(x,y+0.8,z+2);
  glTexCoord2f(0,rep);glVertex3f(x,y,z+2);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,texture[9]);

  //roof
  //glColor3f(1,0,0);
  float CjacksP1[3] = {x+0.5,y+1.2,z};
  float CjacksP2[3] = {x+1,y+0.8,z};
  float CjacksP3[3] = {x+1,y+0.8,z+2};
  float CmyNormalVec[3] = {0};
  jacksonNormal(CmyNormalVec,CjacksP1,CjacksP2,CjacksP3);
  glBegin(GL_QUADS);
  glNormal3f(-CmyNormalVec[0],-CmyNormalVec[1],-CmyNormalVec[2]);
  glColor3f(1,1,1);
  glTexCoord2f(0,0);glVertex3f(x+0.5,y+1.2,z);
  glTexCoord2f(0,rep);glVertex3f(x+1,y+0.8,z);
  glTexCoord2f(rep,rep);glVertex3f(x+1,y+0.8,z+2);
  glTexCoord2f(rep,0);glVertex3f(x+0.5,y+1.2,z+2);
  glEnd();

  float DjacksP1[3] = {x+0.5,y+1.2,z};
  float DjacksP2[3] = {x,y+0.8,z};
  float DjacksP3[3] = {x,y+0.8,z+2};
  float DmyNormalVec[3] = {0};
  jacksonNormal(DmyNormalVec,DjacksP1,DjacksP2,DjacksP3);
  glColor3f(1,1,1);
  glBegin(GL_POLYGON);
  glNormal3f(DmyNormalVec[0],DmyNormalVec[1],DmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(x+0.5,y+1.2,z);
  glTexCoord2f(0,rep);glVertex3f(x,y+0.8,z);
  glTexCoord2f(rep,rep);glVertex3f(x,y+0.8,z+2);
  glTexCoord2f(rep,0);glVertex3f(x+0.5,y+1.2,z+2);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,texture[8]);

  //sides
  float EjacksP1[3] = {x,y,z};
  float EjacksP2[3] = {x,y,z+2};
  float EjacksP3[3] = {x,y+0.8,z+2};
  float EmyNormalVec[3] = {0};
  jacksonNormal(EmyNormalVec,EjacksP1,EjacksP2,EjacksP3);
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glNormal3f(EmyNormalVec[0],EmyNormalVec[1],EmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(x,y,z);
  glTexCoord2f(0,rep);glVertex3f(x,y,z+2);
  glTexCoord2f(rep,rep);glVertex3f(x,y+0.8,z+2);
  glTexCoord2f(rep,0);glVertex3f(x,y+0.8,z);
  glEnd();

  float FjacksP1[3] = {x+1,y,z};
  float FjacksP2[3] = {x+1,y,z+2};
  float FjacksP3[3] = {x+1,y+0.8,z+2};
  float FmyNormalVec[3] = {0};
  jacksonNormal(FmyNormalVec,FjacksP1,FjacksP2,FjacksP3);
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glNormal3f(-FmyNormalVec[0],-FmyNormalVec[1],-FmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(x+1,y,z);
  glTexCoord2f(0,rep);glVertex3f(x+1,y,z+2);
  glTexCoord2f(rep,rep);glVertex3f(x+1,y+0.8,z+2);
  glTexCoord2f(rep,0);glVertex3f(x+1,y+0.8,z);
  glEnd();

  //bottom
  float GjacksP1[3] = {x,y,z};
  float GjacksP2[3] = {x+1,y,z};
  float GjacksP3[3] = {x+1,y,z+2};
  float GmyNormalVec[3] = {0};
  jacksonNormal(GmyNormalVec,GjacksP1,GjacksP2,GjacksP3);
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glNormal3f(GmyNormalVec[0],GmyNormalVec[1],GmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(x,y,z);
  glTexCoord2f(0,rep);glVertex3f(x+1,y,z);
  glTexCoord2f(rep,rep);glVertex3f(x+1,y,z+2);
  glTexCoord2f(rep,0);glVertex3f(x,y,z+2);
  glEnd();


  glDisable(GL_TEXTURE_2D);



  glPopMatrix();

}

static void jacksonsStar(double x, double y, double z,
                         double dx, double dy, double dz,
                         double th)
{
  glPushMatrix();

  glTranslated(x,y,z);
  glRotated(th,0,1,0);
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

  float AjacksP1[3] = {x,y,z};
  float AjacksP2[3] = {x-2,y-3,z};
  float AjacksP3[3] = {x+2,y-3,z};
  float AmyNormalVec[3] = {0};
  jacksonNormal(AmyNormalVec,AjacksP1,AjacksP2,AjacksP3);

  //HERE I AM PUTTING IN MY TEXTURES FOR THE STAR
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glBindTexture(GL_TEXTURE_2D,texture[7]);


  glColor3f(1,1,0);
  glBegin(GL_TRIANGLES);
  glNormal3f(-AmyNormalVec[0],-AmyNormalVec[1],-AmyNormalVec[2]);

  //front face
  //triangle 1
  glTexCoord2f(0.5,1);glVertex3f(x,y,z);
  glTexCoord2f(0,0);glVertex3f(x-2,y-3,z);
  glTexCoord2f(0,1);glVertex3f(x+2,y-3,z);
  glEnd();

  //triangle 2
  float BjacksP1[3] = {x,y-4,z};
  float BjacksP2[3] = {x-2,y-1,z};
  float BjacksP3[3] = {x+2,y-1,z};
  float BmyNormalVec[3] = {0};
  jacksonNormal(BmyNormalVec,BjacksP1,BjacksP2,BjacksP3);
  glBegin(GL_TRIANGLES);
  glNormal3f(BmyNormalVec[0],BmyNormalVec[1],BmyNormalVec[2]);
  glTexCoord2f(0.5,-1);glVertex3f(x,y-4,z);
  glTexCoord2f(0,0);glVertex3f(x-2,y-1,z);
  glTexCoord2f(0,1);glVertex3f(x+2,y-1,z);
  glEnd();

  //back face

  //triangle 1
  float CjacksP1[3] = {x,y,z+1};
  float CjacksP2[3] = {x-2,y-3,z+1};
  float CjacksP3[3] = {x+2,y-3,z+1};
  float CmyNormalVec[3] = {0};
  jacksonNormal(CmyNormalVec,CjacksP1,CjacksP2,CjacksP3);
  glBegin(GL_TRIANGLES);
  glNormal3f(CmyNormalVec[0],CmyNormalVec[1],CmyNormalVec[2]);
  glTexCoord2f(0.5,1);glVertex3f(x,y,z+1);
  glTexCoord2f(0,0);glVertex3f(x-2,y-3,z+1);
  glTexCoord2f(0,1);glVertex3f(x+2,y-3,z+1);
  glEnd();

  //triangle 2
  float DjacksP1[3] = {x,y-4,z+1};
  float DjacksP2[3] = {x-2,y-1,z+1};
  float DjacksP3[3] = {x+2,y-1,z+1};
  float DmyNormalVec[3] = {0};
  jacksonNormal(DmyNormalVec,DjacksP1,DjacksP2,DjacksP3);
  glBegin(GL_TRIANGLES);
  glNormal3f(-DmyNormalVec[0],-DmyNormalVec[1],-DmyNormalVec[2]);
  glTexCoord2f(0.5,-1);glVertex3f(x,y-4,z+1);
  glTexCoord2f(0,0);glVertex3f(x-2,y-1,z+1);
  glTexCoord2f(0,1);glVertex3f(x+2,y-1,z+1);
  glEnd();

  //Now I must do the sides to close the surface
  float EjacksP1[3] = {x,y,z};
  float EjacksP2[3] = {x,y,z+1};
  float EjacksP3[3] = {x-2,y-3,z+1};
  float EmyNormalVec[3] = {0};
  jacksonNormal(EmyNormalVec,EjacksP1,EjacksP2,EjacksP3);
  glBegin(GL_QUADS);
  glNormal3f(-EmyNormalVec[0],-EmyNormalVec[1],-EmyNormalVec[2]);
  glColor3f(1,1,0);

  //3 rectangles needed to seal off triangle 1
  glTexCoord2f(0,0);glVertex3f(x,y,z);
  glTexCoord2f(1,0);glVertex3f(x,y,z+1);
  glTexCoord2f(1,1);glVertex3f(x-2,y-3,z+1);
  glTexCoord2f(0,1);glVertex3f(x-2,y-3,z);
  glEnd();


  //glColor3f(1,0,0);
  float FjacksP1[3] = {x,y,z};
  float FjacksP2[3] = {x,y,z+1};
  float FjacksP3[3] = {x+2,y-3,z+1};
  float FmyNormalVec[3] = {0};
  jacksonNormal(FmyNormalVec,FjacksP1,FjacksP2,FjacksP3);
  glBegin(GL_QUADS);
  glNormal3f(FmyNormalVec[0],FmyNormalVec[1],FmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(x,y,z);
  glTexCoord2f(1,0);glVertex3f(x,y,z+1);
  glTexCoord2f(1,1);glVertex3f(x+2,y-3,z+1);
  glTexCoord2f(0,1);glVertex3f(x+2,y-3,z);
  glEnd();

  float GjacksP1[3] = {x-2,y-3,z};
  float GjacksP2[3] = {x-2,y-3,z+1};
  float GjacksP3[3] = {x+2,y-3,z+1};
  float GmyNormalVec[3] = {0};
  jacksonNormal(GmyNormalVec,GjacksP1,GjacksP2,GjacksP3);
  glBegin(GL_QUADS);
  glNormal3f(-GmyNormalVec[0],-GmyNormalVec[1],-GmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(x-2,y-3,z);
  glTexCoord2f(1,0);glVertex3f(x-2,y-3,z+1);
  glTexCoord2f(1,1);glVertex3f(x+2,y-3,z+1);
  glTexCoord2f(0,1);glVertex3f(x+2,y-3,z);
  glEnd();

  //3 rectangles needed to seal off triangle 2
  float HjacksP1[3] = {x,y-4,z};
  float HjacksP2[3] = {x,y-4,z+1};
  float HjacksP3[3] = {x-2,y-1,z+1};
  float HmyNormalVec[3] = {0};
  jacksonNormal(HmyNormalVec,HjacksP1,HjacksP2,HjacksP3);
  glBegin(GL_QUADS);
  glNormal3f(HmyNormalVec[0],HmyNormalVec[1],HmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(x,y-4,z);
  glTexCoord2f(1,0);glVertex3f(x,y-4,z+1);
  glTexCoord2f(1,1);glVertex3f(x-2,y-1,z+1);
  glTexCoord2f(0,1);glVertex3f(x-2,y-1,z);
  glEnd();

  float IjacksP1[3] = {x,y-4,z};
  float IjacksP2[3] = {x,y-4,z+1};
  float IjacksP3[3] = {x+2,y-1,z+1};
  float ImyNormalVec[3] = {0};
  jacksonNormal(ImyNormalVec,IjacksP1,IjacksP2,IjacksP3);
  glBegin(GL_QUADS);
  glNormal3f(-ImyNormalVec[0],-ImyNormalVec[1],-ImyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(x,y-4,z);
  glTexCoord2f(1,0);glVertex3f(x,y-4,z+1);
  glTexCoord2f(1,1);glVertex3f(x+2,y-1,z+1);
  glTexCoord2f(0,1);glVertex3f(x+2,y-1,z);
  glEnd();


  float JjacksP1[3] = {x-2,y-1,z};
  float JjacksP2[3] = {x-2,y-1,z+1};
  float JjacksP3[3] = {x+2,y-1,z+1};
  float JmyNormalVec[3] = {0};
  jacksonNormal(JmyNormalVec,JjacksP1,JjacksP2,JjacksP3);
  glBegin(GL_QUADS);
  glNormal3f(JmyNormalVec[0],JmyNormalVec[1],JmyNormalVec[2]);
  glTexCoord2f(0,0);glVertex3f(x-2,y-1,z);
  glTexCoord2f(1,0);glVertex3f(x-2,y-1,z+1);
  glTexCoord2f(1,1);glVertex3f(x+2,y-1,z+1);
  glTexCoord2f(0,1);glVertex3f(x+2,y-1,z);
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
   glVertex3d(x,y,z);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
static void ball(double x,double y,double z,double r)
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph=-90;ph<40;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}


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
      float Position[]  = {distance*Cos(zh),distance*Sin(zh),ylight,1.0};   //HERE I SWITCHED THE AXES THAT THE LIGHT IS ROTATING AROUND
      if(orbit)
      {
         Position[1] = ylight;
         Position[2] = distance*Sin(zh);
      }
      
      //////////
      /*
      if(obj==2)
      {
         Position[0] = 10*Cos(zh);
         Position[1] = 10*Sin(zh);
         Position[2] =0;
      }
      */
      ///////////
      /*
      if(orbit)
      {
         Position[0]  = distance*Cos(zh);
         Position[1] = ylight;
         Position[2] = distance*Sin(zh),1.0};
      }
      */
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 0.1);
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
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
      glDisable(GL_LIGHTING);

   //  Draw individual objects
   if (obj==1)
   {
      jacksonsHouse(0,0,0 , 1,2,2, 0);
   }
   else if (obj==2)
   {
      jacksonsStar(0,1,0 ,0.7,0.7,0.7, 0);
   }
     
   else if (obj==3)
   {
      jacksonsCube(0,0,0 , 1,1,1 , 0);
      ball(0,2,0,1);
   }
   else
   {
      for(int i=0;i<3;i++)
      {
       jacksonsHouse(i*1,0,0, i*1+1,2,2, 0);
      }
      jacksonsHouse(0,0,3, 1,1,1, 0);

      jacksonsStar(8*Cos(zh),8*Sin(zh),0, 0.7,0.7,0.7, 0);
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
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
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
   else if (ch=='s' && specular>0)
      specular -= 5;
   else if (ch=='S' && specular<100)
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
         dim=8;
      else if (obj==2)
         dim=7;
      else if (obj==3)
         dim=3;
      else
         dim=14;
   }

   //MY CONTROLS
   else if (ch == 'c' || ch=='C')
      orbit = 1-orbit;
   //  Light elevation
   else if (ch=='u')
      ylight -= 0.1;
   else if (ch=='U')
      ylight += 0.1;

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
   //TEST CASE FOR MY FUNCTION FOR CALCULATING NORMALS!
   //glNormal3f( 0, 0, 1);
   //glVertex3f(-1,-1, 1);
   //glVertex3f(+1,-1, 1);
   //glVertex3f(+1,+1, 1);

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
   texture[0] = LoadTexBMP("crate.bmp");
   texture[1] = LoadTexBMP("img1.bmp");
   texture[2] = LoadTexBMP("img2.bmp");
   texture[3] = LoadTexBMP("img3.bmp");
   texture[4] = LoadTexBMP("img4.bmp");
   texture[5] = LoadTexBMP("img5.bmp");
   texture[6] = LoadTexBMP("img6.bmp");
   texture[7] = LoadTexBMP("secondTrySun.bmp");
   texture[8] = LoadTexBMP("brickwall.bmp");
   texture[9] = LoadTexBMP("roofing.bmp");

   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}

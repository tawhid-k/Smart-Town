#include <iostream>
using namespace std;

#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#define pi 3.14159265358979323846

GLfloat car1 = 0.0f, car2 = 0.0f, car3 = 0.0f, car4 = 0.0f;
GLfloat rainX = 0.0f, rainY = 0.0f;
GLfloat day_r = 1.0f, day_g = 1.0f, day_b = 0.8f;
GLfloat sun_x = 800.0f, sun_y = 850.0f, sun_r = 1.0f, sun_g = 0.7f, sun_b = 0.0f;
GLfloat t1r[3], t1g[3], t1b[3];
GLfloat birdX = 0.7f, birdY =-0.15f;

int t1ch = 1, cnt = 0;

bool goRain = false, day = true;

void birdMoves(int x)
{
    if (birdX < -5.00f || birdY > 5.00f) {
      if (!day) return;
      birdX = 0.7;
      birdY = -0.15;
    }
    birdX-=.001;
    birdY+=.0001;
}

void runCars (int v) {
  if (!(t1ch == 0 && (car1 >= -0.85f && car1 <= -0.80f))) {
  car1 += 0.0012f;
  if (car3 < -1.5f) car3 = 0.2f;
  if (car3 < -0.35f) car3 -= 0.001f;
  else if (car3 > -0.3f) car3 -= 0.0012f;
  if (car1 > 3.0f) {
    car1 = -2.0f;
  }
  if (car4 < -1.5f) car4 = 0.4f;
  if (car4 < -0.09f) car4 -= 0.001f;
  else if (car4 > -0.07f) car4 -= 0.0015f;
  if (car1 > 3.0f) {
    car1 = -2.0f;
  }
}
  if (!(t1ch == 0 && (car2 >= -0.07f && car2 <= -0.05f))) {
  car2 += 0.001f;
  if (car3 < -1.5f) car3 = 0.2f;
  if (car3 < -0.35f) car3 -= 0.001f;
  else if (car3 > -0.3f) car3 -= 0.0012f;
  if (car1 > 3.0f) {
    car1 = -2.0f;
  }
  if (car4 < -1.5f) car4 = 0.4f;
  if (car4 < -0.09f) car4 -= 0.001f;
  if (car2 > 3.0f) {
    car2 = -2.0f;
  }
}
  if (t1ch == 0 && !(car1 >= -0.44f && car1 <= 0.11f) && !(car2 >= 0.18f && car2 <= 1.04f)) {
    car3 -= 0.0012f;
    car4 -= 0.001f;
    if (car3 < -1.5f) car3 = 0.2f;
    if (car4 < -1.5f) car4 = 0.4f;
  }
}

void bird()  {
  glScalef(1.3,1.3,0);
  glTranslatef(0,-.1,0);
  glPushMatrix();
  glTranslatef(birdX,birdY,0);
  glBegin(GL_LINES);
  glColor3f(1,0,0);
  glVertex2f(0.2f,0.8f);
  glVertex2f(0.18f,0.77f);
  glVertex2f(0.18f,0.77f);
  glVertex2f(0.15f,0.79f);
  glVertex2f(0.13f,0.8f);
  glVertex2f(0.11f,0.77f);
  glVertex2f(0.11f,0.77f);
  glVertex2f(0.08f,0.79f);
  glEnd();
  glPopMatrix();
  glLoadIdentity();
  glutTimerFunc(100,birdMoves,0);
}

void keepRaining (int v) {
   if (goRain) {
     rainX -= 0.2f;
     rainY -= 0.2f;
     if (rainX < -0.2f) {
      rainX = 0.0f;
      rainY = 0.0f;
     }
     glutTimerFunc(100, keepRaining, 0);
   }
}

void raiseMoon (int v) {
   if (sun_b == 0.0f) {
     sun_g = 1.0f; sun_b = 1.0f;
   }
   if (sun_y < 850.0f) {
     sun_y += 10.0f;
     glutTimerFunc(100, raiseMoon, 0);
   }
   else return;
}

void raiseSun (int v) {
   if (sun_b == 1.0f) {
     sun_g = 0.7f, sun_b = 0.0f;
   }
   if (sun_y < 850.0f) {
     sun_y += 10.0f;
     glutTimerFunc(100, raiseSun, 0);

   }
}

void day_night (int v) {
   if (!day) {
     if (day_r <= 0.0f && day_g <= 0.0f, day_b <= 0.0f) {
        glutTimerFunc(100, raiseMoon, 0);
        return;
     }
     if (day_g > 0.0f) day_g -= 0.03f;
     else if (day_r > 0.0f) day_r -= 0.03f;
     else if (day_b > 0.0f) day_b -= 0.03f;
     if (sun_y > 400) sun_y -= 10.0f;
     glutTimerFunc(100, day_night, 0);
   }
   else {
     if (day_r == 1.0f && day_g == 1.0f && day_b == 0.8f) {
       glutTimerFunc(100, raiseSun, 0);
       return;
     }
     if (day_r < 1.0f) day_r += 0.03f;
     else if (day_b < 0.8f) day_b += 0.03f;
     else if (day_g < 1.0f) day_g += 0.03f;
     if (sun_y > 400) sun_y -= 10.0f;
     glutTimerFunc(100, day_night, 0);
   }
}

void Idle()
{
    glutPostRedisplay();
}

void Control_Through_Keyboard (unsigned char key, int x, int y) {
    switch (key) {
      case 'r':
      if (goRain) {
        goRain = false;
      }
      else {
        goRain = true;
        glutTimerFunc(100, keepRaining, 0);
      }
      break;
      case 'x':
      t1ch++;
      t1ch %= 3;
      for (int i = 0; i < 3; i++) {
        t1r[i] = 0.0f; t1g[i] = 0.0f; t1b[i] = 0.0f;
      }
      if (t1ch == 1) {
        t1r[1] = 1.0f; t1g[1] = 1.0f; t1b[1] = 0.0f;
        cnt = 0;
      }
      else if (t1ch == 2) {
        t1r[2] = 0.0f; t1g[2] = 1.0f; t1b[2] = 0.0f;
      }
      else {
        t1r[0] = 1.0f; t1g[0] = 0.0f; t1b[0] = 0.0f;
        cnt = 0;
      }
      break;
      case 'c':
      cout << car2  << endl;
      break;
    }
    glutPostRedisplay();
}

void Control_Through_Mouse (int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
      if (day) {
        day = false;
        glutTimerFunc(100, day_night, 0);
      }
    }
    else if (button == GLUT_RIGHT_BUTTON) {
      if (!day) {
        day = true;
        glutTimerFunc(100, day_night, 0);
      }
    }
}

void drawCircle (GLfloat x, GLfloat y, GLfloat rad, GLfloat a, GLfloat b, GLfloat c) {
	x /= 1000.0; y /= 1000.0; rad /= 1000.0;
	int triangleAmount = 100;
	GLfloat twicePi = 2.0f * pi;
	glBegin(GL_TRIANGLE_FAN);
    glColor3f(a, b, c);
    glVertex2f(x, y);
    for(int i = 0; i <= triangleAmount; i++) {
       glVertex2f( x + (rad * cos(i *  twicePi / triangleAmount)),
       y + (rad * sin(i * twicePi / triangleAmount)));
    }
	glEnd();
}

void drawTriangle (GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat a, GLfloat b, GLfloat c) {
    x1 /= 1000.0; y1 /= 1000.0; x2 /= 1000.0; y2 /= 1000.0; x3 /= 1000.0; y3 /= 1000.0;
    glBegin(GL_TRIANGLES);
    glColor3f(a, b, c);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawLine (GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat a, GLfloat b, GLfloat c , int w) {
    x1 /= 1000.0; y1 /= 1000.0; x2 /= 1000.0; y2 /= 1000.0;
    glLineWidth(w);
    glBegin(GL_LINES);
    glColor3f(a, b, c);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawQuad (GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4, GLfloat a, GLfloat b, GLfloat c) {
    x1 /= 1000.0; y1 /= 1000.0; x2 /= 1000.0; y2 /= 1000.0; x3 /= 1000.0; y3 /= 1000.0; x4 /= 1000.0; y4 /= 1000.0;
    glBegin(GL_QUADS);
    glColor3f(a, b, c);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
}

void drawBuilding (GLfloat x1, GLfloat y1, GLfloat height, GLfloat weight) {
   drawQuad(x1, y1, x1 + weight, y1, x1 + weight, y1 + height, x1, y1 + height, 0.4, 0.7, 0.7);
}

void drawWindow (GLfloat x, GLfloat y, GLfloat inc) {
   drawQuad(x, y, x + inc, y, x + inc, y + inc, x, y + inc, 0.9, 0, 0);
   drawQuad(x + inc*0.1, y + inc*0.1, x + inc - (inc*0.1), y + inc*0.1, x + inc - inc*0.1, y + inc - inc*0.1, x + inc*0.1, y + inc - inc*0.1, 0.5, 1.0, 0.9);
}

void display() {

	glClearColor(day_r, day_g, day_b, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glTranslatef(0.0f, 0.0f, 0.0f);

	drawCircle(sun_x, sun_y, 130, sun_r, sun_g, sun_b);
	//Buildings starting from y = 400
    glScalef(1, 0.8, 0.0);
    drawBuilding(-1000, 500, 200, 100);
    drawBuilding(-900, 500, 400, 100);
    drawBuilding(-900, 500, 400, 100);
    drawBuilding(-750, 500, 300, 50);
    drawBuilding(-700, 500, 400, 50);
    drawBuilding(-650, 500, 500, 100);
    drawBuilding(-550, 500, 400, 50);
    drawBuilding(-500, 500, 300, 50);
    drawBuilding(-400, 500, 400, 100);
    drawBuilding(-300, 500, 500, 200);
    drawBuilding(-100, 500, 200, 100);
    drawBuilding(0, 500, 400, 200);
    drawBuilding(100, 500, 500, 50);
    drawBuilding(200, 500, 450, 100);
    drawBuilding(300, 500, 350, 100);
    drawBuilding(400, 500, 200, 100);
    drawBuilding(450, 500, 300, 50);
    drawBuilding(500, 500, 400, 50);
    drawBuilding(550, 500, 500, 50);
    drawBuilding(600, 500, 400, 50);
    drawBuilding(650, 500, 300, 50);
    drawBuilding(700, 500, 200, 50);
    drawBuilding(750, 500, 350, 50);
    drawBuilding(800, 500, 300, 100);
    drawBuilding(900, 500, 200, 100);
    glLoadIdentity();
    // End - Buildings

	bird();

    // Upper - Left houses
    // X(-1000, -300) Y(400, -250)
    drawQuad(-1000, -250, -300, -250, -300, 500, -1000, 500, 0.8, 0.9, 0.5);
    drawQuad(-1000, -200, -350, -200, -350, 500, -1000, 500, 0, 0.6, 0.2);
    drawLine(-530, -100, -530, 400, 0.7, 0.3, 0.2, 10);
    drawCircle(-900, 330, 80, 0.7, 0.9, 0.4);
    drawCircle(-820, 380, 80, 0.7, 0.9, 0.4);
    drawCircle(-750, 330, 80, 0.7, 0.9, 0.4);
    glTranslatef(-0.15, 0.15, 0);
    glScalef(0.8, 0.8, 1);
    drawCircle(-480, 380, 100, 0.7, 0.9, 0.4);
    drawCircle(-550, 340, 80, 0.7, 0.9, 0.4);
    drawCircle(-410, 340, 80, 0.7, 0.9, 0.4);
    glLoadIdentity();
    drawQuad(-950, -150, -600, -150, -600, 200, -950, 200, 0.9, 0.6, 0);
    drawQuad(-600, -150, -400, -150, -400, 200, -600, 200, 0.9, 0.7, 0);
    drawQuad(-600, 205, -480, 320, -850, 320, -980, 205, 0.9, 0.0, 0.3);
    drawQuad(-400, 205, -370, 210, -480, 320, -500, 305, 0.9, 0.0, 0.3);
    drawQuad(-700, -10, -700, 160, -850, 160, -850, -10, 0.9, 0.0, 0.0);
    drawQuad(-710, 0, -710, 150, -840, 150, -840, 0, 0.5, 1.0, 0.9);
    drawLine(-700, 80, -850, 80, 0.9, 0.0, 0.0, 3);
    drawLine(-775, -10, -775, 160, 0.9, 0.0, 0.0, 3);
    drawQuad(-570, -150, -570, 90, -430, 90, -430, -150, 1, 0.3, 0.3);
    drawCircle(-530, 3, 20, 0.8, 0.9, 0.8);
    drawTriangle(-400, 200, -500, 300, -600, 200, 0.9, 0.7, 0);
    drawLine(-950, 205, -600, 205, 1, 1, 1, 3);
    drawLine(-600, 205, -500, 305, 1, 1, 1, 3);
    drawLine(-500, 305, -400, 205, 1, 1, 1, 3);
    glScalef(.65, .65, 0);
    glTranslatef(.01, .19, 0);
    drawQuad(-700, -10, -700, 160, -850, 160, -850, -10, 0.9, 0.0, 0.0);
    drawQuad(-710, 0, -710, 150, -840, 150, -840, 0, 0.5, 1.0, 0.9);
    drawLine(-700, 80, -850, 80, 0.9, 0.0, 0.0, 3);
    glLoadIdentity();
    // End

    // Upper - Right houses
    // X(1000, 300) Y(400, -250)
    drawQuad(1000, -250, 1000, 500, 300, 500, 300, -250, 0.8, 0.9, 0.5);
    drawQuad(1000, -200, 1000, 500, 350, 500, 350, -200, 0, 0.6, 0.2);
    drawQuad(1000, -50, 1000, 350, 400, 350, 400, -50, 0.9, 0.5, 0.3);
    drawQuad(1000, 350, 1000, 380, 380, 380, 380, 350, 1, 1, 1);
    drawQuad(1000, 380, 1000, 480, 430, 480, 360, 380, 0.9, 0, 0.3);
    drawQuad(1000, 180, 1000, 200, 400, 200, 400, 180, 0.9, 0.9, 0.9);

    drawQuad(720, -100, 720, 400, 550, 400, 550, -100, 1, 0.5, 0.3);
    drawQuad(720, 150, 720, 180, 550, 180, 550, 150, 1, 1, 1);
    drawTriangle(720, 400, 635, 480, 550, 400, 1, 0.5, 0.3);
    drawQuad(540, 390, 635, 480, 635, 500, 520, 390, 1, 1, 1);
    drawQuad(740, 400, 635, 500, 635, 480, 720, 400, 1, 1, 1);
    drawQuad(520, 390, 635, 500, 635, 530, 490, 390, 1, 0.2, 0.2);
    drawQuad(770, 400, 635, 530, 635, 500, 740, 400, 1, 0.2, 0.2);
    drawQuad(910, -50, 910, 130, 790, 130, 790, -50, 1, 0.3, 0.3);
    drawQuad(900, -50, 900, 120, 800, 120, 800, -50, 0.9, 0.8, 0.5);
    drawCircle(820, 20, 10, 1, 1, 1);
    drawWindow(550, 230, 80);
    drawWindow(640, 230, 80);
    drawWindow(560, -40, 150);
    drawWindow(420, 230, 100);
    drawWindow(420, 0, 100);
    drawWindow(750, 230, 100);
    drawWindow(870, 230, 100);
    glLoadIdentity();
    //End

    // Lower - left corner
    // X(-1000, -300) Y(-1000, -750)
    drawQuad(-1000, -750, -1000, -1000, -300, -1000, -300, -750, 0.8, 0.9, 0.5);
    drawQuad(-1000, -800, -1000, -1000, -350, -1000, -350, -800, 0, 0.6, 0.2);
    //End

    // Lower - Right corner
    // X(1000, 300) Y(-1000, -750)
    drawQuad(1000, -750, 300, -750, 300, -1000, 1000, -1000, 0.8, 0.9, 0.5);
    drawQuad(1000, -800, 350, -800, 350, -1000, 1000, -1000, 0, 0.6, 0.2);
    //End

    //Roads
    // X(300, -300) Y(500, -1000)
    drawQuad(300, -1000, -300, -1000, -300, 500, 300, 500, 0.8, 0.9, 1.0);
    // X(-1000, 1000) Y(-250, -750)
    drawQuad(1000, -750, -1000, -750, -1000, -250, 1000, -250, 0.8, 0.9, 1.0);
    // End


    // Car
    glTranslatef(car1, 0, 0);
    glTranslatef(0.0, 0.0, 0);
    drawCircle(10, -480, 50, 0, 0, 0);
    drawCircle(10, -480, 10, 1, 1, 1);
    drawCircle(300, -480, 50, 0, 0, 0);
    drawCircle(300, -480, 10, 1, 1, 1);
    drawQuad(-40, -460, 350, -460, 350, -350, -40, -350, 0.7, 0.3, 0.9);
    drawCircle(-40, -405, 55, 0.7, 0.3, 0.9);
    drawCircle(350, -405, 55, 0.7, 0.3, 0.9);
    drawCircle(380, -405, 25, 1, 1, 1);
    drawQuad(340, -350, 300, -270, 10, -270, -30, -350, 0, 0.0, 0.0);
    drawQuad(-20, -350, 330, -350, 290, -290, 20, -290, 0.5, 1.0, 0.9);
    drawLine(162, -270, 162, -350, 0, 0.0, 0.0, 3);
    drawLine(-30, -352, 340, -350, 0, 0, 0, 2);
    /*drawLine(-30, -350, -30, -460, 0, 0, 0, 2);
    drawLine(340, -350, 340, -460, 0, 0, 0, 2);*/
    drawLine(165, -350, 165, -460, 0, 0, 0, 2);
    glLoadIdentity();
    // End

    // Car
    glTranslatef(car2, 0, 0);
    glTranslatef(-0.8, -0.2, 0);
    drawCircle(10, -480, 50, 0, 0, 0);
    drawCircle(10, -480, 10, 1, 1, 1);
    drawCircle(300, -480, 50, 0, 0, 0);
    drawCircle(300, -480, 10, 1, 1, 1);
    drawQuad(-40, -460, 350, -460, 350, -350, -40, -350, 0.9, 0.0, 0.0);
    drawCircle(-40, -405, 55, 0.9, 0.0, 0.0);
    drawCircle(350, -405, 55, 0.9, 0.0, 0.0);
    drawCircle(380, -405, 25, 1, 1, 1);
    drawQuad(340, -350, 300, -270, 10, -270, -30, -350, 0, 0.0, 0.0);
    drawQuad(-20, -350, 330, -350, 290, -290, 20, -290, 0.5, 1.0, 0.9);
    drawLine(162, -270, 162, -350, 0, 0.0, 0.0, 3);
    drawLine(-30, -352, 340, -350, 0, 0, 0, 2);
    drawLine(165, -350, 165, -460, 0, 0, 0, 2);
    glLoadIdentity();


    //3rd car
    glPushMatrix();
    glTranslatef(0, car3, 0);
    drawCircle(200,90,40,0,0,0);
    drawCircle(50,90,40,0,0,0);
    drawCircle(200,90,15,1,1,1);
    drawCircle(50,90,15,1,1,1);
    drawQuad(0,100,250,100,250,220,0,220,.7,.2,.5);
    drawQuad(0,220,250,220,200,350,50,350,0,0,0);
    drawQuad(30,220,220,220,180,320,80,320,.5,1,.9);
    drawCircle(60,150,40,1,1,1);
    drawCircle(185,150,40,1,1,1);
    glPopMatrix();
    glLoadIdentity();
    //End

    //4rth car
    glPushMatrix();
    glTranslatef(0, car4, 0);
    glTranslatef(-.28,-0.2,0);
    drawCircle(200,90,40,0,0,0);
    drawCircle(50,90,40,0,0,0);
    drawCircle(200,90,15,1,1,1);
    drawCircle(50,90,15,1,1,1);
    drawQuad(0,100,250,100,250,220,0,220,.1,.4,.7);
    drawQuad(0,220,250,220,200,350,50,350,0,0,0);
    drawQuad(30,220,220,220,180,320,80,320,.5,1,.9);
    drawCircle(60,150,40,1,1,1);
    drawCircle(185,150,40,1,1,1);
    glLoadIdentity();
    // End

    // Raining
    if (goRain) {
       glTranslatef(rainX, rainY, 0);
	   for (double i = -1.0f; i < 1.0f; i += 0.15f) {
          for (double j = -1.0f; j < 1.0f; j += 0.15f) {
            drawLine(i * 1000, j * 1000, (i - 0.1f) * 1000, (j - 0.1f) * 1000, 1, 1, 1, 1);
          }
	   }
	   glLoadIdentity();
    }
    // End


    //Traffic light
    glTranslatef(-0.35, -0.9, 0);
    drawQuad(0, 0, 100, 0, 70, 80, 30, 80, 0, 0, 0);
    drawLine(50, 50, 50, 300, 0, 0, 0, 5);
    drawQuad(0, 300, 100, 300, 100, 600, 0, 600, 0, 0, 0);
    drawCircle(50, 550, 50, t1r[0], t1g[0], t1b[0]);
    drawCircle(50, 450, 50, t1r[1], t1g[1], t1b[1]);
    drawCircle(50, 350, 50, t1r[2], t1g[2], t1b[2]);
    glLoadIdentity();
    //End

    glutTimerFunc(100, runCars, 0);
	glFlush();
}

int main(int argc, char** argv) {

	cout << "1. Press X for traffic control" << endl;
	cout << "2. Press R for raining" << endl;
	cout << "3. Left mouse clicking for night" << endl;
	cout << "4. Right mouse clicking for day" << endl;
	glutInit(&argc, argv);
	glutCreateWindow("OpenGL Setup");
	glutInitWindowSize(320, 320);
	glutDisplayFunc(display);
	glutIdleFunc(Idle);

	glutKeyboardFunc(Control_Through_Keyboard);
	glutMouseFunc(Control_Through_Mouse);
	glutMainLoop();
	return 0;
}

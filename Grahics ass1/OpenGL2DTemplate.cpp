
#include <random>
#include <iostream>
#include <glut.h>

using namespace std;

double playerX = 285;
double playerY = 247.5;
double c1x = 0;
double c2x = 0;
double c3x = 0;
double c4x = 0;
double c5x = 0;
double c1y = 0;
double c2y = 0;
double c3y = 0;
double c4y = 0;
double c5y = 0;
double p1x = 0;
double p1y = 0;
double p2x = 0;
double p2y = 0;
int score = 0;
int lives = 5;
int Time = 200;
bool c1collected = false;
bool c2collected = false;
bool c3collected = false;
bool c4collected = false;
bool c5collected = false;
bool p1collected = false;
bool p2collected = false;
bool gcollected = false;
int rot = 0;
double rotanim = 0;
bool faceup = true;
bool facedown = false;
bool faceleft = false;
bool faceright = false;
bool doublescore = false;
bool timestop = false;
bool won = false;
bool lost = false;
double animmove = 0;

void print(int x, int y, char* string)
{
	int len, i;


	glRasterPos2f(x, y);


	len = (int)strlen(string);


	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
void drawplayer() {
	glPushMatrix();

	glTranslated(playerX, playerY, 0);
	glTranslated(15.0, 15.0, 0);
	glRotated(rot, 0, 0, 1);
	glTranslated(-15.0, -15.0, 0);
	glColor3ub(214, 233, 255);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(30.0, 0);
	glVertex2f(30.0, 30.0);
	glVertex2f(0, 30.0);
	glEnd();



	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex2f(310.0f - 285.0f, 272.5f - 247.5f);
	glEnd();

	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex2f(290.0f - 285.0f, 272.5f - 247.5f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(300.0f - 285.0f, 270.0f - 247.5f);
	glVertex2f(300.0f - 285.0f, 265.0f - 247.5f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex2f(295.0f - 285.0f, 260.0f - 247.5f);
	glVertex2f(305.0f - 285.0f, 260.0f - 247.5f);
	glVertex2f(300.0f - 285.0f, 250.0f - 247.5f);
	glEnd();

	glPopMatrix();

}
void drawobstacles() {

	glPushMatrix();
	glColor3ub(27, 67, 186);
	glBegin(GL_QUADS);
	glVertex2f(100.0f, 105.0f);
	glVertex2f(105.0f, 105.0f);
	glVertex2f(105.0f, 85.0f);
	glVertex2f(100.0f, 85.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(92.5f, 97.5f);
	glVertex2f(112.5f, 97.5f);
	glVertex2f(112.5f, 92.5f);
	glVertex2f(92.5f, 92.5f);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslated(400, 0, 0);
	glColor3ub(27, 67, 186);
	glBegin(GL_QUADS);
	glVertex2f(100.0f, 105.0f);
	glVertex2f(105.0f, 105.0f);
	glVertex2f(105.0f, 85.0f);
	glVertex2f(100.0f, 85.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(92.5f, 97.5f);
	glVertex2f(112.5f, 97.5f);
	glVertex2f(112.5f, 92.5f);
	glVertex2f(92.5f, 92.5f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(400, 300, 0);
	glColor3ub(27, 67, 186);
	glBegin(GL_QUADS);
	glVertex2f(100.0f, 105.0f);
	glVertex2f(105.0f, 105.0f);
	glVertex2f(105.0f, 85.0f);
	glVertex2f(100.0f, 85.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(92.5f, 97.5f);
	glVertex2f(112.5f, 97.5f);
	glVertex2f(112.5f, 92.5f);
	glVertex2f(92.5f, 92.5f);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslated(0, 300, 0);
	glColor3ub(27, 67, 186);
	glBegin(GL_QUADS);
	glVertex2f(100.0f, 105.0f);
	glVertex2f(105.0f, 105.0f);
	glVertex2f(105.0f, 85.0f);
	glVertex2f(100.0f, 85.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(92.5f, 97.5f);
	glVertex2f(112.5f, 97.5f);
	glVertex2f(112.5f, 92.5f);
	glVertex2f(92.5f, 92.5f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 150, 0);
	glColor3ub(27, 67, 186);
	glBegin(GL_QUADS);
	glVertex2f(100.0f, 105.0f);
	glVertex2f(105.0f, 105.0f);
	glVertex2f(105.0f, 85.0f);
	glVertex2f(100.0f, 85.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(92.5f, 97.5f);
	glVertex2f(112.5f, 97.5f);
	glVertex2f(112.5f, 92.5f);
	glVertex2f(92.5f, 92.5f);
	glEnd();
	glPopMatrix();

}
void drawpower1() {
	if (!p1collected) {
		glPushMatrix();
		glTranslated(p1x, p1y, 0);
		glTranslated(10.0f, 10.0f, 0);
		glRotated(rotanim, 0, 0, 1);
		glTranslated(-10.0f, -10.0f, 0);
		glColor3ub(94, 139, 242);
		glBegin(GL_QUADS);
		glVertex2f(92.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(97.5 - 92.5f, 105.0f - 85.0f);
		glVertex2f(97.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(92.5f - 92.5f, 85.0f - 85.0f);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(107.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(107.5f - 92.5f, 85.0f - 85.0f);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(92.5f - 92.5f, 90.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 90.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(92.5f - 92.5f, 85.0f - 85.0f);
		glEnd();

		glBegin(GL_QUADS);
		glVertex2f(92.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 100.0f - 85.0f);
		glVertex2f(92.5f - 92.5f, 100.0f - 85.0f);
		glEnd();
		glPopMatrix();
	}
}
void drawpower2() {
	if (!p2collected) {
		glPushMatrix();
		glTranslated(p2x, p2y, 0);
		glTranslated(10.0f, 10.0f, 0);
		glRotated(rotanim, 0, 0, 1);
		glTranslated(-10.0f, -10.0f, 0);
		glColor3ub(94, 139, 242);
		glBegin(GL_TRIANGLES);
		glVertex2f(92.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(92.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(100.0f - 92.5f, 95.0f - 85.0f);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2f(112.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(105.0f - 92.5f, 95.0f - 85.0f);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2f(112.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(92.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(102.5f - 92.5f, 92.5f - 85.0f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(92.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(102.5f - 92.5f, 97.5f - 85.0f);
		glEnd();
		glPopMatrix();
	}
}
void drawboundries() {



	glPushMatrix();
	glColor3ub(27, 67, 186);
	glBegin(GL_POLYGON);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(25.0f, 0.0f);
	glVertex2f(25.0f, 400.0f);
	glVertex2f(0.0f, 400.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(25.0f, 400.0f);
	glVertex2f(25.0f, 500.0f);
	glVertex2f(0.0f, 450.0f);
	glEnd();


	glPopMatrix();


	glPushMatrix();
	glColor3ub(27, 67, 186);
	glBegin(GL_POLYGON);
	glVertex2f(600.0f, 25.0f);
	glVertex2f(575.0f, 25.0f);
	glVertex2f(575.0f, 400.0f);
	glVertex2f(600.0f, 400.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(575.0f, 400.0f);
	glVertex2f(575.0f, 500.0f);
	glVertex2f(600.0f, 450.0f);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glColor3ub(27, 67, 186);
	glBegin(GL_POLYGON);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 25.0f);
	glVertex2f(500.0f, 25.0f);
	glVertex2f(500.0f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(500.0f, 25.0f);
	glVertex2f(600.0f, 25.0f);
	glVertex2f(550.0f, 0.0f);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glColor3ub(27, 67, 186);
	glBegin(GL_POLYGON);
	glVertex2f(0.0f, 525.0f);
	glVertex2f(0.0f, 500.0f);
	glVertex2f(500.0f, 500.0f);
	glVertex2f(500.0f, 525.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(500.0f, 500.0f);
	glVertex2f(600.0f, 500.0f);
	glVertex2f(550.0f, 525.0f);
	glEnd();
	glPopMatrix();

}

void drawgoal() {
	if (!gcollected) {
		glPushMatrix();
		glTranslated(-50, -50, 0);
		glTranslated(102.5, 95.0, 0);
		glRotated(rotanim, 0, 0, 1);
		glTranslated(-102.5, -95.0, 0);


		glColor3f(0, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f(92.5f, 105.0f);
		glVertex2f(97.5f, 105.0f);
		glVertex2f(97.5f, 85.0f);
		glVertex2f(92.5f, 85.0f);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(107.5f, 105.0f);
		glVertex2f(112.5f, 105.0f);
		glVertex2f(112.5f, 85.0f);
		glVertex2f(107.5f, 85.0f);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(92.5f, 90.0f);
		glVertex2f(112.5f, 90.0f);
		glVertex2f(112.5f, 85.0f);
		glVertex2f(92.5f, 85.0f);
		glEnd();

		glBegin(GL_QUADS);
		glVertex2f(92.5f, 105.0f);
		glVertex2f(112.5f, 105.0f);
		glVertex2f(112.5f, 100.0f);
		glVertex2f(92.5f, 100.0f);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2f(92.5f, 85.0f);
		glVertex2f(112.5f, 85.0f);
		glVertex2f(102.5f, 95.0f);
		glEnd();
		glPopMatrix();
	}
}
void drawcollects() {
	if (!c1collected) {
		glPushMatrix();
		glTranslated(c1x, c1y, 0);
		glTranslated(10.0f, 10.0f, 0);
		glRotated(rotanim, 0, 0, 1);
		glTranslated(-10.0f, -10.0f, 0);
		glColor3ub(167, 193, 238);
		glBegin(GL_QUADS);
		glVertex2f(92.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(97.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(97.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(92.5f - 92.5f, 85.0f - 85.0f);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(107.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(107.5f - 92.5f, 85.0f - 85.0f);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(92.5f - 92.5f, 97.5f - 85.0f);
		glVertex2f(112.5f - 92.5f, 97.5f - 85.0f);
		glVertex2f(112.5f - 92.5f, 92.5f - 85.0f);
		glVertex2f(92.5f - 92.5f, 92.5f - 85.0f);
		glEnd();
		glPopMatrix();
	}
	if (!c2collected) {
		glPushMatrix();
		glTranslated(c2x, c2y, 0);
		glTranslated(10.0f, 10.0f, 0);
		glRotated(rotanim, 0, 0, 1);
		glTranslated(-10.0f, -10.0f, 0);
		glColor3ub(167, 193, 238);
		glBegin(GL_QUADS);
		glVertex2f(92.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(97.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(97.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(92.5f - 92.5f, 85.0f - 85.0f);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(107.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(107.5f - 92.5f, 85.0f - 85.0f);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(92.5f - 92.5f, 97.5f - 85.0f);
		glVertex2f(112.5f - 92.5f, 97.5f - 85.0f);
		glVertex2f(112.5f - 92.5f, 92.5f - 85.0f);
		glVertex2f(92.5f - 92.5f, 92.5f - 85.0f);
		glEnd();
		glPopMatrix();
	}
	if (!c3collected) {
		glPushMatrix();
		glTranslated(c3x, c3y, 0);
		glTranslated(10.0f, 10.0f, 0);
		glRotated(rotanim, 0, 0, 1);
		glTranslated(-10.0f, -10.0f, 0);
		glColor3ub(167, 193, 238);
		glBegin(GL_QUADS);
		glVertex2f(92.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(97.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(97.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(92.5f - 92.5f, 85.0f - 85.0f);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(107.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(107.5f - 92.5f, 85.0f - 85.0f);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(92.5f - 92.5f, 97.5f - 85.0f);
		glVertex2f(112.5f - 92.5f, 97.5f - 85.0f);
		glVertex2f(112.5f - 92.5f, 92.5f - 85.0f);
		glVertex2f(92.5f - 92.5f, 92.5f - 85.0f);
		glEnd();
		glPopMatrix();
	}
	if (!c4collected) {
		glPushMatrix();
		glTranslated(c4x, c4y, 0);
		glTranslated(10.0f, 10.0f, 0);
		glRotated(rotanim, 0, 0, 1);
		glTranslated(-10.0f, -10.0f, 0);
		glColor3ub(167, 193, 238);
		glBegin(GL_QUADS);
		glVertex2f(92.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(97.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(97.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(92.5f - 92.5f, 85.0f - 85.0f);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(107.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(107.5f - 92.5f, 85.0f - 85.0f);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(92.5f - 92.5f, 97.5f - 85.0f);
		glVertex2f(112.5f - 92.5f, 97.5f - 85.0f);
		glVertex2f(112.5f - 92.5f, 92.5f - 85.0f);
		glVertex2f(92.5f - 92.5f, 92.5f - 85.0f);
		glEnd();
		glPopMatrix();
	}
	if (!c5collected) {
		glPushMatrix();
		glTranslated(c5x, c5y, 0);
		glTranslated(10.0f, 10.0f, 0);
		glRotated(rotanim, 0, 0, 1);
		glTranslated(-10.0f, -10.0f, 0);
		glColor3ub(167, 193, 238);
		glBegin(GL_QUADS);
		glVertex2f(92.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(97.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(97.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(92.5f - 92.5f, 85.0f - 85.0f);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(107.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 105.0f - 85.0f);
		glVertex2f(112.5f - 92.5f, 85.0f - 85.0f);
		glVertex2f(107.5f - 92.5f, 85.0f - 85.0f);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(92.5f - 92.5f, 97.5f - 85.0f);
		glVertex2f(112.5f - 92.5f, 97.5f - 85.0f);
		glVertex2f(112.5f - 92.5f, 92.5f - 85.0f);
		glVertex2f(92.5f - 92.5f, 92.5f - 85.0f);
		glEnd();
		glPopMatrix();
	}
}


void thetime(int val) {

	if (Time <= 0 && !gcollected)
		lost = true;

	if (!timestop && Time > 0) {
		Time--;
		glutTimerFunc(1000, thetime, 0);
	}
	else {
		glutTimerFunc(5000, thetime, 0);
		timestop = false;
	}



}
void Timerp1(int val) {
	if (val == 1)
		doublescore = false;

	if (!doublescore) {
		glutTimerFunc(1000, Timerp1, 0);
	}
	else {
		glutTimerFunc(5000, Timerp1, 1);

	}


}

void collect() {
	if (playerX > c1x - 26 && playerX < c1x + 16 && playerY>c1y + -27 && playerY < c1y + 15) {
		if (c1collected)
			return;
		c1collected = true;
		if (doublescore)
			score += 2;
		else
			score++;

	}
	else if (playerX > c2x - 26 && playerX < c2x + 16 && playerY>c2y - 27 && playerY < c2y + 15)
	{
		if (c2collected)
			return;
		c2collected = true;
		if (doublescore)
			score += 2;
		else
			score++;
	}
	else if (playerX > c3x - 26 && playerX < c3x + 16 && playerY>c3y - 27 && playerY < c3y + 15)
	{
		if (c3collected)
			return;
		c3collected = true;
		if (doublescore)
			score += 2;
		else
			score++;
	}
	else if (playerX > c4x - 26 && playerX < c4x + 16 && playerY>c4y - 27 && playerY < c4y + 15)
	{
		if (c4collected)
			return;
		c4collected = true;
		if (doublescore)
			score += 2;
		else
			score++;
	}
	else if (playerX > c5x - 26 && playerX < c5x + 16 && playerY>c5y - 27 && playerY < c5y + 15) {
		if (c5collected)
			return;
		c5collected = true;
		if (doublescore)
			score += 2;
		else
			score++;

	}
	else if (playerX > p1x - 20 && playerX < p1x + 22 && playerY>p1y - 27 && playerY < p1y + 17) {
		if (p1collected)
			return;
		p1collected = true;
		timestop = true;


	}
	else if (playerX > p2x - 20 && playerX < p2x + 22 && playerY>p2y - 27 && playerY < p2y + 17) {
		if (p2collected)
			return;
		p2collected = true;
		doublescore = true;


	}
	else if (playerX > 42.5 - 20 && playerX < 42.5 + 22 && playerY>35 - 27 && playerY < 35 + 17) {
		if (gcollected)
			return;
		gcollected = true;
		won = true;



	}

	glutPostRedisplay();
}


bool checkoverlap(double x, double y, int val) {
	if (x > 450 && x < 525 && y>42 && y < 118 ||
		x > 50 && x < 125 && y>342 && y < 418 ||
		x > 50 && x < 125 && y>192 && y < 268 ||
		x > 50 && x < 125 && y>42 && y < 118 ||
		x > 450 && x < 525 && y>342 && y < 418) {
		printf("M1");
		return true;
	}
	else if (x > c1x - 26 && x < c1x + 20 && y>c1y + -27 && y < c1y + 20) {
		printf("M2");
		if (val != 1)
			return true;
		else
			return false;

	}
	else if (x > c2x - 26 && x < c2x + 20 && y>c2y - 27 && y < c2y + 20)
	{
		printf("M3");
		if (val != 2)
			return true;
		else
			return false;
	}
	else if (x > c3x - 26 && x < c3x + 20 && y>c3y - 27 && y < c3y + 20)
	{
		printf("M4");
		if (val != 3)
			return true;
		else
			return false;
	}
	else if (x > c4x - 26 && x < c4x + 20 && y>c4y - 27 && y < c4y + 20)
	{
		printf("M5");
		if (val != 4)
			return true;
		else
			return false;
	}
	else if (x > c5x - 26 && x < c5x + 20 && y>c5y - 27 && y < c5y + 20) {
		printf("M6");
		if (val != 5)
			return true;
		else
			return false;
	}
	else if (x > p1x - 20 && x < p1x + 25 && y>p1y - 27 && y < p1y + 20) {
		printf("M7");
		if (val != 6)
			return true;
		else
			return false;
	}
	else if (x > p2x - 20 && x < p2x + 25 && y>p2y - 27 && y < p2y + 20) {
		printf("M8");
		if (val != 7)
			return true;
		else
			return false;

	}
	else if (x > 42.5 - 20 && x < 42.5 + 25 && y>35 - 27 && y < 35 + 20) {
		printf("M9");
		return true;


	}
	else if (x > 285 && x < 285 + 30 && y>247.5 && y < 247.5 + 30) {
		printf("center");
		return true;


	}

	else
	{
		printf("M10");
		return false;

	}
}

bool canmove(double x, double y, unsigned char k) {
	if (x > 460 && x < 515 && y>52 && y < 108 ||
		x > 60 && x < 115 && y>352 && y < 408 ||
		x > 60 && x < 115 && y>202 && y < 258 ||
		x > 60 && x < 115 && y>52 && y < 108 ||
		x > 460 && x < 515 && y>352 && y < 408) {


		if (lives > 0)
			lives = lives - 1;
		else
			lost = true;
		glutPostRedisplay();

		return false;


	}
	else if (playerX >= 540 && k == 'd' || k == 'a' && playerX <= 30 || k == 'w' && playerY >= 467 || k == 's' && playerY <= 27.5) {

		if (lives > 0)
			lives = lives - 1;
		else
			lost = true;
		return false;
	}

	else {

		return true;
	}
}

void key(unsigned char k, int x, int y)
{


	if (k == 'd' && playerX < 540 & canmove(playerX + 5, playerY, k)) {



		rot = -90;
		playerX += 5;

	}
	if (k == 'a' && playerX > 30 & canmove(playerX - 5, playerY, k)) {



		rot = 90;
		playerX -= 5;

	}
	if (k == 'w' && playerY < 467 & canmove(playerX, playerY + 5, k)) {


		rot = 0;
		playerY += 5;

	}
	if (k == 's' && playerY > 27.5 & canmove(playerX, playerY - 5, k)) {

		rot = 180;
		playerY -= 5;


	}


	collect();

	printf("%.0f %.0f %d %d\n", playerX, playerY, p1x, p1y);


	glutPostRedisplay();



}
void therand3() {
	std::random_device rd;
	std::mt19937 gen(rd());
	c1x = rand() % 500 + 25;
	c2x = rand() % 500 + 25;
	c3x = rand() % 500 + 25;
	c4x = rand() % 500 + 25;
	c5x = rand() % 500 + 25;
	c1y = rand() % 450 + 25;
	c2y = rand() % 450 + 25;
	c3y = rand() % 450 + 25;
	c4y = rand() % 450 + 25;
	c5y = rand() % 450 + 25;
	p1x = rand() % 500 + 25;
	p1y = rand() % 450 + 25;
	p2x = rand() % 500 + 25;
	p2y = rand() % 450 + 25;

	printf(" %.0f %.0f\n", c1x, c1y);
	glutPostRedisplay();
}
void therand2() {
	std::random_device rd;
	std::mt19937 gen(rd());
	c1x = rand() % 500 + 25;
	c2x = rand() % 500 + 25;
	c3x = rand() % 500 + 25;
	c4x = rand() % 500 + 25;
	c5x = rand() % 500 + 25;
	c1y = rand() % 450 + 25;
	c2y = rand() % 450 + 25;
	c3y = rand() % 450 + 25;
	c4y = rand() % 450 + 25;
	c5y = rand() % 450 + 25;
	p1x = rand() % 500 + 25;
	p1y = rand() % 450 + 25;
	p2x = rand() % 500 + 25;
	p2y = rand() % 450 + 25;

	if (checkoverlap(c1x, c1y, 1) ||
		checkoverlap(c2x, c2y, 2) ||
		checkoverlap(c3x, c3y, 3) ||
		checkoverlap(c4x, c4y, 4) ||
		checkoverlap(c5x, c5y, 5) ||
		checkoverlap(p1x, p1y, 6) ||
		checkoverlap(p2x, p2y, 7)) {

		printf(" %.0f %.0f\n", c1x, c1y);

		therand3();



	}
	glutPostRedisplay();
}

void therand() {


	srand((unsigned)time(0));
	c1x = rand() % 500 + 25;
	c2x = rand() % 500 + 25;
	c3x = rand() % 500 + 25;
	c4x = rand() % 500 + 25;
	c5x = rand() % 500 + 25;
	c1y = rand() % 450 + 25;
	c2y = rand() % 450 + 25;
	c3y = rand() % 450 + 25;
	c4y = rand() % 450 + 25;
	c5y = rand() % 450 + 25;
	p1x = rand() % 500 + 25;
	p1y = rand() % 450 + 25;
	p2x = rand() % 500 + 25;
	p2y = rand() % 450 + 25;

	if (checkoverlap(c1x, c1y, 1) ||
		checkoverlap(c2x, c2y, 2) ||
		checkoverlap(c3x, c3y, 3) ||
		checkoverlap(c4x, c4y, 4) ||
		checkoverlap(c5x, c5y, 5) ||
		checkoverlap(p1x, p1y, 6) ||
		checkoverlap(p2x, p2y, 7)) {

		printf(" %.0f %.0f\n", c1x, c1y);

		therand2();

	}




	glutPostRedisplay();
}



void healthbar() {
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex2f(50.0f, 580);
	glVertex2f(50.0f * (lives + 1), 580);
	glVertex2f(50.0f * (lives + 1), 550);
	glVertex2f(50.0f, 550);
	glEnd();
}
void Display() {
	glClear(GL_COLOR_BUFFER_BIT);




	if (animmove >= 600) {
		animmove = 0;
	}
	else
		animmove += 0.1;


	if (gcollected)
	{


		//gluOrtho2D(0.0, 100, 0.0, 100);
		glColor3ub(94, 139, 242);
		char* p0s5 = "you won";
		print(300, 300, (char*)p0s5);
	}

	if ((Time <= 0 || lives <= 0) && !gcollected) {
		glColor3ub(94, 139, 242);
		char* p0s6 = "you lost";
		print(300, 300, (char*)p0s6);
	}

	if (!won && !lost)
	{

		glPushMatrix();
		glTranslated(animmove, 530.0, 0);
		glColor3ub(214, 233, 255);
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(15, 0);
		glVertex2f(15, 15);
		glVertex2f(0, 15);
		glEnd();
		glPopMatrix();

		glColor3ub(94, 139, 242);
		char* p0s[20];
		sprintf((char*)p0s, "Score: %d", score);
		print(350, 560, (char*)p0s);
		rotanim += 0.1;

		glColor3ub(94, 139, 242);
		char* p0s3[20];
		sprintf((char*)p0s3, "Timer: %d", Time);
		print(500, 560, (char*)p0s3);

		drawboundries();
		drawplayer();
		drawobstacles();
		drawcollects();
		drawgoal();
		drawpower1();
		drawpower2();
		healthbar();
	}
	glutPostRedisplay();
	glFlush();
}

void main(int argc, char** argr) {
	glutInit(&argc, argr);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 50);
	glutCreateWindow("Lab 01");
	therand();
	glutDisplayFunc(Display);
	glutTimerFunc(1000, thetime, 0);
	glutTimerFunc(1000, Timerp1, 0);
	glutKeyboardFunc(key);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	gluOrtho2D(0.0, 600.0, 0.0, 600.0);
	glutMainLoop();
}



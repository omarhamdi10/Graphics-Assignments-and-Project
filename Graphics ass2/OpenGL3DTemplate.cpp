#include <iostream>
#include <cmath>
#include <cstdlib>  // Include the cstdlib library for rand function
#include <glut.h>

double playerX = 285;
double playerY = 247.5;
int rot = 0;
double goalX = 52.5;
double goalY = 42;
double playerDirection = 0.0;
double rotanim = 0;
int Time = 250;
bool timestop = false;
bool gcollected = false;
bool doublescore = false;
bool lost = false;
bool won = false;
bool rotateObjects = false;
bool gameOver = false; // this variable to track game over state
char timeStr[50];


GLfloat wallColor1[3] = { 1.0, 1.0, 1.0 };  // Initialize wall color 1 to white
GLfloat wallColor2[3] = { 1.0, 1.0, 1.0 };  // Initialize wall color 2 to white
GLfloat wallColor3[3] = { 1.0, 1.0, 1.0 };  // Initialize wall color 3 to white

void print(int x, int y, char* string) {
    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(string);

    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}
void thetime(int val) {
    // Check if time is up and set 'lost' flag
    if (Time <= 0 && !gcollected)
        lost = true;

    // If time is not stopped and time is greater than 0, decrement time
    if (!timestop && Time > 0) {
        Time--;
        glutPostRedisplay();
        glutTimerFunc(1000, thetime, 0);
    }
    else {
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
void drawPlayer() {
    glPushMatrix();
    glTranslated(playerX, playerY, 0);
    glRotated(playerDirection, 0, 0, 1);

    // Head (Square)
    glColor3ub(255, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(-5, 15);
    glVertex2f(5, 15);
    glVertex2f(5, 5);
    glVertex2f(-5, 5);
    glEnd();

    // Body
    glColor3ub(0, 255, 0);
    glBegin(GL_QUADS);
    glVertex2f(-5, -30);
    glVertex2f(5, -30);
    glVertex2f(5, 0);
    glVertex2f(-5, 0);
    glEnd();

    // Left Leg
    glColor3ub(0, 0, 255);
    glBegin(GL_LINES);
    glVertex2f(0, -30);
    glVertex2f(-10, -40);
    glEnd();

    // Right Leg
    glBegin(GL_LINES);
    glVertex2f(0, -30);
    glVertex2f(10, -40);
    glEnd();

    // Left Arm
    glBegin(GL_LINES);
    glVertex2f(0, -10);
    glVertex2f(-10, -20);
    glEnd();

    // Right Arm
    glBegin(GL_LINES);
    glVertex2f(0, -10);
    glVertex2f(10, -20);
    glEnd();

    glColor3ub(0, 0, 0); // Set text color to black
    char timeStr[50];
    sprintf(timeStr, "Time: %d", Time); // Convert time to string
    print(10, 580, timeStr);

    // Display the time at the top of the screen
    glColor3ub(0, 0, 0); // Set text color to black

    sprintf(timeStr, "Time: %d", Time); // Convert time to string
    print(10, 580, timeStr);

    glPopMatrix();
}

void drawBoundaries() {
    // Boundary 1
    glPushMatrix();
    glColor3fv(wallColor1);
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

    // Boundary 2
    glPushMatrix();
    glColor3fv(wallColor2);
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

    // Boundary 3
    glPushMatrix();
    glColor3fv(wallColor3);
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
}

bool canmove(double x, double y) {
    // Check if the player's head is inside the goal
    if (x > goalX - 10 && x < goalX + 10 && y > goalY && y < goalY + 10) {
        gcollected = true;
        return true;


    }

    // Check if the player's body is inside the goal
    if (x > goalX - 10 && x < goalX + 10 && y > goalY - 30 && y < goalY + 10) {
        gcollected = true;
        return true;


    }

    // Check if the player's legs are inside the goal
    if ((x > goalX - 10 && x < goalX + 10 && y > goalY - 40 && y < goalY - 30) ||
        (x > goalX - 10 && x < goalX + 10 && y > goalY && y < goalY + 10)) {
        gcollected = true;
        return true;


    }

    // Check if the player's hands are inside the goal
    if ((x > goalX - 10 && x < goalX + 10 && y > goalY - 20 && y < goalY - 10) ||
        (x > goalX - 10 && x < goalX + 10 && y > goalY - 20 && y < goalY - 10)) {
        gcollected = true;
        return true;


    }


    if (x < 0 || x > 600 || y < 0 || y > 600) {
        return false;
    }


    if ((x > 25 && x < 500 && y > 25 && y < 400) ||
        (x > 0 && x < 575 && y > 25 && y < 400) ||
        (x > 0 && x < 25 && y > 0 && y < 400)) {
        return true;
    }


    return false;
}

void key(unsigned char k, int x, int y) {
    if (gameOver) {
        return;
    }

    double newX = playerX;
    double newY = playerY;

    if (k == 'd') {
        newX += 5;
        playerDirection = 270.0;
    }
    else if (k == 'a') {
        newX -= 5;
        playerDirection = 90.0;
    }
    else if (k == 'w') {
        newY += 5;
        playerDirection = 0.0;
    }
    else if (k == 's') {
        newY -= 5;
        playerDirection = 180.0;
    }
    else if (k == 'r') {
        rotateObjects = true; // Start rotation when 'R' key is pressed
    }
    else if (k == 't') {
        rotateObjects = false; // Stop rotation when 'T' key is pressed
    }

    if (canmove(newX, newY)) {
        playerX = newX;
        playerY = newY;
        glutPostRedisplay();
    }
}

void drawGround() {
    glPushMatrix();
    glColor3ub(0, 255, 0);
    glBegin(GL_LINES);
    glVertex2f(575.0f, 25.0f);
    glVertex2f(0.0f, 25.0f);
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

        glColor3f(1.0f, 0.0f, 0.0f);

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

void drawCar() {
    glPushMatrix();
    glTranslated(100, 50, 0);
    glScaled(0.5, 0.5, 1.0);
    if (rotateObjects) {
        glRotated(rot, 0, 0, 1);
    }
    glColor3ub(255, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(250, 50);
    glVertex2f(350, 50);
    glVertex2f(350, 100);
    glVertex2f(250, 100);
    glEnd();

    glColor3ub(0, 0, 255);
    glBegin(GL_TRIANGLES);
    glVertex2f(250, 100);
    glVertex2f(350, 100);
    glVertex2f(300, 150);
    glEnd();

    glColor3ub(0, 0, 0);
    const float leftWheelX = 270;
    const float leftWheelY = 45;
    const float leftWheelRadius = 10;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(leftWheelX, leftWheelY);
    for (int i = 0; i <= 360; ++i) {
        float angle = i * 3.1415926 / 180.0;
        glVertex2f(leftWheelX + leftWheelRadius * cos(angle), leftWheelY + leftWheelRadius * sin(angle));
    }
    glEnd();

    const float rightWheelX = 330;
    const float rightWheelY = 45;
    const float rightWheelRadius = 10;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(rightWheelX, rightWheelY);
    for (int i = 0; i <= 360; ++i) {
        float angle = i * 3.1415926 / 180.0;
        glVertex2f(rightWheelX + rightWheelRadius * cos(angle), rightWheelY + rightWheelRadius * sin(angle));
    }
    glEnd();

    glColor3ub(255, 255, 0);
    glBegin(GL_POLYGON);
    glVertex2f(265, 100);
    glVertex2f(285, 100);
    glVertex2f(285, 120);
    glVertex2f(265, 120);
    glEnd();
    glPopMatrix();
}

void drawTree() {
    glPushMatrix();
    glTranslated(250, 50, 0);
    glScaled(0.5, 0.5, 1.0);
    if (rotateObjects) {
        glRotated(rot, 0, 0, 1);
    }
    glColor3ub(139, 69, 19);
    glBegin(GL_QUADS);
    glVertex2f(450, 50);
    glVertex2f(470, 50);
    glVertex2f(470, 150);
    glVertex2f(450, 150);
    glEnd();

    glColor3ub(34, 139, 34);
    const float treeTopX = 460;
    const float treeTopY = 150;
    const float treeTopRadius = 30;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(treeTopX, treeTopY);
    for (int i = 0; i <= 360; ++i) {
        float angle = i * 3.1415926 / 180.0;
        glVertex2f(treeTopX + treeTopRadius * cos(angle), treeTopY + treeTopRadius * sin(angle));
    }
    glEnd();

    glColor3ub(139, 69, 19);
    glBegin(GL_LINES);
    glVertex2f(460, 150);
    glVertex2f(430, 170);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(460, 150);
    glVertex2f(490, 170);
    glEnd();

    glColor3ub(139, 69, 19);
    glBegin(GL_TRIANGLES);
    glVertex2f(450, 50);
    glVertex2f(470, 50);
    glVertex2f(460, 30);

    glVertex2f(470, 50);
    glVertex2f(450, 50);
    glVertex2f(460, 30);
    glEnd();
    glPopMatrix();
}

void drawSeeSaw() {
    glPushMatrix();
    // Adjust the position of the seesaw between the tree and the car
    glTranslated(200, 50, 0);
    glScaled(0.5, 0.5, 1.0);  // Scale the seesaw to half its original size
    if (rotateObjects) {
        glRotated(rot, 0, 0, 1);
    }
    // Base
    glColor3ub(139, 69, 19);
    glBegin(GL_QUADS);
    glVertex2f(200, 25);
    glVertex2f(400, 25);
    glVertex2f(400, 30);
    glVertex2f(200, 30);
    glEnd();

    // Left Support
    glColor3ub(139, 69, 19);
    glBegin(GL_TRIANGLES);
    glVertex2f(200, 30);
    glVertex2f(190, 100);
    glVertex2f(210, 100);
    glEnd();

    // Right Support
    glColor3ub(139, 69, 19);
    glBegin(GL_TRIANGLES);
    glVertex2f(400, 30);
    glVertex2f(390, 100);
    glVertex2f(410, 100);
    glEnd();

    glPopMatrix();
}
void drawBench() {
    glPushMatrix();
    // Adjust the position of the bench
    glTranslated(180, 70, 0);
    glScaled(0.8, 0.8, 1.0);  // Scale the bench to adjust its size
    if (rotateObjects) {
        glRotated(rot, 0, 0, 1);
    }
    // Horizontal seat
    glColor3ub(139, 69, 19);
    glBegin(GL_QUADS);
    glVertex2f(-30, 0);
    glVertex2f(30, 0);
    glVertex2f(30, 10);
    glVertex2f(-30, 10);
    glEnd();

    // Left vertical support
    glColor3ub(139, 69, 19);
    glBegin(GL_QUADS);
    glVertex2f(-30, 0);
    glVertex2f(-25, 0);
    glVertex2f(-25, 20);
    glVertex2f(-30, 20);
    glEnd();

    // Right vertical support
    glColor3ub(139, 69, 19);
    glBegin(GL_QUADS);
    glVertex2f(25, 0);
    glVertex2f(30, 0);
    glVertex2f(30, 20);
    glVertex2f(25, 20);
    glEnd();



    glPopMatrix();
}
void drawTrashbin() {
    glPushMatrix();
    // Adjust the position of the trash bin
    glTranslated(550, 80, 0);
    glScaled(0.8, 0.8, 1.0);  // Scale the trash bin to adjust its size
    if (rotateObjects) {
        glRotated(rot, 0, 0, 1);
    }
    // Body of the trash bin
    glColor3ub(128, 128, 128);
    glBegin(GL_QUADS);
    glVertex2f(-20, 0);
    glVertex2f(20, 0);
    glVertex2f(20, 50);
    glVertex2f(-20, 50);
    glEnd();

    // Lid of the trash bin
    glColor3ub(128, 128, 128);
    glBegin(GL_QUADS);
    glVertex2f(-25, 50);
    glVertex2f(25, 50);
    glVertex2f(20, 60);
    glVertex2f(-20, 60);
    glEnd();

    // Trash bin label
    glColor3ub(255, 255, 255);
    char labelStr[] = "Trash";
    print(-15, 30, labelStr);

    // Cylindrical legs of the trash bin
    glColor3ub(128, 128, 128);
    const float legRadius = 5;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-15, 0);
    for (int i = 0; i <= 360; ++i) {
        float angle = i * 3.1415926 / 180.0;
        glVertex2f(-15 + legRadius * cos(angle), legRadius * sin(angle));
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(15, 0);
    for (int i = 0; i <= 360; ++i) {
        float angle = i * 3.1415926 / 180.0;
        glVertex2f(15 + legRadius * cos(angle), legRadius * sin(angle));
    }
    glEnd();

    glPopMatrix();
}




void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (!won && !lost)
    {

        glColor3ub(94, 139, 242);
        char* p0s3[20];
        sprintf((char*)p0s3, "Timer: %d", Time);
        print(500, 560, (char*)p0s3);

        drawBoundaries();
        drawGround();
        drawPlayer();
        drawgoal();
        drawCar();
        drawTree();
        drawSeeSaw();
        drawBench();
        drawTrashbin();
        if (gcollected) {
            glColor3ub(0, 255, 0); // Set text color to green
            print(250, 300, "You Won!");
            gameOver = true;
        }


    }


    // Display the "You Lost" message if the 'lost' flag is true
    if (lost) {
        glColor3ub(255, 0, 0); // Set text color to red
        print(250, 300, "You Lost!");
        gameOver = true;
    }

    glutSwapBuffers();
}


//bta3 el boundaries
void timer(int value) {
    // Change wall colors at regular intervals
    wallColor1[0] = static_cast<GLfloat>(rand() % 256) / 255.0;
    wallColor1[1] = static_cast<GLfloat>(rand() % 256) / 255.0;
    wallColor1[2] = static_cast<GLfloat>(rand() % 256) / 255.0;

    wallColor2[0] = static_cast<GLfloat>(rand() % 256) / 255.0;
    wallColor2[1] = static_cast<GLfloat>(rand() % 256) / 255.0;
    wallColor2[2] = static_cast<GLfloat>(rand() % 256) / 255.0;

    wallColor3[0] = static_cast<GLfloat>(rand() % 256) / 255.0;
    wallColor3[1] = static_cast<GLfloat>(rand() % 256) / 255.0;
    wallColor3[2] = static_cast<GLfloat>(rand() % 256) / 255.0;

    glutPostRedisplay(); // Redraw the scene

    // Set the timer function to be called again after 5000 milliseconds (5 seconds)
    glutTimerFunc(5000, timer, 0);
}



void anim() {
    rot += 1;
    if (rot > 360) {
        rot -= 360;
    }

    rotanim += 1;
    if (rotanim > 360) {
        rotanim -= 360;
    }





    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Player and Boundaries");
    glutDisplayFunc(display);
    glutIdleFunc(anim);
    glutTimerFunc(Time, timer, 0); // Set up the timer function

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutKeyboardFunc(key);
    glutTimerFunc(1000, thetime, 0); // Set up the timer function to decrement time every second
    glutTimerFunc(5000, timer, 0);  // Set up the timer function for color change every 5 seconds

    glutMainLoop();
    return 0;
}

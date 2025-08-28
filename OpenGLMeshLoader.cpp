#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <cmath>
#include <glut.h>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <playsoundapi.h>
#include <mutex>
#include <queue>
#include <algorithm> // Add this include for std::max

#define DEG2RAD(a) (a * 0.0174532925)

std::queue<std::wstring> soundQueue;
std::mutex queueMutex;

int WIDTH = 1280;
int HEIGHT = 720;
bool waitingToReset = false;
time_t resetStartTime;

GLuint tex;
char title[] = "3D Model Loader Sample";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 100;


float varX = 0;
bool flag = false;
// Player
float PlayerX = 0.0f;
float PlayerY = 0.0f;
float PlayerZ = -14.0f;
float movementSpeed = 0.1f;  // Adjust the speed as needed
float playerRadius = 1.0f;  // Adjust the player's collision radius as needed

//Keeper
float KeeperX = -1.0f;
float KeeperY = 0.0f;
float KeeperZ = -12.0f;

//Defender
float defenderX = 4.0f;
float defenderY = 0.0f;
float defenderZ = 0.0f;

// Ball
float ballX = 0.0f;
float ballY = 0.0f;
float ballZ = 5.0f;
bool isShooting = false;
float ballSpeed = 0.5f;



bool firstPerson;




float skycolor2 = 1;

//Sun
float sunPositionX = 0;
float sunPositionY = 10;
float sunPositionZ = 0;
float translationSpeed = 0.06f;
float sunIntensity = 1.0f;  // Initial intensity of the sun

// Player 2
float Player2X = 0.0f;
float Player2Y = 0.0f;
float Player2Z = -14.0f;

// Cone
float coneX = 4.0f;
float coneY = 0.0f;
float coneZ = 0.0f;

// Ball 2
float ball2X = 0.0f;
float ball2Y = 0.0f;
float ball2Z = 5.0f;
float ball2Speed = 0.5f;


// Can
float canX = 17.0f;
float canY = 0.0f;
float canZ = 0.0f;


// Keeper 2
float Keeper2X = -1.0f;
float Keeper2Y = 0.0f;
float Keeper2Z = -12.0f;

// Collectible 2
float colX = 10.0;
float colY = 0.0;
float colZ = 0.0;
bool p2collected = false;


// Score
int score = 0;

float x = 10;
float y = 0;
float z = 0;


float skycolor = 0;

// counter
int counter = 80;  // Set an initial timer value in seconds

//collectibe1
double p1x = 5.0;
double p1y = 3.0;
bool p1collected = false;
bool pcollected = false;

bool secondEnvironmentActive = false;

bool scoreIncrease = false;

// Method Dec
void timer();
float calculateDistance(float x1, float y1, float x2, float y2);
void LoadAssets2();
void myDisplay2();



class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(20, 5, 20);
Vector At(0, 0, 0);
Vector Up(0, 1, 0);

class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};




int cameraZoom = 0;

// Model Variables Env 1
Model_3DS model_ball;
Model_3DS model_player;
Model_3DS model_defender;
Model_3DS model_net;
Model_3DS model_sun;

// Model Variables Env 2
Model_3DS model_cone;
Model_3DS model_player2;
Model_3DS model_ball2;
Model_3DS model_can;
Model_3DS model_keeper2;

// Textures
GLTexture tex_ground;


void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);


}

void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

void handleKeyRelease(unsigned char key, int x, int y) {
	switch (key) {

	case 'g':
		// Press 'g' to start shooting
		isShooting = true;
		break;
		// Add more cases for other keys if needed
	}
}

void drawText(const char* text, float x, float y) {
	glColor3f(1.0f, 1.0f, 1.0f);  // Set text color to white
	glRasterPos2f(x, y);  // Set text position

	for (int i = 0; text[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}
}

void drawScoreAndTimer() {
	// Score display 
	char scoreText[20];
	sprintf(scoreText, "Score: %d", score);  // Format the score as a string
	drawText(scoreText, 10.0f, 9.0f);  // Adjust position as needed

	// Timer display
	//char timerText[20];
	//sprintf(timerText, "Timer: %d", counter);  // Format the timer as a string
	//drawText(timerText, 12.0f, 9.0f);  // Adjust position as needed
}

void timer(int value) {
	if (counter > 0) {
		//counter--;
		glutPostRedisplay();

		glutTimerFunc(20, timer, 0);
		skycolor += 0.01;
		varX += 0.02;
		if (varX > 4.9) {
			varX = 0;
			skycolor *= -1;
		}


	}
	else {
		exit(0);
	}  // Set the interval to 1000 milliseconds (1 second)
}

float calculateDistance(float x1, float y1, float x2, float y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool canMove(float newX, float newZ) {
	// Define the ground boundaries
	float minX = -19.5f;
	float maxX = 19.5f;
	float minZ = -19.5f;  // Change minY to minZ
	float maxZ = 19.5f;   // Change maxY to maxZ

	// Check if the new position is within the boundaries
	return (newX >= minX && newX <= maxX && newZ >= minZ && newZ <= maxZ && newX != -defenderX  && newZ != defenderZ);
}

void movePlayer2(unsigned char key, int x, int y) {
	float& currentPlayerX = (key == 'o' || key == 'p') ? Keeper2X : Player2X;
	float& currentPlayerY = (key == 'o' || key == 'p') ? Keeper2Y : Player2Y;
	float& currentPlayerZ = (key == 'o' || key == 'p') ? Keeper2Z : Player2Z;

	float newPlayerX = currentPlayerX;
	float newPlayerY = currentPlayerY;
	float newPlayerZ = currentPlayerZ;
	//std::cout << Player2X << " " << Player2Y << " " << Player2Z << std::endl;


	switch (key) {
	case 'o':
		newPlayerX -= movementSpeed;  // Move left for keeper
		break;
	case 'p':
		newPlayerX += movementSpeed;  // Move right for keeper
		break;
	case 'a':
		newPlayerX += movementSpeed;  // Move left for player
		break;
	case 'd':
		newPlayerX -= movementSpeed;  // Move right for player
		break;
	case 's':
		newPlayerZ -= movementSpeed;  // Move backward for both
		break;
	case 'w':
		newPlayerZ += movementSpeed;  // Move forward for both
		break;
		// Add more cases for other keys if needed
	case 'k':
		firstPerson = true;  // Move forward for both
		break;
	case 'l':
		firstPerson = false;  // Move forward for both
		break;

	}

	//std::cout << currentPlayerX << " " << currentPlayerY << " " << currentPlayerZ << std::endl;

	// Check if the new position is within the boundaries before updating
	if (canMove(newPlayerX, newPlayerY)) {
		if (currentPlayerZ == -5.3f && key != 'o' && key != 'p')
			return;

		currentPlayerX = newPlayerX;
		currentPlayerY = newPlayerY;
		currentPlayerZ = newPlayerZ;
	}

	glutPostRedisplay();  // Trigger a redisplay to update the rendered scene
}

void movePlayer(unsigned char key, int x, int y) {
	float& currentPlayerX = (key == 'o' || key == 'p') ? KeeperX : PlayerX;
	float& currentPlayerY = (key == 'o' || key == 'p') ? KeeperY : PlayerY;
	float& currentPlayerZ = (key == 'o' || key == 'p') ? KeeperZ : PlayerZ;

	float newPlayerX = currentPlayerX;
	float newPlayerY = currentPlayerY;
	float newPlayerZ = currentPlayerZ;

	switch (key) {
	case 'o':
		newPlayerX -= movementSpeed;// Move left for keeper
		break;
	case 'p':
		newPlayerX += movementSpeed;  // Move right for keeper
		break;
	case 'a':
		newPlayerX += movementSpeed;  // Move left for player
		break;
	case 'd':
		newPlayerX -= movementSpeed;  // Move right for player
		break;
	case 's':
		newPlayerZ -= movementSpeed;  // Move backward for both
		break;
	case 'w':
		newPlayerZ += movementSpeed;  // Move forward for both
		break;
		// Add more cases for other keys if needed
	}

	//std::cout << currentPlayerX << " " << currentPlayerY << " " << currentPlayerZ << std::endl;

	// Check if the new position is within the boundaries before updating
	if (canMove(newPlayerX, newPlayerZ)) {
		if (currentPlayerZ == -5.3f && key != 'o' && key != 'p')
			return;

		currentPlayerX = newPlayerX;
		currentPlayerY = newPlayerY;
		currentPlayerZ = newPlayerZ;
	}

	glutPostRedisplay();  // Trigger a redisplay to update the rendered scene
}

void drawpower1() {

	if (PlayerZ >= -10.0f && PlayerX == 0) {
		movementSpeed = 0.4;
		x = 100;
		y = 100;
		z = 100;
		pcollected = true;

		//PlaySound(TEXT("Sound/collect.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}

	if (!p1collected) {
		glPushMatrix();

		// Specify the fixed position for the powerup
		glTranslated(x, y, z);

		// Apply scaling to make the power smaller
		glScalef(1.0f, 1.0f, 1.0f);

		// Apply rotation if needed
		// glRotatef(angle, 0.0f, 1.0f, 0.0f);  // Uncomment and set angle as needed

		// Draw a cube
		glutSolidCube(1.0);

		glPopMatrix();
	}
}

void drawpower2() {

	if (Player2Z >= -10.0f && Player2X == 0) {
		movementSpeed = 0.4;
		colX = 100;
		colY = 100;
		colZ = 100;
		p2collected = true;
		ball2Speed += 1;

		//PlaySound(TEXT("Sound/collect.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}

	if (!p2collected) {

		glPushMatrix();

		// Specify the fixed position for the powerup
		glTranslated(colX, colY, colZ);

		// Apply scaling to make the power smaller
		glScalef(1.0f, 1.0f, 1.0f);

		// Apply rotation if needed
		// glRotatef(angle, 0.0f, 1.0f, 0.0f);  // Uncomment and set angle as needed

		glColor3f(0, 0, 1);
		// Draw a triangular pyramid
		glBegin(GL_TRIANGLES);
		// Base
		glVertex3f(-0.5, 0, -0.5);
		glVertex3f(0.5, 0, -0.5);
		glVertex3f(0, 0, 0.5);
		// Front face
		glVertex3f(0, 0, 0.5);
		glVertex3f(0.5, 0, -0.5);
		glVertex3f(0, 1, 0);
		// Right face
		glVertex3f(0, 0, 0.5);
		glVertex3f(0, 0, -0.5);
		glVertex3f(0.5, 0, -0.5);
		// Left face
		glVertex3f(0, 0, 0.5);
		glVertex3f(-0.5, 0, -0.5);
		glVertex3f(0, 0, -0.5);
		glEnd();

		glPopMatrix();
	}
}

void LoadAssets2() {

	model_player2.Load("Models/player/Man footballer Messi N241113.3DS");
	model_cone.Load("Models/Cone2/Traffic_cone N031209.3DS");
	model_ball2.Load("Models/Ball2/Ball Jabulani N230523.3ds");
	model_can.Load("Models/Can/Sprite N250418.3ds");
	model_keeper2.Load("Models/player/Man footballer Messi N241113.3DS");

	tex_ground.Load("textures/istockphoto-155441905-612x612.bmp");
	loadBMP(&tex, "textures/sky2.bmp", true);
}




void checkGoalCollision() {
	// Assuming the keeper is at a certain position (adjust as needed)
	if (PlayerZ >= -5.3f && PlayerX == 0) {
		if (ballX < 2.9) {

			ballX += 0.1;
			ballZ -= 1;
			ballY += 0.1;
		}
		else if (ballY >= -0.7) {
			ballY -= 0.2;
		}
		else
		{
			ballX = 0;
			ballY = 0;
			ballZ = 5;
			PlayerZ = -14;
		}
		if (ballY < 0.75 && ballY>0.7)
		{
			score++;
			//PlaySound(TEXT("Sound/Goal.wav"), NULL, SND_FILENAME | SND_ASYNC);

		}

		if (score > 3 && !secondEnvironmentActive) {
			secondEnvironmentActive = true;

			// Open a new window with new models
			glutCreateWindow("Second Window");
			// Initialize the new window
			myInit();
			LoadAssets2();
			// Set the display function for the second window
			glutDisplayFunc(myDisplay2);
			glutKeyboardFunc(movePlayer2);
			score = 0;
		}

	}
}

void checkGoalCollision2() {
	// Assuming the keeper is at a certain position (adjust as needed)

	if (Player2Z >= -5.3f && Player2X == 0) {
		std::cout << ball2X << " " << ball2Y << " " << ball2Z << std::endl;

		if (ball2X < 2.9) {

			ball2X += 0.1;
			ball2Z -= 1;
			//ball2Y += 0.1;
		}
		else if (ball2Z <= -24) {
			//std::cout << x << " " << currentPlayerY << " " << currentPlayerZ << std::endl;

			if (PlayerZ >= -5.3f && PlayerX == 0) {

				score++;
				PlaySound(TEXT("Sound/Goal.wav"), NULL, SND_FILENAME | SND_ASYNC);

			}
			canY = 197;

			ball2X = 0;
			ball2Y = 0;
			ball2Z = 5;
			Player2Z = -14;
			flag = true;

		}

	}
	else canY = 0;
}



void firstEnvModels(void) {
	
	if (isShooting) {
		// Update ball position in the shooting direction
		ballZ -= 30 * ballSpeed; // You may need to adjust the speed
	}

	checkGoalCollision();

	// Ball
	glPushMatrix();
	glRotatef(90.f, 0, 1, 0);
	glTranslatef(ballX, ballY, ballZ);
	glScalef(0.02, 0.02, 0.02);
	// Rotate 90 degrees around the x-axis
	//glScalef(0.2f, 0.2f, 0.2f);  // Scale down by a factor of 0.5 in all three dimensions
	model_ball.Draw();
	glPopMatrix();

	// Net
	glPushMatrix();
	glRotatef(180.f, 0, 1, 0);
	glTranslatef(17, 2, 0);
	glScalef(0.2f, 0.2f, 0.2f);  // Scale down by a factor of 0.5 in all three dimensions
	model_net.Draw();
	glPopMatrix();

	//Player
	glPushMatrix();
	glRotatef(270.f, 0, 1, 0);
	glTranslatef(PlayerX, PlayerY, PlayerZ);
	glScalef(0.05f, 0.05f, 0.05f);
	//glScalef(playerRadius, playerRadius, playerRadius);
	model_defender.Draw();
	glPopMatrix();

	//Keeper
	glPushMatrix();
	glRotatef(90.f, 0, 1, 0);
	glTranslatef(KeeperX, KeeperY, KeeperZ);
	glScalef(0.05f, 0.05f, 0.05f);
	//glScalef(playerRadius, playerRadius, playerRadius);
	model_defender.Draw();
	glPopMatrix();

	//defender
	glPushMatrix();
	glRotatef(90.f, 0, 1, 0);
	glTranslatef(defenderX, defenderY, defenderZ);
	glScalef(0.05f, 0.05f, 0.05f);
	//glScalef(playerRadius, playerRadius, playerRadius);
	model_defender.Draw();
	glPopMatrix();


	


	//Sun
	glPushMatrix();
	glRotatef(180.f, 0, 1, 0);
	glTranslatef(sunPositionX, sunPositionY, sunPositionZ);
	glScalef(0.003f, 0.003f, 0.003f);
	// Set the sun color with intensity
	glColor3f(1 * sunIntensity, 1 * sunIntensity, sunIntensity);
	model_sun.Draw();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 1);
	drawpower1();
	glPopMatrix();
}

float calculateSunIntensity() {
	// Implement your own logic to calculate intensity based on time or other factors
	// Example: return a value between 0.0 and 1.0 based on time
	return 0.5f + 0.5f * sin(glutGet(GLUT_ELAPSED_TIME) * 0.001f);

}

void updateSun(int value) {
	// Update the sun's position in the x-direction
	sunPositionX += translationSpeed;
	
	// Reverse direction if the sun reaches the screen edge
	if (sunPositionX >= 5.0f || sunPositionX <= -5.0f) {
		translationSpeed *= -1;
	}

	sunIntensity = calculateSunIntensity();  // Implement your own function
	if (sunIntensity < 0)
	{
		sunIntensity = -1;
	}

	// Call the display function to redraw the scene
	glutPostRedisplay();

	// Set the next update
	glutTimerFunc(16, updateSun, 0);  // Assuming 60 frames per second
}

void secondEnvModels(void) {

	checkGoalCollision2();


	glPushMatrix();
	glRotatef(180.f, 0, 1, 0);
	glTranslatef(coneX, coneY, coneZ);
	glScalef(0.004f, 0.004f, 0.004f);  // Scale down by a factor of 0.5 in all three dimensions
	model_cone.Draw();
	glPopMatrix();

	glPushMatrix();
	glRotatef(270.f, 0, 1, 0);
	glTranslatef(Player2X, Player2Y, Player2Z);
	glScalef(0.05f, 0.05f, 0.05f);
	//glScalef(playerRadius, playerRadius, playerRadius);
	model_player2.Draw();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.f, 0, 1, 0);
	glTranslatef(ball2X, ball2Y, ball2Z);
	glScalef(0.02, 0.02, 0.02);
	// Rotate 90 degrees around the x-axis
	//glScalef(0.2f, 0.2f, 0.2f);  // Scale down by a factor of 0.5 in all three dimensions
	model_ball2.Draw();
	glPopMatrix();

	

	glPushMatrix();
	glRotatef(90.f, 0, 1, 0);
	glTranslatef(Keeper2X, Keeper2Y, Keeper2Z);
	glScalef(0.05f, 0.05f, 0.05f);
	//glScalef(playerRadius, playerRadius, playerRadius);
	model_keeper2.Draw();
	glPopMatrix();

	

	glPushMatrix();
	glColor3f(100, 0, 12);
	drawpower2();
	glPopMatrix();
}

void myDisplay2(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up the view for the second environment
	// Adjust the view parameters as needed
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, aspectRatio, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);

	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	// Draw Ground
	RenderGround();

	// Draw models for the second environment
	secondEnvModels();

	// Draw Score and Timer
	glPushMatrix();
	glPushMatrix();
	glRotatef(180.f, 0, 1, 0);
	glTranslatef(canX, canY, canZ);
	glScalef(0.006f, 0.01f, 0.006f);  // Scale down by a factor of 0.5 in all three dimensions
	model_can.Draw();
	glPopMatrix();
	drawScoreAndTimer();

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 100, 100, 100);
	gluDeleteQuadric(qobj);

	glPopMatrix();

	// Swap buffers
	glutSwapBuffers();
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	// Draw Ground
	RenderGround();

	// Draw Tree Model
	/*glPushMatrix();
	glTranslatef(10, 0, 0);
	glScalef(0.7, 0.7, 0.7);
	model_tree.Draw();
	glPopMatrix();*/

	// Draw house Model
	/*glPushMatrix();
	glRotatef(90.f, 1, 0, 0);
	model_house.Draw();
	glPopMatrix();*/

	firstEnvModels();

	//secondEnvModels();

	drawScoreAndTimer();

	

	//sky box
	glPushMatrix();
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();

	glColor3f(1 - skycolor, 1 - skycolor, 1 - skycolor);
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 100, 100, 100);
	gluDeleteQuadric(qobj);

	glPopMatrix();

	glutSwapBuffers();
}

void myKeyboard(unsigned char button, int x, int y)
{
	switch (button)
	{
	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'r':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else
	{
		Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}

void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}

void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

void LoadAssets()
{
	// Loading Model files
	model_defender.Load("Models/player/Man footballer Messi N241113.3DS");
	model_net.Load("Models/net/Gates  N140608.3ds");
	model_sun.Load("Models/sun2/Mirror sun N261217.3DS");
	model_ball.Load("Models/Ball2/Ball Jabulani N230523.3ds");
	

	//model_tree.Load("Models/tree/Tree1.3ds");

	// Loading texture files
	tex_ground.Load("Textures/ground.bmp");
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);


}


void main(int argc, char** argv)
{
	if (!secondEnvironmentActive) {
		glutInit(&argc, argv);

		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

		glutInitWindowSize(WIDTH, HEIGHT);

		glutInitWindowPosition(100, 150);

		glutCreateWindow("Score Heroo");

		glutDisplayFunc(myDisplay);
		//glutDisplayFunc(myDisplay2);
		//glutKeyboardFunc(movePlayer2);

		//glutKeyboardFunc(myKeyboard);

		glutKeyboardFunc(movePlayer);
		//glutKeyboardUpFunc(handleKeyRelease);


		glutMotionFunc(myMotion);

		//glutMouseFunc(myMouse);


		glutReshapeFunc(myReshape);

		myInit();

		LoadAssets();
		//LoadAssets2();

		PlaySound(TEXT("Sound/Whistle1.wav"), NULL, SND_FILENAME | SND_ASYNC);

		glutTimerFunc(25, updateSun, 0);  // Set up the timer for the update function

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);

		glShadeModel(GL_SMOOTH);

		glutTimerFunc(16, timer, 0); // Adjust the timer interval as needed

		glutMainLoop();
	}
	//else {
	//	exit(0);

	//	glutInit(&argc, argv);

	//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	//	glutInitWindowSize(WIDTH, HEIGHT);

	//	glutInitWindowPosition(100, 150);

	//	glutCreateWindow("Score Heroo");

	//	//glutDisplayFunc(myDisplay);
	//	glutDisplayFunc(myDisplay2);
	//	glutKeyboardFunc(movePlayer2);

	//	//glutKeyboardFunc(myKeyboard);

	//	//glutKeyboardFunc(movePlayer);
	//	//glutKeyboardUpFunc(handleKeyRelease);


	//	glutMotionFunc(myMotion);

	//	//glutMouseFunc(myMouse);


	//	glutReshapeFunc(myReshape);

	//	myInit();

	//	//LoadAssets();
	//	LoadAssets2();

	//	PlaySound(TEXT("Sound/Whistle1.wav"), NULL, SND_FILENAME | SND_ASYNC);

	//	glutTimerFunc(25, updateSun, 0);  // Set up the timer for the update function

	//	glEnable(GL_DEPTH_TEST);
	//	glEnable(GL_LIGHTING);
	//	glEnable(GL_LIGHT0);
	//	glEnable(GL_NORMALIZE);
	//	glEnable(GL_COLOR_MATERIAL);

	//	glShadeModel(GL_SMOOTH);

	//	glutTimerFunc(16, timer, 0); // Adjust the timer interval as needed

	//	glutMainLoop();
	//}
}
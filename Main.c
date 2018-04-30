//##############################################################################
#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#include <GL\glut.h>
#include "Figures.c"
//------------------------------------------------------------------------------
void changeSize(int w, int h) {
	FWI = w;
	FHE = h;
	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}
//------------------------------------------------------------------------------
void computePos(float deltaMove) {
	deltaMove = 0.0f;
	Player[GamerNum].lz = 0;
	Player[GamerNum].lx = 0;
	if( KEY_LEFT == 1){
		Player[GamerNum].lx = 1;
		deltaMove = 0.999f;
	}
	if( KEY_RIGHT == 1){
		Player[GamerNum].lx = -1;
		deltaMove = 0.999f;
	}
	if( KEY_UP == 1){
		Player[GamerNum].lz = 1;
		deltaMove = 0.999f;
	}
	if( KEY_DOWN == 1){
		Player[GamerNum].lz = -1;
		deltaMove = 0.999f;
	}
	if (Player[GamerNum].lx != 0 && Player[GamerNum].lz != 0)	{
		Player[GamerNum].lx = Player[GamerNum].lx / sqrt (2);
		Player[GamerNum].lz = Player[GamerNum].lz / sqrt (2);
	}
	Player[GamerNum].x += deltaMove * Player[GamerNum].lx * 0.1f;
	Player[GamerNum].z += deltaMove * Player[GamerNum].lz * 0.1f;
//****************************************
	EndOfWorld(deltaMove, GamerNum);
	Nastupil(deltaMove, GamerNum);
	BulletsFly(GamerNum);
//****************************************
	Player[GamerNum].reload --;
//****************************************
}
//------------------------------------------------------------------------------
void renderScene(void) {
	int kek;
	computePos(Player[GamerNum].deltaMove);
	Shoot(GamerNum);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(Player[GamerNum].x, Player[GamerNum].y+50, Player[GamerNum].z,
		  Player[GamerNum].x ,Player[GamerNum].y - 1,Player[GamerNum].z,
		  0,0,1);
	DrawMainField(Field[0].width, Field[0].height, 5);	
	for (kek = 0; kek < 2; kek ++){
		DrawPlayer(kek);
		DrawPistole(kek);
		DrawBullets(kek);	
	}		  
	DrawBlocks();
	glutSwapBuffers();
}
//------------------------------------------------------------------------------
void pressKey(int key, int xx, int yy) {
	switch (key) {
		case GLUT_KEY_LEFT:
			KEY_LEFT = 1;
			break;
		case GLUT_KEY_RIGHT:
			KEY_RIGHT = 1;
			break;
		case GLUT_KEY_UP:
			KEY_UP = 1;
			break;
		case GLUT_KEY_DOWN:
			KEY_DOWN = 1;
			break;
	}
}
//------------------------------------------------------------------------------
void releaseKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
			KEY_LEFT = 0;
			break;
		case GLUT_KEY_RIGHT: 
			KEY_RIGHT = 0;
			break;
		case GLUT_KEY_UP:
			KEY_UP = 0;
			break;
		case GLUT_KEY_DOWN:
			KEY_DOWN = 0; 
			break;
		case GLUT_KEY_F1:
			GamerNum ++;
			GamerNum = GamerNum % 2;
			glClearColor(0.0/2,0.0/2,2.0/2,0);
			break;
	}
}
//------------------------------------------------------------------------------
void mouseMove(int x, int y) {
	Player[GamerNum].angle = atan2(-(double)(x-FWI/2), (double)(y-FHE/2));		
}
//------------------------------------------------------------------------------
void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP) {

			LEFT_BUTTON = 0;
		}
		else  {
			LEFT_BUTTON = 1;
		}
	}
}
//------------------------------------------------------------------------------
int main(int argc, char **argv) {
	LEFT_BUTTON = 0;
	GamerNum = 0;
	FieldInit();
	BlocksInit();
	PlayerInit();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(400,400);
	glutCreateWindow("Урок 2");
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutSpecialFunc(pressKey);
	glutPassiveMotionFunc(mouseMove);
	glutMotionFunc(mouseMove);
	glutMouseFunc(mouseButton);
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.937/2,0.937/2,0.961/2,0);
	glutMainLoop();
	return 0;
}
//##############################################################################

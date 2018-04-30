//##############################################################################
#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#include <GL\glut.h>
#include "Func.c"
int GamerNum;
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
//******************************************************************************
	glPushMatrix();
	glColor3f(0.937,0.937,0.961);
	glTranslatef(0,0,0);
	glBegin(GL_QUADS);
		glVertex3f(0.0, -0.001f, 0.0);
		glVertex3f(0.0, -0.001f,  5 * Field[0].height);
		glVertex3f( 5 * Field[0].width, -0.001f,  5 * Field[0].height);
		glVertex3f( 5 * Field[0].width, -0.001f, 0.0);
	glEnd();
	glPopMatrix();	
//******************************************************************************
	for (kek = 0; kek < 2; kek ++)
	{
		glPushMatrix();
		glColor3f(0.949/2,0.404/2,0.251/2);
		glTranslatef(Player[kek].x,Player[kek].y,Player[kek].z);
		glRotatef(180-(Player[kek].angle+Player[kek].deltaangle)*180.0/3.1415,0.0,1.0,0.0);
	    glBegin( GL_TRIANGLE_FAN );
	        glVertex3f( 0.0f, 0.0f, 0.0f );
	        int ii;
	        for( ii = 0; ii <= 50; ii++ ) {
	            float da = (float)ii / 50.0f * 3.1415f * 2.0f;
	            glVertex3f( cos( da ) * ( Player[kek].Radius + 0.2 ), 0.0f, sin( da ) * ( Player[kek].Radius + 0.2 ));
	        }
	    glEnd();
		glColor3f(0.949,0.404,0.251);
	    glBegin( GL_TRIANGLE_FAN );
	        glVertex3f( 0.0f, 0.001f, 0.0f );
	        for( ii = 0; ii <= 50; ii++ ) {
	        	float da = (float)ii / 50.0f * 3.1415f * 2.0f;
	        	glVertex3f( cos( da ) * Player[kek].Radius, 0.0f, sin( da ) * Player[kek].Radius );
	        }
	    glEnd();
		glPopMatrix();	 
		glPushMatrix();
		glColor3f(0.2,0.2,0.2);
		glTranslatef(Player[kek].x - cos(Player[kek].angle) * Player[kek].Radius * 1.2 ,Player[kek].y,Player[kek].z - sin(Player[kek].angle) * Player[kek].Radius * 1.2);
		glRotatef(180-Player[kek].angle * 180.0 / 3.1415, 0.0, 1.0, 0.0);
			glBegin(GL_QUADS);
			glVertex3f(0.0, 0.3f, -0.2);
			glVertex3f(0.0, 0.3f,  2.5);
			glVertex3f( 0.5, 0.3f,  2.5);
			glVertex3f( 0.5, 0.3f, -0.2);
		glEnd();
		glPopMatrix(); 
	}
//******************************************************************************		  
	int i,j;
	for(i = 0; i < 25; i++)
		if(Player[GamerNum].x - Field[i].x < (FWI + Field[i].width)/2 && - Player[GamerNum].x + Field[i].x < (FWI + Field[i].width)/2 &&
		   Player[GamerNum].z - Field[i].y < (FHE + Field[i].height)/2 && - Player[GamerNum].z + Field[i].y < (FHE + Field[i].height)/2){
			for(j=0; j < NB; j++){
		 		glPushMatrix();
				glColor3f(0.9137/2,0.749/2,0.624/2);
				glTranslatef(Field[i].blocks[j].x, 0.0f, Field[i].blocks[j].y);
				glBegin(GL_QUADS);
					glVertex3f(-Field[i].blocks[j].d/2-0.2, 0.0f, -Field[i].blocks[j].d/2-0.2);
					glVertex3f(-Field[i].blocks[j].d/2-0.2, 0.0f,  Field[i].blocks[j].d/2+0.2);
					glVertex3f( Field[i].blocks[j].d/2+0.2, 0.0f,  Field[i].blocks[j].d/2+0.2);
					glVertex3f( Field[i].blocks[j].d/2+0.2, 0.0f, -Field[i].blocks[j].d/2-0.2);
				glEnd();
				glPopMatrix();
				glColor3f(0.9137,0.749,0.624);
				glPushMatrix();
				glTranslatef(Field[i].blocks[j].x, 0.0f, Field[i].blocks[j].y);
				glBegin(GL_QUADS);
					glVertex3f(-Field[i].blocks[j].d/2, 0.001f, -Field[i].blocks[j].d/2);
					glVertex3f(-Field[i].blocks[j].d/2, 0.001f,  Field[i].blocks[j].d/2);
					glVertex3f( Field[i].blocks[j].d/2, 0.001f,  Field[i].blocks[j].d/2);
					glVertex3f( Field[i].blocks[j].d/2, 0.001f, -Field[i].blocks[j].d/2);
				glEnd();
				glPopMatrix();
			}
		}
//******************************************************************************
	for (kek = 0; kek < 2; kek ++)
	{
		for( i = 0; i < 20; i ++) 
			if (Player[kek].bullets[i].time > 0) {
				glPushMatrix();
				glColor3f(0.0,0.0,0.0);
				glTranslatef(Player[kek].bullets[i].x, Player[kek].bullets[i].y, Player[kek].bullets[i].z);
				glRotatef(180-Player[kek].bullets[i].angle * 180.0 / 3.1415, 0.0, 1.0, 0.0);
				glBegin(GL_QUADS);
					glVertex3f(-0.2, 0.01f, -0.2);
					glVertex3f(-0.2, 0.01f,  0.2);
					glVertex3f( 0.2, 0.01f,  0.2);
					glVertex3f( 0.2, 0.01f, -0.2);
				glEnd();
				glPopMatrix();		
			}
	}
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

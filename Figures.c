#include <math.h>
#include <GL\glut.h>
#include "Func.c"
int GamerNum;
//------------------------------------------------------------------------------
void DrawMainField(double width, double height, int N){
	glPushMatrix();
	glColor3f(0.937,0.937,0.961);
	glTranslatef(0,0,0);
	glBegin(GL_QUADS);
		glVertex3f(0.0, -0.001f, 0.0);
		glVertex3f(0.0, -0.001f,  N * height);
		glVertex3f( N * width, -0.001f,  N * height);
		glVertex3f( N * width, -0.001f, 0.0);
	glEnd();
	glPopMatrix();
}
//------------------------------------------------------------------------------
void DrawPlayer(int kek){
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
}
//------------------------------------------------------------------------------
void DrawPistole(int kek){
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
//------------------------------------------------------------------------------
void DrawBlocks(){
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
}
//------------------------------------------------------------------------------
void DrawBullets(int kek){
	int i;
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
//------------------------------------------------------------------------------

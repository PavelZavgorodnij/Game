#include <math.h>
#include<stdlib.h>
#include<stdio.h>
#include "Structs.c"
//------------------------------------------------------------------------------
int LEFT_BUTTON;
int FWI, FHE;
int KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN;
Pole Field[25];
Gamer Player[2];
//------------------------------------------------------------------------------
void FieldInit() {
	int i,j;
	for (i = 0; i < 5; i ++ )
		for( j = 0; j < 5; j ++ )
		{
			Field[5 * i + j].x = 25 + 50 * j;
			Field[5 * i + j].y = 25 + 50 * i;
			Field[5 * i + j].width = 50;
			Field[5 * i + j].height = 50;
		}
}
//------------------------------------------------------------------------------
void BlocksInit() {
	int i,j;
	for ( i = 0; i < 25; i ++ )
		for ( j = 0; j < NB; j ++ )
		{
			Field[i].blocks[j].d = 4;
			Field[i].blocks[j].x = Field[i].x - Field[i].width / 2 + rand() % Field[i].width;
			Field[i].blocks[j].y = Field[i].y - Field[i].height / 2 + rand() % Field[i].height;
		}
}
//------------------------------------------------------------------------------
void PlayerInit()
{
	int kek;
	for (kek = 0; kek < 2; kek ++)
	{
		Player[kek].angle = 0.0f;
		Player[kek].lx = 0.0f; 
		Player[kek].lz = - 1.0f;
		Player[kek].ly = 0.0f;
		Player[kek].x = 5.0f; 
		Player[kek].z = 8.5f; 
		Player[kek].y = 1.65f;
		Player[kek].deltaangle = 0.0f;
		Player[kek].deltaMove = 0;
		Player[kek].Radius = 1.7;
		Player[kek].bullettime = 1000;
		Player[kek].reload = 0;
		Player[kek].bulmove = 5.0;
		int i;
		for (i = 0; i < 20; i ++)
			Player[kek].bullets[i].time = 0;	
	}
}
//------------------------------------------------------------------------------
void Shoot(int kek) {
	if(LEFT_BUTTON == 1)
		if (Player[kek].reload <= 0) {
			int i;
			for (i = 0; i < 20; i ++)
				if (Player[kek].bullets[i].time == 0) {
					Player[kek].bullets[i].time = Player[kek].bullettime;
					Player[kek].bullets[i].x = Player[kek].x - cos(Player[kek].angle) * Player[kek].Radius * 1.4;
					Player[kek].bullets[i].y = Player[kek].y;
					Player[kek].bullets[i].z = Player[kek].z - sin(Player[kek].angle) * Player[kek].Radius * 1.4;
					Player[kek].bullets[i].angle = Player[kek].angle;
					Player[kek].bullets[i].deltaMove = Player[kek].bulmove;
					break;
				}
			Player[kek].reload = 100;
		}
}
//------------------------------------------------------------------------------
void Nastupil(float deltaMove, int kek){
	int i,j;
	Player[kek].Radius +=0.25;
	for(i = 0; i < 25; i ++)
		for(j = 0; j < NB; j ++)
			if((Player[kek].x >= Field[i].blocks[j].x - Field[i].blocks[j].d / 2 && Player[kek].x <= Field[i].blocks[j].x + Field[i].blocks[j].d / 2 &&
				Player[kek].z >= Field[i].blocks[j].y - Field[i].blocks[j].d / 2 - Player[kek].Radius && Player[kek].z <= Field[i].blocks[j].y + Field[i].blocks[j].d / 2 + Player[kek].Radius ) ||
				(Player[kek].z >= Field[i].blocks[j].y - Field[i].blocks[j].d / 2 && Player[kek].z <= Field[i].blocks[j].y + Field[i].blocks[j].d / 2 &&
				Player[kek].x >= Field[i].blocks[j].x - Field[i].blocks[j].d / 2 - Player[kek].Radius && Player[kek].x <= Field[i].blocks[j].x + Field[i].blocks[j].d / 2 + Player[kek].Radius ) ||
				((Player[kek].x - Field[i].blocks[j].x + Field[i].blocks[j].d / 2) * (Player[kek].x - Field[i].blocks[j].x + Field[i].blocks[j].d / 2) + (Player[kek].z - Field[i].blocks[j].y + Field[i].blocks[j].d / 2) * (Player[kek].z - Field[i].blocks[j].y + Field[i].blocks[j].d / 2) <= Player[kek].Radius * Player[kek].Radius) || 
				((Player[kek].x - Field[i].blocks[j].x + Field[i].blocks[j].d / 2) * (Player[kek].x - Field[i].blocks[j].x + Field[i].blocks[j].d / 2) + (Player[kek].z - Field[i].blocks[j].y - Field[i].blocks[j].d / 2) * (Player[kek].z - Field[i].blocks[j].y - Field[i].blocks[j].d / 2) <= Player[kek].Radius * Player[kek].Radius) ||
				((Player[kek].x - Field[i].blocks[j].x - Field[i].blocks[j].d / 2) * (Player[kek].x - Field[i].blocks[j].x - Field[i].blocks[j].d / 2) + (Player[kek].z - Field[i].blocks[j].y + Field[i].blocks[j].d / 2) * (Player[kek].z - Field[i].blocks[j].y + Field[i].blocks[j].d / 2) <= Player[kek].Radius * Player[kek].Radius) ||
				((Player[kek].x - Field[i].blocks[j].x - Field[i].blocks[j].d / 2) * (Player[kek].x - Field[i].blocks[j].x - Field[i].blocks[j].d / 2) + (Player[kek].z - Field[i].blocks[j].y - Field[i].blocks[j].d / 2) * (Player[kek].z - Field[i].blocks[j].y - Field[i].blocks[j].d / 2) <= Player[kek].Radius * Player[kek].Radius)){
					double moddd = (Player[kek].x - Field[i].blocks[j].x)*(Player[kek].x - Field[i].blocks[j].x)+(Player[kek].z - Field[i].blocks[j].y)*(Player[kek].z - Field[i].blocks[j].y);
					moddd = sqrt(moddd);
					Player[kek].x -= deltaMove * Player[kek].lx * 0.1f;
					Player[kek].z -= deltaMove * Player[kek].lz * 0.1f;
					Player[kek].x += deltaMove * (Player[kek].x - Field[i].blocks[j].x)/moddd * 0.1f;
					Player[kek].z += deltaMove * (Player[kek].z - Field[i].blocks[j].y)/moddd * 0.1f;
			}
	Player[kek].Radius -=0.25;
}
//------------------------------------------------------------------------------
void EndOfWorld(float deltaMove, int kek){
	if (Player[kek].x + Player[kek].Radius > 5 * Field[0].width )
		Player[kek].x -= deltaMove * 0.1f;
	if (Player[kek].x - Player[kek].Radius < 0 )
		Player[kek].x += deltaMove * 0.1f;
	if (Player[kek].z + Player[kek].Radius > 5 * Field[0].height )
		Player[kek].z -= deltaMove * 0.1f;
	if (Player[kek].z - Player[kek].Radius < 0 )
		Player[kek].z += deltaMove * 0.1f;
}
//------------------------------------------------------------------------------
void BulletsFly(int kek){
	int i;
	for (i = 0; i < 20; i ++) 
		if (Player[kek].bullets[i].time > 0) {
			Player[kek].bullets[i].time --;
			Player[kek].bullets[i].x += Player[kek].bullets[i].deltaMove * sin (Player[kek].bullets[i].angle) * 0.1f;
			Player[kek].bullets[i].z += Player[kek].bullets[i].deltaMove * -cos (Player[kek].bullets[i].angle) * 0.1f;
			int ii,jj;
			for(ii = 0; ii < 25; ii ++)
				for(jj = 0; jj < NB; jj ++)
					if((Player[kek].bullets[i].x >= Field[ii].blocks[jj].x - Field[ii].blocks[jj].d / 2 && Player[kek].bullets[i].x <= Field[ii].blocks[jj].x + Field[ii].blocks[jj].d / 2 &&
						Player[kek].bullets[i].z >= Field[ii].blocks[jj].y - Field[ii].blocks[jj].d / 2 && Player[kek].bullets[i].z <= Field[ii].blocks[jj].y + Field[ii].blocks[jj].d / 2 ))
							Player[kek].bullets[i].time = 0;
			if (Player[kek].bullets[i].x > 5 * Field[0].width || Player[kek].bullets[i].x < 0 || 
				Player[kek].bullets[i].z > 5 * Field[0].height || Player[kek].bullets[i].z < 0 )
					Player[kek].bullets[i].time = 0;
		}
}

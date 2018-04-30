//------------------------------------------------------------------------------
#define NB 20
//------------------------------------------------------------------------------
typedef struct {
	int x;
	int y;
	double d;	
} Block;
//------------------------------------------------------------------------------
typedef struct {
	int width;
	int height;
	int x;
	int y;
	Block blocks[NB];	
} Pole;
//------------------------------------------------------------------------------
typedef struct {
	float x;
	float y;
	float z;
	float angle;
	float deltaMove;
	int time;
} Bullet;
//------------------------------------------------------------------------------
typedef struct {
	float x;
	float y;
	float z;
	float lx;
	float ly;
	float lz;
	float angle;
	float deltaangle;
	float deltaMove;
	float bulmove;
	float Radius;
	int bullettime;
	int reload;
	Bullet bullets[20];
} Gamer ;

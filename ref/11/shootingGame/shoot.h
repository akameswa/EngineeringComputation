#ifndef SHOOT_H_IS_DEFINED_837401831
#define SHOOT_H_IS_DEFINED_837401831

class SpaceShip
{
public:
	int x,y;
	void Initialize(void);
	void Move(int key);
	void Draw(void);
};

class Missile
{
public:
	int x,y,v;
	bool state;

	void Initialize(void);
	void Launch(int X,int Y);
	void MoveUp(void);
	void Terminate(void);
	void Render(void);
};

class Target
{
public:
	int x,y,w,h,v;
	bool state;

	void Initialize(void);
	void MoveRight(void);
	void Terminate(void);
	void Render(void);
};

class Particle
{
public:
	int x,y,vx,vy;

	void Initialize(void);
	void Start(int x0,int y0);
	void Move(void);
};

bool CheckCollision(int mx,int my,int tx,int ty,int tw,int th);  // <- Function prototype

#endif

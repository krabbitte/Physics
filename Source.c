#include <stdio.h>
#include <math.h>
#include <windows.h>

#define PI 3.1415926535897
#define GRAV -9.8
#define SLEEPRATIO interval/1000
#define sec(sec) sec * 1000.0 / interval
#define velmag point.vel.x * point.vel.x + point.vel.y * point.vel.y
#define accmag point.acc.x * point.acc.x + point.acc.y * point.acc.y
#define setpointfield(a,b) point.a.x = b; point.acc.y = b;

int updatepos();
int checkforces();
int clearforce();
int clearscreen();

typedef struct force {
	double x, y;
	double magnitude;
	double angle;
	double radius;
}force;

typedef struct acceleration {
	double x, y;
}acceleration;

typedef struct velocity {
	double x, y;
}velocity;

typedef struct object {
	double x, y;
	double mass;
	acceleration vel;
	velocity acc;
	force forces[20];
}obj;

obj point;
double interval;
double acc, vel, angle;
force force1, force2;

int main()
{
	int time = 0;

	interval = 10;

	force1.angle = 90;
	force1.magnitude = 5;
	force2.angle = 0;
	force2.magnitude = 0;

	while (time < sec(30.0))
	{

		for (int i = 0; i < 20; i++)
		{
			clearforce();
			setpointfield(acc, 0);
		}

		checkforces();

		for (int i = 0; i < 20; i++)
		{
			point.acc.x += point.forces[i].magnitude * cos(point.forces[i].angle * (PI/180));
			point.acc.y += point.forces[i].magnitude * sin(point.forces[i].angle * (PI / 180));
		}

		if (fmod(time, sec(1)) == 0)
		{
			clearscreen();
			printf("Time: %0.3f\tVel = %0.3f\tAcc = %0.3f\t(%0.2f , %0.2f)", (double)time * SLEEPRATIO, sqrt(velmag), sqrt(accmag), point.x, point.y);
		}

		Sleep(interval);
		updatepos();

		time++;
	}

	return 0;
}

int updatepos()
{
	point.vel.x += (point.acc.x * (SLEEPRATIO));
	point.vel.y += (point.acc.y * (SLEEPRATIO));

	point.x += point.vel.x * SLEEPRATIO;
	point.y += point.vel.y * SLEEPRATIO;

	return 0;
}

int clearforce()
{
	for (int i = 0; i < 20; i++)
	{
		point.forces[i].x = 0;
		point.forces[i].y = 0;
		point.forces[i].magnitude = 0;
		point.forces[i].angle = 0;
		point.forces[i].radius = 0;
	}

	return 0;
}

int clearscreen()
{
	for (int i = 0; i < 300; i++)
	{
		if (i < 100)
		{
			printf("\b");
		}
		else if (i > 99 && i < 200)
		{
			printf(" ");
		}
		else
			printf("\b");
	}

	return 0;
}

int checkforces()
{
	/*Add system for adding forces by distance from point*/

	point.forces[0] = force1;
	point.forces[1] = force2;

	return 0;
}
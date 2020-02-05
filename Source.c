#include <stdio.h>
#include <math.h>
#include <windows.h>

#define PI 3.14159265359
#define GRAV -9.8
#define SLEEPRATIO interval/1000
#define sec(sec) sec * 1000 / interval

int updatepos();

typedef struct force {
	double x, y;
	double magnitude;
	double radius;
}force;

typedef struct object {
	double x, y;
	double vel, acc;
	double mass;
	force forces[20];
}obj;

obj point;
double interval;
double acc, vel, angle;

int main()
{
	int time = 0;

	for (int i = 0; i < 20; i++)
		point.forces[i].magnitude = 0;

	point.forces[0].magnitude = 2;
	point.forces[1].magnitude = -1;
	point.vel = 0;
	interval = 10;
	angle = 45;

	while (time < sec(30))
	{
		/* Print coordinates every sec(x) seconds */
		point.acc = 0;
		for (int i = 0; i < 20; i++)
			point.acc += point.forces[i].magnitude;

		if (fmod(time, sec(0.1)) == 0)
			printf("Time: %0.3f	Vel = %0.3f	(%0.5f , %0.5f)\n", (double)time * SLEEPRATIO, point.vel, point.x, point.y);

		Sleep(interval);
		updatepos();

		time++;
	}

	return 0;
}

int updatepos()
{
	point.vel += (point.acc * (SLEEPRATIO));

	point.x += point.vel * cos(angle * (PI / 180)) * SLEEPRATIO;
	point.y += point.vel * sin(angle * (PI / 180)) * SLEEPRATIO;

	return 0;
}
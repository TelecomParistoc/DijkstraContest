#include "obstacles.h"
#include "point.h"
#include <math.h>

#define PI 3.14159265

//Cos in degrees
float dcos(float angle) {
	return cos(angle * PI / 180);
}

//Sin in degrees
float dsin(float angle) {
	return sin(angle * PI / 180);
}

extern float radius;

Obstacle::Obstacle(float x, float y, float halfWidth, float halfHeight, float angle) {
	this->x = x;
	this->y = y;
	this->halfWidth = halfWidth;
	this->halfHeight = halfHeight;
	this->angle = angle;
}

float Obstacle::getX() const{
	return this->x;
}

float Obstacle::getY() const{
	return this->y;
}

float Obstacle::getWidth() const{
	return this->halfWidth*2;
}

float Obstacle::getHeight() const{
	return this->halfHeight*2;
}

void Obstacle::getCorners(Point out[]) const{
	float margin = radius/5;
	//Top Left Corner
	out[0].x = this->x - (this->halfWidth * dcos(-this->angle) - this->halfHeight * dsin(-this->angle)) - radius - margin;
	out[0].y = this->y + (this->halfHeight * dcos(-this->angle) + this->halfWidth * dsin(-this->angle)) + radius + margin;
	//Top Right Corner
	out[1].x = this->x + (this->halfWidth * dcos(-this->angle) + this->halfHeight * dsin(-this->angle)) + radius + margin;
	out[1].y = this->y + (this->halfHeight * dcos(-this->angle) - this->halfWidth * dsin(-this->angle)) + radius + margin;
	//Bottom Right Corner
	out[2].x = this->x + (this->halfWidth * dcos(-this->angle) - this->halfHeight * dsin(-this->angle)) + radius + margin;
	out[2].y = this->y - (this->halfHeight * dcos(-this->angle) + this->halfWidth * dsin(-this->angle)) - radius - margin;
	//Bottom Left Corner
	out[3].x = this->x - (this->halfWidth * dcos(-this->angle) + this->halfHeight * dsin(-this->angle)) - radius - margin;
	out[3].y = this->y - (this->halfHeight * dcos(-this->angle) - this->halfWidth * dsin(-this->angle)) - radius - margin;
}

#ifndef BALL_H
#define BALL_H
#pragma once

const int ballLength = 8;

class ball
{
private:
	float xPos;
	float yPos;
	float xDir;
	float yDir;
	float ballSpeed;

public:
	ball(float xPos, float yPos, float xDir, float yDir);
	ball(float xPos, float yPos, float xDir, float yDir, float ballSpeed);

	float getXPos() { return xPos; };
	float getYPos() { return yPos; };
	float getXDir() { return xDir; };
	float getYDir() { return yDir; };
	float getBallSpeed() { return ballSpeed; };

	void setXPos(float newX) { xPos = newX; };
	void setYPos(float newY) { yPos = newY; };
	void setXDir(float newXDir) { xDir = newXDir; };
	void setYDir(float newYDir) { yDir = newYDir; };

	void checkRacketCollision(int gameWidth, int racketWidth, int racketHeight, int X, int Y);

	void soundOnHit();
};

#endif // !BALL_H
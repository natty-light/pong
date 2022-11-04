#include "ball.hh"
#include <math.h>
#include <windows.h>

ball::ball(float x, float y, float vx, float vy) {
	xDir = vx;
	yDir = vy;
	xPos = x;
	yPos = y;
}
ball::ball(float x, float y, float vx, float vy, float vScalar) {
	ballSpeed = vScalar;
	xDir = vx;
	yDir = vy;
	xPos = x;
	yPos = y;
}

void ball::soundOnHit() {
	PlaySound(TEXT("pongSound.wav"), NULL, SND_ASYNC | SND_FILENAME);
}

void ball::checkRacketCollision(int gameWidth, int racketWidth, int racketHeight, int X, int Y) {
	float xVelMultiplier = 1.;
	if (X > gameWidth / 2.f) {
		xVelMultiplier *= -1.;
	}

	if (xPos < X + racketWidth &&
		xPos > X &&
		yPos < Y + racketHeight &&
		yPos > Y) {
		float t = ((yPos - Y) / racketHeight) - .5f;
		setXDir(xVelMultiplier * fabs(xDir));
		setYDir(t);
		soundOnHit();
	}
}



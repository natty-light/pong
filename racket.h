#ifndef RACKET_H
#define RACKET_H
#pragma once

const int racketHeight = 80;
const int racketWidth = 10;
const int racketSpeed = 3;

class racket
{
private:
	float xPos;
	float yPos;
	
public:
	racket(float xPos, float yPos); // Constructor Declaration

	float getXPos() { return xPos; }; // Getter Functions
	float getYPos() { return yPos; }; 

	void setXPos(float newX) { xPos = newX; }; // Setter Functions
	void setYPos(float newY) { yPos = newY; };
};

#endif // !RACKET_H
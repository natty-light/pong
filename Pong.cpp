#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLFW/glfw3.h>
#include "racket.hh"
#include "ball.hh"
#pragma comment(lib, "OpenGL32.lib")

// TODO: Move normalize velocity to ball class

// keycodes I'm not sure if this would be better to do this in the racket header
#define VK_W 0x57
#define VK_S 0x53
#define VK_UP 0x26
#define VK_DOWN 0x28

#define UP_W 0x77
#define DOWN_S 0x73

#define GL_SILENCE_DEPRECATION 1

int width = 500;
int height = 500;
int interval = 1000 / 60;
int offset = 10;
float ballSpeedMult = 1.0f;

int lScore = 0;
int rScore = 0;

racket leftRacket = racket(10 + racketWidth, height / 2 - racketHeight / 2);
racket rightRacket = racket(width - racketWidth - 10, height / 2 - racketHeight / 2);
ball gameBall = ball(width / 2, height / 2, ballSpeedMult*1.0f, ballSpeedMult * 1.0f, 5.0f);

float ballSpeed = gameBall.getBallSpeed();

void enable2D(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// void drawText(float x, float y, std::string text) {
//     glRasterPos2f(x, y);
//     glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
// }

void drawRect(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void vec2_norm(float& vx, float& vy) {
    // sets a vectors length to 1 (which means that x + y == 1)
    float length = sqrt((vx * vx) + (vy * vy));
    if (length != 0.0f) {
        length = 1.0f / length;
        gameBall.setXDir(vx * length);
        gameBall.setYDir(vy * length);
    }
}

float predictX(float x, float y, float vx, float vy, float X, float Y) {
    float nextBallX = x + ballSpeed * vx;
    float nextBallY = y + ballSpeed * vy;

    float ballPosAtX = y + (nextBallY - y) / (nextBallX - x) * (X - racketWidth - x);
    return ballPosAtX;
}

static void handleInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS) {
        return;
    }
    switch (key) {
        case GLFW_KEY_W:
            if (leftRacket.getYPos() < height - racketHeight - offset) leftRacket.setYPos(leftRacket.getYPos() + racketSpeed);
            break;
        case GLFW_KEY_S:
            if (leftRacket.getYPos() > 0) leftRacket.setYPos(leftRacket.getYPos() - racketSpeed);
            break;
        case GLFW_KEY_UP:
            if (rightRacket.getYPos() < height - racketHeight- offset) rightRacket.setYPos(rightRacket.getYPos() + racketSpeed);
            break;
        case GLFW_KEY_DOWN:
            if (rightRacket.getYPos() > 0) rightRacket.setYPos(rightRacket.getYPos() - racketSpeed);
            break;
    }
    return;
}

void draw() {
    // clear (has to be done at the beginning)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // ToDo: draw our scene
    // drawText(width / 4 - 10, height - 30, std::to_string(lScore));
    // drawText(3 * width / 4 + 10, height - 30, std::to_string(rScore));

    // draw rackets and ball
    drawRect(leftRacket.getXPos(), leftRacket.getYPos(), racketWidth, racketHeight);
    drawRect(rightRacket.getXPos(), rightRacket.getYPos(), racketWidth, racketHeight);
    drawRect(gameBall.getXPos() - ballLength / 2, gameBall.getYPos() - ballLength / 2, ballLength, ballLength);
    //drawRect(leftRacket.getXPos(), predictX(gameBall.getXPos(), gameBall.getYPos(), gameBall.getXDir(), gameBall.getYDir(), leftRacket.getXPos(), leftRacket.getYPos()), ballLength, ballLength);
}

void reset(float vx, float mult) {
    gameBall.setXPos(width / 2);
    gameBall.setYPos(height / 2);
    gameBall.setXDir(mult * fabs(vx)); // force it to be positive
    gameBall.setYDir(0);

    leftRacket.setXPos(10 + racketWidth);
    leftRacket.setYPos(height / 2 - racketHeight / 2);

    rightRacket.setXPos(width - racketWidth - 10);
    rightRacket.setYPos(height / 2 - racketHeight / 2);
}

void updateBall() {
    // Get some values
    float x = gameBall.getXPos();
    float vx = gameBall.getXDir();
    float y = gameBall.getYPos();
    float vy = gameBall.getYDir();

    float X_L = leftRacket.getXPos();
    float Y_L = leftRacket.getYPos();
    float X_R = rightRacket.getXPos();
    float Y_R = rightRacket.getYPos();

    // fly a bit
    gameBall.setXPos(x + vx * ballSpeed);
    gameBall.setYPos(y + vy * ballSpeed);

    // hit by left racket?
    gameBall.checkRacketCollision(width, racketWidth, racketHeight, X_L, Y_L);

    // hit by right racket?
    gameBall.checkRacketCollision(width, racketWidth, racketHeight, X_R, Y_R);

    // hit left wall?
    if (x < 0) {
        ++rScore;
        reset(vx, 1);
    }

    // hit right wall?
    if (x > width) {
        ++lScore;
        reset(vx, -1);
    }

    // hit top wall?
    if (y > height - offset) {
        gameBall.setYDir(-fabs(vy)); // force it to be negative
    }

    // hit bottom wall?
    if (y < 0) {
        gameBall.setYDir(fabs(vy)); // force it to be positive
    }
    vx = gameBall.getXDir();
    vy = gameBall.getYDir();
    // make sure that length of dir stays at 1
    vec2_norm(vx, vy);
}

void controlPaddle(char Racket) {
    float x = gameBall.getXPos();
    float y = gameBall.getYPos();
    float vx = gameBall.getXDir();
    float vy = gameBall.getYDir();
    
    if (Racket == 'l') {
    float X = leftRacket.getXPos();
    float Y = leftRacket.getYPos();

    float ballPosAtX = predictX(x, y, vx, vy, X, Y);
	 
    if (ballPosAtX < Y + racketHeight / 2. or ballPosAtX < 0) {
		if (Y > 0) leftRacket.setYPos(Y - racketSpeed);
	}
	if (ballPosAtX > Y + racketHeight / 2. or ballPosAtX > height) {
		if (Y < height - racketHeight - offset) leftRacket.setYPos(Y + racketSpeed);
	}
    }

    if (Racket == 'r') {
        float X = rightRacket.getXPos();
        float Y = rightRacket.getYPos();

        float ballPosAtX = predictX(x, y, vx, vy, X, Y);

        if (ballPosAtX < Y + racketHeight / 2. or ballPosAtX < 0) {
            if (Y > 0) rightRacket.setYPos(Y - racketSpeed);
        }
        if (ballPosAtX > Y + racketHeight / 2. or ballPosAtX > height) {
            if (Y < height - racketHeight - offset) rightRacket.setYPos(Y + racketSpeed);
        }
    }
    
}

int main(int argc, char** argv) {
    // Init glut and set window params
    if (!glfwInit()) {
        return 0;
    }
    GLFWwindow* window = glfwCreateWindow(width, height, "Pong by Nat :) ", NULL, NULL);
    if (!window) {
        return 0;
    }
    glfwMakeContextCurrent(window);
    enable2D(width, height);
    glfwSwapInterval(1);
    
    // Register callback functions  
    glfwSetKeyCallback(window, handleInput);

    glColor3f(1.0f, 1.0f, 1.0f);
    while (!glfwWindowShouldClose(window)) {
        // update ball
        updateBall();
        controlPaddle('l');
        // controlPaddle('r');
        draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

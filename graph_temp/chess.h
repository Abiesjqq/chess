#ifndef CHESS_H
#define CHESS_H

#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

#define step 20

double distance(int x1, int y1, int x2, int y2);
void endgame();
void judgeover(int x, int y, int borad[33][33]);
void playchess(int& cnt, int board[33][33]);
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y);

#endif


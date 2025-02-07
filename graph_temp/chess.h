#ifndef CHESS_H
#define CHESS_H

#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <utility>
#include <vector>
#include <time.h>
using namespace std;

#define step 35
#define width 1110
#define height 710
#define board_x1 50
#define board_y1 30
#define board_x2 700
#define board_y2 680
#define st_x 60
#define st_y 40
#define end_x 690
#define end_y 670
#define boarder_space 20
#define cell 18
#define EMPTY 0
#define WHITE 1
#define BLACK -1


double distance(int x1, int y1, int x2, int y2);
void endgame();
bool judge_over(int x, int y, int borad[cell+1][cell+1]);
void player_move(int& cnt, int board[cell+1][cell+1]);
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y);
bool is_valid(int x, int y, int board[cell + 1][cell + 1]);
pair <int, int> computer_move_location(int board[cell + 1][cell + 1]);
void computer_move(int& cnt, int board[cell + 1][cell + 1]);

#endif


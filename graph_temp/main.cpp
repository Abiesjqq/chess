#include "chess.h"

//#define step 35
//#define width 1110
//#define height 710
//#define board_x1 50
//#define board_y1 30
//#define board_x2 700
//#define board_y2 680
//#define st_x 60
//#define st_y 40
//#define end_x 690
//#define end_y 670
//#define boarder_space 20
//#define cell 18
//#define EMPTY 0
//#define WHITE 1
//#define BLACK -1


int main()
{
	// 初始化棋盘
	initgraph(width, height, 0);
	setbkcolor(LIGHTGRAY);
	cleardevice();

	setfillcolor(RGB(128, 76, 46));
	setlinecolor(BLACK);
	fillrectangle(board_x1, board_y1, board_x2, board_y2);
	rectangle(st_x, st_y, end_x, end_y);

	for (int i = st_x+boarder_space;i < end_x;i += step) {	//画线
		line(i, st_y, i, end_y);
	}
	for (int i = st_y+boarder_space;i < end_y;i += step) {
		line(st_x, i, end_x, i);
	}

	setfillcolor(BLACK);	//画黑点
	for (int i = st_x+step*3;i < end_x;i += step * 6) {
		for (int j = st_y+step*3;j < end_y;j += step * 6) {
			solidcircle(i, j, 3);
		}
	}

	int board[cell+1][cell+1];	//建立数组
	for (int i = 0;i < cell+1;i++) {
		for (int j = 0;j < cell+1;j++) {
			board[i][j] = 0;
		}
	}


	// 下棋
	int cnt = 0;
	bool gameover = false;
	while (!gameover) {
		if (!(cnt & 1)) player_move(cnt, board);
		else computer_move(cnt,board);
		Sleep(100);
	}

	return 0;
}

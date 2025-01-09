#include "chess.h"

int main()
{
	// ≥ı ºªØ∆Â≈Ã
	initgraph(1110, 720, 0);
	setbkcolor(LIGHTGRAY);
	cleardevice();

	setfillcolor(RGB(128, 76, 46));
	setlinecolor(BLACK);
	fillrectangle(50, 30, 710, 690);
	rectangle(60, 40, 700, 680);
	for (int i = 80;i < 700;i += step) {
		line(i, 40, i, 680);
	}
	for (int i = 60;i < 680;i += step) {
		line(60, i, 700, i);
	}
	setfillcolor(BLACK);
	for (int i = 140;i < 700;i += step * 12) {
		for (int j = 120;j < 680;j += step * 12) {
			solidcircle(i, j, 3);
		}
	}
	int board[33][33];
	for (int i = 0;i < 33;i++) {
		for (int j = 0;j < 33;j++) {
			board[i][j] = 0;
		}
	}


	// œ¬∆Â
	int cnt = 0;
	bool gameover = false;
	while (!gameover) {
		playchess(cnt, board);
		Sleep(100);
	}

	return 0;
}

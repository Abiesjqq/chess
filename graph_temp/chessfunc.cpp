#include "chess.h"

// �ж�������
double distance(int x1, int y1, int x2, int y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// ��Ϸ����ʱ����
void endgame() {
	Sleep(1000);
	setfillcolor(RED);
	fillrectangle(0, 0, 1110, 720);
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTGRAY);
	settextstyle(50, 0, L"Consolas");
	outtextxy(480, 300, TEXT("GAME OVER"));
	Sleep(1000);
	closegraph();
}

// �ж��Ƿ����
void judgeover(int posx, int posy, int board[33][33]) {
	int x = (posx - 60) / step;
	int y = (posy - 40) / step;
	int x1 = x, y1 = y;
	int sum = 1;
	int cur = board[x1][y1];

	// ������
	while (x - 1 >= 0 && board[x - 1][y] == cur) {
		x--;sum++;
	}
	x = x1;
	while (x + 1 <= 32 && board[x + 1][y] == cur) {
		x++;sum++;
	}
	if (sum >= 5) {
		endgame();
		return;
	}

	// �������
	sum = 1; x = x1;
	while (y - 1 >= 0 && board[x][y - 1] == cur) {
		y--;sum++;
	}
	y = y1;
	while (y + 1 <= 32 && board[x][y + 1] == cur) {
		y++;sum++;
	}
	if (sum >= 5) {
		endgame();
		return;
	}

	// ���б��
	sum = 1;
	x = x1, y = y1;
	while (x - 1 >= 0 && y - 1 >= 0 && board[x - 1][y - 1] == cur) {
		x--;y--;sum++;
	}
	x = x1, y = y1;
	while (x + 1 <= 32 && y + 1 <= 32 && board[x + 1][y + 1] == cur) {
		x++;y++;sum++;
	}
	if (sum >= 5) {
		endgame();
		return;
	}

	sum = 1;
	x = x1, y = y1;
	while (x - 1 >= 0 && y + 1 <= 32 && board[x - 1][y + 1] == cur) {
		x--;y++;sum++;
	}
	x = x1, y = y1;
	while (x + 1 <= 32 && y - 1 >= 0 && board[x + 1][y - 1] == cur) {
		x++;y--;sum++;
	}
	if (sum >= 5) {
		endgame();
		return;
	}
}

// ����
void playchess(int& cnt, int board[33][33]) {
	ExMessage msg;
	int  posx = 0, posy = 0;
	while (true) {
		if (MouseHit()) {
			getmessage(&msg);
			if (msg.message == WM_LBUTTONDOWN) {
				for (posx = 60;posx <= 700;posx += step) {
					for (posy = 40;posy <= 680;posy += step) {
						if (distance(msg.x, msg.y, posx, posy) < 6 && !board[(posx - 60) / step][(posy - 40) / step]) {
							IMAGE img;
							if (cnt & 1) loadimage(&img, L"D:\\vs_projects\\graph_temp\\White.png", 16, 16);
							else loadimage(&img, L"D:\\vs_projects\\graph_temp\\Black.png", 16, 16);
							drawAlpha(&img, posx - 8, posy - 8);

							if (cnt & 1) board[(posx - 60) / step][(posy - 40) / step] = 1; // 1��ʾ����
							else board[(posx - 60) / step][(posy - 40) / step] = -1; // -1��ʾ����
							cnt++;
							judgeover(posx, posy, board);
						}
					}
				}
			}
		}
	}
}

// ����PNGͼ��ȥ͸������
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //xΪ����ͼƬ��X���꣬yΪY����
{

	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

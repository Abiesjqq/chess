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

// 判断两点间距
double distance(int x1, int y1, int x2, int y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// 游戏结束时操作
void endgame() {
	Sleep(1000);
	setfillcolor(RED);
	fillrectangle(0, 0, width, height);
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTGRAY);
	settextstyle(50, 0, L"Consolas");
	outtextxy(480, 300, TEXT("GAME OVER"));
	Sleep(1000);
	closegraph();
}

// 判断是否结束
bool judge_over(int posx, int posy, int board[cell+1][cell+1]) {
	int x = (posx - st_x) / step;
	int y = (posy - st_y) / step;
	int x1 = x, y1 = y;
	int sum = 1;
	int cur = board[x1][y1];
	bool res = false;

	// 检查横向
	while (x - 1 >= 0 && board[x - 1][y] == cur) {
		x--;sum++;
	}
	x = x1;
	while (x + 1 <= cell && board[x + 1][y] == cur) {
		x++;sum++;
	}
	if (sum >= 5) {
		res = true;
		endgame();
		return res;
	}

	// 检查纵向
	sum = 1; x = x1;
	while (y - 1 >= 0 && board[x][y - 1] == cur) {
		y--;sum++;
	}
	y = y1;
	while (y + 1 <= cell && board[x][y + 1] == cur) {
		y++;sum++;
	}
	if (sum >= 5) {
		res = true;
		endgame();
		return res;
	}

	// 检查斜向
	sum = 1;
	x = x1, y = y1;
	while (x - 1 >= 0 && y - 1 >= 0 && board[x - 1][y - 1] == cur) {
		x--;y--;sum++;
	}
	x = x1, y = y1;
	while (x + 1 <= cell && y + 1 <= cell && board[x + 1][y + 1] == cur) {
		x++;y++;sum++;
	}
	if (sum >= 5) {
		res = true;
		endgame();
		return res;
	}

	sum = 1;
	x = x1, y = y1;
	while (x - 1 >= 0 && y + 1 <= cell && board[x - 1][y + 1] == cur) {
		x--;y++;sum++;
	}
	x = x1, y = y1;
	while (x + 1 <= cell && y - 1 >= 0 && board[x + 1][y - 1] == cur) {
		x++;y--;sum++;
	}
	if (sum >= 5) {
		res = true;
		endgame();
		return res;
	}
}

void draw_chess(int x,int y,int& cnt,int board[cell+1][cell+1]) {
	IMAGE img;	//画图
	int img_size = 16;
	if (cnt & 1) loadimage(&img, L"D:\\vs_projects\\graph_temp\\White.png", img_size, img_size);
	else loadimage(&img, L"D:\\vs_projects\\graph_temp\\Black.png", img_size, img_size);
	drawAlpha(&img, x - img_size / 2, y - img_size / 2);

	if (cnt & 1) board[(x - st_x) / step][(y - st_y) / step] = WHITE; // 1表示白子
	else board[(x - st_x) / step][(y - st_y) / step] = BLACK; // -1表示黑子
	cnt++;

}

// 落子
void player_move(int& cnt, int board[cell+1][cell+1]) {
	ExMessage msg;
	int  posx = 0, posy = 0;
	while (true) {
		if (MouseHit()) {
			getmessage(&msg);
			if (msg.message == WM_LBUTTONDOWN) {
				for (posx = st_x;posx <= end_x;posx += step) {
					for (posy = st_y;posy <= end_y;posy += step) {
						if (distance(msg.x, msg.y, posx, posy) < 6 && !board[(posx - st_x) / step][(posy - st_y) / step]) {
							IMAGE img;	//画图
							int img_size = 16;
							if (cnt & 1) loadimage(&img, L"D:\\vs_projects\\graph_temp\\White.png", img_size, img_size);
							else loadimage(&img, L"D:\\vs_projects\\graph_temp\\Black.png", img_size, img_size);
							drawAlpha(&img, posx - img_size/2, posy - img_size/2);

							if (cnt & 1) board[(posx - st_x) / step][(posy - st_y) / step] = WHITE; // 1表示白子
							else board[(posx - st_x) / step][(posy - st_y) / step] = BLACK; // -1表示黑子
							cnt++;
							judge_over(posx, posy, board);

							break;
						}
					}
				}
			}
		}
	}
}

void computer_move(int& cnt, int board[cell + 1][cell + 1]) {
	pair<int, int> computer_loc = computer_move_location(board);

}

// 载入PNG图并去透明部分
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //x为载入图片的X坐标，y为Y坐标
{

	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

// 判断数组中落子是否合规
bool is_valid(int x, int y,int board[cell+1][cell+1]) {
	if (x >= 0 && x < cell + 1 && y >= 0 && y < cell + 1 && !board[x][y]) return true;
	else return false;
}

// 判断机器落子位置
pair <int, int> computer_move_location(int board[cell + 1][cell + 1]) {
	for (int x = 0;x <= cell + 1;x++) {
		for (int y = 0;y <= cell + 1;y++) {
			if (is_valid(x, y, board)) {
				// 模拟电脑落子
				board[x][y] = WHITE;
				if (judge_over(x, y, board)) {
					return { x,y };
				}
				board[x][y] = EMPTY;

				// 检查用户
				board[x][y] = BLACK;
				if (judge_over(x, y, board)) {
					return { x,y };
				}
				board[x][y] = EMPTY;
			}
		}
	}

	// 如果没有连子，随机选择空位
	vector<pair<int, int>> empty_cells;
	for (int x = 0;x <= cell + 1;x++) {
		for (int y = 0;y <= cell + 1;y++) {
			if (is_valid(x, y, board)) empty_cells.push_back({ x,y });
		}
	}

	if (!empty_cells.empty()) {
		srand(time(0));
		int index = rand() % empty_cells.size();
		return empty_cells[index];
	}

	// 棋盘已满，无法继续落子
	return { -1,-1 };
}
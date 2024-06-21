#include<iostream>
using namespace std;
#include<graphics.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 650
#define RATIO 50

#define ROW 9
#define COLUMN 12

#define START_X 100
#define START_Y 100


/*
	墙：0，地板：1，箱子目的地：2，
	小人：3，箱子：4，箱子命中目标：5
*/

enum _PROPS {
	WALL,
	FLOOR,
	BOX_DES,
	MAN,
	BOX,
	HIT
};

typedef enum _PROPS PROP;


/*
	墙：0
	地板：1
	箱子目的地：2
	小人：3
	箱子：4
	箱子命中目标：5
*/
int map[ROW][COLUMN]{
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,1,1,1,1,1,1,1,0,0},
	{0,1,4,1,0,2,1,0,2,1,0,0},
	{0,1,0,1,0,1,0,0,1,1,1,0},
	{0,1,0,2,0,1,1,4,1,1,1,0},
	{0,1,1,1,0,3,1,1,1,4,1,0},
	{0,1,2,1,1,4,1,1,1,1,1,0},
	{0,1,0,0,1,0,1,1,0,0,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
};

//图片数组
IMAGE images[6];
IMAGE bg_img;


int main(void) {
	//建github仓库
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);

	//加载背景图片
	loadimage(&bg_img, "blackground.bmp", 0, 0, true);
	//显示背景图片
	putimage(0, 0, &bg_img);

	//加载道具图片
	loadimage(&images[WALL], "wall_right.bmp", RATIO, RATIO, true);
	loadimage(&images[FLOOR], "floor.bmp", RATIO, RATIO, true);
	loadimage(&images[BOX_DES], "des.bmp", RATIO, RATIO, true);
	loadimage(&images[MAN], "man.bmp", RATIO, RATIO, true);
	loadimage(&images[BOX], "box.bmp", RATIO, RATIO, true);
	loadimage(&images[HIT], "box.bmp", RATIO, RATIO, true);


	//显示道具图片
	for (int i = 0;i < ROW;i++) {
		for (int j = 0;j < COLUMN;j++) {
			putimage(START_X+j*RATIO, START_Y+i*RATIO, &images[map[i][j]]);					
		}
	}

	system("pause");
	return 0;
}
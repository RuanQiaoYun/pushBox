#include<iostream>
using namespace std;
#include<graphics.h>
#include<conio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 650
#define RATIO 50

#define ROW 9
#define COLUMN 12

#define START_X 100
#define START_Y 100

#define KEY_UP		'u'
#define KEY_DOWN	'n'
#define KEY_LEFT	'g'
#define KEY_RIGHT	'k'
#define QUIT	'q'

#define isValid(pos) (pos.row >= 0 && pos.row < ROW && pos.col >= 0 && pos.col < COLUMN)

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

enum _DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct _POS {
	int row;	//小人所在的行
	int col;	//小人所在的列
};

typedef enum _PROPS PROP;
typedef enum _DIRECTION DIRECTION;
typedef struct _POS POS;

/*
	墙：0
	地板：1
	箱子目的地：2
	小人：3
	箱子：4
	箱子命中目标：5
*/
int map[ROW][COLUMN]{
	{1,1,1,1,1,1,1,1,1,1,1,1},
	//{0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,0,1,1,1,1,1,1,1,0,1},
	{1,1,4,1,0,2,1,0,2,1,0,1},
	{1,1,0,1,0,1,0,0,1,1,1,1},
	{1,1,0,2,0,1,1,4,1,1,1,1},
	{1,1,1,1,0,3,1,1,1,4,1,1},
	{1,1,2,1,1,4,1,1,1,1,1,1},
	{1,1,0,0,1,0,1,1,0,0,1,1},
	//{0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1},
};

//图片数组
IMAGE images[6];
IMAGE bg_img;

POS man;	//小人实时的位置

void changeMap(POS* pos, PROP prop) {
	//改地图数组
	map[pos->row][pos->col] = prop;

	//显示图片
	putimage(START_X + (pos->col) * RATIO, START_Y + (pos->row) * RATIO, &images[prop]);

}


void gameControl(DIRECTION direction) {
	POS next_pos = man, next_next_pos = man;

	switch (direction) {
	case UP:
	{
		next_pos.row = man.row - 1;
		next_next_pos.row = man.row - 2;
		break;
	}
	case DOWN:
	{
		next_pos.row = man.row + 1;
		next_next_pos.row = man.row + 2;
		break;
	}
	case LEFT:
	{
		next_pos.col = man.col - 1;
		next_next_pos.col = man.col - 2;
		break;
	}
	case RIGHT:
	{
		next_pos.col = man.col + 1;
		next_next_pos.col = man.col + 2;
		break;
	}

	}

	/*
	小人要做出的动作，自己往前走一步？推着箱子走一步？不能走？
	要做出具体的响应
	只处理能走的情况即可，不能走的情况地图不变，即说明小人不能走
	*/

	//小人前面是地板，前面一个变成小人，小人原来的位置变成地板
	if (isValid(next_pos) && map[next_pos.row][next_pos.col] == FLOOR) {
		changeMap(&next_pos, MAN);
		changeMap(&man, FLOOR);
		man = next_pos;
	}

	/*
		小人前面是箱子，判断箱子前面的道具，
		如果是地板，小人推箱子前进一步，
		小人前前面的位置变成箱子，
		箱子原来的位置变成小人，小人原来的位置变成地板
		如果是箱子目的地，小人推箱子前进一步，
		小人前前面的位置变成箱子命中，
		箱子原来的位置变成小人，小人原来的位置变成地板
	*/
	if (isValid(next_pos) && map[next_pos.row][next_pos.col] == BOX) {
		if (isValid(next_next_pos) && map[next_next_pos.row][next_next_pos.col] == FLOOR) {
			changeMap(&next_next_pos, BOX);
			changeMap(&next_pos, MAN);
			changeMap(&man, FLOOR);
			man = next_pos;
		}
		else if (isValid(next_next_pos) && map[next_next_pos.row][next_next_pos.col] == BOX_DES) {
			changeMap(&next_next_pos, HIT);
			changeMap(&next_pos, MAN);
			changeMap(&man, FLOOR);
			man = next_pos;
		}

	}

}

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

	for (int i = 0;i < ROW;i++) {
		for (int j = 0;j < COLUMN;j++) {
			//找小人的位置
			if (map[i][j] == MAN) {
				man.row = i;
				man.col = j;
			}
			//显示道具图片
			putimage(START_X+j*RATIO, START_Y+i*RATIO, &images[map[i][j]]);					
		}
		
	}

	//实现热键控制

	bool quit = false;
	do {
		if (_kbhit()) { //判断键盘是否有输入
			char ch = _getch(); //获取键盘输入，并存入ch变量中
			switch (ch) {
			case KEY_UP:
				gameControl(UP);
				break;
			case KEY_DOWN:
				gameControl(DOWN);
				break;
			case KEY_LEFT:
				gameControl(LEFT);
				break;
			case KEY_RIGHT:
				gameControl(RIGHT);
				break;
			case QUIT:
				quit = true;
				break;
			default:
				break;
			}
		}
		//性能优化
		Sleep(100);

	} while (quit == false);



	system("pause");
	return 0;
}
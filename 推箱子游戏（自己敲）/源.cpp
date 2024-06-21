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
	ǽ��0���ذ壺1������Ŀ�ĵأ�2��
	С�ˣ�3�����ӣ�4����������Ŀ�꣺5
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
	int row;	//С�����ڵ���
	int col;	//С�����ڵ���
};

typedef enum _PROPS PROP;
typedef enum _DIRECTION DIRECTION;
typedef struct _POS POS;

/*
	ǽ��0
	�ذ壺1
	����Ŀ�ĵأ�2
	С�ˣ�3
	���ӣ�4
	��������Ŀ�꣺5
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

//ͼƬ����
IMAGE images[6];
IMAGE bg_img;

POS man;	//С��ʵʱ��λ��

void changeMap(POS* pos, PROP prop) {
	//�ĵ�ͼ����
	map[pos->row][pos->col] = prop;

	//��ʾͼƬ
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
	С��Ҫ�����Ķ������Լ���ǰ��һ��������������һ���������ߣ�
	Ҫ�����������Ӧ
	ֻ�������ߵ�������ɣ������ߵ������ͼ���䣬��˵��С�˲�����
	*/

	//С��ǰ���ǵذ壬ǰ��һ�����С�ˣ�С��ԭ����λ�ñ�ɵذ�
	if (isValid(next_pos) && map[next_pos.row][next_pos.col] == FLOOR) {
		changeMap(&next_pos, MAN);
		changeMap(&man, FLOOR);
		man = next_pos;
	}

	/*
		С��ǰ�������ӣ��ж�����ǰ��ĵ��ߣ�
		����ǵذ壬С��������ǰ��һ����
		С��ǰǰ���λ�ñ�����ӣ�
		����ԭ����λ�ñ��С�ˣ�С��ԭ����λ�ñ�ɵذ�
		���������Ŀ�ĵأ�С��������ǰ��һ����
		С��ǰǰ���λ�ñ���������У�
		����ԭ����λ�ñ��С�ˣ�С��ԭ����λ�ñ�ɵذ�
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
	//��github�ֿ�
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);

	//���ر���ͼƬ
	loadimage(&bg_img, "blackground.bmp", 0, 0, true);
	//��ʾ����ͼƬ
	putimage(0, 0, &bg_img);

	//���ص���ͼƬ
	loadimage(&images[WALL], "wall_right.bmp", RATIO, RATIO, true);
	loadimage(&images[FLOOR], "floor.bmp", RATIO, RATIO, true);
	loadimage(&images[BOX_DES], "des.bmp", RATIO, RATIO, true);
	loadimage(&images[MAN], "man.bmp", RATIO, RATIO, true);
	loadimage(&images[BOX], "box.bmp", RATIO, RATIO, true);
	loadimage(&images[HIT], "box.bmp", RATIO, RATIO, true);

	for (int i = 0;i < ROW;i++) {
		for (int j = 0;j < COLUMN;j++) {
			//��С�˵�λ��
			if (map[i][j] == MAN) {
				man.row = i;
				man.col = j;
			}
			//��ʾ����ͼƬ
			putimage(START_X+j*RATIO, START_Y+i*RATIO, &images[map[i][j]]);					
		}
		
	}

	//ʵ���ȼ�����

	bool quit = false;
	do {
		if (_kbhit()) { //�жϼ����Ƿ�������
			char ch = _getch(); //��ȡ�������룬������ch������
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
		//�����Ż�
		Sleep(100);

	} while (quit == false);



	system("pause");
	return 0;
}
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

typedef enum _PROPS PROP;


/*
	ǽ��0
	�ذ壺1
	����Ŀ�ĵأ�2
	С�ˣ�3
	���ӣ�4
	��������Ŀ�꣺5
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

//ͼƬ����
IMAGE images[6];
IMAGE bg_img;


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


	//��ʾ����ͼƬ
	for (int i = 0;i < ROW;i++) {
		for (int j = 0;j < COLUMN;j++) {
			putimage(START_X+j*RATIO, START_Y+i*RATIO, &images[map[i][j]]);					
		}
	}

	system("pause");
	return 0;
}
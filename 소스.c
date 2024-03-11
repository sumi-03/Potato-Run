#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <conio.h>
#include <Windows.h>

// ����
#include <mmsystem.h>
#include <process.h>
#pragma comment(lib,"winmm.lib")

// ���� ����
#define BLACK   0
#define BLUE1   1
#define GREEN1   2
#define CYAN1   3
#define RED1   4
#define MAGENTA1 5
#define YELLOW1   6
#define GRAY1   7
#define GRAY2   8
#define BLUE2   9
#define GREEN2   10
#define CYAN2   11
#define RED2   12
#define MAGENTA2 13
#define YELLOW2   14
#define WHITE   15


#define SPECIAL1 0xe0 // Ư��Ű�� 0xe0 + key ������ �����ȴ�.
#define SPECIAL2 0x00 // keypad ��� 0x00 + key �� �����ȴ�.
#define UP  0x48 // Up key�� 0xe0 + 0x48 �ΰ��� ���� ���´�.
#define DOWN 0x50

#define BLANK ' '
#define ESC 0x1b

#define WIDTH 82
#define HEIGHT 23

int map1[HEIGHT][WIDTH];
int map2[HEIGHT][WIDTH];
int map3[HEIGHT][WIDTH];
int map4[HEIGHT][WIDTH];
int map5[HEIGHT][WIDTH];
int map6[HEIGHT][WIDTH];

int Delay = 15;// 100 msec delay, �� ���� ���̸� �ӵ��� ��������.
int cnt = 0;
int success = 0;
int monster = 0;

struct block {

	int width;
	int height;
	int color;

};

struct block block;

void gotoxy(int x, int y) //���� ���ϴ� ��ġ�� Ŀ�� �̵�
{
	COORD pos; // Windows.h �� ����
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void textcolor(int fg_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

void removeCursor(void) { // Ŀ���� �Ⱥ��̰� �Ѵ�
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void showCursor(void) { // Ŀ���� ���̰� �Ѵ�
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void cls(int text_color, int bg_color) // ȭ�� �����
{
	char cmd[100];
	system("cls");
	sprintf(cmd, "COLOR %x%x", bg_color, text_color);
	system(cmd);
}

void draw_box2(int x1, int y1, int x2, int y2, char* ch)
{
	int x, y;

	for (x = x1; x <= x2; x += 2) {

		gotoxy(x, y1);
		printf("%s", ch);
		gotoxy(x, y2);
		printf("%s", ch);
	}
	for (y = y1; y <= y2; y++) {

		gotoxy(x1, y);
		printf("%s", ch);
		gotoxy(x2, y);
		printf("%s", ch);
	}
	textcolor(BLACK, WHITE);
}

void draw_box3(int x1, int y1, int x2, int y2, char* ch)
{
	int x;

	for (x = x1; x <= x2; x += 2) {

		gotoxy(x, y1);
		printf("%s", ch);
		gotoxy(x, y2);
		printf("%s", ch);
	}

	textcolor(BLACK, WHITE);
}

void draw_box4(int x1, int y1, int x2, int y2, char* ch) {

	int x, y;
	for (x = x1; x <= x2; x += 4) {

		gotoxy(x, y1);
		printf("%s", ch);
		gotoxy(x, y2);
		printf("%s", ch);
	}

	for (y = y1; y <= y2; y += 2) {

		gotoxy(x1, y);
		printf("%s", ch);
		gotoxy(x2, y);
		printf("%s", ch);
	}
	textcolor(BLACK, WHITE);
}


void draw_text1() {

	textcolor(MAGENTA2, WHITE);

	gotoxy(13, 5);
	printf("����    ����    ����    ����    ����    ����");
	gotoxy(13, 6);
	printf("��  ��    ��  ��      ��      ��  ��      ��      ��  ��");
	gotoxy(13, 7);
	printf("����    ��  ��      ��      ����      ��      ��  ��");
	gotoxy(13, 8);
	printf("��        ��  ��      ��      ��  ��      ��      ��  ��");
	gotoxy(13, 9);
	printf("��        ����      ��      ��  ��      ��      ����");

	textcolor(MAGENTA1, WHITE);

	gotoxy(23, 12);
	printf("�����     ��    ��     ��      ��");
	gotoxy(23, 13);
	printf("��    ��     ��    ��     ���    ��");
	gotoxy(23, 14);
	printf("����       ��    ��     ��  ��  ��");
	gotoxy(23, 15);
	printf("��    ��     ��    ��     ��    ���");
	gotoxy(23, 16);
	printf("��    ��     �����     ��      ��");

}

void draw_text2() {

	textcolor(MAGENTA1, WHITE);

	gotoxy(13, 5);
	printf("����    ����    ����    ����    ����    ����");
	gotoxy(13, 6);
	printf("��  ��    ��  ��      ��      ��  ��      ��      ��  ��");
	gotoxy(13, 7);
	printf("����    ��  ��      ��      ����      ��      ��  ��");
	gotoxy(13, 8);
	printf("��        ��  ��      ��      ��  ��      ��      ��  ��");
	gotoxy(13, 9);
	printf("��        ����      ��      ��  ��      ��      ����");

	textcolor(MAGENTA2, WHITE);

	gotoxy(23, 12);
	printf("�����     ��    ��     ��      ��");
	gotoxy(23, 13);
	printf("��    ��     ��    ��     ���    ��");
	gotoxy(23, 14);
	printf("����       ��    ��     ��  ��  ��");
	gotoxy(23, 15);
	printf("��    ��     ��    ��     ��    ���");
	gotoxy(23, 16);
	printf("��    ��     �����     ��      ��");

}

void effect1() {

	int i;

	i = 0;
	textcolor(GREEN1, WHITE);
	Sleep(100);
	draw_box2(i * 2, i, 80 - i * 2, 22 - i, "��");

	i = 1;
	textcolor(GRAY1, WHITE);
	Sleep(100);
	draw_box2(i * 2, i, 80 - i * 2, 22 - i, "��");

	i = 2;
	textcolor(YELLOW1, WHITE);
	Sleep(100);
	draw_box3(i * 2, i, 80 - i * 2, 22 - i, "��");

	draw_text1();

	i = 1;
	textcolor(RED1, WHITE);
	Sleep(100);
	draw_box4(i * 2, i, 80 - i * 2, 22 - i, "��");



	i = 0;
	textcolor(WHITE, GREEN1);
	Sleep(100);
	draw_box2(i * 2, i, 80 - i * 2, 22 - i, "��");

	i = 1;
	textcolor(GRAY1, WHITE);
	Sleep(100);
	draw_box2(i * 2, i, 80 - i * 2, 22 - i, "��");

	i = 2;
	textcolor(YELLOW1, WHITE);
	Sleep(100);
	draw_box3(i * 2, i, 80 - i * 2, 22 - i, "��");

	gotoxy(29, 18);
	textcolor(BLACK, WHITE);
	printf("�� �ƹ� Ű�� �������� ��");
	fflush(stdin);
	i = 1;
	textcolor(BLACK, WHITE);
	Sleep(100);
	draw_box4(i * 2, i, 80 - i * 2, 22 - i, "��");

	draw_text2();


}

void effect2() {

	int i = 0;
	textcolor(WHITE, GREEN1);
	Sleep(100);
	draw_box2(i * 2, i, 80 - i * 2, 22 - i, "��");
	Sleep(500);

}

void info() {

	gotoxy(8, 3);
	textcolor(RED1, WHITE);
	printf("��");
	textcolor(BLACK, WHITE);
	Sleep(100);

	printf(" ��"); Sleep(100); printf("�� "); Sleep(100); printf("��"); Sleep(100); printf("��"); Sleep(500);


	printf(" (�ǳʶٷ��� �ƹ� Ű�� ��������)");

	Sleep(500);

	unsigned  char* string1 = { "���ΰ� �������䰡 �Ǿ�����(Up key)�� �ٿ�(Dn key)�� ������ �����Ͽ� ��ֹ��� ���ϸ� ���������̾ Ż���ϴ� ����" };
	unsigned char* string2 = { "���� 7�� ����, �������� ������ 3 ���� (�ִ� 10)���� ��ֹ��� �ε��� ��� ���� 1 ���ұ����� ��ô�ϴ� �ҵ��̿� ������ ���� 1 ���һ����� 0 �� �Ǳ� �� ���������̾ Ż���ϸ� ����Ż�� ���� ������ ����" };

	int len = strlen(string1);
	gotoxy(12, 6);
	getch();

	for (int i = 0; i < len; i += 2) {

		if (kbhit() == 1) {
			getch();
			gotoxy(12, 6);  printf("                                           ");
			gotoxy(12, 6);  printf("���ΰ� �������䰡 �Ǿ�");
			gotoxy(12, 8); printf("                                                         ");
			gotoxy(12, 8); printf("����(Up key)�� �ٿ�(Dn key)�� ������ �����Ͽ�");
			gotoxy(12, 10); printf("                                                         ");
			gotoxy(12, 10); printf("��ֹ��� ���ϸ� ���������̾ Ż���ϴ� ����");
			break;
		}

		if (i == 22) { gotoxy(12, 8); }
		if (i == 68) { gotoxy(12, 10); }
		printf("%c%c", string1[i], string1[i + 1]);
		Sleep(40);
	}
	Sleep(1000);

	gotoxy(12, 6);
	textcolor(WHITE, WHITE);
	printf("                                                              ");
	gotoxy(12, 8);
	printf("                                                              ");
	gotoxy(12, 10);
	printf("                                                              ");
	Sleep(800);
	textcolor(BLACK, WHITE);

	len = strlen(string2);
	gotoxy(12, 6);

	for (int i = 0; i < len; i += 2) {

		if (kbhit() == 1) {
			getch();
			textcolor(BLACK, WHITE);
			gotoxy(12, 6);
			printf("                                                   ");
			gotoxy(12, 6);
			printf("���� 7�� ����, �������� ������ 3 ���� (�ִ� 10)");
			gotoxy(12, 8);
			printf("                                                ");
			gotoxy(12, 8);
			printf("���� ��ֹ��� �ε��� ��� ���� 1 ����");
			gotoxy(12, 10);
			printf("                                                             ");
			gotoxy(12, 10);
			printf("������ ��ô�ϴ� �ҵ��̿� ������ ���� 1 ����");
			gotoxy(15, 15);
			printf("                                                     ");
			textcolor(BLUE1, YELLOW2);
			gotoxy(15, 15);
			printf("������ 0 �� �Ǳ� �� ���������̾ Ż���ϸ� ����");
			textcolor(WHITE, WHITE);
			gotoxy(15, 17);
			printf("                                           ");
			textcolor(BLUE1, YELLOW2);
			gotoxy(15, 17);
			printf("Ż�� ���� ������ ����");

			break;
		}

		if (i == 50) { gotoxy(12, 8); } // 42

		if (i == 86) { gotoxy(12, 10); }
		if (i == 130) { textcolor(BLUE1, YELLOW2); gotoxy(15, 15); }
		if (i == 178) { gotoxy(15, 17); }
		printf("%c%c", string2[i], string2[i + 1]);
		Sleep(40);
	}
	Sleep(1000);
}

void start() {

	textcolor(WHITE, WHITE);
	gotoxy(8, 3);
	printf("                                                              ");
	gotoxy(12, 6);
	printf("                                                              ");
	gotoxy(12, 8);
	printf("                                                              ");
	gotoxy(12, 10);
	printf("                                                              ");
	gotoxy(12, 12);
	printf("                                                              ");
	gotoxy(15, 15);
	printf("                                                              ");
	gotoxy(15, 17);
	printf("                                                              ");

	int timer = 4;
	clock_t start, now, remain;
	clock_t duration, sec, min, hour, milsec;
	timer *= 1000;
	start = clock();

	while (1) {

		now = clock();
		// ������ �ð�
		duration = now - start;
		// ���� �ð�
		remain = timer - duration;
		// ���� �ð� ���
		sec = remain / CLOCKS_PER_SEC;
		sec %= 60;


		textcolor(BLACK, YELLOW2);

		if (sec == 3) {


			gotoxy(40, 7);
			printf("3");

		}
		if (sec == 2) {

			gotoxy(40, 7);
			printf("2");
		}

		if (sec == 1) {

			gotoxy(40, 7);
			printf("1");
		}

		if (sec == 0) {

			gotoxy(38, 7);
			printf("START");
		}
		if (remain == 0) {
			break;
		}
	}
	Sleep(100);
	gotoxy(38, 7);
	textcolor(WHITE, WHITE);
	printf("     ");

}

void putpotato(int x, int y)
{
	textcolor(YELLOW1, WHITE);
	gotoxy(x, y);
	printf("��");
}
void erasepotato(int x, int y)
{
	textcolor(WHITE, WHITE);
	gotoxy(x, y);
	putchar(BLANK);
}

int block_x = 78;
int block_y = 17;
int block_x2 = 78;
int block_y2 = 17;
int block_x3 = 78;
int block_y3 = 17;
int block_x4 = 78;
int block_y4;
int block_x5 = 78;
int block_y5 = 11;

int oh1 = 3;
int oh2 = 4;
int oh3 = 5;

void init_map_all() {
	int i, j;
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			// map1�� �ʱ�ȭ�ϸ� �ȵ�
			map2[i][j] = 0;
			map3[i][j] = 0;
			map4[i][j] = 0;
			map5[i][j] = 0;
			map6[i][j] = 0;
		}
	}

}
void init_block1(int oh)
{
	for (int i = block_y + 4 - oh; i <= block_y + 4; i++) {
		map2[i][block_x] = 1;
	}

}

void init_block2(int oh2)
{

	for (int i = block_y2 + 4 - oh2; i <= block_y2 + 4; i++) {
		map3[i][block_x2] = 1;
	}

}

void init_block3(int oh3)
{

	for (int i = block_y3 + 4 - oh3; i <= block_y3 + 4; i++) {
		map6[i][block_x3] = 1;
	}

}

void init_monster() {

	map4[10][block_x4] = 1;
}

void 	init_fire() {
	map5[block_y5][block_x5] = 1;
}

void show_life() // ����
{
	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map1[y][x] == 1) {
				gotoxy(x, y);
				textcolor(RED1, WHITE);
				printf("��");
			}
		}
	}
}

void show_block1() // ��ֹ� 1
{
	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map2[y][x] == 1) {
				gotoxy(x, y);
				printf("��");
			}
		}
	}
}

void show_block2() // ��ֹ� 2
{
	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map3[y][x] == 1) {
				gotoxy(x, y);
				printf("��");
			}
		}
	}
}

void show_block3() { // ��ֹ� 3

	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map6[y][x] == 1) {
				gotoxy(x, y);
				printf("��");
			}
		}
	}

}

void show_monster() { // ��������

	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map4[y][x] == 1) {
				gotoxy(x, y);
				textcolor(BLACK, WHITE);
				if (block_x4 < 56) { textcolor(WHITE, WHITE); }
				printf("��");
			}
		}
	}
}
void show_fire() { // �ҵ��̵���

	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map5[y][x] == 1) {
				gotoxy(x, y);
				textcolor(RED2, WHITE);
				printf("��");
			}
		}
	}


}
void erase_block1()
{
	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map2[y][x] == 1) {
				gotoxy(x, y);
				printf(" ");
			}
		}
	}

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {

			map2[j][i] = 0;
		}
	}

}

void erase_block2()
{
	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map3[y][x] == 1) {
				gotoxy(x, y);
				printf(" ");
			}
		}
	}

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {

			map3[j][i] = 0;
		}
	}
}

void erase_block3()
{
	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map6[y][x] == 1) {
				gotoxy(x, y);
				printf(" ");
			}
		}
	}

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {

			map6[j][i] = 0;
		}
	}
}

void erase_monster()
{
	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map4[y][x] == 1) {
				gotoxy(x, y);
				printf(" ");
			}
		}
	}

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			map4[j][i] = 0;
		}
	}
}

void erase_fire() {

	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map5[y][x] == 1) {
				gotoxy(x, y);
				printf(" ");
			}
		}
	}

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			map5[j][i] = 0;
		}
	}
}
void move_block1(int dx, int dy, int count1)
{

	erase_block1();
	block_x += dx;

	if (block_x == 1) {

		block_x = WIDTH - 4;
	}

	if (count1 % 77 == 0) {

		srand(time(NULL));
		oh1 = rand() % 5 + 1;
	}

	init_block1(oh1);
	show_block1();

}

void move_block2(int dx, int dy, int count2)
{

	erase_block2();
	block_x2 += dx;

	if (block_x2 == 1) {

		block_x2 = WIDTH - 4;

	}

	if (count2 % 77 == 0) {

		srand(time(NULL));
		oh2 = rand() % 6 + 2;
	}

	init_block2(oh2);
	show_block2();

}

void move_block3(int dx, int dy, int count3) { // 3��° ��ֹ�

	erase_block3();
	block_x3 += dx;

	if (block_x3 == 1) {

		block_x3 = WIDTH - 4;

	}

	if (count3 % 77 == 0) {

		srand(time(NULL));
		oh3 = rand() % 5 + 2;
	}

	init_block3(oh3);
	show_block3();
}

void 	move_fire(int dx, int dy, int count) {

	erase_fire();
	block_x5 += dx;
	block_y5 += dy;

	if (block_y5 == 22) {

		block_y5 = 11;
		block_x5 = block_x4;//

		monster = 0;
	}
	if (block_x5 == 1) {
		block_x5 = WIDTH - 4;
		monster = 0;
	}
	else { monster = 1; }

	if (block_x4 > 56) {

		init_fire();
		show_fire();
	}
}

void move_monster(int dx, int dy, int count)
{
	erase_monster();

	block_x4 += dx;

	if (block_x4 == 1) {

		block_x4 = WIDTH - 4;

		monster = 0;
	}
	else {

		monster = 1;
	}

	init_monster();
	show_monster();
}

void show_heart(int myheart) {
	textcolor(RED1, WHITE);
	gotoxy(6, 2); printf("                                              "); gotoxy(6, 2); for (int i = 0; i < myheart / 2; i++) printf("��");
	gotoxy(6, 5); printf("    "); gotoxy(6, 5); textcolor(RED1, WHITE); printf("%2d", myheart / 2);
}

void end_block1() {

	textcolor(MAGENTA1, WHITE);

	gotoxy(13, 5);
	printf("�����      ��");
	gotoxy(13, 6);
	printf("��    ��      �� ");
	gotoxy(13, 7);
	printf("��    ��      �����");
	gotoxy(13, 8);
	printf("��    ��      ��    �� ");
	gotoxy(13, 9);
	printf("�����      ��    ��       ��       ��       ��");

	textcolor(MAGENTA2, WHITE);

	gotoxy(23, 12);
	printf("�����      ��      ��      ����");
	gotoxy(23, 13);
	printf("��            ���    ��      ��    ��");
	gotoxy(23, 14);
	printf("�����      ��  ��  ��      ��    ��");
	gotoxy(23, 15);
	printf("��            ��    ���      ��    ��");
	gotoxy(23, 16);
	printf("�����      ��      ��      ����");

}

void end_block2() {

	textcolor(MAGENTA1, WHITE);

	gotoxy(15, 5);
	printf("�����      �����      �����      ����");
	gotoxy(15, 6);
	printf("��            ��    ��      ��    ��      ��    ��");
	gotoxy(15, 7);
	printf("��  ���      ��    ��      ��    ��      ��    ��");
	gotoxy(15, 8);
	printf("��    ��      ��    ��      ��    ��      ��    ��");
	gotoxy(15, 9);
	printf("�����      �����      �����      ����");

	textcolor(MAGENTA2, WHITE);

	gotoxy(25, 12);
	printf("�����    �����     �����");
	gotoxy(25, 13);
	printf("    ��      ��    ��     ��    ��");
	gotoxy(25, 14);
	printf("    ��      ��    ��     ����");
	gotoxy(25, 15);
	printf("    ��      ��    ��     ��    ��");
	gotoxy(25, 16);
	printf("����      �����     �����");
}

int end_restart() {

	cls(BLACK, WHITE);
	effect2();
	gotoxy(16, 10);
	textcolor(BLUE1, YELLOW2);
	printf("�ٽ��Ϸ��� UpŰ��, �����Ϸ��� Dn Ű�� ��������");
	unsigned char ch = 0;

	while (1) {
		if (kbhit() == 1) {  // Ű���尡 ������ ������
			ch = getch(); // key ���� �д´�
			if (ch == SPECIAL1 || ch == SPECIAL2) { // ���� Ư��Ű
				ch = getch();
				switch (ch) {
				case UP: return 1;
				case DOWN: return 0;
				}
			}
		}
	}
}

int count = 0;
int count2 = 0;
int count3 = 0;

int main()
{

	unsigned char ch = 0;

	int cnt = 0;
	int plus = 0;
	int oldx, oldy, newx, newy;
	int keep_moving = 0;

	int myheartck = 0; // ���� ����
	int myheart = 14; // ���� ���� 
	// ��ֹ��� ��ĭ �����̰� �ε������� Ȯ���ϰ� ��ĭ �����̰� Ȯ���ϰ� �ݺ� �ϴµ�, 
	// ��ֹ��� ��ĭ�̾ �ѹ� �ε����� ������ 2�� �پ��, �׷��� 7�ǵι� 14�� ������

	map1[2][6] = 1;
	map1[2][8] = 1;
	map1[2][10] = 1;
	map1[2][12] = 1;
	map1[2][14] = 1;
	map1[2][16] = 1;
	map1[2][18] = 1;

	newx = oldx = 20;
	newy = oldy = HEIGHT - 2;
	removeCursor(); // Ŀ���� �Ⱥ��̰� �Ѵ�



	while (kbhit() != 1) { // ������ ���� ����

		effect1();
	}

	cls(BLACK, WHITE);

	effect2();

	info();

	while (1) {
		init_map_all();
		start();

		cnt = 0;
		monster = 0;// 
		count = 0; // ��ֹ�1 �ѹ� �Ű����� count 1���� 
		count2 = 0;
		count3 = 0;
		block_x = 78;
		block_y = 17;
		block_x2 = 78;
		block_y2 = 17;
		block_x4 = 78;
		block_y4;
		block_x5 = 78;
		block_y5 = 11;
		block_x3 = 78;
		block_y3 = 17;



		oh1 = 3;
		oh2 = 4;
		oh3 = 5;

		init_block1(oh1);
		init_block2(oh2);
		init_block3(oh3);
		init_monster();
		init_fire();

		show_life();
		myheart = 14;
		gotoxy(6, 5); printf("%2d", myheart / 2);

		textcolor(MAGENTA1, WHITE);
		show_block1();

		putpotato(oldx, oldy);

		int x = 19;
		int bonus = 14; // ������
		while (1) {

			if (kbhit() == 1) {  // Ű���尡 ������ ������
				ch = getch(); // key ���� �д´�

				if (ch == SPECIAL1 || ch == SPECIAL2) { // ���� Ư��Ű

					ch = getch();
					switch (ch) {
					case UP:
					case DOWN:

						keep_moving = 1;
						break;

					}
				}
			}
			if (keep_moving && cnt % 2 == 0) { // �����̰� ������

				switch (ch) {
				case UP:
					if (oldy > (HEIGHT - 10)) {
						newy = oldy - 1;
					}
					else {
						newy = HEIGHT - 10;
						ch = DOWN;
					}

					break;
				case DOWN:
					if (oldy < HEIGHT - 2)
						newy = oldy + 1;
					else
						keep_moving = 0;

					break;

				}

				erasepotato(oldx, oldy); // ������ ��ġ�� * �� �����
				putpotato(newx, newy); // ���ο� ��ġ���� * �� ǥ���Ѵ�.
				oldx = newx; // ������ ��ġ�� ����Ѵ�.
				oldy = newy;
				keep_moving = 1; //1:����̵�, 0:�ѹ��� ��ĭ���̵�
			}

			///////////////////////////////////////////////////////////////////////////////////////
			for (int i = block_y + 4 - oh1; i <= block_y + 4; i++) {

				if (block_x == oldx && i == oldy) {

					PlaySound(TEXT("Minus.wav"), 0, SND_FILENAME | SND_ASYNC); // ����
					myheartck = 1;
				}
			}

			if (myheartck == 1) {

				// ��ֹ��� ��ĭ �����̰� Ȯ���ϰ� ��ĭ �����̰� Ȯ���ϰ� �ϴµ�, 
				// ��ֹ��� ��ĭ�̾ -2�� �ع����� ������ 2�� �پ��
				myheart -= 1;
				show_heart(myheart);
				myheartck = 0;
			}

			if (myheart / 2 == 0) {
				break;
			}
			/////////////////////////////////////////////////////////////////////////////////////////

			textcolor(MAGENTA1, WHITE);
			move_block1(-1, 0, count);
			count++; // ��ֹ�1 �ѹ� �Ű����� count 1����

			for (int i = block_y + 4 - oh1; i <= block_y + 4; i++) {

				if (block_x == oldx && i == oldy) {

					PlaySound(TEXT("Minus.wav"), 0, SND_FILENAME | SND_ASYNC); // ����
					myheartck = 1;
				}
			}

			if (myheartck == 1) {

				myheart -= 1;
				show_heart(myheart);

				myheartck = 0;
			}

			if (myheart / 2 == 0) {
				break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////
			if (count == 25) {

				show_block2();

			}


			for (int i = block_y2 + 4 - oh2; i <= block_y2 + 4; i++) {
				if (block_x2 == oldx && i == oldy) {

					PlaySound(TEXT("Minus.wav"), 0, SND_FILENAME | SND_ASYNC); // ����
					myheartck = 1;

				}
			}
			if (myheartck == 1) {

				myheart -= 1;
				show_heart(myheart);
				myheartck = 0;
			}

			if (myheart / 2 == 0) {
				break;
			}
			////////////////////////////////////////////////////////////////////////////////////////////
			if (count == 60) {

				show_block3();
			}

			for (int i = block_y3 + 4 - oh3; i <= block_y3 + 4; i++) {
				if (block_x3 == oldx && i == oldy) {

					PlaySound(TEXT("Minus.wav"), 0, SND_FILENAME | SND_ASYNC); // ����
					myheartck = 1;

				}
			}
			if (myheartck == 1) {

				myheart -= 1;
				show_heart(myheart);
				myheartck = 0;
			}

			if (myheart / 2 == 0) {
				break;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////
			if (count > 25) {
				textcolor(MAGENTA1, WHITE);
				move_block2(-1, 0, count2);
				count2++;
			}

			for (int i = block_y2 + 4 - oh2; i <= block_y2 + 4; i++) {
				if (block_x2 == oldx && i == oldy) {

					PlaySound(TEXT("Minus.wav"), 0, SND_FILENAME | SND_ASYNC); // ����
					myheartck = 1;

				}
			}

			if (myheartck == 1) {

				myheart -= 1;
				show_heart(myheart);
				myheartck = 0;
			}

			if (myheart / 2 == 0) {
				break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////
			if (count > 60) {
				textcolor(MAGENTA1, WHITE);
				move_block3(-1, 0, count3);
				count3++;
			}

			for (int i = block_y3 + 4 - oh3; i <= block_y3 + 4; i++) {
				if (block_x3 == oldx && i == oldy) {

					PlaySound(TEXT("Minus.wav"), 0, SND_FILENAME | SND_ASYNC); // ����
					myheartck = 1;

				}
			}

			if (myheartck == 1) {

				myheart -= 1;
				show_heart(myheart);
				myheartck = 0;
			}

			if (myheart / 2 == 0) {
				break;
			}
			////////////////////////////////////////////////////////////////////////////////////////////
			if (monster != 1 && cnt % 40 == 0) { // ������ �ҵ��� ���̰�
				show_monster();
				show_fire();//

				monster = 1;
			}


			if (block_x5 == oldx && block_y5 == oldy) { // �������䰡 �¾Ҵ��� Ȯ���ϰ�

				PlaySound(TEXT("Minus.wav"), 0, SND_FILENAME | SND_ASYNC); // ����
				myheartck = 1;

			}

			if (myheartck == 1) {

				myheart -= 1;
				show_heart(myheart);
				myheartck = 0;
			}

			if (myheart / 2 == 0) {
				break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////
			if (monster == 1 && cnt % 3 == 0) { // ������  �ҵ��� �����̰�
				move_monster(-1, 0, count);
				move_fire(-6, 1, count);
			}

			if (block_x5 == oldx && block_y5 == oldy) { // �������䰡 �¾Ҵ��� Ȯ���ϰ�

				PlaySound(TEXT("Minus.wav"), 0, SND_FILENAME | SND_ASYNC); // ����
				myheartck = 1;

			}

			if (myheartck == 1) {

				myheart -= 1;
				show_heart(myheart);
				myheartck = 0;
			}

			if (myheart / 2 == 0) {
				break;
			}
			///////////////////////////////////////////////////////////////////////////////////////////
			if (cnt % 200 == 0) { // ������ ����
				bonus = rand() % 3 + 13;
				gotoxy(20, bonus);
				textcolor(BLUE1, WHITE);
				printf("��");
				plus = 1;

			}

			// ������ ���� ���
			if (oldx == 20 && oldy == bonus && plus == 1) { // plus�߰�, ��Ʈ�� �ѹ��� 6���� �þ�°� ����

				if (myheart <= 14) {
					PlaySound(TEXT("Plus.wav"), 0, SND_FILENAME | SND_ASYNC); // ����
					plus = 0;
					myheart += 6;
					show_heart(myheart);

				}
				else if (myheart == 16) {
					PlaySound(TEXT("Plus.wav"), 0, SND_FILENAME | SND_ASYNC); // ����
					plus = 0;
					myheart += 4;
					show_heart(myheart);

				}
				else if (myheart == 18) {
					PlaySound(TEXT("Plus.wav"), 0, SND_FILENAME | SND_ASYNC); // ����
					plus = 0;
					myheart += 2;
					show_heart(myheart);

				}
				else if (myheart > 18) {
					PlaySound(TEXT("Plus.wav"), 0, SND_FILENAME | SND_ASYNC); // ����
				}

			}

			// ������ ���ֱ�
			if ((cnt - 7) % 200 == 0 || (oldx == 20 && oldy == 12)) {
				gotoxy(20, bonus);
				textcolor(WHITE, WHITE);
				printf(" ");
				bonus = 0;
			}

			if (cnt == 2000) {
				success = 1;
				break;
			}

			Sleep(Delay); // Delay�� ���̸� �ӵ��� ������
			cnt++;
		}

		cls(BLACK, WHITE);
		effect2();

		if (success == 0) {
			end_block1();
			Sleep(1000);
			if (end_restart() == 0) {

				gotoxy(16, 10);
				textcolor(WHITE, WHITE);
				printf("                                                               ");
				textcolor(BLACK, WHITE);
				break;
			}
			else {
				cnt = 0;
				gotoxy(16, 10);
				textcolor(WHITE, WHITE);
				printf("                                                               ");
			}
		}
		else if (success == 1) {

			end_block2();
			Sleep(1000);

			if (end_restart() == 0) {
				gotoxy(16, 10);
				textcolor(WHITE, WHITE);
				printf("                                                               ");
				textcolor(BLACK, WHITE);
				break;
			}
			else {
				cnt = 0;
				gotoxy(16, 10);
				textcolor(WHITE, WHITE);
				printf("                                                               ");

			}
		}
	}
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <conio.h>
#include <Windows.h>

// 음향
#include <mmsystem.h>
#include <process.h>
#pragma comment(lib,"winmm.lib")

// 색상 정의
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


#define SPECIAL1 0xe0 // 특수키는 0xe0 + key 값으로 구성된다.
#define SPECIAL2 0x00 // keypad 경우 0x00 + key 로 구성된다.
#define UP  0x48 // Up key는 0xe0 + 0x48 두개의 값이 들어온다.
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

int Delay = 15;// 100 msec delay, 이 값을 줄이면 속도가 빨라진다.
int cnt = 0;
int success = 0;
int monster = 0;

struct block {

	int width;
	int height;
	int color;

};

struct block block;

void gotoxy(int x, int y) //내가 원하는 위치로 커서 이동
{
	COORD pos; // Windows.h 에 정의
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void textcolor(int fg_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

void removeCursor(void) { // 커서를 안보이게 한다
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void showCursor(void) { // 커서를 보이게 한다
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void cls(int text_color, int bg_color) // 화면 지우기
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
	printf("■■■    ■■■    ■■■    ■■■    ■■■    ■■■");
	gotoxy(13, 6);
	printf("■  ■    ■  ■      ■      ■  ■      ■      ■  ■");
	gotoxy(13, 7);
	printf("■■■    ■  ■      ■      ■■■      ■      ■  ■");
	gotoxy(13, 8);
	printf("■        ■  ■      ■      ■  ■      ■      ■  ■");
	gotoxy(13, 9);
	printf("■        ■■■      ■      ■  ■      ■      ■■■");

	textcolor(MAGENTA1, WHITE);

	gotoxy(23, 12);
	printf("■■■■     ■    ■     ■      ■");
	gotoxy(23, 13);
	printf("■    ■     ■    ■     ■■    ■");
	gotoxy(23, 14);
	printf("■■■       ■    ■     ■  ■  ■");
	gotoxy(23, 15);
	printf("■    ■     ■    ■     ■    ■■");
	gotoxy(23, 16);
	printf("■    ■     ■■■■     ■      ■");

}

void draw_text2() {

	textcolor(MAGENTA1, WHITE);

	gotoxy(13, 5);
	printf("■■■    ■■■    ■■■    ■■■    ■■■    ■■■");
	gotoxy(13, 6);
	printf("■  ■    ■  ■      ■      ■  ■      ■      ■  ■");
	gotoxy(13, 7);
	printf("■■■    ■  ■      ■      ■■■      ■      ■  ■");
	gotoxy(13, 8);
	printf("■        ■  ■      ■      ■  ■      ■      ■  ■");
	gotoxy(13, 9);
	printf("■        ■■■      ■      ■  ■      ■      ■■■");

	textcolor(MAGENTA2, WHITE);

	gotoxy(23, 12);
	printf("■■■■     ■    ■     ■      ■");
	gotoxy(23, 13);
	printf("■    ■     ■    ■     ■■    ■");
	gotoxy(23, 14);
	printf("■■■       ■    ■     ■  ■  ■");
	gotoxy(23, 15);
	printf("■    ■     ■    ■     ■    ■■");
	gotoxy(23, 16);
	printf("■    ■     ■■■■     ■      ■");

}

void effect1() {

	int i;

	i = 0;
	textcolor(GREEN1, WHITE);
	Sleep(100);
	draw_box2(i * 2, i, 80 - i * 2, 22 - i, "●");

	i = 1;
	textcolor(GRAY1, WHITE);
	Sleep(100);
	draw_box2(i * 2, i, 80 - i * 2, 22 - i, "■");

	i = 2;
	textcolor(YELLOW1, WHITE);
	Sleep(100);
	draw_box3(i * 2, i, 80 - i * 2, 22 - i, "★");

	draw_text1();

	i = 1;
	textcolor(RED1, WHITE);
	Sleep(100);
	draw_box4(i * 2, i, 80 - i * 2, 22 - i, "♥");



	i = 0;
	textcolor(WHITE, GREEN1);
	Sleep(100);
	draw_box2(i * 2, i, 80 - i * 2, 22 - i, "◆");

	i = 1;
	textcolor(GRAY1, WHITE);
	Sleep(100);
	draw_box2(i * 2, i, 80 - i * 2, 22 - i, "●");

	i = 2;
	textcolor(YELLOW1, WHITE);
	Sleep(100);
	draw_box3(i * 2, i, 80 - i * 2, 22 - i, "♥");

	gotoxy(29, 18);
	textcolor(BLACK, WHITE);
	printf("◀ 아무 키나 누르세요 ▶");
	fflush(stdin);
	i = 1;
	textcolor(BLACK, WHITE);
	Sleep(100);
	draw_box4(i * 2, i, 80 - i * 2, 22 - i, "★");

	draw_text2();


}

void effect2() {

	int i = 0;
	textcolor(WHITE, GREEN1);
	Sleep(100);
	draw_box2(i * 2, i, 80 - i * 2, 22 - i, "◆");
	Sleep(500);

}

void info() {

	gotoxy(8, 3);
	textcolor(RED1, WHITE);
	printf("♥");
	textcolor(BLACK, WHITE);
	Sleep(100);

	printf(" 게"); Sleep(100); printf("임 "); Sleep(100); printf("설"); Sleep(100); printf("명"); Sleep(500);


	printf(" (건너뛰려면 아무 키나 누르세요)");

	Sleep(500);

	unsigned  char* string1 = { "주인공 포테이토가 되어점프(Up key)와 다운(Dn key)을 적절히 선택하여 장애물을 피하며 에어프라이어를 탈출하는 게임" };
	unsigned char* string2 = { "생명 7로 시작, 생명물약을 먹으면 3 증가 (최대 10)고정 장애물에 부딪힐 경우 생명 1 감소괴물이 투척하는 불덩이에 맞으면 생명 1 감소생명이 0 이 되기 전 에어프라이어를 탈출하면 성공탈출 전에 죽으면 실패" };

	int len = strlen(string1);
	gotoxy(12, 6);
	getch();

	for (int i = 0; i < len; i += 2) {

		if (kbhit() == 1) {
			getch();
			gotoxy(12, 6);  printf("                                           ");
			gotoxy(12, 6);  printf("주인공 포테이토가 되어");
			gotoxy(12, 8); printf("                                                         ");
			gotoxy(12, 8); printf("점프(Up key)와 다운(Dn key)을 적절히 선택하여");
			gotoxy(12, 10); printf("                                                         ");
			gotoxy(12, 10); printf("장애물을 피하며 에어프라이어를 탈출하는 게임");
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
			printf("생명 7로 시작, 생명물약을 먹으면 3 증가 (최대 10)");
			gotoxy(12, 8);
			printf("                                                ");
			gotoxy(12, 8);
			printf("고정 장애물에 부딪힐 경우 생명 1 감소");
			gotoxy(12, 10);
			printf("                                                             ");
			gotoxy(12, 10);
			printf("괴물이 투척하는 불덩이에 맞으면 생명 1 감소");
			gotoxy(15, 15);
			printf("                                                     ");
			textcolor(BLUE1, YELLOW2);
			gotoxy(15, 15);
			printf("생명이 0 이 되기 전 에어프라이어를 탈출하면 성공");
			textcolor(WHITE, WHITE);
			gotoxy(15, 17);
			printf("                                           ");
			textcolor(BLUE1, YELLOW2);
			gotoxy(15, 17);
			printf("탈출 전에 죽으면 실패");

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
		// 지나간 시간
		duration = now - start;
		// 남은 시간
		remain = timer - duration;
		// 남은 시간 출력
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
	printf("●");
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
			// map1은 초기화하면 안됨
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

void show_life() // 생명
{
	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map1[y][x] == 1) {
				gotoxy(x, y);
				textcolor(RED1, WHITE);
				printf("♥");
			}
		}
	}
}

void show_block1() // 장애물 1
{
	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map2[y][x] == 1) {
				gotoxy(x, y);
				printf("◆");
			}
		}
	}
}

void show_block2() // 장애물 2
{
	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map3[y][x] == 1) {
				gotoxy(x, y);
				printf("◆");
			}
		}
	}
}

void show_block3() { // 장애물 3

	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map6[y][x] == 1) {
				gotoxy(x, y);
				printf("◆");
			}
		}
	}

}

void show_monster() { // 괴물등장

	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map4[y][x] == 1) {
				gotoxy(x, y);
				textcolor(BLACK, WHITE);
				if (block_x4 < 56) { textcolor(WHITE, WHITE); }
				printf("Œ");
			}
		}
	}
}
void show_fire() { // 불덩이등장

	int x, y;
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			if (map5[y][x] == 1) {
				gotoxy(x, y);
				textcolor(RED2, WHITE);
				printf("▲");
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

void move_block3(int dx, int dy, int count3) { // 3번째 장애물

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
	gotoxy(6, 2); printf("                                              "); gotoxy(6, 2); for (int i = 0; i < myheart / 2; i++) printf("♥");
	gotoxy(6, 5); printf("    "); gotoxy(6, 5); textcolor(RED1, WHITE); printf("%2d", myheart / 2);
}

void end_block1() {

	textcolor(MAGENTA1, WHITE);

	gotoxy(13, 5);
	printf("■■■■      ■");
	gotoxy(13, 6);
	printf("■    ■      ■ ");
	gotoxy(13, 7);
	printf("■    ■      ■■■■");
	gotoxy(13, 8);
	printf("■    ■      ■    ■ ");
	gotoxy(13, 9);
	printf("■■■■      ■    ■       ■       ■       ■");

	textcolor(MAGENTA2, WHITE);

	gotoxy(23, 12);
	printf("■■■■      ■      ■      ■■■");
	gotoxy(23, 13);
	printf("■            ■■    ■      ■    ■");
	gotoxy(23, 14);
	printf("■■■■      ■  ■  ■      ■    ■");
	gotoxy(23, 15);
	printf("■            ■    ■■      ■    ■");
	gotoxy(23, 16);
	printf("■■■■      ■      ■      ■■■");

}

void end_block2() {

	textcolor(MAGENTA1, WHITE);

	gotoxy(15, 5);
	printf("■■■■      ■■■■      ■■■■      ■■■");
	gotoxy(15, 6);
	printf("■            ■    ■      ■    ■      ■    ■");
	gotoxy(15, 7);
	printf("■  ■■      ■    ■      ■    ■      ■    ■");
	gotoxy(15, 8);
	printf("■    ■      ■    ■      ■    ■      ■    ■");
	gotoxy(15, 9);
	printf("■■■■      ■■■■      ■■■■      ■■■");

	textcolor(MAGENTA2, WHITE);

	gotoxy(25, 12);
	printf("■■■■    ■■■■     ■■■■");
	gotoxy(25, 13);
	printf("    ■      ■    ■     ■    ■");
	gotoxy(25, 14);
	printf("    ■      ■    ■     ■■■");
	gotoxy(25, 15);
	printf("    ■      ■    ■     ■    ■");
	gotoxy(25, 16);
	printf("■■■      ■■■■     ■■■■");
}

int end_restart() {

	cls(BLACK, WHITE);
	effect2();
	gotoxy(16, 10);
	textcolor(BLUE1, YELLOW2);
	printf("다시하려면 Up키를, 종료하려면 Dn 키를 누르세요");
	unsigned char ch = 0;

	while (1) {
		if (kbhit() == 1) {  // 키보드가 눌려져 있으면
			ch = getch(); // key 값을 읽는다
			if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키
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

	int myheartck = 0; // 남은 생명
	int myheart = 14; // 남은 생명 
	// 장애물을 한칸 움직이고 부딪혔는지 확인하고 한칸 움직이고 확인하고 반복 하는데, 
	// 장애물이 두칸이어서 한번 부딪히면 생명이 2씩 줄어듬, 그래서 7의두배 14로 설정함

	map1[2][6] = 1;
	map1[2][8] = 1;
	map1[2][10] = 1;
	map1[2][12] = 1;
	map1[2][14] = 1;
	map1[2][16] = 1;
	map1[2][18] = 1;

	newx = oldx = 20;
	newy = oldy = HEIGHT - 2;
	removeCursor(); // 커서를 안보이게 한다



	while (kbhit() != 1) { // 눌리지 않은 동안

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
		count = 0; // 장애물1 한번 옮겨지면 count 1증가 
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
		int bonus = 14; // 생명물약
		while (1) {

			if (kbhit() == 1) {  // 키보드가 눌려져 있으면
				ch = getch(); // key 값을 읽는다

				if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키

					ch = getch();
					switch (ch) {
					case UP:
					case DOWN:

						keep_moving = 1;
						break;

					}
				}
			}
			if (keep_moving && cnt % 2 == 0) { // 움직이고 있으면

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

				erasepotato(oldx, oldy); // 마지막 위치의 * 를 지우고
				putpotato(newx, newy); // 새로운 위치에서 * 를 표시한다.
				oldx = newx; // 마지막 위치를 기억한다.
				oldy = newy;
				keep_moving = 1; //1:계속이동, 0:한번에 한칸씩이동
			}

			///////////////////////////////////////////////////////////////////////////////////////
			for (int i = block_y + 4 - oh1; i <= block_y + 4; i++) {

				if (block_x == oldx && i == oldy) {

					PlaySound(TEXT("Minus.wav"), 0, SND_FILENAME | SND_ASYNC); // 음향
					myheartck = 1;
				}
			}

			if (myheartck == 1) {

				// 장애물을 한칸 움직이고 확인하고 한칸 움직이고 확인하고 하는데, 
				// 장애물이 두칸이어서 -2로 해버리면 생명이 2씩 줄어듬
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
			count++; // 장애물1 한번 옮겨지면 count 1증가

			for (int i = block_y + 4 - oh1; i <= block_y + 4; i++) {

				if (block_x == oldx && i == oldy) {

					PlaySound(TEXT("Minus.wav"), 0, SND_FILENAME | SND_ASYNC); // 음향
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

					PlaySound(TEXT("Minus.wav"), 0, SND_FILENAME | SND_ASYNC); // 음향
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

					PlaySound(TEXT("Minus.wav"), 0, SND_FILENAME | SND_ASYNC); // 음향
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

					PlaySound(TEXT("Minus.wav"), 0, SND_FILENAME | SND_ASYNC); // 음향
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

					PlaySound(TEXT("Minus.wav"), 0, SND_FILENAME | SND_ASYNC); // 음향
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
			if (monster != 1 && cnt % 40 == 0) { // 괴물과 불덩이 보이고
				show_monster();
				show_fire();//

				monster = 1;
			}


			if (block_x5 == oldx && block_y5 == oldy) { // 포테이토가 맞았는지 확인하고

				PlaySound(TEXT("Minus.wav"), 0, SND_FILENAME | SND_ASYNC); // 음향
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
			if (monster == 1 && cnt % 3 == 0) { // 괴물과  불덩이 움직이고
				move_monster(-1, 0, count);
				move_fire(-6, 1, count);
			}

			if (block_x5 == oldx && block_y5 == oldy) { // 포테이토가 맞았는지 확인하고

				PlaySound(TEXT("Minus.wav"), 0, SND_FILENAME | SND_ASYNC); // 음향
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
			if (cnt % 200 == 0) { // 생명물약 생김
				bonus = rand() % 3 + 13;
				gotoxy(20, bonus);
				textcolor(BLUE1, WHITE);
				printf("♥");
				plus = 1;

			}

			// 생명물약 먹은 경우
			if (oldx == 20 && oldy == bonus && plus == 1) { // plus추가, 하트가 한번에 6개씩 늘어나는거 방지

				if (myheart <= 14) {
					PlaySound(TEXT("Plus.wav"), 0, SND_FILENAME | SND_ASYNC); // 음향
					plus = 0;
					myheart += 6;
					show_heart(myheart);

				}
				else if (myheart == 16) {
					PlaySound(TEXT("Plus.wav"), 0, SND_FILENAME | SND_ASYNC); // 음향
					plus = 0;
					myheart += 4;
					show_heart(myheart);

				}
				else if (myheart == 18) {
					PlaySound(TEXT("Plus.wav"), 0, SND_FILENAME | SND_ASYNC); // 음향
					plus = 0;
					myheart += 2;
					show_heart(myheart);

				}
				else if (myheart > 18) {
					PlaySound(TEXT("Plus.wav"), 0, SND_FILENAME | SND_ASYNC); // 음향
				}

			}

			// 생명물약 없애기
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

			Sleep(Delay); // Delay를 줄이면 속도가 빨라짐
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
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define LEFT 75 // 방향키 왼쪽
#define RIGHT 77 // 방향키 오른쪽
#define UP 72 // 방향키 위쪽
#define DOWN 80 // 방향키 아래쪽
#define ENTER 13 // 엔터키 (확인버튼)

void init(void); // 콘솔창의 크기와 커서
void title_draw(void); // 초기 화면 구현
int menu_draw(void); // 메뉴를 그리는 함수
int key_control(void); // 키 값 반환 함수
void gotoxy(int x, int y); // 커서 좌표 함수
void info_draw(void); // 게임 방법 출력함수
void game_level(void); // 지렁이 이동속도 조절 함수
void game_background(void); // 게임 백그라운드 구현 함수(가로 51/세로 26)
int select_level();

int key; // 키보드로 부터 입력받은 값
int speed = 0; //지렁이 스피드 조절(Sleep함수 파라미터)

int main(void)
{
	int menu_code;
	int x;//현재 지렁이의 위치
	int y;// 현재 지렁이의 위치
	unsigned char chr; // 방향키의 키값을 받기위한 변수
	init();
	while (1)
	{	
		chr = 99;
		title_draw();
		menu_code = menu_draw();

		if (menu_code == 0) //게임 시작
		{
			//printf("11/16 들렸다 갑니다 ^^7");
			game_level();
			
		}
		else if (menu_code == 2) // 게임 정보
		{
			info_draw();
		}
		else if (menu_code == 4) // 게임 종료
		{
			break;
		}else menu_code = 5;
		system("cls");
		game_background();
		x = 3;  // 지렁이의 최초 시작 좌표를 나타냄
		y = 2;
		gotoxy(x, y);
		printf("◑");
		while (1) {
			if (kbhit() != 0) {  //아무키나 입력받았을시 if문을 실행함
				chr = getch();
				if (chr == 0 || chr == 0xe0) {
					chr = getch();
				}
			}
			if (chr == UP) { //방향키 '상' 입력받을시
				y -= 1;
				if (y < 2) {
					system("cls"); // 화면을 깨끗이 지운다
					gotoxy(30, 10);
					printf("GAME OVER\n");
					break;
				}
			}
			else if (chr == DOWN) { //방향키 '하' 입력받을시
				y += 1;
				if (y > 23) {
					system("cls");
					gotoxy(30, 10);
					printf("GAME OVER\n");
					break;
				}
			}
			else if (chr == LEFT) { //방향키 '좌' 입력받을시
				x -= 2; // 네모는 특수문자(2byte)이므로 가로는 2칸씩 이동해야함
				if (x < 3) {
					system("cls");
					gotoxy(30, 10);
					printf("GAME OVER\n");
					break;
				}
			}
			else if (chr == RIGHT) { //방향키 '우' 입력받을시
				x += 2;
				if (x > 75) {
					system("cls");
					gotoxy(30, 10);
					printf("GAME OVER\n");
					break;
				}
			}
		}

	}

	gotoxy(28, 24);
	printf("게임 종료!");
	_getch();

	return 0;

}

void init(void) // 콘솔창의 크기와 커서 
{

	system("mode con cols=100 lines=35 | title Escape Game"); // 임시 크기
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

}

void gotoxy(int x, int y)
{
	//HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


void title_draw(void) // 타이틀 그리기
{
	printf("\n\n");
	printf("    _____    _    ____ _____ _   ___        _____  ____  __  __ \n");
	printf("   | ____|  / \\  |  _ \\_   _| | | \\ \\      / / _ \\|  _ \\|  \\/  |\n");
	printf("   |  _|   / _ \\ | |_) || | | |_| |\\ \\ /\\ / / | | | |_) | |\\/| |\n");
	printf("   | |___ / ___ \\|  _ < | | |  _  | \\ V  V /| |_| |  _ <| |  | |\n");
	printf("   |_____/_/   \\_\\_| \\_\\|_| |_| |_|  \\_/\\_/  \\___/|_| \\_\\_|  |_|\n\n");
	printf("                     ____    _    __  __ _____                  \n");
	printf("                    / ___|  / \\  |  \\/  | ____|                 \n");
	printf("                   | |  _  / _ \\ | |\\/| |  _|                   \n");
	printf("                   | |_| |/ ___ \\| |  | | |___                  \n");
	printf("                    \\____/_/   \\_\\_|  |_|_____|                 \n");

}

int key_control(void) // 키값을 받는함수
{
	key = 0; // 키값을 초기화
	while (1)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == 224)
			{
				key = _getch();
				switch (key)
				{
				case 72:
					return UP;
					break;
				case 75:
					return LEFT;
					break;
				case 77:
					return RIGHT;
					break;
				case 80:
					return DOWN;
					break;
				default:
					break;
				}
			}
			else
			{
				if (key == 13)
					return ENTER;
			}

		}
	}
}

int menu_draw(void) // 메뉴를 그리는 함수
{
	int x = 28;
	int y = 16;

	gotoxy(x - 2, y);
	printf("> 게임 시작");
	gotoxy(x, y + 2);
	printf("게임 방법");
	gotoxy(x, y + 4);
	printf("  종료  ");

	while (1)
	{
		int n = key_control();
		switch (n)
		{
		case UP:
		{
			if (y > 16)
			{
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, y - 2);
				printf(">");
				y -= 2;
			}
			break;
		}
		case DOWN:
		{
			if (y < 20)
			{
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, y + 2);
				printf(">");
				y += 2;
			}
			break;
		}
		case ENTER:
		{
			return y - 16;  // 0 2 4 중 하나를 리턴해줌
		}
		}
	}
}

void info_draw(void) // 게임정보 
{
	system("cls");
	gotoxy(1, 3);
	printf("                              [규칙]\n\n");
	printf("    * 지렁이는 현재 머리가 향하고 있는 방향으로 계속 이동합니다.\n");
	printf("      플레이어의 조작으로 머리의 진행 방향을 바꿀수 있습니다.\n");
	printf("    * 지렁이는 벽이나 자신의 몸 일부에 닿으면 죽습니다.\n");
	printf("    * 지렁이는 먹이를 먹을때마다 몸이 길어집니다 \n");
	printf("    * 지렁이의 길이를 늘려보세요!!\n\n\n\n");
	printf("                            [조작 방법]\n\n");
	printf("    * [↑] - 지렁이의 진행 방향을 위쪽으로 바꿀 수 있습니다. \n");
	printf("    * [→] - 지렁이의 진행 방향을 오른쪽으로 바꿀 수 있습니다. \n");
	printf("    * [←] - 지렁이의 진행 방향을 왼쪽으로 바꿀 수 있습니다. \n");
	printf("    * [↓] - 지렁이의 진행 방향을 아래쪽으로 바꿀 수 있습니다. \n\n\n\n");
	printf("    * Enter - 나가기  \n");


	while (1) // ENTER을 입력받으면 메인화면으로 돌아갑니다.
	{
		if (key_control() == ENTER)
		{
			break;
		}
	}
}

void game_level(void) // 게임의 난이도 설정
{
	int n = 0;
	system("cls");
	gotoxy(1, 1);
	printf("\n\n                          [난이도 선택]\n\n");
	printf("\n\n    * 게임의 난이도를 선택하고 Enter키를 누르세요. (1~5)\n\n");
	printf("    * 난이도가 올라갈수록 지렁이의 이동 속도가 증가합니다!! \n\n");
	n = select_level();
	switch (n)
	{
	case 0:
		speed = 200;
		printf("0");
		break;
	case 5:
		speed = 175;
		printf("5");
		break;
	case 10:
		speed = 150;
		break;
	case 15:
		speed = 125;
		break;
	case 20:
		speed = 100;
		break;
	default:
		speed = 150;
		break;
	}
	n = 5;
	system("cls");
}

void game_background(void) // 게임판의 가로 길이는 75,세로 길이는 23
{
	system("cls");
	int i;

	gotoxy(1, 1);
	printf("■■■■■■■■■■■■■■■■■■■-■■■■■■■■■■■■■■■■■■■");
	for (int i = 2; i <= 24; i++)
	{
		gotoxy(1, i);
		printf("■");
	}
	for (int j = 2; j <= 24; j++)
	{
		gotoxy(76, j);
		printf("■");
	}
	gotoxy(1, 25);
	printf("■■■■■■■■■■■■■■■■■■■-■■■■■■■■■■■■■■■■■■■");
	//scanf_s("%d", &i); //  그냥 화면 고정시키려고.....

}
int select_level()
{
	int x = 19;
	int y = 15;

	gotoxy(x, y);
	printf("난이도 :①   ②   ③   ④   ⑤");
	x += 8; // x = 27
	y += 2; // y = 16
	gotoxy(x, y);
	printf("▲");
	while (1)
	{
		int n = key_control();
		switch (n)
		{
		case RIGHT:
		{
			if (x < 47)
			{
				gotoxy(x, y);
				printf(" ");
				gotoxy(x + 1, y);
				printf(" ");
				gotoxy(x + 5, y);
				printf("▲");
				x += 5;
			}
			break;
		}
		case LEFT:
		{
			if (x > 28)
			{
				gotoxy(x, y);
				printf(" ");
				gotoxy(x + 1, y);
				printf(" ");
				gotoxy(x - 5, y);
				printf("▲");
				x -= 5;
			}
			break;
		}
		case ENTER:
		{
			return x - 27; // 0,5,10,15,20,25 리턴
		}
		}
	}
}

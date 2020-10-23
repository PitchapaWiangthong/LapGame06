#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

#define bullet_count 5

void draw_ship(int, int);
void erase_ship(int, int);
void gotoxy(int, int);
void setcursor(bool);
void setcolor(int, int);
void draw_bullet(int, int);
void erase_bullet(int, int);
void draw_enemy(int,int);
char cursor(int, int);

int main()
{
	char ch = '.';
	char direction = 's';
	int x = 38, y = 20, bx[bullet_count], by[bullet_count];
	bool state[bullet_count] = { 0 };
	int i,randomx,randomy;
	int PrandomX[20], PrandomY[20];

	srand(time(NULL));
	for (i = 0; i < 20; i++)
	{
		randomx = rand() % 61 + 10;
		randomy = rand() % 4 + 2;
		draw_enemy(randomx, randomy);
		PrandomX[i] = randomx;
		PrandomY[i] = randomy;
	}
	setcursor(0);
	gotoxy(x, y);
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') { direction = 'l'; }
			if (ch == 'd') { direction = 'r'; }
			if (ch == 's') { direction = 's'; }
			if (ch == ' ') {
				for (int i = 0; i < bullet_count; i++)
				{
					if (state[i] == 0)
					{
						state[i] = 1;
						bx[i] = x + 2;
						by[i] = y - 1;
						Beep(500, 50);
						break;
					}
				}
			}
			fflush(stdin);
		}
		if (direction == 'l' && x != 0) { erase_ship(x, y); draw_ship(--x, y); }
		if (direction == 'r' && x <= 80) { erase_ship(x, y); draw_ship(++x, y); }
		if (direction == 's') { erase_ship(x, y); draw_ship(x, y); }
		for (int i = 0; i < bullet_count; i++)
		{
			if (state[i] == 1)
			{
				int Iscollide = 0;
				for (int j = 0; j < 20; j++)
				{
					if (bx[i] == PrandomX[j] and by[i] == PrandomY[j])
					{
						Iscollide = TRUE;
					}
				}

				erase_bullet(bx[i], by[i]);
				if (by[i] > 0  or Iscollide == TRUE)
				{
					draw_bullet(bx[i], --by[i]);
				}
				else
				{
					state[i] = 0;
				}

				
			}
		}
		Sleep(100);
	} while (ch != 'p');
	return 0;
}




	//function
void draw_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(2, 4);
	printf("<-0->");
}

void erase_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(2, 0);
	printf("       ");
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(4, 4);
	printf(" ");
}
void erase_bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}
void draw_enemy(int x,int y)
{
	gotoxy(x, y);
	printf("*",rand());
}
char cursor(int x, int y)
{
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; 
	COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];
}
#include<iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>
using namespace std;
int speed = 300;
int fruitX;
int fruitY;
int width = 20;
int height = 20;
int x = 10;
int y = 10;
int tailX[100];
int tailY[100];
int nTail = 0;
char dir = 'd';
bool gameOver = false;
void StartScreen() {

	system("cls");
	cout << "######################" << endl;
	cout << "      SNAKE GAME      " << endl;
	cout << endl;
	cout << "  press Space to start  " << endl;
	cout << "######################" << endl;
	while (true) {
		if (_kbhit()) {
			char key = _getch();
			if (key == ' ') {
				break;
			}
		}
	}
}
void GotoXY(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void Draw() {
	GotoXY(0, 0);
	for (int i = 0; i < width + 2; i++) {
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) {
				cout << "#";
			}
			if (i == y && j == x) {
				cout << "O";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "*";
			}
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
						break;
					}
				}
				if (!print) {
					cout << " ";
				}
			}


			if (j == width - 1) {
				cout << "#";
			}


		}
		cout << endl;

		


	}
	for (int i = 0; i < width + 2; i++) {
			cout << "#";
		}
	cout<<"\nScore:"<<nTail<<endl;
}

	void Input() {
		while(_kbhit()){
			char key = _getch();
			if (key == 'a' || key == 'A')dir = 'a';
			if (key == 'd' || key == 'D')dir = 'd';
			if (key == 's' || key == 'S')dir = 's';
			if (key == 'w' || key == 'W')dir = 'w';
			
			}
	}
	void Logic() {
		int prevX = x;
		int prevY = y;
		int prev2X, prev2Y;
		for (int i = 0; i < nTail; i++) {
			prev2X = tailX[i];
			prev2Y = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}
		if (dir == 'a')x--;
		if (dir == 'd')x++;
		if (dir == 'w')y--;
		if (dir == 's')y++;
		if (x < 0 || x >= width || y < 0 || y >= height) {
			gameOver = true;
		}
		for (int i = 0; i < nTail; i++) {
			if (tailX[i] == x && tailY[i] == y) {
				gameOver = true;
				return;
			}
		}
		if (x == fruitX && y == fruitY) {
			do {
				fruitX = rand() % width;
				fruitY = rand() % height;
			} while (fruitX == x && fruitY == y);
			nTail++;
			if (speed > 60) {
				speed -= 10;
			}
		}
}
	void Setup() {
		x = width / 2;
		y = height / 2;
		nTail = 0;
		speed = 300;
		dir = 'd';
		fruitX = rand() % width;
		fruitY = rand() % height;
	}
	int main() {
		srand(time(0));
		CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
		while (true) {
			StartScreen();
			Setup();
			gameOver = false;
			while (!gameOver) {
				Draw();
				Input();
				Logic();
				Sleep(speed);
			}
			system("cls");
			cout << "Game Over!" << endl;
			cout << "Score:" << nTail << endl;
			cout << endl;
			cout << "Press R to Restart" << endl;
			cout << "Press Q to Quit" << endl;
			while (true) {
				char key = _getch();
				if (key == 'R' || key == 'r') {
					break;
				}
				if (key == 'q' || key == 'Q') {
					cout << "See You Next Time" << endl;
					return 0;
				}

			}
		}
	}
	 
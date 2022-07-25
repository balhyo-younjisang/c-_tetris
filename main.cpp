#include <iostream>
#include <stdio.h>
#include <string>
#include <Windows.h> // gotoxy()
#include<conio.h> // _getch()
#include <stdlib.h> //exit()
#include <ctime>
#include <vector>
#include <algorithm>
#include <cstdlib> //srand()

#define TABLE_X 20 // ��Ʈ���� ���̺� x�� ����
#define TABLE_Y 38 // ��Ʈ���� ���̺� y�� ����	
#define UP 0 //��
#define	DOWN 1 // ��
#define LEFT 2 //	��
#define RIGHT 3 // ��
#define SUBMIT 4 // ���� ( �����̽��� )

using namespace std;

vector <vector<int>> table;
vector <vector<int>> backup;

// Ŀ�� ��ġ �̵� �Լ�
void gotoxy(int x, int y) { 
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ� ��������
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
//Ŀ�� ����� 
void cursor_view() {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
//Ű���� �Է�
int key_control() {
	char tmp = _getch();

	if (tmp == 'w' || tmp == 'W') { return UP; }
	else if (tmp == 'A' || tmp == 'a') {
		return LEFT;
	}
	else if (tmp == 'D' || tmp == 'd') {
		return RIGHT;
	}
	else if (tmp == 'S' || tmp == 's') {
		return DOWN;
	}
	else if (tmp == ' ') {
		return SUBMIT;
	}
}
//�ʱ� ����
void init() {
	system("mode con cols=56 lines=20 | title TETRIS"); 
	cursor_view();
}
// Ÿ��Ʋ ����ϱ�
void draw_title() {
	printf("\n\n\n\n"); // 4ĭ ����
	printf("--------------------------------------------------------\n"); //Ÿ��Ʋ ���
	printf("|    #####    #####    #####    ####     #    #####    |\n");
	printf("|      #      #          #      #   #    #   #         |\n");
	printf("|      #      ###        #      ####     #    #####    |\n");
	printf("|      #      #          #      #  ##    #         #   |\n");
	printf("|      #      #####      #      #    #   #    #####    |\n");
	printf("--------------------------------------------------------\n");
	printf("\n\n\n\n");
	return;
}

//���� ������ �׸���
void draw_info_menu() {
	system("cls");
	printf("\n\n");
	printf("                         [���۹�]\n");
	printf("                     �̵�: W, A, S, D\n");
	printf("                     ����: SPACE\n\n");
	printf("                     ���� : ������\n");
	printf("          �����̽��ٸ� ������ ����ȭ������ �̵��մϴ�.");

	while (true) {
		if (key_control() == SUBMIT) {
			break;
		}
	}

}
//���� �޴� �׸���
int draw_start_menu() {
	int x = 24;
	int y = 12;
	gotoxy(x - 2, y);
	printf("> ���� ����"); 
	gotoxy(x, y+1);
	printf("����");
	gotoxy(x, y+2);
	printf("���� ����");

	while (true) { // ���� �ݺ�
		int input = key_control();
		switch (input) {
		case UP: { //�Էµ� Ű�� ���� UP�� ��� (w,W)
			if (y > 12) {//y �� 12~14������ �̵�
				gotoxy(x - 2, y); //x-2�� �ϴ� ������ ">"�� �� ĭ ������ ����ϱ� ����
				printf(" ");
				gotoxy(x - 2, --y); //���� �̵��� ��ġ�� �̵��Ͽ�
				printf(">"); // ">" ���
			}
			break;
		}
		
		case DOWN: {
			if (y < 14) { //y�� 12~14������ �̵�
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}

		case SUBMIT: {
			return y - 12;
			// 0 : ���� ����
			// 1 : ���� ����
			// 2 : ���� ����
		}
		}
	}
}


/*
���� : 0
�� : 1
�� : 2
�̹� ���� �� : 3
���� ���̴� �ٴ� : 4
*/


int block1[4][4][4] = {
	{
		{0,0,0,0},
		{0,0,0,0},
		{1,1,1,1},
		{0,0,0,0}
	},
	{
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0}
	},
	{
		{0,0,0,0},
		{0,0,0,0},
		{1,1,1,1},
		{0,0,0,0}
	},
	{
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0}
	}
};
int block2[4][4][4] = {
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	}
};
int block3[4][4][4] = {
	{
		{0,1,0,0},
		{0,1,0,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,1},
		{0,1,0,0},
		{0,0,0,0}
	},
	{
		{0,0,1,1},
		{0,0,0,1},
		{0,0,0,1},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,0,0,1},
		{0,1,1,1},
		{0,0,0,0}
	}
};
int block4[4][4][4] = {
	{
		{0,1,0,0},
		{0,1,0,0},
		{1,1,0,0},
		{0,0,0,0}
	},
	{
		{0,1,0,0},
		{0,1,1,1},
		{0,0,0,0},
		{0,0,0,0}
	},
	{
		{0,0,1,1},
		{0,0,1,0},
		{0,0,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,1},
		{0,0,0,1},
		{0,0,0,0}
	}
};
int block5[4][4][4] ={
	{
		{0,0,1,0},
		{0,1,1,0},
		{0,1,0,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,0,1,1},
		{0,0,0,0}
	},
	{
		{0,0,1,0},
		{0,1,1,0},
		{0,1,0,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,0,1,1},
		{0,0,0,0}
	}
};
int block6[4][4][4] ={
	{
		{0,1,0,0},
		{0,1,1,0},
		{0,1,0,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,0,1,0},
		{0,1,1,1},
		{0,0,0,0}
	},
	{
		{0,0,1,0},
		{0,0,1,1},
		{0,0,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,1},
		{0,0,1,0},
		{0,0,0,0}
	}
};
int block7[4][4][4] ={
	{
		{0,1,0,0},
		{0,1,1,0},
		{0,0,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,0,1,1},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,1,0,0},
		{0,1,1,0},
		{0,0,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,0,1,1},
		{0,1,1,0},
		{0,0,0,0}
	}
};

// �� �θ� Ŭ����
class block {
protected:
	int shape[4][4][4]; //shape[y][x]
	int x;
	int y;
	int rotationCnt;
public:
	int getShape(int rotationCnt, int y, int x) {
		return shape[rotationCnt][y][x];
	}
	int get_x() {
		return x;
	}
	int get_y() {
		return y;
	}
	int getRotationCount() {
		return rotationCnt;
	}
	void down() {
		y++;
	}
	void left() {
		x--;
	}
	void right() {
		x++;
	}
	void rotate() {
		rotationCnt = (rotationCnt + 1) % 4;
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	} 
	void setRotationCount(int r) {
		this->rotationCnt = r;
	}
	void setShape(int r, int y, int x, int value) {
		this->shape[r][y][x] = value;
	}
};
//1�� �� Ŭ����
class Block1:block {
public:
	Block1() {
		x = TABLE_X / 2 - 3;
		y = 1;
		rotationCnt = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					shape[i][j][k] = block1[i][j][k];
				}
			}
		}
	}
};
//2�� �� Ŭ����
class Block2 :block {
public:
	Block2() {
		x = TABLE_X / 2 - 3;
		y = 1;
		rotationCnt = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					shape[i][j][k] = block2[i][j][k];
				}
			}
		}
	}
};
//3�� �� Ŭ����
class Block3 :block {
public:
	Block3() {
		x = TABLE_X / 2 - 3;
		y = 1;
		rotationCnt = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					shape[i][j][k] = block3[i][j][k];
				}
			}
		}
	}
};
//4�� �� Ŭ����
class Block4 :block {
public:
	Block4() {
		x = TABLE_X / 2 - 3;
		y = 1;
		rotationCnt = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					shape[i][j][k] = block4[i][j][k];
				}
			}
		}
	}
};
//5�� �� Ŭ����
class Block5 :block {
public:
	Block5() {
		x = TABLE_X / 2 - 3;
		y = 1;
		rotationCnt = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					shape[i][j][k] = block5[i][j][k];
				}
			}
		}
	}
};
//6�� �� Ŭ����
class Block6 :block {
public:
	Block6() {
		x = TABLE_X / 2 - 3;
		y = 1;
		rotationCnt = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					shape[i][j][k] = block6[i][j][k];
				}
			}
		}
	}
};
//7�� �� Ŭ����
class Block7 :block {
public:
	Block7() {
		x = TABLE_X / 2 - 3;
		y = 1;
		rotationCnt = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					shape[i][j][k] = block7[i][j][k];
				}
			}
		}
	}
};

//��,table ��� Ŭ���� -> ���� ���۸�
class backup {
public:
	// �� ���
	static void updateBlock(block* source, block& backupBlock) {
		backupBlock.setX(source->get_x());
		backupBlock.setY(source->get_y());
		backupBlock.setRotationCount(source->getRotationCount());
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					backupBlock.setShape(i, j, k, source->getShape(i, j, k));
				}
			}
		}
	}
	//���̺� ���
	static void updateTable(vector<vector<int>>& source, vector<vector<int>>& backuptable) {
		backuptable.resize(source.size(), vector<int>(source.size()));
		copy(source.begin(), source.end(), backuptable.begin());
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	while (true) {
		draw_title();
		int menu_code = draw_start_menu(); 
		if (menu_code == 0) {
			// ���� ����
			system("cls");
			system("mode con cols=120 lines=30 | title TETRIS");
			while (true) {
			}	
			
		}
		else if (menu_code == 1) {
			//���� ����
			exit(0);
		}
		else if (menu_code == 2) {
			//���� ����
			draw_info_menu();
		}
		system("cls"); //�ܼ�â ���� + �ܼ� ��ǥ 0,0 �ʱ�ȭ
	}
	

	return 0;
}
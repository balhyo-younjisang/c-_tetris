#include <iostream>
#include <stdio.h>
#include <string>
#include <Windows.h> // gotoxy()
#include<conio.h> // _getch()
#include <stdlib.h> //exit()
#include <ctime>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <cstdlib> //srand()

#define TABLE_X 20 // 테트리스 테이블 x축 길이
#define TABLE_Y 38 // 테트리스 테이블 y축 길이	
#define UP 72 //↑
#define	DOWN 80 // ↓
#define LEFT 75  //	←
#define RIGHT 77 // →
#define SUBMIT 4 // 선택 ( 스페이스바 )

using namespace std;


// 커서 위치 이동 함수
void gotoxy(int x, int y) { 
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 가져오기
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
//커서 숨기기 
void cursor_view(char show) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
//키보드 입력
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
//초기 설정
void init() {
	system("mode con cols=56 lines=20 | title TETRIS"); 
	cursor_view(false);
}
// 타이틀 출력하기
void draw_title() {
	printf("\n\n\n\n"); // 4칸 개행
	printf("--------------------------------------------------------\n"); //타이틀 출력
	printf("|    #####    #####    #####    ####     #    #####    |\n");
	printf("|      #      #          #      #   #    #   #         |\n");
	printf("|      #      ###        #      ####     #    #####    |\n");
	printf("|      #      #          #      #  ##    #         #   |\n");
	printf("|      #      #####      #      #    #   #    #####    |\n");
	printf("--------------------------------------------------------\n");
	printf("\n\n\n\n");
	return;
}

//정보 페이지 그리기
void draw_info_menu() {
	system("cls");
	printf("\n\n");
	printf("                         [조작법]\n");
	printf("                     이동: W, A, S, D\n");
	printf("                     선택: SPACE\n\n");
	printf("                     개발 : 윤지상\n");
	printf("          스페이스바를 누르면 메인화면으로 이동합니다.");

	while (true) {
		if (key_control() == SUBMIT) {
			break;
		}
	}

}
//시작 메뉴 그리기
int draw_start_menu() {
	int x = 24;
	int y = 12;
	gotoxy(x - 2, y);
	printf("> 게임 시작"); 
	gotoxy(x, y+1);
	printf("종료");
	gotoxy(x, y+2);
	printf("게임 정보");

	while (true) { // 무한 반복
		int input = key_control();
		switch (input) {
		case UP: { //입력된 키의 값이 UP인 경우 (w,W)
			if (y > 12) {//y 는 12~14까지만 이동
				gotoxy(x - 2, y); //x-2를 하는 이유는 ">"를 두 칸 이전에 출력하기 위해
				printf(" ");
				gotoxy(x - 2, --y); //새로 이동한 위치로 이동하여
				printf(">"); // ">" 출력
			}
			break;
		}
		
		case DOWN: {
			if (y < 14) { //y는 12~14까지만 이동
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}

		case SUBMIT: {
			return y - 12;
			// 0 : 게임 시작
			// 1 : 게임 종료
			// 2 : 게임 정보
		}
		}
	}
}


/*
공백 = 0
▦ = 1
■ = 2
이미 쌓인 블럭 = 3
블럭이 쌓이는 맨 밑바닥 = 4
*/


int block1[4][4][4] = {
	{
		{0,0,0,0},
		{0,0,0,0},
		{2,2,2,2},
		{0,0,0,0}
	},
	{
		{0,0,2,0},
		{0,0,2,0},
		{0,0,2,0},
		{0,0,2,0}
	},
	{
		{0,0,0,0},
		{0,0,0,0},
		{2,2,2,2},
		{0,0,0,0}
	},
	{
		{0,0,2,0},
		{0,0,2,0},
		{0,0,2,0},
		{0,0,2,0}
	}
};
int block2[4][4][4] = {
	{
		{0,0,0,0},
		{0,2,2,0},
		{0,2,2,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,2,2,0},
		{0,2,2,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,2,2,0},
		{0,2,2,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,2,2,0},
		{0,2,2,0},
		{0,0,0,0}
	}
};
int block3[4][4][4] = {
	{
		{0,2,0,0},
		{0,2,0,0},
		{0,2,2,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,2,2,2},
		{0,2,0,0},
		{0,0,0,0}
	},
	{
		{0,0,2,2},
		{0,0,0,2},
		{0,0,0,2},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,0,0,2},
		{0,2,2,2},
		{0,0,0,0}
	}
};
int block4[4][4][4] = {
	{
		{0,2,0,0},
		{0,2,0,0},
		{2,2,0,0},
		{0,0,0,0}
	},
	{
		{0,2,0,0},
		{0,2,2,2},
		{0,0,0,0},
		{0,0,0,0}
	},
	{
		{0,0,2,2},
		{0,0,2,0},
		{0,0,2,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,2,2,2},
		{0,0,0,2},
		{0,0,0,0}
	}
};
int block5[4][4][4] ={
	{
		{0,0,2,0},
		{0,2,2,0},
		{0,2,0,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,2,2,0},
		{0,0,2,2},
		{0,0,0,0}
	},
	{
		{0,0,2,0},
		{0,2,2,0},
		{0,2,0,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,2,2,0},
		{0,0,2,2},
		{0,0,0,0}
	}
};
int block6[4][4][4] ={
	{
		{0,2,0,0},
		{0,2,2,0},
		{0,2,0,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,0,2,0},
		{0,2,2,2},
		{0,0,0,0}
	},
	{
		{0,0,2,0},
		{0,0,2,2},
		{0,0,2,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,2,2,2},
		{0,0,2,0},
		{0,0,0,0}
	}
};
int block7[4][4][4] ={
	{
		{0,2,0,0},
		{0,2,2,0},
		{0,0,2,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,0,2,2},
		{0,2,2,0},
		{0,0,0,0}
	},
	{
		{0,2,0,0},
		{0,2,2,0},
		{0,0,2,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,0,2,2},
		{0,2,2,0},
		{0,0,0,0}
	}
};

// 블럭 부모 클래스
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
//1번 블럭 클래스
class Block1:public block {
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
//2번 블럭 클래스
class Block2 :public block {
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
//3번 블럭 클래스
class Block3 :public block {
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
//4번 블럭 클래스
class Block4 :public block {
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
//5번 블럭 클래스
class Block5 :public block {
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
//6번 블럭 클래스
class Block6 :public block {
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
//7번 블럭 클래스
class Block7 :public block {
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

//블럭,table 백업 클래스 -> 더블 버퍼링
class backup {
public:
	// 블럭 백업
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
	//테이블 백업
	static void updateTable(vector<vector<int>>& source, vector<vector<int>>& backuptable) {
		backuptable.resize(source.size(), vector<int>(source.size()));
		copy(source.begin(), source.end(), backuptable.begin());
	}
};
//테이블 클래스
class Table {
private:
	int x;
	int y;
	block* blockObject;
	vector<vector<int>> table;
public:
	Table(int x, int y) { //프레임 생성
		blockObject = nullptr;
		this->x = x;
		this->y = y;
		for (int i = 0; i < y; i++) {
			vector<int> tmp;
			for (int j = 0; j < x; j++) {
				tmp.push_back(0);
			}
			table.push_back(tmp);
		}
		for (int i = 0; i < x; i++) {
			table[0][i] = 1;
			table[y - 1][i] = 1;
		}
		for (int i = 0; i < y - 1; i++) {
			table[i][0] = 1;
			table[i][x - 1] = 1;
		}
		for (int i = 1; i < x - 1; i++) {
			table[y - 1][i] = 4;
		}
	}
	void draw_game_table() {
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				if (table[i][j] == 1 || table[i][j] == 4) cout << "▩";
				else if (table[i][j] == 2 || table[i][j] == 3) cout << "■";
				else cout << "  ";
			}
			cout << "\n";
		}
	}
	void create_block() {
		srand((unsigned int)time(NULL));
		int s = rand() % 7 + 1;
		if (s == 1)blockObject = new Block1();
		else if (s == 2) blockObject = new Block2();
		else if (s == 3) blockObject = new Block3();
		else if (s == 4) blockObject = new Block4();
		else if (s == 5) blockObject = new Block5();
		else if (s == 6) blockObject = new Block6();
		else if (s == 7) blockObject = new Block7();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int Y = j + blockObject->get_y();
				int X = i + blockObject->get_x();
				table[Y][X] = blockObject->getShape(blockObject->getRotationCount(),i,j);
			}
		}
	}
	void move_block(int key) {
		block backupBlock;
		vector<vector<int>> backupTable;
		backup::updateBlock(blockObject, backupBlock);
		backup::updateTable(table, backupTable);

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++	) {
				int Y = j + blockObject->get_y();
				int X = i + blockObject->get_x();
				if (table[Y][X] == 2) table[Y][X] = 0;
			}
		} 
		if (key == DOWN) blockObject->down(); 
		else if (key == LEFT) blockObject->left();  
		else if (key == RIGHT) blockObject->right(); 
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int Y = j + blockObject->get_y();
				int X = i + blockObject->get_x();
				int blockValue = blockObject->getShape(blockObject->getRotationCount(), i, j);
				if (blockValue != 2) continue; // 블럭이 아니면 무시
				if (table[Y][X] == 0) { // 빈 공간이면 -> 갱신
					table[Y][X] = blockValue;
				}
				else if (table[Y][X] == 1) { // 블럭이 양 옆 벽에 닿으면 -> 취소
					copy(backupTable.begin(), backupTable.end(), table.begin());
					blockObject->setX(blockObject->get_x());
					blockObject->setY(blockObject->get_y());
					return;	
				}
				else if (table[Y][X] == 3) { // 이미 쌓여진 블럭과 접촉하면
					copy(backupTable.begin(), backupTable.end(), table.begin()); // table 백업
					blockObject->setX(backupBlock.get_x()); // 블럭 x 좌표 백업
					blockObject->setY(backupBlock.get_y()); // 블럭 y 좌표 백업
					if (key == DOWN) { // 만약 아랫 방향일 경우에
						BuildBlock(); // 블럭을 쌓고
						create_block(); // 새로운 블럭을 만듬
					}
					return; // 함수 종료
				}
				else if (table[Y][X] == 4) { //	 맨 밑바닥에 접촉했으면
					copy(backupTable.begin(), backupTable.end(), table.begin()); // table 백업
					blockObject->setX(backupBlock.get_x()); // 블럭 x 좌표 백업
					blockObject->setY(backupBlock.get_y()); // 블럭 y 좌표 백업
					if (key == DOWN) { // 만약 아랫 방향일 경우에
						BuildBlock(); // 블럭을 쌓고
						create_block(); // 새로운 블럭을 만듬
					}
					return; // 함수 종료
				}
			}
		}
	} 
	void rotate_block() {
		block backupBlock; 
		vector<vector<int>> backupTable;
		backup::updateBlock(blockObject, backupBlock);
		backup::updateTable(table, backupTable);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int Y = j + blockObject->get_y();
				int X = i + blockObject->get_x();
				if (table[Y][X] == 2)
					table[Y][X] = 0;
			}
		}
		blockObject->rotate();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int Y = j + blockObject->get_y();
				int X = i + blockObject->get_x();
				int blockValue = blockObject->getShape(blockObject->getRotationCount(), i, j);
				if (blockValue != 2) continue;
				if (table[Y][X] == 0) table[Y][X] = blockObject->getShape(blockObject->getRotationCount(), i, j);
				else if (table[Y][X] == 1 || table[Y][X] == 4 || table[Y][X] == 3) {
					copy(backupTable.begin(), backupTable.end(), table.begin());
					blockObject->setRotationCount(backupBlock.getRotationCount());
					return;
				}
			}
		}
	}
	


	void BuildBlock() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int Y = j + blockObject->get_y();
				int X = i + blockObject->get_x();
				int blockValue = blockObject->getShape(blockObject->getRotationCount(), i, j); //블럭 배열 값 얻기
				if (blockValue != 2) continue; // 블럭이 아니면 무시 (블럭은 2로 이루어져있음)
				table[Y][X] = 3;
			}
		}
	}
 };

 class GamePlay {
 private:
	 Table* t;
 public:
	 GamePlay() {
		 t = new Table(TABLE_X, TABLE_Y);
		 t->create_block();
		 t->draw_game_table();
		 while (1) {
			 int nselect;
			 if (_kbhit()) {
				 nselect = _getch();
				 if (nselect == 224) {
					 nselect = _getch();
					 switch (nselect)
					 {
					 case UP:
						 t->rotate_block();
						 break;
					 case DOWN:
						 t->move_block(DOWN);
						 break;
					 case LEFT:
						 t->move_block(LEFT);
						 break;
					 case RIGHT:			
						 t->move_block(RIGHT);
						 break;
					 default:
						 break;
					 }
				 }
			 }
			 gotoxy(0, 0);
			 t->draw_game_table();
		 }
	 }
	 ~GamePlay() {
		 delete t;
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
			// 게임 시작
			system("cls");
			system("mode con cols=100 lines=40 | title TETRIS"); 
			break;
		}
		else if (menu_code == 1) {
			//게임 종료
			exit(0);
		}
		else if (menu_code == 2) {
			//게임 정보
			draw_info_menu();
		}
		system("cls"); //콘솔창 비우기 + 콘솔 좌표 0,0 초기화
	}
	Table(TABLE_X, TABLE_Y);
	GamePlay();
	getchar();

	return 0;
}


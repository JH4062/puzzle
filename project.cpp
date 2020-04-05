#include<Bangtal.h>
#pragma comment(lib,"bangtal.lib")

SceneID scene1,scene2;
ObjectID start;
ObjectID image00, image01, image02, image10, image11, image12, image20, image21, image22, blank;

int boardX[3][3] = {
	{0, 200, 400},
	{0, 200, 400},
	{0, 200, 400}
};

int boardY[3][3] = {
	{400, 400, 400},
	{200,200,200},
	{0,0,0}
};

ObjectID board[3][3] = {
	{image00, image01, image02},
	{image10, image11, image12},
	{image20,image21,blank} 
};

ObjectID createObject(const char* name, const char* image, SceneID scene, int x, int y, bool shown) {
	ObjectID object = createObject(name, image);
	locateObject(object, scene, x, y);
	if (shown) {
		showObject(object);
	}
	return object;
}

void Swap(ObjectID a, ObjectID b)
{
	ObjectID t = a;
	a = b;
	b = t;
}

void SwapX(int x1, int x2) {
	int tt = x1;
	x1 = x2;
	x2 = tt;
}

void SwapY(int y1, int y2) {
	int ttt = y1;
	y1 = y2;
	y2 = ttt;
}

void Shuffle() {

}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == start) {
		hideObject(start);
		enterScene(scene2);
	}

	//이미지12를 눌렀을때 ?
	if (object == board[1][2]) {
		locateObject(board[1][2], scene2, boardX[2][2], boardY[2][2]);
		locateObject(board[2][2], scene2, boardX[2][1], board[2][1]);
		Swap(board[1][2], board[2][1]);
	} 

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			if (object == board[i][j] && object != blank) {
				if (i < 2 && board[i + 1][j] == blank) { // 밑칸이 공백일때.
					locateObject(board[i][j], scene2, boardX[i + 1][j], boardY[i + 1][j]);
					locateObject(board[i + 1][j], scene2, boardX[i][j], boardY[i][j]);

					Swap(board[i][j], blank);
					SwapX(boardX[i][j], boardX[i + 1][j]);
					SwapY(boardY[i][j], boardY[i + 1][j]);

				}

				else if (i>0 && board[i -1][j] == blank) { // 윗칸이 공백일때.
					locateObject(board[i][j], scene2, boardX[i - 1][j], boardY[i - 1][j]);
					locateObject(board[i- 1][j], scene2, boardX[i][j], boardY[i][j]);
					Swap(board[i][j], blank);

				}

				else if (j<2 && board[i][j+1] == blank) { // 오른쪽칸이 공백일때.
					locateObject(board[i][j], scene2, boardX[i][j+1], boardY[i][j+1]);
					locateObject(board[i][j+1], scene2, boardX[i][j], boardY[i][j]);
					Swap(board[i][j], blank);

				}

				else if (j > 0 && board[i][j-1] == blank) { // 왼쪽칸이 공백일때.
					locateObject(board[i][j], scene2, boardX[i][j-1], boardY[i][j-1]);
					locateObject(board[i][j-1], scene2, boardX[i][j], boardY[i][j]);
					Swap(board[i][j], blank);

				}
				
			}
							
		}
					
	}

}


int main() {

	setMouseCallback(mouseCallback);
	scene1 = createScene("배경", "지구.jpg");
	scene2 = createScene("퍼즐", "흰 배경.jpg");
	board[0][0] = createObject("이미지0", "0.png", scene2, boardX[0][0], boardY[0][0], true);
	board[0][1] = createObject("이미지1", "1.png", scene2, boardX[0][1], boardY[0][1], true);
	board[0][2] = createObject("이미지2", "2.png", scene2, boardX[0][2], boardY[0][2], true);
	board[1][0] = createObject("이미지3", "3.png", scene2, boardX[1][0], boardY[1][0], true);
	board[1][1] = createObject("이미지4", "4.png", scene2, boardX[1][1], boardY[1][1], true);
	board[1][2] = createObject("이미지5", "5.png", scene2, boardX[1][2], boardY[1][2], true);
	board[2][0] = createObject("이미지6", "6.png", scene2, boardX[2][0], boardY[2][0], true);
	board[2][1] = createObject("이미지7", "7.png", scene2, boardX[2][1], boardY[2][1], true);
	// = createObject("이미지8", "8.png", scene2, boardX[2][2], boardY[2][2], false);
	board[2][2] = createObject("공백", "공백.jpg", scene2, boardX[2][2], boardY[2][2], true);

	start = createObject("스타트 버튼", "start.png",scene1,650,300,true);
	
	startGame(scene1);
	}

	
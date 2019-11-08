#include <iostream>
#include <string>
#include "ChessHead.h"
#include <cmath>
#include <algorithm>

using namespace std;

bool King::can_it_move_to(int x, int y, int x1, int y1) {
	int g = (x - x1) * (x - x1) + (y - y1) * (y - y1);
	if (g <= 2) return true;
	else return false;
}

bool Queen::can_it_move_to(int x, int y, int x1, int y1) {
	if (x == x1 || y == y1) {
		return true;
	}
	else if (x + y == x1 + y1) {
		return true;
	}
	else if (x - y == x1 - y1) {
		return true;
	}
	else return false;
}

bool Bishop::can_it_move_to(int x, int y, int x1, int y1) {
	
	return (x + y == x1 + y1) || (x - y == x1 - y1);
}

bool Pawn::can_it_move_to(int x, int y, int x1, int y1) {
	if (x + y == x1 + y1) {
		if (team == 1 && y1 == y + 1) return true;
		else if (team == 2 && y1 == y - 1) return true;
		else return false;
	}
	else if (x - y == x1 - y1) {
		if (team == 1 && y1 == y + 1) return true;
		else if (team == 2 && y1 == y - 1) return true;
		else return false;
	}
	else return false;
}

bool Rook::can_it_move_to(int x, int y, int x1, int y1) {
	if (x == x1 || y == y1) {
		return true;
	}
	else return false;
}

bool Knight::can_it_move_to(int x, int y, int x1, int y1) {
	int sq = abs(x - x1) + abs(y - y1);
	if (sq == 3 && x != x1 && y != y1) return true;
	else return false;
}

Board::Board() {
	for (int i = 0; i < 8; i++) {
		board[i][1] = &pawn1;
		board[i][6] = &pawn2;
	}
	board[0][0] = &rookl1;
	board[1][0] = &knightl1;
	board[2][0] = &bishopl1;
	board[3][0] = &queen1;
	board[4][0] = &king1;
	board[5][0] = &bishopp1;
	board[6][0] = &knightp1;
	board[7][0] = &rookp1;
	board[0][7] = &rookl2;
	board[1][7] = &knightl2;
	board[2][7] = &bishopl2;
	board[3][7] = &queen2;
	board[4][7] = &king2;
	board[5][7] = &bishopp2;
	board[6][7] = &knightp2;
	board[7][7] = &rookp2;
	for (int i = 0; i < 8; i++) {
		for (int j = 2; j < 6; j++) {
			board[i][j] = &empty;
		}
	}

}

int Board::getkingx(int x1) {
	int x = 0;
	if (x1 == 4) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j]->getteam() == 3) return i;
			}
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j]->getteam() == 4) return i;
			}
		}
	}
}

int Board::getkingy(int x1) {
	int x = 0;
	if (x1 == 4) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j]->getteam() == 3) return j;
			}
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j]->getteam() == 4) return j;
			}
		}
	}
}

bool Board::attackon(int xk) {
	if (xk == 3) {
		int xnew = getkingx(3);
		int ynew = getkingy(3);
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j]->getteam() == 1) {
					if (!checkposition(i, j, xnew, ynew, 0)) {
						cout << "Check!\nBlack King under attack!\n";
						return true;
					}
				}
			}
		}
		return false;
	}
	if (xk == 4) {
		int xnew = getkingx(4);
		int ynew = getkingy(4);
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j]->getteam() == 2) {
					if (!checkposition(i, j, xnew, ynew, 1)) {
						cout << "Check!\nWhite King under attack!\n";
						return true;
					}
				}
			}
		}
		return false;
	}
}

bool Board::can_it_move_for_king(int xold, int yold, int xnew, int ynew) {
	if (board[xold][yold]->can_it_move_to(xold,yold,xnew,ynew)) return true;
	else {
		int r = board[xold][yold]->getteam();

		if (r == 4) r = 3;
		else r = 4;

		bool k = attackon(r);

		if (!k)
		{
			bool b = false;
			bool h = true, v = false;
			if (xnew > xold) h = false;
			if (board[xold][yold]->getteam() == 3) {
				if (h) {
					for (int i = 0; i < moves.size(); i++) 
					{
						if (moves[i][0] == 'a' && moves[i][1] == '1') v = true;
					}
				}
				else {
					for (int i = 0; i < moves.size(); i++) 
					{
						if (moves[i][0] == 'h' && moves[i][1] == '1') v = true;
					}
				}
				for (int i = 0; i < moves.size(); i++) 
				{
					if ((moves[i][0] == 'e' && moves[i][1] == '1') || v) b = true;
				}
			}
			else {
				if (h) 
				{
					for (int i = 0; i < moves.size(); i++) {
						if (moves[i][0] == 'a' && moves[i][1] == '8') v = true;
					}
				}
				else 
				{
					for (int i = 0; i < moves.size(); i++) {
						if (moves[i][0] == 'h' && moves[i][1] == '8') v = true;
					}
				}
				for (int i = 0; i < moves.size(); i++)
				{
					if ((moves[i][0] == 'e' && moves[i][1] == '8') || v) b = true;
				}
			}
			if (!b) {
				if (xnew == 6 || xnew == 2) return true;
				else return false;
			}
			else return false;
		}
		else return false;
	}
}

void Board::castlecastle(int xold, int yold, int xnew) {
	Figure* f;
	f = board[xold][yold];
	board[xold][yold] = board[xnew][yold];
	board[xnew][yold] = f;
	 if(xnew > xold) {
		f = board[xold + 1][yold];
		board[xold + 1][yold] = board[7][yold];
		board[7][yold] = f;
	}
	else {
		f = board[xold - 1][yold];
		board[xold - 1][yold] = board[0][yold];
		board[0][yold] = f;
	}
	
}

bool Board::can_it_move_for_pawn(int xold, int yold, int xnew, int ynew) {
	int nteam = board[xnew][ynew]->getteam();
	int oteam = board[xold][yold]->getteam();
	char notype = board[xnew][yold]->gettype();
	bool can = board[xold][yold]->can_it_move_to(xold, yold, xnew, ynew);
	bool u1 = ((nteam == 1 || nteam == 3) && oteam == 2);
	bool u2 = ((nteam == 2 || nteam == 4) && oteam == 1);

	if (notype == 'p' && checkonenpassant(xold, yold, xnew, ynew))
	{
		return true;
	}
	if (u1 || u2) {
		return can;
	}
	else {
		if ((yold == 1 && oteam == 1) || (yold == 6 && oteam == 2)) {
			int e = abs(ynew - yold);
			if (e < 3 && xold == xnew) return true;
			else return false;
		}
		else {
			int e = abs(ynew - yold);
			if (e < 2 && xold == xnew) return true;
			else return false;
		}
	}

}

bool Board::checkonenpassant(int xold, int yold, int xnew, int ynew) {
	int noteam = board[xnew][yold]->getteam();
	int oteam = board[xold][yold]->getteam();
	char notype = board[xnew][yold]->gettype();
	int i = moves.size() - 1;

	bool u3 = ((noteam == 2 && notype == 'p') && oteam == 1 && yold == 4);
	bool u4 = ((noteam == 1 && notype == 'p') && oteam == 2 && yold == 3);
	bool u5 = false;
	if (i >= 1)
	{
		int x = moves[i][0] - 'a', y = moves[i][1] - '0';
		int xn = moves[i][2] - 'a', yn = moves[i][3] - '0';
		if ((x == xnew && xn == xnew) && (abs(y - yn) == 2)) u5 = true;
	}

	if ((u3 || u4) && u5) return true;
	else return false;
}


void Board::enpassant(int xold, int yold, int xnew, int ynew) {
	board[xnew][yold] = &empty;
	board[xnew][ynew] = board[xold][yold];
	board[xold][yold] = &empty;
}

bool Board::nothingisbetween(int x, int y, int x1, int y1) {
	if (x == x1 || y == y1) {
		if (x == x1) {
			for (int j = min(y, y1) + 1; j < max(y, y1); j++) {
				if (board[x][j]->getteam() != 0) return false;
			}
		}
		else {
			for (int j = min(x, x1) + 1; j < max(x, x1); j++) {
				if (board[j][y]->getteam() != 0) return false;
			}
		}
		return true;
	}
	else if (x + y == x1 + y1) {
		for (int j = min(y, y1) + 1; j < max(y, y1); j++) {
			if (board[x+y-j][j]->getteam() != 0) return false;
		}
		return true;
	}
	else if (x - y == x1 - y1) {
		for (int j = min(y, y1) + 1; j < max(y, y1); j++) {
			if (board[x - y + j][j]->getteam() != 0) return false;
		}
		return true;
	}
	else return false;
}

void Board::display() {
	system("cls");
	string str;

	for (int i = 0; i < moves.size(); i++) cout << moves[i][0] << moves[i][1] << "->" << moves[i][2] << moves[i][3]  << endl;  // Выведение истории ходов
	cout << endl; 

	cout << "    |----|----|----|----|----|----|----|----|\n";

	for (int j = 0; j < 8; j++) 
	{
		cout << " " << 8 - j << "  |";

		for (int i = 0; i < 8; i++) {
			char g = board[i][7 - j]->gettype();

			if (board[i][7 - j]->getteam()== 1 || board[i][7 - j]->getteam() == 3)
			{
				if (board[i][7 - j]->getteam() == 3) str = str+ " wKg" + '|';
				else str = str  + " w" + g + " " + '|';
			}
			else if (board[i][7 - j]->getteam() == 2 || board[i][7 - j]->getteam() == 4)
			{
				if (board[i][7 - j]->getteam() == 4) str = str + " bKg" + '|';
				else str = str+ " b" + g + " " + '|'; 
			}
			else 
			{
				str = str + " " + g + "  " + '|';
			}

		}
		cout << str << endl;
		cout << "    |----|----|----|----|----|----|----|----|\n";
		str = "";
	}
	cout << "\n      a    b    c    d    e    f    g    h\n";
}

bool Board::checkmate() {
	bool k1 = false;
	bool k2 = false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) 
		{
			if (board[i][j]->getteam() == 3) k1 = true;
			if (board[i][j]->getteam() == 4) k2 = true;
		}
	}
	if (!k1) {
		cout << "Black Win!\n";
		return true;
	}
	else if (!k2) {
		cout << "White Win!\n";
		return true;
	}
	else return false;
}

void Board::start() {
	int turn = 0;
	bool win = false;
	do {
		display();
		move(turn);
		win = checkmate();													// Проверка на взятие Короля
		bool y = attackon(3), y2 = attackon(4);								// Проверка на шах
		if (y || y2) system("pause");
		turn++;
	} while (!win);
	system("pause");
}

void Board::move(int turn) {

	bool k = true, gg = true;
	string xch1,xch2;
	int xold, yold, xnew, ynew;
	do {
		k = true;
		do {
			cin >> xch1;															     // Ввод первой координаты
			xold = xch1[0] - 'a';
			yold = xch1[1] - '0';
			yold -= 1;

			int oteam = board[xold][yold]->getteam();
			bool l = false;
			bool tchwhite = ((oteam == 1 || oteam == 3) && turn % 2 == 0);
			bool tchblack = ((oteam == 2 || oteam == 4) && turn % 2 == 1);

			if (tchwhite || tchblack) l = true;                                          // Проверят, взяли ли мы фигуру тех, кто ходит
			if ((xold < 8 && xold >= 0) && (yold < 8 && xold >= 0) && l) k = false;
			else cout << "Incorrect position, try again\n";

		} while (k);

		k = true;
		do {
			cin >> xch2;																 // Ввод второй координаты		
			xnew = xch2[0] - 'a';
			ynew = xch2[1] - '0';
			ynew -= 1;
			if (xch1 != xch2) {
				bool y = checkposition(xold, yold, xnew, ynew, turn);					 // Проверка возможности хода
				if (!y) k = false;
				else cout << "Incorrect position, try again\n";
			}
			else k = false;
		} while (k);

		if (xch1 != xch2) gg = false;													// Отпуск фигуры при одинаковых координатах
	} while (gg);

	int nteam = board[xnew][ynew]->getteam();
	char otype = board[xold][yold]->gettype();
	bool can = board[xold][yold]->can_it_move_to(xold, yold, xnew, ynew);
	bool tchblack = ((nteam == 2 || nteam == 4) && turn % 2 == 0);
	bool tchwhite = ((nteam == 1 || nteam == 3) && turn % 2 == 1);

	k = false;

	if (tchwhite || tchblack) board[xnew][ynew] = &empty;                             // Проверяет атака напрямлена ли на противника или просто ходит на пустую клетку,
	                                                                                  // если на противника, то заменяет противника на пустую клетку

	if (!can && otype == 'K') {
		castlecastle(xold, yold, xnew);                                               // рокировка
	}

	else if (otype == 'p' && checkonenpassant(xold, yold, xnew, ynew)) { 
		enpassant(xold, yold, xnew, ynew);                                            // удар на проходе
	}
	else {                                                                            // else - стандарный своп фигур
		Figure* f;
		f = board[xold][yold];
		board[xold][yold] = board[xnew][ynew];
		board[xnew][ynew] = f;
	}
	
	char ntype = board[xnew][ynew]->gettype();
	nteam = board[xnew][ynew]->getteam();

	if (ntype == 'p' && (ynew == 7 || ynew == 0))                                     // Проверка на нахожденние пешки на последней линии и замене на ферзя
	{
		if (nteam == 1) board[xnew][ynew] = &queen1;
		else  board[xnew][ynew] = &queen2;
	}

	moves.push_back(xch1 + xch2);                                                     // дополнение истории ходов

}

bool Board::checkposition(int xold, int yold,int xnew,int ynew,int turn) {

	bool l = false, v = false, can = board[xold][yold]->can_it_move_to(xold, yold, xnew, ynew);
	char otype = board[xold][yold]->gettype(), ntype = board[xnew][ynew]->gettype();
	int oteam = board[xold][yold]->getteam(), nteam = board[xnew][ynew]->getteam();

	if (otype != 'k' && otype != 'p' && otype != 'K') {                               //Проверяет возможность хода для фигур кроме Короля,Коня и пешки

		if ((this->nothingisbetween(xold, yold, xnew, ynew)) && can) v = true;
		else v = false;
	}
	else {

		if (can && otype == 'k') v = true;											  //Проверка для коня

		else if (otype == 'K' && can_it_move_for_king(xold, yold, xnew, ynew))	      //Проверка для Короля
		{ 
			v = true; 
		}

		else {
			if (can_it_move_for_pawn(xold, yold, xnew, ynew)) v = true;			      //Проверка для пешки
		}
	}

	bool bbt = ((nteam == 1 || nteam == 3) && turn % 2 == 1);
	bool bwt = ((nteam == 2 || nteam == 4) && turn % 2 == 0);

	if (bbt || bwt || nteam == 0) l = true;                                           // Проверяет взятие своих фигур
	
	if ((xold < 8 && xold >= 0) && (yold < 8 && xold >= 0) && l && v) return false;
	else return true;

}


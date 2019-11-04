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

bool Board::can_it_move_for_king(int xold, int yold, int xnew, int ynew) {
	if (board[xold][yold]->can_it_move_to(xold,yold,xnew,ynew)) return true;
	else {
		bool b = false;
		if (board[xold][yold]->getteam() == 3) {
			for (int i = 0; i < moves.size(); i++) {
				if (moves[i][0] == 'e' && moves[i][1] == '1') b = true;
			}
		}
		else {
			for (int i = 0; i < moves.size(); i++) {
				if (moves[i][0] == 'e' && moves[i][1] == '8') b = true;
			}
		}
		if (!b) {
			if (xnew == 6 || xnew == 2) return true;
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

bool Board::can_it_move_for_pawn(int xold, int yold, int xnew, int ynew) {
	bool u1 = ((board[xnew][ynew]->getteam() == 1 || board[xnew][ynew]->getteam() == 3) && board[xold][yold]->getteam() == 2);
	bool u2 = ((board[xnew][ynew]->getteam() == 2 || board[xnew][ynew]->getteam() == 4) && board[xold][yold]->getteam() == 1);
	if (u1 || u2) {
		return board[xold][yold]->can_it_move_to(xold, yold, xnew, ynew);
	}
	else {
		if ((yold == 1 && board[xold][yold]->getteam() == 1) || (yold == 6 && board[xold][yold]->getteam() == 2)) {
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
	for (int i = 0; i < moves.size(); i++) cout << moves[i][0] << moves[i][1] << "->" << moves[i][2] << moves[i][3]  << endl;
	cout << endl; 
	cout << "    |----|----|----|----|----|----|----|----|\n";
	for (int j = 0; j < 8; j++) {
		cout << " " << 8 - j << "  |";
		for (int i = 0; i < 8; i++) {
			char g = board[i][7 - j]->gettype();
			if (board[i][7 - j]->getteam()== 1 || board[i][7 - j]->getteam() == 3) {
				if (board[i][7 - j]->getteam() == 3) str = str+ "wKg" + " " + '|';
				else str = str  + " w" + g + " " + '|';
			}
			else if (board[i][7 - j]->getteam() == 2 || board[i][7 - j]->getteam() == 4) {
				if (board[i][7 - j]->getteam() == 4) str = str + "bKg" + " " + '|';
				else str = str+ " b" + g + " " + '|';
			}
			else {
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
		for (int j = 0; j < 8; j++) {
			if (board[i][j]->getteam() == 3) k1 = true;
			if (board[i][j]->getteam() == 4) k2 = true;
		}
	}
	if (!k1) {
		cout << "Black Win!";
		return true;
	}
	else if (!k2) {
		cout << "White Win!";
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
		win = checkmate();
		turn+=2;
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
			cin >> xch1;
			xold = xch1[0] - 'a';
			yold = xch1[1] - '0';
			yold -= 1;
			bool l = false;
			if (((board[xold][yold]->getteam() == 1 || board[xold][yold]->getteam() == 3) && turn % 2 == 0) || ((board[xold][yold]->getteam() == 2 || board[xold][yold]->getteam() == 4) && turn % 2 == 1)) l = true;
			if ((xold < 8 && xold >= 0) && (yold < 8 && xold >= 0) && l) k = false;
			else cout << "Incorrect position, try again\n";
		} while (k);
		k = true;
		do {
			cin >> xch2;
			xnew = xch2[0] - 'a';
			ynew = xch2[1] - '0';
			if (xch1 != xch2) {
				ynew -= 1;
				bool l = false, v = false;
				if (board[xold][yold]->gettype() != 'k' && board[xold][yold]->gettype() != 'p' && board[xold][yold]->gettype() != 'K') {
					if ((this->nothingisbetween(xold, yold, xnew, ynew)) && (board[xold][yold]->can_it_move_to(xold, yold, xnew, ynew))) v = true;
					else v = false;
				}
				else {
					if (board[xold][yold]->can_it_move_to(xold, yold, xnew, ynew) && board[xold][yold]->gettype() == 'k') v = true;
					else if (can_it_move_for_king(xold, yold, xnew, ynew) && board[xold][yold]->gettype() == 'K') v = true;
					else {
						if (can_it_move_for_pawn(xold, yold, xnew, ynew)) v = true;
					}
				}
				if (((board[xnew][ynew]->getteam() == 1 || board[xnew][ynew]->getteam() == 3) && turn % 2 == 1) || ((board[xnew][ynew]->getteam() == 2 || board[xnew][ynew]->getteam() == 4) && turn % 2 == 0) || board[xnew][ynew]->getteam() == 0) l = true;
				if ((xold < 8 && xold >= 0) && (yold < 8 && xold >= 0) && l && v) k = false;
				else cout << "Incorrect position, try again\n";
			}
			else k = false;
		} while (k);
		if (xch1 != xch2) gg = false;
	} while (gg);
	moves.push_back(xch1 + xch2);
	k = false;
	if (((board[xnew][ynew]->getteam() == 1 || board[xnew][ynew]->getteam() == 3) && turn % 2 == 1) || ((board[xnew][ynew]->getteam() == 2 || board[xnew][ynew]->getteam() == 4) && turn % 2 == 0)) k = true;
	if (k) board[xnew][ynew] = &empty;
	if (!board[xold][yold]->can_it_move_to(xold, yold, xnew, ynew) && board[xold][yold]->gettype() == 'K') {
		castlecastle(xold, yold,xnew);
	}
	else {
		Figure* f;
		f = board[xold][yold];
		board[xold][yold] = board[xnew][ynew];
		board[xnew][ynew] = f;
	}
	if (board[xnew][ynew]->gettype() == 'p' && (ynew == 7 || ynew == 0)) {
		if (board[xnew][ynew]->getteam() == 1) board[xnew][ynew] = &queen1;
		else  board[xnew][ynew] = &queen2;
	}

}


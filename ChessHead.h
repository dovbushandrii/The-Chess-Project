#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;
/* team:
0 - empty slot;
1 - white team;
2 - black team;
3 - white King;
4 - black King;
*/



class Figure {
protected:
	int team;
	char type;
public:
	virtual bool can_it_move_to(int x, int y, int x1, int y1) = 0;
	int getteam() {
		return team;
	}
	char gettype() {
		return type;
	}
};

class EmptySquare : public Figure {
public: EmptySquare() {
	team = 0;
	type = ' ';
}
	  bool can_it_move_to(int x, int y, int x1, int y1) override {
		  return true;
	  }
};

class King : public Figure {
public:
	King(int x) {
		team = x;
		type = 'K';
	}
	bool can_it_move_to(int x, int y, int x1, int y1) override;

};

class Queen : public Figure {
public:
	Queen(int x) {
		team = x;
		type = 'Q';
	}
	bool can_it_move_to(int x, int y, int x1, int y1) override;
};

class Bishop : public Figure {
public:
	Bishop(int x) {
		team = x;
		type = 'B';
	}
	bool can_it_move_to(int x, int y, int x1, int y1) override;
};

class Pawn : public Figure {
public:
	Pawn(int x) {
		team = x;
		type = 'p';
	}
	bool can_it_move_to(int x, int y, int x1, int y1) override;

};

class Rook : public Figure {
public:
	Rook(int x) {
		team = x;
		type = 'R';
	}
	bool can_it_move_to(int x, int y, int x1, int y1) override;
};

class Knight : public Figure {
public:
	Knight(int x) {
		team = x;
		type = 'k';

	}
	bool can_it_move_to(int x, int y, int x1, int y1) override;
};

class Board {
public:
	Board();
	void start();
	
private:

	Figure* board[8][8];
	vector<string> moves;

	int getkingx(int x);
	int getkingy(int x);
	bool nothingisbetween(int x, int y, int x1, int y1);
	void display();
	void move(int turn);
	bool can_it_move_for_pawn(int xold,int yold,int xnew,int ynew);
	bool can_it_move_for_king(int xold, int yold, int xnew, int ynew);
	void castlecastle(int xold,int yold,int xnew);
	bool checkmate();
	bool attackon(int xk);
	bool checkposition(int xold, int yold, int xnew, int ynew,int turn);
	void enpassant(int xold, int yold, int xnew,int ynew);
	bool checkonenpassant(int xold, int yold, int xnew, int ynew);
	
	Rook rookl1 = Rook(1);
	Knight knightl1 = Knight(1);
	Bishop bishopl1 = Bishop(1);
	Queen queen1 = Queen(1);
	King king1 = King(3);
	Bishop bishopp1 = Bishop(1);
	Knight knightp1 = Knight(1);
	Rook rookp1 = Rook(1);
	Rook rookl2 = Rook(2);
	Knight knightl2 = Knight(2);
	Bishop bishopl2 = Bishop(2);
	Queen queen2 = Queen(2);
	King king2 = King(4);
	Bishop bishopp2 = Bishop(2);
	Knight knightp2 = Knight(2);
	Rook rookp2 = Rook(2);
	Pawn pawn1 = Pawn(1);
	Pawn pawn2 = Pawn(2);
	EmptySquare empty = EmptySquare();
	
};




#pragma once

#include <random>
#include <vector>
#include <iostream>

using namespace std;

class Board {
private:
	int width;
	int mines;
	vector<vector<char>> board;
	vector<vector<int>> positions = {
			{-1, 0},
			{-1, -1},
			{-1, 1},
			{0,  1},
			{1,  1},
			{1,  0},
			{1,  -1},
			{0,  -1},
	};

	void placeMines();

	void uncoverTiles(int row, int column);

public:
	Board(int width, int mines) : width(width), mines(mines) {
		vector<char> row(width, 'E');
		vector<vector<char>> filledBoard(width, row);
		board = filledBoard;

		placeMines();
		printBoard();
	}

	bool isGuessCorrect(int row, int column);

	bool isTileInRange(int row, int column) const;

	bool isBoardClean();

	void printBoard() const;

	void showMines();
};

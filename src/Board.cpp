#include "Board.h"

void Board::placeMines() {
	int count = 0, row, column;

	do {
		do {
			random_device rd;
			mt19937 generator(rd());
			uniform_int_distribution<> range(0, width - 1);

			row = range(generator);
			column = range(generator);
		} while (board[row][column] != 'E');
		board[row][column] = 'M';
		count++;
	} while (count < mines);
}

bool Board::isGuessCorrect(int row, int column) {
	if (board[row][column] == 'M') {
		board[row][column] = 'X';

		return false;
	} else {
		uncoverTiles(row, column);

		return true;
	}
}

void Board::uncoverTiles(int row, int column) {
	int mine = 0;

	for (int i = 0; i < 8; ++i) {
		int x = row + positions[i][0], y = column + positions[i][1];
		if (x >= 0 && x < width && y >= 0 && y < width) {
			if (board[x][y] == 'M') ++mine;
		}
	}

	if (mine) {
		board[row][column] = mine + '0';
	} else {
		board[row][column] = 'B';
		for (int i = 0; i < 8; ++i) {
			int x = row + positions[i][0], y = column + positions[i][1];
			if (x >= 0 && x < width && y >= 0 && y < width && board[x][y] == 'E')
				uncoverTiles(x, y);
		}
	}
}

bool Board::isTileInRange(int row, int column) const {
	return row >= 0 && column >= 0 && row < width && column < width;
}

bool Board::isBoardClean() {
	for (auto & row : board)
		for (int column = 0; column < board.size(); ++column)
			if (row[column] == 'E') return false;

	return true;
}

void Board::printBoard() const {
	for (int column = 0; column < board.size(); ++column)
		cout << column << "\t";
	cout << endl;

	for (int row = 0; row < board.size(); ++row) {
		for (char tile : board[row]) {
			switch (tile) {
				case 'B': {
					cout << "◻";
					break;
				}
				case 'X': {
					cout << "⌧";
					break;
				}
				case '1': {
					cout << "❶";
					break;
				}
				case '2': {
					cout << "❷";
					break;
				}
				case '3': {
					cout << "❸";
					break;
				}
				case '4': {
					cout << "❹";
					break;
				}
				case '5': {
					cout << "❺";
					break;
				}
				case '6': {
					cout << "❻";
					break;
				}
				case '7': {
					cout << "❼";
					break;
				}
				case '8': {
					cout << "❽";
					break;
				}
				default: {
					cout << "■";
					break;
				}
			}
			cout << "\t";
		}

		cout << row << endl;
	}

	cout << endl;
}

void Board::showMines() {
	for (int column = 0; column < board.size(); ++column)
		cout << column << "\t";
	cout << endl;

	for (int row = 0; row < board.size(); ++row) {
		for (char tile : board[row]) {
			if (tile == 'M') {
				cout << "◉";
			} else if (tile == 'X') {
				cout << "⌧";
			} else {
				cout << "◻";
			}

			cout << "\t";
		}

		cout << row << endl;
	}

	cout << endl;
}

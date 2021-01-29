#include "Game.h"

void Game::showOptions() {
	status = NOT_PLAYING;

	cout << "MENU:" << endl;
	cout << "\tP - PLAY" << endl;
	cout << "\tS - SCOREBOARD" << endl;
	cout << "\tQ - QUIT" << endl;

	cout << "OPTION: ";
	char option;
	cin >> option;

	while (cin.fail()) {
		cout << "WRONG INPUT. TRY AGAIN." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cout << endl;
		showOptions();
		cout << "OPTION: ";
		cin >> option;
	}

	cout << endl;

	switch (option) {
		case 'P':
		case 'p':
			playGame();
			break;
		case 'S':
		case 's':
			displayScores();
			break;
		case 'Q':
		case 'q':
			quitGame();
			break;
		default:
			cout << "WRONG INPUT. TRY AGAIN." << endl;
			showOptions();
	}
}

Board Game::setNewBoard(char level) {
	switch (level) {
		case 'M':
		case 'm':
			return Board(12, 24);
		case 'H':
		case 'h':
			return Board(15, 45);
		default:
			return Board(9, 5);
	}
}

void Game::playGame() {
	char level = setDifficulty();
	Board board = setNewBoard(level);

	status = Status::PLAYING;
	auto start = chrono::high_resolution_clock::now();

	cout << "ACTIONS:" << endl;
	cout << "\tD - DEFUSE" << endl;
	cout << "\tG - GIVE UP" << endl;
	cout << "\tH - HELP" << endl;

	while (status == PLAYING) {
		cout << "OPTION: ";
		char action;
		cin >> action;

		cout << endl;

		switch (action) {
			case 'D':
			case 'd': {
				defuse(board);
				break;
			}
			case 'G':
			case 'g': {
				status = LOST;
				break;
			}
			case 'H':
			case 'h': {
				cout << "ACTIONS:" << endl;
				cout << "\tD - DEFUSE" << endl;
				cout << "\tG - GIVE UP" << endl;
				cout << "\tH - HELP" << endl;
				break;
			}
			default: {
				cout << "INVALID OPTION. TRY AGAIN." << endl;
			}
		}
	}

	if (status == WON) {
		cout << " ██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗██╗███╗   ██╗" << endl;
		cout << " ╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██║████╗  ██║" << endl;
		cout << "  ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║██╔██╗ ██║" << endl;
		cout << "   ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║██║╚██╗██║" << endl;
		cout << "    ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝██║██║ ╚████║" << endl;
		cout << "    ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝" << endl;
		cout << endl;

		auto stop = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsed = stop - start;
		int score = ceil(elapsed.count());
		cout << "SCORE: " << score << endl;

		saveScore(score, level);
	} else {
		cout << "  ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ " << endl;
		cout << " ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗" << endl;
		cout << " ██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝" << endl;
		cout << " ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗" << endl;
		cout << " ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║" << endl;
		cout << "  ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝" << endl;
		cout << endl;
	}

	board.showMines();
	status = NOT_PLAYING;

	showOptions();
}

char Game::setDifficulty() {
	cout << "PICK A LEVEL OF DIFFICULTY:" << endl;
	cout << "\t E - EASY" << endl;
	cout << "\t M - MEDIUM" << endl;
	cout << "\t H - HARD" << endl;

	char level;

	while (true) {
		cout << "LEVEL: ";
		cin >> level;

		if (level == 'E' || level == 'e' || level == 'M' || level == 'm' || level == 'H' || level == 'h') {
			break;
		} else {
			cout << "WRONG INPUT. TRY AGAIN." << endl;
		}
	}

	cout << endl;

	return level;
}

void Game::defuse(Board &board) {
	positionInput(board, [&](int row, int column) -> void {
		if (!board.isGuessCorrect(row, column)) {
			status = LOST;
		}

		if (board.isBoardClean()) {
			status = WON;
		}
	});
}

template<typename F>
void Game::positionInput(const Board &board, F function) {
	int row, column;

	while (true) {
		cout << "ROW: ";
		cin >> row;

		while (cin.fail()) {
			cout << "NOT A NUMBER. TRY AGAIN." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "ROW: ";
			cin >> row;
		}

		cout << "COLUMN: ";
		cin >> column;

		while (cin.fail()) {
			cout << "NOT A NUMBER. TRY AGAIN." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "COLUMN: ";
			cin >> column;
		}

		if (board.isTileInRange(row, column)) {
			function(row, column);

			board.printBoard();
			break;
		}

		cout << "POSITION OUT OF RANGE. TRY AGAIN." << endl;
	}
}

void Game::saveScore(int score, char level) {
	string name, difficulty;
	cout << "ENTER YOUR NAME: ";
	cin >> name;

	cout << endl;

	switch (level) {
		case 'M':
		case 'm':
			difficulty = "MEDIUM";
			break;
		case 'H':
		case 'h':
			difficulty = "HARD";
			break;
		default:
			difficulty = "EASY";
			break;
	}

	ofstream file;
	file.open("scoreboard.txt", ios_base::app);
	file << name << "\t" << difficulty << "\t" << score << "\n";
}

void Game::displayScores() {
	string line;
	ifstream file("scoreboard.txt");
	if (file.is_open()) {
		while (getline(file, line))
			cout << line << '\n';

		file.close();
	} else {
		cout << "SCOREBOARD IS EMPTY!" << endl;
	}

	cout << endl;

	showOptions();
}

void Game::quitGame() {
	exit(0);
}

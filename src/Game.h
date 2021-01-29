#pragma once

#include <iostream>
#include <chrono>
#include <cmath>
#include <fstream>

#include "Board.h"

using namespace std;

class Game {
private:
	enum Status {
		NOT_PLAYING,
		PLAYING,
		WON,
		LOST,
	};

	Status status = Status::NOT_PLAYING;

	static Board setNewBoard(char level);

	void playGame();

	static char setDifficulty();

	void defuse(Board &board);

	template<typename F>
	void positionInput(const Board &board, F function);

	static void saveScore(int score, char level);

	void displayScores();

	static void quitGame();

public:
	Game() = default;

	void showOptions();
};

#include "pch.h"
#include <iostream>
#include <vector>

int global_row;
int global_col;
std::vector<std::vector<bool>> Board_V;
std::vector<std::vector<bool>> Next_Board_V;

void setup(int row, int col) {
	int v;
	Board_V.resize(row);
	Next_Board_V.resize(row);

	for (int i = 0; i < row; i++) {
		Board_V[i] = std::vector<bool>(col);
	}
	for (int i = 0; i < row; i++) {
		Next_Board_V[i] = std::vector<bool>(col);
	}
	for (int i=0; i < global_row ; i++) {
		for (int j = 0; j < global_col; j++) {
			if (i == 0 || i == global_row - 1 || j == 0 || j == global_col - 1) {
				Board_V[i][j] = false;
			}
			else {
				v = rand() % 100;
				if (v <= 50) {
					Board_V[i][j] = 1;
				}
				else {
					Board_V[i][j] = 0;
				}
			}
		}
	}
}

void output() {
	for (int i = 1; i < global_row - 1; i++) {
		for (int j = 1; j < global_col - 1; j++) {
			
			if (Board_V[i][j] == 1) {
				std::cout << "*";
			}
			else {
				std::cout << "o";
			}
			
		}
		std::cout << "\n";
	}
}

void NextStep() {
	int current_cell = 0;
	int neighbours = 0;

	for (int i = 1; i < global_row - 1; i++) {
		for (int j = 1; j < global_col - 1; j++) {
			neighbours = 0;
			current_cell = Board_V[i][j];

			for (int k = i - 1; k <= i + 1; k++) {
				for (int l = j - 1; l <= j + 1; l++) {
					if (k == i && l == j) {	
					}
					else {
						neighbours += Board_V[k][l];
					}
				}
			}
			//std::cout << neighbours;


			switch (neighbours) {
			case 0:
			case 1: Next_Board_V[i][j] = 0;
				break;
			case 2: 
				if (current_cell == 1) {
					Next_Board_V[i][j] = 1;
				}
				else {
					Next_Board_V[i][j] = 0;
				}
				break;
			case 3: Next_Board_V[i][j] = 1;
				break;
			default: Next_Board_V[i][j] = 0;
				break;
			}
		}
		//std::cout << "\n";
	}
	std::swap(Board_V, Next_Board_V);
}

int main()
{
	std::cout << "Please enter the number of rows: ";
	while (global_row <= 0) {
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin >> global_row;
		if (global_row <= 0) {
			std::cout << "Sorry, number not recognised. Is it greater than 0? Please try again: ";
			std::cin.clear();
		}
	}
	std::cout << "Please enter the number of columns: ";

	while (global_col <= 0) {
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin >> global_col;
		if (global_col <= 0) {
			std::cout << "Sorry, number not recognised. Is it greater than 0? Please try again: ";
			std::cin.clear();
		}
	}
	global_row += 2;
	global_col += 2;
	setup(global_row, global_col);
	std::cout << "Initial State: \n";
	output();

	while (true) {
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin.ignore();
		NextStep();
		std::cout << "One Step Later: \n";
		output();
		std::cin.clear();
	}
}
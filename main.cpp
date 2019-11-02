//SIMPLE SUDOKU SOLVER
#include <iostream>
#include <chrono>

inline int getValueAtCell(int row, int col, const int* array) {
	//std::cout << array[row * 9 + col];
	return array[row * 9 + col];
}

bool ifCanAddToRow(int number, int row, const int* array) {
	for (int i = 0; i < 9; i++) {
		if (array[row * 9 + i] == number) {
			return false;
		}
	}
	return true;
}

bool ifCanAddToCol(int number, int col, const int* array) {
	for (int i = 0; i < 9; i++) {
		if (array[i * 9 + col] == number) {
			return false;
		}
	}
	return true;
}

bool ifCanAddToBox(int number, int row, int col, const int* array) {

	int boxRow = row / 3;
	int boxCol = col / 3;

	for (int r = boxRow * 3; r < boxRow * 3 + 3; ++r) {
		for (int c = boxCol * 3; c < boxCol * 3 + 3; ++c) {
			if (array[r * 9 + c] == number) {
				return false;
			}
		}
	}

	return true;
}

void printPuzzle(const int* array) {
	for (int row = 0; row < 9; ++row)
	{
		if (row % 3 == 0) std::cout << "\n";
		for (int col = 0; col < 9; ++col)
		{
			if (col % 3 == 0) std::cout << " ";
			std::cout << " " << getValueAtCell(row, col, array);
		}
		std::cout << "\n";
	}
}

bool checkForNoCollision(int pNum, int row, int col, const int* array) {
	return 
		ifCanAddToRow(pNum, row, array) && 
		ifCanAddToCol(pNum, col, array) && 
		ifCanAddToBox(pNum, row, col, array);
}

bool solvePuzzleRecursive(int row, int col, int* array) {
	if (col > 8) {
		col = 0;
		row++;
	}
	if (row > 8) {
		return true;
	}
	if (array[row * 9 + col] == 0) {
		for (int pNum = 1; pNum < 10; pNum++) {
			if (checkForNoCollision(pNum, row, col, array))
			{
				array[row * 9 + col] = pNum;
				if (solvePuzzleRecursive(row, col + 1, array)) {
					return true;
				}
			}
		}
		array[row * 9 + col] = 0;
	}
	else {
		return solvePuzzleRecursive(row, ++col, array);
	}
	return false;
}

void emptyOutArray(int* array) {
	for (int i = 0; i < 91; ++i) {
		array[i] = 0;
	}
}

int main(int argc, char* argv[]) {
	//int* sudokuArray = createNewPartialArray();
	//need optimization here
	//maybe use stack allocation
	//pointer to array

	int sudokuArray[91] = {
		4,0,0,  0,0,0,  0,0,7,
		0,0,0,  7,9,0,  3,0,0,
		5,7,9,  4,0,0,  0,0,0,
	
		0,6,0,  0,0,0,  0,8,0,
		0,0,0,  1,3,7,  5,0,6,
		0,5,4,  2,0,0,  7,0,9,
	
		2,8,0,  9,0,5,  0,0,1,
		0,0,3,  6,0,2,  0,0,0,
		7,0,0,  0,0,0,  0,0,0,
	};

	std::cout << "INITIAL PUZZLE:\n";
	printPuzzle(sudokuArray);


	//emptyOutArray(sudokuArray);

	auto start = std::chrono::high_resolution_clock::now();
	solvePuzzleRecursive(0, 0, sudokuArray);
	auto stop = std::chrono::high_resolution_clock::now();

	
	std::cout << "\nCOMPLETED PUZZLE:\n";
	printPuzzle(sudokuArray);

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
	std::cout << "\nTime took : " << time << " microseconds\n";
	
	std::cout << "\n\n";
	system("PAUSE");
	return 0;
}





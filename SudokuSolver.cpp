#include "SudokuSolver.hpp"

/**
   @post: sets up the new board with all zeros
*/
SudokuSolver::SudokuSolver(){
    board = new int*[9];
    for (int i = 0; i < 9; i++) {
        board[i] = new int[9];
        for (int j = 0; j < 9; j++) {
            board[i][j] = 0;
        }
    }
    solvable = false;
}

/**
@param: a string that contains the input file
@post: creates a board by using the numbers in the text file and inputing it into the 2D pointer then
calls the Solver function to see if the puzzle is solvable and sets the solvable variable accordingly.
*/
SudokuSolver::SudokuSolver(std::string input_file){
     std::ifstream my_file(input_file);
    if (!my_file) {
        std::cerr << "Error: Could not open input file" << std::endl;
        exit(1);
    }
    board = new int*[9];
    for (int i = 0; i < 9; i++) {
        board[i] = new int[9];
    }

    std::string line, num;
    int i = 0;
    while (std::getline(my_file, line) && i < 9) {
        std::string str = line;
        int j = 0;
        std::stringstream iss(str);
        while(iss.good()) {
            std::getline(iss, num, ',');
            board[i][j] = stoi(num);
            j++;
        }
        i++;
    }
    my_file.close();
    if(Solver()){
        setSolvable();
    }
    else{
        solvable = false;
    }
}

/**
@post: checks the location of the next 0 and it sees if it can put a number between 1-9 into it while 
following sudoku rules. It recurses to solve 0 in the grid and if it can't it will backtrack  then try 
the next valid value.
*/
bool SudokuSolver::Solver(){
    Sudoku::Location current_location = returnNextEmpty();
    if(current_location.row == -1 && current_location.col == -1){
        return true;
    }
    for(int i = 0; i < 9; i++){
        if(checkLegalValue((i + 1), current_location)){
            board[current_location.row][current_location.col] = (i + 1);
            if(Solver()){
                return true;
            }
            board[current_location.row][current_location.col] = 0;
        }
    }
    return false;
}

/**
@return: the solvable flag
*/
bool SudokuSolver::isPuzzleSolvable(){
    return solvable;
}

/**
@post: sets the solvable flag to true
*/
void SudokuSolver::setSolvable(){
    solvable = true;
}

/**
@return: a 2D pointer to int that contains the numbers of the board
*/
int** SudokuSolver::getPuzzleNumbers(){
    int** nums;
    nums = new int*[9];
    for(int i = 0; i < 9; i++){
        nums[i] = new int[9];
    }
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            nums[i][j] = board[i][j];
        }
    }
    return nums;
}

/**
@param: a 2D pointer to int
@post: replaces the values in the board with the values in the param
*/
void SudokuSolver::setPuzzleNumbers(int** puzzle){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            board[i][j] = puzzle[i][j];
        }
    }
}

/**
@return: a Location object of the next 0 on the board
*/
Sudoku::Location SudokuSolver::returnNextEmpty(){
    Sudoku::Location loc;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] == 0){
                loc.row = i;
                loc.col = j;
                return loc;
            }
        }
    }
    loc.row = -1;
    loc.col = -1;
    return loc;
}

/**
@param: a value from 1-9
@param: a location(row, col) on the board
@return: true if the value can be placed in the location according to sudoku rules and false otherwise
*/
bool SudokuSolver::checkLegalValue(int value, Sudoku::Location location){
    for(int i = 0; i < 9; i++){
        if(board[location.row][i] == value){
            return false;
        }
    }
    for(int i = 0; i < 9; i++){
        if(board[i][location.col] == value){
            return false;
        }
    }
    int grid_row = (location.row / 3) * 3;
    int grid_col = (location.col / 3) * 3;
    for(int i = grid_row; i < grid_row + 3; i++){
        for(int j = grid_col; j < grid_col + 3; j++){
            if(board[i][j] == value){
                return false;
            }
        }
    }
    return true;
}

/**
@post: displays all of the numvers on the board with X for the locations that have a 0
*/
void SudokuSolver::display(){
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            std::cout << "- - - - - - - - - - - -" << std::endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                std::cout << " | ";
            }
            if (board[i][j] == 0) {
                std::cout << "X";
            } 
            else {
                std::cout << board[i][j];
            }
            if(j < 8){
                std::cout << " ";
            }
        }
        if(i < 8){
            std::cout << std::endl;
        }
    }
}
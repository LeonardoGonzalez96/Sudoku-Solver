#ifndef SUDOKU_SOLVER_HPP_
#define SUDOKU_SOLVER_HPP_
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// This is the SudokuSolver class that creates a sudoku board based off a input file and solves it if its possible
// users can display the board and also edit it by using the setPuzzleNumbers function with their own numbers

//We define Location within the Sudoku namespace.
namespace Sudoku
{ 
  struct Location
  {
    int row;
    int col;
  };
}

class SudokuSolver
{
public:
 
//Add your public members here
  SudokuSolver(); //default constructor

  /**
     @param: a string that contains the input file
     @post: creates a board by using the numbers in the text file and inputing it into the 2D pointer then
     calls the Solver function to see if the puzzle is solvable and sets the solvable variable accordingly.
  */
  SudokuSolver(std::string input_file);

  /**
     @post: checks the location of the next 0 and it sees if it can put a number between 1-9 into it while 
     following sudoku rules. It recurses to solve 0 in the grid and if it can't it will backtrack  then try 
     the next valid value.
  */
  bool Solver();

  /**
     @return: the solvable flag
  */
  bool isPuzzleSolvable();

  /**
     @post: sets the solvable flag to true
  */
  void setSolvable();

  /**
     @return: a 2D pointer to int that contains the numbers of the board
  */
  int** getPuzzleNumbers();

  /**
     @param: a 2D pointer to int
     @post: replaces the values in the board with the values in the param
  */
  void setPuzzleNumbers(int** puzzle);

  /**
     @return: a Location object of the next 0 on the board
  */
  Sudoku::Location returnNextEmpty();

  /**
     @param: a value from 1-9
     @param: a location(row, col) on the board
     @return: true if the value can be placed in the location according to sudoku rules and false otherwise
  */
  bool checkLegalValue(int value, Sudoku::Location location);

  /**
     @post: displays all of the numvers on the board with X for the locations that have a 0
  */
  void display();



private:
//Add your private members here
int** board; //the 2D pointer to int that contains the board
bool solvable; //a bool that contains true if the puzzle is solvable and false otherwise
};

#endif

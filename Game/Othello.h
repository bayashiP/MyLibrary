/****************************************************
Othello.h
 ****************************************************/
#include <cstdlib>
using namespace std;
#ifndef OTHELLO_H
#define OTHELLO_H

//State of the board
#define BLACK 2
#define WHITE 1
#define EMPTY 0

//Direction
typedef enum{
  N = 100,
  NE,
  E,
  SE,
  S,
  SW,
  W,
  NW
} Direction;


  
class Othello{
private:
  char **board;        //state of the board
  int b_size;          //size of the board (default:8x8)
  int num_piece_black; //number of pieces(black)
  int num_piece_white; //number of pieces(white)
  int turn;            //Current number of turn

public:

  //@function: Constructor  Othello()
  //@descript: Allocate memory for board & initialize
  //@argument: [s] size of the board (default: 8x8)
  //@cond    : s should be even and >= 4
  Othello(int s);


  //@function: Othello::initBoard()
  //@descript: Reset the board and counters to the initial state.
  void initBoard();
  

  //@function: Othello::putPiece()
  //@argument: [x] column id
  //           [y] row    id
  //           [color] BLACK or WHITE
  //@return  : true if the piece is put successfully.
  //           Otherwise,false
  //@cond    : x,y should be in [0 , b_size-1]
  bool putPiece(int x, int y, char color);




  //@function: Othello::canPutHere()
  //@descript: Judge that player can put a piece at (x,y)
  //@argument: [x] column id
  //           [y] row    id
  //           [color] BLACK or WHITE
  //@return  : if it is possible, return true.  Otherwise, false.
  //@cond    : x,y should be in [0 , b_size-1]
  bool canPutHere(int x, int y, char color);



  //@function: Othello::canReverseLine()
  //@argument: [x] column id
  //           [y] row    id
  //           [d] which direction to check
  //           [color] BLACK or WHITE
  //@return  : if it is possible, return true.  Otherwise, false.
  //@cond    : x,y should be in [0 , b_size-1]
  bool canReverseLine(int x, int y, Direction d, char color);



  //@function: Othello::isGameOver()
  //@return  : return true if all cells are filled.
  bool isGameOver(){ return (num_piece_black + num_piece_white ==
			     b_size*b_size); }


  //@function: Othello::getNumOfBlack()
  //@return  : Number of black pieces on the board
  int getNumOfBlack(){ return num_piece_black; }

  //@function: Othello::getNumOfWhite()
  //@return  : Number of white pieces on the board
  int getNumOfWhite(){ return num_piece_white; }



  //@function: Othello::printBoardCLI()
  //@descript: Output the board to command line
  //@argument: [assistFlag] if this is true, print '*' in the cells
  //                        where you can put a piece.
  void printBoardCLI(bool assistFlag);



  //@function: Othello::inputHandCLI()
  //@descript: Input interface for CLI (print message & read the inputs).
  //@argument: [&x][&y] record the input in this variable
  //@return  : return ture if it succeeded. Otherwise,
  //           e.g. format is incorrect, return false.
  //@cond    : The input value would be [1,b_size], but this function
  //            automatically adjust it into [0,b_size-1]
  bool inputHandCLI(int &x, int &y);
  


  //@function: Othello::playGame()
  //@descript: 
  void playGame();


  //@function: Destructor  ~Othello()
  //@descript: Free allocated memory
  ~Othello(){
    for(int i=0; i<b_size; i++){ free(board[i]); }
    free(board);
  }
  
};




#endif

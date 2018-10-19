/****************************************************
Othello.cpp
 ****************************************************/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "Othello.h"
using namespace std;

//@function: Constructor  Othello() 
//@descript: Allocate memory for board & initialize
//@argument: [s] size of the board (default: 8x8)
//@cond    : s should be even and >= 4
Othello::Othello(int s=8){

  b_size = s;
  if( b_size < 4 )b_size=4;
  if( b_size % 2 )b_size--;
  
  board = (char**)malloc( sizeof(char*) * b_size);
  if(board == NULL)exit(1);
  
  for(int i=0; i<b_size; i++){
    board[i] = (char*)malloc( sizeof(char) * b_size);
    if(board[i] == NULL)exit(1);
  }
  
  initBoard();
}
//@end: Othello()



//@function: Othello::initBoard()
//@descript: Reset the board and counters to the initial state.
void Othello::initBoard(){
  for(int i=0; i<b_size; i++){
    for(int j=0; j<b_size; j++){
      board[i][j] = EMPTY;
    }
  }
  board[(b_size/2)-1][(b_size/2)-1] =
    board[(b_size/2)][(b_size/2)]   = WHITE;

  board[(b_size/2)-1][b_size/2] =
    board[b_size/2][(b_size/2)-1] = BLACK;

  num_piece_black = num_piece_white = 2;
  turn = 1;
}
//@end: initBoard()




//@function: Othello::putPiece()
//@argument: [x] column id
//           [y] row    id
//           [color] BLACK or WHITE
//@return  : true if the piece is put successfully.
//           Otherwise,false
//@cond    : x,y should be in [0 , b_size-1]
bool Othello::putPiece(int x, int y, char color){
  if( x<0 || b_size<=x || y<0 || b_size<=y )return false;
  if( color != BLACK && color != WHITE )    return false;
  
  bool success = false;  //succeed to put a piece or not
  
  //1. Check board[y][x] is empty
  if( board[y][x] != EMPTY )return false;

  //2. Reverse pieces in a line of each direction if possible
  if( canReverseLine(x, y, N , color) ){
    for(int i=1; board[y-i][x]!=color; i++){
      board[y-i][x]=color;
      if(color==BLACK){ num_piece_black++; num_piece_white--; }
      else            { num_piece_black--; num_piece_white++; }
    }
    success = true;
  }
  if( canReverseLine(x, y, NE, color) ){
    for(int i=1; board[y-i][x+i]!=color; i++){
      board[y-i][x+i]=color;
      if(color==BLACK){ num_piece_black++; num_piece_white--; }
      else            { num_piece_black--; num_piece_white++; }
    }
    success = true;
  }
  if( canReverseLine(x, y, E , color) ){
    for(int i=1; board[y][x+i]!=color; i++){
      board[y][x+i]=color;
      if(color==BLACK){ num_piece_black++; num_piece_white--; }
      else            { num_piece_black--; num_piece_white++; }
    }
    success = true;
  }
  if( canReverseLine(x, y, SE, color) ){
    for(int i=1; board[y+i][x+i]!=color; i++){
      board[y+i][x+i]=color;
      if(color==BLACK){ num_piece_black++; num_piece_white--; }
      else            { num_piece_black--; num_piece_white++; }
    }
    success = true;
  }
  if( canReverseLine(x, y, S , color) ){
    for(int i=1; board[y+i][x]!=color; i++){
      board[y+i][x]=color;
      if(color==BLACK){ num_piece_black++; num_piece_white--; }
      else            { num_piece_black--; num_piece_white++; }	
    }
    success = true;
  }
  if( canReverseLine(x, y, SW, color) ){
    for(int i=1; board[y+i][x-i]!=color; i++){
      board[y+i][x-i]=color;
      if(color==BLACK){ num_piece_black++; num_piece_white--; }
      else            { num_piece_black--; num_piece_white++; }	
    }
    success = true;
  }
  if( canReverseLine(x, y, W , color) ){
    for(int i=1; board[y][x+i]!=color; i++){
      board[y][x+i]=color;
      if(color==BLACK){ num_piece_black++; num_piece_white--; }
      else            { num_piece_black--; num_piece_white++; }
    }
    success = true;
  }
  if( canReverseLine(x, y, NW , color) ){
    for(int i=1; board[y-i][x-i]!=color; i++){
      board[y-i][x-i]=color;
      if(color==BLACK){ num_piece_black++; num_piece_white--; }
      else            { num_piece_black--; num_piece_white++; }
    }
    success = true;
  }


  //3. Put a piece in (x,y)
  if(success){
    turn++;
    board[y][x] = color;
  }
  return success;
}
//@end: putPiece()





//@function: Othello::canPutHere()
//@descript: Judge that player can put a piece at (x,y)
//@argument: [x] column id
//           [y] row    id
//           [color] BLACK or WHITE
//@return  : if it is possible, return true.  Otherwise, false.
//@cond    : x,y should be in [0 , b_size-1]
bool Othello::canPutHere(int x, int y, char color){
  if( color != BLACK && color != WHITE )    return false;
  if( x<0 || b_size<=x || y<0 || b_size<=y )return false;
  if( board[y][x] != EMPTY )                return false;

  //look up all 8 directions
  return ( canReverseLine(x , y , N  , color) ||
	   canReverseLine(x , y , NE , color) ||
	   canReverseLine(x , y , E  , color) ||
	   canReverseLine(x , y , SE , color) ||
	   canReverseLine(x , y , S  , color) ||
	   canReverseLine(x , y , SW , color) ||
	   canReverseLine(x , y , W  , color) ||
	   canReverseLine(x , y , NW , color)
	   );
}
//@end: canPutHere()




//@function: Othello::canReverseLine()
//@argument: [x] column id
//           [y] row    id
//           [d] which direction to check
//           [color] BLACK or WHITE
//@return  : if it is possible, return true.  Otherwise, false.
//@cond    : x,y should be in [0 , b_size-1]
bool Othello::canReverseLine(int x, int y, Direction d, char color){
  if( color != BLACK && color != WHITE )    return false;
  if( x<0 || b_size<=x || y<0 || b_size<=y )return false;

  
  switch(d){
    /*****************************/
  case N:
    if( y > 0    &&
	board[y-1][x] != color  &&  board[y-1][x] != EMPTY    ) {
      for(int i=y-2 ; i>=0 ; i--){
	if     (board[i][x]==color) return true;
	else if(board[i][x]==EMPTY) return false;
      }
    }
    break;
    /*****************************/
  case S:
    if( y < b_size-1            &&
	board[y+1][x] != color  &&  board[y+1][x] != EMPTY    ) {
      for(int i=y+2 ; i<b_size ; i++){
	if     (board[i][x]==color) return true;
	else if(board[i][x]==EMPTY) return false;
      }
    }
    break;
    /*****************************/
  case E:
    if( x < b_size-1            &&
	board[y][x+1] != color  &&  board[y][x+1] != EMPTY    ){
      for(int i=x+2; i<b_size ; i++){
	if     (board[y][i]==color) return true;
	else if(board[i][x]==EMPTY) return false;
      }
    }
    break;
    /*****************************/
  case W:
    if( x > 0    &&
	board[y][x-1] != color  &&  board[y][x-1] != EMPTY    ){
      for(int i=x-2; i>=0 ; i--){
	if     (board[y][i]==color) return true;
	else if(board[i][x]==EMPTY) return false;
      }
    }
    break;
    /*****************************/
  case NE:
    if( x < b_size-1  &&  y > 0   &&
	board[y-1][x+1] != color  &&  board[y-1][x+1] != EMPTY ){
      for(int i=2; (y-i>=0 && x+i<b_size) ; i++){
	if     (board[y-i][x+i]==color) return true;
	else if(board[y-i][x+i]==EMPTY) return false;
      }
    }
    break;
    /*****************************/
  case SE:
    if( x < b_size-1  &&  y < b_size-1   &&
	board[y+1][x+1] != color  &&  board[y+1][x+1] != EMPTY ){
      for(int i=2; (y+i<b_size && x+i<b_size) ; i++){
	if     (board[y+i][x+i]==color) return true;
	else if(board[y+i][x+i]==EMPTY) return false;
      }
    }
    break;
    /*****************************/
  case NW:
    if( x > 0  &&  y > 0   &&
	board[y-1][x-1] != color  &&  board[y-1][x-1] != EMPTY ){
      for(int i=2; (y-i>=0 && x-i>=0) ; i++){
	if     (board[y-i][x-i]==color) return true;
	else if(board[y-i][x-i]==EMPTY) return false;
      }
    }
    break;
    /*****************************/
  case SW:
    if( x > 0  &&  y < b_size-1   &&
	board[y+1][x-1] != color  &&  board[y+1][x-1] != EMPTY ){
      for(int i=2; (y+i<b_size && x-i>=0) ; i++){
	if     (board[y+i][x-i]==color) return true;
	else if(board[y+i][x-i]==EMPTY) return false;
      }
    }
    break;
    /*****************************/
  default:
    return false;

  }
  //switch()

  return false;
}
//@end: canReverseLine()






//@function: Othello::printBoardCLI()
//@descript: Output the board to command line
//@argument: [assistFlag] if this is true, print '*' in the cells
//                        where you can put a piece.
void Othello::printBoardCLI(bool assistFlag){
  //if you want to change the design, please change these variables. 
  const char blackMarker='@';
  const char whiteMarker='O';
  const char emptyMarker=' ';
  const char assistMarker='*';


  //output
  cout << "==================================================" << endl;
  if(turn%2==1)
    cout<<"[Turn ] Black" << endl;
  else
    cout<<"[Turn ] White" << endl;

  cout << "[Number of Pieces]";
  cout << " Black("<<blackMarker<<"):"<<num_piece_black << "     ";
  cout << " White("<<whiteMarker<<"):"<<num_piece_white << endl;
  cout << "[Remain] "<<(b_size*b_size)-(num_piece_black+num_piece_white)<<endl;
  cout << "==================================================" << endl;
  cout << endl;

  //Column Number
  cout << "    ";
  for(int i=1; i<=b_size; i++){cout<<setw(2)<<i; cout;} cout << endl;
  //first glid
  cout << "    +";for(int i=0; i<b_size; i++)cout<<"-+";   cout << endl;
  //board
  for(int i=0; i<b_size; i++){
    cout<<" "<<setw(2)<<i+1; cout << " |";
    for(int j=0; j<b_size; j++){
      if(board[i][j] == BLACK)cout << blackMarker;
      else if(board[i][j] == WHITE) cout << whiteMarker;
      else if(assistFlag){
	if(turn%2 && canPutHere(j,i,BLACK))cout<<assistMarker;
	else if(!(turn%2) && canPutHere(j,i,WHITE))cout<<assistMarker;
	else cout << emptyMarker;
      }
      else cout << emptyMarker;

      cout << "|";
    }
    cout << endl;
    //separate line
    cout << "    +";for(int j=0; j<b_size; j++)cout<<"-+";   cout << endl;
  }
  
  cout << endl << endl;
}
//@end: printBoardCLI()









//@function: Othello::inputHandCLI()
//@descript: Input interface for CLI.
//@argument: [&x][&y] record the input in this variable
//@return  : return ture if it succeeded. Otherwise,
//           e.g. format is incorrect, return false.
//@cond    : The input value would be [1,b_size], but this function
//            automatically adjust it into [0,b_size-1]
bool Othello::inputHandCLI(int &x, int &y){
  cout << "Input space-separated [column ID] and [row ID]." << endl;
  cout << "Where would you put a piece? ===> ";
  cin  >> x >> y;
  x--; y--;
  if( 0<=x && x<b_size && 0<=y && y<b_size )return true;

  return false;
}
//@end: inputHandCLI()











//@function: Othello::playGame()
//@descript: 
void Othello::playGame(){

  char yesno;
  bool assistFlag_black, assistFlag_white;


  //Print the start menu & edit preferences
  cout << "==================================================" << endl;
  cout << " Start Othello Game! " <<endl;
  cout << endl;
  cout << "[Initial Setting]" << endl;
  cout << "Would you activate play assist? " <<
          "(Program indicates where you can put a piece)" << endl;
  cout << "Black(y/n) > ";  cin >> yesno;
  if(yesno == 'y')
    assistFlag_black = true;
  else
    assistFlag_black = false;
  
  cout << "White(y/n) > ";  cin >> yesno;
  if(yesno == 'y')
    assistFlag_white = true;
  else
    assistFlag_white = false;

  cout << "Play Assist ==> Black:";
  if(assistFlag_black)cout << "ON";
  else               cout << "OFF";
  cout << "   White:";
  if(assistFlag_white)cout << "ON";
  else               cout << "OFF";
  cout << endl;


  //Play 1 Game
  printBoardCLI(assistFlag_black);
  cout << endl << endl;
  while(isGameOver() == false){
    int x,y;

    //If input was successful, put a piece at (x,y)
    if( inputHandCLI(x,y) ){
      bool is_success;
      if(turn%2)is_success = putPiece(x,y,BLACK);
      else      is_success = putPiece(x,y,WHITE);

      if(turn%2)
	printBoardCLI(assistFlag_black);
      else
	printBoardCLI(assistFlag_white);

      if(is_success){
	cout << "Put a piece at ("<<x+1<<","<<y+1<<")." << endl;
      }
      else{
	cout << "### You cannot put piece at ("<<x+1<<","<<y+1<<"). ###"
	     << endl;
      }
    }
    //If input was invalid, print error message and try again
    else{
      if(turn%2)
	printBoardCLI(assistFlag_black);
      else
	printBoardCLI(assistFlag_white);

      cout << "### Input was invalid. (Example Input)===> 2 5 ###"
	   << endl;
    }
    
  }

}
//@end: playGame()




/*###########################################################*/

#ifdef CLI_OTHELLO
//play othello in CLI

int main(){

  Othello game;
  game.playGame();
  return 0;
}

#endif

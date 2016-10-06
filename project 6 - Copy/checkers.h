/*
 * David Sorrell
 * Game project
 */

#ifndef CHECKERS_H
#define CHECKERS_H
 
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <queue>
#include <iomanip>
#include "colors.h"   
#include <string> 
#include "game.h"
#include "game_object.h"
 
 using namespace std;

class Checkers:public main_savitch_14::game{
	public:
		Checkers();
		void restart();
		void display_status()const;
		bool is_legal(const string& move)const;
		void make_move(const string& move);
		bool is_game_over()const;
		who winning()const;
		game* clone()const;
		void compute_moves(queue<string>& moves)const;
		int evaluate( )const;
		
	private:
	Game_object board[7][7];
};

Checkers::Checkers(){
	restart();
}

void Checkers::restart(){
	// setting up the red squares on a board.
	// row 1
	board[1][0].set_red();
	board[1][2].set_red();
	board[1][4].set_red();
	board[1][6].set_red();
	// row 3
	board[3][0].set_red();
	board[3][2].set_red();
	board[3][4].set_red();
	board[3][6].set_red();
	//row 5
	board[5][0].set_red();
	board[5][2].set_red();
	board[5][4].set_red();
	board[5][6].set_red();
	//row 7
	board[7][0].set_red();
	board[7][2].set_red();
	board[7][4].set_red();
	board[7][6].set_red();
	
	//row 0
	board[0][1].set_red();
	board[0][3].set_red();
	board[0][5].set_red();
	board[0][7].set_red();
	//row 2
	board[2][1].set_red();
	board[2][3].set_red();
	board[2][5].set_red();
	board[2][7].set_red();
	//row 4
	board[4][1].set_red();
	board[4][3].set_red();
	board[4][5].set_red();
	board[4][7].set_red();
	//row 6
	board[6][1].set_red();
	board[6][3].set_red();
	board[6][5].set_red();
	board[6][7].set_red();
	
	// red starting
	board[0][0].set_piece("red");
	board[0][2].set_piece("red");
	board[0][4].set_piece("red");
	board[0][6].set_piece("red");
	
	board[1][1].set_piece("red");
	board[1][3].set_piece("red");
	board[1][5].set_piece("red");
	board[1][7].set_piece("red");
	
	board[2][0].set_piece("red");
	board[2][2].set_piece("red");
	board[2][4].set_piece("red");
	board[2][6].set_piece("red");
	
	//rows 3-4 empty
	board[3][1].set_empty();
	board[3][3].set_empty();
	board[3][5].set_empty();
	board[3][7].set_empty();
	
	board[4][0].set_empty();
	board[4][2].set_empty();
	board[4][4].set_empty();
	board[4][6].set_empty();
	
	// starters for black
	board[5][1].set_piece();
	board[5][3].set_piece();
	board[5][5].set_piece();
	board[5][7].set_piece();
	
	board[6][0].set_piece();
	board[6][2].set_piece();
	board[6][4].set_piece();
	board[6][6].set_piece();
	
	board[7][1].set_piece();
	board[7][3].set_piece();
	board[7][5].set_piece();
	board[7][7].set_piece();
	
	main_savitch_14::game::restart();
}
		
void Checkers::display_status()const{
	char ch = 'A';
	cout.fill(' ');
	cout << "current game status" << endl;
	cout << " .----------------------------------------."<< endl;
	for(int i =0; i <8; i++){
		if(board[i][0].is_red()){
			//first square red
			cout << " |" << B_WHITE << setw(9) << RESET << B_BLUE << setw(9) << RESET << B_WHITE << setw(9) << RESET << B_BLUE << setw(9) << RESET << B_WHITE << setw(9) << RESET << B_BLUE << setw(9) << RESET << B_WHITE << setw(9) << RESET << B_BLUE << setw(9) << RESET << "|" << endl;	
			cout << ch << "|" ;
			ch++;
			for(int j=0; j<8; j++){
				if(board[i][j].is_piece()){
					if(board[i][j].is_piece_red()){
						if(board[i][j].is_king()){
							cout << B_BLUE << RED << "  K  " << RESET; 
						}
						else{
							cout << B_BLUE  << RED << "  O  " << RESET; 
						}
					}
					else{
						if(board[i][j].is_king()){
							cout << B_BLUE << BLACK << "  K  " << RESET; 
						}
						else{
							cout << B_BLUE << BLACK << "  @  "  << RESET; 
						}
					}
				}
				else if(board[i][j].is_empty()){
					cout << B_BLUE << "     " << RESET;
				}
				else if(board[i][j].is_red()){
					cout << B_WHITE << "     " << RESET;
				}
			}
			cout << "|" << endl;
			cout << " |" << B_WHITE << setw(9) << RESET << B_BLUE << setw(9) << RESET << B_WHITE << setw(9) << RESET << B_BLUE << setw(9) << RESET << B_WHITE << setw(9) << RESET << B_BLUE << setw(9) << RESET << B_WHITE << setw(9) << RESET << B_BLUE << setw(9) << RESET << "|" << endl;	
		}
		else{
			//first square black
			cout << " |" <<  B_BLUE << setw(9) << RESET << B_WHITE << setw(9) << RESET <<  B_BLUE << setw(9) << RESET << B_WHITE << setw(9) << RESET <<  B_BLUE << setw(9) << RESET << B_WHITE << setw(9) << RESET <<  B_BLUE << setw(9) << RESET << B_WHITE << setw(9) << RESET << "|" << endl;
			cout << ch << "|" ;
			ch++;
			for(int j=0; j<8; j++){
				if(board[i][j].is_piece()){
					if(board[i][j].is_piece_red()){
						if(board[i][j].is_king()){
							cout << B_BLUE << RED << "  K  " << RESET;
						}
						else{
							cout << B_BLUE << RED << "  O  " << RESET;
						}
					}
					else{
						if(board[i][j].is_king()){
							cout << B_BLUE << BLACK << "  K  " << RESET;
						}
						else{
							cout << B_BLUE << BLACK << "  @  " << RESET;
						}
					}
				}
				else if(board[i][j].is_empty()){
					cout << B_BLUE << "     " << RESET;
				}
				else if(board[i][j].is_red()){
					cout << B_WHITE << "     " << RESET;
				}
			}
			
			cout << "|" << endl;
			cout << " |" <<  B_BLUE << setw(9) << RESET << B_WHITE << setw(9) << RESET <<  B_BLUE << setw(9) << RESET << B_WHITE << setw(9) << RESET <<  B_BLUE << setw(9) << RESET << B_WHITE << setw(9) << RESET <<  B_BLUE << setw(9) << RESET << B_WHITE << setw(9) << RESET << "|" << endl;
		}
	}

	cout << " .----------------------------------------. "<< endl;
	cout << "    0    1    2    3    4    5    6    7  " << endl;
	cout << endl;
}

bool Checkers::is_legal(const string& move)const{
	// row 1 moves
	//a0
	if((move == "a0b1")){
		if(board[0][0].is_piece_red()){
			return true;
		}
		
		else if(board[0][0].is_king()){
			return true;
		}	
	}
	
	//a2
	if((move == "a2b1")){
		if(board[0][2].is_piece_red()){
			return true;
		}
		
		else if(board[1][1].is_king()){
			return true;
		}	
	}
	if((move == "a2b3")){
		if(board[0][2].is_piece_red()){
			return true;
		}
		
		else if(board[1][1].is_king()){
			return true;
		}	
	}
	//a4
	if((move == "a4b3")){
		if(board[0][4].is_piece_red()){
			return true;
		}
		
		else if(board[1][1].is_king()){
			return true;
		}	
	}
	if((move == "a4b5")){
		if(board[0][4].is_piece_red()){
			return true;
		}
		
		else if(board[1][1].is_king()){
			return true;
		}	
	}
	//a6
	if((move == "a6b5")){
		if(board[0][6].is_piece_red()){
			return true;
		}
		
		else if(board[1][1].is_king()){
			return true;
		}	
	}
	if((move == "a6b7")){
		if(board[0][6].is_piece_red()){
			return true;
		}
		
		else if(board[1][1].is_king()){
			return true;
		}	
	}
	
	// row 2 moves
	//b1
	if((move == "b1a0")){
		if(board[1][1].is_piece()){
			return true;
		}
		
		else if(board[1][1].is_king()){
			return true;
		}	
	}
	if((move == "b1a2")){
		if(board[1][1].is_piece()){
			return true;
		}
		
		else if(board[1][1].is_king()){
			return true;
		}
	}
	if((move == "b1c0")){
		if(board[1][1].is_piece_red()){
			return true;
		}
		
		else if(board[1][1].is_king()){
			return true;
		}
	}
	if((move == "b1c2")){
		if(board[1][1].is_piece_red()){
			return true;
		}
		
		else if(board[1][1].is_king()){
			return true;
		}
	}
	//b3
	if((move == "b3a2")){
		if(board[1][3].is_piece()){
			return true;
		}
		
		else if(board[1][3].is_king()){
			return true;
		}
	}
	if((move == "b3a4")){
		if(board[1][3].is_piece()){
			return true;
		}
		
		else if(board[1][3].is_king()){
			return true;
		}
	}
	if((move == "b3c2")){
		if(board[1][3].is_piece_red()){
			return true;
		}
		
		else if(board[1][3].is_king()){
			return true;
		}
	}
	if((move == "b3c4")){
		if(board[1][3].is_piece_red()){
			return true;
		}
		
		else if(board[1][3].is_king()){
			return true;
		}
	}
	//b5
	
	if((move == "b5a4")){
		if(board[1][5].is_piece()){
			return true;
		}
		
		else if(board[1][5].is_king()){
			return true;
		}
	}
	if((move == "b5a6")){
		if(board[1][5].is_piece()){
			return true;
		}
		
		else if(board[1][5].is_king()){
			return true;
		}
	}
	if((move == "b5c4")){
		if(board[1][5].is_piece_red()){
			return true;
		}
		
		else if(board[1][5].is_king()){
			return true;
		}
	}
	if((move == "b5c6")){
		if(board[1][5].is_piece_red()){
			return true;
		}
		
		else if(board[1][5].is_king()){
			return true;
		}
	}
	
	// b7
	
	if((move == "b7a6")){
		if(board[1][7].is_piece()){
			return true;
		}
		
		else if(board[1][7].is_king()){
			return true;
		}
	}
	
	if((move == "b7c6")){
		if(board[1][7].is_piece_red()){
			return true;
		}
		
		else if(board[1][7].is_king()){
			return true;
		}
	}
	
	// 3rd row
	//c0
	if((move == "c0b1")){
		if(board[2][0].is_piece()){
			return true;
		}
		
		else if(board[2][0].is_king()){
			return true;
		}
	}
	
	if((move == "c0d1")){
		if(board[2][0].is_piece_red()){
			return true;
		}
		
		else if(board[2][0].is_king()){
			return true;
		}
	}
	
	// c2
	
	if((move == "c2b1")){
		if(board[2][2].is_piece()){
			return true;
		}
		
		else if(board[2][2].is_king()){
			return true;
		}
	}
	if((move == "c2b3")){
		if(board[2][2].is_piece()){
			return true;
		}
		
		else if(board[2][2].is_king()){
			return true;
		}
	}
	if((move == "c2d1")){
		if(board[2][2].is_piece_red()){
			return true;
		}
		
		else if(board[2][2].is_king()){
			return true;
		}
	}
	if((move == "c2d3")){
		if(board[2][2].is_piece_red()){
			return true;
		}
		
		else if(board[2][2].is_king()){
			return true;
		}
	}
	
	// c4
	if((move == "c4b3")){
		if(board[2][4].is_piece()){
			return true;
		}
		
		else if(board[2][4].is_king()){
			return true;
		}
	}
	if((move == "c4b5")){
		if(board[2][4].is_piece()){
			return true;
		}
		
		else if(board[2][4].is_king()){
			return true;
		}
	}
	if((move == "c4d3")){
		if(board[2][4].is_piece_red()){
			return true;
		}
		
		else if(board[2][4].is_king()){
			return true;
		}
	}
	if((move == "c4d5")){
		if(board[2][4].is_piece_red()){
			return true;
		}
		
		else if(board[2][4].is_king()){
			return true;
		}
	}
	
	// c6
	if((move == "c6b5")){
		if(board[2][6].is_piece()){
			return true;
		}
		
		else if(board[2][6].is_king()){
			return true;
		}
	}
	if((move == "c6b7")){
		if(board[2][6].is_piece()){
			return true;
		}
		
		else if(board[2][6].is_king()){
			return true;
		}
	}
	if((move == "c6d5")){
		if(board[2][6].is_piece_red()){
			return true;
		}
		
		else if(board[2][6].is_king()){
			return true;
		}
	}
	if((move == "c6d7")){
		if(board[2][6].is_piece_red()){
			return true;
		}
		
		else if(board[2][6].is_king()){
			return true;
		}
	}
	
	//4 row
	// d1
	
	if((move == "d1c0")){
		if(board[3][1].is_piece()){
			return true;
		}
		
		else if(board[3][1].is_king()){
			return true;
		}	
	}
	if((move == "d1c2")){
		if(board[3][1].is_piece()){
			return true;
		}
		
		else if(board[3][1].is_king()){
			return true;
		}
	}
	if((move == "d1e0")){
		if(board[3][1].is_piece_red()){
			return true;
		}

		else if(board[3][1].is_king()){
			return true;
		}
	}
	if((move == "d1e2")){
		if(board[3][1].is_piece_red()){
			return true;
		}
		
		else if(board[3][1].is_king()){
			return true;
		}
	}
	
	//d3
	if((move == "d3c2")){
		if(board[3][3].is_piece()){
			return true;
		}
		
		else if(board[3][3].is_king()){
			return true;
		}	
	}
	if((move == "d3c4")){
		if(board[3][3].is_piece()){
			return true;
		}
		
		else if(board[3][3].is_king()){
			return true;
		}
	}
	if((move == "d3e2")){
		if(board[3][3].is_piece_red()){
			return true;
		}
		
		else if(board[3][3].is_king()){
			return true;
		}
	}
	if((move == "d3e4")){
		if(board[3][3].is_piece_red()){
			return true;
		}
		
		else if(board[3][3].is_king()){
			return true;
		}
	}
	
	// d5
	if((move == "d5c4")){
		if(board[3][5].is_piece()){
			return true;
		}
		
		else if(board[3][5].is_king()){
			return true;
		}	
	}
	if((move == "d5c6")){
		if(board[3][5].is_piece()){
			return true;
		}

		else if(board[3][5].is_king()){
			return true;
		}
	}
	if((move == "d5e4")){
		if(board[3][5].is_piece_red()){
			return true;
		}
		
		else if(board[3][5].is_king()){
			return true;
		}
	}
	if((move == "d5e6")){
		if(board[3][5].is_piece_red()){
			return true;
		}
		
		else if(board[3][5].is_king()){
			return true;
		}
	}
	
	//d7
	if((move == "d7c6")){
		if(board[3][7].is_piece()){
			return true;
		}
		
		else if(board[3][7].is_king()){
			return true;
		}
	}
	
	if((move == "d7e6")){
		if(board[3][7].is_piece_red()){
			return true;
		}
		
		else if(board[3][7].is_king()){
			return true;
		}
	}
	
	// 5th row
	//e0
	if((move == "e0d1")){
		if(board[4][0].is_piece()){
			return true;
		}
		
		else if(board[4][0].is_king()){
			return true;
		}
	}
	
	if((move == "e0f1")){
		if(board[4][0].is_piece_red()){
			return true;
		}
		
		else if(board[4][0].is_king()){
			return true;
		}
	}
	
	// e2
	if((move == "e2d1")){
		if(board[4][2].is_piece()){
			return true;
		}
		
		else if(board[4][2].is_king()){
			return true;
		}
	}
	if((move == "e2d3")){
		if(board[4][2].is_piece()){
			return true;
		}
		
		else if(board[4][2].is_king()){
			return true;
		}
	}
	if((move == "e2f1")){
		if(board[4][2].is_piece_red()){
			return true;
		}
		
		else if(board[4][2].is_king()){
			return true;
		}
	}
	if((move == "e2f3")){
		if(board[4][2].is_piece_red()){
			return true;
		}
		
		else if(board[4][2].is_king()){
			return true;
		}
	}
	
	//e4
	if((move == "e4d3")){
		if(board[4][4].is_piece()){
			return true;
		}
		
		else if(board[4][4].is_king()){
			return true;
		}
	}
	if((move == "e4d5")){
		if(board[4][4].is_piece()){
			return true;
		}
		
		else if(board[4][4].is_king()){
			return true;
		}
	}
	if((move == "e4f3")){
		if(board[4][4].is_piece_red()){
			return true;
		}
		
		else if(board[4][4].is_king()){
			return true;
		}
	}
	if((move == "e4f5")){
		if(board[4][4].is_piece_red()){
			return true;
		}
		
		else if(board[4][4].is_king()){
			return true;
		}
	}
	
	//e6
	if((move == "e6d5")){
		if(board[4][6].is_piece()){
			return true;
		}
		
		else if(board[4][6].is_king()){
			return true;
		}
	}
	if((move == "e6d7")){
		if(board[4][6].is_piece()){
			return true;
		}
		
		else if(board[4][6].is_king()){
			return true;
		}
	}
	if((move == "e6f5")){
		if(board[4][6].is_piece_red()){
			return true;
		}
		
		else if(board[4][6].is_king()){
			return true;
		}
	}
	if((move == "e6f7")){
		if(board[4][6].is_piece_red()){
			return true;
		}
		
		else if(board[4][6].is_king()){
			return true;
		}
	}
	
	// 6th row
	// f1
	if((move == "f1e0")){
		if(board[5][1].is_piece()){
			return true;
		}
		
		else if(board[5][1].is_king()){
			return true;
		}
	}
	if((move == "f1e2")){
		if(board[5][1].is_piece()){
			return true;
		}
		
		else if(board[5][1].is_king()){
			return true;
		}
	}
	if((move == "f1g0")){
		if(board[5][1].is_piece_red()){
			return true;
		}
		
		else if(board[5][1].is_king()){
			return true;
		}
	}
	if((move == "f1g2")){
		if(board[5][1].is_piece_red()){
			return true;
		}
		
		else if(board[5][1].is_king()){
			return true;
		}
	}
	
	//f3
	if((move == "f3e2")){
		if(board[5][3].is_piece()){
			return true;
		}
		
		else if(board[5][3].is_king()){
			return true;
		}
	}
	if((move == "f3e4")){
		if(board[5][3].is_piece()){
			return true;
		}
		
		else if(board[5][3].is_king()){
			return true;
		}
	}
	if((move == "f3g2")){
		if(board[5][3].is_piece_red()){
			return true;
		}
		
		else if(board[5][3].is_king()){
			return true;
		}
	}
	if((move == "f3g4")){
		if(board[5][3].is_piece_red()){
			return true;
		}
		
		else if(board[5][3].is_king()){
			return true;
		}
	}
	
	//f5
	if((move == "f5e4")){
		if(board[5][5].is_piece()){
			return true;
		}
		
		else if(board[5][5].is_king()){
			return true;
		}
	}
	if((move == "f5e6")){
		if(board[5][5].is_piece()){
			return true;
		}
		
		else if(board[5][5].is_king()){
			return true;
		}
	}
	if((move == "f5g4")){
		if(board[5][1].is_piece_red()){
			return true;
		}
		
		else if(board[5][5].is_king()){
			return true;
		}
	}
	if((move == "f5g6")){
		if(board[5][5].is_piece_red()){
			return true;
		}
		
		else if(board[5][5].is_king()){
			return true;
		}
	}
	
	// f7
	if((move == "f7e6")){
		if(board[5][7].is_piece()){
			return true;
		}
		
		else if(board[5][7].is_king()){
			return true;
		}
	}
	
	if((move == "f7g6")){
		if(board[5][7].is_piece_red()){
			return true;
		}
		
		else if(board[5][7].is_king()){
			return true;
		}
	}
	
	//6th row
	//g0
	if((move == "g0f1")){
		if(board[6][0].is_piece()){
			return true;
		}
		
		else if(board[6][0].is_king()){
			return true;
		}
	}
	
	if((move == "g0h1")){
		if(board[6][0].is_piece_red()){
			return true;
		}
		
		else if(board[6][0].is_king()){
			return true;
		}
	}
	
	// g2
	if((move == "g2f1")){
		if(board[6][2].is_piece()){
			return true;
		}
		
		else if(board[6][2].is_king()){
			return true;
		}
	}
	if((move == "g2f3")){
		if(board[6][2].is_piece()){
			return true;
		}
		
		else if(board[6][2].is_king()){
			return true;
		}
	}
	if((move == "g2h1")){
		if(board[6][2].is_piece_red()){
			return true;
		}
		
		else if(board[6][2].is_king()){
			return true;
		}
	}
	if((move == "g2h3")){
		if(board[6][2].is_piece_red()){
			return true;
		}
		
		else if(board[6][2].is_king()){
			return true;
		}
	}
	
	//g4
	if((move == "g4f3")){
		if(board[6][4].is_piece()){
			return true;
		}
		
		else if(board[6][4].is_king()){
			return true;
		}
	}
	if((move == "g4f5")){
		if(board[6][4].is_piece()){
			return true;
		}
		
		else if(board[6][4].is_king()){
			return true;
		}
	}
	if((move == "g4h3")){
		if(board[6][4].is_piece_red()){
			return true;
		}
		
		else if(board[6][4].is_king()){
			return true;
		}
	}
	if((move == "g4h5")){
		if(board[6][4].is_piece_red()){
			return true;
		}
		
		else if(board[6][4].is_king()){
			return true;
		}
	}
	
	//g6
	if((move == "g6f5")){
		if(board[6][6].is_piece()){
			return true;
		}
		
		else if(board[6][6].is_king()){
			return true;
		}
	}
	if((move == "g6f7")){
		if(board[6][6].is_piece()){
			return true;
		}
		
		else if(board[6][2].is_king()){
			return true;
		}
	}
	if((move == "g6h5")){
		if(board[6][6].is_piece_red()){
			return true;
		}
		
		else if(board[6][6].is_king()){
			return true;
		}
	}
	if((move == "g6h7")){
		if(board[6][6].is_piece_red()){
			return true;
		}
		
		else if(board[6][6].is_king()){
			return true;
		}
	}
	
	// row 7
	// h1
	if((move == "h1g0")){
		if(board[7][1].is_piece()){
			return true;
		}
		
		else if(board[7][1].is_king()){
			return true;
		}
	}
	if((move == "h1g2")){
		if(board[7][1].is_piece()){
			return true;
		}
		
		else if(board[7][1].is_king()){
			return true;
		}
	}
	
	// h3
	if((move == "h3g2")){
		if(board[7][3].is_piece()){
			return true;
		}
		
		else if(board[7][3].is_king()){
			return true;
		}
	}
	if((move == "h3g4")){
		if(board[7][3].is_piece()){
			return true;
		}
		
		else if(board[7][3].is_king()){
			return true;
		}
	}
	
	// h5
	if((move == "h5g4")){
		if(board[7][5].is_piece()){
			return true;
		}
		
		else if(board[7][5].is_king()){
			return true;
		}
	}
	if((move == "h5g6")){
		if(board[7][5].is_piece()){
			return true;
		}
		
		else if(board[7][5].is_king()){
			return true;
		}
	}
	
	// h7
	if((move == "h7g5")){
		if(board[7][7].is_piece()){
			return true;
		}
		
		else if(board[7][7].is_king()){
			return true;
		}
	}	
}

void Checkers::make_move(const string& move){
	int value1, value2, num1, num2;
	char v1,v2;
	
	
	move.c_str();
	v1 = tolower(move[0]);
	value1 = atoi((move.substr(1,1)).c_str());
	v2 = tolower(move[3]);
	value2 = atoi((move.substr(4,4)).c_str());
	
	// changing the first letter to a number
	if(v1=='a'){
		num1 = 0;
	}
	else if(v1=='b'){
		num1 = 1;
	}
	else if(v1=='c'){
		num1 = 2;
	}
	else if(v1=='d'){
		num1 = 3;
	}
	else if(v1=='e'){
		num1 = 4;
	}
	else if(v1=='f'){
		num1 = 5;
	}
	else if(v1=='g'){
		num1 = 6;
	}
	else{
		num1 = 7;
	}
	
	
	// changing the second letter to a number
	if(v2=='a'){
		num2 = 0;
	}
	else if(v2=='b'){
		num2 = 1;
	}
	else if(v2=='c'){
		num2 = 2;
	}
	else if(v2=='d'){
		num2 = 3;
	}
	else if(v2=='e'){
		num2 = 4;
	}
	else if(v2=='f'){
		num2 = 5;
	}
	else if(v2=='g'){
		num2 = 6;
	}
	else{
		num2 = 7;
	}
	//jumping and moving
	if((board[num2][value2].is_piece()) || (board[num2][value2].is_piece_red())){
		board[num1][value1] = board[num2 + 1][value2 -1];
		board[num1][value1].set_empty();
	}
	else{
	board[num1][value1] = board[num2][value2];
	board[num1][value1].set_empty();
	}
	
	
	main_savitch_14::game::make_move(move);
}
	
bool Checkers::is_game_over()const{
	int count1 = 0;
	int count2 = 0;
	
	for(int i = 0; i<8; i++){
		for(int j = 0; j<8; j++){
			if(board[i][j].is_piece_red()){
				count1++;
			}
			else if(board[i][j].is_piece()){
				count2++;
			}
		}
	}
	
	if(count1 == 0 || count2 == 0){
		return true;
	}	
}

Checkers::who Checkers::winning( )const{
	int value = evaluate( ); 

	if (value > 0)
	    return last_mover( );
	else if (value < 0)
	    return next_mover( );
	else
	    return NEUTRAL;
}

int Checkers::evaluate( )const{
	int count1 = 0;
	int count2 = 0;
	int total = 0;
	
	for(int i = 0; i<8; i++){
		for(int j = 0; j<8; j++){
			if(board[i][j].is_piece_red()){
				count1++;
			}
			else if(board[i][j].is_piece()){
				count2++;
			}
		}
	}
	if(count1<count2){
		total = 1;
		return total;
	}
	else{
		total = -1;
		return total;
	}	
}

main_savitch_14::game* Checkers::clone()const{
	return new Checkers(*this);
}

void Checkers::compute_moves(queue<string>& moves)const{
	string move;
	move = "f1d0";
	if(is_legal(move)){
		moves.push(move);
	}
	move = "f1d2";
	if(is_legal(move)){
		moves.push(move);
	}
	move = "d0e1";
	if(is_legal(move)){
		moves.push(move);
	}
}
#endif
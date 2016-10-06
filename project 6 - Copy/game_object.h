/*
 * David Sorrell
 * Game project
 */

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
 
#include <iostream>
#include <cstdlib>   
#include <string> 


using namespace std;

class Game_object{
	public:
		Game_object();
		bool is_king()const;
		bool is_empty()const;
		bool is_red()const;
		bool is_piece()const;
		bool is_piece_red()const;
		void set_king(string color = "black");
		void set_piece(string color = "black");
		void set_red();
		void set_empty();
		void unset_king();
		void unset_piece();
		
	 
	private:
		bool empty;
		bool piece_red;
		bool king;
		bool piece;
		bool red;
		
};

Game_object::Game_object(){
	piece_red = false;
	piece = false;
	king = false;
	red = false;
}

bool Game_object::is_king()const{
	return king;
}

bool Game_object::is_red()const{
	return red;
}

bool Game_object::is_piece()const{
	return piece;
}

bool Game_object::is_piece_red()const{
	return piece_red;
}

bool Game_object::is_empty()const{
	return empty;
}

void Game_object::set_king(string color){
	king = piece = true;
	if(color == "red"){
		piece_red = true;
	}
}

void Game_object::set_piece(string color){
	piece = true;
	if(color == "red"){
		piece_red = true;
	}
}

void Game_object::set_red(){
	red = true;
}

void Game_object::set_empty(){
	empty = true;
}

void Game_object::unset_piece(){
	piece = piece_red = false;
}

void Game_object::unset_king(){
	king = piece = piece_red = false;
}

#endif
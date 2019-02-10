/*
Ethan Lennon 325000366
Alex Lade 425008185
Joseph Hernandez 825002632
Josiah Hamid-Khani 725003646
Samuel Huff 424009128
CSCE 315-505
November 19, 2018
GameStats.cpp

Original Code taken from Project 3 team 31
*/
#include "GameStats.h"
#include <iostream>
#include <fstream>
#include <utility>
using namespace std;

/*
Resets the game stats.
Parameters: none
Return value: void
*/
void GameStats::reset_game(){
  player_name = "";
  m_difficulty = -1;      //-1 to denote unset
  m_pancake_count = -1;   //-1 to denote unset
}

/*
Saves the high scores as pairs into the high_scores vector.
Parameters: none
Return value: void
*/
void GameStats::save_high_scores(){
  ofstream scorefile;
  scorefile.open("scores.txt");
  for(size_t i = 0; i < high_scores.size(); i++){
    scorefile << high_scores[i].first <<" "<< high_scores[i].second<< '\n';
  }
  scorefile.close();
}

/*
Reads in high scores from the score.txt file. 
File must be formatted as: "name score" with a space in between.
Parameters: none
Return value: none
*/
void GameStats::load_high_scores(){
  high_scores.clear();
  string line;
  int score;
  ifstream scorefile;
  scorefile.open("scores.txt");

  if(scorefile.is_open()){
    while(scorefile>>line>>score){
		pair<string, int> p (line, score);
      high_scores.push_back(p);
    }
    scorefile.close();
  }
  else{
    return; // If file is not read the game should still be playable
  }
}


/*
Sets the current user's name.
Parameters: a char pointer representing a string for the user name
Return value: void
*/
void GameStats::set_player_name(string name){
  if(name.size() == 0){
    this->player_name = "NUL";
  }
  else{
    for(long unsigned int i = 0; i < name.size(); ++i){
      this->player_name += name[i];
      if(i >= 2){
        break;
      }
    }
  }
}

//used to print out high scores at the beginning of the game
void GameStats::print_top_scores(){
    cout<<("_high scores_\n");
    for(size_t i = 0; i < high_scores.size(); i++){
        cout<<(high_scores[i].first.c_str());
        cout<<(" %d", high_scores[i].second);
        cout<<("\n");
    }
    cout<<(player_name.c_str());
    cout<<(" 0");
    cout<<("\n");

}


//this function does not print out the current user at the end. Used for repeated
//play or end of game
void GameStats::print_top_scores_repeat(){
    cout<<("_high scores_\n");
    for(size_t i = 0; i < high_scores.size(); i++){
        cout<<(high_scores[i].first.c_str());
        cout<<(" %d", high_scores[i].second);
        cout<<("\n");
    }
}


void GameStats::flip_pancakes(int flip_number){
	int flip_index;
	for(int i = 0; i < m_pancakes.size(); i++){
		if(m_pancakes[i] == flip_number)
			flip_index = i;
	}
    //flip_index = m_pancakes.size()-flip_index-1;
    vector<int> temp;
	
	for(int i = 0; i < flip_index; i++)
		temp.push_back(m_pancakes[i]);
    for (int i = m_pancakes.size()-1; i >=flip_index; i--) {     //5in total, 3, 0=3,1=2,2=1,3=0
        temp.push_back(m_pancakes[i]);
    }
    for (size_t i = 0; i < m_pancakes.size(); i++) {     //5in total, 3, 0=3,1=2,2=1,3=0
        set_pan_vec_i(i,temp[i]);
		
    }
	
    //refresh();
}
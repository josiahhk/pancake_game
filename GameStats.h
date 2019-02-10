/*
Ethan Lennon 325000366
Alex Lade 425008185
Joseph Hernandez 825002632
Josiah Hamid-Khani 725003646
Samuel Huff 424009128
CSCE 315-505
November 19, 2018
GameStats.h

Original Code taken from Project 3 team 31
*/

#ifndef GAMESTATS_H
#define GAMESTATS_H

#include <utility> 
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>


using namespace std;

class GameStats{
public:
  int get_pancake_count() { return this->m_pancake_count; }
  void set_pancake_count(int count) { this->m_pancake_count = count;}

  int get_difficulty() {return this->m_difficulty;}
  void set_difficulty(int difficulty) { this->m_difficulty = difficulty;}

  void load_high_scores();
  void save_high_scores();
  void set_player_name(string name);

   
  vector<int> get_pan_vec(){return this->m_pancakes;}
  void input_pan_vec(int i){m_pancakes.push_back(i);}
  void set_pan_vec_i(int i,int val){m_pancakes[i]=val;};

  
  void shuf_vec(){
	for(int i = 1; i < m_pancake_count+1; i++){
        m_pancakes.push_back(i);
    }
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(m_pancakes.begin(), m_pancakes.end(), default_random_engine(seed));
  }
  
  void clear_vecs(){m_pancakes.clear();}
  void reset_game();
 
  int check_go();
  void print_top_scores();
  void print_top_scores_repeat();
  void shuffle_function();
  void flip_pancakes(int flip_number);

 // CPU cpu;
private:
  int m_difficulty;
  int m_pancake_count;
  vector<int> m_pancakes;
  string player_name;
  vector<pair<string, int>> high_scores;
  
};

#endif /* GAMESTATS_H */

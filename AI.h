#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//Needed for the AI to play
struct Node{
    //Used as the state of the game for the computer and player.
    vector<int> stack;
    int depth;
    vector<int> rootMoves;

    Node(vector<int> s, int d, vector<int> m){
        //Constructor for the state of the computer stack
        stack = s;
        depth = d;
        rootMoves = m;
    }
};

class AI {
public:
    int _difficulty = 0;
    int _current_best_move = 0;
    int _lowest_utility = 0;
    
    int signsFlipped(vector<int> p);
    int sortednessJ(vector<int> v);
    int evaluateStack(Node* root);
    int makeMove(Node*& root);

    void play_game(vector<int> stackOrder, int difficulty);

    void rFlipStack(int pos, vector<int>& pancakes);
    vector<int> FlipStack(int pos, vector<int> pancakes);
    vector<int> getPossibleMoves(vector<int> p);
    void set_difficulty(int i) { _difficulty = i; }
    void set_current_best_move(int i) {_current_best_move = i; }
    void set_lowest_utility(int i) { _lowest_utility = i; }

    int get_current_best_move() { return _current_best_move; }
    int get_difficulty() { return _difficulty; }
    int get_lowest_utility() { return _lowest_utility; }
};

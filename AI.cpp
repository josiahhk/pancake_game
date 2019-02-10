#include "AI.h"

int AI::signsFlipped(vector<int> p){
    //This function iterates through the vector and counts the number of sign changes in the vector.
    //This is used to help calculate the 'sortedness' of the state of the game.
    //Declare variables for the first iteration.
    int count =0;
    vector<int> _p;
    int inc = 1;
    int a,b;
    a = p.at(0);
    int PSize = p.size();
    while(inc<PSize){
        b = p.at(inc);
        if(a<b)
            _p.push_back(1);
        else
            _p.push_back(0);
        a = b;
        inc++;
    }
    int i = 1;
    int x,y;
    x = _p.at(0);
    int _PSize = _p.size();
    while(i<_PSize){
        y=_p.at(i);
        if(x!=y)
            count++;
        x = y;
        i++;
    }
    return count;
}

int AI::sortednessJ(vector<int> v){
    //This is called at all steps in the minimax tree. This is the utility functin in the AI, which analyzes and quantifies the state of the game.
    int count;
    count = signsFlipped(v);
    int rightSpot = 0;
    int Vsize = v.size();
    for(int i = 0; i<Vsize; i++){
        int vsize1 = v.size();
        if(vsize1 - i == v.at(i)){
            rightSpot++;
        }else{
            break;
        }
    }
    return count-rightSpot;
}

void AI::rFlipStack(int pos, vector<int>& pancakes){
    //Flips the stack of pancakes by passing in the position and the reference of the stack of pancakes.
//Passed by reference so that we can concate the two vectors without worrying about copying the values again.
    //cout<<"move make: "<<pos<<endl;
    // _secondReverseMove = pos;
    // _reverseMove = pos;
    int pancakesSize = pancakes.size();
    if(pos < 0 || pos >= pancakesSize){
        //cout<<"invalid position: "<<pos<<endl;
        return;
    }
    vector<int> flippedPancakes;
    for(int i = pancakesSize-1; i>=pos; i--){
        flippedPancakes.push_back(pancakes.at(i));
        pancakes.pop_back();
    }
    //Concatenates the two vectors: pancakes and the dummy vector, flippedPancakes so that the order from position onward is flipped.
    pancakes.insert(pancakes.end(), flippedPancakes.begin(), flippedPancakes.end());
}

vector<int> AI::FlipStack(int pos, vector<int> pancakes){
    //Function that flips the stack of pancakes from a position onward. NOT pass by reference so that we can return a flipped copy without messing with the current state.
//Checks to make sure that the position entered is a valid move.
    int PanSize = pancakes.size();
    if(pos < 0 || pos >= PanSize){
        cout<<"regular flip: invalid position: "<<pos<<endl;
        return pancakes;
    }
     //Creates a dummy vector so that only one iteration is used to flip the pancakes.
    vector<int> flippedPancakes;
    int pancakesSize = pancakes.size();
    for(int i = pancakesSize-1; i>=pos; i--){
        flippedPancakes.push_back(pancakes.at(i));
        pancakes.pop_back();
    }
    pancakes.insert(pancakes.end(), flippedPancakes.begin(), flippedPancakes.end());
    return pancakes;
}

vector<int> AI::getPossibleMoves(vector<int> p){
    //Returns all the possible moves that the decesion tree can output.
    vector<int> moves;
    int PSize = p.size();
    for(int i = 0; i<PSize-1; i++){
            moves.push_back(i);
    }
    return moves;
}

int AI::evaluateStack(Node* root){
    //Returns the evaluation of the current state of the game. If the stack is sorted this will return the value -1.
    bool next = false;
    int p = 0;
    int RootStackSize = root->stack.size();
    for(int i = RootStackSize; i>0; i--){
        if(i != root->stack.at(p)){
            next = true;
        }
        p++;
    }
    if(next == false){
        return -1;
    }
    if(next){
        int RootStackSize = root->stack.size();
        for(int i = 0; i < RootStackSize; i++){
            //Iterates through the stack of pancakes to see if the stack is in reverse order.
            if(i+1 != root->stack.at(i)){
                return 0;
            }
        }
    }
    return -2;
}

int AI::makeMove(Node*& root){
    //This function gets passed the reference to the game state and then will make the next logical move in the game.
    vector<int> emptyV;
    root->rootMoves = emptyV;
    //Declares a queue to load the root value and then to push all branches of the minimax tree to implement a BFS.
    queue<Node*> q;
    q.push(root);
    int this_depth;
     //The lowest utility that the AI should play is same state as the current sortedness of the game.
     set_lowest_utility(sortednessJ(root->stack));

    while(!q.empty()){
        Node* s = q.front();
        this_depth = s->depth;
        q.pop();
         //updates the temporarySortedness of the current state of the game.
        int tempSortedness = sortednessJ(s->stack);


            if(tempSortedness <= get_lowest_utility()){

                set_lowest_utility(tempSortedness);

                int RootMovesSize = s->rootMoves.size();
                if(RootMovesSize > 0)
                    set_current_best_move(s->rootMoves.at(0));

                //Best move: it is sorted after this
                int stackSize = s->stack.size();
                if(tempSortedness == -1 * stackSize){
                    rFlipStack(get_current_best_move(), root->stack);
                    return -100;
                }
            }

        //Increments the depth to make sure we are only going so far into the minimax tree.
        this_depth++;
        if(this_depth < get_difficulty()){
            vector<int> moves = getPossibleMoves(s->stack);
            int MovesSize = moves.size();
            for(int i = 0; i<MovesSize; i++){
                std::vector<int> v = s->rootMoves;
                    v.push_back(moves.at(i));
                    q.push(new Node(FlipStack(moves.at(i), s->stack), this_depth, v));

            }
        }
    }


    rFlipStack(get_current_best_move(), root->stack);


    return 0;
}

void AI::play_game(vector<int> stackOrder, int difficulty) {
    _difficulty = difficulty;
    _lowest_utility = 100;
    vector<int> emptyVec;
    Node* root = new Node(stackOrder, 0, emptyVec);
    int eval = evaluateStack(root);
    while(eval != -1){
        makeMove(root); //Passed by reference
        eval = evaluateStack(root); //checks to see if AI has won the game.
        //NEED TO IMPLEMENT PRINT AI's stack: can be accessed: print(root->stack);
    }
}

/*
Ethan Lennon 325000366
Alex Lade 425008185
Joseph Hernandez 825002632
Josiah Hamid-Khani 725003646
Samuel Huff 424009128
CSCE 315-505
November 19, 2018
Game.cpp

Original Code taken from Project 3 team 31
*/


#include "std_lib_facilities_5.h"
#include "Point.h"
#include "Graph.h"
#include "Window.h"
#include "AI.h"
#include "Simple_window.h"
#include "GameStats.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Output.H>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <random>
#include <vector>
#include <chrono>
#include <thread>


using namespace Graph_lib;

struct Game : Graph_lib::Window 
{
	/*======Game constructor======*/
	Game(Point xy, int w, int h, const string& title);
	
	/*======Local 'game_stats' and 'cpu' object======*/
	GameStats game_stats;
	AI computer;
	vector<int> nullvctr;
	vector<int> AI_pancakes;
	Node *computerState = nullptr; 
	 //this and high_scores are necessary here because the linker sucks
	string player_name = "NUL";
	vector<pair<string, int>> high_scores_vec;
	
	/*======Splash screen elements======*/
	Text 	game_title;
	Text 	game_sub_title;
	Button 	start;
	Out_box team;
	
	/*======Instruction screen elements======*/
	Out_box instructions;
	Button 	lets_play;
	
	/*======"setup game" screen elements======*/
	In_box 	initials_box;
	Button 	initials_submit;
	Text 	welcome;
	Out_box high_scores;
	Text 	settings;
	In_box 	stack_size_box;
	Button 	stack_size_submit;
	Text 	stack_size_invalid;
	Text 	diff_text;
	In_box 	diff_box;
	Button 	diff_submit;
	Text 	diff_invalid;
	Text 	settings_results;
	In_box 	order_pref_box;
	Button 	order_pref_submit;
	Text 	order_pref_invalid;
	Text 	initial_order;
	Button start_game;
	
	/*======Custom stack screen elements======*/
	Text 	cust_sel_text;
	In_box 	cust_sel_box;
	Button 	cust_sel_submit;
	int 	index=0;
	Text 	out_range_text;
	Text 	in_stack_text;
	Text 	selected;
	
	
	/*======End screen elements===============*/
	Text result;
	Text score;
	Button replay;
	Button quit;
	Text user_title;
	Text ai_title;
	Text gameplay_instructions;
	
	/*======Different buttons for flipping======*/
	Button one, two, three, four, five, six, seven, eight, nine;
	Rectangle aone, atwo, athree, afour, afive, asix, aseven, aeight, anine;
	
	
	/*======Functions======*/
	void show_instructions(); 	// Callback for "start" button
	void get_initials(); 		// Callback for "let's play" button
	void show_scores();  		// Callback for "submit initials" button
	void get_stack_size();
	void check_stack_size();	// Callback for "submit size" button
	void get_diff(); 	 		
	void check_diff();			// Callback for "submit diff" button
	void show_results(); 	 	
	void get_order_choice();
	void check_order_choice(); 	// Callback for "submit order pref" button
	void create_vec();
	void get_cust_input();
	void check_cust_input(); 	// Callback for "submit cust" button
	void random_stack();
	void show_initial_order();
	void game_start();			// Callback for "start game" button
	void display_buttons(); 
	void display_user_rect(bool from_buttons);
	void clear_buttons();
	void clear_rects();
	void all_display(int i);
	int check_go();
	void end_screen(int end_state);
	void insert_player_score(int score);
	void load_high_scores();
	void final_scores_display();
	void retry();
	void display_ai();
	void save_high_scores();
	
	//Functionality for callback functions
	void one_pressed(){all_display(1);}
	void two_pressed(){all_display(2);}
	void three_pressed(){all_display(3);}
	void four_pressed(){all_display(4);}
	void five_pressed(){all_display(5);}
	void six_pressed(){all_display(6);}
	void seven_pressed(){all_display(7);}
	void eight_pressed(){all_display(8);}
	void nine_pressed(){all_display(9);}
	
	void quit_pressed(){hide();}
	void replay_pressed(){retry();}
	
	// Not sure why these are necessary for each callback but they are...
	static void cb_show_instructions(Address, Address pw) { reference_to<Game>(pw).show_instructions(); }
	static void cb_get_initials(Address, Address pw) { reference_to<Game>(pw).get_initials(); }
	static void cb_show_scores(Address, Address pw) { reference_to<Game>(pw).show_scores(); }
	static void cb_check_stack_size(Address, Address pw) { reference_to<Game>(pw).check_stack_size(); }
	static void cb_check_diff(Address, Address pw) { reference_to<Game>(pw).check_diff(); }
	static void cb_check_order_choice(Address, Address pw) { reference_to<Game>(pw).check_order_choice(); }
	static void cb_check_cust_input(Address, Address pw) { reference_to<Game>(pw).check_cust_input(); }
	static void cb_game_start(Address, Address pw) { reference_to<Game>(pw).game_start(); }
	
	static void cb_one_pressed(Address, Address pw) { reference_to<Game>(pw).one_pressed(); }
	static void cb_two_pressed(Address, Address pw) { reference_to<Game>(pw).two_pressed(); }
	static void cb_three_pressed(Address, Address pw) { reference_to<Game>(pw).three_pressed(); }
	static void cb_four_pressed(Address, Address pw) { reference_to<Game>(pw).four_pressed(); }
	static void cb_five_pressed(Address, Address pw) { reference_to<Game>(pw).five_pressed(); }
	static void cb_six_pressed(Address, Address pw) { reference_to<Game>(pw).six_pressed(); }
	static void cb_seven_pressed(Address, Address pw) { reference_to<Game>(pw).seven_pressed(); }
	static void cb_eight_pressed(Address, Address pw) { reference_to<Game>(pw).eight_pressed(); }
	static void cb_nine_pressed(Address, Address pw) { reference_to<Game>(pw).nine_pressed(); }
	
	
	static void cb_replay_pressed(Address, Address pw) { reference_to<Game>(pw).replay_pressed(); }
	static void cb_quit_pressed(Address, Address pw) { reference_to<Game>(pw).quit_pressed(); }
	
};

/*======Game constructor======*/
Game::Game(Point xy, int w, int h, const string& title) : Window(xy, w, h, title),

	// Initialize splash screen elements:
	game_title(Point(200,80), "pancakes"),
	game_sub_title(Point(230,105), "the game"),
	start(Point(305,240), 175, 30, "Click to start game:", cb_show_instructions), 
	team(Point(300,400), 200, 150, ""),
	
	// Initialize instruction screen elements:
	instructions(Point(100,80), 600, 200, ""),
	lets_play(Point(300,420), 175, 30, "Let's Play!", cb_get_initials),
	
	// Initialize "setup game" screen elements:
	initials_box(Point(165,50), 50, 20, "Please enter initials: "),
	initials_submit(Point(230, 48), 65, 25, "Submit", cb_show_scores),
	welcome(Point(65,100), ""),
	high_scores(Point(25,110), 200, 150, ""),
	settings(Point(15,300), "Game Settings:"),
	stack_size_box(Point(410, 320), 40, 20, "Choose the number of pancakes in the game (2-9): "),
	stack_size_submit(Point(465,318), 65, 25, "Submit", cb_check_stack_size),
	stack_size_invalid(Point(50, 350), "Please enter a number between 2 and 9:"),
	diff_text(Point(42,375), ""),
	diff_box(Point(415,362), 40, 20, ""),
	diff_submit(Point(470,360), 65, 25, "Submit", cb_check_diff),
	diff_invalid(Point(50, 400), ""),
	settings_results(Point(70,437), ""),
	order_pref_box(Point(600,487), 40, 20, "Input 0 to choose the order of the pancakes manually or 1 for a random order:"),
	order_pref_submit(Point(655,485), 65, 25, "Submit", cb_check_order_choice),
	order_pref_invalid(Point(550, 530), "Please enter either 0 or 1"),
	initial_order(Point(200,300), ""),
	start_game(Point(325,400), 110, 25, "Begin Game:", cb_game_start),
	
	// Initialize "custom stack" screen elements:
	cust_sel_text(Point(140,50), ""),
	cust_sel_box(Point(140,75), 40, 20, ""),
	cust_sel_submit(Point(200, 75), 65, 25, "Submit", cb_check_cust_input),
	out_range_text(Point(165,150), "Error: Input is out of range"),
	in_stack_text(Point(165,150), "Error: The number you input is already in the list"),
	selected(Point(300, 100), ""),
	
	
	// Initialize pancake stack buttons, user, and AI rectangles:
    one(Point(176.66, 150), 80, 30, "1", cb_one_pressed),
	aone(Point(506.66, 150), 80, 30),
	two(Point(163.33, 180), 110, 30, "2", cb_two_pressed),
	atwo(Point(493.33, 180), 110, 30),
	three(Point(150, 210), 140, 30, "3", cb_three_pressed),
	athree(Point(480, 210), 140, 30),
	four(Point(136.66, 240), 170, 30, "4", cb_four_pressed),
	afour(Point(466.66, 240), 170, 30),
	five(Point(123.33, 270), 200, 30, "5", cb_five_pressed),
	afive(Point(453.33, 270), 200, 30),
	six(Point(110,     300), 230, 30, "6", cb_six_pressed),
	asix(Point(440,     300), 230, 30),
	seven(Point(96.666, 330), 260, 30, "7", cb_seven_pressed),
	aseven(Point(426.666, 330), 260, 30),
	eight(Point(83.33, 360), 290, 30, "8", cb_eight_pressed),
	aeight(Point(413.33, 360), 290, 30),
	nine(Point(70, 390), 320, 30, "9", cb_nine_pressed),
	anine(Point(400, 390), 320, 30),
	user_title(Point(190, 100), ""),
	ai_title(Point(506.666, 100), "AI Stack"),
	gameplay_instructions(Point(150, 500), "Click the pancake you want to flip along with everything above it"),
	
	
	//Initialize end screen stuff
	result(Point(25,90), ""),
	score(Point(190, 90), ""),
	replay(Point(300, 300), 100, 30, "Replay", cb_replay_pressed),
	quit(Point(450, 300), 100, 30, "Quit", cb_quit_pressed)
	
{
	// Customize splash screen Title
	game_title.set_font(Graph_lib::Font::helvetica_bold_italic);
	game_title.set_font_size(80);
	game_title.set_color(Color::blue);
	
	game_sub_title.set_font(Graph_lib::Font::helvetica_bold_italic);
	game_sub_title.set_font_size(20);
	game_sub_title.set_color(Color::black);
	
	// Attach splash screen
	attach(game_title);
	attach(game_sub_title);
	attach(start);
	attach(team);
	
	// Initialize 'team' output
	stringstream members;
	members << "\t     [ Team 24 ]\n";
	members << "Team \"Clever Team Name\"\n";
	members << "      Josiah Hamid-Khani\n";
	members << "       Joseph Hernandez\n";
	members << "\t    Samuel Huff\n";
	members << "\t     Alexei Lade\n";
	members	<< "\t   Ethan Lennon";
	team.put(members.str());	
}

void Game::show_instructions()
{
	// Erase splash screen
	detach(game_title);
	detach(game_sub_title);
	detach(start);
	detach(team);
	
	// Attach instruction screen
	attach(instructions);
	attach(lets_play);
	
	// Initialize 'instructions' output
	stringstream instr;
	instr << "\t\t\t\t\t\t    How to play pancakes:\n\n";
	instr << "\t\t\t  The goal of the game is to organize your stack first.\n";
	instr << "\t        During each turn, select one pancake to flip everything above it.\n";
	instr << "     An organized stack means that each pancake only has smaller ones above it.\n";
	instr << "\t\t\t\t Beat the CPU player to get a huge bonus score.\n";
	instr << "\t\t\t\t    Controls will be explained on the game screen";
	instructions.put(instr.str());
	
	redraw();
}

//loads the high scores into a vector for sorting future display
void Game::load_high_scores(){
	high_scores_vec.clear();
	string line;
	int score;
	ifstream scorefile;
	scorefile.open("scores.txt");

	if(scorefile.is_open()){
	  while(scorefile>>line>>score){
		pair<string, int> p (line, score);
		high_scores_vec.push_back(p);
		}
		scorefile.close();
	}
	else{
		return; // If file is not read the game should still be playable
	}
}

void Game::get_initials()
{
	// Erase instruction screen
	detach(instructions);
	detach(lets_play);
	
	// Show initials box and submit button
	attach(initials_box);
	attach(initials_submit);
}

void Game::show_scores()
{	
	player_name = initials_box.get_string();
	attach(welcome);
	attach(high_scores);
	attach(settings);
	settings.set_font(Graph_lib::Font::helvetica_bold);
	
	//Actually load the high scores into the vector for later
	load_high_scores();
	
	// Initialize welcome message
	stringstream welc;
	welc << "Welcome: " << player_name;
	welcome.set_label(welc.str());
	
	// Initialize the high scores display
	stringstream ss;
	ss << "High Scores:\n";
	string line;
	ifstream scorefile;
	scorefile.open("scores.txt");
	while(!scorefile.eof())
	{
		getline(scorefile, line);
		line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
		ss<<line<<endl;
	}
	scorefile.close();
	ss<< player_name <<": 0";
	high_scores.put(ss.str());
	
	redraw();
	get_stack_size();
}

void Game::get_stack_size()
{	
	this->attach(stack_size_box);
	this->attach(stack_size_submit);
}

//error checks the input size of pancakes
void Game::check_stack_size()
{
	int input = stack_size_box.get_int();
	
	// Reset screen
	detach(stack_size_box);
	detach(stack_size_submit);
	detach(stack_size_invalid);
	
	// If stack size selection is out of range, show error message and get new input
	if(input < 2 || input > 9)
	{
		attach(stack_size_invalid);
		stack_size_invalid.set_color(Color::red);
		get_stack_size();
	}
	// Else, store stack size in game_stats 'm_pancake_count' variable and call get_diff():
	else
	{
		attach(stack_size_box);
		attach(stack_size_submit);
		game_stats.set_pancake_count(input);
		get_diff();
	}
}	

//gets the difficulty from the user
void Game::get_diff(){
	this->attach(diff_text);
	this->attach(diff_box);
	this->attach(diff_submit);
	
	// Initialize "get difficulty" message
	stringstream ss;
	ss << "Choose the competition level of the opponent (1-" << game_stats.get_pancake_count() << "):";
	diff_text.set_label(ss.str());
}

//checks the difficulty the user input
void Game::check_diff(){
	int input = diff_box.get_int();
	
	// Reset screen
	detach(diff_text);
	detach(diff_box);
	detach(diff_submit);
	detach(diff_invalid);
	
	// If AI difficulty selection is out of range, show error message and get new input
	if(input < 1 || input > game_stats.get_pancake_count())
	{
		attach(diff_invalid);
		diff_invalid.set_color(Color::red);
		stringstream ss;
		ss << "Please select a number between 1 and " << game_stats.get_pancake_count() << ":";
		diff_invalid.set_label(ss.str());
		get_diff();
	}
	
	// Else, store AI difficulty in game_stats 'm_difficulty' variable and show setting results
	else
	{
		game_stats.set_difficulty(input);
		attach(diff_text);
		attach(diff_box);
		attach(diff_submit);
		show_results();
	}
}

void Game::show_results()
{
	this->attach(settings_results);
	
	// Initialize "setting results" message
	stringstream ss;
	ss << "There are " << game_stats.get_pancake_count() << " pancakes in the game ";
	ss << "and the difficulty is set to " << game_stats.get_difficulty();
	settings_results.set_label(ss.str());
	settings_results.set_font(Graph_lib::Font::helvetica_italic);
	settings_results.set_color(Color::blue);

	get_order_choice();
}

void Game::get_order_choice()
{
	this->attach(order_pref_box);
	this->attach(order_pref_submit);
}

void Game::check_order_choice()
{
	int pref = order_pref_box.get_int();
	
	// Reset screen
	detach(order_pref_box);
	detach(order_pref_submit);
	detach(order_pref_invalid);
	
	// If input is not 0 or 1, display error message and get new input
	if(pref != 1 && pref != 0)
	{
		attach(order_pref_invalid);
		order_pref_invalid.set_color(Color::red);
		get_order_choice();
	}
	
	// Otherwise, create the initial vector
	else
		create_vec();
}
	
void Game::create_vec()
{
	int order_pref = order_pref_box.get_int();
	
	this->detach(initials_box);
	this->detach(initials_submit);
	this->detach(welcome);
	this->detach(high_scores);
	this->detach(settings);
	this->detach(stack_size_box);
	this->detach(stack_size_submit);
	this->detach(diff_text);
	this->detach(diff_box);
	this->detach(diff_submit);
	this->detach(settings_results);
	this->detach(order_pref_box);
	this->detach(order_pref_submit);
	
	// Create either a custom or random initial stack order
	if(order_pref == 0)
	{
		index = game_stats.get_pancake_count();
		get_cust_input();
	}
	else
		random_stack();
}

/*======Displays custom stack creation screen======*/
void Game::get_cust_input()
{
	this->attach(cust_sel_text);
	this->attach(cust_sel_box);
	this->attach(cust_sel_submit);
	this->attach(selected);
	
	// Set the "choose pancake" message
	stringstream ss;
	if(index == game_stats.get_pancake_count())
	{
		ss << "Choose pancake size for bottom of stack:";
		cust_sel_text.set_label(ss.str());
	}
	else if(index == 1)
	{
		ss << "Choose pancake size for top of stack:";
		cust_sel_text.set_label(ss.str());
	}
	else if(index > 1 && index < game_stats.get_pancake_count())
	{
		ss << "Choose next pancake size:";
		cust_sel_text.set_label(ss.str());
	}
	
	// If user has input all necessary values, display initial order
	else
	{
		this->detach(cust_sel_text);
		this->detach(cust_sel_box);
		this->detach(cust_sel_submit);
		this->detach(selected);
		
		show_initial_order();
	}
}


void Game::check_cust_input()
{
	vector<int> v = this->game_stats.get_pan_vec();
	int input = cust_sel_box.get_int();
	
	// Reset the screen
	detach(cust_sel_text);
	detach(cust_sel_submit);
	detach(cust_sel_box);
	detach(out_range_text);
	detach(in_stack_text);
	
	// Check to see if input is out of range
	if(input < 1 || input > game_stats.get_pancake_count())
	{ 
		attach(out_range_text);
		out_range_text.set_color(Color::red);
	}
	
	// Check to see if input is already in stack
	else if(std::find(v.begin(), v.end(), input) != v.end())
	{
		attach(in_stack_text);
		in_stack_text.set_color(Color::red);
	}
	
	// Add input to m_pancakes
	else
	{
		game_stats.input_pan_vec(input);
		AI_pancakes.push_back(input);
		index--;
		
		// Display already selected pancakes
		stringstream ss;
		for(int i=0; i<game_stats.get_pan_vec().size(); i++)
		{
			ss << game_stats.get_pan_vec()[i] << " ";
		}
		selected.set_label(ss.str());
		selected.set_color(Color::blue);
	}
	
	// Get next input
	get_cust_input();
}

/*======Creates random initial stack order======*/
void Game::random_stack()
{
	game_stats.shuf_vec();
	for(int i = 0; i < game_stats.get_pan_vec().size(); i++)
		AI_pancakes.push_back(game_stats.get_pan_vec()[i]);
	show_initial_order();
}

/*======Display initial stack order======*/
void Game::show_initial_order()
{
	this->attach(initial_order);
	this->attach(start_game);
	
	stringstream ss;
	ss << "The initial order of the pancakes is:  ";
	for(int i=0; i < game_stats.get_pan_vec().size(); i++)
		ss << game_stats.get_pan_vec()[i] << " ";
	
	initial_order.set_label(ss.str());;
	
}

//Clears the user buttons off the screen
void Game:: clear_buttons(){
	if(game_stats.get_pan_vec().size() >= 2){
		detach(one);
		detach(two);
	}	
	if(game_stats.get_pan_vec().size() >= 3)	
		detach(three);	
	if(game_stats.get_pan_vec().size() >= 4)
		detach(four);
	if(game_stats.get_pan_vec().size() >= 5)
		detach(five);
	if(game_stats.get_pan_vec().size() >= 6)
		detach(six);
	if(game_stats.get_pan_vec().size() >= 7)
		detach(seven);
	if(game_stats.get_pan_vec().size() >= 8)
		detach(eight);
	if(game_stats.get_pan_vec().size() == 9)
		detach(nine);
	
}

//Clears the AI rectanges off the screen
void Game:: clear_rects(){
	if(AI_pancakes.size() >= 2){
		detach(aone);
		detach(atwo);
	}	
	if(AI_pancakes.size() >= 3)	
		detach(athree);	
	if(AI_pancakes.size() >= 4)
		detach(afour);
	if(AI_pancakes.size() >= 5)
		detach(afive);
	if(AI_pancakes.size() >= 6)
		detach(asix);
	if(AI_pancakes.size() >= 7)
		detach(aseven);
	if(AI_pancakes.size() >= 8)
		detach(aeight);
	if(AI_pancakes.size() == 9)
		detach(anine);
	
}


//Displays the AI rectangles
void Game:: display_ai(){
	vector<int> y_points;
	y_points = {390, 360, 330, 300, 270, 240, 210, 180, 150};
	int size = AI_pancakes.size();

	if(AI_pancakes.size() >= 2){
		attach(aone);
		attach(atwo);
	}
	if(AI_pancakes.size() >= 3)	
		attach(athree);
	if(AI_pancakes.size() >= 4)
		attach(afour);
	if(AI_pancakes.size() >= 5)
		attach(afive);
	if(AI_pancakes.size() >= 6)
		attach(asix);
	if(AI_pancakes.size() >= 7)
		attach(aseven);
	if(AI_pancakes.size() >= 8)
		attach(aeight);
	if(AI_pancakes.size() == 9)
		attach(anine);
	
	
	for(int i = 0; i < size; i++){
		if(AI_pancakes[i] == 1)
			aone.move(aone.get_x(), y_points[i]);
		else if(AI_pancakes[i] == 2)
			atwo.move(atwo.get_x(), y_points[i]);
		else if(AI_pancakes[i] == 3)
			athree.move(athree.get_x(), y_points[i]);
		else if(AI_pancakes[i] == 4)
			afour.move(afour.get_x(), y_points[i]);
		else if(AI_pancakes[i] == 5)
			afive.move(afive.get_x(), y_points[i]);
		else if(AI_pancakes[i] == 6)
			asix.move(asix.get_x(), y_points[i]);
		else if(AI_pancakes[i] == 7)
			aseven.move(aseven.get_x(), y_points[i]);
		else if(AI_pancakes[i] == 8)
			aeight.move(aeight.get_x(), y_points[i]);
		else if(AI_pancakes[i] == 9)
			anine.move(anine.get_x(), y_points[i]);
	
	}
}




void Game:: display_buttons(){
	vector<int> y_points;
	y_points = {390, 360, 330, 300, 270, 240, 210, 180, 150};

	for(int i = 0; i < game_stats.get_pan_vec().size(); i++){
		if(game_stats.get_pan_vec()[i] == 1)
			one.move(one.get_x(), y_points[i]);
		else if(game_stats.get_pan_vec()[i] == 2)
			two.move(two.get_x(), y_points[i]);
		else if(game_stats.get_pan_vec()[i] == 3)
			three.move(three.get_x(), y_points[i]);
		else if(game_stats.get_pan_vec()[i] == 4)
			four.move(four.get_x(), y_points[i]);
		else if(game_stats.get_pan_vec()[i] == 5)
			five.move(five.get_x(), y_points[i]);
		else if(game_stats.get_pan_vec()[i] == 6)
			six.move(six.get_x(), y_points[i]);
		else if(game_stats.get_pan_vec()[i] == 7)
			seven.move(seven.get_x(), y_points[i]);
		else if(game_stats.get_pan_vec()[i] == 8)
			eight.move(eight.get_x(), y_points[i]);
		else if(game_stats.get_pan_vec()[i] == 9)
			nine.move(nine.get_x(), y_points[i]);
	}
	
}


void Game::game_start(){
	vector<int> y_points;
	y_points = {390, 360, 330, 300, 270, 240, 210, 180, 150};
	user_title.set_label(player_name);
	attach(user_title);
	attach(ai_title);
	attach(gameplay_instructions);
	detach(initial_order);
	detach(start_game);
	


	if(game_stats.get_pan_vec().size() >= 2){
		attach(one);
		attach(two);
		attach(aone);
		attach(atwo);
	}
	if(game_stats.get_pan_vec().size() >= 3){	
		attach(three);	
		attach(athree);
	}
	if(game_stats.get_pan_vec().size() >= 4){
		attach(four);
		attach(afour);
	}
	if(game_stats.get_pan_vec().size() >= 5){	
		attach(five);
		attach(afive);
	}
	if(game_stats.get_pan_vec().size() >= 6){
		attach(six);
		attach(asix);
	}
	if(game_stats.get_pan_vec().size() >= 7){
		attach(seven);
		attach(aseven);
	}
	if(game_stats.get_pan_vec().size() >= 8){
		attach(eight);
		attach(aeight);
	}
	if(game_stats.get_pan_vec().size() == 9){
		attach(nine);
		attach(anine);
	}

	for(int i = 0; i < AI_pancakes.size(); i++){
		if(AI_pancakes[i] == 1)
			aone.move(aone.get_x(), y_points[i]);
		else if(AI_pancakes[i] == 2)
			atwo.move(atwo.get_x(), y_points[i]);
		else if(AI_pancakes[i] == 3)
			athree.move(athree.get_x(), y_points[i]);
		else if(AI_pancakes[i] == 4)
			afour.move(afour.get_x(), y_points[i]);
		else if(AI_pancakes[i] == 5)
			afive.move(afive.get_x(), y_points[i]);
		else if(AI_pancakes[i] == 6)
			asix.move(asix.get_x(), y_points[i]);
		else if(AI_pancakes[i] == 7)
			aseven.move(aseven.get_x(), y_points[i]);
		else if(AI_pancakes[i] == 8)
			aeight.move(aeight.get_x(), y_points[i]);
		else if(AI_pancakes[i] == 9)
			anine.move(anine.get_x(), y_points[i]);
	
	}
	
	display_buttons();
	computer.set_difficulty(game_stats.get_difficulty());
	computerState = new Node(AI_pancakes, 0, nullvctr);
	
}


/*
Inserts a score into the high_score vector. Adds the score in order and removes a score if there
are more than 5.
Parameters: an integer representing the score of the current user
Return value: void
*/
void Game::insert_player_score(int score){
	pair<string, int> player(player_name, score);
	int i = 0;
	while(score < high_scores_vec[i].second){
		i++;
		if(i == high_scores_vec.size()) break;
	}
	high_scores_vec.insert(high_scores_vec.begin()+i, player);
	if(high_scores_vec.size() == 6)
		high_scores_vec.erase(high_scores_vec.end()-1);

}


/*
Saves the high scores as pairs into the high_scores vector.
Parameters: none
Return value: void
*/
void Game::save_high_scores(){
  ofstream scorefile;
  scorefile.open("scores.txt");
  for(size_t i = 0; i < high_scores_vec.size(); i++){
    scorefile << high_scores_vec[i].first <<" "<< high_scores_vec[i].second<< '\n';
  }
  scorefile.close();
}


//checks whether or not the game is over depending on the order of the vectors
int Game::check_go(){
	int size = game_stats.get_pan_vec().size();
	int difficulty = game_stats.get_difficulty();
	bool ai_sorted = true;
	bool m_sorted = true;
	for(int i = 0; i < size; i++){
		if(size - (game_stats.get_pan_vec()[i]) != i)
			m_sorted = false;
	}
	if (computer.evaluateStack(computerState) != -1)
		ai_sorted = false;

	if(ai_sorted==false && m_sorted==false) //FF game not over
		return -1;	
	else if(ai_sorted== true && m_sorted == false){	//TF ai wins
		insert_player_score(difficulty);
		return 1;
	}
	else if(m_sorted==true && ai_sorted == false){		//TF user wins
		insert_player_score(2*size*(difficulty+1));
		return 2;
	}
	else{
		insert_player_score(size*(difficulty+1));
		return 3;
	}

}

//sets up the screen for the retry
void Game::retry(){
	detach(high_scores);
	detach(score);
	detach(replay);
	detach(quit);
	detach(result);
	
	game_stats.clear_vecs();
	AI_pancakes.clear();
	
	show_instructions();
}

//sets up the end screen
void Game::end_screen(int end_state){
	int size = game_stats.get_pan_vec().size();
	int difficulty = game_stats.get_difficulty();
	clear_buttons();
	clear_rects();
	detach(user_title);
	detach(ai_title);
	detach(gameplay_instructions);
	
	if(end_state == 1){
		result.set_label("AI WINS! Your score: ");
		string score_string = to_string(difficulty);
		score.set_label(score_string);
		attach(result); attach(score);
	}
	else if(end_state == 2){
		result.set_label("YOU WIN! Your score: ");
		string score_string = to_string(2*size*(difficulty+1));
		score.set_label(score_string);
		attach(result); attach(score);
	}
	else if(end_state == 3){
		result.set_label("A TIE! Your score: ");
		string score_string = to_string(size*(difficulty+1));
		score.set_label(score_string);
		attach(result); attach(score);
	}	
	final_scores_display();
	save_high_scores();
	attach(quit);
	attach(replay);
	
}

//sets up the final scores box
void Game::final_scores_display(){
	attach(high_scores);
	ostringstream oss;
	oss<<"High scores: \n\n";
	for(int i = 0; i < high_scores_vec.size(); i++)
		oss<<high_scores_vec[i].first<<" :"<<high_scores_vec[i].second<<"\n";
	
	high_scores.put(oss.str());
}

//displays the screen for the game part of the game and checks for the game over
//Called by every button press
void Game:: all_display(int i){
	int n;
	game_stats.flip_pancakes(i);
	computer.makeMove(computerState);
	AI_pancakes = computerState->stack;
	five.show();
	display_ai();
	display_buttons();
	if(check_go()>0){
		end_screen(check_go());
	}
}

int main (void)
{
    Game win(Point(150,20), 800, 600, "Pancakes Game");
	return gui_main();
}
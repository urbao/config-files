// minesweeper game
// table counted from 0
// different levels(simple --> hard)
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <ctime>
#include <cstdlib>

#define EASY_MAX 9
#define MEDIUM_MAX 16
#define TOUGH_MAX 24

#define EASY_BOMB 10
#define MEDIUM_BOMB 40
#define TOUGH_BOMB 99

using namespace std;

class grid{
public:
	bool is_opened=false;
	char data='-';
};

// FOREGROUND_RED|BACKGROUND_BLUE| ......
void change_font_color(WORD c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    return;
}

// show table
void color_grid(string stats, char c){
	if(stats=="bomb"){
		change_font_color(FOREGROUND_RED);
        cout<<c;
        change_font_color(7);
	}else if(stats=="safe"){
		if(c=='0')change_font_color(FOREGROUND_BLUE|FOREGROUND_RED);
		else if(c=='1')change_font_color(FOREGROUND_RED|FOREGROUND_INTENSITY);
		else change_font_color(FOREGROUND_GREEN|FOREGROUND_RED);
        cout<<c;
        change_font_color(7);
	}
	else if(stats=="notopen"){
		change_font_color(7);
        cout<<c;
	}
    else{                     
        change_font_color(FOREGROUND_RED);
        cout<<"No matched stats instruction"<<endl;
        change_font_color(7);
    }
    return;
}

// show message
void show_message(string stats, string line, bool new_line){
    if(stats=="input"||stats=="info"){  // yellow output
        change_font_color(FOREGROUND_RED|FOREGROUND_GREEN);
        cout<<line;
        change_font_color(7);
    }    
	else if(stats=="number"){  // green output
        change_font_color(FOREGROUND_GREEN);
        cout<<line;
        change_font_color(7);
    }
    else if(stats=="normal"){// normal white color
		cout<<line;
	}
    else{                     
        change_font_color(FOREGROUND_RED);
        cout<<"No matched stats instruction";
        change_font_color(7);
    }
	if(new_line)cout<<endl;
	return;
}

// game info 
void game_info(){
	show_message("info", "================MineSweeper================",true);
	show_message("normal", "> Easy mode to Tough mode", true);
	show_message("normal", "> Use bomb counts to analyze grid", true);
	show_message("normal", "> Sometimes, luck is important !!", true);
	show_message("info", "\n> creator: zardforever", true);
    show_message("info", "===========================================", true);
	system("pause");
	system("cls");
	show_message("info", "\n========Choose Mode========", true);
	show_message("normal", "> 1.Easy   (9*9)   10 bombs", true);
	show_message("normal", "> 2.Medium (16*16) 40 bombs", true);
	show_message("normal", "> 3.Tough  (24*24) 99 bombs", true);
	show_message("info", "===========================", true);
	return;
}

// yes or not
bool yes_or_not(const string ques){
    string input;
    while(true){
        show_message("info", ques, false);
        getline(cin, input);
        if(input=="Y"||input=="y")return true;
        else if(input=="n"||input=="N")return false;
        else show_message("normal", "failed: Only 'y' or 'n'", true);
    }
}

// get user input
string get_user_input(const string line, bool int_only, int min, int max){
	string input;
	bool okay=false;
	while(!okay){
		ENTER:
		show_message("input", line, false);
		getline(cin, input);
		if(input.size()==0){ //empty input
			show_message("normal", "failed: empty input", true);
			goto ENTER;
		}
		if(input=="zard")return "-1";
		if(input=="forever")return "-2";
		if(int_only){
			for(int i=0;i<input.size();i++){
				if(!isdigit(input[i])){
					show_message("normal", "failed: integer only", true);
					goto ENTER;
				}
				else if(i==input.size()-1)okay=true;
			}
			if(stoi(input)>max||stoi(input)<min){
				show_message("normal", "failed: invalid input", true);
				okay=false;
			}
		}
		else okay=true;
	}
	return input;
}

//generate bomb with given table
void generate_bomb(string game_mode, int max_size, vector<vector<grid>>& table){
	srand(time(NULL));
	int bomb_count=0, current=0;
	if(game_mode=="1")bomb_count=EASY_BOMB;
	else if(game_mode=="2")bomb_count=MEDIUM_BOMB;
	else bomb_count=TOUGH_BOMB;
	while(current!=bomb_count){
		int row=rand()%max_size;
		int col=rand()%max_size;
		if(table[row][col].data=='-'){
			table[row][col].data='X';
			current++;
		}
		else;
	}
	// update all data
	for(int i=0;i<table.size();i++){
		for(int j=0;j<table.size();j++){
			if(table[i][j].data!='X'){
				int count=0;
				if(i-1>=0&&j-1>=0){
					if(table[i-1][j-1].data=='X')count++;
				}
				if(i-1>=0&&j>=0){
					if(table[i-1][j].data=='X')count++;
				}
				if(i-1>=0&&j+1<table.size()){
					if(table[i-1][j+1].data=='X')count++;
				}
				if(i>=0&&j-1>=0){
					if(table[i][j-1].data=='X')count++;
				}
				if(i>=0&&j+1<table.size()){
					if(table[i][j+1].data=='X')count++;
				}
				if(i+1<table.size()&&j-1>=0){
					if(table[i+1][j-1].data=='X')count++;
				}
				if(i+1<table.size()&&j>=0){
					if(table[i+1][j].data=='X')count++;
				}
				if(i+1<table.size()&&j+1<table.size()){
					if(table[i+1][j+1].data=='X')count++;
				}
				table[i][j].data=char(count+'0');
			}
			else;
		}
	}
	return;
}

// build game & initialize table
vector<vector<grid>> build_game(string game_mode){	
	if(game_mode=="1"){
		vector<vector<grid>> table(EASY_MAX, (vector<grid>(EASY_MAX)));
		generate_bomb(game_mode, EASY_MAX, table);
		return table;
	}
	else if(game_mode=="2"){
		vector<vector<grid>> table(MEDIUM_MAX, (vector<grid>(MEDIUM_MAX)));
		generate_bomb(game_mode, MEDIUM_MAX, table);
		return table;
	}
	else if(game_mode=="3"){
		vector<vector<grid>> table(TOUGH_MAX, (vector<grid>(TOUGH_MAX)));
		generate_bomb(game_mode, TOUGH_MAX,table);
		return table;
	}
	else{
		vector<vector<grid>> table;
		show_message("info", "failed: build_game error",true);
		return table;
	}
}

// check already win or not
bool is_win(vector<vector<grid>> table, int row, int col){
	table[row][col].is_opened=true; // update already open
	for(int i=0;i<table.size();i++){
		for(int j=0;j<table.size();j++){
			if(table[i][j].data!='X'&&table[i][j].is_opened==false)return false;
		}
	}
	return true;
}

// print out table
void print_table(vector<vector<grid>> table, string current_status, bool no_hide){
	if(!no_hide){
		show_message("info", "> Current Status: "+current_status, true);
		// print col number
		cout<<"   ";
		for(int i=1;i<=table.size();i++){		
			if(i<10)show_message("number", "0"+to_string(i), false);
			else show_message("number", to_string(i), false);
			cout<<" ";
		}
		cout<<endl;
		show_message("number", "====", false);
		for(int i=1;i<=table.size();i++){		
			show_message("number", "===", false);
		}
		cout<<endl;
		for(int i=0;i<table.size();i++){
			if(i<9)show_message("number", "0"+to_string(i+1)+"|", false);
			else show_message("number", to_string(i+1)+"|", false);
			cout<<" ";
			for(int j=0;j<table.size();j++){
				if(!table[i][j].is_opened)color_grid("notopen", '-');
				else if(table[i][j].data=='X')color_grid("bomb", table[i][j].data);
			    else color_grid("safe", table[i][j].data);
				cout<<"  ";
			}
			show_message("number", "\b|", true);
		}
		show_message("number", "====", false);
		for(int i=0;i<table.size();i++){
			show_message("number", "===", false);
		}
		cout<<endl;
		return;
	}
	else{
		show_message("info", "> Current Status: "+current_status, true);
		// print col number
		cout<<"   ";
		for(int i=1;i<=table.size();i++){		
			if(i<10)show_message("number", "0"+to_string(i), false);
			else show_message("number", to_string(i), false);
			cout<<" ";
		}
		cout<<endl;
		show_message("number", "====", false);
		for(int i=1;i<=table.size();i++){		
			show_message("number", "===", false);
		}
		cout<<endl;
		for(int i=0;i<table.size();i++){
			if(i<9)show_message("number", "0"+to_string(i+1)+"|", false);
			else show_message("number", to_string(i+1)+"|", false);
			cout<<" ";
			for(int j=0;j<table.size();j++){
				if(table[i][j].data=='X')color_grid("bomb", table[i][j].data);
			    else color_grid("safe", table[i][j].data);
				cout<<"  ";
			}
			show_message("number", "\b|", true);
		}
		show_message("number", "====", false);
		for(int i=0;i<table.size();i++){
			show_message("number", "===", false);
		}
		cout<<endl;
		return;
	}
}

// show all non-bomb grids
void non_bomb_grid(vector<vector<grid>>& table, int row, int col){
	if(row<0||row>=table.size()||col<0||col>=table.size())return;
	else if(table[row][col].data=='X')return;
	else if(table[row][col].data=='0'&&!table[row][col].is_opened){
		table[row][col].is_opened=true;
		non_bomb_grid(table, row-1, col);
		non_bomb_grid(table, row, col+1);
		non_bomb_grid(table, row+1, col);
		non_bomb_grid(table, row, col-1);
		return;
	}
	else{
		table[row][col].is_opened=true;
		return;
	}
}

void minesweeper(){
	game_info(); 
	string game_mode=get_user_input("\nChoose mode[1/2/3]: ", true, 1, 3);
	int max_size=0;
	if(game_mode=="1")max_size=EASY_MAX;
	else if(game_mode=="2")max_size=MEDIUM_MAX;
	else max_size=TOUGH_MAX;
	system("cls");
	vector<vector<grid>> table=build_game(game_mode);
	string current_status="keep going\n";
	bool not_end=true;
	// game start
	while(not_end){
		system("cls");
		print_table(table, current_status, false);
		bool valid_input=false;
		int row=0, col=0;
		while(!valid_input){
			row=stoi(get_user_input("Row number: ", true, 1, max_size))-1;
			col=stoi(get_user_input("Col number: ", true, 1, max_size))-1;
			if(row==-2&&col==-3)print_table(table, "Little Hack\n", true);
			else if(table[row][col].is_opened)show_message("normal", "failed: Already opened this grid", true);
			else{				
				valid_input=true;
			}
		}
		// all possible condition
		if(table[row][col].data=='X'){ // boom 
			current_status="Boom! You lose !!\n";
			for(int i=0;i<table.size();i++){ // detonate all bombs
				for(int j=0;j<table.size();j++){
					if(table[i][j].data=='X')table[i][j].is_opened=true;
				}
			}
			system("cls");
			print_table(table, current_status, false);
			not_end=false;
		}
		else if(is_win(table, row, col)){   // win the game
			system("cls");
			current_status="Congrats! You win !!\n";
			print_table(table, current_status, false);
			not_end=false;
		}
		else{
			non_bomb_grid(table, row, col); 	// show all nearby non-bomb grids
			not_end=true;
		} 
	}
	return;
}


int main(){
	bool again=true;
	while(again){
		minesweeper();
		again=yes_or_not("> Do you want to continue?? [y/n] ");
		system("cls");
	}
	return 0;
}

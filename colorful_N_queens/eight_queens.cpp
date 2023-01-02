// N Queens problem solver
// 1: Queen / 0: Nothing
// User choose the place of queens in first column
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <windows.h>

using namespace std;

static int ans_count=0;

// change color
void change_color(WORD c){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return;
}

// change output char color
void color_char(string stats, char c, bool new_line){
	if(stats=="user_queen")change_color(FOREGROUND_RED|FOREGROUND_GREEN);
	else if(stats=="queen")change_color(FOREGROUND_RED|FOREGROUND_INTENSITY);
	else if(stats=="normal")change_color(FOREGROUND_BLUE|FOREGROUND_GREEN);
	else{
		change_color(FOREGROUND_RED);
		cout<<"No matched stats instruction";
	}
	cout<<c;
	change_color(7);
	if(new_line)cout<<endl;
	return;
}


// change output string color
void color_str(string stats, string line, bool new_line){
	if(stats=="info"||stats=="input")change_color(FOREGROUND_RED|FOREGROUND_GREEN);
	else if(stats=="number")change_color(FOREGROUND_GREEN);
	else if(stats=="result")change_color(FOREGROUND_BLUE|FOREGROUND_GREEN);
	else if(stats=="ans_count")change_color(FOREGROUND_RED|FOREGROUND_INTENSITY);
	else if(stats=="normal")change_color(7);
    else{                     
        change_color(FOREGROUND_RED);
        cout<<"No matched stats instruction";
    }
	cout<<line;
	change_color(7);
	if(new_line)cout<<endl;
	return;
} 

// yes or not
bool yes_or_not(const string ques){
	bool okay=false;
	string ans;
	while(!okay){
		color_str("input", ques, false);
		getline(cin, ans);
		if(ans=="y"||ans=="Y")return true;
		else if(ans=="n"||ans=="N")return false;
		else color_str("normal", "failed: Only 'y' or 'n'", true);
	}
}

// get user input
string get_input(const string line, bool int_only, int min, int max){
	string input;
	bool okay=false;
	while(!okay){
		ENTER:
		color_str("input", line, false);
		getline(cin, input);
		if(input.size()==0){ //empty input
			color_str("normal", "failed: empty input\n", true);
			goto ENTER;
		}
		if(input=="zardforever")return "0"; //little trick
		if(int_only){
			for(int i=0;i<input.size();i++){
				if(!isdigit(input[i])){
					color_str("normal", "failed: integer only\n", true);
					goto ENTER;
				}
				else if(i==input.size()-1)okay=true;
			}
			if(stoi(input)>max||stoi(input)<min){
				color_str("normal", "failed: invalid input\n", true);
				okay=false;
			}
		}
		else okay=true;
	}
	return input;
}

// program info
void program_info(){
	color_str("info", "====================Eight Queens=====================",true);
	color_str("normal", "> No two queens share the same row/column/diagonal", true);
	color_str("normal", "> User choose the column of 1st row to place queen", true);
	color_str("normal", "> Queen is denoted by 'Q'", true);
	color_str("normal", "> Civilian is denoted by '-'", true);
	color_str("info", "\n> creator: zardforever", true);
    color_str("info", "=====================================================", true);
	color_str("info", "\n========Choose Queen's Column Position========", true);
	return;
}

// print list func
void print_result(vector<vector<int>> q_vec){
	color_str("result", "soluiton ", false);
	color_str("ans_count", to_string(ans_count), false);
	cout<<":"<<endl;
	cout<<"   ";
	for(int i=0;i<q_vec.size();i++){
		color_str("number", to_string(i+1)+" ", false);
	}
	color_str("number", "\n====", false);
	for(int i=0;i<q_vec.size();i++){
		color_str("number", "==", false);
	}
	cout<<endl;
	for(int i=0;i<q_vec.size();i++){
		color_str("number", to_string(i+1)+"| ", false);
		for(int j=0;j<q_vec.size();j++){
			if(q_vec[i][j]==1&&i==0)color_char("user_queen", 'Q', false);
			else if(q_vec[i][j]==1)color_char("queen", 'Q',false);
			else color_char("normal", '-', false);
			cout<<" ";
		}
		color_str("number", "|\n", false);
	}
	color_str("number", "====", false);
	for(int i=0;i<q_vec.size();i++){
		color_str("number", "==", false);
	}
	color_str("info", "\n----------------------------------", true);
}

// queen okay or not to place specific row & color
bool q_safe(vector<vector<int>> q_vec, int q_row, int q_col){
	// horizontal
	for(int col=0;col<q_vec.size();col++){
		if(q_vec[q_row][col]==1)return false;
	}
	// vertical
	for(int row=0;row<q_vec.size();row++){
		if(q_vec[row][q_col]==1)return false;
	}
	// diagonal
	for(int row=0;row<q_vec.size();row++){
		for(int col=0;col<q_vec.size();col++){
			if(q_vec[row][col]==1){ // exist a queen
				if(abs(q_row-row)==abs(q_col-col))return false; // check if existed queen is at diagonal direction
			}
		}
	}
	return true;
}

// queen solver
void q_solve(vector<vector<int>>& q_vec, int row){
	if(row==q_vec.size()){  // reach the terminated condition
		ans_count++;
		print_result(q_vec);
		return;
	}
	for(int col=0;col<q_vec.size();col++){ // check every column
		if(q_safe(q_vec, row, col)){
			q_vec[row][col]=1; // update value to 1 
			q_solve(q_vec, row+1); // move to next row see if any possiblity of Queen
		}
		q_vec[row][col]=0; // set back to 0 for next column chk (OR the next chk will NOT pass)
	}
	return;
}

int main(){
	bool again=true;
	while(again){
		program_info();
		int q_vec_size=stoi(get_input("Queen Counts[1~9] ", true, 1, 9)); // setup how the N-queen's N is
		vector<vector<int>> q_vec(q_vec_size, vector<int>(q_vec_size, 0)); // queen place check
	int q_col=stoi(get_input("Queen Column[1~"+to_string(q_vec_size)+"] ", true, 1, q_vec_size))-1; // user place first queen column
		ans_count=0; // reinitialize answer counter value
		system("cls");
		color_str("info", "=======Eight Queens Result========",true);
		if(q_col==-1)q_solve(q_vec, 0); // sovle all solution
		else{
			q_vec[0][q_col]=1;
			q_solve(q_vec, 1);
		}
		color_str("info", "==================================",true);
		color_str("result", "> Total soultion counts: ", false);
		color_str("ans_count", to_string(ans_count), true);
		again=yes_or_not("Do you want to play again?? [y/n] ");
		system("cls");
	}
	
	return 0;
}

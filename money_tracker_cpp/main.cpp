#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>

using namespace std;

/*-----------------FUNCTIONALITY----------------------*/
// help function (show all functionality)
void help(){
	fstream file;
	file.open("help.txt", ios::in);
	if(!file)cerr<<"\033[1;31mfailed to open help file\033[0m\n";
	string line="";
	while(file){
		getline(file, line);
		cout<<line<<endl;
	}
	file.close();
}

int income_type(string str){
	if(str.find("income")!=std::string::npos)return 1;
	else if(str.find("expense")!=std::string::npos)return 0;
	else return 2;
}

// show funciton (show all file's data)
void show(){
	fstream file;
	file.open("log.txt", ios::in);
	if(!file)cerr<<"\033[1;31mfailed to open log file\033[0m\n";
	string line="";
	int counter=0;
	while(file){
		getline(file, line);
		if(counter==0||counter==1)cout<<"\033[1;33m"<<line<<"\033[0m\n";
		else {
			if(income_type(line)==1)cout<<"\033[1;32m"<<line<<"\033[0m\n";
			else if(income_type(line)==0)cout<<"\033[1;31m"<<line<<"\033[0m\n";
			else cout<<"\033[1;33m"<<line<<"\033[0m\n";
		}
		counter++;
	}
	file.close();
	return;
}

// find function (for log data searching)
void find(string data){
	ifstream file;
	// check if data exist
    file.open("log.txt", ios::in);
    string line;
    bool matched=false;
    while(file>>line){
        if(line.find(data) != string::npos){
            matched=true;
            break;
        }
    }
    file.close();
    // print out with highlight
    file.open("log.txt", ios::in);
    if(matched){
    	string replace_str="\033[1;33m"+data+"\033[0m";
        while(getline(file, line)){
        	if(line.find(data) == string::npos)continue; // nothing will be replaced in this line
        	boost::replace_all(line, data, replace_str);
        	cout<<line<<endl;
        }
    }
    else cout<<"\033[1;31mfailed: No matched case\033[0m\n";
    file.close();
    cout<<endl;
    return;
}

stringstream format_string(string date, string type, string amount, string detail){
	stringstream result;
	result<<date;
	if(type=="income")result<<"    income";
	else result<<"   expense";
	for(int i=0;i<7-amount.length();i++)result<<" ";
	result<<amount<<"  "<<detail;
	for(int i=0;i<50-detail.length();i++)result<<" ";
    auto start = chrono::system_clock::now();
    auto end = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(end);
 	result<<ctime(&end_time);
	return result;
}

bool confirm_append(){
	string ans;
	while(true){
		cout<<"\033[1;31mDo you want to append? (Y/n)\033[0m";
		getline(cin, ans);
		if(ans=="Y"||ans=="y")return true;
		else if(ans=="N"||ans=="n")return false;
		else cout<<"Only `Y' and `n' acceptable"<<endl; 
	}
}

// append function (appending log data)
void append(){
	string date, type, amount, detail;
	cin.ignore(); // for \n character ignore
	cout<<"\033[1;33m-----Basic Info-----\033[0m\n";
	cout<<"\033[1;35mDate: \033[0m";
	getline(cin, date);
	cout<<"\033[1;35mType: \033[0m";
	getline(cin, type);
	cout<<"\033[1;35mAmount: \033[0m";
	getline(cin, amount);
	cout<<"\033[1;35mDetail: \033[0m";
	getline(cin, detail);
	bool confirm=confirm_append();
	if(!confirm){
		cout<<"\033[1;33m----Cancel Update----\033[0m\n\n";
		return;
	}
	// writing file
	ofstream file;
	file.open("log.txt", ios_base::app);
	stringstream ss=format_string(date, type, amount, detail);
	file<<ss.str();
	file.close();
	cout<<"\033[1;33m--Successful Update--\033[0m\n";
	// use git push to backup log file
	cout<<"\033[1;36m-----Backup-----\033[0m\n";
	cout<<"\033[1;36m----git add----\033[0m\n";
	system("git add log.txt");
	cout<<"\033[1;36m----git commit----\033[0m\n";
	system("git commit -m \"update log.txt\"");
	cout<<"\033[1;36m----git push----\033[0m\n";
	system("git push");
	cout<<"\033[1;36m----finished----\033[0m\n\n";
	return;
}

// total function (calc. total income && expense)
void total(){
	ifstream file;
	file.open("log.txt", ios::in);
	string str;
	int income=0, expense=0;
	int income_count=0, expense_count=0;
	while(file>>str){
		if(str=="income"){
			file>>str;
			income+=stoi(str);
			income_count++;
		}
		if(str=="expense"){
			file>>str;
			expense+=stoi(str);
			expense_count++;
		}
	}
	int percent_income=100*income_count/(income_count+expense_count);
	int percent_expense=100-percent_income;
	cout<<"\033[1;35mTotal income: \033[0m";
	cout<<"\033[1;32m"<<income<<"("<<percent_income<<"%)\033[0m"<<endl;
	cout<<"\033[1;35mTotal expense: \033[0m";
	cout<<"\033[1;31m"<<expense<<"("<<percent_expense<<"%)\033[0m"<<endl;
	cout<<"\033[1;35mNet value: \033[0m";
	if(income-expense>0)cout<<"\033[1;32m"<<income-expense<<"\033[0m\n"<<endl;
	else cout<<"\033[1;31m"<<income-expense<<"\033[0m\n"<<endl;
	file.close();
	return;
}


int main(){
 	string str, obj;
  	while(true){
  		cout<<"\033[1;35murbao\033[0m"<<":";
	  	cin>>str;
		if(str=="help")help();
		else if(str=="show")show();
		else if(str=="find"){
			cin>>obj;
			find(obj);
		}
		else if(str=="total")total();
		else if(str=="clear")system("clear");
		else if(str=="exit")break;
		else if(str=="append"){
			append();
		}
		else {
			cout<<"\033[1;31mNo corresponding command\033[0m\n";
			cout<<"type `help' for commands help\n"<<endl;
		}
	}
	return 0;
}


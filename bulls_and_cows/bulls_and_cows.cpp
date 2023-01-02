// 1A2B game
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

// show info
void show_info() {
    cout << "==========Bulls & Cows (aka 1A2B)==========\n\n";
    cout << "> from 3 digit to 5 digit (easy -> hard)\n";
    cout << "> each digit is different from the others\n";
    cout << "> A: means number placed in right place\n";
    cout << "> B: means exist but not in the right place\n\n";
    cout << "             Good luck !!\n";
    cout << "===========================================\n";
    system("pause");
    system("cls");
}

// get answer digit
int get_digit(const string& info) {
    bool okay = false;
    string input;
    while (!okay) {
        cout << info;
        getline(cin, input);
        for (int i = 0; i < input.size(); i++) {
            if (!isdigit(input[i]) || input.size() > 1 || input.empty() || input[i] - '0' > 5 || input[i] - '0' < 3) {
                cout << "Error >> not valid input\n\n";
                break;
            } else if (i == input.size() - 1)okay = true;
        }
    }
    cout << "> Game Start\n";
    system("pause");
    system("cls");
    return stoi(input);
}

// random generate number
string generate_num(const int& digit) {
    bool no_repeat = false;
    string random;
    while (!no_repeat) {
        int Max = pow(10, digit), min = pow(10, digit - 2);
        random = to_string(rand() % Max + min);
        if (random.size() == digit - 1)random = '0' + random;
        //check if repeat occur
        int array[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (int i = 0; i < random.size(); i++) {
            for (int j = 0; j < 10; j++) {
                if (random[i] - '0' == j)array[j]++;
            }
        }
        for (int i = 0; i < 10; i++) {
            if (array[i] >= 2)break;
            else if (i == 9)no_repeat = true;
        }
    }
    return random;
}

// get input(with foolproof)
string get_input(const string& info, const int& digit) {
    bool okay = false;
    string input;
    while (!okay) {
        cout << info;
        getline(cin, input);
        for (int i = 0; i < input.size(); i++) {
            // small hack
            if (input == "show me the answer")return input;
            else if (!isdigit(input[i]) || input.size() != digit) {
                cout << "Error >> not valid input\n\n";
                break;
            } else if (i == input.size() - 1)okay = true;
        }
    }
    return input;
}

// analyze input correctness
bool win_game(const string& user_input, const string& random_num, int& A, int& B, const int& guess_count, const int& digit) {
    for (int i = 0; i < digit; i++) {
        // calculate A
        if (user_input[i] == random_num[i])A++;
        for (int j = 0; j < digit; j++) {
            if (i == j);
            else if (user_input[i] == random_num[j])B++;
        }
    }
    if (A == digit) {
        cout << "> Congratulations !! You win !!\n";
        cout << "> Total spent counts: " << guess_count << " times\n\n";
        return true;
    } else {
        cout << "> Status: " << A << "A" << B << "B" << endl << endl;
        return false;
    }
}

// play again or not
bool play_again(const string& info) {
    string reply;
    cout << info;
    getline(cin, reply);
    if (reply == "y" || reply == "Y")return true;
    else if (reply == "n" || reply == "N")return false;
    else return play_again(info);
}

// run the game
void run() {
    // time seed
    srand(time(nullptr));
    bool playing = true;
    while (playing) {
        bool win = false;
        int guess_count = 0;
        show_info();
        int digit = get_digit("> Enter digit: ");
        // generate answer
        string random_num = generate_num(digit);
        // start the game
        while (!win) {
            int A = 0, B = 0;
            string user_input = get_input("> Enter guess number: ", digit);
            guess_count++;
            if (user_input == "show me the answer")cout << "> " << random_num << endl;
            win = win_game(user_input, random_num, A, B, guess_count, digit);
        }
        // check play again
        playing = play_again("Restart ??? (y/n): ");
        system("cls");
        if (!playing){
            cout << "> Hope you enjoy the game\n";
            cout << "> See you next time\n\n";
        }
    }
}

int main() {

    run();

    system("pause");
    return 0;
}
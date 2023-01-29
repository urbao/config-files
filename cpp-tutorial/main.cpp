/*
Creator: Eason Chen 
Purpose: C++ basic implementation and tutorial
*/

# include <iostream>  // library needed included for Input/Output Stream
# include <string> // string library needed included for 'string' datatype usage
# include <vector> // like a 2D array, but more powerful

// There are still so many library avalable to use
using namespace std; // 'std' means Standard, since same object or function might exist in different library
                     // , so we need to tell compiler which exact library we want to use

string username="DoggieChen"; // GLOBAL variable, which can be accessed anywhere in this program
int age=50;   // Integer datatype, Everytime we new a variable, we need to tell exactly wut's the datatype of this variable
char gender='f'; // 'char' is Character datatype, which is composed by only single one letter
bool idiot=true; // 'bool' is Boolean, which only has either 'true(1)' or 'false(0)' value
float weight=12.5; // 'float' can used to represent float point number, and there're also 'double', 'long double'...
char array={}; // a series of same datatype variable, store in line-up array, which user can access via 'index'

// show some datatype memory size
void play_size()
{
    std::cout<<"Integer size: "<<sizeof(15)<<std::endl;
    std::cout<<"Float size: "<<sizeof('d')<<std::endl;
    std::cout<<"String size: "<<sizeof("Hey Hey")<<std::endl;
    std::cout<<"Boolean size: "<<sizeof(true)<<std::endl;

    return;
}

// play with string('void' means return 'NOTHING')
void play_string()
{
    // cout will print out the line behind it
    // 'endl' means 'endline' a.k.a. 'newline'
    // since we already type 'using namespace std;' in line 18, 
    //, so typing 'std::' before cout & endl is not necessary
    std::cout<<"Username: "<<username<<"("<<typeid(username).name()<<")"<<std::endl;

    // print out all single 'char' in the string, and show their datatype
    for(int i=0; i<username.length(); i++)
    {
        std::cout<<to_string(i+1)<<"."<<username[i]<<"("<<typeid(username[i]).name()<<")"<<std::endl;
    }

    // replace substring 'Doggie' with 'Cutey'
    std::cout<<"After replace: "<<username.replace(0, 6, "Cutey")<<std::endl;

     // show length and size of string
    std::cout<<"Username length: "<<username.length()<<std::endl;
    std::cout<<"Username size: "<<sizeof(username)<<std::endl;

    // append description after the username(Can also be achieved by using str1+str2)
    string description=" is so cute!";
    std::cout<<"After append: "<<username.append(description)<<std::endl;

    // show length and size of string AGAIN
    std::cout<<"Username length: "<<username.length()<<std::endl;
    std::cout<<"Username size: "<<sizeof(username)<<std::endl;

    // push_back and pop_back for string
    username.pop_back();
    std::cout<<"After pop_back: "<<username<<std::endl;
    username.push_back('~');
    std::cout<<"After push_back: "<<username<<std::endl; 

    return;
}

// play with integer
void play_integer()
{   
    // show some basic info
    std::cout<<"64-bits Integer Max: "<<INT64_MAX<<std::endl;
    std::cout<<"64-bits Integer min: "<<INT64_MIN<<std::endl;
    std::cout<<"User age: "<<age<<std::endl;
    std::cout<<"After divided by 3: "<<age/3<<std::endl;

    // comparison
    if(age>21)
    {
        std::cout<<"Older than 21"<<std::endl;
    }
    else if(age==21) // remember comparision equal is '==' in C++, while '=' is 'assign operator'
    {
        std::cout<<"Eqaul to 21"<<std::endl;
    }
    else
    {
        std::cout<<"Younger than 21"<<std::endl;
    }

    return;
}

// play float point number
void play_float()
{
    // show some basic info
    std::cout<<"Float Max: "<<__FLT_MAX__<<std::endl;
    std::cout<<"Float min: "<<__FLT_MIN__<<std::endl;
    std::cout<<"User weight: "<<weight<<std::endl;
    std::cout<<"After divided by 3: "<<weight/3<<std::endl;
    return;
}

// play while-loop and passing parameter
void play_while(int times)
{
    // using while loop to print out certain amount of times of line
    /*
    WARNING: the counter MUST changed, or the while-loop will be 
    infinite-loop, and the program will not end itself
    */
    int counter=0; //used to track how many times already printed
    while(counter<times) // end loop condition
    {   
        std::cout<<(counter+1)<<": "<<"\\Doggie Doggie Doggie/"<<std::endl;
        counter++;
    }
    return;
}

// play array
void play_array(int size)
{
    char arr[5]={'D', 'o', 'g', 'g', 'y'}; // initialize an array with size 5
    for (int i=0; i<sizeof(arr); i++)
    {
        std::cout<<arr[i]<<std::endl;
    }

    /*
    HOWEVER, sometimes we dont know wut size we will have in initialization
    , so we will need to use 'new' & 'delete' for asking dynamic memory
    */
    int* arr1=new int[size];
    arr1[0]=10;
    arr1[1]=20;
    arr1[2]=30;
    std::cout<<"arr1:"<<arr1<<std::endl;
    for(int i=0;i<size; i++)
    {
        std::cout<<" "<<arr1[i]<<" ";
        std::cout<<"("<<&arr1[i]<<")"<<std::endl;
    }

    return;
}

// play with 2-dimensional vector
vector<vector<char>> play_vector(int size)
{
    // initialize a 2D vector
    vector<vector<char>> vec(size, vector<char>(size, 'X'));
    for(int i=0; i<vec.size(); i++)
    {
        for(int j=0; j<vec.size(); j++)
        {
            std::cout<<vec[i][j]<<" ";
        }
        std::cout<<endl;
    }

    // assign value to vector
    string line="Doggie";
    for(int i=0; i<vec.size(); i++)
    {
        for(int j=0; j<vec.size(); j++)
        {
            vec[i][j]=line[i];
        }
    }
    return vec;
}


int main() // main body of this whole program, only those inside main() will be executed
{   
    play_size();
    play_string();
    play_integer();
    play_float();
    play_while(20);
    play_array(3);
    vector<vector<char>> result=play_vector(6);
    // print out the 2D vector 'result' for better understanding
    for(int i=0;i<6; i++)
    {
        for (int j=0;j<6;j++)
        {
            std::cout<<result[i][j]<<" ";
        }
        std::cout<<endl;
    }
    return 0; // return 0 tells computer this whole task is finished successfully, and it can end up its work
}
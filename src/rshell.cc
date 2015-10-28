#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <vector>


using namespace std;
using namespace boost;

class Connectors
{
    private:
        string a[100];
        bool state = 1;
    public:
        void setbool(bool b)
        {
            state = b;
        }
        bool getbool()
        {
            return state;
        }
        bool run(string arr[], bool k) == 0;  
};

class Semicolon
{
    public:
    void run(string arr[])
    {

    }
};

class And
{
    public:
    void run(string arr[])
    {

    }

};

class Or
{
    public:
    void run(string arr[])
    {

    }

};



int main()
{

    cout << "$ ";           //outputs terminal $
    string input;
    getline(cin, input);    //gets user input

    vector<string> e_input;        

    tokenizer<> tok(input); //uses tokenizer to parse the input
    for (tokenizer<>::iterator itr = tok.begin(); itr != tok.end(); ++itr)
    {
        if (*itr == ";" ||  )
        {

        e_input.push_back(*itr);               
    }

      

    


}



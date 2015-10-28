#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

class Connectors
{
    private:
        string a[100];
        bool donext;
    public:
        void setbool(bool b)
        {
            donext = b;
        }
        bool getbool()
        {
            return donext;
        }
        bool run(string arr[], bool k) == 0;  
};

class Semicolon
{
    public:
    bool run(string arr[], bool k)
    {

    }
};

class And
{
    public:
    bool run(string arr[], bool k)
    {

    }

};

class Or
{
     public:
    bool run(string arr[], bool k)
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



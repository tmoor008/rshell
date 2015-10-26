#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <queue>

using namespace std;
using namespace boost;

int main()
{

    cout << "$ ";           //outputs terminal $
    string input;
    getline(cin, input);    //gets user input

    queue<string> q;        //creates queue to hold parsed input

    tokenizer<> tok(input); //uses tokenizer to parse the input
    for (tokenizer<>::iterator itr = tok.begin(); itr != tok.end(); ++itr)
    {
        q.push(*itr);       //puts the input, parsed, into a queue    
    }

    //tests that queue is filled
    //unsigned size = q.size();
    //for (unsigned i = 0; i < size; ++i)
    //{
        //cout << q.front() << " ";
        //q.pop();
    //}  




}



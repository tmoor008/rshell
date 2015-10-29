#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <vector>
#include <queue>

using namespace std;
using namespace boost;

class Connectors
{
    private:
        string a[100];
        bool state;
    public:
        Connectors()
        {
            state = 1;
        }
        void setbool(bool b)
        {
            state = b;
        }
        bool getbool()
        {
            return state;
        }
        virtual bool run(string arr[], bool k) = 0;  
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

    //containers we'll use for storage
    vector< vector<string> > v;
    vector<Connectors*> objects;
    queue<string> q;        
    
    bool check = 0;
    int column = 0;
    
    typedef tokenizer<char_separator<char> > tokenizer;
    char_separator<char> sep(" ", ";");
    tokenizer tokens(input, sep);    

    

    for (tokenizer::iterator itr = tokens.begin(); itr != tokens.end(); ++itr)
    {
        if (*itr == ";" && "||" && "&&")
        {
            q.push(*itr);
            v.at(column).push_back(NULL);
            column = column + 1;                             
        }
        else if (*itr == "#")
        {
            break;          //if commented, break out of loop
        }
        else
        {
            v.at(column).push_back(*itr);
        }
    }

    vector<string> current;

    for (unsigned i = 0; i < v.at(i).size(); ++i)
    {
        for (unsigned j = 0; j < v.at(i).at(j).size(); ++j)
        {
            current.push_back(v.at(i).at(j));     
        }
        
        if (q.front() == ";")
        {
            Semicolon s = new Semicolon(current);
            objects.push_back(s);
        }

        if (q.front() == "||")
        {
            Or o = new Or(current);
            objects.push_back(o);
        }
        
        if (q.front() == "&&")
        {
            And a = new And(current);
            objects.push_back(a);
        }

        q.pop();
        current.clear();
    }

    


}



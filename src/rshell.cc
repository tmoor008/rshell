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
        bool state;
    public:
        void setbool(bool b)
        {
            state = b;
        }
        bool getbool()
        {
            return state;
        }
        virtual void  run(string arr[]) = 0;  
};

class Semicolon : public Connectors
{
    private:
         const char *arr[100];
    public:
    Semicolon(vector<string> v)
    {
        setbool(1);
        for (unsigned i = 0; i < v.size(); ++i)
        {
            arr[i] = v.at(i).c_str();    
        }   
    }
    virtual void run(string arr[])
    {

    }
};

class And : public Connectors
{
    private:
        const char *arr[100];
    public:
    And(vector<string> v)
    {
        setbool(1);
        for (unsigned i = 0; i < v.size(); ++i)
        {
            arr[i] = v.at(i).c_str();    
        }   
    }
    virtual void run(string arr[])
    {

    }

};

class Or : public Connectors
{
    private:
        const char *arr[100];
    public:
    Or(vector<string> v)
    {
        setbool(1);
        for (unsigned i = 0; i < v.size(); ++i)
        {
            arr[i] = v.at(i).c_str();    
        }   
    }

    virtual void run(string arr[])
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
            objects.push_back(new Semicolon(current));
        }

        if (q.front() == "||")
        {
            objects.push_back(new Or(current));
        }
        
        if (q.front() == "&&")
        {
            objects.push_back(new And(current));
        }

        q.pop();
        current.clear();
    }



}



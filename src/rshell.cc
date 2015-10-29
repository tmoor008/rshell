#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <vector>
#include <queue>
#include <stdio.h>
#include <cstring>
#include <sys/wait.h>

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
        virtual void  run() = 0;  
};

class Semicolon : public Connectors
{
    private:
        char *arr[100];
    public:
    Semicolon(vector<string> v)
    {
        setbool(1);
        
        for (unsigned i = 0; i < v.size(); ++i)
        {
            string str  = v.at(i);
            char *cstr = new char[str.length() + 1];
            strcpy(cstr, str.c_str());
            arr[i] = cstr;
            delete[] cstr;            
        }
           
    }
    virtual void run()
    {
        pid_t c_pid, pid;
        int status;
        c_pid = fork();

        if (c_pid < 0)
        {
            perror("fork failed");
            setbool(0);
            return;
        }
        else if (c_pid == 0)
        {
            execvp(arr[0], arr);
            perror("execvp failed");
            setbool(0);
        }
        else 
        {
            if ((pid = wait(&status)) < 0)
            {
                perror("wait");
                setbool(0);
                return;
            }
        }

        setbool(1);
        return;
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
    virtual void run()
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

    virtual void run()
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
    vector<string> t;
    vector<Connectors*> objects;
    queue<string> q;        
    
    int column = 0;
    
    typedef tokenizer<char_separator<char> > tokenizer;
    char_separator<char> sep(" ", ";");
    tokenizer tokens(input, sep);    

    
    bool flag = 0;

    for (tokenizer::iterator itr = tokens.begin(); itr != tokens.end(); ++itr)
    {
        if ((*itr == ";") || (*itr == "||") || (*itr == "&&"))   
        {
            q.push(*itr);
            v.at(column).push_back("\0");
            column = column + 1; 
            flag = 0;                            
        }
        else if (*itr == "#")
        {
            break;          //if commented, break out of loop
        }
        else
        {
            if (!flag)
            {
                v.push_back(t);
                v.at(column).push_back(*itr);
                flag = 1;
            }
            else
            {
                v.at(column).push_back(*itr);
            }
        }
    }

    v.at(v.size() - 1).push_back("\0");         //adds null to last command

    //for (unsigned i = 0; i < v.size(); ++i)
    //{
       //for (unsigned j = 0; j < v.at(i).size(); ++j)
       //{
            //cout << v.at(i).at(j);   
       //}
        
    //}

    //cout << "Rows: " << v.size() << endl;
    //cout << "Colums at 1st pos: " << v.at(0).size() << endl;
    //if (v.at(0).at(v.at(0).size() - 1) == "\0")
    //{
        //cout << "NULL" << endl;
    //}
   
    bool first = 1; 
    vector<string> current;

    for (unsigned i = 0; i < v.size(); ++i)
    {
        for (unsigned j = 0; j < v.at(i).at(j).size(); ++j)
        {
            current.push_back(v.at(i).at(j));     
        }
        if (!q.empty())
        {
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
        }
        if (first == 1)
        {
            objects.push_back(new Semicolon(current));
            first = 0;
        }   
        current.clear();
    }
    
    cout << objects.size()  << endl;
    for (unsigned i = 0; i < objects.size(); ++i)
    {
        objects.at(i)->run();
    }



}



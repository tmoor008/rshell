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
            //cout << v.at(i).at(j) << " ";   
        //}
        //cout << endl;
    //}

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

//const char *a[3];
//a[0] = "hello";
//a[1] = "cat";
//a[2] = "tree";

//for (unsigned i = 0; i < 2; ++i)
//{
  //  cout << a[i] << endl;
//}


}



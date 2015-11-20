#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <vector>
#include <queue>
#include <stdio.h>
#include <cstring>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;
using namespace boost;

int parenthesisState(vector<int> v, bool b)
{
    int totalState = v.at(v.size() - 1);

    return totalState;
}


class Connectors    //abstract base class so we can dynamically call run
{
    public:
        virtual ~Connectors()
        {}
        virtual int run(int state) = 0;  
};

class Semicolon : public Connectors
{
    private:
       vector<char *> vctr; 
    public:
    Semicolon(vector<string> v) : vctr(50)  //constructor creates char* vector
    {                                       //which stores one command+params
        vctr.reserve(v.size());             //in a semicolon object
        for (unsigned i = 0; i < v.size(); ++i)
        {
            vctr[i] = const_cast<char*>(v[i].c_str());
        }
        vctr.push_back(NULL);   //makes sure the command ends with a null char
    }
    virtual ~Semicolon()
    {
        unsigned sz = vctr.size();
        for (unsigned i = 0; i < sz; ++i)
        {
            vctr.pop_back();
        }
    }
                           //so execvp can determine the end
    virtual int run(int state)
    {
        char **pointer = &vctr[0];  //points to vctr we'll use for execvp
        
        string ex = "exit";
        string p = pointer[0];
        if (p == ex) // check if the command entered is exit
        {
            state = -1;
            return state;
        }
        
        pid_t c_pid, pid;
        int status;
        c_pid = fork();

        if (c_pid < 0)      //checks if fork failed
        {
            perror("fork failed");
            state = 0; 
            return state;
        }
        else if (c_pid == 0)    //if we're in the child, call execvp
        {
            execvp(pointer[0], pointer);
            perror("execvp failed");
            exit(127);         
        }
        else //if in the parent, wait for child to terminate
        {
            //checks if wait fails
            if ((pid = waitpid(c_pid, &status, 0)) < 0)
            {
                perror("wait failed");
                state = 0;
                return state;
            }
            //checks whether the child succeeded or not
            //returns the state accordingly
            if (status == 0)
            {
                state = 1; //if it succeeded, set the state to true
                return state;
            }
            else
            {
                state = 0;
                return state;
            }
        }
        return 0;
    }
};

class And : public Connectors
{
    private:
       vector<char *> vctr; 
    public:
    And(vector<string> v) : vctr(50)
    {       
        vctr.reserve(v.size()); //store one command+param of type And
        for (unsigned i = 0; i < v.size(); ++i)
        {
            vctr[i] = const_cast<char*>(v[i].c_str());
        }
        vctr.push_back(NULL); //end with null char
    }

    virtual ~And()
    {
        unsigned sz = vctr.size();
        for (unsigned i = 0; i < sz; ++i)
        {
            vctr.pop_back();
        }
    }

    virtual int run(int state)
    {
        if (state != 1) //return if the previous command failed
        {
            return state;
        }    
    
        char **pointer = &vctr[0];  //points to vctr we'll use for execvp
        
        string ex = "exit";
        string p = pointer[0];
        if (p == ex) // check if the command entered is exit
        {
            state = -1;
            return state;
        }
        
        pid_t c_pid, pid;
        int status;
        c_pid = fork();

        if (c_pid < 0)      //checks if fork failed
        {
            perror("fork failed");
            state = 0; 
            return state;
        }
        else if (c_pid == 0)    //if we're in the child, call execvp
        {
            execvp(pointer[0], pointer);
            perror("execvp failed");
            exit(127);         
        }
        else //if in the parent, wait for child to terminate
        {
            //checks if wait fails
            if ((pid = waitpid(c_pid, &status, 0)) < 0)
            {
                perror("wait failed");
                state = 0;
                return state;
            }
            //checks whether the child succeeded or not
            //outputs the state accordingly
            if (status == 0)
            {
                state = 1; //if it succeeded, set the state to true
                return state;
            }
            else
            {
                state = 0;
                return state;
            }
        }
        return 0;    
    }
};

class Or : public Connectors
{
    private:
       vector<char *> vctr; 
    public:
    Or(vector<string> v) : vctr(50) //stores one command+params of type Or
    {       
        vctr.reserve(v.size());
        for (unsigned i = 0; i < v.size(); ++i)
        {
            vctr[i] = const_cast<char*>(v[i].c_str());
        }
        vctr.push_back(NULL); //end with null
    }
    virtual ~Or()
    {
        unsigned sz = vctr.size();
        for (unsigned i = 0; i < sz; ++i)
        {
            vctr.pop_back();
        }
    }

    virtual int run(int state)
    {
        if (state != 0) //return if the previous command succeeded
        {
            return state;
        }    
        
        char **pointer = &vctr[0];  //points to vctr we'll use for execvp
        
        string ex = "exit";
        string p = pointer[0];
        if (p == ex) // check if the command entered is exit
        {
            state = -1;
            return state;
        }
        
        pid_t c_pid, pid;
        int status;
        c_pid = fork();

        if (c_pid < 0)      //checks if fork failed
        {
            perror("fork failed");
            state = 0; 
            return state;
        }
        else if (c_pid == 0)    //if we're in the child, call execvp
        {
            execvp(pointer[0], pointer);
            perror("execvp failed");
            exit(127);         
        }
        else //if in the parent, wait for child to terminate
        {
            //checks if wait fails
            if ((pid = waitpid(c_pid, &status, 0)) < 0)
            {
                perror("wait failed");
                state = 0;
                return state;
            }
            //checks whether the child succeeded or not
            //outputs the state accodingly
            if (status == 0)
            {
                state = 1; //if it succeeded, set the state to true
                return state;
            }
            else
            {
                state = 0;
                return state;
            }
        }
        return 0; 
    }
};

class Por : public Connectors
{
    private:
        vector< vector<string> > pv;
        queue<string> pq;
    public:
    Por(vector< vector<string> > v, queue<string> q) : pv(v), pq(q) 
    {}
    virtual ~Por()
    {
        unsigned sz = pv.size();
        for (unsigned i = 0; i < sz; ++i)
        {
            pv.pop_back();
        }
        sz = pq.size();
        for (unsigned i = 0; i < sz; ++i)
        {
            pq.pop();
        }
    }
    virtual int run(int state)
    {
        pq.pop();
        if (state == 1) // return state if the previous command succeeded
        {
            return state; 
        }        
        
        vector<Connectors*> objects;
        bool first = 1;
        vector<string> current;
        bool semiCheck = 0; // flag for semicolon object in the objects vector
        for (unsigned i = 0; i < pv.size(); ++i)
        {
            for (unsigned j = 0; j < pv.at(i).size(); ++j)
            {
                current.push_back(pv.at(i).at(j));     
            }
            if (!pq.empty() && first != 1)
            {
                if (pq.front() == ";")
                {
                    objects.push_back(new Semicolon(current));
                    semiCheck = 1; // if a semicolon object is created set flag to true
                }

                if (pq.front() == "|")
                {   
                    objects.push_back(new Or(current));
                }
            
                if (pq.front() == "&")
                {
                    objects.push_back(new And(current));
                }
                pq.pop();
            }
            if (first == 1)
            {   
                objects.push_back(new Semicolon(current));
                first = 0;
            }   
            current.clear();
        }

        int beg = 0;
        int durr = 0;

        vector<int> pStates; // vector that holds the states of the run loop

        //this loop goes through the object vector and calls run on each 
        //object, dynamically calling the run of the class type
        //cout << "Size: " << objects.size()  << endl;
        for (unsigned i = 0; i < objects.size(); ++i)
        {
            pStates.push_back(beg); // push the beg state into the pCheck vector
            //cout << "Curr size: " << objects.size() << endl;
            durr = objects.at(i)->run(beg);
            //cout << "State after run: " << durr << endl;
            //check for if exit is called
            if (durr == -1)
            {
                break;
            }
            beg = durr;
        }
        
        //deletes the dynamically allocated memory
        Connectors *p;
        for (vector<Connectors*>::iterator ptr = objects.begin(); ptr != objects.end();
        ++ptr)
        {
            p = *ptr;
            delete p;
        }
        p = NULL;
        return parenthesisState(pStates, semiCheck);        
   }
   
};



class Pand : public Connectors
{
    private:
        vector< vector<string> > pv;
        queue<string> pq;
    public:
    Pand(vector< vector<string> > v, queue<string> q) : pv(v), pq(q) 
    {}
    virtual ~Pand()
    {
        unsigned sz = pv.size();
        for (unsigned i = 0; i < sz; ++i)
        {
            pv.pop_back();
        }
        sz = pq.size();
        for (unsigned i = 0; i < sz; ++i)
        {
            pq.pop();
        }
    }
    virtual int run(int state)
    {
        pq.pop();
        if (state == 0) // return state if the previous command failed
        {
            return state; 
        }        
        
        vector<Connectors*> objects;
        bool first = 1;
        vector<string> current;
        bool semiCheck = 0; // flag for semicolon object in the objects vector
        for (unsigned i = 0; i < pv.size(); ++i)
        {
            for (unsigned j = 0; j < pv.at(i).size(); ++j)
            {
                current.push_back(pv.at(i).at(j));     
            }
            if (!pq.empty() && first != 1)
            {
                if (pq.front() == ";")
                {
                    objects.push_back(new Semicolon(current));
                    semiCheck = 1; // if a semicolon object is created set flag to true
                }

                if (pq.front() == "|")
                {   
                    objects.push_back(new Or(current));
                }
            
                if (pq.front() == "&")
                {
                    objects.push_back(new And(current));
                }
                pq.pop();
            }
            if (first == 1)
            {   
                objects.push_back(new Semicolon(current));
                first = 0;
            }   
            current.clear();
        }

        int beg = 0;
        int durr = 0;

        vector<int> pStates; // vector that holds the states of the run loop

        //this loop goes through the object vector and calls run on each 
        //object, dynamically calling the run of the class type
        //cout << "Size: " << objects.size()  << endl;
        for (unsigned i = 0; i < objects.size(); ++i)
        {
            pStates.push_back(beg); // push the beg state into the pCheck vector
            //cout << "Curr size: " << objects.size() << endl;
            durr = objects.at(i)->run(beg);
            //cout << "State after run: " << durr << endl;
            //check for if exit is called
            if (durr == -1)
            {
                break;
            }
            beg = durr;
        }
        
        //deletes the dynamically allocated memory
        Connectors *p;
        for (vector<Connectors*>::iterator ptr = objects.begin(); ptr != objects.end();
        ++ptr)
        {
            p = *ptr;
            delete p;
        }
        p = NULL;
        return parenthesisState(pStates, semiCheck);        
   }
   
};

class Psemicolon : public Connectors
{
    private:
        vector< vector<string> > pv;
        queue<string> pq;
    public:
    Psemicolon(vector< vector<string> > v, queue<string> q) : pv(v), pq(q) 
    {}
    virtual ~Psemicolon()
    {
        unsigned sz = pv.size();
        for (unsigned i = 0; i < sz; ++i)
        {
            pv.pop_back();
        }
        sz = pq.size();
        for (unsigned i = 0; i < sz; ++i)
        {
            pq.pop();
        }
    }
    virtual int run(int state)
    {
        pq.pop();
        vector<Connectors*> objects;
        bool first = 1;
        vector<string> current;
        bool semiCheck = 0; // flag for semicolon object in the objects vector
        for (unsigned i = 0; i < pv.size(); ++i)
        {
            for (unsigned j = 0; j < pv.at(i).size(); ++j)
            {
                current.push_back(pv.at(i).at(j));     
            }
            if (!pq.empty() && first != 1)
            {
                if (pq.front() == ";")
                {
                    objects.push_back(new Semicolon(current));
                    semiCheck = 1; // if a semicolon object is created set flag to true
                }

                if (pq.front() == "|")
                {   
                    objects.push_back(new Or(current));
                }
            
                if (pq.front() == "&")
                {
                    objects.push_back(new And(current));
                }
                pq.pop();
            }
            if (first == 1)
            {   
                objects.push_back(new Semicolon(current));
                first = 0;
            }   
            current.clear();
        }

        int beg = 0;
        int durr = 0;

        vector<int> pStates; // vector that holds the states of the run loop

        //this loop goes through the object vector and calls run on each 
        //object, dynamically calling the run of the class type
        //cout << "Size: " << objects.size()  << endl;
        for (unsigned i = 0; i < objects.size(); ++i)
        {
            if (i != 0)
            {
                pStates.push_back(beg); // push the beg state into the pCheck vector
            }
            //cout << "Curr size: " << objects.size() << endl;
            durr = objects.at(i)->run(beg);
            //cout << "State after run: " << durr << endl;
            //check for if exit is called
            if (durr == -1)
            {
                break;
            }
            beg = durr;
        }
        pStates.push_back(beg);
        //deletes the dynamically allocated memory
        Connectors *p;
        for (vector<Connectors*>::iterator ptr = objects.begin(); ptr != objects.end();
        ++ptr)
        {
            p = *ptr;
            delete p;
        }
        p = NULL;
        return parenthesisState(pStates, semiCheck);        
   }
   
};

int main()
{
    int w = 0;
    while (w == 0)
    {   
        // extra credit part
        char *username;
        int host;
        if ((username = getlogin()) != NULL) // get the username
        {
            char name[101];
            int len = 100;
            if ((host = gethostname(name, len)) == 0) // get the hostname
            {
                cout << username << "@" << name << "$ ";        
            }
            else
            {
                 cout << "$ ";           //outputs terminal $
            }
        }
        else
        {
            cout << "$ ";
        }
    
        string input;
        getline(cin, input);    //gets user input    

        //containers we'll use for storage
        vector< vector<string> > v;
        vector<string> t;
        vector<Connectors*> objects;
        queue<string> q;        
        
        int column = 0;
        
        //creates tokenizer and char separator to parse input
        typedef tokenizer<char_separator<char> > tokenizer; 
        char_separator<char> sep(" ", ";#|&()[]\"");
        tokenizer tokens(input, sep);

        bool lastVal = 0;
        bool firstVal = 0;
 
        //checks for placement of connectors
        for (tokenizer::iterator check = tokens.begin(); check != tokens.end(); ++check)
        {
            if (check == tokens.begin())
            {
                if ((*check == "|") || (*check == "&") || (*check == ";"))
                {
                    firstVal = 1;
                }
            }
            tokenizer::iterator count = check;
            ++count;
            if (count == tokens.end())
            {
                if ((*check == "|") || (*check == "&"))
                {                
                    lastVal = 1;
                }    
            }
        }

        //loops again if the input begins or ends with a connector    
        if (firstVal == 1)
        {
            cout << "beginning of input cannot be a connector" << endl;
            continue;
        }

        if (lastVal == 1)
        {
            cout << "end of input cannot be a connector" << endl;
            continue;
        }

        bool flag = 0; //flag to check when to start a new column
        bool wrong = 0;
        bool quotes = 0;
        bool endquote = 0;
        //holds commands in a 2d vector


        //pushes commands into 2d vector and pushes connectors into a queue
        for (tokenizer::iterator itr = tokens.begin(); itr != tokens.end(); ++itr)
        {
            tokenizer::iterator temp = itr;
            if (*itr == ";" && !quotes)
            {
                ++temp;
                if (temp != tokens.end())
                {
                    if (*temp == *itr)
                    {
                        cout << "cannot have multiple semicolons" << endl;
                        wrong = 1;
                        break;
                    }
                }
                q.push(*itr);
                column = column + 1;
                flag = 0;   
            }
            else if (((*itr == "|") || (*itr == "&")) && !quotes)   
            {
                ++temp;
                if (*temp != *itr)
                {
                    cout << "cannot enter single connector" << endl;
                    wrong = 1;
                    break;
                }
                ++temp;
                if (*temp == *itr)
                {
                    cout << "cannot enter 3+ connector" << endl;
                    wrong = 1;
                    break;   
                }
                         
                q.push(*itr); //pushes connector into queue
                column = column + 1; //increments column
                flag = 0;
                ++itr;  //extra increments itr to not test second connector in pair                             
            }
            else if (((*itr == "[") || (*itr == "]")) && !quotes)
            {
                if (*itr == "[")
                {
                    v.push_back(t);
                    v.at(column).push_back("test");
                    flag = 1;
                }
            }
            //extra credit that implements quotation marks
            else if (*itr == "\"")
            {
                if (!endquote)
                {
                    quotes = 1; //sets a flag to bundle everything in quotes
                    endquote = 1;
                }
                else
                {
                    quotes = 0;
                    endquote = 0;
                }
            }
            else if (*itr == "#" && !quotes)
            {
                break;          //if there's a comment, break out of loop
            }
            else
            {
                //checks for () to parse them into their own columns
                if (*itr == "(" && !quotes)
                {
                    q.push(";");
                    v.push_back(t);
                    v.at(column).push_back(*itr);
                    column = column + 1;
                    flag = 0;
                    
                }
                else if (*itr == ")" && !quotes)
                {
                    column = column + 1;
                    v.push_back(t);
                    v.at(column).push_back(*itr);
                    flag = 0;
                   
                }
                else if (!flag)
                {
                    v.push_back(t); //starts a new column
                    v.at(column).push_back(*itr);
                    flag = 1;
                }
                else
                { //push value into position
                    v.at(column).push_back(*itr);
                }
            }
        }

        //checks the contents of v
        //for (unsigned i = 0; i < v.size(); ++i)
        //{
           //for (unsigned j = 0; j < v.at(i).size(); ++j)
           //{
                //cout << v.at(i).at(j) << " *** ";   
           //}
             //cout << endl; 
        //}
        //cout << endl; 
        //loops if wrong amt of connectors are entered
        if (wrong == 1)
        {
            continue;
        }

        //this part of the code creates a temp vector current which holds
        //a single command+param chunk at a time
        //then determines the connector previous to the command its told to run
        //it then creates the corresponding connector class type object
        //and pushes the new object into a vector of Connectors pointers
        bool first = 1;
        bool pflag = 0;
        string ptype = "default";        
        vector<string> r;
        vector < vector<string> > paren;        
        int col = 0;
        queue<string> pqu;

        vector<string> current;
        for (unsigned i = 0; i < v.size(); ++i)
        {
            for (unsigned j = 0; j < v.at(i).size(); ++j)
            {
                current.push_back(v.at(i).at(j));     
            }
            if (current.at(0) == "(") //checks type of () object to make
            {
                pflag = 1;
                if (first == 1)
                {
                    ptype = ";";
                    first = 0;
                    current.clear();
                    continue;
                }
                else if (!q.empty() && !first)
                {
                    col = 0;
                    if (q.front() == ";")
                    {
                        ptype = ";";    
                    }
                    else if (q.front() == "&")
                    {
                        ptype = "&";    
                    }
                    else if (q.front() == "|")
                    {
                        ptype = "|";
                    }
                    q.pop();
                    current.clear();
                    continue;
                }
                first = 0;
            }
            else if ((!q.empty() && first != 1) || pflag == 1)
            {
                //pushes items inside () into a temp 2D vector
                //which is then passed into a Pcommand object
                if (pflag == 1)
                {
                    if (current.at(0) == ")")
                    {
                        pflag = 0;
                        if (ptype == ";" || ptype == "default")
                        {
                            objects.push_back(new Psemicolon(paren, pqu));
                        }
                        if (ptype == "&")
                        {
                            objects.push_back(new Pand(paren, pqu));
                        }
                        if (ptype == "|")
                        {
                            objects.push_back(new Por(paren, pqu));
                        }
                        paren.clear();
                        while (!pqu.empty())
                        {
                            pqu.pop();
                        }
                    }    
                    else
                    {   
                        paren.push_back(r);
                        for (unsigned k = 0; k < current.size(); ++k)
                        {
                            paren.at(col).push_back(current.at(k));   
                        }
                        col = col + 1;
                        if (!q.empty())
                        {
                            pqu.push(q.front());
                            q.pop();
                        }
                    }
                    current.clear();
                    continue;    
                }
                if (q.front() == ";")
                {
                    objects.push_back(new Semicolon(current));
                }

                if (q.front() == "|")
                {   
                    objects.push_back(new Or(current));

                }
                if (q.front() == "&")
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

        int beg = 0;
        int durr = 0;

        //this loop goes through the object vector and calls run on each 
        //object, dynamically calling the run of the class type
        //cout << "Size: " << objects.size()  << endl;
        for (unsigned i = 0; i < objects.size(); ++i)
        {
            durr = objects.at(i)->run(beg);
            //check for if exit is called
            if (durr == -1)
            {
                break;
            }
            beg = durr;
        }
        
        //deletes the dynamically allocated memory
        Connectors *p;
        for (vector<Connectors*>::iterator ptr = objects.begin(); ptr != objects.end();
        ++ptr)
        {
            p = *ptr;
            delete p;
        }
        p = NULL;
        
        //makes sure to end program if exit is called
        if (durr == -1)
        {
            break;
        }
    }
    return 0;
}



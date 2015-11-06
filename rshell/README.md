Tia Moore

Monica Moreno

---
# Rshell Project
---

> Summary

This is Monica Moreno and Tia Moore's implementation of a command shell called 
rshell.
Our code prints a command prompt which reads in a line of commands and 
connectors. We then parse the input line using a tokenizer. We use the tokenizer
separator to separate not only on spaces but on the connectors as well.

```C++
char_separator<char> sep(" ", ";#|&");
tokenizer tokens(input, sep);
```
We then push our tokenized input into a 2D vector. Each column holds one command
and any flags or aparameters it may have. A new column is created when a 
connector is reached. Connectors are not stored in the array, rather, they
are pushed into a queue so that we can pop them off in the order they were
input.

```C++
vector< vector<string> > v;
queue<string> q;
```

We then create a temporary string vector to hold a single command
and it's parameters/flags at a time. We then pop off the front connector 
from the queue to determine what type of object the command should be.

```C++
class Connectors
{
    public:
        virtual bool run(bool state) = 0;
}
```

We haved created an abstract base class, class Connecctors, which allows us
to dynamically call run on each type of object.

We have three types of objects

---
1. Semicolon
  + Commands that should run regardless of the previous commands success or failure
2. Or
  + Commands that run only if the previous command failed
3. And
  + Commands that run only if the previous command succeeded

--- 

We then created a vector of Connectors object pointers in order to store
each new object of the three different classes we create. 

```C++
vector<Connectors*> objects;

objects.push_back(new Semicolon(current));
objects.push_back(new Or(current));
objects.push_back(new And(current));
```

We then iterate through our objects vector so that we can call run on
each type of object.

Each of our run functions checks the specific state needed to run
as well as checks for the exit call.

We then use fork() to create a child process which can then use the
execvp() call to run the passed in command.

```C++
c_pid = fork();

execvp(pointer[0], pointer);
```

 Depending on execvp()
succeeding or failing, we can set the new bool state and return to run
the next object's run. 

> Known Bugs

1. If one enters the up arrow key multiple times, and then backspaces, 
    they can possibly delete the $.
2. If the '#' is appended to an echo statement, it considers it a
    comment and does not output it along with the rest of the echo.
    This still makes everything after it a comment.
3. In script, if you use backspace, the resulting code will sometimes show random
    letters in the commands. 
4. There is a possibility that getlogin() and gethostname() may fail. 

 

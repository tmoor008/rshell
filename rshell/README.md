# Rshell Project
---

> Summary

`This is Monica Moreno and Tia Moore's implementation of a command shell called 
rshell.
Our code prints a command prompt which reads in a line of commands and 
connectors. We then parse the input line using a tokenizer. We use the tokenizer
separator to separate not only on spaces but on the connectors as well.`

```C++
char_separator<char> sep(" ", ";#|&");
tokenizer tokens(input, sep);
```
`We then push our tokenized input into a 2D vector. Each column holds one command
and any flags or aparameters it may have. A new column is created when a 
connector is reached. Connectors are not stored in the array, rather, they
are pushed into a queue so that we can pop them off in the order they were
input.`

```C++
vector< vector<string> > v;
queue<string> q;
```

`We then create a temporary string vector to hold a single command
and it's parameters/flags at a time. We then pop off the ront connector 
from the queue to determine what type of object the command should be.`

`We have three types of objects`
---
1. Semicolon
  + Commands that should run regardless of the previous commands success or failure
2. Or
  + Commands that run only if the previous command failed
3. And
  + Commands that run only if the previous command succeeded
--- 
 

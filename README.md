# A program that emulates the unix pipe function ("|").

It must be executed as follows:
~~~
  ./pipex file1 cmd1 cmd2 file2
~~~

and behave like the shell commmand line:
~~~
   < file1 cmd1 | cmd2 > file2
~~~
   
## BONUS PART~~~

Compile with "make bonus" to handle multiple pipes:
~~~
   ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
~~~
And HereDocs:
 ~~~
 ./pipex here_doc LIMITER cmd cmd1 file  ==  cmd << LIMITER | cmd1 >> file
~~~

### Leaks check and suppression

Check for memory leaks and the state of processes and File Descriptors with:
~~~
valgrind --track-origins=yes --show-leak-kinds=all --leak-check=full --track-fds=yes --trace-children=yes
~~~

Suppress memory leaks from system functions by adding:

~~~
 --suppressions=supp.supp
~~~

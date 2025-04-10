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

### Leak suppression

Suppress memory leaks from system functions with:

~~~
vlagrind valchild --suppressions=supp.supp
~~~

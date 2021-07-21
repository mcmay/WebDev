This is an application for learning English vocabulary which enables the user to save a particular sense of a word with a certain part of speech into an html file.  This particular sense of the word is extracted from an existing html file obtained by saving the search result of the Lingoes dictionary.

This app is executed with a shell script, "scripthtm.sh", which
  1) 


The script executes two programs written in C are executed. One of the programs:

  1) copies the body section of a given html file whose file name is received as the only argument of the shell script. 
  2) writes the copied body into a temporary file, "temp2.htm", for further processing.

The other C program:

  1) asks for
  2)  

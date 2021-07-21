This is an application for learning English vocabulary which enables the user to save a particular sense of a word with a certain part of speech into an html file.  This particular sense of the word is extracted from a source html file obtained by saving the search result of the Lingoes dictionary.

This app is executed with a shell script, "scripthtm.sh", which
  1) creates an empty html file, "temp1.htm", and copies the content of the "beforeBody.htm" file to temp1.htm. "beforeBody.htm" is the part of the aforementioned source html before its <BODY> tag.
  2) executes the "getBodyElement" program which copies the body section of the source html file to an html file, "temp2.htm";
  3) moves "temp2.htm" to the "Studying/htm_samples_with_tests/" directory;
  


The script executes two programs written in C are executed. One of the programs:

  1) copies the body section of a given html file whose file name is received as the only argument of the shell script. 
  2) writes the copied body into an html file, "temp2.htm", which it creates.

The other C program:

  1) asks for
  2)  

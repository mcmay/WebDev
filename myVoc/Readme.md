This is an application for learning English vocabulary which enables the user to save a particular sense of a word with a certain part of speech into an html file.  This particular sense of the word is extracted from a source html file obtained by saving the search result of the Lingoes dictionary.

This app is executed with a shell script, "scripthtm.sh", which
  1) creates an empty html file, "temp1.htm", and copies the content of the "beforeBody.htm" file to temp1.htm. "beforeBody.htm" is the part of the aforementioned source html file before its <BODY> tag.
  2) executes the "getBodyElement" program which copies the body section of the source html file to an html file, "temp2.htm";
  3) moves "temp2.htm" to the "Studying/htm_samples_with_tests/" directory;
  4) appends the content of "temp2.htm" to "temp1.htm";
  5) appends "myScriptLast.htm" to "temp1.htm" so that now "temp1.htm" becomes a whole html file with a head and body with JavaScript code attached;
  6) remove source html file and "temp2.htm";
  7) rename "temp1.htm" to the name of the source html file (hereafter called the "middle file").
  8) executes the "insertTagsInExample" which takes the newly created middle file, extracts the particular sense signified by the tags in file's name, asks for user input of a possible collocation and example and create an html file ;
  9) 


The script executes two programs written in C are executed. One of the programs:

  1) copies the body section of a given html file whose file name is received as the only argument of the shell script. 
  2) writes the copied body into an html file, "temp2.htm", which it creates.

The other C program:

  1) asks for
  2)  

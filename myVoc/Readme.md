This is an application for learning English vocabulary which enables the user to save a particular sense of a word with a certain part of speech into an html file.  The particular sense of the word is extracted from a source html file obtained by saving the search result of the Lingoes dictionary. I refer to the particular sense as the "target sense" in the rest of this document.

This app is executed with a shell script, "scripthtm.sh", which

  1) creates an empty html file, "temp1.htm", and copies the content of the "beforeBody.htm" file to temp1.htm. "beforeBody.htm" is the part of the aforementioned source html file before its <BODY> tag.
  2) executes the C program "getBodyElement" program which copies the body section of the source html file to an html file, "temp2.htm";
  3) moves "temp2.htm" to the "Studying/htm_samples_with_tests/" directory;
  4) appends the content of "temp2.htm" to "temp1.htm";
  5) appends "myScriptLast.htm" to "temp1.htm" so that now "temp1.htm" becomes a whole html file with a head and body with JavaScript code attached;
  6) remove source html file and "temp2.htm";
  7) rename "temp1.htm" to the name of the source html file (hereafter referred to as the "middle file").
  8) executes the C program "insertTagsInExample" which 
      a) takes the middle file as an argument, 
      b) extracts from the file the particular sense signified by the tags in file's name, 
      c) asks for user input of a possible collocation and a possible example,
      d) inserts the collocation and example, if any, into the middle file, and
      e) writes the updated middle file to an html file, "temp3.htm".
  9) remove the middle file and rename "temp3.htm" to name of the source htm file.
  
  While the resulting product file bears the name of the source htm file, it now has very much different contents and functionalities. It
  
  1) prompts the user to enter its file name when opened and asks the user to enter whether they wish to take a test; 
  2) displays the word in the file name entered by the user;'
  3) inserts a button with the button text "Shown Meaning" if the user entered "y" when prompted for their decision to take a test; If "n" is entered, displays meaning of the word directly or displays the meaning after the user pressed the "Shown Meaning" button;
  4) displays only the aforementioned target sense of the word followed by its part of speech;
  5) displays example(s) provided by the Lingoes dictionary in the source html file with the headword colored red for prominence;
  6) displays any collocations or examples entered by the user when the "insertTagesInExample" program is running;
  7) displays the number of times the user has encountered the word, which is indicated by a suffix in the name of the source html file;
  8) displays a button with the button text "Try it" and prompts the user to enter an example of their own creation if the user pressed the button;
  9) places the example entered by the user under the line of text "Your own example:".
  
  Now a customised flashcard for learning new words results.

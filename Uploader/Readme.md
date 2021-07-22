This java GUI program does the following:

  1) copying or moving one or more files (the 'target file) stored in a certain directory on a computer to a directory (the 'destination directory') under the root directory of the Apache server running on the same computer;
  2) getting the path of each target file in the destination directory;
  3) constructing an href attribute with the path of the target file;
  4) constructing a <a> element with the href attribute;
  5) constructing a <li> element with the <a> element; and
  6) insterting the <li> element into the <ul> list of an index.html file. 
  
  
This program loads files with the "Open" menu item in its "File" menu. The "Files" scrollable pane under the menu displays the paths of files selected. The three buttons at the bottom of the "Files" pane has the following functionalities respectively:
  a) the "Copy" button enabled when files are loaded copies the selected files to the destination directory so that the selected files remain in their source directories;
  b) the "Move" button is different from the "Copy" button in that it moves the selected files to avoid creating unnecssary copies;
  c) the "Clear" button enabled when files are loaded clears the "Files" pane of the paths of selected files and release any loaded files.

With this utitlity, a user with Java and an Apache server installed on their computer can easily let their computer work as a file server and share files with other users in the same LAN by sending the link to that file on the index.html page.

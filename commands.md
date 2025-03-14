
    
    Linux file management and file manipulation commands (all of these commands need to have the "xx" prefix):


    -touch <filename1> <filename2> <filename3> ... - command is used to create one or multiple files to the currect directory.
    -rm <filename1> <filename2> <filename3> ... - command is used to delete one or multiple files from a currect directory.
    -echo <message> <append mode> <filesname> - command is used to create and write the message directly into a file (append mode is written is square brackets).
    -mv:
        * mv <filesname1> <filename2> <filename3> .. <directoriesPath> - command is used to move one or multiple files to a directory.
        * mv <filesname1> <filesname2> - command is used to rename <filesname1> name to <filesname2> name.
    -cat:
        * cat <filesname> - command is used to print out to the console files content.
        * cat <appendMode> <filename> - command is used to rewrite or append text to a file. (">>" - is append mode and ">" - truncate mode.(append mode command is written with duoble quotes - "")).
    -mkdir <directoriesPath> - command is used to create single or nested directories.
    -rmdir <directoriesPath> - command is used to delete the directory and its content.
    -ls:
        * ls - command is used to print current directories content.
        * ls <filesFormat> - command is used to print only the certaint type of files in a current directory.
    -find <directoriesPath> <constantVariable> <filename> - command is used to find the file in specified directory. (directoriesPath is '.' searching is in current path. constantVariable should always have dash in front of its have and commands: "-path" - if found displays the files path; "-name" - if found displays the files name).



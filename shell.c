#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"




int main(){
       
       while(1){
              char currentPath[1024] = ""; // the path that the user currently is located in
              char commandLine[1024] = ""; // user input
              char** commandArr[1024] = {NULL}; // two dimensional array
              
              shellPrompt(currentPath); // display user and the directory the user is in
              handleInput(commandLine, commandArr);// handels the user input(command)
              if(strcmp(commandArr[0][0], "cd") == 0){  // if cd
                     changeDirectory(commandArr[0]);   
              }
              // if no cd
              else{ 
                     if(commandArr[1] == NULL){ // if no pipe
                            executeCommand(commandArr[0]);
                     }
                     else{ // if pipe
                            executePipe(commandArr);
                     }
              }
              freeMem(commandArr); // free up the allocated memory
       }
}


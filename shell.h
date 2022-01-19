void shellPrompt(char* currentPath);
void handleInput(char* commandLine, char*** commandArr);
char ** allocateMem(char * commandLine);
void strTokenizer(char* commandLine, char* command[], char* delim);
void changeDirectory(char** command);
void executeCommand(char** command);
void executePipe(char *** command);
void freeMem(char *** commandArr);

void shellPrompt(char* currentPath){
       char hostName[1024];

       // clear shell at startup
       static int first_time = 1;
       if(first_time){
              system("clear");
              first_time = 0;
       }
       // display hostname and the directory is currently present in
       gethostname(hostName, sizeof(hostName));
       printf("%s@%s:%s$ ", getenv("LOGNAME"), hostName, getcwd(currentPath, 1024));
}

void handleInput(char* commandLine, char*** commandArr){
       fgets(commandLine, 1024, stdin); // Stores user input in array of string commandLine
              
       // removing newline characters
       size_t length = strlen(commandLine); 
       if(*commandLine && commandLine[length - 1] == '\n'){
              commandLine[length - 1] = '\0';
       }

       // if user input is equal to exit close the program
       if(strcmp(commandLine, "exit") == 0){ // If user input is equal to exit break
              exit(0);
       }
       //if pipe
       if(strstr(commandLine, "|")){
            char* commands[1024];
            strTokenizer(commandLine, commands, "|"); // tokenize pipe
            for(int i = 0; commands[i] != NULL; i++){
              commandArr[i] = allocateMem(commands[i]); // allocate memory and save in commandArr
            }  

       }
       // if no pipe
       else{
              commandArr[0] = allocateMem(commandLine); // allocate memory and save in commandArr
       }

}

char** allocateMem(char* commandLine){
       // allocate the appropriate space for the user input command
       char ** command = malloc(1024 * sizeof(char*));
       for (int i = 0 ; i < 1024; ++i)
        command[i] = malloc(1024 * sizeof(char));
       strTokenizer(commandLine, command, " "); // tokenize space
       return command;
}

void strTokenizer(char* commandLine, char* command[], char* delim){
       int i = 0;

       // takes a string and splits it up into parts depending on the delimiter
       command[i] = strtok(commandLine, delim);
       while(command[i] != NULL){
              command[++i] = strtok(NULL, delim);
       }
}

void changeDirectory(char** command){
       if(command[1] == NULL){ // if user only inputs cd
              chdir(getenv("HOME"));
       }
       else{
              if(chdir(command[1]) == -1){ // if the directory is not present
                     printf("%s: No such file or directory\n", command[1]);
              }
       }        
}

void executeCommand(char** command){
       int pid = fork(); // Forking child

       if(pid==0){
              execvp(command[0], command); // execute command
              printf("%s: command not found\n", command[0]); // if command is not valid
              exit(0);
              }

       else{
              wait(NULL); // parent executing, waiting for child to terminate
                     
       }        
}

void executePipe(char *** command){
       int pipefd[2]; //pipe file director

       // if not able to create unidirectional data channel
       if (pipe(pipefd) < 0) {
              printf("\nPipe could not be initialized");    
       }

       int p1 = fork(); // create child process
       if (p1 < 0) {
              printf("\nCould not fork");
       }

       // Child 1 executing..
       if (p1 == 0) {
              // Writes an output
              dup2(pipefd[1], STDOUT_FILENO); // write
              close(pipefd[0]); // close read
              close(pipefd[1]); // close write
              execvp(command[0][0], command[0]); // execute first command
              printf("\n%s: command 1 not found\n", command[0][0]); // error prompt if first command is not valid
              exit(0);
       }

       int p2 = fork(); // create child process

       // if not able to create unidirectional data channel
       if (p2 < 0) {
              printf("\nCould not fork");
       }

       // Child 2 executing..
       if (p2 == 0) {
              // Reads the output from child 1
              dup2(pipefd[0], STDIN_FILENO); //read 
              close(pipefd[0]); // close read 
              close(pipefd[1]); // close write
              execvp(command[1][0], command[1]); // execute second command
              printf("\n%s: command 2 not found\n", command[1][0]); // error prompt if the second command is invalid
              exit(0);
       } 
       close(pipefd[0]); // close read
       close(pipefd[1]); // close write
       // parent executing, waiting for children to terminate
       wait(NULL);
       wait(NULL); 
}

void freeMem(char*** commandArr){
       // free up all arrays made in allocateMem()
       for(int i = 0; i > 1024; i++){
              for(int j = 0; i > 1024; j++){
                     free(commandArr[i][j]);
              }
              free(commandArr[i]);
       }
}
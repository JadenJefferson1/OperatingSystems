#include <iostream>     
#include <cstring>      
#include <unistd.h>     
#include <sys/wait.h>   
#include <sys/types.h>  


using namespace std;

char strings[20][100];
char *newargv[20];

void read_command(char strings[20][100]){
        cout <<"> ";
        cin.getline(strings[0], 100); 
}

void prep_argv(char strings[20][100], char *newargv[20]){     
        int count = 0;
        char *token = strtok(strings[0], " "); 

        while(token != NULL){
                strcpy(strings[count], token);
                newargv[count] = strings[count];
                count++;
                token = strtok(NULL, " ");
        }
        newargv[count] = NULL;
}

int main()
{
        int status;     
        while(1)
        {   
                read_command(strings);
                prep_argv(strings, newargv);

                if(fork() != 0){
                        // Parent process
                        waitpid(-1, &status, 0);
                }
                // Child process
                else{          
                        // Change directory
                        if(strcmp(newargv[0], "clear") == 0){
                                system("clear");
                        }              

                        else if(strcmp(newargv[0], "ls") == 0){
                                execl("/bin/ls", "ls", newargv[1], NULL);
                        } 
                        else if(strcmp(newargv[0], "pwd") == 0){
                                execl("/bin/pwd", "pwd", NULL);
                        } 
                        
                        else if(strcmp(newargv[0], "ps") == 0){
                                execl("/bin/ps", "ps", newargv[1], NULL);
                        }
                        
                        else if(strcmp(newargv[0], "vi") == 0){
                                execl("/bin/vi", "vi", newargv[1], NULL);
                        }
                        else if(strcmp(newargv[0], "cat") == 0){
                                execl("/bin/cat", "cat", newargv[1], NULL);
                        }
                        else if(strcmp(newargv[0], "rm") == 0){
                                execl("/bin/rm", "rm", newargv[1], NULL);
                        }
                        else if(strcmp(newargv[0], "cd") == 0){
                                if(chdir(newargv[1]) != 0){
                                        perror("chdir");          
                                }                        
                        }
                        else 
                        {      
                                cout<<": Command not found" <<endl;                                
                        }                                  
                }
        }
        return 0;
} 
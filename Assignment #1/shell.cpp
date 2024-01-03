#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;


int main()
{
	/* The command buffer */
	string cmdBuff;
	
	/* The ID of the child process */
	pid_t pid;

	// The return value of execlp
	int execlpRetVal;

	// The return value of wait
	int waitReturn;

	// Stores information about events in the child (e.g., child termination/exit status)
	int childEventInfo;

	
	/* Keep running until the user has typed "exit" */
	do 
	{
		/* Prompt the user to enter the command */
		cerr << "cmd>";
		cin >> cmdBuff;
		
		/* If the user wants to exit */
		if(cmdBuff != "exit")
		{
			/* TODO: Create a child */
			pid = fork();
			/* TODO: Error check to make sure the child was successfully created */
			if(pid < 0){
				perror("fork");
				exit(1);
			}
			/*** TODO: If I am child, I will do this: ****/
			/* Call execlp() to replace my program with that specified at the command line.
			 * PLEASE NOTE: YOU CANNOT PASS cmdBuff DIRECTLY to execlp(). It is because 
			 * cmdBuff is an object of type string (i.e., a class) and execlp() expects
 			 * an array of characters.  However, you can pass cmdBuff.c_str(), which will
			 * return an array of characters representation of the string object.
			 * 
			 * Also, please do not forget to error check your exelp() system calls.
			 */
			
			if(pid == 0){
				execlpRetVal = execlp(cmdBuff.c_str(), NULL);
				// This code is unreachable unless execlp has failed 
				if(execlpRetVal < 0){
					perror("execlp");
					exit(1);
				}
			} else {

			/*** TODO: If I am a parent, I will do the following ***?
			Wait for the child process to terminate */

				waitReturn = wait(&childEventInfo);

				// Sanity checks -- wait failed?
				if(waitReturn < 0)
				{
					perror("wait");
					exit(1);
				}
			}
			
			
		}
	}
	while(cmdBuff != "exit");
	
	return 0;	
}

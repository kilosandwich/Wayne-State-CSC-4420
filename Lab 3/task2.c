//I'm May Wandyez and this is my favorite task2 from lab 3 of CSC 4420 On The Citadel
//haha I need to type stuff to save it I refuse to use the built in nano editor
//let's take a looksie at this code. It looks like the point of this code is to
//1 Generate A Fork
//2 Detect that you have generated a fork
//3 Print out the ID of the name of the parent and child of for the fork.

//one day I will understand what these libraries mean
#include <sys/types.h>
#include<stdio.h>
#include <unistd.h>

//oh wow a global variable. Looks like the point of this is to print it out 
//and to change it within the parent and child differently.
//You would think you could use a different series of variables to demonstrate the 
//same thing. REMEMBER. THE PARENT AND CHILD DO NOT AFFECT EACH OTHER, THE CHILD IS A COPY.
int globalVariable = 2;
int main()
{
	char parentStr[] = "Parent Process";
	char childStr[] = "Child Process";
	char *string = NULL;
	int functionVariable = 20;
	// Create a child process.
	//I know it's called a child, but to me it will always be a forked process
	// REMEMBER, THE FORK OCCURS AT FORK, WHICH IS WHY THE VALUES RETURNED ARE DIFFERENT
	//FOR THE PARENT AND CHILD PROCESS
	pid_t pid = fork();
	if (pid < 0) // Failed to fork NEGATIVE VALUES INDICATE A FAILURE TO FORK
	{
		
		perror("Unable to create child process");
		return 1;
	}
	else if (pid == 0) // child
	{
		// Code only executed by child process
		string = &childStr[0];
		globalVariable++;
		functionVariable++;
	}
	else// parent
	{
		// Code only executed by parent process
		string = &parentStr[0];
		globalVariable += 2;
		functionVariable += 2;
	}
	// Code executed by both parent and child.
	printf("%s\n", string);
	printf(" Global Variable: %d\n",globalVariable);
	printf(" Function Variable: %d\n", functionVariable);

}

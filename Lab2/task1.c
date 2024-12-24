#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
/*


Implement a program to display a file’s contents. When given a single file, it
should be similar to the UNIX cat command. Name your command show. It should
have the following syntax:
$ ./show fileName
The above program displays the contents of the file named fileName.
Each system call must have error checking, and print an error message if
it occurs. You must use open(), read(), write() and close() system calls.
*/

int main(int argc, char *argv[])
{
	int directory;
	char pathname;
	//open the file, make sure to open it in read only mode
	directory = open(argv[1],O_RDONLY);

	//check the number of comment line arguments, if it is not equal to 2,
	//print an error and return 1
	if (argc!=2){
		//I do not understand the structure of this line, but formatting was never
		//my forte
		fprintf(stderr, "Usage: %s directory name\n", argv[1]);
		return 1;
	}
	//if there is no directory argument, print an error.
	if (directory <0)
	{
		perror("Failed to open directory");
		return 1;
	}
	//as long as read returns a positive value, print out the contents of the filepath
	while (read(directory, &pathname,1)){
		if (directory <0)
		{
			perror("Failed reading file");
			return 1;
		}else{
			write(STDOUT_FILENO, &pathname,1);
		}
	}
	//close up thee drectories, we just had to open them.
	while(close(directory) == -1){
		return 0;
	}


}


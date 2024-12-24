#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
/*


Modify the above program to implement a program called body similar to UNIX
commands head or tail. It should print from the mth line to the nth line of the given
file. It should have the following syntax:
$ ./body m n fileName
The above program displays the contents of the file named fileName, from line m to
line n.
Each system call must have error checking, and print an error message if
it occurs. You must use open(), read(), write(), and close() system calls. 10
points each.

*/

int main(int argc, char *argv[])
{
	int directory;
	char pathname;


	//check the number of comment line arguments, if it is not equal to 4,
	//print an error and return 1 ERROR CHECKING SHOULD COME FIRST FOR THIS
	if (argc!=4){
		//I do not understand the structure of this line, but formatting was never
		//my forte
		fprintf(stderr, "Usage: %s m n directory name\n", argv[0]);
		return 1;
	}
	//open the file, make sure to open it in read only mode
	directory = open(argv[3],O_RDONLY);
	int line_we_are_at = 1;
	int m,n;
	//ATOI converts from string to integer
	m = atoi(argv[1]);
	n = atoi(argv[2]);
	
	if (m<0 || n<0){
		perror("M AND N CANNOT BE NEGATIVE!!!!");
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
		if(pathname == '\n'){
			//every time we encounter a new line character, increase
			//yeah I COULD have used ++ but I didn't OK.
			//++ confuses me, I'm not a fan of math happening where I can't see it
			line_we_are_at = line_we_are_at +1;
		}
		if (directory <0)
		{
			perror("Failed reading file");
			return 1;
		}else{
			if (line_we_are_at >=m && line_we_are_at <=n){
				write(STDOUT_FILENO, &pathname,1);
			}
			
		}
	}
	//close up thee drectories, we just had to open them.
	while(close(directory) == -1){
		return 0;
	}


}

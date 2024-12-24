#include <dirent.h>
#include <errno.h>
#include <stdio.h>

//The objective of this lab is to show a system call in Linux
//Personal note: how the heck do we do this in VSC? It would save
// a lot of time to be able to run the extensions that provide
//further information on what the basic functions do.

//This is the main function, for some reason it has been given as empty
//I suspect this is because we are supposed to be using mostly
//structures in C. I never thought I would actually have to use these
//since the way structures was initially presented was just a less
//functional version of 

//argc calculates how many arguments were passed to the program
//argv is an array of strings representing the arguments passed 
//to the program
int main (int argc, char *argv[])
{

	struct dirent *direntp;
		// define a pointer with type directory stream (DIR):
	
		DIR *dir;
		dir = NULL;

		// check the number of arguments (argc). It should be two. If it
		// is not two, then print an error message and exit the program:
		if (argc != 2){
 			fprintf (stderr, "Usage: %s directory name \n", argv[0]);
			return 1;
		}

// The following lines should open the directory given by
// argument argv[1] (by using opendir).
// Store it in your defined directory stream variable.
dir = opendir(argv[1]);

// The rest checks if the system call returned a proper value
// if not an error message is printed and the program closed
if ( dir == NULL)
{
 perror ( "Failed to open directory" );
return 1;
}
// Read all the entries in this directory and store them in
// direntp. readdir will read one entry at a time andincrement
// automatically. This is why it is in a while loop.
// Then, print all the file names (using the struct from readdir).
while ((direntp = readdir(dir))!=NULL)
 printf ("%s \n" , direntp->d_name);
// close the defined directory stream.
while ( ( closedir (dir) == -1) && ( errno == EINTR) );

return 0;
} 

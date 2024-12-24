#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

//This is May Wandyez, gq5426
//It should be noted that I tend to do my programming
//for these files within the text editor in Ubuntu,
//this is purely because I have a severe distrust of terminal
//this is entirely irrational - but I am choosing to stick to it
//note to self, you can access your c functions in terminal using nano
//remember to use CD to change directory
int main (int argc, char *argv[])
{
 // define an instance of struct stat (don’t use a pointer).
struct state structstat;
 // Use the stat function store the status of the file in your stat
// stat takes a pointer, so pass your struct by reference with
& if ( state(argv[1], &structstat == -1)
 {
 // use perror to print error message then exit program
perror("Error, unable to get file);
return 1;
 }
 // print the last access time for the file using defined instance of
// struct stat. ctime requires a pointer, hence the & below.
 printf ("%s last accessed at %s", argv[1], ctime(&structstat.st_atime));
return 0;
} 

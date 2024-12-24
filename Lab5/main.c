//MAY WANDYEZ HOMEWORK 05

#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <semaphore.h> 
#include <stdint.h>
//declare globe var, such as the three matrices and mutex lock
int matrix1[256][256], matrix2[256][256], result[256][256];

//to declare semaphore
sem_t mutex;

//this func is to write a matrix into a file called "output.txt"
//it's already written for you, which means it's not your problem.
int matrixOutput(int matrix[256][256]){
	FILE *fp=fopen("output.txt", "w+");
	if(fp==NULL){
		printf("could not open file!\n");
		exit(-1);
	}
	
	for(int i=0; i<256; i++){
		for(int j=0; j<256; j++){
			fprintf(fp,"%d ", matrix[i][j]);	
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}

//??????????????????????????????????????????????????
//This is the matrix add function
//every single thread you will create will run this after parsing
//off the matrix into equally sized parts. 
//each part is a linear 1 dimensional block, 
//which means that each thread handles size/i pieces
//THE BIGGEST RISK IS WRITING TO THE MATRIX AT THE SAME TIME
void* matrixAdd(void *passMeTheIntBro){		
	//first need to convert i datatype
	int num=(intptr_t)passMeTheIntBro;
	//in hindsight I probably should have made this some kind of variable
	//to be adjusted, but it works so whatever
	int matrixSize = 256;
	int numthreads = 8;
	
	int upperbound = (matrixSize/numthreads)*(num+1);
	int lowerbound = (matrixSize/numthreads)*num;
	
	//you know, I bet the fastest way to deal with this is to
    //do the math first, THEN free the mutex to save it
    for(int i = lowerbound; i<upperbound; i++ ){
        for(int j = 0; j<matrixSize;j++){
            //do the math first to speed up saving the result
            int tempresult = matrix1[i][j] + matrix2[i][j];
            //wait for the mutex to be free, 
            sem_wait(&mutex);
            result[i][j] = tempresult;
            sem_post(&mutex);
        }
    }

	//put a semaphore so only one thread can modify the result matrix at once
    //I put the sempahore up there, I thought it would be more interesting

	//this thread will do addition for rows from num*32 to num*32+31

	printf("Thread %d Done!\n", num);

	pthread_exit(NULL);
}


int main(){
    
	//to initialize semaphore FORGOT TO DO THIS WHOOPS
    sem_init(&mutex,0,1);
    
	//firstly initialize the two matrices
	//both matrix 1 and 2 will be like:
	// 1,2,...,256
	// 1,2,...,256
	// ...
	// 1,2,...,256
	//this bit creates the matrix
	for(int i=0; i<256; i++){
		for(int j=0; j<256; j++){
		    //thinking logically, the value of each column
		    //is equal to the value of the column it is in
		    //and when they are added, it will be as if they were
		    //multiplied by 2
			matrix1[i][j]=j+1;
			matrix2[i][j]=j+1;
			result[i][j]=0;
		}
	}
    
    int matrixSize = 256;
    //??????????????????????????????????????
	//secondly to create the threads and assign jobs for them
	//this bit needs to be filled out
	//OK i cannot count backwards for the life of me
	pthread_t thread[8];	
	for(int i=0; i<8; i++) { 

		//create the thread here
		//create a thread, store the ID in the location of the thread matrix
		pthread_create(&thread[i], NULL, matrixAdd, (void *)(intptr_t)i);
	}
	
    //?????????????????????????????????????????
	//thirdly use pthread join to make sure all threads are done before the main thread
	for(int i=0; i<8; i++) { 
	    //I still can't count backwards
	    //this section joins all the thread ids stored in the thread array
		pthread_join(thread[i], NULL);
	}
	
	//lastly to write the result into output.txt
	matrixOutput(result);
	//destroying the semaphore seems like good practice
	sem_destroy(&mutex);
	
	return 0;
}

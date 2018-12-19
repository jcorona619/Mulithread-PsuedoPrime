/* Josh Corona
 * CS530 Assignment 2
 * Prog2_2.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include "prog2_1.h"

//Function Prototypes
void * generatePrimes(void *);
void * getNextNum();

#define MAX_THREADS 4
pthread_t thread[MAX_THREADS];

//declare and intitialize global variables
mpz_t globalCounter;
pthread_mutex_t counterguard = PTHREAD_MUTEX_INITIALIZER;
TSAFELIST *numberList;

int main(int argc, char *argv[]){
    /*Argument Check*/
    if(argc < 3){
        printf("3 arguments required\n");
        exit(1);
    }

    int i;
    int maxPrimes;  	// K numbers: argv[1]
    int bitLength;  	// B length: argv[2]
    int primes;			// incrementer for primes
    mpz_t one;      	// add 1 to globalCounter to make odd
    TSAFEDATA *data;	// returned data is stored here

    //convert string to integer type
    maxPrimes = atoi(argv[1]);
    bitLength = atoi(argv[2]);
    primes = 0;
    
    //initialize globals, safelist
    numberList = tSafeConstruct();
    mpz_init(globalCounter);
    mpz_ui_pow_ui(globalCounter,2,bitLength-1);

    printf("Assignment #2, Josh Corona, josh.corona@outlook.com\n");

    //Create threads an generate primes
    for(i=0;i<=MAX_THREADS;i++){
        pthread_create(&thread[i],NULL,generatePrimes,NULL);
    }

    //dequeues and checks validity from the list until K primes is reached
    while(1){
        usleep(50);
        if(numberList->head !=NULL){
        	data = tSafeDequeue(numberList);
        	if(data->isValid == 1){
        		primes++;
	        	gmp_printf("%Zd\n",data->value);
	        	if(primes == maxPrimes){
	        		break;
	        	}
        	}
    	}
    }

    //Join threads
    for(i=0;i<=MAX_THREADS;i++){
        pthread_cancel(thread[i]);
    }
    tSafeDestruct(numberList);
}

void * getNextNum(){ 
        mpz_t addOne;
        mpz_init(addOne);
        mpz_set_ui(addOne,1);
        mpz_add(globalCounter,globalCounter,addOne);
	}

void * generatePrimes(void *ptr){
	while(1){
		pthread_mutex_lock(&counterguard);
	    getNextNum();
	    mpz_t check;
	    mpz_init(check);
	    mpz_set(check,globalCounter);
	    pthread_mutex_unlock(&counterguard);
	    if(mpz_probab_prime_p(check,100000)){
	        tSafeEnqueue(numberList,globalCounter);
	    }
	}
}

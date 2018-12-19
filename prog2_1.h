/* Josh Corona
 * CS530 Assignment 2
 * Prog2_2.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <gmp.h>


typedef struct tsafenode {
	mpz_t number;
    struct tsafenode *next;
} TSAFENODE;

typedef struct tsafelist {
    pthread_mutex_t *mutex;
    TSAFENODE *head;
} TSAFELIST;

typedef struct tsafereturndata {
    // True(1)/False(0) if returned data is valid.
    int isValid;
    mpz_t value;
} TSAFEDATA;

TSAFELIST* tSafeConstruct();
void tSafeDestruct(TSAFELIST*);
void tSafeEnqueue(TSAFELIST *,mpz_t);
TSAFEDATA* tSafeDequeue(TSAFELIST *);
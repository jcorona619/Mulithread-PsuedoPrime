/* Josh Corona
 * CS530 Assignment 2
 * Prog2_2.c
 */

#include <stdlib.h>
#include "prog2_1.h"

TSAFELIST* tSafeConstruct(){
	TSAFELIST *list = malloc(sizeof(TSAFELIST));
	list->mutex = malloc(sizeof(*(list->mutex)));
	pthread_mutex_init((list->mutex),NULL);
	list->head = NULL;
	return list;
}

void tSafeDestruct(TSAFELIST* list){
	pthread_mutex_lock(list->mutex);
	TSAFENODE *temp;
	TSAFENODE *curr;
	if(list->head != NULL){
		curr = list->head;
		while(curr->next != NULL){
			temp = curr->next;
			free(curr);
			curr = temp;
		}
		free(curr);
	}
	pthread_mutex_unlock(list->mutex);
	free(list);
}

void tSafeEnqueue(TSAFELIST *list,mpz_t data){
	pthread_mutex_lock(list->mutex);
	TSAFENODE *curr;
	TSAFENODE *newNode = malloc(sizeof(TSAFENODE));
	newNode->next = NULL;
	curr = list->head;
	if(list->head == NULL){
		list->head = newNode;
        mpz_init(newNode->number);
		mpz_set(newNode->number,data);
	}
	else{
        curr = list->head;
		while(curr->next != NULL){
			curr = curr->next;
		}
        curr->next = newNode;
        mpz_init(newNode->number);
        mpz_set(newNode->number,data);
	}
	pthread_mutex_unlock(list->mutex);
}

TSAFEDATA* tSafeDequeue(TSAFELIST *list){
	pthread_mutex_lock(list->mutex);
    TSAFENODE *tempNode;
    TSAFEDATA *tempData = malloc(sizeof(TSAFEDATA));
    if(list->head == NULL){
        tempData->isValid = 0;
    }
    else{
        tempNode = list->head;
        tempData->isValid = 1;
        mpz_init(tempData->value);
        mpz_set(tempData->value,tempNode->number);
        list->head = list->head->next;
        free(tempNode);
    }
    pthread_mutex_unlock(list->mutex);
    return tempData;
}





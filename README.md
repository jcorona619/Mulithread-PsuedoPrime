Author: Josh Corona

This program implements a multithreaded psuedoprime number finder that uses the GMP library.
A thread-safe linked-list is used to shuttle data between threads. A thread-safe number 
generator is used and these numbers are checked to ensure these numbers are prime. Ocassionally, 
these numbers are not actucally prime since mpz_probab_prime_p() returns 0 for non-prime, 1 for 
maybe prime, and 2 for definitely prime. If the numbers checked are definitely prime or maybe 
prime, they are inserted into the list. Once numbers are gathered, they are dequeued from the 
list and printed to STDOUT.

-------------------------------------------------------------------------------------------------
prog2_1.h :
-------------------------------------------------------------------------------------------------	
	This is the header file that defines the structs and functions used for the entire program. 
	It consists of three structs:
		tsafenode:          A node that contains the data and pointer to the next node.
		tsafelist:          A list that contains a head node variable and a mutex for locking.
		tsafereturndata:    Contains a value to check and vaild checker
	It contains four function prototypes:
		tSafeConstruct():                       nitializes the list
		tSafeDestruct(TSAFELIST*):              Destroys the list
		void tSafeEnqueue(TSAFELIST *,mpz_t):   Inserts a new node on the list
		TSAFEDATA* tSafeDequeue(TSAFELIST *):   Removes a node from the list
-------------------------------------------------------------------------------------------------
prog2_1.c:
-------------------------------------------------------------------------------------------------
	This file defines all the functions located in prog2_1.h. The functions are thread-safe so
	when nodes are inserted/removed, only one thread can access variables and perfrom operations 
	at any given time. This is to ensure that multiple threads only access the critical region one
	at a time.
-------------------------------------------------------------------------------------------------
prog2_2.c:
-------------------------------------------------------------------------------------------------
	This is the main function of the program. It prints out a specific amount of prime numbers K 
    and of at least bit length B. It implements 4 threads that all generate prime numbers using 
    functions from the gmp library. Prog2_2.c contains two additional functions:

        generatePrimes(): Continuously calls getNextNum() and checks the number to see if it is
                          prime in a thread-safe manner.
        
        getNextNum(): Gets the next number to be checked by generatePrimes()

    Once K prime members are printed to STDOUT, the threads are closed and the list is destroyed.

    Compilation:

        gcc prog2_2.c prog2_1.c -o main-lgmp -pthread

    Execution:
        
        ./main [K] [B] 
            
            K = The number of primes to print to STDOUT
            B = The smallest bit length for each number


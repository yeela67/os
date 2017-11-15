/*
 * Thread test code.
 */ 
#include <types.h>
#include <lib.h>
#include <thread.h>
#include <synch.h>
#include <test.h>

static struct semaphore *tsem = NULL;

static void init_sem_fun ( void ) 
{
	if ( tsem == NULL )
	{
		tsem = sem_create ( "tsem" , 0 );
		if ( tsem == NULL )
		{
			panic ( "threadtest: sem_create_fun failed\n" );
		}
	}
}

static void have_fun ( void *junk , unsigned long num )
{
	( void ) junk ;

	num = num * 10000 + 6768 ;

	kprintf ( "%lu " , num ) ;

	/*
	 * P is wait = { proberen (to test) }
	 * V is signal =  { verhogen (to increment) }
	 */
	V ( tsem ) ;

}

static void runthreads_fun ( int NTHREADS )
{
	char name [ 16 ];

	int i;
	int result;

	for ( i = 0 ; i < NTHREADS ; i ++ )
	{

		result = thread_fork ( name , NULL , have_fun , i , i );

		if ( result ) 
		{
			panic ( "threadtest: thread_fork failed %s)\n",
					strerror ( result ) );
		}	
	}


	/*
	 * P is wait = { proberen (to test) }
	 * V is signal =  { verhogen (to increment) }
	 */
	for ( i = 0 ; i < NTHREADS ; i ++ )
	{
		P ( tsem );
	}

}

/*
 * @paran nargs is thenumber of arguments
 * @paran args is the vector of arguments
 *		[ the program name counts as the 1st arguement ]
 *
 */
int threadtest_fun ( int nargs , char** args )
{

    int NTHREADS = 10;

    if ( nargs > 1 )
    {
    	int num = atoi ( args [ 1 ] ) ;
    	NTHREADS = num ;
    }

	init_sem_fun ();

	kprintf ( "\n------------------------------" ) ;
	kprintf ( "\nStarting thread test fun ... \n\n" );
	
	runthreads_fun ( NTHREADS );
	
	kprintf ( "\n\nThread test fun done." );
	kprintf ( "\n------------------------------\n\n" ) ;

	return 0;

}


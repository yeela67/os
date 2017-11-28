#include <types.h>
#include <lib.h>
#include <thread.h>
#include <synch.h>
#include <test.h>

static struct semaphore *tsem = NULL;

static int counter = 0 ;

static struct lock *testlock;


/*
 * Methods
 */

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

static void have_fun ( void *junk , unsigned long NINCREMENT )
{
	( void ) junk ;

	for ( int i = 0 ; i < NINCREMENT ; i ++ )
	{
		lock_acquire(testlock);

		counter ++ ;

		lock_release(testlock);
	}

	/*
	 * P is wait = { proberen (to test) }
	 * V is signal =  { verhogen (to increment) }
	 */
	V ( tsem ) ;
}

static void runthreads_fun ( int NTHREADS , int NINCREMENT )
{
	char name [ 16 ];

	int i;
	int result;

	for ( i = 0 ; i < NTHREADS ; i ++ )
	{

		result = thread_fork ( name , NULL , have_fun , NULL , NINCREMENT );
		
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
int lock_thread_counter ( int nargs , char** args )
{

	if ( nargs == 1 )
	{
		return 0 ;
	}

    int NTHREADS = 10;
    int NINCREMENT = 1 ;

    if ( nargs > 1 )
    {
    	int num_threads = atoi ( args [ 1 ] ) ;
    	NTHREADS = num_threads ;
    }

    if ( nargs > 2 )
    {
    	int num_times_each_thread_increment = atoi ( args [ 2 ] ) ;
    	NINCREMENT = num_times_each_thread_increment ;
    }

	init_sem_fun ();

	kprintf ( "\n------------------------------" ) ;
	kprintf ( "\nStarting lock thread counter ... \n\n" );
	
	runthreads_fun ( NTHREADS , NINCREMENT );

	int real_total = NTHREADS * NINCREMENT ;

	kprintf ( "This is the final shared counter variable value: %d" , counter ) ;
	kprintf ( "\nThis is what what it should be: %d" , real_total ) ;
	
	kprintf ( "\n\nlock thread counter done." );
	kprintf ( "\n------------------------------\n\n" ) ;

	return 0;

}

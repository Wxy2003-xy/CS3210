# include <omp.h>
# include <stdio.h>
# include <stdlib.h>
int main (int argc , char * argv [])
{
int num_threads ;
/* Fork worker threads , each with its own unique thread id */
# pragma omp parallel
{
/* Obtain thread id */
int thread_id = omp_get_thread_num ();
printf (" Hello World from thread = %d\n", thread_id );
/* Only master thread executes this .
Master thread always has id equal to 0 */
if ( thread_id == 0)
{
num_threads = omp_get_num_threads ();
printf (" Number of threads = %d\n", num_threads );
}
} /* All worker threads join master thread and are destroyed */
}
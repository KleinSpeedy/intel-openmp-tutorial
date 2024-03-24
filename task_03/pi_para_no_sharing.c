#include <stdio.h>
#include <omp.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int temp_threads, temp_steps = 0;
    // no number specfied, use 4
    if(argc != 2)
    {
        temp_threads = 4;
    }
    else
    {
        temp_threads = atoi(argv[1]);
        if(temp_threads <= 0 || temp_threads > 1000)
        {
            fprintf(stderr, "Error using number threads specified\n");
            return 1;
        }
    }

    const int NUM_THREADS = temp_threads;
    const int STEP_WIDTH = 100000000 / NUM_THREADS;

    double start_time, run_time;
    double pi = 0.0;
    start_time = omp_get_wtime();

    omp_set_num_threads(NUM_THREADS);

    const long num_steps = STEP_WIDTH * NUM_THREADS;
    const double step = 1.0 / (double)num_steps;

    #pragma omp parallel
    {
        const int id = omp_get_thread_num();
        double sum = 0.0;
        double x = 0.0;

        if(id == 0)
        {
            assert(NUM_THREADS == omp_get_num_threads());
        }

        const int start = (id * STEP_WIDTH) + 1;
        const int end = (id+1) * STEP_WIDTH;

        for(int i = start; i < end; i++)
        {
            x = (i-0.5) * step;
            sum += 4.0 / (1.0 + (x*x));
        }

        #pragma omp critical
        {
            pi += (sum * step);
        }
    }

    run_time = omp_get_wtime() - start_time;
    printf("pi with %ld steps and %d threads is %lf in %lf seconds\n",
            num_steps,
            NUM_THREADS,
            pi,
            run_time);
}

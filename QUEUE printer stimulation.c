//28.	An operating system assigns job to print queues based on the number of pages to be printed (1 to 50 pages). You may assume that the system printers are able to print 10 page per minute. Smaller print jobs are printed before larger print jobs and print jobs are processed from a single print queue implemented as a priority queue). The system administrators would like to compare the time required to process a set of print jobs using 1, 2, or 3 system printers. Write a program which simulates processing 100 print jobs of varying lengths using either 1, 2, or 3 printers. Assume that a print request is made every minute and that the number of pages to print varies from 1 to 50 pages. To be fair, you will need to process the same set of print jobs each time you add a printer. The output from your program should indicate the order in which the jobs were received, the order in which they were printed, and the time required to process the set of print jobs. If more than one printer is being used, indicate which printer each job was printed on.
//(Hint: Can implement job queue using suitable queue data structure)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_JOBS 100
#define MIN_PAGES 1
#define MAX_PAGES 50
#define PAGES_PER_MIN 10
#define MAX_PRINTERS 3

typedef struct {
    int job_id;
    int pages;
    int arrival_time;
} Job;

typedef struct {
    Job jobs[NUM_JOBS];
    int size;
} PriorityQueue;

typedef struct {
    int busy_until;
    int printer_id;
} Printer;

void pq_init(PriorityQueue *pq) {
    pq->size = 0;
}

void pq_push(PriorityQueue *pq, Job job) {
    int i = pq->size++;
    while (i > 0 && pq->jobs[i-1].pages > job.pages) {
        pq->jobs[i] = pq->jobs[i-1];
        i--;
    }
    pq->jobs[i] = job;
}

Job pq_pop(PriorityQueue *pq) {
    return pq->jobs[--pq->size];
}

int pq_empty(PriorityQueue *pq) {
    return pq->size == 0;
}

void generate_jobs(Job jobs[NUM_JOBS], unsigned int seed) {
    srand(seed);
    for (int i = 0; i < NUM_JOBS; i++) {
        jobs[i].job_id = i+1;
        jobs[i].pages = (rand() % (MAX_PAGES - MIN_PAGES + 1)) + MIN_PAGES;
        jobs[i].arrival_time = i; // one job per minute
    }
}

void simulate(Job jobs[NUM_JOBS], int num_printers) {
    PriorityQueue pq;
    pq_init(&pq);
    Printer printers[MAX_PRINTERS] = {0};
    int printed_order[NUM_JOBS];
    int printed_on[NUM_JOBS];
    int print_start[NUM_JOBS];
    int print_end[NUM_JOBS];
    int jobs_processed = 0, next_job = 0, time = 0;

    for (int i = 0; i < num_printers; i++) {
        printers[i].busy_until = 0;
        printers[i].printer_id = i+1;
    }

    printf("\n--- Simulation with %d printer(s) ---\n", num_printers);
    printf("Job Arrival Order:\n");
    for (int i = 0; i < NUM_JOBS; i++)
        printf("Job %d: %d pages (arrived at %d)\n", jobs[i].job_id, jobs[i].pages, jobs[i].arrival_time);

    while (jobs_processed < NUM_JOBS) {
        // Add jobs that arrive at this minute
        while (next_job < NUM_JOBS && jobs[next_job].arrival_time <= time) {
            pq_push(&pq, jobs[next_job]);
            next_job++;
        }
        // Assign jobs to free printers
        for (int p = 0; p < num_printers; p++) {
            if (printers[p].busy_until <= time && !pq_empty(&pq)) {
                Job job = pq_pop(&pq);
                int duration = (job.pages + PAGES_PER_MIN - 1) / PAGES_PER_MIN;
                printers[p].busy_until = time + duration;
                printed_order[jobs_processed] = job.job_id;
                printed_on[jobs_processed] = printers[p].printer_id;
                print_start[jobs_processed] = time;
                print_end[jobs_processed] = printers[p].busy_until;
                jobs_processed++;
            }
        }
        time++;
    }

    printf("\nPrint Order:\n");
    for (int i = 0; i < NUM_JOBS; i++) {
        printf("Job %d printed on Printer %d (start: %d, end: %d)\n",
            printed_order[i], printed_on[i], print_start[i], print_end[i]);
    }
    printf("\nTotal time to process all jobs: %d minutes\n", time-1);
}

int main() {
    Job jobs[NUM_JOBS];
    unsigned int seed = (unsigned int)time(NULL);
    generate_jobs(jobs, seed);

    for (int printers = 1; printers <= MAX_PRINTERS; printers++) {
        simulate(jobs, printers);
    }
    return 0;
}

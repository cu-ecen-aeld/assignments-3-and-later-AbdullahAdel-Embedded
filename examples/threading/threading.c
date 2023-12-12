#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    
   struct thread_data* thread_func_args = (struct thread_data*)thread_param;

    // Wait to obtain the mutex
    usleep(thread_func_args->wait_to_obtain_ms * 1000);  // Convert to microseconds

    pthread_mutex_lock(thread_func_args->mutex);

    // Perform operations that require the mutex

    // Simulate some work
    usleep(thread_func_args->wait_to_release_ms * 1000);  // Convert to microseconds

    // Release the mutex
    pthread_mutex_unlock(thread_func_args->mutex);

    // Set the completion status to true
    thread_func_args->thread_complete_success = true;

    return thread_param;  // Returning the thread data structure

    // Note: It's important that the thread data structure is dynamically allocated so that it survives
    // beyond the scope of this function. The main function or another part of the program should
    // eventually free this memory.
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
    //return false;
    struct thread_data* thread_args = malloc(sizeof(struct thread_data));

    if (thread_args == NULL) {
        perror("Error allocating memory for thread arguments");
        return false;
    }

    thread_args->mutex = mutex;
    thread_args->wait_to_obtain_ms = wait_to_obtain_ms;
    thread_args->wait_to_release_ms = wait_to_release_ms;
    thread_args->thread_complete_success = false;

    // Create the thread and pass thread_args as a parameter
    if (pthread_create(thread, NULL, threadfunc, (void*)thread_args) != 0) {
        perror("Error creating thread");
        free(thread_args);
        return false;
    }

    return true;
}


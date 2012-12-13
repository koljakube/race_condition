#include <sched.h>

#include "race_condition.h"

void* thread_worker(void* count_max_p) {
  counter_t count_max = (counter_t)count_max_p;
  counter_t next_free_slot;
  
  while (count_max > 0) {
    next_free_slot = in;
    next_free_slot += 1;
#ifdef DO_YIELD
    sched_yield();
#endif
    in = next_free_slot;
    count_max -= 1;
  }

  pthread_exit(NULL);
}

int create_threads(pthread_t* threads, size_t thread_count, counter_t count_max) {
  size_t index;
  for (index = 0; index < thread_count; index++) {
    int err = pthread_create(&threads[index], NULL, thread_worker, (void*)count_max);
    if (err != 0) {
      return err;
    }
  }
  return 0;
}

void join_threads(pthread_t* threads, size_t thread_count) {
  size_t index;
  for (index = 0; index < thread_count; index++) {
    pthread_join(threads[index], NULL);
  }
}

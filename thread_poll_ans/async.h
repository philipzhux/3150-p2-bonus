#ifndef __ASYNC__
#define __ASYNC__

#include <pthread.h>



typedef void (*handler_t)(int);

typedef struct my_item {
  int args;
  handler_t handler;
  struct my_item *next;
  struct my_item *prev;
} my_item_t;

typedef struct my_queue {
  int size;
  my_item_t *head;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  /* TODO: More stuff here, maybe? */
} my_queue_t;

void wq_init(my_queue_t *wq);
void wq_push(my_queue_t *wq, handler_t handler, int args);
void wq_pop(my_queue_t *wq, void (**hanlder)(int),int* arg);
void async_init(int);
void async_run(void (*fx)(int), int args);
void* async_handler(void *stub);


#endif

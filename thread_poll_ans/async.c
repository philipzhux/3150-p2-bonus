
#include <stdlib.h>
#include <pthread.h>
#include "async.h"
#include "utlist.h"
my_queue_t wq;

void async_init(int num_threads) {
    /** create num_threads threads and initialize the thread pool **/
    
    wq_init(&wq);
    for(int i=0;i<num_threads;i++){
    pthread_t temp;
    pthread_create(&temp,NULL,async_handler,(void*)&wq);
    pthread_detach(temp);
  }
    return;
}

void async_run(void (*handler)(int), int args) {
    // hanlder(args);
    /** ewrite it to support thread pool **/
    wq_push(&wq,handler,args);
}

void* async_handler(void *stub) {
    my_queue_t* wq = (my_queue_t*)stub;
    pthread_detach(pthread_self());
    while(1) {
        handler_t handler;
        int arg;
        wq_pop(wq,&handler,&arg);
        handler(arg);
    }
    return NULL;
}


/* Initializes a work queue WQ. */
void wq_init(my_queue_t *wq) {

    wq->size = 0;
    wq->head = NULL;
    pthread_mutex_init ( &wq->mutex, NULL);
    pthread_cond_init(&wq->cond,NULL);
}

/* Remove an item from the WQ. This function should block until there
 * is at least one item on the queue. */

void wq_pop(my_queue_t *wq, handler_t* hanlder,int* arg) {
    pthread_mutex_lock(&wq->mutex);
    while(!wq->size) pthread_cond_wait(&wq->cond, &wq->mutex);
    my_item_t *my_item = wq->head;
    wq->size--;
    DL_DELETE(wq->head, wq->head);
    *arg = my_item->args;
    *hanlder = my_item->handler;
    free(my_item);
    pthread_mutex_unlock(&wq->mutex);
}

/* Add ITEM to WQ. */
void wq_push(my_queue_t *wq, handler_t handler, int args) {

    my_item_t *my_item = calloc(1, sizeof(my_item_t));
    my_item->handler = handler;
    my_item->args = args;
    pthread_mutex_lock(&wq->mutex);
    DL_APPEND(wq->head, my_item);
    wq->size++;
    pthread_cond_signal(&wq->cond);
    pthread_mutex_unlock(&wq->mutex);
}
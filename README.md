# THEAD POLL

## Task
* Implement in async.c and async.h: ```void async_init(int num_threads)``` and ```void async_run(void (*handler)(int), int args)```
* You can use list data structure in utlist.h, for example: ```DL_APPEND(my_queue->head, my_item);```(adding to queue end) and  ```DL_DELETE(my_queue->head, my_queue->head);```(popping from queue head)
* When no jobs are coming, your threads created in ```async_init``` have to go to sleep and is not allowed to do busying waiting like ```while(1){sleep(any);}```, and when jobs are coming the thread in your thread poll **must** wake up immediately (that is, no ```sleep()``` call is allowed).

## Test
* ./httpserver --proxy inst.eecs.berkeley.edu:80 --port 8000 --num-threads 5
* Once you create num-threads of threads in ```async_init``` to initialize your program, you are not allowed to create any more thread in ```async_run```, otherwise zero score will be granted.

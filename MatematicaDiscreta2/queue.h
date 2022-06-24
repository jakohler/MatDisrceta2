#ifndef _QUEUE
#define _QUEUE

#include <stdint.h>

typedef uint32_t u32;

typedef struct _node{
  u32 index;
  struct _node *next;
}* node;

struct _queue{
  node first;
  node last;
  u32 length;
};

typedef struct _queue *queue;

/*instantiate an empty queue*/
queue queue_init();
/*destroy a queue*/
queue queue_destroy(queue q);
/*add element to a queue*/
queue queue_add(u32 i, queue q);
/*pops first element from queue*/
void queue_remove(queue q);
/*returns index of first element*/
u32 queue_get_index(queue q);
/*self explanatory*/
u32 queue_length(queue q);
#endif

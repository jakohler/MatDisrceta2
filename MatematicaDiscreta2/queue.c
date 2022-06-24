#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

// Retorna el puntero a queue si todo sale bien.
// Si el alloc sale mal, devuelve NULL.
queue queue_init(){
    queue q = calloc(1,sizeof(struct _queue));
    if (q != NULL){
        q->first = NULL;
        q->last = NULL;
        q->length = 0;
    }

    return q;
}

queue queue_destroy(queue q){
    if (q != NULL){
        node to_free = q->first;
        node next_node;

        while (to_free != NULL){
            next_node = to_free->next;
            free(to_free);
            to_free = next_node;
        }

        free(q);
    }
    return NULL;
}

queue queue_add(u32 index, queue q){
    node n = calloc(1,sizeof(struct _node));
    if (n != NULL){
        n->index = index;
        n->next = NULL;

        if (q->length == 0){
            q->first = n;
        } else {
            q->last->next = n;
        }

        q->last = n;
        q->length ++;

        return q;
    } else {
        queue_destroy(q);
        return NULL;
    }
}

u32 queue_get_index(queue q){
    return q->first->index;
}

void queue_remove(queue q){
    node n = q->first;

    q->first = q->first->next;
    if (q->length == 1){
        q->last = NULL;
    }
    q->length --;

    free(n);
}

u32 queue_length(queue q){
    return q->length;
}

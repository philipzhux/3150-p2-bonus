#include "liblist.h"

void insert(struct fd_pair* head, struct fd_pair* p) {
    assert(head!=NULL);
    static struct fd_pair* tail = NULL;

    if(tail == NULL) {
        while(head->next!=NULL) head = head->next;
        tail = head;
    }
    tail->next = p;
    p->next = NULL;
}

void delete(struct fd_pair* head, int fd) {
    assert(head!=NULL);
    struct fd_pair* p = head->next;

    while(p!=NULL) {
        if(p->fd == fd) break;
        head = p;
        p = p->next;
    }
    if(p!=NULL) {
        head = p->next;
        free(p);
    }
}



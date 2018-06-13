#ifndef CWREVISE_LINKEDLIST_H
#define CWREVISE_LINKEDLIST_H

#include <stddef.h>

template <class T>
class LinkedList {
public:
    LinkedList();
    LinkedList(T* a, size_t size);
    LinkedList(const LinkedList& other);
    LinkedList(LinkedList&& other);
    virtual ~LinkedList();
private:
    struct Node{
        T payload;
        Node* next;
    };
};


#endif //CWREVISE_LINKEDLIST_H

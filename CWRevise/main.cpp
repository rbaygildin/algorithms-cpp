#include <iostream>
#include <algorithm>
#include "FixedArr.h"
using namespace std;

template <class T>
struct Node{
    Node(T payload, Node<T> *next){
        this->payload = payload;
        this->next = next;
    }
    T payload;
    Node<T> *next;
};

template <class T>
Node<T> reverse(Node<T>*);

int main() {
    Node<int> head(1, nullptr);
    Node<int> *prev = &head;
    for(int i = 2; i <= 10; i++){
        Node<int> *temp = new Node<int>(i, nullptr);
        prev->next = temp;
        prev = temp;
    }
    Node<int> temp = head;
    int i = 0;
    while(temp.next != nullptr){
        cout << ++i << ": " << temp.payload << endl;
        temp = *temp.next;
    }
    temp = reverse(&head);
    i = 0;
    do{
        cout << ++i << ": " << temp.payload << endl;
        temp = *temp.next;
    }while(temp.next != nullptr);
    return 0;
}

template <class T>
Node<T> reverse(Node<T> *head){
    Node<T> *prev = head;
    Node<T> *pos = head->next;
    while(pos != nullptr){
        Node<T> *next = pos->next;
        pos->next = prev;
        prev = pos;
        pos = next;
    }
    head->next = nullptr;
    return *prev;
}

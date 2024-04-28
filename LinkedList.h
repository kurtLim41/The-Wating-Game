#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

template <class T>
class ListNode{
    public:
        ListNode();
        ListNode(T k);
        ~ListNode();
        T key;
        ListNode<T> *next;
        ListNode<T> *prev;
};

template <class T>
ListNode<T>::ListNode(){
    key = nullptr;
    next = nullptr;
    prev = nullptr;
}

template <class T>
ListNode<T>::ListNode(T k){
    key = k;
    next = nullptr;
    prev = nullptr;
}

template <class T>
ListNode<T>::~ListNode(){
    //doesnt need anything here b/c we arent allocating any dynamic memeory 
}

template <class T>
class LinkedList{
    public:
        LinkedList();
        ~LinkedList();
        void insertBack(T d);
        T removeFront();
        T removeBack();
        bool isEmpty();
        unsigned int getSize();
        T peek();
        void printList();  //helper functions 
        
    private:
        ListNode<T> *front;
        ListNode<T> *back;
        unsigned int size;
};

template <class T>
LinkedList<T>::LinkedList(){
    front = nullptr;
    back = nullptr;
    size = 0;
}

template <class T>
LinkedList<T>::~LinkedList(){
    ListNode<T> *current = front;
	while (current != nullptr)
	{
		ListNode<T> *nextNode = current->next;
		delete current;
        current = nextNode;
	}
}


template <class T>
void LinkedList<T>::insertBack(T d){
    ListNode<T> *node = new ListNode<T>(d);

    if(isEmpty()){
        front = node;
    }
    else{
        back->next = node;
        node->prev = back;
    }
    back = node;
    ++size;
}

template <class T>
bool LinkedList<T>::isEmpty(){
    return (size ==0);
}

template <class T>
unsigned int LinkedList<T>::getSize(){
    return size;
}

template <class T>
T LinkedList<T>::removeFront(){
    if(isEmpty()){
        cerr << "list is empty" << endl;
    }

    ListNode<T> *temp  = front;
    
    if (front->next == NULL){
        //one node in the list
        back = NULL;
    }
    else{
        //more then one node in the list 
        front->next->prev = NULL;
    }
    front = front->next;
    temp->next = NULL;
    T data = temp->key;
    --size;

    delete temp;
    return data;
}







template <class T>
T LinkedList<T>::peek(){
    return front->key;
}

template <class T>
void LinkedList<T>::printList(){
    ListNode<T> *curr = front;
    while(curr != NULL){
        cout << curr->key << ",";
        curr = curr->next;
    }
    cout << "\n";
}


#endif
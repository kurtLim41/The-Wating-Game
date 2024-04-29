#ifndef LISTQUEUE_H
#define LISTQUEUE_H
#include <iostream>
#include <exception>
#include "LinkedList.h"

using namespace std;

//linked list based queue 

template <class T>
class ListQueue{
    public:
        ListQueue(); //default constructor
        ~ListQueue();

        //core functions 
        void insert(T *d);  //aka enqueue()
        T* remove(); //dequeue
       

        //aux/helper functions 
        T* peek(); //whp is at the front of the queue
        bool isEmpty();
        unsigned int getSize(); //unsigned-> cant be less then 0
        void printQueue(); //helper function to visualize array base queue 

    private:
        LinkedList<T> *myQueue;
        

};

template <class T>
ListQueue<T>::ListQueue(){
    myQueue = new LinkedList<T>;
}

template <class T>
ListQueue<T>::~ListQueue(){
    delete myQueue;
}

template <class T>
void ListQueue<T>::insert(T *d){
    myQueue->insertBack(d);
}

// //for using a priority queue
// void ListQueue::enqueue(char d){
//     if(isFull()){
//         throw runtime_error("Priority Queue is full");
//     }
//     int i = numElements-1;
//     while(i >= 0 && d < myQueue[i]){
//         myQueue[i+1] = myQueue[i];
//         i--;
//     }
//     myQueue[i+1] = d;
//     numElements++;
// }

template <class T>
T* ListQueue<T>::remove(){
    return myQueue->removeFront();
    
}

template <class T>
T* ListQueue<T>::peek(){ 
    return myQueue->peek();
}

template <class T>
bool ListQueue<T>::isEmpty(){
    return myQueue->isEmpty();
}

template <class T>
unsigned int ListQueue<T>::getSize(){
    return myQueue->getSize();
}

template <class T>
void ListQueue<T>::printQueue(){
    myQueue->printList();
}
#endif
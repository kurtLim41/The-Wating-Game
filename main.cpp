#include "LinkedList.h"
#include "ListQueue.h"
#include "ServiceCenter.h"

int main(){
    LinkedList<int> *test = new LinkedList<int>;

    test->insertBack(4);
    test->insertBack(3);
    test->insertBack(2);
    test->insertBack(1);
    test->printList();

    ListQueue<char> *a = new ListQueue<char>;
    a->insert('b');
    a->insert('c');
    a->insert('d');
    a->insert('e');

    a->printQueue();

    ServiceCenter chapman("input.txt");


}
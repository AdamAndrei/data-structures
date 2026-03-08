#include "linked-lists/demos/SimpleLinkedListDemo.h"
#include "linked-lists/simple-linked-list/SinglyLinkedList.h"
#include "linked-lists/simple-linked-list/DoublyLinkedList.h"
#include "linked-lists/simple-linked-list/OrderedLinkedList.h"
#include "linked-lists/simple-linked-list/CircularLinkedList.h"
#include <iostream>
#include <functional>

void demoSinglyLinkedList()
{
    SinglyLinkedList<int> singlyLinkedList;

    std::cout << "SinglyLinkedList demo" << std::endl;

    singlyLinkedList.insertFront(1);
    singlyLinkedList.insertFront(2);
    singlyLinkedList.insertFront(3);
    std::cout << singlyLinkedList << std::endl;

    singlyLinkedList.insertBack(4);
    singlyLinkedList.insertBack(5);
    std::cout << singlyLinkedList << std::endl;

    singlyLinkedList.insertAfter(99, 2);
    singlyLinkedList.insertBefore(999, 5);
    std::cout << singlyLinkedList << std::endl;

    singlyLinkedList.removeBack();
    singlyLinkedList.removeFront();
    singlyLinkedList.remove(999);
    std::cout << singlyLinkedList << std::endl;

    singlyLinkedList.update(99, 1999);
    std::cout << singlyLinkedList << std::endl;
}

void demoDoublyLinkedList()
{
    DoublyLinkedList<int> doublyLinkedList;

    std::cout << "DoublyLinkedList demo" << std::endl;

    doublyLinkedList.insertFront(1);
    doublyLinkedList.insertFront(2);
    doublyLinkedList.insertFront(3);
    std::cout << doublyLinkedList << std::endl;

    doublyLinkedList.insertBack(4);
    doublyLinkedList.insertBack(5);
    std::cout << doublyLinkedList << std::endl;

    doublyLinkedList.insertAfter(99, 2);
    doublyLinkedList.insertBefore(999, 5);
    std::cout << doublyLinkedList << std::endl;

    doublyLinkedList.removeBack();
    doublyLinkedList.removeFront();
    doublyLinkedList.remove(999);
    std::cout << doublyLinkedList << std::endl;

    doublyLinkedList.update(99, 1999);
    std::cout << doublyLinkedList << std::endl;
}

void demoOrderedLinkedList()
{
    OrderedLinkedList<int> orderedLinkedList;

    std::cout << "OrderedLinkedList demo (default comparator)" << std::endl;

    orderedLinkedList.insert(2);
    orderedLinkedList.insert(1);
    orderedLinkedList.insert(3);
    std::cout << orderedLinkedList << std::endl;

    orderedLinkedList.insert(5);
    orderedLinkedList.insert(4);
    std::cout << orderedLinkedList << std::endl;

    orderedLinkedList.removeBack();
    orderedLinkedList.removeFront();
    orderedLinkedList.remove(4);
    std::cout << orderedLinkedList << std::endl;

    orderedLinkedList.insert(100);
    orderedLinkedList.insert(50);
    std::cout << orderedLinkedList << std::endl;

    orderedLinkedList.update(50, 0);
    std::cout << orderedLinkedList << std::endl;

    OrderedLinkedList<int, std::greater<int>> orderedLinkedListCmp;

    std::cout << "OrderedLinkedList demo (custom comparator)" << std::endl;

    orderedLinkedListCmp.insert(2);
    orderedLinkedListCmp.insert(1);
    orderedLinkedListCmp.insert(3);
    std::cout << orderedLinkedListCmp << std::endl;

    orderedLinkedListCmp.insert(5);
    orderedLinkedListCmp.insert(4);
    std::cout << orderedLinkedListCmp << std::endl;

    orderedLinkedListCmp.removeBack();
    orderedLinkedListCmp.removeFront();
    orderedLinkedListCmp.remove(4);
    std::cout << orderedLinkedListCmp << std::endl;

    orderedLinkedListCmp.insert(100);
    orderedLinkedListCmp.insert(50);
    std::cout << orderedLinkedListCmp << std::endl;

    orderedLinkedListCmp.update(50, 0);
    std::cout << orderedLinkedListCmp << std::endl;
}

void demoCircularLinkedList()
{
    CircularLinkedList<int> circularLinkedList;

    std::cout << "CircularLinkedList demo" << std::endl;

    circularLinkedList.insertFront(1);
    circularLinkedList.insertFront(2);
    circularLinkedList.insertFront(3);
    std::cout << circularLinkedList << std::endl;

    circularLinkedList.insertBack(4);
    circularLinkedList.insertBack(5);
    std::cout << circularLinkedList << std::endl;

    circularLinkedList.insertAfter(99, 2);
    circularLinkedList.insertBefore(999, 5);
    std::cout << circularLinkedList << std::endl;

    circularLinkedList.removeBack();
    circularLinkedList.removeFront();
    circularLinkedList.remove(999);
    std::cout << circularLinkedList << std::endl;

    circularLinkedList.update(99, 1999);
    std::cout << circularLinkedList << std::endl;

    std::cout << "Josephus problem (step 2):" <<std::endl;
    circularLinkedList.josephus(2);
}

void demoSimpleLinkedList()
{
    demoSinglyLinkedList();
    demoDoublyLinkedList();
    demoOrderedLinkedList();
    demoCircularLinkedList();
}
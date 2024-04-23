//
//  Stack.cpp
//  sonhal
//
//  Created by Selin İmren on 10.11.2023.
//

#include "Stack.h"
#include <iostream>
#include <fstream>
using namespace std;


template <class Object>
Stack<Object>::Stack() {
    topOfStack = NULL;
}

template<class Object>
bool Stack<Object>::isFull() const {
    return false;
}

template<class Object>
bool Stack<Object>::isEmpty() const {
    return topOfStack == NULL;
}

template<class Object>
const Object &Stack<Object>::top() const {
    // if ( isEmpty( ) )
    // throw Underflow( );
    return topOfStack->element;
}

template<class Object>
void Stack<Object>::pop() {
    //if ( isEmpty( ) )
    // throw Underflow( );
    ListNode *oldTop = topOfStack;
    topOfStack = topOfStack->next;
    delete oldTop;
}

template<class Object>
void Stack<Object>::push(const Object &x) {
    topOfStack = new ListNode(x, topOfStack);
}

template<class Object>
Object Stack<Object>::topAndPop() {
    Object topItem = top();
    pop();
    return topItem;
}

template<class Object>
void Stack<Object>::makeEmpty() {
    while (!isEmpty())
        pop();
}

template<class Object>
const Stack<Object> &Stack<Object>::
operator=(const Stack<Object> &rhs) {
    if (this != &rhs) {
        makeEmpty();
        if (rhs.isEmpty())
            return *this;

        ListNode *rptr = rhs.topOfStack;
        ListNode *ptr = new ListNode(rptr->element);
        topOfStack = ptr;

        for (rptr = rptr->next; rptr != NULL; rptr = rptr->next)
            ptr = ptr->next = new ListNode(rptr->element);
    }
    return *this;
}

template<class Object>
Stack<Object>::Stack(const Stack<Object> &rhs) {
    topOfStack = NULL;
    *this = rhs; // deep copy
}

template<class Object>
Stack<Object>::~Stack() {
    makeEmpty();
}
template<class Object>
void Stack<Object>::display() const {
        ListNode* current = topOfStack;
        while(current!= nullptr){
           cout << "x: " << current->element.x << ", y: " << current->element.y
            << ", l: " << current->element.l << ", r: " << current->element.r
            << ", u: " << current->element.u << ", d: " << current->element.d
            << ", visited: " << current->element.visited << std::endl;
            current=current->next;
        }
      }
    



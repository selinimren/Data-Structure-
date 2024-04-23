//
//  Stack.h
//  cs300_homework1
//
//  Created by Selin İmren on 6.11.2023.
//

#ifndef Stack_h
#define Stack_h



#include <iostream>

template <class Object>
class Stack
{
public:
    Stack( );
    Stack( const Stack & rhs );
    ~Stack();

    bool isEmpty() const;
    bool isFull() const;
    void makeEmpty();

    void pop();
    void push( const Object&x );
    Object topAndPop();
    const Object & top( ) const;

    const Stack & operator=(const Stack & rhs);
    void  display() const;
private:
    struct ListNode
    {
        Object element;
        ListNode *next;

        ListNode( const Object & theElement, ListNode * n = NULL )
                : element( theElement ), next( n ) { }
    };

    ListNode *topOfStack;  // list itself is the stack
};
#endif


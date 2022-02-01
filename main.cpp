//
//  main.cpp
//  TestCPP
//
//  Created by Đỗ Hữu Phúc on 8/29/19.
//  Copyright © 2019 Phuc Do. All rights reserved.
//

#include <iostream>
using namespace std;

// Node
class Node {
public:
    int data;
    Node *next;
    
public:
    Node() {
        this->next = NULL;
    }
    Node(int data) {
        this->data = data;
        this->next = NULL;
    }
};

//List
class LinkedList {
    Node *head;
    int count;
public:
    LinkedList();
    ~LinkedList();
    int InsertNode(Node *pPre, int data);
    int DeleteNode(Node *pPre, Node *pLoc);
    void DeleteNodeAt(int index);
    Node* SearchNode(int value);
    void Traverse();
    void Clear();
    void Reverse();
};

LinkedList::LinkedList() {
    this->head = NULL;
    this->count = 0;
};


//Insert
int LinkedList::InsertNode(Node *pPre, int data) {
    Node *pNew = new Node(data);
    if (pNew == NULL) {
        return 0;
    }
    if (pPre == NULL) {
        pNew->next = this->head;
        this->head = pNew;
    } else {
        pNew->next = pPre->next;
        pPre->next = pNew;
    }
    this->count++;
    return 1;
}

//Delete
int LinkedList::DeleteNode(Node *pPre, Node *pLoc) {
    if (pPre == NULL) {
        this->head = pLoc->next;
    } else {
        pPre->next = pLoc->next;
    }
    this->count--;
    delete pLoc;
    return 1;
}

void LinkedList::DeleteNodeAt(int index) {
    if (index < 0 || index > this->count - 1) {
        cout << "Errr delete" <<endl;
        return;
    }
    Node *pPre = NULL;
    Node *pCur = this->head;
    if (index == 0){
        this->head = this->head->next;
    } else {
        for (int i = 0; i < index; i++) {
            pPre = pCur;
            pCur = pCur->next;
        }
        pPre->next = pCur->next;
    }
    delete pCur;
    this->count--;
}

//Search
Node* LinkedList::SearchNode(int value) {
    Node *pPre = NULL;
    Node *pLoc = this->head;
    while (pLoc != NULL && pLoc->data != value) {
        pPre = pLoc;
        pLoc = pLoc->next;
    }
    return pLoc;
}

//Traverse
void LinkedList::Traverse() {
    cout << "\nLinkedlist data: " << endl;
    Node *p = this->head;
    while (p != NULL) {
        cout << p->data << " " ;
        p = p->next;
    }
}

//

void LinkedList::Reverse() {
    Node *pPre = NULL, *pNext = NULL;
    Node *pCur = this->head;
    
    while(pCur != NULL) {
        pNext = pCur->next;
        pCur->next = pPre;
        pPre = pCur;
        pCur = pNext;
    }
    
    this->head = pPre;
}
// Clear
void LinkedList::Clear() {
    Node *temp;
    while (this->head != NULL) {
        temp = this->head;
        this->head = this->head->next;
        delete temp;
    }
    this->count = 0;
    return;
}


LinkedList::~LinkedList() {
    this->Clear();
}

void testLinkedList() {
    LinkedList *list = new LinkedList();
    list->InsertNode(NULL, 5);
    list->InsertNode(NULL, 10);
    list->InsertNode(NULL, 15);
    list->Traverse();
    Node *node = list->SearchNode(10);
    list->InsertNode(node, 6);
    list->Traverse();
    
    list->Reverse();
    list->Traverse();
    
    list->DeleteNodeAt(2);
    list->Traverse();
    list->DeleteNodeAt(1);
    list->Traverse();
    list->DeleteNodeAt(1);
    list->DeleteNodeAt(0);
    list->DeleteNodeAt(0);
    list->Traverse();
}


// Stack

class Stack {
    int count;
    Node *top;
public:
    Stack();
    ~Stack();
    void Push(int data);
    int Pop();
    int GetTop();
    void Clear();
    bool IsEmpty();
    int GetSize();
    void PrintStack();
};

Stack::Stack() {
    this->count = 0;
    this->top = NULL;
};

Stack::~Stack(){
    this->Clear();
}

void Stack::Push(int data){
    Node *pNew = new Node(data);
    pNew->next = this->top;
    this->top = pNew;
    this->count++;
}

int Stack::Pop() {
    if (this->GetSize() == 0) {
        return 0;
    }
    Node *temp = this->top;
    int value = temp->data;
    this->top = this->top->next;
    delete temp;
    this->count--;
    return value;
}

int Stack::GetTop() {
    if(this->GetSize() == 0) {
        return 0 ; // mặc định 0 thì không lấy được
    }
    int data = this->top->data;
    return data;
}

void Stack::Clear() {
    Node *pTemp;
    while(this->top != NULL) {
        pTemp = this->top;
        this->top = this->top->next;
        delete pTemp;
    }
    this->count = 0;
}

bool Stack::IsEmpty() {
    return this->count == 0;
}

int Stack::GetSize() {
    return this->count;
}

void Stack::PrintStack() {
    cout << "Stack data top -> bottom: " << endl;
    Node *temp = this->top;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void testStack() {
    Stack *stack = new Stack();
    stack->Push(5);
    stack->Push(7);
    stack->Push(6);
    
    stack->PrintStack();
    stack->Clear();
}

//Stack with array
class ArrayStack {
    int top;
    int capacity;
    int *storage;
public:
    ArrayStack(int capacity) {
        this->capacity = capacity;
        storage = new int[capacity];
        top = -1;
    }
    ~ArrayStack() {
        delete [] storage;
    }
    int Pop();
    void Push(int data);
    int Top();
    bool IsFull();
    bool IsEmpty();
    int GetSize();
    void PrintStack();
};

void ArrayStack::Push(int data) {
    if (this->IsFull()){
        cout << "Stack is Full" <<endl;
        return;
    }
    this->top++;
    storage[top] = data;
}

int ArrayStack::Pop() {
    if (this->top == -1) {
        cout << "Stack is Empty" << endl;
        return -1; // default -1 is empty
    }
    int value = storage[top];
    this->top--;
    return value;
}

int ArrayStack::Top() {
    if (this->top == -1) {
        cout << "Stack is Empty" << endl;
        return -1; // default em
    }
    return storage[top];
}

bool ArrayStack::IsFull() {
    return top == capacity - 1;
}

int ArrayStack::GetSize() {
    return top + 1;
}

void ArrayStack::PrintStack(){
    if (top > -1) {
        cout<< "Data is: " << endl;
        for (int i = top; i > -1; i--) {
            cout << storage[i] << endl;
        }
    }
}

void testArrayStack(){
    ArrayStack *stack = new ArrayStack(10);
    stack->Push(5);
    stack->Push(7);
    stack->Push(10);
    stack->PrintStack();
    int value = stack->Pop();
    cout << "data get is: " << value << endl;
    stack->Push(20);
    cout << "size is: " << stack->GetSize() << endl;
    stack->PrintStack();
    delete stack;
    return;
}

//Queue

class Queue {
private:
    int count;
    Node *front;
    Node *rear;
public:
    Queue();
    ~Queue();
    void EnQueue(int data);
    Node* DeQueue();
    int GetSize();
    int GetFront();
    int GetRear();
    void Print();
    void Clear();
};

Queue::Queue() {
    this->count = 0;
    this->front = NULL;
    this->rear = NULL;
};
Queue::~Queue() {
    this->Clear();
}
void Queue::Clear() {
    Node *temp;
    while (this->front != NULL) {
        temp = this->front;
        this->front = this->front->next;
        delete temp;
    }
}

void Queue::EnQueue(int data) {
    Node *pNew = new Node(data);
    if (this->count == 0) {
        this->front = pNew;
    } else {
        this->rear->next = pNew;
    }
    this->rear = pNew;
    this->count++;
};

Node* Queue::DeQueue() {
    if (this->count == 0) {
        cout << "Queue is empty" <<endl;
        return NULL;
    }
    Node* node = this->front;
    this->front = this->front->next;
    this->count--;
    return node;
};

void Queue::Print() {
    cout<< "Queue data:" <<endl;
    Node *temp = this->front;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
}

int Queue::GetRear() {
    if (this->count == 0) {
        return -1; // default empty
    }
    return this->rear->data;
}

int Queue::GetFront(){
    if (this->count == 0) {
        return -1; // default empty
    }
    return this->front->data;
}

int Queue::GetSize() {
    return this->count;
}

void testQueue() {
    Queue *queue = new Queue();
    queue->Print();
    queue->EnQueue(5);
    queue->EnQueue(6);
    queue->EnQueue(7);
    queue->Print();
    Node *p = queue->DeQueue();
    cout << "data dequeue is: "<< p->data <<endl;
    queue->Print();
    queue->EnQueue(10);
    queue->Print();
}

//Array-based queue
class ArrayQueue {
private:
    int front, rear;
    int *storage;
    int capacity;
public:
    ArrayQueue(int capacity) {
        this->capacity = capacity;
        this->front = -1;
        this->rear  = -1;
        storage = new int[capacity];
    }
    ~ArrayQueue() {
        delete []storage;
    }
    void EnQueue(int value);
    int DeQueue();
    bool isFull();
    bool isEmpty();
    void PrintQueue();
};

bool ArrayQueue::isFull() {
    return rear - front + 1 == capacity;
}

bool ArrayQueue::isEmpty() {
    return front > rear || front == -1;
}

void ArrayQueue::EnQueue(int value) {
    if (isFull()) {
        cout << "Queue full" <<endl;
        return;
    }
    if (front == -1) {
        front = 0;
    }
    rear++;
    storage[rear % capacity] = value;
}


int ArrayQueue::DeQueue() {
    if (isEmpty()) {
        throw string("Queue is Empty");
    }
    int value = storage[front%capacity];
    front++;
    return value;
}

void ArrayQueue::PrintQueue() {
    cout << "Queue data is:" <<endl;
    if (isEmpty()) {
        cout << "Queue is empty" <<endl;
        return;
    }
    for (int i = front; i <= rear; i++) {
        cout<< storage[i%capacity] <<endl;
    }
}

void testArrayQueue() {
    ArrayQueue *queue = new ArrayQueue(5);
    queue->PrintQueue();
    queue->EnQueue(2);
    queue->EnQueue(5);
    queue->EnQueue(4);
    queue->EnQueue(6);
    queue->EnQueue(7);
    queue->EnQueue(9);
    queue->PrintQueue();
    
    int value = queue->DeQueue();
    
    cout << "enqueue data: " <<value;
    
    queue->PrintQueue();
    
    queue->DeQueue();
    queue->DeQueue();
    queue->DeQueue();
    queue->PrintQueue();
    queue->DeQueue();
    queue->PrintQueue();
    
    
    
}

class Animal {
public:
    string name;

    Animal(string name) {
        this->name = name;
    }
};

void testPointer() {
    Animal a = Animal("dog");
    cout << "&a: " <<&a << endl;
    cout << "a.name: " <<&(a.name) << endl;
    Animal &b = a;
    cout << "&b: " <<&b << endl;
    cout << "b.name: " <<&(b.name) << endl;
    b.name = "cat";
    cout<< "a.name after: " <<a.name <<endl;
}



//
int findMax(int a, int b) {
    return a > b ? a : b;
}

int MaxRecursive(Queue *queue, int size) {
    if(size < 1) {
        cout << "Queue 0 có phần tử" <<endl;
        return -100;
    }
    Node *node = queue->DeQueue();
    int value = node->data;
    size--;
    queue->EnQueue(value);
    if (size == 0) {
        return value;
    }
    return findMax(value, MaxRecursive(queue, size));
}

void testMaxRecursive() {
    Queue *queue = new Queue();
    queue->EnQueue(1);
    queue->EnQueue(5);
    queue->EnQueue(6);
    queue->EnQueue(9);
    queue->EnQueue(2);
    queue->Print();
    
    int value = MaxRecursive(queue, queue->GetSize());
    
    cout << "max value is: " << value <<endl;
    queue->Print();
}

// check equal queue

bool isIdentical(Queue* q1, Queue *q2) {
    if (q1->GetSize() != q2->GetSize()) {
        return false;
    }
    for (int i = 0; i < q1->GetSize(); i++) {
        Node* p1 = q1->DeQueue();
        q1->EnQueue(p1->data);
        Node* p2 = q2->DeQueue();
        q2->EnQueue(p2->data);
        if(p1->data != p2->data) {
            return false;
        }
    }
    return true;
}

void testIsIdentical(){
    Queue *queue1 = new Queue();
    queue1->EnQueue(5);
    queue1->EnQueue(5);
    queue1->EnQueue(6);
    queue1->EnQueue(9);
    queue1->EnQueue(2);
    Queue *queue2 = new Queue();
    queue2->EnQueue(5);
    queue2->EnQueue(5);
    queue2->EnQueue(6);
    queue2->EnQueue(9);
    queue2->EnQueue(3);
    
    queue1->Print();
    queue2->Print();
    
    bool check = isIdentical(queue1, queue2);
    cout << "check is: " << check <<endl;
    
}

void swapInt(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

Stack* catStack(Stack *s1, Stack *s2) {
    Stack *temp = new Stack();
    int data;
    while (!s1->IsEmpty()) {
        data = s1->Pop();
        temp->Push(data);
    }
    while (!temp->IsEmpty()) {
        data = temp->Pop();
        s2->Push(data);
    }
    return s2;
}

void testCatStack(){
    Stack *stack1 = new Stack();
    stack1->Push(5);
    stack1->Push(4);
    stack1->Push(15);
    Stack *stack2 = new Stack();
    stack2->Push(9);
    stack2->Push(29);
    stack2->Push(1);
    
    stack1->PrintStack();
    stack2->PrintStack();
    
    Stack *result = catStack(stack1, stack2);
    result->PrintStack();
}
int main() {
    
    testLinkedList();
//    testStack();
//    testArrayStack();
//    testQueue();
//    testArrayQueue();
    
//    testPointer();
    
//    testMaxRecursive();
//    testIsIdentical();
//    testCatStack();
    return 0;
}






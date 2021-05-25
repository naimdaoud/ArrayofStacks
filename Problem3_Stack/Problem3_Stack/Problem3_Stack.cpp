#include <iostream>

using namespace std;

struct NODE {
    int data;
    NODE* next;
};

struct Stack {
    NODE* top;
};

void init(Stack& s) {
    s.top = nullptr;
}

void initStackArray(Stack*& s, int N) {
    for (int i = 0; i < N; i++) {
        s[i].top = nullptr;
    }    
}

bool empty(Stack& s) {
    return s.top == nullptr;
}

int Size(Stack& s) {
    NODE* cur;
    int size = 0;
    cur = s.top;
    while (cur != nullptr) {
        size = size + cur->data;
        cur = cur->next;
    }
    return size;
}

void push(Stack& s, int val) {
    NODE* tmp;
    tmp = new NODE;
    tmp->data = val;
    tmp->next = nullptr;

    if (empty(s)) {
        s.top = tmp;
        return;
    }
    tmp->next = s.top;
    s.top = tmp;
}

void SortArrayDesc(int *a, int N) { //insertionSortShift
    int key, j;
    for (int i = 1; i < N; i++) {
        key = a[i];
        for (j = i; j > 0; j--)
            if (key > a[j - 1])
                a[j] = a[j - 1];
            else
                break;
        a[j] = key;
    }
}

Stack* InsertBin(int *a, int N) {
    Stack* st = new Stack[N];
    initStackArray(st,N);
    int remSize = 0;
    SortArrayDesc(a, N);
    for (int i = 0; i < N; i++) {
        if (empty(st[0])) {
            push(st[0], a[i]);
            continue;
        }
        for (int k = 0; k < N; k++) {
            if (empty(st[k])) {
                push(st[k], a[i]);
                break;
            }
            remSize = 10 - Size(st[k]);
            if (a[i] <= remSize) {
                push(st[k], a[i]);
                break;
            }
            if (a[i] > remSize) {
                continue;
            }
        }
    }
    return st;
}

void display(Stack& s) {
    NODE* cur;
    if (empty(s)) {
        cout << "Empty stack" << endl;
        return;
    }

    cur = s.top;
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

int RemoveEmptyStack(Stack* s, int N) { //Return the number of elements after removal of empty stacks.
    int c = 0;
    Stack* tmp = new Stack[N];
    for (int i = 0; i < N; i++) {
        if (!empty(s[i])) {
            tmp[i] = s[i];
            c = c + 1;
        }  
    }
    s = tmp;
    delete[] tmp;
    return c;
}

int main()
{
    srand(time(0));
    int N = 7;
    int newN;
    int* a = new int[N];
    cout << "Printing random array: " << endl;
    for (int i = 0; i < N; i++) {
        a[i]= (rand() % 10) + 1;
        cout << a[i] << ", ";
    }
    cout << endl << endl;
    Stack* st = new Stack[N];
    st = InsertBin(a,N);
    cout << "Printing sorted array: " << endl;
    for (int i = 0; i < N; i++) {
        cout << a[i] << ", ";
    }
    cout << endl << endl;
    newN = RemoveEmptyStack(st, N);
    cout << "The number of bins is: " << newN << endl << endl;
    cout << "Printing each bin content: " << endl;
    for (int i = 0; i < newN; i++) {
        cout << "Bin" << i << ": ";
        display(st[i]);
    }
}
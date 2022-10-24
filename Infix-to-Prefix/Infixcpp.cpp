#include <iostream>
#include <string>
#include "Infix.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

//Stack manipulation
void initStack(Stack& s) {
    s.top = NULL;
}
bool isEmpty(Stack s) {
    if (s.top == NULL) return true;
    return false;
}
Node* createNode(Data x) {
    Node* p = new Node;
    if (p == NULL) {
        cout << "Not enough memory to allocate!" << endl;
        return	NULL;
    }
    p->data = x;
    p->next = NULL;
    return p;
}
void deleteNode(Node* p)
{
    if (p == NULL)	return;

    p->next = NULL;
    delete p;
}
void push(Stack& s, Node* p) {
    if (p != NULL) {
        if (s.top == NULL) s.top = p;
        else {
            p->next = s.top;
            s.top = p;
        }
    }
}
Node* pop(Stack& s) {
    Node* p = new Node;
    if (s.top != NULL) {
        p = s.top;
        s.top = s.top->next;
        p->next = NULL;
    }
    return p;
}
void addAValueToStack(Stack& s, char x) {
    Node* p = new Node;
    if (p == NULL) {
        cout << "Error with data shortage :)))" << endl;
    }
    p->data = x;
    p->next = NULL;
    push(s, p);
}
string enterValue() {
    string x;
    cout << "Enter infix: "; getline(cin, x);
    return x;
}
int getTop(Stack s) {
    if (s.top == NULL) return -1;
    return s.top->data;
}
void displayStack(Stack s) {
    if (s.top == NULL) return;
    for (Node* p = s.top; p->next != NULL; p = p->next) {
        cout << "\t" << p->data << endl;
    }
}
//ex 2
bool isNumber(char a) {
    return a >= '0' && a <= '9';
}
bool isSpecialCharacter(char a) {
    return a == '*' || a == '/' || a == '%' || a == '+' || a == '-' || a == '(' || a == ')';
}
int priority(char a) {
    if (a == '*' || a == '/' || a == '%')
        return 2;
    if (a == '+' || a == '-')
        return 1;
    return 0;
}
void swapCharacter(char& a, char& b) {
    char temp = a;
    a = b;
    b = temp;
}
void reverse(string& a) {
    int n = a.length();
    if (n == 1 || n == 0) return;
    for (int i = 0; i * 2 < n; i++) {
        swapCharacter(a[i], a[n - 1 - i]);
    }
}
string convertInfixtToPrefix(string a) {
    reverse(a);
    int count = 0;
    int n = a.length();
    if (n == 1 || n == 0) return a;
    Stack s;
    initStack(s);
    string result = "";
    for (int i = 0; i < n; i++) {
        if (isSpecialCharacter(a[i])) {
            if (s.top == NULL) {
                if (a[i] == ')') {
                    count++;
                }
                push(s, createNode(a[i]));
            }
            else {
                if (a[i] == ')') {
                    count++;
                    push(s, createNode(a[i]));
                }
                else if (a[i] == '(') {
                    while (s.top->data != ')') {
                        result += pop(s)->data;                        
                        if (s.top == NULL) break;
                    }
                    if (s.top->data == ')') {
                        count--;
                        deleteNode(pop(s));
                    }                    
                }
                else {
                    if (priority(s.top->data) == priority(a[i])) {
                        push(s, createNode(a[i]));
                    }
                    else if (priority(s.top->data) > priority(a[i])) {
                        if (s.top->data == ')') {
                            push(s, createNode(a[i]));
                            continue;
                        }
                        while (s.top != NULL) {
                            if (priority(s.top->data) > priority(a[i])) {
                                result += pop(s)->data;
                            }
                            else {
                                break;
                            }
                        }
                        push(s, createNode(a[i]));
                    }
                    else {
                        push(s, createNode(a[i]));
                    }
                }
            }            
        }
        else if (isNumber(a[i])) {
            result += a[i];
        }
        else {
            continue;
        }
    }
    while (s.top != NULL) {
        if (count != 0) {
            if (s.top->data == ')') {
                deleteNode(pop(s));
                count--;
                continue;
            }        
        }
        result += pop(s)->data;
        if (s.top == NULL) break;
    }
    reverse(result);
    return result;
}
string convertInfixtToPostfix(string a) {
    int count = 0;
    int n = a.length();
    if (n == 1 || n == 0) return a;
    Stack s;
    initStack(s);
    string result = "";
    for (int i = 0; i < n; i++) {
        if (isSpecialCharacter(a[i])) {
            if (s.top == NULL) {
                if (a[i] == '(') {
                    count++;
                }
                push(s, createNode(a[i]));
            }
            else {
                if (a[i] == '(') {
                    count++;
                    push(s, createNode(a[i]));
                }
                else if (a[i] == ')') {
                    while (s.top->data != '(') {
                        result += pop(s)->data;
                        if (s.top == NULL) break;
                    }
                    if (s.top->data == '(') {
                        count--;
                        deleteNode(pop(s));
                    }
                }
                else {
                    if (priority(s.top->data) >= priority(a[i])) {
                        if (s.top->data == '(') {
                            push(s, createNode(a[i]));
                            continue;
                        }
                        while (s.top != NULL) {
                            if (priority(s.top->data) >= priority(a[i])) {
                                result += pop(s)->data;
                            }
                            else {
                                break;
                            }
                        }
                        push(s, createNode(a[i]));
                    }
                    else {
                        push(s, createNode(a[i]));
                    }
                }
            }
        }
        else if (isNumber(a[i])) {
            result += a[i];
        }
        else {
            continue;
        }
    }
    while (s.top != NULL) {
        if (count != 0) {
            if (s.top->data == '(') {
                deleteNode(pop(s));
                count--;
                continue;
            }
        }
        result += pop(s)->data;
        if (s.top == NULL) break;
    }
    return result;
}
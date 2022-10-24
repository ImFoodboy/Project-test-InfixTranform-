#pragma once
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

typedef char Data;
struct Node {
    Data data;
    Node* next;
};
struct Stack {
    Node* top;
};

void initStack(Stack& s);
bool isEmpty(Stack s);
Node* createNode(Data x);
void deleteNode(Node* p);
void push(Stack& s, Node* p);
Node* pop(Stack& s);
void addAValueToStack(Stack& s, char x);
string enterValue();
int getTop(Stack s);
void displayStack(Stack s);
bool isNumber(char a);
bool isSpecialCharacter(char a);
int priority(char a);
void swapCharacter(char& a, char& b);
void reverse(string& a);
string convertInfixtToPrefix(string a);
string convertInfixtToPostfix(string a);
#pragma once
#include <iostream>
using std::string;

#define X 100000
#define A 50000
//
struct Book {
	string id;
	string bookname;
	int numberofpages;
	float price;
	int publishingyear;
};

typedef Book Data;
struct Node {
	Data data;
	Node* next;

	//pthuc thiet lap
	Node();// rong
	Node(Data item);
};
struct LinkedListBook {
	Node* head;
	Node* tail;
};

void init(LinkedListBook& l);
bool isEmpty(LinkedListBook l);
Node* createNode(Data x);
Node* searchByID(LinkedListBook l, string idX);
bool insertXBeforeYByID(LinkedListBook& l, Data x, Data y);
void removeHead(LinkedListBook& l);
void removeLast(LinkedListBook& l);
void removeNodeNext(LinkedListBook& l, Node* p);
void addLastList(LinkedListBook& l, Node* p);
void addHead(LinkedListBook& l, Node* p);
void addAfterNode(LinkedListBook& l, Node* q, Node* p);
void enterFromFile(LinkedListBook& l, string directory);
void displayABook(Data data);
void displayAllBooks(LinkedListBook l);
bool isDuplicateID(LinkedListBook l, string id);
int countBooks500NPAndOlder2018(LinkedListBook l);
bool deleteBooksGreaterThanXPrice(LinkedListBook& l);
Data enterABook();
bool addBookBeforeTheBookSmallerThanAPrice(LinkedListBook& l, Data x, float priceX);
void Menu();
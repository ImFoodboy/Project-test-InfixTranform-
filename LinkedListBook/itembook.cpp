#include "itembook.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ios;
using std::fstream;
using std::setw;
using std::left;
using std::right;
using std::setfill;

//phuong thuc thiet lap
Node::Node() {
	data.id = "None";
	data.bookname = "None";	
	data.numberofpages = 0;
	data.price = 0;	
	data.publishingyear = 0;
	next = NULL;
}
Node::Node(Data item) {
	data = item;
	next = NULL;
}

void init(LinkedListBook& l) {
	l.head = NULL;
	l.tail = NULL;
}
bool isEmpty(LinkedListBook l) {
	return l.head == NULL;
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
Node* searchByID(LinkedListBook l, string idX) {
	for (Node* p = l.head; p != NULL; p = p->next) {
		if (p->data.id == idX) {
			return p;
		}
	}
	return NULL;
}
bool insertXBeforeYByID(LinkedListBook& l, Data x, Data y) {
	if (l.head == NULL) return false;
	Node* elementX = createNode(x);
	if (l.head->data.id == y.id) {
		addHead(l, elementX);
		return true;
	}
	for (Node* p = l.head; p->next != l.tail; p = p->next) {
		if (p->next->data.id == y.id) {
			elementX->next = p->next;
			p->next = elementX;
			return true;
		}
	}
	return false;
}
void removeHead(LinkedListBook& l) {
	if (l.head == NULL) return;
	Node* p = l.head;
	l.head = p->next;
	p->next = NULL;
	delete p;
}
void removeLast(LinkedListBook& l) {
	if (l.head == NULL) return;
	if (l.head == l.tail) {
		Node* p = l.tail;
		l.tail = NULL;
		l.head = NULL;
		delete p;
		return;
	}
	Node* p = l.tail;
	Node* q = l.head;
	while (q->next != l.tail) {
		q = q->next;
	}
	l.tail = q;
	l.tail->next = NULL;
	delete p;
}
void removeNodeNext(LinkedListBook& l, Node* p)
{
	if (l.head == NULL || p == NULL || p == l.tail) return;
	else {
		if (p->next == l.tail)
		{
			removeLast(l);
		}
		else {
			Node* q = p->next;
			p->next = q->next;
			q->next = NULL;
			delete q;
		}
	}
}
void addLastList(LinkedListBook& l, Node* p) {
	if (p == NULL) {
		return;
	}
	else {
		if (l.head == NULL) l.head = p, l.tail = p;
		else {
			l.tail->next = p;
			l.tail = p;
			p->next = NULL;
		}
	}
}
void addHead(LinkedListBook& l, Node* p) {
	if (p == NULL) return;
	if (isEmpty(l)) {
		l.head = p;
		l.tail = p;
	}
	else {
		p->next = l.head;
		l.head = p;
	}
}
void addAfterNode(LinkedListBook& l, Node* q, Node* p)
{
	if (p == NULL)	return;
	else
	{
		if (q == NULL)
		{
			if (l.head == NULL)//list is empty
				l.head = l.tail = p;
			else//cannot find node q in list
				return;
		}
		else
		{
			if (q == l.tail)
				addLastList(l, p);
			else
			{
				p->next = q->next;
				q->next = p;
			}
		}
	}
}
void enterFromFile(LinkedListBook& l, string directory)
{
	fstream file;
	file.open(directory, ios::in);//read mode
	if (file.is_open()) {
		Data temp;
		while (getline(file, temp.id,'#'))
		{
			getline(file, temp.bookname, '#');
			file >> temp.numberofpages;
			file.ignore();
			file >> temp.price;
			file.ignore();
			file >> temp.publishingyear;
			file.ignore();			
			addLastList(l, createNode(temp));
		}
		file.close();
	}
	else {
		cout << "Khong tim thay file !" << endl;
	}
}
void displayABook(Data data) {
	cout << setw(15) << left << data.id;
	cout << setw(40) << left << data.bookname;
	cout << setw(15) << right << data.numberofpages;
	cout << setw(10) << right << data.publishingyear;
	cout << setw(10) << right << data.price << endl;
}
void displayAllBooks(LinkedListBook l) {
	cout << setw(10) << left << "Serial";
	cout << setw(15) << left << "ID";
	cout << setw(40) << left << "Name";
	cout << setw(15) << right << "Numberofpages";
	cout << setw(10) << right << "Year";
	cout << setw(10) << right << "Price" << endl;
	if (l.head == NULL) {
		// reset fill to ' '
		cout << setfill(' ');
		cout << setw(10) << left << " ";
		return;
	}
	int i = 1;
	for (Node* p = l.head; p != NULL; p = p->next) {
		cout << setfill('-');		// set fill ' ' to '-'
		cout << setw(100) << "-" << endl;

		// reset fill to ' '
		cout << setfill(' ');
		cout << setw(10) << left << i++;
		displayABook(p->data);
	}
}
bool isDuplicateID(LinkedListBook l, string id) {
	if (searchByID(l, id) != NULL) return true;
	return false;
}
int countBooks500NPAndOlder2018(LinkedListBook l) {
	int count = 0;
	for (Node* p = l.head; p != NULL; p = p->next) {
		if (p->data.numberofpages > 500 && p->data.publishingyear < 2018) {
			count++;
		}
	}
	return count;
}
bool deleteBooksGreaterThanXPrice(LinkedListBook& l)
{
	bool flag = false;
	Node* q;
	for (Node* p = l.head; p->next != NULL; p = q) {
		if (p == l.head && p->data.price > X) {
			removeHead(l);
			flag = true;
			q = l.head;
		}
		else {
			if (p->next->data.price > X) {
				q = p;
				flag = true;
				removeNodeNext(l, p);
			}
			else {
				q = p->next;
			}
		}
	}
	if (l.tail->data.price > X) {
		removeLast(l);
		flag = true;
	}
	return flag;
}
Data enterABook() {
	Data p;
	cout << "Enter id: ";
	getline(cin, p.id);
	cout << "Enter the name of book: ";
	getline(cin, p.bookname);	
	cout << "Enter number of pages: ";
	cin >> p.numberofpages;
	cout << "Enter publishing year: ";
	cin >> p.publishingyear;
	cout << "Enter price (VND): ";
	cin >> p.price;
	return p;
}
bool addBookBeforeTheBookSmallerThanAPrice(LinkedListBook& l, Data x, float priceX) {
	if (l.head == NULL) return false;
	Node* elementX = createNode(x);
	if (l.head->data.price < priceX) {
		addHead(l, elementX);
		return true;
	}
	for (Node* p = l.head; p->next != l.tail; p = p->next) {
		if (p->next->data.price < priceX) {
			Node* elementX = createNode(x);
			elementX->next = p->next;
			p->next = elementX;
			p = p->next;
		}
		if (p->next->next == l.tail) {
			if (l.tail->data.price < priceX) {
				Node* elementX = createNode(x);
				elementX->next = p->next->next;
				p->next->next = elementX;
			}
			break;
		}
	}	
	return false;
}
void Menu() {
	cout << "Welcome to Menu !" << endl;
	cout << "0.\tExit" << endl;
	cout << "1.\tInput" << endl;
	cout << "2.\tDisplay" << endl;
	cout << "3.\tHow many books are larger than 500 pages and published before 2018" << endl;
	cout << "4.\tDelete all books is expensive than 100000" << endl;
	cout << "5.\tAdd another book before the books cost less than 5000" << endl;
}

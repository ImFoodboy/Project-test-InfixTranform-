#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "itembook.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
    LinkedListBook l;
    LinkedListBook a;
    init(a);
    init(l);
    Node* p;
    string directory, x;
    int choice = 0;
    float n;
    do {
        system("cls");
        Menu();
        cout << "Let's choose one of choices: "; cin >> choice;
        switch (choice) {
        case 0: cout << "Oh byeeee!" << endl;
        case 1:
            cin.ignore();
            cout << "Enter directory (ex:input.txt): "; getline(cin, directory);
            enterFromFile(l, directory);
            break;
        case 2:
            displayAllBooks(l);
            break;
        case 3:;
            cout << "Number of books are larger than 500 pages and published before 2018: " << countBooks500NPAndOlder2018(l) << endl;
            break;
        case 4:
            if (deleteBooksGreaterThanXPrice(l)) {
                cout << "Successful deleting!" << endl;
            }
            else {
                cout << "Can't find this type of books!" << endl;
            }
            break;
        case 5:
            cin.ignore();
            addBookBeforeTheBookSmallerThanAPrice(l, enterABook(), X);
            cout << "Successful adding!" << endl;
            break;
        default: cout << "Invalid!" << endl;
        }        
        if (choice != 2) {
            cout << "Original: " << endl;
            displayAllBooks(l);
        }
        system("pause>0");
    } while (choice != 0);


    system("pause>0");
    return 0;
}

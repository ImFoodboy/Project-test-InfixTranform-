#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Infix.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
    cout << "Convert infix to prefix and postfix!" << endl;
    string temp = enterValue();
    string a = convertInfixtToPrefix(temp);
    cout << "Prefix: " << a << endl;
    a = convertInfixtToPostfix(temp);
    cout << "Postfix: " << a << endl;
    system("pause>0");
    return 0;
}

#include <iostream>
#include <cstring>

using namespace std;

bool checkOpt(char* opt, char* value);
bool m_debug = false;
bool m_verbose = false;
string karatsuba(string n1, string n2);
string addition(string n1, string n2);
string subtraction(string n1, string n2);
long unsigned int getLength(string n1, string n2);
string padWithZeros(string &n, long unsigned int len);

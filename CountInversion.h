#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

bool checkOpt(char* opt, char* value);
bool m_debug   = false;
bool m_verbose = false;
bool m_brutal  = false;
ifstream m_inStream;
long unsigned int countInversions(int arr[], int n);
long unsigned int countInversions(int array[], int size);
long unsigned int countInv(int array[], int tmp[], int left, int right);
long unsigned int countSplitInv(int array[], int tmp[], int left, int mid, int right);
void printArray(int array [], int size);
void printVector(vector<int> vec);

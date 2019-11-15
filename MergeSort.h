#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

bool checkOpt(char* opt, char* value);
bool m_debug   = false;
bool m_verbose = false;
bool m_useArr  = false;
ifstream m_inStream;
vector<int> mergeSort(vector<int> array);
vector<int> merge(const vector<int> &left, const vector<int> &right);
void mergeSort(int *array, int left, int right);
void merge(int *array, int left, int mid, int right);
void printArray(int *array, int size);
void printVector(vector<int> vec);

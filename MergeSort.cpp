#include "MergeSort.h"

int main( int argc, char* argv[] ){

  string inFile = "";
  bool printHelp = false;
  for(int i = 1; i < argc; i++){ 
    bool validCmd = false;
    string cmd = argv[i];
    if( !strcmp(argv[i],"--inFile")        ){
      if( checkOpt(argv[i],argv[i+1]) )     { inFile    = argv[i+1]; } validCmd = true; }
    else if( !strcmp(argv[i],"--useArray") ){ m_useArr  = true;        validCmd = true; }
    else if( !strcmp(argv[i],"--debug")    ){ m_debug   = true;        validCmd = true; }
    else if( !strcmp(argv[i],"--verbose")  ){ m_verbose = true;        validCmd = true; }    
    else if( !strcmp(argv[i],"--help")     ){ printHelp = true;        validCmd = true; }
    if( !validCmd && cmd.find("--")!=string::npos){
      cout << "\033[1;31m ERROR:: Option " << cmd << " not valid. Type ./MergeSort"
	   << " --help and check the available options, exit!\033[0m"  << endl;
      exit(0);
    }
  }
  if( printHelp ){
    cout << "MergeSort Algorithm: sort an array of integers"            << endl;
    cout << "  usage:    ./MergeSort [--help] [--inFile] [--useArray]"  << endl;
    cout << "                        [--debug] [--verbose]"             << endl;
    cout << "  arguments (default value): "                             << endl;
    cout << "  --help     print this help and exit"                     << endl;
    cout << "  --inFile   define input file with the array (None)"      << endl;
    cout << "  --useArray enable using array instead of vector (false)" << endl;
    cout << "  --debug    enable debug mode (false)"                    << endl;
    cout << "  --verbose  enable verbose mode (false)"                  << endl;
    exit(0);
  }

  vector<int> vecList;
  int num  = 0;
  if(inFile=="" ){
    cout << " WARNING:: inFile is a needed argument!! \n"
	 << "           Please type name and path to it" << endl;
    cin >> inFile;
  }

  m_inStream.open( inFile.c_str() );
  if( !m_inStream.good() ){
    cout << " ERROR:: inFile " << inFile << " doesn't exist \n"
	 << "         Please enter the array manually! \n"
	   << "         Type the size of the array " << endl;
    int size = 0;
    cin >> size;
    for(int i=0; i<size; i++){
      cout << "       Type an integer " << endl;
      cin >> num;
      vecList.push_back( num );
	num = 0;
    }
  } 
  else{
    cout << " File containing the array is : " << inFile << endl;
    while( m_inStream.good() ){
      m_inStream>>num;
      vecList.push_back(num);
      num=0;
    }
  }
  m_inStream.close();
  
  int arrList[vecList.size()];
  if(m_useArr){
    for(uint i=0; i<vecList.size(); i++){
      arrList[i] = vecList[i];
    }
    if(vecList.size()!=sizeof(arrList) / sizeof(*arrList)){
      cout << " ERROR:: wrong conversion from vector to array! Exiting" << endl;
      exit(0);
    }
    vecList.clear();
  }
  
  if(m_debug){
    if(m_useArr){
      cout << " Size of the array = " << sizeof(arrList) / sizeof(*arrList) << endl;
      cout << " DEBUG:: values in the array are : " << endl;
      printArray(arrList,sizeof(arrList) / sizeof(*arrList));
    }
    else{
      cout << " Size of the vector = " << vecList.size() << endl;
      cout << " DEBUG:: values in the vector are: " << endl;
      printVector(vecList);
    }
  }

  if(m_useArr){
    mergeSort(arrList,0,sizeof(arrList) / sizeof(*arrList) -1);
    if(m_debug){
      cout << " DEBUG:: values on the sorted array are: " << endl;
      printArray(arrList,sizeof(arrList) / sizeof(*arrList));
    }
  }
  else{
    vector<int> sortedVector = mergeSort(vecList);
    if(m_debug){
      cout << " DEBUG:: values on the sorted array are: " << endl;
      printVector(sortedVector);
    }
  }
  
  return 0;

}

vector<int> mergeSort(vector<int> array){

  // base case: if size 1 return vector
  if( array.size() == 1){
    return array;  
  }
  
  // Determine the location of the middle element in the vector
  vector<int>::iterator middle = array.begin() + (array.size() / 2);  

  // define left and right halves
  vector<int> left ( array.begin(), middle      );  
  vector<int> right( middle       , array.end() );  
  
  // Perform a merge sort on the two smaller vectors  
  left  = mergeSort(left);  
  right = mergeSort(right);  
  
  return merge(left, right);

}

vector<int> merge(const vector<int> &left, const vector<int> &right){

  // Fill the resultant vector with sorted results from both vectors  
  vector<int> result;  
  unsigned left_it = 0, right_it = 0;  
  
  while( left_it < left.size() && right_it < right.size() ){
    // If the left value is smaller than the right it goes next  
    // into the resultant vector  
    if( left[left_it] < right[right_it] ){  
      result.push_back(left[left_it]);  
      left_it++;  
    }  
    else{
      result.push_back(right[right_it]);  
      right_it++;  
    }
  }
  
  // Push the remaining data from both vectors onto the resultant  
  while( left_it < left.size() ){  
    result.push_back(left[left_it]);  
    left_it++;  
    }  
  
  while( right_it < right.size() ){  
    result.push_back(right[right_it]);  
    right_it++;  
  }
  
  return result;
  
}

void mergeSort(int *array, int left, int right){

  if(left<right){
  
    //find middle of the array
    int mid = (right+left)/2;

    // Sort left and right halves 
    mergeSort(array, left, mid); 
    mergeSort(array, mid+1, right);

    // merge halves
    merge(array, left, mid, right);
    
  }
  
}

void merge(int *array, int left, int mid, int right){

  int nl = mid-left+1; 
  int nr = right-mid; 
  
  /* create temp arrays */
  int L[nl], R[nr]; 
  
  /* Copy data to temp arrays L[] and R[] */
  for(int ii=0; ii<nl; ii++)
    L[ii] = array[left+ii]; 
  for(int jj=0; jj<nr; jj++) 
    R[jj] = array[mid+1+jj]; 
  
  /* Merge the temp arrays back into arr[l..r]*/
  int i = 0;    // Initial index of left subarray 
  int j = 0;    // Initial index of right subarray 
  int k = left; // Initial index of merged subarray 

  while (i<nl && j<nr){
    if (L[i]<=R[j]){
      array[k] = L[i]; 
      i++; 
    } 
    else{
      array[k] = R[j]; 
      j++; 
    }
    k++; 
  }

  //Copy the remaining elements of L[], if any 
  while(i<nl){
    array[k] = L[i]; 
    i++; 
    k++;
  } 
  
  // Copy the remaining elements of R[], if any
  while(j<nr){ 
    array[k] = R[j]; 
    j++; 
    k++;
  }
  
}

bool checkOpt(char* opt, char* value){

  std::string val = value;
  if( 0==val.find("--") ){
    cout << "WARNING:: Option " << opt <<
      " requires value -> skipping " << endl;
    return false;
  }
  return true;
  
}

void printArray(int *array, int size){
  
  for(int i=0; i<size; i++){
    if(i==0) cout << "                         " << array[i];
    else     cout << " , " << array[i];
  }
  cout << endl;
  
}

void printVector(vector<int> vec){
  
  for(uint i=0; i<vec.size(); i++){
    if(i==0) cout << "                         " << vec[i];
    else     cout << " , " << vec[i];
  }
  cout << endl;
  
}

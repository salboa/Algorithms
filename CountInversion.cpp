#include "CountInversion.h"

int main( int argc, char* argv[] ){

  string inFile = "";
  bool printHelp = false;
  for(int i = 1; i < argc; i++){ 
    bool validCmd = false;
    string cmd = argv[i];
    if( !strcmp(argv[i],"--inFile")       ){
      if( checkOpt(argv[i],argv[i+1]) )    { inFile    = argv[i+1]; } validCmd = true; }
    else if( !strcmp(argv[i],"--brutal")  ){ m_brutal  = true;        validCmd = true; }
    else if( !strcmp(argv[i],"--debug")   ){ m_debug   = true;        validCmd = true; }
    else if( !strcmp(argv[i],"--verbose") ){ m_verbose = true;        validCmd = true; }
    else if( !strcmp(argv[i],"--help")    ){ printHelp = true;        validCmd = true; }
    if( !validCmd && cmd.find("--")!=string::npos){
      cout << "\033[1;31m ERROR:: Option " << cmd << " not valid. Type ./CountInversion"
	   << " --help and check the available options, exit!\033[0m"  << endl;
      exit(0);
    }
  }
  if( printHelp ){
    cout << "CountInversion Algorithm: count number of inversions in the array" << endl;
    cout << "  usage:    ./CountInversion [--help] [--inFile] [--brutal] "      << endl;
    cout << "                             [--debug] [--verbose]"                << endl;
    cout << "  arguments (default value): "                                     << endl;
    cout << "  --help     print this help and exit"                             << endl;
    cout << "  --inFile   define input file with the array (None)"              << endl;
    cout << "  --brutal   enable brute forse mode - double loop (false)"        << endl;
    cout << "  --debug    enable debug mode (false)"                            << endl;
    cout << "  --verbose  enable verbose mode (false)"                          << endl;
    exit(0);
  }

  vector<int> tmpVec;
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
      tmpVec.push_back( num );
      num = 0;
    }
  } 
  else{
    cout << " File containing the array is : " << inFile << endl;
    while( m_inStream.good() ){
      m_inStream>>num;
      tmpVec.push_back(num);
      num=0;
    }
  }
  m_inStream.close();

  int array[tmpVec.size()];
  for(uint i=0; i<tmpVec.size(); i++){
    array[i] = tmpVec[i];
  }
  
  if(m_debug){
    cout << " Size of the (vec , array) = (" << tmpVec.size()
	 << " , " << sizeof(array) / sizeof(*array) << ")" << endl;
    cout << " DEBUG:: values in the array are : " << endl;
    printArray(array,sizeof(array) / sizeof(*array));
    cout << " DEBUG:: values in the vector are: " << endl;
    printVector(tmpVec);
  }
  if(tmpVec.size()!=sizeof(array) / sizeof(*array)){
    cout << " ERROR:: wrong conversion from vector to array! Exiting" << endl;
    exit(0);
  }
  tmpVec.clear();
  
  long unsigned int Ninv = 0;
  if(m_brutal)
    Ninv = countInversions( array, sizeof(array) / sizeof(*array) );
  else
    Ninv = countInversions( array, sizeof(array) / sizeof(*array) );
  cout << " Number of inversions is : "<< Ninv << endl;
  
  return 0;

}

long unsigned int countInversions(int array[], int size){

  int tmp[size];
  return countInv(array, tmp, 0, size -1 );
  
}

long unsigned int countInv(int array[], int tmp[], int left, int right){
  
  // initialize n. inversions to 0;
  long unsigned int linv = 0;
  long unsigned int rinv = 0;
  long unsigned int sinv  = 0;
  long unsigned int total  = 0;

  if(right>left){

    // define middle point of the array
    int mid = (right+left)/2;
    
    // count left/right inversions
    linv = countInv( array, tmp, left, mid);
    rinv = countInv( array, tmp, mid+1, right);

    //count split inversion
    sinv = countSplitInv( array, tmp, left, mid+1, right );

    //sum up inversions
    total = linv+rinv+sinv;

    if(m_debug){
      cout << " DEBUG:: left  inversions = " << linv  << endl;
      cout << " DEBUG:: right inversions = " << rinv  << endl;
      cout << " DEBUG:: split inversions = " << sinv  << endl;
      cout << " DEBUG:: total inversions = " << total << endl;
    }
  }
  
  return total;
      
}

long unsigned int countSplitInv(int array[], int tmp[], int left, int mid, int right){

  // Fill the resultant vector with sorted results from both vectors

  int splitInv = 0;
  int i = left; // i -> index for left subarray
  int j = mid;  // j -> index for right subarray
  int k = left; // k -> index for resultant merged subarray
  
  while ( (i<=mid-1) && (j<=right)) { 
    if (array[i] <= array[j]) { 
      tmp[k++] = array[i++]; 
    } 
    else { 
      tmp[k++] = array[j++];
      //split inversion = remaining element in left subarray at this point
      splitInv += (mid-i); 
    } 
  } 
  
  //Copy remaining elements of left subarray (if any) to resultant array
  while (i <= mid - 1) 
    tmp[k++] = array[i++]; 

  // Copy remaining elements of right subarray (if any) to resultant array
  while (j <= right) 
    tmp[k++] = array[j++]; 
  
  // Copy back the merged elements to original array
  for (i = left; i <= right; i++) 
    array[i] = tmp[i]; 
  
  return splitInv;
  
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

void printArray(int array [], int size){
  
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

long unsigned int getInvCount(int arr[], int n){ 

  long unsigned int invs = 0; 
  for(int i=0; i <n-1; i++) 
    for(int j=i+1; j<n; j++) 
      if (arr[i] > arr[j]) 
	invs++; 
  
  return invs;
  
}

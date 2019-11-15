#include "Karatsuba.h"

int main( int argc, char* argv[] ){

  string Num1 = "";
  string Num2 = "";
  bool printHelp = false;
  for(int i = 1; i < argc; i++){ 
    bool validCmd = false;
    string cmd = argv[i];
    if( !strcmp(argv[i],"--num1")         ){
      if( checkOpt(argv[i],argv[i+1]) )    { Num1      = argv[i+1]; } validCmd = true; }
    if( !strcmp(argv[i],"--num2")         ){
      if( checkOpt(argv[i],argv[i+1]) )    { Num2      = argv[i+1]; } validCmd = true; }
    else if( !strcmp(argv[i],"--debug")   ){ m_debug   = true;        validCmd = true; }
    else if( !strcmp(argv[i],"--verbose") ){ m_verbose = true;        validCmd = true; }    
    else if( !strcmp(argv[i],"--help")    ){ printHelp = true;        validCmd = true; }
    if( !validCmd && cmd.find("--")!=string::npos){
      cout << "\033[1;31m ERROR:: Option " << cmd << " not valid. Type ./Karatsuba"
	   << " --help and check the available options, exit!\033[0m"  << endl;
      exit(0);
    }
  }
  if( printHelp ){
    cout << "Karatsuba Algorithm: multiply to integers"  << endl;
    cout << "  usage:    ./Karatsuba [--help] [--num1] " << endl;
    cout << "                        [--num2] [--debug]" << endl;
    cout << "                        [--verbose]"        << endl;
    cout << "  arguments (default value): "              << endl;
    cout << "  --help     print this help and exit"      << endl;
    cout << "  --num1     define first number (None)"    << endl;
    cout << "  --num2     define second number (None)"   << endl;
    cout << "  --debug    enable debug mode (false)"     << endl;
    cout << "  --verbose  enable verbose mode (false)"   << endl;
    exit(0);
  }
  
  if(Num1=="" ){
    cout << " WARNING:: firstNum is a needed argument!! \n"
	 << "           Please type a number" << endl;
    cin >> Num1;
  }
  if(Num2==""){
    cout << " WARNING:: secondNum is a needed argument!! \n"
	 << "           Please type a number" << endl;
    cin >> Num2;
  }
  
  cout << " Numbers to be multiplied are: \n"
       << "  n1 = " << Num1 << " \n"
       << "  n2 = " << Num2 << endl;

  string product = karatsuba(Num1,Num2);
  cout << " Final product is " << product << endl;
  
  return 0;

}

string karatsuba(string n1, string n2){

  /* function to multiply 2 numbers using Karatsuba 
     multiplication algorithm */

  //get the maximum length of numbers
  long unsigned int len = getLength(n1,n2);

  //pad the shortest number with zero
  padWithZeros(n1,len);
  padWithZeros(n2,len);

  /* base case: string of size 1 */
  if(n1.size()<2 || n2.size()<2){
    string prod = to_string( (n1[0]-'0')*(n2[0]-'0') );
    if(m_debug)
      cout << " DEBUG:: in base case -> n1*n2 = " << prod << endl;
    return prod;
  }

  string a = n1.substr( 0    , len/2     );
  string b = n1.substr( len/2, len-len/2 );
  string c = n2.substr( 0    , len/2     );
  string d = n2.substr( len/2, len-len/2 );

  if(m_debug)
    cout << " DEBUG:: values of \n"
	 << "         a = " << a << " , b = " << b
	 << " , c = " << c << " , d = " << d << endl;

  //derive main parameters
  string ac    = karatsuba( a, c );
  string bd    = karatsuba( b, d );
  string ab_cd = karatsuba( addition( a, b ), addition( c, d ) );
  string ad_bc = subtraction( ab_cd, addition( ac, bd ) );
  if(m_debug)
    cout << " DEBUG:: values of \n"
	 << "         ac    = " << ac
	 << "         bd    = " << bd
	 << "         ab_cd = " << ab_cd
	 << "         ad_bc = " << ad_bc << endl;
  
  //perform 10^2 shifthing of ac term
  for(long unsigned int i=0; i<2*(len-len/2); i++)
    ac.append("0");

  //perform 10^n/2 shifthing of ad_bc term
  for(long unsigned int i=0; i<(len-len/2); i++)
    ad_bc.append("0");

  if(m_debug)
    cout << " DEBUG:: partial values before the sum of \n"
	 << "         ac*(10**n)        = " << ac    << "\n"
         << "         (ad_bc*(10**n_2)) = " << ad_bc << "\n"
         << "         bd                = " << bd    << "\n" << endl;

  string res = addition( addition( ac, bd ), ad_bc );
  if(m_debug)
    cout << " DEBUG:: result (befor lead. 0s removal) = "
	 << res << endl;
  
  res.erase( 0, min(res.find_first_not_of('0'), res.size()-1) );
  if(m_debug)
    cout << " DEBUG:: result (after lead. 0s removal) = "
	 << res << endl;
  
  
  return res;
  
}

string addition(string n1, string n2){

  if(m_verbose)
    cout << " VERBOSE:: called addition with \n"
	 << "           n1 = " << n1 << " , n2 = " << n2 << endl;
    
  long unsigned int len = getLength(n1,n2);
  padWithZeros(n1,len);
  padWithZeros(n2,len);

  int carry = 0;
  int col_sum =0;
  string sum = "";
  
  //build sum from right to left
  for(int i=len-1; i>=0; i--){
    col_sum = (n1[i]-'0')+(n2[i]-'0')+carry;
    carry   = col_sum/10;
    sum.insert( 0,to_string(col_sum %10) );
    if(m_verbose){
      cout << " VERBOSE:: col_sum = " << col_sum
	   << " , carry = " << carry
	   << " , sum = " << sum << endl;
    }
  }
  
  if(carry)
    sum.insert( 0,to_string(carry) );
  
  if(m_verbose)
    cout << " VERBOSE:: sum (after last carry check) = "
	 << sum << endl;

  sum.erase(0, min(sum.find_first_not_of('0'),sum.size()-1) );

  if(m_verbose)
    cout << " VERBOSE:: sum (after lead. 0s removal) = "
	 << sum << endl;
  
  return sum;
  
}

string subtraction(string n1, string n2){

   if(m_verbose)
     cout << " VERBOSE:: called subtraction with \n"
	 << "         n1 = " << n1 << " , n2 = " << n2 << endl;
  
  long unsigned int len = getLength(n1,n2);
  padWithZeros(n1,len);
  padWithZeros(n2,len);

  int col_diff =0;
  string diff = "";
  
  //build subtraction from right to left
  for(int i=len-1; i>=0; i--){
    col_diff = (n1[i]-'0')-(n2[i]-'0');
    if(col_diff>=0){
      diff.insert( 0,to_string(col_diff) );
    }
    else{
      //take a decine from the previous column
      int j = i -1;
      while(j>=0){
	n1[j] = ((n1[j]-'0') - 1) % 10 + '0';
	if (n1[j] != '9') 
	  break;
	else 
	  j--;
      }
      diff.insert(0, to_string(col_diff+10));
    }
    if(m_verbose){
      cout << " VERBOSE:: col_diff = " << col_diff
	   << " , diff = " << diff << endl;
    }
  }
  
  diff.erase(0, min(diff.find_first_not_of('0'),diff.size()-1) );

  if(m_verbose)
    cout << " VERBOSE:: diff (after lead. 0s removal) = "
	 << diff << endl;
  
  return diff;
  
}

long unsigned int getLength(string n1, string n2){

  return max(n1.size(),n2.size());
  
}

string padWithZeros(string &n, long unsigned int len){

  while(n.size()<len)
    n.insert(0,"0");

  return n;
  
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

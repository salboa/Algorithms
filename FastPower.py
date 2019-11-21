#!/usr/bin/python3

import os
import argparse

""" 
PSEUDOCODE FOR CALCULATING a^b where a and b are positive integers
  FastPower(a,b) :
    if b = 1
      return a
    else
      c := a*a
      ans := FastPower(c,[b/2])
    if b is odd
      return a*ans
    else return ans
  end
"""

parser = argparse.ArgumentParser(description='Perform a^b fast algorithm'                    )
parser.add_argument('--aVal'  , type=int           , default=None , help='specify a value'   )
parser.add_argument('--bVal'  , type=int           , default=None , help='specify b value'   )
args = parser.parse_args()

count = 0

def main():

    a = args.aVal
    b = args.bVal
    
    if not a:
        a = int( input( ' Specify a value: ' ) )
    if not b:
        b = int( input( ' Specify b value: ' ) )

    print( ' Going to perform a^b ... ' )
    ans = FastPower(a,b)
    print( ' result is = %s  done with %s operations' %(ans,count) )


def FastPower(a,b):

    global count
    if b == 1:
        count += 1
        return a
    else:
        count +=2
        c = a*a
        ans = FastPower(c,b/2)
    if b%2 == 1:
        count +=1
        return a*ans
    else:
        count +=1
        return ans
    
if __name__ == "__main__":
    main()

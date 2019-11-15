#!/usr/bin/python3

import os
import argparse
from math import *


parser = argparse.ArgumentParser(description='Perform Karatsuba Multiplication of two integers'    )
parser.add_argument('--num1' , type=str           , default=None , help='specify first number' )
parser.add_argument('--num2' , type=str           , default=None , help='specify second number')
parser.add_argument('--debug', action='store_true', default=False, help='enable debug mode'    )
args = parser.parse_args()


def main():

    num1 = args.num1
    num2 = args.num2
    if not num1:
        num1 = input('Specify the first number! ')

    if not num2:
        num2 = input('Specify the second number! ')

    print('Numbers to be multiplied are: \n n1 = %s \n n2 = %s' %(num1,num2))

    product = karatsuba(int(num1),int(num2))

    print('Final product is %s' %product)


def karatsuba(x, y):

    """ Function to multiply 2 numbers using the Karatsuba 
        multiplication algorithm """


    """ defining the base case """
    if x < 10 or y < 10:
        if args.debug:
            print( ' DEBUG:: in base case -> x*y = %i' %(x*y) )
        return x*y

    else:

        """ actually implementing karatsuba algorithm """

        #finding the biggest size between the two numbers
        n    = max(len(str(x)),len(str(y)))
        #n    = max(int(log10(x)+1), int(log10(y)+1)) -> it's better for very large values?
        
        #check if n is even, otherwise lower it by 1
        if n % 2 !=0:
            n -= 1;
           
        n_2  = int(n / 2)

        if args.debug:
            print( ' DEBUG:: max numbers size n = %i  and n / 2 = %i '%(n,n_2) )

        #a = int( x / 10**(n_2) )
        #b = int( x % 10**(n_2) )
        #c = int( y / 10**(n_2) )
        #d = int( y % 10**(n_2) )
        #replacing above with divmod
        a, b = divmod( x, 10**(n_2) )
        c, d = divmod( y, 10**(n_2) )
        
        if args.debug:
            print( ' DEBUG:: values of \n         a = %i , b = %i , c = %i , d = %i' %(a,b,c,d) )

        ac    = karatsuba( a, c )
        bd    = karatsuba( b, d )
        ad_bc = karatsuba( (a+b),(c+d) ) - ac - bd

        if args.debug:
            print( ''' DEBUG:: values of
         ac    = %i
         bd    = %i
         ad_bc = %i''' %(ac,bd,ad_bc) )
            
            print( ''' DEBUG:: partial values before sum of
         ac*(10**n)        = %i
         (ad_bc*(10**n_2)) = %i
         bd                = %i''' %(ac*(10**n),(ad_bc*(10**n_2)),bd) )
            
        if args.debug:
            print('')
            
        return ( ac*(10**n) + bd + (ad_bc*(10**n_2)) )


if __name__ == "__main__":
    main()    

#!/usr/bin/python3

import os
import argparse
import functools
from math import *


parser = argparse.ArgumentParser(description='Perform Third Grade Multiplication of two integers' )
parser.add_argument('--num1' , type=str           , default=None , help='specify first number'    )
parser.add_argument('--num2' , type=str           , default=None , help='specify second number'   )
parser.add_argument('--debug', action='store_true', default=False, help='enable debug mode'       )
args = parser.parse_args()


def main():

    num1 = args.num1
    num2 = args.num2
    if not num1:
        num1 = input('Specify the first number! ')

    if not num2:
        num2 = input('Specify the second number! ')

    print('Numbers to be multiplied are: \n n1 = %s \n n2 = %s' %(num1,num2))

    product = thirdGrade(int(num1),int(num2))

    print('Final product is %s' %product)


def thirdGrade(x, y):

    """ Function to multiply 2 numbers using the Third Grade 
        multiplication algorithm """


    """ defining the base case """
    if x < 10 or y < 10:
        if args.debug:
            print( ' DEBUG:: in base case -> x*y = %i' %(x*y) )
        return x*y

    """ actually implementing first grade algorithm """
    x, y = str(x), str(y)
    
    products_dN = []
    for i, digit in enumerate(reversed(y)):
        products_dN.append( digit_to_number(digit,x)+ "0"*i )
        if args.debug:
            print( ' DEBUG:: digit_to_number (arranged) -> d *N (%s * %s) = %s' %(digit,x,products_dN[i]) )
    return sum_products(products_dN)
        

def digit_to_number(d, x):

    """ d = single digit, n = n-digits
        return all partial products of d*x """

    prd = ""
    res = ""
    carry  = "0"
    for i, digit in enumerate(reversed(x)):
        part_prd = sum( product(d, digit), carry )
        carry, digit = part_prd[:-1], part_prd[-1]
        if not carry:
            carry = "0"
        prd = digit + prd
    if carry=="0":
        res = prd
    else:
        res = carry + prd

    if args.debug:
        print( ' DEBUG:: digit_to_number -> d *N (%s * %s) = %s' %(d,x,res) )

    return res


def sum_products(products_dN):

    """ partial_prd_digNum is a list of strings
        return the sum of all numbers containined in the strings """

    max_len = max([len(pp) for pp in products_dN])
    for i, md in enumerate(products_dN):
        products_dN[i] = "0" * (max_len - len(md)) + md

    carry = "0"
    res   = ""
    
    for i in range(1, max_len + 1):
        row = [carry] + [md[-i] for md in products_dN]
        if args.debug:
            print(' DEBUG:: i-th row %s ' %row)
        r = functools.reduce(sum, row)
        
        if args.debug:
            print( ' DEBUG:: i-th row (from right)   = %s ' %row )
            print( ' DEBUG:: i-th digit (from right) = %s ' %r   )
            
        carry, digit = r[:-1], r[-1]
        res = digit + res

    return carry + res
    

def product(x, y):

    """ x, y are strings 
        returns a string of x*y """
    return str(eval("%s * %s" % (x, y)))
 
 
def sum(x, y):

    """ x, y are strings 
        returns a string of x+y """
    return str(eval("%s + %s" % (x, y)))


if __name__ == "__main__":
    main()    

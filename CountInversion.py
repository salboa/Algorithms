#!/usr/bin/python3

import os
import argparse

parser = argparse.ArgumentParser(description='Perform Counting Inversion algorithm on unsorted array' )
parser.add_argument('--inFile', type=str           , default=None , help='specify input file'         )
parser.add_argument('--debug' , action='store_true', default=False, help='enable debug mode'          )
args = parser.parse_args()

def main():

    filename = args.inFile
    numlist  = []
    if not filename:
        filename = input(' Specify input file containing unsorted array: ')

    if not os.path.exists(filename):
        print( ' ERROR:: input file %s does not exist!' %filename )
        print( '         Please enter the array manually!' )
        size = int(input('  Type array size: '))
        for i in range(0,size):
            numlist.append(input('  Type an integer: ') )
    else:
        inFile = open(filename, 'r')
        with inFile as f:
            numlist = [int(integers.strip()) for integers in f.readlines()]

    print( ' array has size = %s' %len(numlist) )
    if args.debug:
        print(' DEBUG:: values in the array are  ->  ', numlist)

    sorted, inversions = countingInversion(numlist)
    print( ' number of inversions = %s' %inversions )

def countingInversion(x):

    linv = 0
    rinv = 0
    sinv = 0
    #define middle point of array
    midsection = len(x) // 2

    #define left and right halves
    leftArray  = x[:midsection]
    rightArray = x[midsection:]

    #do not go on if array length is 1
    if len(x) > 1:

        # count left/right inversions in left/right halve
        _ , linv  = countingInversion(leftArray)
        _ , rinv  = countingInversion(rightArray)

        count = linv+rinv
        # count of split inversions
        i, j = 0, 0
        a = leftArray; b = rightArray
        for k in range(len(a) + len(b) + 1):
            if a[i] <= b[j]:
                x[k] = a[i]
                i += 1
                if i == len(a) and j != len(b):
                    while j != len(b):
                        k +=1
                        x[k] = b[j]
                        j += 1
                    break
            elif a[i] > b[j]:
                x[k] = b[j]
                sinv += (len(a) - i)
                j += 1
                if j == len(b) and i != len(a):
                    while i != len(a):
                        k+= 1
                        x[k] = a[i]
                        i += 1                    
                    break

    if args.debug:
        print( 'DEBUG:: left  inversions = %s' %linv )
        print( 'DEBUG:: right inversions = %s' %linv )
        print( 'DEBUG:: split inversions = %s' %linv )
        print( 'DEBUG:: total inversions = %s' %(linv+rinv+sinv) )
        
    return x, linv+rinv+sinv


if __name__ == "__main__":
    main()  

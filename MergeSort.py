#!/usr/bin/python3

import os
import argparse

parser = argparse.ArgumentParser(description='Perform Merge Sort algorithm on unsorted array' )
parser.add_argument('--inFile', type=str           , default=None , help='specify input file' )
parser.add_argument('--debug' , action='store_true', default=False, help='enable debug mode'  )
args = parser.parse_args()


def main():

    filename = args.inFile
    numlist  = []
    if not filename:
        filename = input(' Specify input file containing unsorted array: ')

    if not os.path.exists(filename):
        print(' ERROR:: input file %s does not exist!' %filename)
        print('         Please enter the array manually!')
        size = int(input('  Type array size: '))
        for i in range(0,size):
            numlist.append(input('  Type an integer: ') )
    else:
        inFile = open(filename, 'r')
        with inFile as f:
            numlist = [int(integers.strip()) for integers in f.readlines()]

    if args.debug:
        print(' DEBUG:: values in the array are        -> ', numlist)

    sorted = mergeSort(numlist)
    print(' DEBUG:: values in the sorted array are -> ', sorted)

    
def mergeSort(x):

    #define middle point of array
    midsection = len(x) // 2

    #define left and right halves
    leftArray  = x[:midsection]
    rightArray = x[midsection:]

    #do not go on if array length is 1
    if len(x) > 1:

        # sort left/right halve
        mergeSort(leftArray)
        mergeSort(rightArray)

        #merge halves
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
                j += 1
                if j == len(b) and i != len(a):
                    while i != len(a):
                        k+= 1
                        x[k] = a[i]
                        i += 1                    
                    break

    return x


if __name__ == "__main__":
    main()  

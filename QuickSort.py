#!/usr/bin/python3

import os
import argparse
from random import randint

parser = argparse.ArgumentParser(description='Perform Quick Sort algorithm on unsorted array'           )
parser.add_argument('--inFile'  , type=str           , default=None , help='specify input file'         )
parser.add_argument('--pivFirst', action='store_true', default=False, help='use first element as pivot' )
parser.add_argument('--pivLast' , action='store_true', default=False, help='use last element as pivot'  )
parser.add_argument('--pivMed'  , action='store_true', default=False, help='use median element as pivot')
parser.add_argument('--pivRand' , action='store_true', default=False, help='use random element as pivot')
parser.add_argument('--debug'   , action='store_true', default=False, help='enable debug mode'          )
args = parser.parse_args()
rand = lambda arr, l, r: randint(l, r) 

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

    if( not     args.pivFirst and not args.pivLast
        and not args.pivMed   and not args.pivRand):
        print( ' ERROR:: pivot choice not define!!' )
        print( '         Please make a choice:' )
        print( '         pivFirst -> type 1 , pivLast -> type 2 ' )
        print( '         pivMed   -> type 3 , pivRand -> type 4 ' )
        choice = int( input( ' Type pivot choice: ' ) )
        if choice==1:
            args.pivFirst = True
            print( '         using first element as pivot!' )
        elif choice==2:
            args.pivLast  = True
            print( '         using first element as pivot!' )
        elif choice==3:
            args.pivMed   = True
            print( '         using median element as pivot!' )
        elif choice==4:
            args.pivRand  = True
            print( '         using random element as pivot!' )
        else:
            print( '          invalid selection! Exiting' )
            exit(0);

    count = Counter()
    pivotChoice = choosePivot()
    print( ' DEBUG:: pivot choice is %s' %pivotChoice.__name__ )
    quickSort(numlist, count=count, pivot=pivotChoice)
    print( ' %s as pivot -> number of comparisons = %s '%(pivotChoice.__name__,count.total) )


def choosePivot():

    pivot = None
    
    if args.pivFirst:
        pivot = firstElement
        
    elif args.pivLast:
        pivot = lastElement
        
    elif args.pivMed:
        pivot = medianElement
        
    elif args.pivRand:
        pivot = randomElement

    return pivot

            
def partitioning(array, left, right, pos, count=None):

    #value of pivot element
    pivot = array[pos];

    #swap pivot with the leftmost element
    array[left], array[pos] = array[pos], array[left]

    #start iteration after the pivot (leftmost element)
    pos = left+1
    for j in range(pos, right+1):
        if count:
            count(1)

        #move element on the left
        if array[j] < pivot:
            array[j], array[pos] = array[pos], array[j]
            pos += 1                               
    pos -= 1

    # move pivot to the last position on the left
    array[left], array[pos] = array[pos], array[left]

    return pos


def quickSort(array, left=0, right=None, count=None, pivot=None):

    # if right boundary not defined, define it as ArraySize-1
    if right is None:
        right = len(array)-1
    
    # base case: return if size 0
    if right-left < 1: return

    #choose pivot
    p = pivot(array, left, right)
    if args.debug:
        print( ' DEBUG:: left / right / pivot positions %s / %s / %s -> pivot value = %s' %(left,right,p,array[p]) )
    
    #do partitioning around pivot
    p = partitioning(array, left, right, p, count)
    
    #sort left and right halves
    quickSort(array, left, p-1  , count, pivot)
    quickSort(array, p+1 , right, count, pivot)

        
class Counter:

    ''' counter class: used for counting the number of comparisons made by quicksort '''

    def __init__(self, n=0):
        self.total = n

    def __call__(self, x=0):
        self.total += x


''' below function defing the pivot choices '''

def firstElement(array, left, right):
    ''' returning first element of the array '''
    return left

def lastElement(array, left, right):
    ''' returning last element of the array '''
    return right

def medianElement(array, left, right):
    ''' returning median element between left, right and median '''
    
    #defining middle point
    middle = None
    if right-left == 1:
        middle = 0
    else:
        middle = ((right-left)/2) + left

    Mel = array[middle]
    Lel = array[left]
    Rel = array[right]
    ordered = sorted( [(Lel,left), (Mel,middle), (Rel,right)] )

    #return the index of the median value of the three
    return ordered[1][1]


def randomElement(array, left, right):
    ''' returning random element of the array '''
    return randint(left, right)

    
if __name__ == "__main__":
    main()

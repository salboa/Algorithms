CXX = clang++
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
   CXX = g++
endif

CXXFLAGS = -O3 -Wall -fPIC -std=c++0x

#Objects
KS_OBJ = Karatsuba.o
MS_OBJ = MergeSort.o
CI_OBJ = CountInversion.o

#Build
all: kara mrgs cinv

kara:	$(KS_OBJ)
	@echo ""
	@echo "Compiling objects ($(KS_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(KS_OBJ) -o Karatsuba -g $(LIBS)

mrgs:   $(MS_OBJ)
	@echo ""
	@echo "Compiling objects ($(MS_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(MS_OBJ) -o MergeSort -g $(LIBS)

cinv:   $(CI_OBJ)
	@echo ""
	@echo "Compiling objects ($(CI_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(CI_OBJ) -o CountInversion -g $(LIBS)

## Clean
clean:
	@echo "Cleaning path ... "
	rm -rf *.o
	rm -rf Karatsuba
	rm -rf MergeSort
	rm -rf CountInversion
	rm -rf *~

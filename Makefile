CXX = clang++
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
   CXX = g++
endif

CXXFLAGS = -O3 -Wall -fPIC -std=c++0x

#Karatsuba algortithm
KS_OBJ  = Karatsuba.o

#Build
all: kara

kara:	$(KS_OBJ)
	@echo ""
	@echo "Compiling objects ($(KS_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(KS_OBJ) -o Karatsuba -g $(LIBS)

## Clean
clean:
	@echo "Cleaning path ... "
	rm -rf *.o
	rm -rf Karatsuba
	rm -rf *~

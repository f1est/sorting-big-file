CFLAGS 		=--std=c++11
CXX 		=g++
LIBS 		=-lstdc++

SOURCES0    =0_generate_double_digits.cpp
SOURCES1    =1_sort.cpp

0_GENERATOR	=0_generator
1_SORTER	=1_sorter

all:  $(0_GENERATOR) $(1_SORTER) 

0_generator:
$(0_GENERATOR):
	$(CXX) $(CFLAGS) -o $@ $(SOURCES0) $(LIBS) 

1_sorter:
$(1_SORTER):
	$(CXX) $(CFLAGS) -o $@ $(SOURCES1) $(LIBS) 


.PHONY: clean

clean: 
	rm -f 0_generator
	rm -f 1_sorter
	rm -f unsorted_double.txt
	rm -f sorted*

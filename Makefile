INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -g -I$(INCLUDE_DIRS) 


OBJS 		 := customErrorClass.o avl_binarySearchTree.o main.o 
DEPS 		 := ${INCLUDE_DIRS}/customErrorClass.h avl_binarySearchTree.h

.PHONY: clean all

all: Johnson_Assignment3 customErrorClass.o avl_binarySearchTree.o main.o


clean:
	rm $(OBJS) Johnson_Assignment3

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

avl_binarySearchTree.o: avl_binarySearchTree.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

main.o: main.cpp
	$(CC) -c -o $@ $(CFLAGS) $<

Johnson_Assignment3: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
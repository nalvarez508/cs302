OBJS	= sortDriver.o bubbleSort.o mergeSort.o
SOURCE	= sortDriver.cpp bubbleSort.cpp mergeSort.cpp
HEADER	= bubbleSort.h mergeSort.h
OUT	= sortDriver
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

sortDriver.o: sortDriver.cpp
	$(CC) $(FLAGS) sortDriver.cpp 

bubbleSort.o: bubbleSort.cpp
	$(CC) $(FLAGS) bubbleSort.cpp 

mergeSort.o: mergeSort.cpp
	$(CC) $(FLAGS) mergeSort.cpp 


clean:
	rm -f $(OBJS) $(OUT)
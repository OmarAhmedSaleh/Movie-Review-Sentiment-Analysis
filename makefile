CXX = g++

TARGET = main
OBJ = WordEntry.o HashTable.o main.o

$(TARGET):$(OBJ)
		$(CXX) -o $(TARGET) $(OBJ)
		rm -rf $(OBJ)


WordEntry.o:
	$(CXX) -c WordEntry.cpp

HashTable.o:
	$(CXX) -c HashTable.cpp
	
main.o:
	$(CXX) -c main.cpp
	
clean:
	rm -rf $(OBJ) $(TARGET)
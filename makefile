
SRC = src
INC = include
OBJ = obj
BIN = bin
LIB = lib

CXX = g++
CPPFLAGS = -Wall -g -I$(INC)


all: $(BIN)/arteASCII $(BIN)/testarteASCII $(BIN)/testplano $(BIN)/testimagen

$(BIN)/testplano: $(SRC)/testplano.cpp $(LIB)/libimagen.a 
	$(CXX) $(CPPFLAGS) $(SRC)/testplano.cpp $(LIB)/libimagen.a $(OBJ)/byte.o -o $(BIN)/testplano

$(BIN)/testarteASCII: $(SRC)/testarteASCII.cpp $(LIB)/libimagen.a 
	$(CXX) $(CPPFLAGS) $(SRC)/testarteASCII.cpp $(LIB)/libimagen.a $(OBJ)/byte.o -o $(BIN)/testarteASCII

$(BIN)/arteASCII: $(SRC)/arteASCII.cpp $(LIB)/libimagen.a 
	$(CXX) $(CPPFLAGS) $(SRC)/arteASCII.cpp $(LIB)/libimagen.a $(OBJ)/byte.o -o $(BIN)/arteASCII

$(BIN)/testimagen: $(SRC)/testimagen.cpp $(LIB)/libimagen.a
	$(CXX) $(CPPFLAGS) $(SRC)/testimagen.cpp $(LIB)/libimagen.a $(OBJ)/byte.o -o $(BIN)/testimagen

$(LIB)/libimagen.a : $(OBJ)/pgm.o $(OBJ)/imagen.o $(SRC)/imagen.cpp
	ar rvs $(LIB)/libimagen.a $(OBJ)/pgm.o $(OBJ)/imagen.o

$(OBJ)/imagen.o : $(INC)/imagen.h $(SRC)/imagen.cpp $(OBJ)/byte.o $(OBJ)/pgm.o
	$(CXX) -c $(CPPFLAGS) $(SRC)/imagen.cpp -o $(OBJ)/imagen.o

$(OBJ)/pgm.o : $(INC)/pgm.h $(SRC)/pgm.cpp
	$(CXX) -c $(CPPFLAGS) $(SRC)/pgm.cpp -o $(OBJ)/pgm.o

$(OBJ)/byte.o : $(INC)/byte.h $(SRC)/byte.cpp
	$(CXX) -c $(CPPFLAGS) $(SRC)/byte.cpp -o $(OBJ)/byte.o


# ************ documentación *******

documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Limpieza ************

clean:
	rm $(OBJ)/* $(BIN)/* $(LIB)/*
	

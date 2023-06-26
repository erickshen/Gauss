all: Gauss

Gauss: main.o ErrorNorm.o MatrixNorm.o MatrixInput.o MatrixOutput.o Function.o Gauss.o
	g++ main.o ErrorNorm.o MatrixNorm.o MatrixInput.o MatrixOutput.o Function.o Gauss.o -o Gauss

main.o: main.cpp
	g++ -c main.cpp -O3

ErrorNorm.o: ErrorNorm.cpp
	g++ -c ErrorNorm.cpp -O3

MatrixNorm.o: MatrixNorm.cpp
	g++ -c MatrixNorm.cpp -O3

MatrixInput.o: MatrixInput.cpp
	g++ -c MatrixInput.cpp -O3

MatrixOutput.o: MatrixOutput.cpp
	g++ -c MatrixOutput.cpp -O3

Function.o: Function.cpp
	g++ -c Function.cpp -O3

Gauss.o: Gauss.cpp
	g++ -c Gauss.cpp -O3

clean: 
	rm -rf *.o Gauss

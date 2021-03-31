all: simulator_Q1 simulator_Q2
simulator_Q1: simulator.o maxHeap1.o
	g++ simulator.o maxHeap1.o -o simulator_Q1

simulator_Q2: simulator2.o maxHeap2.o
	g++ simulator2.o maxHeap2.o -o simulator_Q2


simulator.o: simulator.cpp
	g++ -c simulator.cpp


maxHeap1.o: maxHeap1.cpp maxHeap1.h
	g++ -c maxHeap1.cpp

simulator2.o: simulator2.cpp
	g++ -c simulator2.cpp


maxHeap2.o: maxHeap2.cpp maxHeap2.h
	g++ -c maxHeap2.cpp


	

clean:
	rm *.o simulator_Q1
	rm *.o simulator_Q2
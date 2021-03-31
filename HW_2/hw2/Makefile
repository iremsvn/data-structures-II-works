hw2: hw2_202.o DecisionTreeNode.o DecisionTree.o
	g++ hw2_202.o DecisionTreeNode.o DecisionTree.o -o hw2


hw2_202.o: hw2_202.cpp
	g++ -c hw2_202.cpp



DecisionTreeNode.o: DecisionTreeNode.cpp DecisionTreeNode.h
	g++ -c DecisionTreeNode.cpp

DecisionTree.o: DecisionTree.cpp DecisionTree.h
	g++ -c DecisionTree.cpp
clean:
	rm *.o hw2
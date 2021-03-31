/*
*irem seven
*21734269
*Section1
*Assigment 4
*/

#include <iostream>
#include "HashTable.h"
using namespace std;



int main()
{
	double sucProb = 0;
	double unsucProb = 0;

	cout << "***LINEAR***" << endl;
	HashTable h(17, LINEAR);	
	h.parseText("tableData.txt");
	cout << endl;
	h.display();
	h.analyze(sucProb, unsucProb);
	cout << "Avg no of successful probes: " << sucProb << endl;
	cout << "Avg no of unsuccessful probes: " << unsucProb << endl;

	cout << endl;
	cout << "***QUADRATIC***" << endl;
	HashTable h2(17, QUADRACTIC);
	h2.parseText("tableData.txt");
	cout << endl;
	h2.display();
	h2.analyze(sucProb, unsucProb);
	cout << "Avg no of successful probes: " << sucProb << endl;
	cout << "Avg no of unsuccessful probes: " << unsucProb << endl;


	cout << endl;
	cout << "***DOUBLE***" << endl;
	HashTable h3(17, DOUBLE);
	h3.parseText("tableData.txt");
	cout << endl;
	h3.display();
	h3.analyze(sucProb, unsucProb);
	cout << "Avg no of successful probes: " << sucProb << endl;
	cout << "Avg no of unsuccessful probes: " << unsucProb << endl;

	return 0;
}

#pragma once
#include <iostream>
#include <cstddef>
#include <string>
#include <fstream>

class Heap {

	struct Patient {
		int id;
		int priority;
		int arrivalTime;
		int serviceTime;
		int assignedTime;
		int doctorId;
	};

	struct Doctor {
		Patient patient;
		bool avaible = true;
	};


public:
	Heap();

	bool heapIsEmpty() const;
	void heapInsert(const Patient& newPatient);
	void heapDelete(Patient& patient);

	Patient createPatient(int id, int priority, int arrival, int service);
	void printData(Patient* patients, int size);

	void parseText(std::string fileName, int avgMax);
	double avgWaitingForMinDoctors(Patient* patients, int avgMax);
	double calculateAvgWaiting(Patient* patients, int doneSize, int doctorNum);
	void simulate(Patient* patients, int& doctorNum);

protected:
	void heapRebuild(int root);

private:
	Patient* patients;
	Patient* arr; //parsed input used as temp
	Patient* donePatients; //used for printing final state
	Doctor* doctors;
	int size; //for heap
	int time;
	int examinedNum; //for donePatients
	int patientNum;  //total patients
	int limitSize;
};


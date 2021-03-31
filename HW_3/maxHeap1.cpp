#include "maxHeap1.h"
using namespace std;

Heap::Heap() :time(0), size(0), patientNum(0), examinedNum(0){

}

bool Heap::heapIsEmpty() const {
	return (size == 0);
}

void Heap::heapInsert(const Heap::Patient& newPatient) {
	if (size >= MAX_HEAP) {
		cout << "Cannot Take any Patients" << endl;
		return;
	}
	patients[size] = newPatient;

	int place = size;
	int parent = (place - 1) / 2;
	while ((place > 0) && (patients[place].priority) > (patients[parent].priority)) {	
		Patient temp = patients[parent];
		patients[parent] = patients[place];
		patients[place] = temp;

		place = parent;
		parent = (place - 1) / 2;
	}
	++size;
}

void Heap::heapDelete(Patient& patient) {
	if (heapIsEmpty()) {
		cout << "No Patients Exist" << endl;
		return;
	}

	patient = patients[0];
	patients[0] = patients[--size];
	heapRebuild(0);
}

Heap::Patient Heap::createPatient(int id, int priority, int arrival, int service) {

	Patient patient;
	patient.id = id;
	patient.priority = priority;
	patient.arrivalTime = arrival;
	patient.serviceTime = service;
	patient.assignedTime = 0;
	patient.doctorId = -1;
	return patient;
}

void Heap::heapRebuild(int root) {
	int child = 2 * root + 1; //left child index
	if (child < size) {
		int rightChild = child + 1; //if any right child index
		if ((rightChild < size) && (patients[rightChild].priority > patients[child].priority)) {
			if (patients[rightChild].priority == patients[child].priority) {
				if ((patients[rightChild].arrivalTime < patients[child].arrivalTime))
					child = rightChild; // fix right child as child, to be swapped
			}
			else
				child = rightChild;
		}
		if (patients[root].priority <= patients[child].priority) {
			if (patients[root].priority == patients[child].priority) {
				if (patients[root].arrivalTime > patients[child].arrivalTime) {
					Patient temp = patients[root];
					patients[root] = patients[child];
					patients[child] = temp;
				}
			}
			else {
				Patient temp = patients[root];
				patients[root] = patients[child];
				patients[child] = temp;
			}
			
		}
		heapRebuild(child);
	}
}

void Heap::printData(Patient* patients, int size) {
	if (size == 0) {
		cout << "No Patients to Display" << endl;
		return;
	}
	for (int i = 0; i < size; i++) {
		int waitingMin = donePatients[i].assignedTime - donePatients[i].arrivalTime;
		cout << "Doctor " << donePatients[i].doctorId << " takes patient " << donePatients[i].id << " at minute " << donePatients[i].assignedTime << " (wait: " << waitingMin << " mins)" << endl;
	}
	cout << "************" << endl;
}
double Heap::calculateAvgWaiting(Heap::Patient* patients, int patientNum, int doctorNum) {
	double avg = 0;
	for (int i = 0; i < patientNum; i++) {
		double waitingTime = double(patients[i].assignedTime) - patients[i].arrivalTime;
		avg += waitingTime;
	}
	return (avg / patientNum);
}



double Heap::avgWaitingForMinDoctors(Patient* patientsArr, int avgMax) {
	int doctorNum = 0;
	double avgWait = 0;
	donePatients = new Patient[patientNum];
	do {
		doctorNum++;
		doctors = new Doctor[doctorNum];
		simulate(patientsArr, doctorNum);
		avgWait = calculateAvgWaiting(donePatients, patientNum, doctorNum);
		delete[] doctors;
		doctors = NULL;
	} while (avgWait > avgMax && doctorNum < patientNum);

	cout << "Minimum number of doctors required: " << doctorNum << endl;
	cout << "\nSimulation with " << doctorNum << " doctors:\n" << endl;
	return avgWait;
}


void Heap::simulate(Patient* patientsArr, int& doctorNum) {
	examinedNum = 0;
	int index = 0;
	time = 1;
	examinedNum = 0;
	while (examinedNum < patientNum ) {
		while (time == patientsArr[index].arrivalTime && index < patientNum) {
			heapInsert(patientsArr[index]);
			index++;
		}
		//assignDoctors
		for (int i = 0; i < doctorNum; i++) {
			 if ((heapIsEmpty() == false) && (doctors[i].avaible == true)) {
				heapDelete(doctors[i].patient);
				doctors[i].patient.assignedTime = time;
				doctors[i].patient.doctorId = i;
				donePatients[examinedNum] = doctors[i].patient; //add to final patients array
				examinedNum++;
				doctors[i].avaible = false;
			}

			//update doctors avaiblity
			else if (doctors[i].avaible == false) {
				if ((doctors[i].patient.serviceTime + doctors[i].patient.assignedTime) == time + 1) {
					doctors[i].avaible = true;
				}
			}

		}
		time++;
	}
}


void Heap::parseText(string fileName, int avgMax) {
	ifstream inputFileStream(fileName.c_str());

	inputFileStream >> patientNum;
	arr = new Patient[patientNum];
	int row = 0;
	int readId, readPriority, readArrivalTime, readServiceTime;
	while (row < patientNum) {
			inputFileStream >> readId;
			inputFileStream >> readPriority;
			inputFileStream >> readArrivalTime;
			inputFileStream >> readServiceTime;
			arr[row] = createPatient(readId, readPriority, readArrivalTime, readServiceTime);
			row++;
		}

	double avg = avgWaitingForMinDoctors(arr, avgMax);
	printData(donePatients, patientNum);
	cout << "\nAverage Waiting time: " << avg << " minutes" << endl;
	delete[] arr;
}
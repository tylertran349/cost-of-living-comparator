#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// Prototype
double calcComp(double, double, double, double, double, double);

int main() {
	// Declare variables
	double groceries, housing, utilities, transportation, health, misc, compositeIndex, lowestIndex, highestIndex;
	lowestIndex = 0.0;
	highestIndex = 0.0;
	string stateName, lowestState, highestState;
	char newline = '\n';
	
	// Open file for input
	ifstream fileInput;
	fileInput.open("StateCOL.txt");
	
	// Create/open file for output
	ofstream fileOutput;
	fileOutput.open("Cost of Living Data Output.txt");
	
	// Check if input file exists - if file does not exist, terminate the program
	if(fileInput.fail()) {
		cout << "No such file exists" << endl;
		system("pause");
		exit(100);
	}
	
	fileOutput << "State                                       Composite Index" << endl;
	
	while(!fileInput.eof()) {
		// Input state name and all 6 values associated with the state
		getline(fileInput, stateName);
		fileInput >> groceries >> housing >> utilities >> transportation >> health >> misc;
		
		// Ignore newlines
		fileInput.get(newline);
		
		// Perform calculations
		compositeIndex = calcComp(groceries, housing, utilities, transportation, health, misc);
		if(lowestIndex == 0.0 && highestIndex == 0.0) {
			lowestIndex = compositeIndex;
			highestIndex = compositeIndex;
			lowestState = stateName;
			highestState = stateName;
		}
		if(compositeIndex > highestIndex) {
			highestIndex = compositeIndex;
			highestState = stateName;
		}
		if(compositeIndex < lowestIndex) {
			lowestIndex = compositeIndex;
			lowestState = stateName;
		}
		
		// Output each state name and composite index for each state to file
		fileOutput << setprecision(1) << fixed;
		fileOutput << setw(21) << left << stateName << setw(30) << right << compositeIndex << endl;
	}
	
	// Output lowest index state and highest index state to screen
	cout << setprecision(1) << fixed;
	cout << "State with highest composite index: " << highestState << "- " << highestIndex << endl;
	cout << "State with lowest composite index: " << lowestState << "- " << lowestIndex << endl;
	
	// Output state with highest/lowest composite index and their respective indexes to file
	fileOutput << endl;
	fileOutput << "State with highest composite index: " << highestState << "- " << highestIndex << endl;
	fileOutput << "State with lowest composite index: " << lowestState << "- " << lowestIndex << endl;
	
	// Close input file and output file
	fileOutput.close();
	fileInput.close();
}

double calcComp(double groceries, double housing, double utilities, double transportation, double health, double misc) {
	return ((0.15 * groceries) + (0.29 * housing) + (0.10 * utilities) + (0.11 * transportation) + (0.12 * health) + (0.23 * misc));
}

#include <cstdlib>

#include <iostream>
#include <string>
#include <fstream>
#include "Circuit.h"

using namespace std;

int main() {

	//get schematic file from user
	string fileName;
	GETFILE://label to come back to
	cout << "Please enter a file to read a schematic from: ";
	getline(cin, fileName);
	
	//create input stream and begin looping through file
	ifstream schematic(fileName.c_str());

	//check if file opened
	if (!schematic.is_open()) {
		cout << "Unable to open file.\n\n";
		goto GETFILE;
	}

	//init vars to pull from file
	string parseln, ele;
	int src, dest, resistance;
	
	//get # nodes (first line in file) and feed into circuit constructor
	getline(schematic, parseln);
	Circuit myCircuit(atoi(parseln.c_str()));

	//loop until no longer able to get input
		//each line of input is 1 wire
	getline(schematic, parseln);
	while (!schematic.fail()) {
			
		cout << "\nCreating wire: " << parseln;

		//get src node
		ele = parseln.substr(0, parseln.find("-"));
		src = atoi(ele.c_str());

		//get dest node
		ele = parseln.substr(parseln.find("-")+1, parseln.find("("));
		dest = atoi(ele.c_str());

		//get resistance between nodes
		ele = parseln.substr(parseln.find("(") + 1, parseln.find(")"));
		resistance = atoi(ele.c_str());

		//create specified wire
		myCircuit.wireJunctions(src, dest, resistance);

		//get next line
		getline(schematic, parseln);
	}

	//close input file
	schematic.close();

	//output resulting circuit data
	cout << "\n\nThe total resistance of the specified schematic is: "
		 << myCircuit.calcResistance() << " Ohms.\n";
		
	system("pause");
	return 0;

}
#ifndef CIRCUIT_H
#define	CIRCUIT_H

#include <vector>
#include "Junction.h"
#include "Wire.h"

using namespace std;

//~~~used to make recursion easier~~~
struct CollisionResult {
	double resistance;
	Junction* collisionNode;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Circuit {

private:
	//list of junctions in the circuit
	vector<Junction*> junctions;

	//recursively calculate the resistance of the circuit
	double calcTotalResistance(Junction* relativeRoot);
	CollisionResult calcEqResistance(Junction* relativeRoot);

public:
	//***no direct getters and setters to maximize encapsulation***

	//constructor
	Circuit(int size);

	//set junction as null or battery
	void setGain(int junction, double voltage);

	//create a wire between two junctions
	void wireJunctions(int srcJunction, int destJunction, double resistance);

	//indirectly call the recursive calc resistance method
	double calcResistance();
	
};
#endif // !CIRCUIT_H
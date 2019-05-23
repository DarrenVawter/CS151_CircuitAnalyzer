#include "Circuit.h"

Circuit::Circuit(int size) {
	for (int i = 0; i < size; i++) {
		junctions.push_back(new Junction(i));
	}
}

void Circuit::setGain(int junction, double voltage) {
	if (junction < junctions.size()) {
		junctions.at(junction)->setVoltage(voltage);
	}
	else {
		//TODO: handle error
	}
}

void Circuit::wireJunctions(int srcJunction, int destJunction, double resistance) {
	//check valid wire
	if (srcJunction < junctions.size() && destJunction < junctions.size() && resistance > 0) {
		//create connection
		Wire* w = new Wire(junctions.at(srcJunction), junctions.at(destJunction), resistance);
		junctions.at(srcJunction)->addConnection(w);
	}
	else {
		//TODO: handle error
	}
}

double Circuit::calcResistance() {
	return calcTotalResistance(junctions.at(0));
}

double Circuit::calcTotalResistance(Junction* relativeRoot) {

	vector<Wire*> forwardConnections = relativeRoot->getForwardConnections();
	int nForwardConnections = forwardConnections.size();
	
	//check # of possible traversals from current node and act accordingly
		//if only 1 --> add resistance and continue on
		//if > 1 --> calc parallel resistance and continue on
		//if < 1 --> handle error
	if (nForwardConnections < 1) {
		//TODO: throw error
	}
	else if (nForwardConnections == 1) {
		if (forwardConnections.at(0)->getDest()!=junctions.at(0)) {
			return forwardConnections.at(0)->getResistance() + calcTotalResistance(forwardConnections.at(0)->getDest());
		}
		else {
			return forwardConnections.at(0)->getResistance();
		}
	}
	else {
		CollisionResult cr = calcEqResistance(relativeRoot);
		return cr.resistance + calcTotalResistance(cr.collisionNode);
	}
}

CollisionResult Circuit::calcEqResistance(Junction* relativeRoot) {

	vector<Wire*> forwardConnections = relativeRoot->getForwardConnections();
	int nForwardConnections = forwardConnections.size();

	//init values to calculate parallel resistance
	double tR = 0.0;
	double* resistance = new double[nForwardConnections];
	Junction** nodes = new Junction*[nForwardConnections];

	//init path resistances and node traversal points
	for (int i = 0; i < nForwardConnections; i++) {
		resistance[i] = forwardConnections.at(i)->getResistance();
		nodes[i] = forwardConnections.at(i)->getDest();
	}

	//detect the point where the parallel paths collide
	bool collided = false;
	while (!collided) {

		//find min of currently traversed nodes
		int minID = INT_MAX;
		int minIndex = -1;
		for (int i = 0; i < nForwardConnections; i++) {
			if (nodes[i]->getID() < minID) {
				minID = nodes[i]->getID();
				minIndex = i;
			}
		}

		//check # of possible traversals from smallest node and act accordingly
			//if>1, find eqResistance from node to next collision
			//if==1, add line resistance and move path down
			//if<1, handle error
		if (nodes[minIndex]->getForwardConnections().size() > 1) {
			CollisionResult cr = calcEqResistance(nodes[minIndex]);//get CR
			resistance[minIndex] += cr.resistance;//adding eq resistance from this node to it's next collision
			nodes[minIndex] = cr.collisionNode;//set current path node to node of collision
		}
		else if(nodes[minIndex]->getForwardConnections().size() == 1){
			resistance[minIndex] += nodes[minIndex]->getForwardConnections().at(0)->getResistance();//adding next line resistance
			nodes[minIndex] = nodes[minIndex]->getForwardConnections().at(0)->getDest();//set current path node to next node
		}
		else {
			//TODO: handle error
		}

		//check if all nodes have now collided
		collided = true;
		for (int i = 1; i < nForwardConnections; i++) {
			if (nodes[i] != nodes[0]) {
				collided = false;
				break;
			}
		}

		//if all nodes have collided, calculate and return the resistance
		if (collided) {
			for (int i = 0; i < nForwardConnections; i++) {
				tR += 1.0 / resistance[i];
			}
			tR = 1 / tR;
		}

	}

	
	//generate collision result
	CollisionResult cr;
	cr.collisionNode = nodes[0];
	cr.resistance = tR;

	//delete dangling pointers before returning
	delete[] resistance;
	delete[] nodes;
	return cr;

}
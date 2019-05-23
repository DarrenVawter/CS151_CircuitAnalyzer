#ifndef JUNCTION_H
#define JUNCTION_H

#include <vector>

using namespace std;

class Wire;

class Junction {

	private:	
		//vector-list of wires moving away from this node
		vector<Wire*> connections;
		//voltage gain of this node
		double voltage;
		//id of node
		int id;
		
	public:
		//constructor
		Junction(int id, double voltage = 0.0);
		//getters
		inline bool isBattery() { return (voltage==0.0?true:false); }
		inline double getVoltage() { return voltage; }
		inline int getID() { return id; }
		inline vector<Wire*> getForwardConnections() { return connections; }
		//setters
		inline void setVoltage(double voltage) { this->voltage = voltage; }
		inline void setID(int id) { this->id = id; }
		inline void addConnection(Wire* w) { connections.push_back(w); }
};
#endif // !JUNCTION_H
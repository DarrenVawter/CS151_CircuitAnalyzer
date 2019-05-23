#ifndef WIRE_H
#define	WIRE_H

class Junction;

class Wire {

	private:
		//trailing junction
		Junction* src;
		//leading junctions
		Junction* dest;
		//resistance of this wire
		double resistance;
		/*
		double capacitance;
		double inductance;
		*/

	public:
		//constructor
		Wire(Junction* src, Junction* dest, double resistance);
		//getters
		inline Junction* getSrc() { return src; }
		inline Junction* getDest() { return dest; }
		inline double getResistance() { return resistance; }
		/*
		inline double getCapacitance() { return capacitance; }
		inline double getInductance() { return inductance; }
		*/
		//setters
		inline void setSrc(Junction* src) { this->src = src; }
		inline void setDest(Junction* dest) { this->dest = dest; }
		inline void setResistance(double resistance) { this->resistance=resistance; }
		/*
		inline void setCapacitance() { this->capacitance=capacitance; }
		inline void setInductance() { this->inductance=inductance; }
		*/


};
#endif // !WIRE_H
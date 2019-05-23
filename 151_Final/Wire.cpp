#include "Wire.h"

Wire::Wire(Junction* src, Junction* dest, double resistance) {
	this->src = src;
	this->dest = dest;
	this->resistance = resistance;
}
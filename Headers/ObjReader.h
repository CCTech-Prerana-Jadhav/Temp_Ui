#pragma once
#include <string> 
#include "Triangulation.h"
#include "Reader.h"

class ObjReader : public Reader
{
public:
	ObjReader();
	~ObjReader();

	void read(const std::string& fileName, Triangulation& triangulation);

	bool operator()(double a, double b) const;
};

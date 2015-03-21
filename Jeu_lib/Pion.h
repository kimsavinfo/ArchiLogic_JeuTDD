#pragma once

#include <string>
using namespace std;

#include "IRepresentation.h"

class Pion : public IRepresentation
{
	public:
		Pion(string _forme);
		~Pion(void);

		virtual string getRepresentation();
		long getId();

	protected:
		long id;
		string representation;
};


#pragma once
#include <string>
using namespace std;

#include "IRepresentation.h"

class Case  : public IRepresentation
{
	public:
		Case(void);
		~Case(void);

		int getLargeur();
		bool isVide();

		long getId();
		virtual string getRepresentation();
		long getIdOccupant();
		void setIdOccupant(long _idOccupant);

	private:
		long id;
		long idOccupant;
};


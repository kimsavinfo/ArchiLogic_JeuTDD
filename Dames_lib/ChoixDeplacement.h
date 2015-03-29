#pragma once

#include <vector>
using namespace std;

#include "IRepresentation.h"

class ChoixDeplacement : public IRepresentation
{
	public:
		ChoixDeplacement(int _ligneArrivee, int _colonneArrivee, vector<long> _pionsManges);
		~ChoixDeplacement(void);

		int getLigneArrivee();
		int getColonneArrivee();
		vector<long> getPionsManges();
		virtual string getRepresentation();

	private:
		int ligneArrivee;
		int colonneArrivee;
		vector<long> pionsManges;
};


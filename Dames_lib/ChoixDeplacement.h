#pragma once

#include <vector>
using namespace std;

class ChoixDeplacement
{
	public:
		ChoixDeplacement(int _ligneArrivee, int _colonneArrivee, vector<long> _pionsManges);
		~ChoixDeplacement(void);

		int getLigneArrivee();
		int getColonneArrivee();
		vector<long> getPionsManges();

	private:
		int ligneArrivee;
		int colonneArrivee;
		vector<long> pionsManges;
};


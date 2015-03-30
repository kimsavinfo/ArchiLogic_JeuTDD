#include "stdafx.h"
#include "ChoixDeplacement.h"


ChoixDeplacement::ChoixDeplacement(int _ligneArrivee, int _colonneArrivee, vector<long> _pionsManges)
{
	ligneArrivee = _ligneArrivee;
	colonneArrivee = _colonneArrivee;
	pionsManges = _pionsManges;
}

int ChoixDeplacement::getLigneArrivee()
{
	return ligneArrivee;
}

int ChoixDeplacement::getColonneArrivee()
{
	return colonneArrivee;
}

vector<long> ChoixDeplacement::getPionsManges()
{
	return pionsManges;
}

string ChoixDeplacement::getRepresentation()
{
	return "["+ to_string(ligneArrivee + 1) + ";" + to_string(colonneArrivee + 1) + "] "
		+ " = " + to_string(pionsManges.size()) + " pion mange(s).";
}


ChoixDeplacement::~ChoixDeplacement(void)
{
}

#include "stdafx.h"
#include "DriverGrille.h"


DriverGrille::DriverGrille(int _nbLignes, int _nbColonnes)
{
	grille = new Grille(_nbLignes, _nbColonnes);
	partieFinie = false;
	egalite = false;
}

Grille * DriverGrille::getGrille()
{
	return grille;
}

bool DriverGrille::isPartieFinie()
{
	return partieFinie;
}
bool DriverGrille::isEgalite()
{
	return egalite;
}

DriverGrille::~DriverGrille(void)
{
	delete grille;
}

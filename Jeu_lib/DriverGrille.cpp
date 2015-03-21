#include "stdafx.h"
#include "DriverGrille.h"


DriverGrille::DriverGrille(int _nbLignes, int _nbColonnes)
{
	grille = new Grille(_nbLignes, _nbColonnes);
}

Grille * DriverGrille::getGrille()
{
	return grille;
}

DriverGrille::~DriverGrille(void)
{
	delete grille;
}

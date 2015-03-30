#include "stdafx.h"
#include "DriverGrille.h"


DriverGrille::DriverGrille(int _nbLignes, int _nbColonnes)
{
	grille = new Grille(_nbLignes, _nbColonnes);
	partieFinie = false;
	egalite = false;
}

int DriverGrille::getGrilleNbLignes()
{
	return grille->getNbLignes();
}

int DriverGrille::getGrilleNbColonnes()
{
	return grille->getNbColonnes();
}

string DriverGrille::getCaseRepresentation(int _iLigne, int _iColonne)
{
	return grille->getCaseRepresentation(_iLigne, _iColonne);
}

long DriverGrille::getCaseIdOccupant(int _iLigne, int _iColonne)
{
	return grille->getCaseIdOccupant(_iLigne, _iColonne);
}

bool DriverGrille::isPartieFinie()
{
	return partieFinie;
}
bool DriverGrille::isEgalite()
{
	return egalite;
}

void DriverGrille::poserPion(long _idPion, long _idCase)
{
	grille->poserPion(_idPion, _idCase);
}

void DriverGrille::setPartieFinie(bool _partieFinie, bool _egalite)
{
	partieFinie = _partieFinie;
	egalite = _egalite;
}

DriverGrille::~DriverGrille(void)
{
	delete grille;
}

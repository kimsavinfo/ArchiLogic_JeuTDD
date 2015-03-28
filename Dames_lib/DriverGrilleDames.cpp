#include "stdafx.h"
#include "DriverGrilleDames.h"


DriverGrilleDames::DriverGrilleDames(int _nbLignes, int _nbColonnes) : DriverGrille(_nbLignes, _nbColonnes)
{
}

void DriverGrilleDames::poserPion(long _idPion, int _iLigne, int _iColonne)
{
	grille->poserPion(_idPion, _iLigne, _iColonne);
}

map<string, int> DriverGrilleDames::getCaseCoordonneesOccupant(long _idOccupant)
{
	return grille->getCaseCoordonneesOccupant(_idOccupant);
}

vector<ChoixPion *> DriverGrilleDames::getChoixPions(vector<long> _pionsIdsJoueur)
{
	vector<ChoixPion *> choix;
	map<string, int> coordonnees;

	for (int iPion = 0; iPion < _pionsIdsJoueur.size(); iPion++)
	{
		coordonnees = getCaseCoordonneesOccupant(_pionsIdsJoueur.at(iPion));
		choix.push_back( new ChoixPion(_pionsIdsJoueur.at(iPion), coordonnees["ligne"], coordonnees["colonne"]) );
	}

	return choix;
}

DriverGrilleDames::~DriverGrilleDames(void)
{
}

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

vector<ChoixPion *> DriverGrilleDames::getChoixPions(int _sensVertical, vector<long> _pionsIdsJoueur)
{
	vector<ChoixPion *> choix;
	map<string, int> coordonnees;

	for (int iPion = 0; iPion < _pionsIdsJoueur.size(); iPion++)
	{
		coordonnees = getCaseCoordonneesOccupant(_pionsIdsJoueur.at(iPion));

		// Check si le pion est bien présent sur la case pour les tests
		if( grille->getCaseIdOccupant(coordonnees["ligne"], coordonnees["colonne"]) == _pionsIdsJoueur.at(iPion) )
		{
			if( isPionDeplacable(coordonnees["ligne"], coordonnees["colonne"], _sensVertical, -1,  _pionsIdsJoueur) 
				|| isPionDeplacable(coordonnees["ligne"], coordonnees["colonne"], _sensVertical, 1,  _pionsIdsJoueur) 
				)
			{
				choix.push_back( new ChoixPion(_pionsIdsJoueur.at(iPion), coordonnees["ligne"], coordonnees["colonne"]) );
			}
		}
	}

	return choix;
}

bool DriverGrilleDames::isPionDeplacable(int _ligne, int _colonne, int _sensVertical, int _sensHorizontal ,vector<long> _pionsIdsJoueur)
{
	bool isDeplacable = false;
	int ligneArrivee = _ligne + _sensVertical;
	int colonneArrivee = _colonne + _sensHorizontal;

	if( grille->isCoordonneesDansGrille(ligneArrivee, colonneArrivee) )
	{
		if( grille->isCaseVide(ligneArrivee, colonneArrivee) )
		{
			isDeplacable = true;
		}
		/*
		else
		{
			if( isCaseOccupeeParPionAdverse(ligneArrivee,  colonneArrivee, _pionsIdsJoueur) )
			{
				isDeplacable = grille->isCaseVide(ligneArrivee + _sensVertical, colonneArrivee + _sensHorizontal);
			}
		}
		*/
	}


	return isDeplacable;
}

bool DriverGrilleDames::isCaseOccupeeParPionAdverse(int _ligne, int _colonne, vector<long> _pionsIdsJoueur)
{
	long idPionOccupant = grille->getCaseIdOccupant(_ligne, _colonne);
	vector<long>::iterator it = find(_pionsIdsJoueur.begin(), _pionsIdsJoueur.end(), idPionOccupant);
	return it == _pionsIdsJoueur.end() ? true : false;
}

DriverGrilleDames::~DriverGrilleDames(void)
{
}

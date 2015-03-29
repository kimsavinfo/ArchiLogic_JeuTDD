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

/** ============================================================================================== */
/**	Choix des pions à déplacer
/** ============================================================================================== */

vector<ChoixPion *> DriverGrilleDames::getChoixPions(int _sensVertical, map<long, bool> _pionsJoueur)
{
	vector<ChoixPion *> choix;
	map<string, int> coordonnees;

	for (auto const& pion: _pionsJoueur)
	{
		coordonnees = getCaseCoordonneesOccupant(pion.first);

		// Check si le pion est bien présent sur la case pour les tests
		if( grille->getCaseIdOccupant(coordonnees["ligne"], coordonnees["colonne"]) == pion.first )
		{
			// Cas pion simple
			if( !pion.second && 
				isPionSimpleDeplacable(coordonnees["ligne"], coordonnees["colonne"], _sensVertical, _pionsJoueur) 
				)
			{
				choix.push_back( new ChoixPion(pion.first, coordonnees["ligne"], coordonnees["colonne"], pion.second) );
			}

			// Cas pion dame
			if( pion.second && 
				isPionDameDeplacable(coordonnees["ligne"], coordonnees["colonne"], _pionsJoueur)
				)
			{
				choix.push_back( new ChoixPion(pion.first, coordonnees["ligne"], coordonnees["colonne"], pion.second) );
			}
		}
	}

	return choix;
}

bool DriverGrilleDames::isPionSimpleDeplacable(int _ligne, int _colonne, int _sensVertical, map<long, bool> _pionsJoueur)
{
	return isPionDeplacable(_ligne, _colonne, _sensVertical, -1,  _pionsJoueur)
		|| isPionDeplacable(_ligne, _colonne, _sensVertical, 1,  _pionsJoueur);
}
		
bool DriverGrilleDames::isPionDameDeplacable(int _ligne, int _colonne, map<long, bool> _pionsJoueur )
{
	return isPionDeplacable(_ligne, _colonne, -1, -1,  _pionsJoueur)
		|| isPionDeplacable(_ligne, _colonne, -1, 1,  _pionsJoueur)
		|| isPionDeplacable(_ligne, _colonne, 1, -1,  _pionsJoueur)
		|| isPionDeplacable(_ligne, _colonne, 1, 1,  _pionsJoueur);
}

bool DriverGrilleDames::isPionDeplacable(int _ligne, int _colonne, int _sensVertical, int _sensHorizontal, map<long, bool> _pionsJoueur)
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
		else
		{
			if( isCaseOccupeeParPionAdverse(ligneArrivee,  colonneArrivee, _pionsJoueur) 
				&& grille->isCoordonneesDansGrille(ligneArrivee + _sensVertical, colonneArrivee + _sensHorizontal)
				)
			{
				isDeplacable = grille->isCaseVide(ligneArrivee + _sensVertical, colonneArrivee + _sensHorizontal);
			}
		}
	}

	return isDeplacable;
}

bool DriverGrilleDames::isCaseOccupeeParPionAdverse(int _ligne, int _colonne, map<long, bool> _pionsJoueur)
{
	long idPionOccupant = grille->getCaseIdOccupant(_ligne, _colonne);
	auto it =_pionsJoueur.find(idPionOccupant);
	return it == _pionsJoueur.end() ? true : false;
}

/** ============================================================================================== */
/**	Choix de la case : où peut-on déplacer le pion ?
/** ============================================================================================== */

vector<ChoixDeplacement *> DriverGrilleDames::getChoixCase(ChoixPion * _choixPion)
{
	vector<ChoixDeplacement *> choixDeplacement;

	return choixDeplacement;
}

// TODO : penser à rendre l'action de manger obligatoire :
// enlever les pionManges = 0 si d'autres on supérieur à 0
// Pour une dame, on doit absolument prendre en compte toutes les diago 

DriverGrilleDames::~DriverGrilleDames(void)
{
}

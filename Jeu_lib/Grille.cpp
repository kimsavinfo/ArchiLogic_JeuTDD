#include "stdafx.h"
#include "Grille.h"


Grille::Grille(int _nbLignes, int _nbColonnes) 
{
	nbLignes = _nbLignes;
	nbColonnes = _nbColonnes;
    
	for(int iLig = 0; iLig < nbLignes; iLig++)
    {
        for(int iCol = 0; iCol < nbColonnes; iCol++)
        {
			Case * newCase = new Case("[" + to_string(iLig+1) + ";" + to_string(iCol+1) + "]");
			cases[iLig][iCol][newCase->getId()] = newCase;
        }
    }
}

Case * Grille::getCase(int _iLigne, int _iColonne)
{
	 Case * laCase = NULL;

	for (auto const& uneCase: cases[_iLigne][_iColonne])
	{
		laCase = uneCase.second;
	}

	 return laCase;
}

map<long, Case*> Grille::getCasesVides()
{
	 map<long, Case*> casesVides;

	for(int iLig = 0; iLig < nbLignes; iLig++)
    {
        for(int iCol = 0; iCol < nbColonnes; iCol++)
        {
			for (auto const& uneCase: cases[iLig][iCol])
			{
				if(uneCase.second->isVide())
				{
					casesVides[uneCase.second->getId()] = uneCase.second;
				}
			}
        }
    }

	return casesVides;
}

int Grille::getLargeur()
{
	int longueur1Case = 1;
	for (auto const& uneCase: cases[0][0])
	{
		longueur1Case = uneCase.second->getLargeur();
	}

	return longueur1Case * nbColonnes;
}

void Grille::poserPion(long _idPion, long _idCase)
{
	getCase(_idCase)->setIdOccupant(_idPion);
}

Case * Grille::getCase(long _idCase)
{
	Case * laCase = NULL;

	for(int iLig = 0; iLig < nbLignes; iLig++)
    {
        for(int iCol = 0; iCol < nbColonnes; iCol++)
        {
			for (auto const& uneCase: cases[iLig][iCol])
			{
				if(uneCase.second->getId() == _idCase)
				{
					laCase = uneCase.second;
				}
			}
        }
    }

	return laCase;
}

map<int, map<int,  map<long, Case*>>> Grille::getCases()
{
	return cases;
}

/**
* Permet de récupérer une case voisine
* _idCase : l'id de la case de référence
* _directionVerticale : comme dans un réréentiel 2D, les valeurs possibles sont
*							-1 : à gauche
*							0 : sur le même X
*							1 : à droite
* _directionHorizontale : comme dans un réréentiel 2D, les valeurs possibles sont
*							-1 : au-dessus
*							0 : sur le même Y
*							1 : en dessous
*/
Case * Grille::getCaseVoisine(long _idCase, int _directionVerticale, int _directionHorizontale)
{
	Case * laCaseVoisine = NULL;

	map<string, int> coordonnees = getCaseCoordonnees(_idCase);
	int iLigVoisine = coordonnees["ligne"] + _directionHorizontale;
	int iColVoisine = coordonnees["colonne"] + _directionVerticale;
	for (auto const& uneCase: cases[iLigVoisine][iColVoisine])
	{
		laCaseVoisine = uneCase.second;
	}

	return laCaseVoisine;
}

map<string, int> Grille::getCaseCoordonnees(long _idCase)
{
	map<string, int> coordonnees;

	for(int iLig = 0; iLig < nbLignes; iLig++)
    {
        for(int iCol = 0; iCol < nbColonnes; iCol++)
        {
			for (auto const& uneCase: cases[iLig][iCol])
			{
				if(uneCase.second->getId() == _idCase)
				{
					coordonnees["ligne"] = iLig;
					coordonnees["colonne"] = iCol;
				}
			}
        }
    }

	return coordonnees;
}

int Grille::getNbLignes()
{
	return nbLignes;
}

int Grille::getNbColonnes()
{
	return nbColonnes;
}

Grille::~Grille(void)
{
	for(int iLig = 0; iLig < nbLignes; iLig++)
    {
        for(int iCol = 0; iCol < nbColonnes; iCol++)
        {
            for (auto const& uneCase: cases[iLig][iCol])
			{
				delete uneCase.second;
			}
        }
    }
}

#include "stdafx.h"
#include "Grille.h"


Grille::Grille(int _nbLignes, int _nbColonnes)
{
	nbLignes = _nbLignes;
	nbColonnes = _nbColonnes;

	creerCases();
}

void Grille::creerCases()
{
	FactoryCase * factory = new FactoryCase();	
	string legende;

	for(int iLig = 0; iLig < nbLignes; iLig++)
    {
		cases.push_back( vector<Case * >() );

        for(int iCol = 0; iCol < nbColonnes; iCol++)
        {
			legende = "[" + to_string(iLig+1) + ";" + to_string(iCol+1) + "]";
			cases[iLig].push_back(factory->creerCase(legende));
		}
    }

	delete factory;
}

void Grille::poserPion(long _idPion, long _idCase)
{
	getCase(_idCase)->setIdOccupant(_idPion);
}

void Grille::poserPion(long _idPion, int _iLigne, int _iColonne)
{
	getCase(_iLigne, _iColonne)->setIdOccupant(_idPion);
}

string Grille::getCaseRepresentation(int _iLigne, int _iColonne)
{
	return getCase(_iLigne, _iColonne)->getRepresentation();
}

long Grille::getCaseIdOccupant(int _iLigne, int _iColonne)
{
	return getCase(_iLigne, _iColonne)->getIdOccupant();
}

string Grille::getCaseLegende(long _idCase)
{
	return getCase(_idCase)->getLegende();
}

bool Grille::isCaseVide(int _iLigne, int _iColonne)
{
	return getCase(_iLigne, _iColonne)->isVide();
}

map<string, int> Grille::getCaseCoordonnees(long _idCase)
{
	map<string, int> coordonnees;
	Case * laCase = NULL;
	int iLigne = 0;
	int iColonne = 0;

	do
	{
		if(cases[iLigne][iColonne]->getId() == _idCase)
		{
			laCase = cases[iLigne][iColonne];
			coordonnees["ligne"] = iLigne;
			coordonnees["colonne"] = iColonne;
		}
		
		iColonne++;
		if(iColonne == nbColonnes)
		{
			iColonne = 0;
			iLigne++;
		}
	}while( (iLigne < nbLignes && iColonne < nbColonnes) && laCase == NULL );

	return coordonnees;
}

map<string, int> Grille::getCaseCoordonneesOccupant(long _idOccupant)
{
	map<string, int> coordonnees;
	Case * laCase = NULL;
	int iLigne = 0;
	int iColonne = 0;

	do
	{
		if(cases[iLigne][iColonne]->getIdOccupant() == _idOccupant)
		{
			laCase = cases[iLigne][iColonne];
			coordonnees["ligne"] = iLigne;
			coordonnees["colonne"] = iColonne;
		}
		
		iColonne++;
		if(iColonne == nbColonnes)
		{
			iColonne = 0;
			iLigne++;
		}
	}while( (iLigne < nbLignes && iColonne < nbColonnes) && laCase == NULL );

	return coordonnees;
}

vector<long> Grille::getCasesVidesIds()
{
	vector<long> casesVides;

	for(int iLig = 0; iLig < nbLignes; iLig++)
    {
        for(int iCol = 0; iCol < nbColonnes; iCol++)
        {
			if(cases[iLig][iCol]->isVide())
			{
				casesVides.push_back( cases[iLig][iCol]->getId() );
			}
		}
    }

	return casesVides;
}

bool Grille::isGrilleRemplie()
{
	int nbCasesOccupees = 0;

	for(int iLig = 0; iLig < nbLignes; iLig++)
    {
        for(int iCol = 0; iCol < nbColonnes; iCol++)
        {
			if(!cases[iLig][iCol]->isVide())
			{
				nbCasesOccupees++;
			}
		}
	}

	return nbCasesOccupees == nbColonnes * nbLignes ? true : false;
}


int Grille::getNbLignes()
{
	return nbLignes;
}

int Grille::getNbColonnes()
{
	return nbColonnes;
}

Case * Grille::getCase(int _iLigne, int _iColonne)
{
	return cases[_iLigne][_iColonne];
}

Case * Grille::getCase(long _idCase)
{
	Case * laCase = NULL;
	int iLigne = 0;
	int iColonne = 0;

	do
	{
		if(cases[iLigne][iColonne]->getId() == _idCase)
		{
			laCase = cases[iLigne][iColonne];
		}
		
		iColonne++;
		if(iColonne == nbColonnes)
		{
			iColonne = 0;
			iLigne++;
		}
	}while( (iLigne < nbLignes && iColonne < nbColonnes) && laCase == NULL );
	
	return laCase;
}

bool Grille::isCoordonneesDansGrille(int _iLigne, int _iColonne)
{
	return _iLigne >= 0 && _iLigne < nbLignes && _iColonne >= 0 && _iColonne < nbColonnes;
}

Grille::~Grille(void)
{
	for(int iLig = 0; iLig < nbLignes; iLig++)
    {
        for(int iCol = 0; iCol < nbColonnes; iCol++)
        {
			delete cases[iLig][iCol];
		}
    }
}

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

	for(int iLig = 0; iLig < nbLignes; iLig++)
    {
		cases.push_back( vector<Case * >() );

        for(int iCol = 0; iCol < nbColonnes; iCol++)
        {
			cases[iLig].push_back(factory->creerCase());
		}
    }

	delete factory;
}

vector< vector<Case *> > Grille::getCases()
{
	return cases;
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

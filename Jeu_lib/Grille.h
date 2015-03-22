#pragma once

#include <vector>

#include "FactoryCase.h"


class Grille
{
	public:
		Grille(int _nbLignes, int _nbColonnes);
		~Grille(void);

		
		Case * getCase(int _iLigne, int _iColonne);

		int getNbLignes();
		int getNbColonnes();
		vector< vector<Case *> > getCases();

	private:
		int nbLignes;
		int nbColonnes;
		vector< vector<Case *> > cases;

		void creerCases();
};


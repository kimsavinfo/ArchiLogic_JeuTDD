#pragma once

#include <vector>

#include "FactoryCase.h"


class Grille
{
	public:
		Grille(int _nbLignes, int _nbColonnes);
		~Grille(void);

		int getNbLignes();
		int getNbColonnes();

		vector< vector<Case *> > getCases();
		Case * getCase(int _iLigne, int _iColonne);

	private:
		int nbLignes;
		int nbColonnes;
		vector< vector<Case *> > cases;

		void creerCases();
};


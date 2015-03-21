#pragma once

#include <vector>

#include "FactoryCase.h"


class Grille
{
	public:
		Grille(int _nbLignes, int _nbColonnes);
		~Grille(void);

		vector< vector<Case *> > getCases();

	private:
		int nbLignes;
		int nbColonnes;
		vector< vector<Case *> > cases;

		void creerCases();
};


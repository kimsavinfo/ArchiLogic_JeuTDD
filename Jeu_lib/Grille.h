#pragma once

#include <vector>
#include <map>

#include "FactoryCase.h"

class Grille
{
	public:
		Grille(int _nbLignes, int _nbColonnes);
		~Grille(void);

		Case * getCase(int _iLigne, int _iColonne);
		Case * getCase(long _idCase);
		vector<Case *> getCasesVides();
		void poserPion(long _idPion, long _idCase);
		map<string, int> getCaseCoordonnees(long _idCase);
		bool isGrilleRemplie();

		int getNbLignes();
		int getNbColonnes();
		vector< vector<Case *> > getCases();

	private:
		int nbLignes;
		int nbColonnes;
		vector< vector<Case *> > cases;

		void creerCases();
};


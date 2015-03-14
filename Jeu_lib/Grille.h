#pragma once

#include <map>
#include <string> 

#include "Case.h"

class Grille
{
	public:
		Grille(int _nbLignes, int _nbColonnes);
		~Grille(void);

		int getLargeur();
		map<long, Case*> getCasesVides();
		void poserPion(long _idPion, long _idCase);

		map<int, map<int,  map<long, Case*>>> getCases();
		map<string, int> getCaseCoordonnees(long _idCase);
		int getNbLignes();
		int getNbColonnes();
		Case * getCase(int _iLigne, int _iColonne);

	private:
		int nbLignes;
		int nbColonnes;
		//	< iLigne < iColonne < idCase, Case > > >
		map<int, map<int,  map<long, Case*>>> cases;

		Case * getCase(long _idCase);
		Case * getCaseVoisine(long _idCase, int _directionVerticale, int _directionHorizontale);
};


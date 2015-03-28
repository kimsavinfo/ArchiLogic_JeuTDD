#pragma once

#include <vector>
#include <map>

#include "FactoryCase.h"

class Grille
{
	public:
		Grille(int _nbLignes, int _nbColonnes);
		~Grille(void);

		string getCaseRepresentation(int _iLigne, int _iColonne);
		map<string, int> getCaseCoordonnees(long _idCase);
		map<string, int> getCaseCoordonneesOccupant(long _idOccupant);
		vector<long> getCasesVidesIds();
		long getCaseIdOccupant(int _iLigne, int _iColonne);
		string getCaseLegende(long _idCase);
		void poserPion(long _idPion, long _idCase);
		void poserPion(long _idPion, int _iLigne, int _iColonne);
		bool isGrilleRemplie();

		int getNbLignes();
		int getNbColonnes();

	private:
		int nbLignes;
		int nbColonnes;
		vector< vector<Case *> > cases;

		void creerCases();
		Case * getCase(int _iLigne, int _iColonne);
		Case * getCase(long _idCase);
};


#pragma once

#include "Grille.h"

class DriverGrille
{
	public:
		DriverGrille(int _nbLignes, int _nbColonnes);
		~DriverGrille(void);

		int getGrilleNbLignes();
		int getGrilleNbColonnes();
		string getCaseRepresentation(int _iLigne, int _iColonne);
		long getCaseIdOccupant(int _iLigne, int _iColonne);
		bool isPartieFinie();
		bool isEgalite();

	protected:
		Grille * grille;
		bool partieFinie;
		bool egalite;
};


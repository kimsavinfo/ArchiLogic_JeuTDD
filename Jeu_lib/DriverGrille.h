#pragma once

#include "Grille.h"

class DriverGrille
{
	public:
		DriverGrille(int _nbLignes, int _nbColonnes);
		~DriverGrille(void);

		Grille * getGrille();
		bool isPartieFinie();
		bool isEgalite();

	protected:
		Grille * grille;
		bool partieFinie;
		bool egalite;
};


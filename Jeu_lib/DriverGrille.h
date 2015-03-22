#pragma once

#include "Grille.h"

class DriverGrille
{
	public:
		DriverGrille(int _nbLignes, int _nbColonnes);
		~DriverGrille(void);

		Grille * getGrille();

	protected:
		Grille * grille;
		bool partieFinie;

};


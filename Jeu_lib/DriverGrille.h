#pragma once

#include "Grille.h"

class DriverGrille
{
	public:
		DriverGrille(int _nbLignes, int _nbColonnes);
		~DriverGrille(void);

		Grille * getGrille();

	private:
		Grille * grille;
		bool partieFinie;

};


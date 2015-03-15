#pragma once

#include "Grille.h"

class ControleurGrilleDames
{
	public:
		ControleurGrilleDames(int _nbColonnes, int _nbLignes);
		~ControleurGrilleDames(void);

		int getGrilleLargeur();
		map<int, map<int,  map<long, Case*>>> getGrilleCases();

	private :
		Grille * grille;
		bool partieFinie;
};


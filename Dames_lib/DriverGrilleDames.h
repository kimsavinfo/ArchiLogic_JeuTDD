#pragma once

#include "DriverGrille.h"

class DriverGrilleDames : public DriverGrille
{
	public:
		DriverGrilleDames(int _nbLignes, int _nbColonnes);
		~DriverGrilleDames(void);

		void poserPion(long _idPion, int _iLigne, int _iColonne);
		map<string, int> getCaseCoordonneesOccupant(long _idOccupant);
};


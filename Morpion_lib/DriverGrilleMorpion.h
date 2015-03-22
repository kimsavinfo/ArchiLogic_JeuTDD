#pragma once

#include "DriverGrille.h"
#include "ChoixCase.h"

class DriverGrilleMorpion : public DriverGrille
{
	public:
		DriverGrilleMorpion(int _nbLignes, int _nbColonnes);
		~DriverGrilleMorpion(void);

		vector<ChoixCase *> getChoixCases();
		void poserPion(long _idPion, long _idCase);
};


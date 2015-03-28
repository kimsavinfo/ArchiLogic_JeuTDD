#pragma once

#include "PionDames.h"

class FactoryPionDames
{
	public:
		FactoryPionDames(void);
		~FactoryPionDames(void);

		PionDames * creerPion(string _couleur);
};


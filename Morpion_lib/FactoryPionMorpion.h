#pragma once

#include "PionMorpion.h"

class FactoryPionMorpion
{
	public:
		FactoryPionMorpion(void);
		~FactoryPionMorpion(void);

		PionMorpion * creerPion(string _forme);
};


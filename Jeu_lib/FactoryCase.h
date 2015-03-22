#pragma once

#include "Case.h"

class FactoryCase
{
	public:
		FactoryCase(void);
		~FactoryCase(void);

		Case * creerCase(string _legende);
};


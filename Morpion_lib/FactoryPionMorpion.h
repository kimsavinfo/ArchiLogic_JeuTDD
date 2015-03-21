#include "PionMorpion.h"

class FactoryPionMorpion
{
	public:
		FactoryPionMorpion(void);
		~FactoryPionMorpion(void);

		PionMorpion * createPion(string _forme);
};


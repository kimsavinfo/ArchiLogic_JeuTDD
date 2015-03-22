#pragma once

#include "Pion.h"

class PionMorpion : public Pion
{
	public:
		PionMorpion(string _forme);
		~PionMorpion(void);

		bool isSurGrille();
		void setSurGrille(bool _surGrille);

	private:
		bool surGrille;
};


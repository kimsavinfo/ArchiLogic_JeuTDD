#include "Pion.h"

class PionMorpion : public Pion
{
	public:
		PionMorpion(string _forme);
		~PionMorpion(void);

		bool isSurGrille();

	private:
		bool surGrille;
};


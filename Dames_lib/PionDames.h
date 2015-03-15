#include "Pion.h"

class PionDames : public Pion
{
public:
	PionDames(string _forme, string _couleurHex);
	~PionDames(void);

	bool isStatutDame();
	void setStatutDame(bool _statutDame);

private :
	bool statutDame;
};


#include "stdafx.h"
#include "PionDames.h"


PionDames::PionDames(string _forme, string _couleurHex) : Pion(_forme, _couleurHex)
{
	statutDame = false;
}

bool PionDames::isStatutDame()
{
	return statutDame;
}

void PionDames::setStatutDame(bool _statutDame)
{
	statutDame = _statutDame;
}

PionDames::~PionDames(void)
{
}

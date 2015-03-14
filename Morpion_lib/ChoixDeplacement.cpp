#include "stdafx.h"
#include "ChoixDeplacement.h"


ChoixDeplacement::ChoixDeplacement(string _legende, long _idCase)
{
	legende = _legende;
	idCase = _idCase;
}

string ChoixDeplacement::getLegende()
{
	return legende;
}

long ChoixDeplacement::getIdCase()
{
	return idCase;
}

ChoixDeplacement::~ChoixDeplacement(void)
{
}

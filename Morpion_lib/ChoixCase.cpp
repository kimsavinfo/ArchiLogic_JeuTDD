#include "stdafx.h"
#include "ChoixCase.h"


ChoixCase::ChoixCase(string _legende, long _idCase)
{
	legende = _legende;
	idCase = _idCase;
}

string ChoixCase::getLegende()
{
	return legende;
}

long ChoixCase::getIdCase()
{
	return idCase;
}


ChoixCase::~ChoixCase(void)
{
}

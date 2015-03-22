#include "stdafx.h"
#include "FactoryCase.h"


FactoryCase::FactoryCase(void)
{
}

Case * FactoryCase::creerCase(string _legende)
{
	return new Case(_legende);
}

FactoryCase::~FactoryCase(void)
{
}

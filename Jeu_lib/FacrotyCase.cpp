#include "stdafx.h"
#include "FactoryCase.h"


FactoryCase::FactoryCase(void)
{
}

Case * FactoryCase::creerCase()
{
	return new Case();
}

FactoryCase::~FactoryCase(void)
{
}

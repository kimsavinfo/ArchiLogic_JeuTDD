#include "stdafx.h"
#include "FactoryPionMorpion.h"


FactoryPionMorpion::FactoryPionMorpion(void)
{
}

PionMorpion * FactoryPionMorpion::creerPion(string _forme)
{
	return new PionMorpion(_forme);
}

FactoryPionMorpion::~FactoryPionMorpion(void)
{
}

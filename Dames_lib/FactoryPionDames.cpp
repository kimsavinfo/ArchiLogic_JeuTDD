#include "stdafx.h"
#include "FactoryPionDames.h"


FactoryPionDames::FactoryPionDames()
{
}

PionDames * FactoryPionDames::creerPion(string _couleur)
{
	return new PionDames(_couleur);
}


FactoryPionDames::~FactoryPionDames(void)
{
}

#include "stdafx.h"
#include "PionDames.h"


PionDames::PionDames(string _couleur) : Pion(_couleur)
{
	typeDame = false;
}

string PionDames::getCouleur()
{
	return representation;
}

string PionDames::getRepresentation()
{
	return typeDame ? representation + "D" :  representation;
}

bool PionDames::isDame()
{
	return typeDame;
}

void PionDames::setDame()
{
	typeDame = true;
}

PionDames::~PionDames(void)
{
}

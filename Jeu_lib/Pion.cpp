#include "stdafx.h"
#include "Pion.h"


Pion::Pion(string _representation)
{
	idPion = reinterpret_cast<int>(this);
	representation = _representation;
}


string Pion::getRepresentation()
{
	return representation;
}


Pion::~Pion(void)
{
}

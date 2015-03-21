#include "stdafx.h"
#include "Pion.h"


Pion::Pion(string _representation)
{
	id = reinterpret_cast<int>(this);
	representation = _representation;
}

long Pion::getId()
{
	return id;
}

string Pion::getRepresentation()
{
	return representation;
}


Pion::~Pion(void)
{
}

#include "stdafx.h"
#include "Case.h"


Case::Case(void)
{
	id = reinterpret_cast<int>(this);
	idOccupant = 0;
}

int Case::getLargeur()
{
	return getRepresentation().length();
}

bool Case::isVide()
{
	return idOccupant == 0 ? true : false;
}

/** ==================================================
	GET / SET
================================================== **/

long Case::getId()
{
	return id;
}

string Case::getRepresentation()
{
	return "   |";
}

long Case::getIdOccupant()
{
	return idOccupant;
}

void Case::setIdOccupant(long _idOccupant)
{
	idOccupant = _idOccupant;
}


Case::~Case(void)
{
}

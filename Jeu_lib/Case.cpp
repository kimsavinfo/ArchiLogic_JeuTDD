#include "stdafx.h"
#include "Case.h"


Case::Case(string _legende)
{
	id = reinterpret_cast<int>(this);
	idOccupant = 0;
	legende = _legende;
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

string Case::getLegende()
{
	return legende;
}

Case::~Case(void)
{
}

#include "stdafx.h"
#include "Case.h"


Case::Case(string _legende) 
{
	idCase = reinterpret_cast<int>(this);
	legende = _legende;
	idOccupant = 0;
}

int Case::getLargeur()
{
	return afficher().length();
}

bool Case::isVide()
{
	return idOccupant == 0 ? true : false;
}

string Case::afficher()
{
	return "   |";
}

long Case::getId()
{
	return idCase;
}

string Case::getLegende()
{
	return legende;
}

int Case::getIdOccupant()
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

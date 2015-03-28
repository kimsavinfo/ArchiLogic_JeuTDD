#include "stdafx.h"
#include "ChoixPion.h"


ChoixPion::ChoixPion(long _idPion, int _ligneDepart, int _colonneDepart)
{
	idPion = _idPion;
	ligneDepart = _ligneDepart;
	colonneDepart = _colonneDepart;
}

long ChoixPion::getIdPion()
{
	return idPion;
}

int ChoixPion::getLigneDepart()
{
	return ligneDepart;
}

int ChoixPion::getColonneDepart()
{
	return colonneDepart;
}

string ChoixPion::getRepresentation()
{
	return "["+ to_string(ligneDepart) + ";" + to_string(colonneDepart) + "]";
}


ChoixPion::~ChoixPion(void)
{
}

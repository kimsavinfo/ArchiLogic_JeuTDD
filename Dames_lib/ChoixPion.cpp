#include "stdafx.h"
#include "ChoixPion.h"


ChoixPion::ChoixPion(long _idPion, int _ligneDepart, int _colonneDepart,  bool _typeDame)
{
	idPion = _idPion;
	ligneDepart = _ligneDepart;
	colonneDepart = _colonneDepart;
	typeDame = _typeDame;
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

bool ChoixPion::isDame()
{
	return typeDame;
}

ChoixPion::~ChoixPion(void)
{
}

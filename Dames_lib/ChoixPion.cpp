#include "stdafx.h"
#include "ChoixPion.h"


ChoixPion::ChoixPion(long _idPion, int _ligneDepart, int _colonneDepart,  bool _typeDame)
{
	idPion = _idPion;
	ligneDepart = _ligneDepart;
	colonneDepart = _colonneDepart;
	typeDame = _typeDame;
	ligneTempo = ligneDepart;
	colonneTempo = colonneDepart;
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

int ChoixPion::getLigneTempo()
{
	return ligneTempo;
}

void ChoixPion::setLigneTempo(int _ligneTempo)
{
	ligneTempo = _ligneTempo;
}

int ChoixPion::getColonneTempo()
{
	return colonneTempo;
}

void ChoixPion::setColonneTempo(int _colonneTempo)
{
	colonneTempo = _colonneTempo;
}

void ChoixPion::setCoordonneesTempo(int _ligneTempo, int _colonneTempo)
{
	setLigneTempo(_ligneTempo);
	setColonneTempo(_colonneTempo);
}

ChoixPion::~ChoixPion(void)
{
}

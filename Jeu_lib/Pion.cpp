#include "stdafx.h"
#include "Pion.h"


Pion::Pion(string _forme, string _couleurHex) 
{
	idPion = reinterpret_cast<int>(this);
	forme = _forme;
	couleurHex = _couleurHex;
	surGrille = false;
}

bool Pion::isSurGrille()
{
	return surGrille;
}

void Pion::setSurGrille(bool _surGrille)
{
	surGrille = surGrille;
}

long Pion::getId()
{
	return idPion;
}

string Pion::afficher()
{
	return forme;
}

Pion::~Pion(void)
{
}

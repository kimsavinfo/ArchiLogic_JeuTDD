#include "stdafx.h"
#include "PionMorpion.h"


PionMorpion::PionMorpion(string _forme) : Pion(_forme)
{
	surGrille = false;
}

bool PionMorpion::isSurGrille()
{
	return surGrille;
}

void PionMorpion::setSurGrille(bool _surGrille)
{
	surGrille = _surGrille;
}

PionMorpion::~PionMorpion(void)
{
}

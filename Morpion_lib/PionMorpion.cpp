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

PionMorpion::~PionMorpion(void)
{
}

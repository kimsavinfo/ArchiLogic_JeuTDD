#include "stdafx.h"
#include "ControleurGrilleDames.h"


ControleurGrilleDames::ControleurGrilleDames(int _nbColonnes, int _nbLignes)
{
	grille = new Grille(_nbColonnes, _nbLignes);
	partieFinie = false;
}

int ControleurGrilleDames::getGrilleLargeur()
{
	return grille->getLargeur();
}

map<int, map<int,  map<long, Case*>>> ControleurGrilleDames::getGrilleCases()
{
	return grille->getCases();
}

ControleurGrilleDames::~ControleurGrilleDames(void)
{
	delete grille;
}

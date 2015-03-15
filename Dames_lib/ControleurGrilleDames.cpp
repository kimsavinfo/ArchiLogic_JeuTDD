#include "stdafx.h"
#include "ControleurGrilleDames.h"


ControleurGrilleDames::ControleurGrilleDames(int _nbColonnes, int _nbLignes)
{
	grille = new Grille(_nbColonnes, _nbLignes);
	partieFinie = false;
}

void ControleurGrilleDames::poserPion(long _idPion, int _iLig, int _iCol)
{
	map<int, map<int,  map<long, Case*>>> cases = grille->getCases();
	long idCaseChoisie;

	for (auto const& uneCase: cases[_iLig][_iCol])
	{
		idCaseChoisie = uneCase.second->getId();
	}

	poserPion(_idPion, idCaseChoisie);
}

void ControleurGrilleDames::poserPion(long _idPion, long _idCase)
{
	grille->poserPion(_idPion, _idCase);
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

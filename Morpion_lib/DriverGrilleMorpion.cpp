#include "stdafx.h"
#include "DriverGrilleMorpion.h"


DriverGrilleMorpion::DriverGrilleMorpion(int _nbLignes, int _nbColonnes) : DriverGrille(_nbLignes, _nbColonnes)
{
}

vector<ChoixCase *> DriverGrilleMorpion::getChoixCases()
{
	vector<ChoixCase *> choix;
	string legende;

	vector<Case *> casesVides = grille->getCasesVides();
	for (int iCaseVide = 0; iCaseVide < casesVides.size(); iCaseVide++)
	{
		legende = to_string(choix.size() +1) + " - " + casesVides[iCaseVide]->getLegende();
		choix.push_back( new ChoixCase( legende , casesVides[iCaseVide]->getId()) );
	}
	
	return choix;
}

void DriverGrilleMorpion::poserPion(long _idPion, long _idCase)
{
	grille->poserPion(_idPion, _idCase);
}

DriverGrilleMorpion::~DriverGrilleMorpion(void)
{
}

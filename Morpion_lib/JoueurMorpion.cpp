#include "stdafx.h"
#include "JoueurMorpion.h"


JoueurMorpion::JoueurMorpion(string _nom, string _forme) : Joueur(_nom)
{
	creerPions(_forme);
}

void JoueurMorpion::creerPions(string _forme)
{
	FactoryPionMorpion * factory = new FactoryPionMorpion();

	for (int iPion = 0; iPion < 5; iPion++)
	{
		PionMorpion * pionJoueur = factory->creerPion(_forme);
		pions[pionJoueur->getId()] = pionJoueur;
	}

	delete factory;
}

void JoueurMorpion::poserPion(long _idPion)
{
	pions[_idPion]->setSurGrille(true);
}

string JoueurMorpion::getFormePions()
{
	return pions.begin()->second->getRepresentation();
}

long JoueurMorpion::getIdPionAPoser()
{
	map<long, PionMorpion*>::iterator pionTest = pions.begin();

	while( pionTest != pions.end() && pionTest->second->isSurGrille() );
	{
		pionTest++;
	}

	return pionTest->second->getId();
}

vector<long> JoueurMorpion::getPionsIds()
{
	vector<long> pionsIds;

	for (auto const& pion: pions)
	{
		pionsIds.push_back(pion.second->getId());
	}

	return pionsIds;
}

bool JoueurMorpion::isPionAuJoueur(long _idPion)
{
	return pions.find(_idPion) != pions.end() ? true : false;
}

JoueurMorpion::~JoueurMorpion(void)
{
	for (auto const& pion: pions)
	{
		delete pion.second;
	}
}

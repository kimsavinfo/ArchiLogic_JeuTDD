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

string JoueurMorpion::getFormePions()
{
	return pions.begin()->second->getRepresentation();
}

map<long, PionMorpion*> JoueurMorpion::getPions()
{
	return pions;
}

JoueurMorpion::~JoueurMorpion(void)
{
	for (auto const& pion: pions)
	{
		delete pion.second;
	}
}

#include "stdafx.h"
#include "JoueurMorpion.h"

JoueurMorpion::JoueurMorpion(string _nom, string _couleurHex) : Joueur(_nom, _couleurHex)
{
}

void JoueurMorpion::attribuerPions(int _nbPions, string _formePion)
{
	for(int iPion = 0; iPion < _nbPions; iPion++)
	{
		Pion * pionJoueur = new Pion(_formePion, couleurHex);
		pions[pionJoueur->getId()] = pionJoueur;
	}
}

Pion* JoueurMorpion::getNextPionNonSurGrille()
{
	Pion * pionNonSurGrille = NULL; 
	map<long, Pion*>::iterator pionTest = pions.begin();

	while( pionTest != pions.end() && pionTest->second->isSurGrille() );
	{
		if(pionTest->second->isSurGrille())
		{
			pionTest++;
		}
	}

	return pionTest->second;
}

void JoueurMorpion::poserPion(long _idPion)
{
	pions[_idPion]->setSurGrille(true);
}


map<long, Pion*> JoueurMorpion::getPions()
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

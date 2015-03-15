#include "stdafx.h"
#include "JoueurDames.h"


JoueurDames::JoueurDames(string _nom, string _couleurHex) : Joueur(_nom, _couleurHex)
{
}

void JoueurDames::attribuerPions(int _nbPions, string _formePion)
{
	for(int iPion = 0; iPion < _nbPions; iPion++)
	{
		PionDames * pionJoueur = new PionDames(_formePion, couleurHex);
		pions[pionJoueur->getId()] = pionJoueur;
	}
}

PionDames* JoueurDames::getNextPionNonSurGrille()
{
	PionDames * pionNonSurGrille = NULL; 
	map<long, PionDames*>::iterator pionTest = pions.begin();

	while( pionTest != pions.end() && pionTest->second->isSurGrille() );
	{
		if(pionTest->second->isSurGrille())
		{
			pionTest++;
		}
	}

	return pionTest->second;
}

void JoueurDames::poserPion(long _idPion)
{
	pions[_idPion]->setSurGrille(true);
}


map<long, PionDames*> JoueurDames::getPions()
{
	return pions;
}

JoueurDames::~JoueurDames(void)
{
	for (auto const& pion: pions)
	{
		delete pion.second;
	}
}

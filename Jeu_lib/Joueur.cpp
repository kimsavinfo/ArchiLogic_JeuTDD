#include "stdafx.h"
#include "Joueur.h"


Joueur::Joueur(string _nom, string _couleurHex) 
{
	nom = _nom;
	couleurHex = _couleurHex;
}

void Joueur::attribuerPions(int _nbPions, string _formePion)
{
	for(int iPion = 0; iPion < _nbPions; iPion++)
	{
		Pion * pionJoueur = new Pion(_formePion, couleurHex);
		pions[pionJoueur->getId()] = pionJoueur;
	}
}

map<long, Pion*> Joueur::getPions()
{
	return pions;
}

Pion* Joueur::getNextPionNonSurGrille()
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

void Joueur::poserPion(long _idPion)
{
	pions[_idPion]->setSurGrille(true);
}

string Joueur::getNom()
{
    return nom;
}

Joueur::~Joueur(void)
{
	for (auto const& pion: pions)
	{
		delete pion.second;
	}
}

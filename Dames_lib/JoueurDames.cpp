#include "stdafx.h"
#include "JoueurDames.h"


JoueurDames::JoueurDames(string _nom, string _couleur) : Joueur(_nom)
{
	creerPions(_couleur);
}

void JoueurDames::creerPions(string _couleur)
{
	FactoryPionDames * factory = new FactoryPionDames();

	for (int iPion = 0; iPion < 20; iPion++)
	{
		PionDames * pionJoueur = factory->creerPion(_couleur);
		pions[pionJoueur->getId()] = pionJoueur;
	}

	delete factory;
}

string JoueurDames::getCouleurPions()
{
	return pions.begin()->second->getRepresentation();
}

vector<long> JoueurDames::getPionsIds()
{
	vector<long> pionsIds;

	if(pions.size() > 0)
	{
		for (auto const& pion: pions)
		{
			pionsIds.push_back(pion.second->getId());
		}
	}
	
	return pionsIds;
}

bool JoueurDames::isPionAuJoueur(long _idPion)
{
	return pions.find(_idPion) != pions.end() ? true : false;
}

string JoueurDames::getPionRepresentation(long _idPion)
{
	return pions.find(_idPion)->second->getRepresentation();
}

JoueurDames::~JoueurDames(void)
{
	for (auto const& pion: pions)
	{
		delete pion.second;
	}
}

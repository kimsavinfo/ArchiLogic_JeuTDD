#include "stdafx.h"
#include "JoueurDames.h"


JoueurDames::JoueurDames(string _nom, string _couleur, int _sensVertical) : Joueur(_nom)
{
	sensVertical = _sensVertical;
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

int JoueurDames::getSensVertical()
{
	return sensVertical;
}

map<long, bool> JoueurDames::getPionsIdsEtIsDame()
{
	map<long, bool> idsEtIsDame;

	for (auto const& pion: pions)
	{
		idsEtIsDame[pion.second->getId()] = pion.second->isDame();
	}

	return idsEtIsDame;
}

void JoueurDames::setPionDame(long _idPion)
{
	pions.find(_idPion)->second->setDame();
}

void JoueurDames::mangerPion(long _idPion)
{
	pions.erase(_idPion);
}

JoueurDames::~JoueurDames(void)
{
	for (auto const& pion: pions)
	{
		delete pion.second;
	}
}

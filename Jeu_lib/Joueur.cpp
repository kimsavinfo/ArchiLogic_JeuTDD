#include "stdafx.h"
#include "Joueur.h"


Joueur::Joueur(string _nom)
{
	nom = _nom;
}


string Joueur::getNom()
{
	return nom;
}

Joueur::~Joueur(void)
{
}

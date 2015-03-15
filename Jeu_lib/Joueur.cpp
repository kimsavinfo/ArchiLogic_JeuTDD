#include "stdafx.h"
#include "Joueur.h"


Joueur::Joueur(string _nom, string _couleurHex) 
{
	nom = _nom;
	couleurHex = _couleurHex;
}

string Joueur::getNom()
{
    return nom;
}

Joueur::~Joueur(void)
{
}

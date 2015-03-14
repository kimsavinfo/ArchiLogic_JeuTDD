#pragma once

#include <string> 
#include <map>
#include <vector>

#include "ChoixDeplacement.h"
#include "Grille.h"
#include "Pion.h"

class ControleurGrilleMorpion
{
	public:
		ControleurGrilleMorpion(int _nbColonnes, int _nbLignes);
		~ControleurGrilleMorpion();

		map<int, map<int,  map<long, Case*>>> getGrilleCases();
		int getGrilleLargeur();
		vector<ChoixDeplacement*> getChoix();
		void poserPion(long _idPion, long _idCase);
		bool isPartieFinie();
		bool isEgalite();
		void checkPartieFinie(long _idCase, map<long, Pion*> _pionsJoueur);
		
	private:
		Grille * grille;
		bool partieFinie;
		bool egalite;
		
		void checkLigneGagnante(int _iLigne, map<long, Pion*> _pionsJoueur);
		void checkColonneGagnante(int _iColonne, map<long, Pion*> _pionsJoueur);
		void checkDiagonaleNOSEGagnante(map<long, Pion*> _pionsJoueur);
		void checkDiagonaleNESOGagnante(map<long, Pion*> _pionsJoueur);
		void checkEgalite();
		void setPartieFinieEgalite(bool _egalite);
};


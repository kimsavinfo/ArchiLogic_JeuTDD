#pragma once

#include "DriverGrille.h"
#include "ChoixPion.h"
#include "ChoixDeplacement.h"

class DriverGrilleDames : public DriverGrille
{
	public:
		DriverGrilleDames(int _nbLignes, int _nbColonnes);
		~DriverGrilleDames(void);

		void poserPion(long _idPion, int _iLigne, int _iColonne);
		map<string, int> getCaseCoordonneesOccupant(long _idOccupant);
		vector<ChoixPion *> getChoixPions(int _sensVertical, map<long, bool> _pionsJoueur);
		vector<ChoixDeplacement *> getChoixCase(ChoixPion * _choixPion, int _sensVertical, map<long, bool> _pionsJoueur);

	private:
		bool isPionDeplacable(int _ligne, int _colonne, int _sensVertical, int _sensHorizontal, map<long, bool> _pionsJoueur);
		bool isPionSimpleDeplacable(int _ligne, int _colonne, int _sensVertical, map<long, bool> _pionsJoueur);
		bool isPionDameDeplacable(int _ligne, int _colonne,map<long, bool> _pionsJoueur );
		bool isCaseOccupeeParPionAdverse(int _ligne, int _colonne, map<long, bool> _pionsJoueur);
		void construireCHoixCasesInit(ChoixPion * _choixPion, int _sensVertical, int _sensHorizontal, map<long, bool> _pionsJoueur,
						  vector<ChoixDeplacement *> &_choixDeplacement);
		void construireCHoixCasesRecursif(ChoixPion * _choixPion, int _sensVertical, int _sensHorizontal, map<long, bool> _pionsJoueur,
			vector<ChoixDeplacement *> &_choixDeplacement, vector<long> &_pionsManges);
		void construireCHoixCasesObligerManger(vector<ChoixDeplacement *> &_choixDeplacement);
		bool isObligeManger(vector<ChoixDeplacement *> &_choixDeplacement);
};


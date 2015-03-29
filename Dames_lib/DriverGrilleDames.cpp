#include "stdafx.h"
#include "DriverGrilleDames.h"


DriverGrilleDames::DriverGrilleDames(int _nbLignes, int _nbColonnes) : DriverGrille(_nbLignes, _nbColonnes)
{
}

void DriverGrilleDames::poserPion(long _idPion, int _iLigne, int _iColonne)
{
	grille->poserPion(_idPion, _iLigne, _iColonne);
}

map<string, int> DriverGrilleDames::getCaseCoordonneesOccupant(long _idOccupant)
{
	return grille->getCaseCoordonneesOccupant(_idOccupant);
}

/** ============================================================================================== */
/**	Choix des pions à déplacer
/** ============================================================================================== */

vector<ChoixPion *> DriverGrilleDames::getChoixPions(int _sensVertical, map<long, bool> _pionsJoueur)
{
	vector<ChoixPion *> choix;
	map<string, int> coordonnees;

	for (auto const& pion: _pionsJoueur)
	{
		coordonnees = getCaseCoordonneesOccupant(pion.first);

		// Check si le pion est bien présent sur la case pour les tests
		if( grille->getCaseIdOccupant(coordonnees["ligne"], coordonnees["colonne"]) == pion.first )
		{
			// Cas pion simple
			if( !pion.second && 
				isPionSimpleDeplacable(coordonnees["ligne"], coordonnees["colonne"], _sensVertical, _pionsJoueur) 
				)
			{
				choix.push_back( new ChoixPion(pion.first, coordonnees["ligne"], coordonnees["colonne"], pion.second) );
			}

			// Cas pion dame
			if( pion.second && 
				isPionDameDeplacable(coordonnees["ligne"], coordonnees["colonne"], _pionsJoueur)
				)
			{
				choix.push_back( new ChoixPion(pion.first, coordonnees["ligne"], coordonnees["colonne"], pion.second) );
			}
		}
	}

	return choix;
}

bool DriverGrilleDames::isPionSimpleDeplacable(int _ligne, int _colonne, int _sensVertical, map<long, bool> _pionsJoueur)
{
	return isPionDeplacable(_ligne, _colonne, _sensVertical, -1,  _pionsJoueur)
		|| isPionDeplacable(_ligne, _colonne, _sensVertical, 1,  _pionsJoueur);
}
		
bool DriverGrilleDames::isPionDameDeplacable(int _ligne, int _colonne, map<long, bool> _pionsJoueur )
{
	return isPionDeplacable(_ligne, _colonne, -1, -1,  _pionsJoueur)
		|| isPionDeplacable(_ligne, _colonne, -1, 1,  _pionsJoueur)
		|| isPionDeplacable(_ligne, _colonne, 1, -1,  _pionsJoueur)
		|| isPionDeplacable(_ligne, _colonne, 1, 1,  _pionsJoueur);
}

bool DriverGrilleDames::isPionDeplacable(int _ligne, int _colonne, int _sensVertical, int _sensHorizontal, map<long, bool> _pionsJoueur)
{
	bool isDeplacable = false;
	int ligneArrivee = _ligne + _sensVertical;
	int colonneArrivee = _colonne + _sensHorizontal;

	if( grille->isCoordonneesDansGrille(ligneArrivee, colonneArrivee) )
	{
		if( grille->isCaseVide(ligneArrivee, colonneArrivee) )
		{
			isDeplacable = true;
		}
		else
		{
			if( isCaseOccupeeParPionAdverse(ligneArrivee,  colonneArrivee, _pionsJoueur) 
				&& grille->isCoordonneesDansGrille(ligneArrivee + _sensVertical, colonneArrivee + _sensHorizontal)
				)
			{
				isDeplacable = grille->isCaseVide(ligneArrivee + _sensVertical, colonneArrivee + _sensHorizontal);
			}
		}
	}

	return isDeplacable;
}

bool DriverGrilleDames::isCaseOccupeeParPionAdverse(int _ligne, int _colonne, map<long, bool> _pionsJoueur)
{
	bool occupe = true;
	long idPionOccupant = grille->getCaseIdOccupant(_ligne, _colonne);
	
	if(idPionOccupant > 0)
	{
		auto it =_pionsJoueur.find(idPionOccupant);
		occupe = it == _pionsJoueur.end() ? true : false;
	}
	else
	{
		occupe = false;
	}

	return occupe;
}

/** ============================================================================================== */
/**	Choix de la case : où peut-on déplacer le pion ?
/** ============================================================================================== */

vector<ChoixDeplacement *> DriverGrilleDames::getChoixCase(ChoixPion * _choixPion, int _sensVertical, map<long, bool> _pionsJoueur)
{
	vector<ChoixDeplacement *> choixDeplacement;
	
	construireCHoixCasesInit(_choixPion, _sensVertical, -1, _pionsJoueur, choixDeplacement);
	construireCHoixCasesInit(_choixPion, _sensVertical, 1, _pionsJoueur, choixDeplacement);
	
	if(_choixPion->isDame())
	{
		construireCHoixCasesInit(_choixPion, - _sensVertical, -1, _pionsJoueur, choixDeplacement);
		construireCHoixCasesInit(_choixPion, - _sensVertical, 1, _pionsJoueur, choixDeplacement);
	}

	// Règle du jeu :
	// On a obligation de manger
	construireCHoixCasesObligerManger(choixDeplacement);

	return choixDeplacement;
}

void DriverGrilleDames::construireCHoixCasesInit(ChoixPion * _choixPion, 
												 int _sensVertical, int _sensHorizontal, 
												 map<long, bool> _pionsJoueur,
												vector<ChoixDeplacement *> &_choixDeplacement)
{
	vector<long> pionsManges;

	_choixPion->setLigneTempo(_choixPion->getLigneDepart());
	_choixPion->setColonneTempo(_choixPion->getColonneDepart());
	construireCHoixCasesRecursif(_choixPion, _sensVertical, _sensHorizontal, 
		_pionsJoueur, _choixDeplacement, pionsManges);
}

void DriverGrilleDames::construireCHoixCasesRecursif(ChoixPion * _choixPion, 
											 int _sensVertical, int _sensHorizontal, 
											 map<long, bool> _pionsJoueur,
											 vector<ChoixDeplacement *> &_choixDeplacement, 
											 vector<long> &_pionsManges)
{
	int ligneArrivee = _choixPion->getLigneTempo() + _sensVertical;
	int colonneArrivee = _choixPion->getColonneTempo() + _sensHorizontal;

	if( grille->isCoordonneesDansGrille(ligneArrivee, colonneArrivee) )
	{
		if( isCaseOccupeeParPionAdverse(ligneArrivee, colonneArrivee, _pionsJoueur) 
			&& grille->isCoordonneesDansGrille(ligneArrivee + _sensVertical, colonneArrivee + _sensHorizontal))
		{
			// ============ Cas où le pion choisi peut manger un pion adverse
			_pionsManges.push_back( grille->getCaseIdOccupant(ligneArrivee,colonneArrivee) );

			// Mettre à jour les coordonnées temporaires
			_choixPion->setCoordonneesTempo(ligneArrivee + _sensVertical, colonneArrivee + _sensHorizontal);

			// Possibilité dans la meme direction
			construireCHoixCasesRecursif(_choixPion, _sensVertical, _sensHorizontal, _pionsJoueur, 
				_choixDeplacement, _pionsManges);
			// Possibilité dans le même sens horinzontal mais dans le sens vertical inverse 
			construireCHoixCasesRecursif(_choixPion, - _sensVertical, _sensHorizontal, _pionsJoueur, 
				_choixDeplacement, _pionsManges);
			// Possibilité dans le même sens vertical mais dans le sens horinzontal inverse 
			construireCHoixCasesRecursif(_choixPion, _sensVertical, - _sensHorizontal, _pionsJoueur, 
				_choixDeplacement, _pionsManges);
		}
		else
		{
			if( grille->isCaseVide(ligneArrivee, colonneArrivee) )
			{
				// ============ Cas où le pion peut avancer dans une case vide
				_choixDeplacement.push_back( new ChoixDeplacement(ligneArrivee, colonneArrivee, _pionsManges) );

				if(_choixPion->isDame())
				{
					// Mettre à jour les cooronnées temporaires
					_choixPion->setCoordonneesTempo(ligneArrivee, colonneArrivee);

					// Pour la dame, on doit continuer dans la même direction
					construireCHoixCasesRecursif(_choixPion, _sensVertical, _sensHorizontal, _pionsJoueur, 
						_choixDeplacement, _pionsManges);

					// SI la a mangé un pion ALORS
					//		la dame peut manger un autre sur l'autre diagonale
					// FIN SI
					if( _pionsManges.size() > 0 )
					{
						// Possibilité dans le même sens horinzontal mais dans le sens vertical inverse 
						construireCHoixCasesRecursif(_choixPion, - _sensVertical, _sensHorizontal, _pionsJoueur, 
							_choixDeplacement, _pionsManges);
						// Possibilité dans le même sens vertical mais dans le sens horinzontal inverse 
						construireCHoixCasesRecursif(_choixPion, _sensVertical, - _sensHorizontal, _pionsJoueur, 
							_choixDeplacement, _pionsManges);
					}
				}
			}
		}
	}
}

// TODO : penser à rendre l'action de manger obligatoire :
// enlever les pionManges = 0 si d'autres on supérieur à 0
// Pour une dame, on doit absolument prendre en compte toutes les diago 
void DriverGrilleDames::construireCHoixCasesObligerManger(vector<ChoixDeplacement *> &_choixDeplacement)
{
	if( isObligeManger(_choixDeplacement) )
	{
		// Enlever proposition qui ne mangent aucun pion
		for (int iChoix = 0; iChoix < _choixDeplacement.size(); iChoix++)
		{
			if(_choixDeplacement.at(iChoix)->getPionsManges().size() == 0)
			{
				_choixDeplacement.erase(_choixDeplacement.begin()+iChoix);
			}
		}
	}
	
	// TODO : gérer le cas des dames
}

bool DriverGrilleDames::isObligeManger(vector<ChoixDeplacement *> &_choixDeplacement)
{
	bool obligeManger = false;
	int iChoix = 0;

	do
	{
		if( _choixDeplacement.at(iChoix)->getPionsManges().size() > 0 )
		{
			obligeManger = true;
		}

		iChoix++;
	}while(iChoix < _choixDeplacement.size() && !obligeManger);

	return obligeManger;
}

DriverGrilleDames::~DriverGrilleDames(void)
{
}

#include "stdafx.h"
#include "DriverGrilleDames.h"


DriverGrilleDames::DriverGrilleDames(int _nbLignes, int _nbColonnes) : DriverGrille(_nbLignes, _nbColonnes)
{
}

void DriverGrilleDames::poserPion(long _idPion, int _iLigne, int _iColonne)
{
	grille->poserPion(_idPion, _iLigne, _iColonne);
}

void DriverGrilleDames::deplacerPion(ChoixPion * _choixPion, ChoixDeplacement * _choixDeplacement)
{
	grille->enleverOccupant(_choixPion->getIdPion());
	grille->poserPion(_choixPion->getIdPion(), _choixDeplacement->getLigneArrivee(), _choixDeplacement->getColonneArrivee());
}

void DriverGrilleDames::mangerPion(long _pionMange)
{
	grille->enleverOccupant(_pionMange);
}

map<string, int> DriverGrilleDames::getCaseCoordonneesOccupant(long _idOccupant)
{
	return grille->getCaseCoordonneesOccupant(_idOccupant);
}

bool DriverGrilleDames::isPionDevientDame(long _idPion, int _sensVertical)
{
	bool devientDame = false;
	map<string, int> coordonnees = grille->getCaseCoordonneesOccupant(_idPion);

	if(_sensVertical == 1)
	{
		devientDame = coordonnees["ligne"] == (grille->getNbLignes() -1) ? true : false;
	}
	else if(_sensVertical == -1)
	{
		devientDame = coordonnees["ligne"] == 0 ? true : false;
	}

	return devientDame;
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
/**	Choix de la case : où peut-on déplacer la dame ?
/** ============================================================================================== */

vector<ChoixDeplacement *> DriverGrilleDames::getChoixCaseDame(ChoixPion * _choixDame, map<long, bool> _pionsJoueur)
{
	vector<ChoixDeplacement *> choixDeplacement;
	
	construireChoixCaseDameInit(_choixDame->getLigneDepart(), _choixDame->getColonneDepart(), _pionsJoueur, choixDeplacement);

	return choixDeplacement;
}

void DriverGrilleDames::construireChoixCaseDameInit(int _ligne, int _colonne, 
												map<long, bool> _pionsJoueur, 
												vector<ChoixDeplacement *> &_choixDeplacement)
{
	vector<long> pionsManges;

	if( !isDiagonalesAvecAdversaireMangeable(_ligne, _colonne, _pionsJoueur) )
	{
		construireChoixCaseDameDiagonaleSansAdversaire( _ligne, _colonne, 1, 1, pionsManges, _choixDeplacement);
		construireChoixCaseDameDiagonaleSansAdversaire( _ligne, _colonne, 1, -1, pionsManges, _choixDeplacement);
		construireChoixCaseDameDiagonaleSansAdversaire( _ligne, _colonne, -1, 1, pionsManges, _choixDeplacement);
		construireChoixCaseDameDiagonaleSansAdversaire( _ligne, _colonne, -1, -1, pionsManges, _choixDeplacement);
	}
	else
	{
		if( isDiagonaleAvecAdversaireMangeable(_ligne, _colonne, 1, 1, _pionsJoueur) )
		{
			construireChoixCaseDameRecursif(_ligne, _colonne, 1, 1, _pionsJoueur, pionsManges, _choixDeplacement);
		}

		if( isDiagonaleAvecAdversaireMangeable(_ligne, _colonne, 1, -1,  _pionsJoueur) )
		{
			construireChoixCaseDameRecursif(_ligne, _colonne, 1, -1, _pionsJoueur, pionsManges, _choixDeplacement);
		}

		if( isDiagonaleAvecAdversaireMangeable(_ligne, _colonne, -1, 1,  _pionsJoueur) )
		{
			construireChoixCaseDameRecursif(_ligne, _colonne, -1, 1, _pionsJoueur, pionsManges, _choixDeplacement);
		}

		if( isDiagonaleAvecAdversaireMangeable(_ligne, _colonne, -1, -1,  _pionsJoueur) )
		{
			construireChoixCaseDameRecursif(_ligne, _colonne, -1, -1, _pionsJoueur, pionsManges, _choixDeplacement);
		}
	}
}

void DriverGrilleDames::construireChoixCaseDameRecursif(int _ligne, int _colonne, 
												int _sensVertical, int _sensHorizontal,
												map<long, bool> _pionsJoueur, 
												vector<long> &_pionsManges,
												vector<ChoixDeplacement *> &_choixDeplacement)
{
	if( isDiagonalesAvecAdversaireMangeable(_ligne, _colonne, _sensVertical, _sensHorizontal, _pionsJoueur) )
	{
		if( isDiagonaleAvecAdversaireMangeable(_ligne, _colonne, _sensVertical, _sensHorizontal, _pionsJoueur) )
		{
			map<string, int> coordonnesArrivee = construireChoixCaseDameDiagonaleAvecAdversaire(
				_ligne, _colonne,
				_sensVertical, _sensHorizontal,
				_pionsJoueur,
				_pionsManges
				);

			// Même direction
			construireChoixCaseDameRecursif(
				coordonnesArrivee["ligne"], coordonnesArrivee["colonne"],
				_sensVertical, _sensHorizontal, 
				_pionsJoueur, _pionsManges, _choixDeplacement);
			
			// Dans le sens vertical inverse mais dans le même sens horinzontal
			construireChoixCaseDameRecursif(
				coordonnesArrivee["ligne"], coordonnesArrivee["colonne"],
				- _sensVertical, _sensHorizontal, 
				_pionsJoueur, _pionsManges, _choixDeplacement);

			// Dans le même sens vertical mais dans le sens horinzontal inverse
			construireChoixCaseDameRecursif(
				coordonnesArrivee["ligne"], coordonnesArrivee["colonne"],
				_sensVertical, - _sensHorizontal, 
				_pionsJoueur, _pionsManges, _choixDeplacement);
		}
	}
	else
	{
		_choixDeplacement.push_back( new ChoixDeplacement(_ligne, _colonne, _pionsManges) );
		construireChoixCaseDameDiagonaleSansAdversaire( _ligne, _colonne, 
			_sensVertical, _sensHorizontal, 
			_pionsManges, _choixDeplacement);
	}
}

map<string, int> DriverGrilleDames::construireChoixCaseDameDiagonaleAvecAdversaire(int _ligneDepart, int _colonneDepart,
												int _sensVertical, int _sensHorizontal,
												map<long, bool> _pionsJoueur,
												vector<long> &_pionsManges)
{
	map<string, int> coordonnesArrivee;
	int ligneLimite = _sensVertical == 1 ? grille->getNbLignes() : -1;
	int colonneLimite = _sensHorizontal == 1 ? grille->getNbColonnes() : -1;
	int iLigne = _ligneDepart;
	int iColonne = _colonneDepart;
	bool avecPionAdverse = false;

	do
	{
		if( isCaseOccupeeParPionAdverse(iLigne, iColonne, _pionsJoueur) 
			&&  grille->isCoordonneesDansGrille(iLigne+_sensVertical, iColonne+_sensHorizontal)
			)
		{
			if(grille->isCaseVide(iLigne+_sensVertical, iColonne+_sensHorizontal) )
			{
				_pionsManges.push_back( grille->getCaseIdOccupant(iLigne, iColonne) );
				coordonnesArrivee["ligne"] = iLigne+_sensVertical;
				coordonnesArrivee["colonne"] = iColonne+_sensHorizontal;
			}

			avecPionAdverse = true;
		}

		iLigne = iLigne + _sensVertical;
		iColonne = iColonne + _sensHorizontal;
	}while( (iLigne != ligneLimite && iColonne != colonneLimite) && !avecPionAdverse);

	return coordonnesArrivee;
}

void DriverGrilleDames::construireChoixCaseDameDiagonaleSansAdversaire(int _ligneDepart, int _colonneDepart,
												int _sensVertical, int _sensHorizontal,
												vector<long> &_pionsManges,
												vector<ChoixDeplacement *> &_choixDeplacement)
{
	int ligneLimite = _sensVertical == 1 ? grille->getNbLignes() : -1;
	int colonneLimite = _sensHorizontal == 1 ? grille->getNbColonnes() : -1;
	int iLigne = _ligneDepart + _sensVertical;
	int iColonne = _colonneDepart + _sensHorizontal;
	bool avecPion = false;

	if( grille->isCoordonneesDansGrille(iLigne,iColonne) )
	{
		do
		{
			if( grille->isCaseVide(iLigne, iColonne) )
			{
				_choixDeplacement.push_back( new ChoixDeplacement(iLigne, iColonne, _pionsManges) );
			}
			else
			{
				avecPion = true;
			}

			iLigne = iLigne + _sensVertical;
			iColonne = iColonne + _sensHorizontal;
		}while( (iLigne != ligneLimite && iColonne != colonneLimite) && !avecPion);
	}
}

bool DriverGrilleDames::isDiagonalesAvecAdversaireMangeable(int _ligneDepart, int _colonneDepart, 
															map<long, bool> _pionsJoueur)
{
	return isDiagonaleAvecAdversaireMangeable(_ligneDepart, _colonneDepart, 1, 1, _pionsJoueur)
		|| isDiagonaleAvecAdversaireMangeable(_ligneDepart, _colonneDepart, 1, -1, _pionsJoueur)
		|| isDiagonaleAvecAdversaireMangeable(_ligneDepart, _colonneDepart, -1, 1, _pionsJoueur)
		|| isDiagonaleAvecAdversaireMangeable(_ligneDepart, _colonneDepart, -1, -1, _pionsJoueur)
		;
}

bool DriverGrilleDames::isDiagonalesAvecAdversaireMangeable(int _ligneDepart, int _colonneDepart, 
										int _sensVerticalDepart, int _sensHorizontalDepart,
											map<long, bool> _pionsJoueur)
{
	 return isDiagonaleAvecAdversaireMangeable(_ligneDepart, _colonneDepart, _sensVerticalDepart, _sensHorizontalDepart, _pionsJoueur)
		|| isDiagonaleAvecAdversaireMangeable(_ligneDepart, _colonneDepart, _sensVerticalDepart, - _sensHorizontalDepart, _pionsJoueur)
		|| isDiagonaleAvecAdversaireMangeable(_ligneDepart, _colonneDepart, - _sensVerticalDepart, _sensHorizontalDepart, _pionsJoueur)
		;
}

bool DriverGrilleDames::isDiagonaleAvecAdversaireMangeable(int _ligneDepart, int _colonneDepart,
								int _sensVertical, int _sensHorizontal,
								map<long, bool> _pionsJoueur)
{
	int ligneLimite = _sensVertical == 1 ? grille->getNbLignes() : -1;
	int colonneLimite = _sensHorizontal == 1 ? grille->getNbColonnes() : -1;
	int iLigne = _ligneDepart + _sensVertical;
	int iColonne = _colonneDepart + _sensHorizontal;
	bool avecAdversaire = false;
	bool avecAdversaireMangeable = false;

	if( grille->isCoordonneesDansGrille(iLigne,iColonne) )
	{
		do
		{
			if( isCaseOccupeeParPionAdverse(iLigne, iColonne, _pionsJoueur) 
				&& grille->isCoordonneesDansGrille(iLigne + _sensVertical, iColonne-1)
				)
			{
				if( grille->isCaseVide(iLigne + _sensVertical, iColonne + _sensHorizontal) )
				{
					avecAdversaireMangeable = true;
				}
				avecAdversaire = true;
			}

			iLigne = iLigne + _sensVertical;
			iColonne = iColonne + _sensHorizontal;
		}while( (iLigne != ligneLimite && iColonne != colonneLimite) && !avecAdversaire);
	}

	return avecAdversaireMangeable;
}

/** ============================================================================================== */
/**	Choix de la case : où peut-on déplacer le pion simple ?
/** ============================================================================================== */

vector<ChoixDeplacement *> DriverGrilleDames::getChoixCase(ChoixPion * _choixPion, 
														   int _sensVertical, 
														   map<long, bool> _pionsJoueur)
{
	vector<ChoixDeplacement *> choixDeplacement;
	
	construireChoixCaseInit(_choixPion->getLigneDepart(), _choixPion->getColonneDepart(),
			_sensVertical, _pionsJoueur, choixDeplacement
		);

	return choixDeplacement;
}

void DriverGrilleDames::construireChoixCaseInit(int _ligne, int _colonne, 
												int _sensVertical, 
												map<long, bool> _pionsJoueur, 
												vector<ChoixDeplacement *> &_choixDeplacement)
{
	vector<long> pionsManges;
	 
	if( !isAuMoinsUnAdversaireAdjacentNonCompte(_ligne, _colonne, pionsManges, _pionsJoueur) )
	{
		if( grille->isCoordonneesDansGrille(_ligne + _sensVertical, _colonne-1) )
		{
			if( grille->isCaseVide(_ligne + _sensVertical, _colonne-1) )
			{
				_choixDeplacement.push_back( 
					new ChoixDeplacement(_ligne + _sensVertical, _colonne-1, pionsManges)
				);
			}
		}

		
		if( grille->isCoordonneesDansGrille(_ligne + _sensVertical, _colonne+1) )
		{
			if( grille->isCaseVide(_ligne + _sensVertical, _colonne+1) )
			{
				_choixDeplacement.push_back( 
					new ChoixDeplacement(_ligne + _sensVertical, _colonne+1, pionsManges)
				);
			}
		}
	}
	else
	{
		if( grille->isCoordonneesDansGrille(_ligne + _sensVertical, _colonne-1) )
		{
			if( isAdversaireAdjacentNonCompte(_ligne + _sensVertical, _colonne-1, pionsManges, _pionsJoueur) )
			{
				construireChoixCaseRecursif(
					_ligne,  _colonne,
					_sensVertical, -1,
					pionsManges, _pionsJoueur, _choixDeplacement
				);
			}
		}

		if( grille->isCoordonneesDansGrille(_ligne + _sensVertical, _colonne+1) )
		{
			if( isAdversaireAdjacentNonCompte(_ligne + _sensVertical, _colonne+1, pionsManges, _pionsJoueur) )
			{
				construireChoixCaseRecursif(
					_ligne,  _colonne,
					_sensVertical, 1,
					pionsManges, _pionsJoueur, _choixDeplacement
				);
			}
		}
	}
}

void DriverGrilleDames::construireChoixCaseRecursif(int _ligne, int _colonne, 
												int _sensVertical, int _sensHorizontal,
												vector<long> &_pionsManges,
												map<long, bool> _pionsJoueur, 
												vector<ChoixDeplacement *> &_choixDeplacement)
{
	int lignePionAdv = _ligne + _sensVertical;
	int colonnePionAdv = _colonne + _sensHorizontal;

	if( isAdversaireAdjacentNonCompte(lignePionAdv, colonnePionAdv, _pionsManges, _pionsJoueur) )
	{
		int ligneArrivee =  _ligne + _sensVertical * 2;
		int colonneArrivee = _colonne + _sensHorizontal *2;

		if( grille->isCaseVide(ligneArrivee, colonneArrivee) )
		{
			_pionsManges.push_back( grille->getCaseIdOccupant(lignePionAdv, colonnePionAdv) );
		}

		if( isAuMoinsUnAdversaireAdjacentNonCompte(ligneArrivee, colonneArrivee, _pionsManges, _pionsJoueur) )
		{
			// Dans la meme direction
			if( isAdversaireAdjacentNonCompte(ligneArrivee + _sensVertical, colonneArrivee + _sensHorizontal, _pionsManges, _pionsJoueur) )
			{
				construireChoixCaseRecursif(
					ligneArrivee, colonneArrivee,
					_sensVertical, _sensHorizontal,
					_pionsManges, _pionsJoueur, _choixDeplacement
				);
			}

			// Dans le même sens horinzontal mais dans le sens vertical inverse 
			if( isAdversaireAdjacentNonCompte(ligneArrivee - _sensVertical, colonneArrivee + _sensHorizontal, _pionsManges, _pionsJoueur) )
			{
				construireChoixCaseRecursif(
					ligneArrivee, colonneArrivee, 
					- _sensVertical, _sensHorizontal,
					_pionsManges, _pionsJoueur, _choixDeplacement
				);
			}

			// Dans le même sens vertical mais dans le sens horinzontal inverse
			if( isAdversaireAdjacentNonCompte(ligneArrivee + _sensVertical, colonneArrivee + _sensHorizontal, _pionsManges, _pionsJoueur) )
			{
				construireChoixCaseRecursif(
					ligneArrivee, colonneArrivee, 
					_sensVertical, - _sensHorizontal,
					_pionsManges, _pionsJoueur, _choixDeplacement
				);
			}
		}
		else
		{
			_choixDeplacement.push_back(new ChoixDeplacement(ligneArrivee, colonneArrivee, _pionsManges));
		}
	}
}

bool DriverGrilleDames::isAuMoinsUnAdversaireAdjacentNonCompte(int _ligne, int _colonne,
												  vector<long> &_pionsManges,
												  map<long, bool> _pionsJoueur)
{

	return isAdversaireAdjacentNonCompte(_ligne -1, _colonne -1, _pionsManges, _pionsJoueur)
		|| isAdversaireAdjacentNonCompte(_ligne -1, _colonne, _pionsManges, _pionsJoueur)
		|| isAdversaireAdjacentNonCompte(_ligne -1, _colonne +1, _pionsManges, _pionsJoueur)
		|| isAdversaireAdjacentNonCompte(_ligne, _colonne -1, _pionsManges, _pionsJoueur)
		|| isAdversaireAdjacentNonCompte(_ligne, _colonne +1,  _pionsManges, _pionsJoueur)
		|| isAdversaireAdjacentNonCompte(_ligne +1, _colonne -1, _pionsManges, _pionsJoueur)
		|| isAdversaireAdjacentNonCompte(_ligne +1, _colonne, _pionsManges, _pionsJoueur)
		|| isAdversaireAdjacentNonCompte(_ligne +1, _colonne +1, _pionsManges, _pionsJoueur)
 		;
}

bool DriverGrilleDames::isAdversaireAdjacentNonCompte(int _ligne, int _colonne, 
													  vector<long> &_pionsManges, 
													  map<long, bool> _pionsJoueur)
{
	bool adversaireNonCompte = false;

	if( grille->isCoordonneesDansGrille(_ligne, _colonne) )
	{	
		if( isCaseOccupeeParPionAdverse(_ligne, _colonne, _pionsJoueur) )
		{
			long idOccupant = grille->getCaseIdOccupant(_ligne, _colonne);
			if( find(_pionsManges.begin(), _pionsManges.end(), idOccupant) == _pionsManges.end() )
			{
				adversaireNonCompte = true;
			}
		}
	}

	return adversaireNonCompte;
}

DriverGrilleDames::~DriverGrilleDames(void)
{
}

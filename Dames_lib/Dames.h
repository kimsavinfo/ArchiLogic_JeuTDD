#pragma once

#include "Jeu.h"

class Dames : public Jeu
{
	public:
		Dames(void);
		~Dames(void);

		virtual void jouer();

	protected:
		virtual void afficherTitre();
		virtual void afficherJeu();
		virtual void afficherJoueurs();

	private:
		
};


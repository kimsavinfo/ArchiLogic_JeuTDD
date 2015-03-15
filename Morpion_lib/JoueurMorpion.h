#include "Joueur.h"

#include "Pion.h"

class JoueurMorpion : public Joueur
{
	public:
		JoueurMorpion(string _nom, string _couleurHex);
		~JoueurMorpion(void);
		
		map<long, Pion*> getPions();
		Pion* getNextPionNonSurGrille();
		void attribuerPions(int _nbPions, string _formePion);
		void poserPion(long _idPion);

	private:
		map<long, Pion*> pions;
};


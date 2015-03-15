#include "Joueur.h"
#include "PionDames.h"

class JoueurDames : public Joueur
{
public:
	JoueurDames(string _nom, string _couleurHex);
	~JoueurDames(void);

	void attribuerPions(int _nbPions, string _formePion);
	map<long, PionDames*> getPions();
	PionDames* getNextPionNonSurGrille();
	void poserPion(long _idPion);

	private:
		map<long, PionDames*> pions;
};


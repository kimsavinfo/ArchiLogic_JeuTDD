#include <string>
using namespace std; 

class Joueur
{
	public:
		Joueur(string _nom);
		~Joueur(void);

		string getNom();

	private:
		string nom;
};


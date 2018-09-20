#include "puzzle.h"

//Initialiser les valeures du jeu
void puzzle::init(ifstream &entree, string nomNoMap)
{
	_pieces[0] = new piece3Case('U', ' ', 'P', 'O', '\0');	//instance de la pi�ce U
	_pieces[1] = new piece3Case('V', 'P', ' ', 'O', '\0');	//instance de la pi�ce V
	_pieces[2] = new piece3Case('W', ' ', 'O', 'P', '\0');	//instance de la pi�ce W
	_pieces[3] = new piece2Case('X', 'P', 'P');				//instance de la pi�ce X
	_pieces[4] = new piece2Case('Y', 'P', 'O');				//instance de la pi�ce Y
	_pieces[5] = new piece3Case('Z', ' ', '\0', 'O', ' ');	//instance de la pi�ce Z

	//Initialiser la carte
	_carte.init(entree, nomNoMap);

	//Initialiser toutes les cases de la solution
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//Mettre des espaces
			_solution[i][j] = " ";
		}
	}
}

//Joue une partie de "Camouflage"
void puzzle::play()
{
	_succes = solve(0);
}

//R�souds une carte de "Camouflage" avec une pi�ce de d�part
bool puzzle::solve(int noPiece)
{
	//Chaques lignes
	for (int ligne = 0; ligne < _carte.getLigne(); ligne++)
	{
		//Chaques colonnes
		for (int colonne = 0; colonne < _carte.getColonne(); colonne++)
		{
			//Chaques rotations
			for (int rotation = 0; rotation < 4; rotation++)
			{
				//Si toutes les pi�ces sont plac�s
				if (noPiece == 6)
					return true;

				//Si la pi�ce entre dans l'emplacement
				if (match(noPiece, ligne, colonne))
				{
					//Place la pi�ce dans solution
					placePiece(noPiece, ligne, colonne);

					//On place une autre pi�ce
					if (!solve(noPiece + 1))

						//On la retire et on passe � une autre
						retirerPiece(noPiece, ligne, colonne);

					//La solution a �t�e trouv�e
					else
						return true;
				}
				//Effectue la rotation d'une pi�ce
				_pieces[noPiece]->rotate();
			}
		}
	}
	//Si toutes boucles ont tourn�s, la pi�ce avant celle-ci n'est pas bonne
	return false;
}

//Pour chaque case de la pi�ce, on la compare � la case de la carte
bool puzzle::match(int noPiece, int ligne, int colonne)
{
	//Pour chaque cases
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			//Si case valide
			if (_pieces[noPiece]->getValide(i, j))
			{
				//Si la case de la pi�ce est dans la carte
				if (colonne + j >= 4 && ligne + i >= 4)
					return false;

				//Si ours est sur autre chose que banquise
				if (_pieces[noPiece]->getValeur(i, j) == 'O'
					&& _carte.getCase(ligne + i, colonne + j) != 'B')
					return false;

				//Si poisson est sur autre chose que eau
				if (_pieces[noPiece]->getValeur(i, j) == 'P'
					&& _carte.getCase(ligne + i, colonne + j) != 'E')
					return false;

				//Si une autre piece est d�j� dans l'emplacement
				if (_solution[ligne + i][colonne + j] != " ")
					return false;
			}
		}
	//Si tout est faux, la pi�ce peut entrer dans l'emplacement
	return true;
}

//Placer une pi�ce dans la solution
void puzzle::placePiece(int noPiece, int ligne, int colonne)
{
	//Pour chaques cases
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)

			//Si valide
			if (_pieces[noPiece]->getValide(i, j))
			{
				//Efface le contenu de la case de la carte
				_solution[ligne + i][colonne + j].clear();

				//Ajoute le nom de la pi�ce
				_solution[ligne + i][colonne + j].push_back(_pieces[noPiece]->getNom());

				//Si la valeure de la pi�ce n'est pas vide
				if (_pieces[noPiece]->getValeur(i, j) != ' ')

					//On ajoute la valeure dans le tableau
					_solution[ligne + i][colonne + j].push_back(_pieces[noPiece]->getValeur(i, j));
			}
}

//Retirer une pi�ce de la solution
void puzzle::retirerPiece(int noPiece, int ligne, int colonne)
{
	//Pour chaques cases
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)

			//Si valide
			if (_pieces[noPiece]->getValide(i, j))

				//L'emplacement est maintenant vide
				_solution[ligne + i][colonne + j] = " ";
}

//Affiche les messages du jeu
void puzzle::print(ostream &os)const
{
	//Affiche la map en console et dans un fichier
	os << endl << "Pour la map suivante : " << endl;
	os << _carte << endl;

	//Si solution trouv�e
	if (_succes)
	{
		os << endl << "Voici la solution : " << endl;

		//Affiche chaques cases de la solution
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				os << _solution[i][j];
				if (j < 3)
				{
					os << ",";
				}
			}
			os << endl;
		}
	}
	//Sinon
	else
		os << endl << "Aucune solution n'a �t� trouv�.";
}

ostream &operator<<(ostream &os, const puzzle &game)
{
	game.print(os);
	return os;
}
/*
Nom:		Karl Boutin et �mile Loiselle
Programme:	main.cpp
Date:		2018-09-09
But:		Le jeu camouflage dans lequel on manipule une map
			et des pi�ces afin de trouver la solution du casse-t�te
			� l'aide d'un algorithme.
*/

#include"puzzle.h"
#include <ctime>

using namespace std;

//M�thodes
string ouvrirFichiers(ifstream &entree, ofstream &sortie);

int main()
{
	setlocale(LC_CTYPE, "fra");

	string temp;
	bool rejouer;

	puzzle		game;		//Une partie du jeu camouflage

	ifstream	entree;		//Fichier dans lequel on lit la map
	ofstream	sortie;		//Fichier dans lequel on ecrie la solution
	string		nomNoMap;	//Nom fichier de la carte

	do
	{
		//Ouvrir le fichier s'il existe
		nomNoMap = ouvrirFichiers(entree, sortie);

		//D�but du calcul du temps d'ex�cution
		clock_t begin = clock();

		//Initialiser le jeu
		game.init(entree, nomNoMap);

		//R�soudre la solution
		game.play();

		//Afficher le r�sultat du jeu
		cout << game;
		sortie << game;

		//Fin du calcul du temps d'ex�cution
		clock_t end = clock();
		//Calcul du temps d'ex�cution
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		//Affichage du temps d'ex�cution
		cout << endl << "Temps: " << elapsed_secs << " ms" << endl;

		//Fermer les fichiers
		entree.close();
		sortie.close();

		while (true)
		{
			//Rejouer
			cout << "Voulez-vous solutionner une autre carte? (o/n)";
			cin >> temp;
			cin.ignore();

			if (temp == "o")
			{
				rejouer = true;
				break;
			}
			else if (temp == "n")
			{
				rejouer = false;
				break;
			}
		}
	} while (rejouer);
	return 0;
}

//Ouvrir les fichiers et v�rifier si le fichier de lecture existe
string ouvrirFichiers(ifstream &entree, ofstream &sortie)
{
	string fichierEntree;

	//Boucle tant que le fichier n'est pas bon
	while (true)
	{
		cout << "Entrer la map a solutionner <Ex : Expert27> : ";
		getline(cin, fichierEntree);

		entree.open("map" + fichierEntree + ".txt");

		//Si le fichier s'est ouvert, on sort de la boucle
		if (entree.good())
			break;

		cout << endl << "Le fichier map" << fichierEntree;
		cout << ".txt n'existe pas!" << endl << endl;
	}

	//Ouvrir fichier sortie
	sortie.open("solution" + fichierEntree + ".txt");

	return fichierEntree;
}
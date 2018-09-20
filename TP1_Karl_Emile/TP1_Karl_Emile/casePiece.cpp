/*
=======================En-t�te=================================
Auteur:		�mile Loiselle
Date:		12 septembre
Programme:	casePiece.cpp
But:		Permet de manipuler des pi�ces 3 cases et 2 cases avec des
			op�rations de base comme faire une rotation des pieces,
			afficher les pieces ou meme modifier ou obtenir les
			valeurs de differentes cases
===============================================================
*/

#include "casePiece.h"

/*----------
---Parent---
----------*/

//Initialise la piece avec les valeures sp�cifi�s
void piece::init(char nom, char case1, char case2, char case3, char case4)
{
	setNom(nom);

	setValeur(0, 0, case1);
	setValeur(0, 1, case2);
	setValeur(1, 0, case3);
	setValeur(1, 1, case4);
}

//D�termine le nom d'une pi�ce
void piece::setNom(char nom)
{
	_nom = nom;
}

//D�termine la valeure d'une piece
void piece::setValeur(int i, int j, char valeur)
{
	assert((i >= 0 || i < 2) && (j >= 0 || j < 2));

	_cases[i][j].valeur = valeur;

	if (valeur == '\0')
		_cases[i][j].active = false;
	else
		_cases[i][j].active = true;
}

//Obtient le nom d'une pi�ce
char piece::getNom() const
{
	return _nom;
}

//Obtient la valeure d'une piece
char piece::getValeur(int i, int j) const
{
	assert((i == 0 || i == 1) && (j == 0 || j == 1));
	return _cases[i][j].valeur;
}

//V�rifie si la case sp�cifi�e contient les charact�res demand�s
bool piece::getValide(int i, int j) const
{
	assert((i == 0 || i == 1) && (j == 0 || j == 1));

	return _cases[i][j].active;
}

//Affiche le nom et lea valeure d'une piece
void piece::print(ostream& os)const
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			//Si pi�ce pas nulle
			if (!_cases[i][j].valeur == '\0')
			{
				os << getNom();				//Nom
				os << _cases[i][j].valeur;	//Valeure
				os << " ";					//Espace (clart�e)
			}
			else
			{
				os << "   ";				//3 espaces (clart�e)
			}
		}
		os << endl;
	}
}

ostream& operator<<(ostream& os, const piece& p)
{
	p.print(os);
	return os;
}

/*--------------------
---Pi�ce deux cases---
--------------------*/

//Constructeur vide mais lisible
piece2Case::piece2Case()
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			setValeur(i, j, '\0');
}

//Constructeur avec parametres
piece2Case::piece2Case(char nom, char case1, char case2)
{
	setNom(nom);

	setValeur(0, 0, case1);
	setValeur(0, 1, case2);
	setValeur(1, 0, '\0');
	setValeur(1, 1, '\0');
}

//Destructeur logique
piece2Case::~piece2Case()
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			setValeur(i, j, '\0');
}

//Fais une rotation des pieces dans le sens horaire
void piece2Case::rotate()
{
	//Variable temporaire permettant le transfert des valeures
	casePiece temp = _cases[0][0];

	//Piece � l'horizontale
	if (_cases[0][1].active)
	{
		_cases[1][0] = _cases[0][0];
		_cases[0][0] = _cases[0][1];
		_cases[0][1] = _cases[1][1];
	}

	//Pi�ce � la verticale
	else
	{
		temp = _cases[1][0];
		_cases[1][0] = _cases[1][1];
		_cases[0][1] = temp;
	}
}

/*---------------------
---Pi�ce trois cases---
-----------------------*/

//Constructeur vide mais lisible
piece3Case::piece3Case()
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			setValeur(i, j, '\0');
}

//Initialise une pi�ce � 4 cases
piece3Case::piece3Case(char nom, char case1, char case2, char case3, char case4)
{
	setNom(nom);

	setValeur(0, 0, case1);
	setValeur(0, 1, case2);
	setValeur(1, 0, case3);
	setValeur(1, 1, case4);
}

//Destructeur logique
piece3Case::~piece3Case()
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			setValeur(i, j, '\0');
}

//Fais une rotation des pieces dans le sens horaire
void piece3Case::rotate()
{
	casePiece temp = _cases[0][0];

	_cases[0][0] = _cases[1][0];
	_cases[1][0] = _cases[1][1];
	_cases[1][1] = _cases[0][1];
	_cases[0][1] = temp;
}
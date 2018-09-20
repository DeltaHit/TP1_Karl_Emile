/*
Nom:		Karl Boutin
Programme:	puzzle.h
Date:		2018-09-15
But:		Classe permetant de jouer une partie du jeu camouflage.
			Elle initialise le jeu pour ensuite trouver une solution
			� la carte choisie.
*/

#pragma once
#include"casePiece.h"
#include"map.h"

class puzzle
{
private:
	map			_carte;				//La carte du jeu
	string		_solution[4][4];	//La solution de la carte
	piece		*_pieces[6];		//Contient les pi�ces du jeu
	bool		_succes;			//D�termine si une solution a �t� trouv�

public:
	//Initialiser le jeu
	void	init(ifstream &entree, string nomNoMap);

	void	play();					//Joue une partie de "Camouflage"
	bool	solve(int);				//R�soud une carte de "Camouflage"
	bool	match(int, int, int);	//Compare une pi�ce � une case

	//Place ou enl�ve une pi�ce dans la solution
	void	placePiece(int, int, int);
	void	retirerPiece(int, int, int);

	//Affiche les messages du jeu
	void	print(ostream &os)const;
};
ostream &operator<<(ostream &os, const puzzle &game);
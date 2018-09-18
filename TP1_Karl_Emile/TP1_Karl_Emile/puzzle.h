/*
Nom:		Karl Boutin
Programme:	puzzle.h
Date:		2018-09-15
But:		Classe permetant de jouer une partie du jeu camouflage.
			Elle initialise le jeu pour ensuite trouver une solution
			a la carte choisie.
*/

#pragma once
#include"casePiece.h"
#include"map.h"

class Puzzle
{
private:
	Map			_carte;			//La carte du jeu
	Map			_solution;		//La solution de la carte
	piece		*_pieces[6];	//Contient les pi�ces du jeu

public:
	void	init(ifstream &entree, string nomNoMap);	//Initialiser le jeu
	void	print(ostream &os)const;					//Affiche les messages du jeu
	void	solve();									//Place les bonnes pi�ces aux bons endroits dans la carte
};
ostream &operator<<(ostream &os, const Puzzle &game);
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "constantes.h"
#include "editeur.h"
#include "fichiers.h"

void editeur(sf::RenderWindow* window)
{
	sf::Sprite* mur = NULL, * caisse = NULL, * objectif = NULL, * mario = NULL;
	sf::Event event;

	int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
	int objetActuel = MUR, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	// Chargement des objets et du niveau
	sf::Texture Tmur;
	texture.loadFromFile("image/mur.jpg");
	mur = new sf::Sprite(Tmur)

	sf::Texture Tcaisse;
	texture.loadFromFile("image/caisse.jpg");
	caisse = new sf::Sprite(Tcaisse)

	sf::Texture Tobjectif;
	texture.loadFromFile("image/objectif.png");
	objectif = new sf::Sprite(Tobjectif)

	sf::Texture Tmario;
	texture.loadFromFile("image/mario_bas.gif");
	mario = new sf::Sprite(Tmario)


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
	{
		objetActuel = MUR;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
	{
		objetActuel = CAISSE;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
	{
		objetActuel = OBJECTIF;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
	{
		objetActuel = MARIO;
	}
	//Pour que le joueur puisse quand meme jouer si son clavier n'a pas de pad : 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		objetActuel = MUR;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		objetActuel = CAISSE;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		objetActuel = OBJECTIF;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		objetActuel = MARIO;
	}


	//Placement objet
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	int x = mousePosition.x / TAILLE_BLOC;
	int y = mousePosition.y / TAILLE_BLOC;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		carte[x][y] = objetActuel;
	}

	//Retirer objet
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	int x = mousePosition.x / TAILLE_BLOC;
	int y = mousePosition.y / TAILLE_BLOC;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		carte[x][y] = VIDE;
	}

	//Sauvegarde et chargement du niveau
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		continuer = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		sauvegarderNiveau(carte);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		chargerNiveau(carte);
	}
}
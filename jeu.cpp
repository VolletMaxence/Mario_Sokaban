#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "constantes.h"
#include "jeu.h"

void jouer(sf::RenderWindow& window)
{
	sf::RenderWindow window{ sf::VideoMode(800, 600), "My window de BG" };

	sf::Sprite *mario[4] = { NULL }; // 4 surfaces pour chacune des directions de mario
	sf::Sprite *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL;
	SDL_Rect position, positionJoueur;
	sf::Event event;

	int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	// Chargement des sprites (décors, personnage...)
	sf::Texture mur;
	if (!texture.loadFromFile("image/mur.jpg"))
	{
		cout << "L'image des murs n'ont pas chargé";
	}

	sf::Texture caisse;
	if (!texture.loadFromFile("image/caisse.jpg"))
	{
		cout << "L'image des caisses n'ont pas chargé";
	}

	sf::Texture caisseOK;
	if (!texture.loadFromFile("image/caisse_ok.jpg"))
	{
		cout << "L'image des caisses OK n'ont pas chargé";
	}

	sf::Texture objectif;
	if (!texture.loadFromFile("image/objectif.png"))
	{
		cout << "L'image des objectifs n'ont pas chargé";
	}

	sf::Texture mario[BAS];
	if (!texture.loadFromFile("image/mario_bas.gif"))
	{
		cout << "L'image de Mario Bas n'a pas chargé";
	}

	sf::Texture mario[GAUCHE];
	if (!texture.loadFromFile("image/mario_gauche.gif"))
	{
		cout << "L'image de Mario Gauche n'a pas chargé";
	}

	sf::Texture mario[HAUT];
	if (!texture.loadFromFile("image/mario_haut.gif"))
	{
		cout << "L'image de Mario haut n'a pas chargé";
	}

	sf::Texture mario[DROITE];
	if (!texture.loadFromFile("image/mario_droite.gif"))
	{
		cout << "L'image de Mario droite n'a pas chargé";
	}


	marioActuel = mario[BAS]; // Mario sera dirigé vers le bas au départ

	// Chargement du niveau
	if (!chargerNiveau(carte))
		exit(EXIT_FAILURE); // On arrête le jeu si on n'a pas pu charger le niveau

	// Recherche de la position de Mario au départ
	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
		{
			if (carte[i][j] == MARIO) // Si Mario se trouve à cette position sur la carte
			{
				positionJoueur.x = i;
				positionJoueur.y = j;
				carte[i][j] = VIDE;
			}
		}
	}

	//Si besoin, mettre le fait de laisser les touche enfoncer pour bouger

	while (window.isOpen())
	{
		switch (event.type)
		{
		case SDL_QUIT:
			continuer = 0;
			break;
		case sf::Event::KeyPressed :
			switch (event.key.code)
			{
			case sf::Keyboard::isKeyPressed(sf::Keyboard::Escape):
				continuer = 0;
				break;
			case sf::Keyboard::isKeyPressed(sf::Keyboard::Up) :
				marioActuel = mario[HAUT];
				deplacerJoueur(carte, &positionJoueur, HAUT);
				break;
			case sf::Keyboard::isKeyPressed(sf::Keyboard::Down):
				marioActuel = mario[BAS];
				deplacerJoueur(carte, &positionJoueur, BAS);
				break;
			case sf::Keyboard::isKeyPressed(sf::Keyboard::Right):
				marioActuel = mario[DROITE];
				deplacerJoueur(carte, &positionJoueur, DROITE);
				break;
			case sf::Keyboard::isKeyPressed(sf::Keyboard::Left):
				marioActuel = mario[GAUCHE];
				deplacerJoueur(carte, &positionJoueur, GAUCHE);
				break;
			}
			break;
		}

		// Effacement de l'écran
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

		// Placement des objets à l'écran
		objectifsRestants = 0;

		for (i = 0; i < NB_BLOCS_LARGEUR; i++)
		{
			for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
			{
				position.x = i * TAILLE_BLOC;
				position.y = j * TAILLE_BLOC;

				switch (carte[i][j])
				{
				case MUR:
					SDL_BlitSurface(mur, NULL, ecran, &position);
					break;
				case CAISSE:
					SDL_BlitSurface(caisse, NULL, ecran, &position);
					break;
				case CAISSE_OK:
					SDL_BlitSurface(caisseOK, NULL, ecran, &position);
					break;
				case OBJECTIF:
					SDL_BlitSurface(objectif, NULL, ecran, &position);
					objectifsRestants = 1;
					break;
				}
			}

			sf::Sprite::setTextureRect()

		}

		// Si on n'a trouvé aucun objectif sur la carte, c'est qu'on a gagné
		if (!objectifsRestants)
			continuer = 0;

		// On place le joueur à la bonne position
		position.x = positionJoueur.x * TAILLE_BLOC;
		position.y = positionJoueur.y * TAILLE_BLOC;
		SDL_BlitSurface(marioActuel, NULL, ecran, &position);



		SDL_Flip(ecran);
	}

	// Désactivation de la répétition des touches (remise à 0)
	//SDL_EnableKeyRepeat(0, 0);

	// Libération des surfaces chargées
	SDL_FreeSurface(mur);
	SDL_FreeSurface(caisse);
	SDL_FreeSurface(caisseOK);
	SDL_FreeSurface(objectif);
	for (i = 0; i < 4; i++)
		SDL_FreeSurface(mario[i]);
}

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction)
{
	switch (direction)
	{
	case HAUT:
		if (pos->y - 1 < 0) // Si le joueur dépasse l'écran, on arrête
			break;
		if (carte[pos->x][pos->y - 1] == MUR) // S'il y a un mur, on arrête
			break;
		// Si on veut pousser une caisse, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre caisse, ou la limite du monde)
		if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) &&
			(pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR ||
				carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK))
			break;

		// Si on arrive là, c'est qu'on peut déplacer le joueur !
		// On vérifie d'abord s'il y a une caisse à déplacer
		deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);

		pos->y--; // On peut enfin faire monter le joueur (oufff !)
		break;


	case BAS:
		if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
			break;
		if (carte[pos->x][pos->y + 1] == MUR)
			break;

		if ((carte[pos->x][pos->y + 1] == CAISSE || carte[pos->x][pos->y + 1] == CAISSE_OK) &&
			(pos->y + 2 >= NB_BLOCS_HAUTEUR || carte[pos->x][pos->y + 2] == MUR ||
				carte[pos->x][pos->y + 2] == CAISSE || carte[pos->x][pos->y + 2] == CAISSE_OK))
			break;


		deplacerCaisse(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);

		pos->y++;
		break;


	case GAUCHE:
		if (pos->x - 1 < 0)
			break;
		if (carte[pos->x - 1][pos->y] == MUR)
			break;

		if ((carte[pos->x - 1][pos->y] == CAISSE || carte[pos->x - 1][pos->y] == CAISSE_OK) &&
			(pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR ||
				carte[pos->x - 2][pos->y] == CAISSE || carte[pos->x - 2][pos->y] == CAISSE_OK))
			break;


		deplacerCaisse(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);

		pos->x--;
		break;


	case DROITE:
		if (pos->x + 1 >= NB_BLOCS_LARGEUR)
			break;
		if (carte[pos->x + 1][pos->y] == MUR)
			break;

		if ((carte[pos->x + 1][pos->y] == CAISSE || carte[pos->x + 1][pos->y] == CAISSE_OK) &&
			(pos->x + 2 >= NB_BLOCS_LARGEUR || carte[pos->x + 2][pos->y] == MUR ||
				carte[pos->x + 2][pos->y] == CAISSE || carte[pos->x + 2][pos->y] == CAISSE_OK))
			break;

		deplacerCaisse(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);

		pos->x++;
		break;
	}
}

void deplacerCaisse(int *premiereCase, int *secondeCase)
{
	if (*premiereCase == CAISSE || *premiereCase == CAISSE_OK)
	{
		if (*secondeCase == OBJECTIF)
			*secondeCase = CAISSE_OK;
		else
			*secondeCase = CAISSE;

		if (*premiereCase == CAISSE_OK)
			*premiereCase = OBJECTIF;
		else
			*premiereCase = VIDE;
	}
}


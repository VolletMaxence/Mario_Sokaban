#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "constantes.h"
#include "editeur.h"
#include "fichiers.h"

void editeur(sf::RenderWindow window)
{
	sf::Sprite * mur = NULL, * caisse = NULL, * objectif = NULL, * mario = NULL;
	SDL_Rect position;
	sf::Event event;

	int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
	int objetActuel = MUR, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	// Chargement des objets et du niveau
	sf::Texture mur;
	if (!texture.loadFromFile("image/mur.jpg"));

	sf::Texture caisse;
	if (!texture.loadFromFile("image/caisse.jpg"));

	sf::Texture objectif;
	if (!texture.loadFromFile("image/objectif.png"));

	sf::Texture mario;
	if (!texture.loadFromFile("image/mario_bas.gif"));

	if (!chargerNiveau(carte))
		exit(EXIT_FAILURE);

	// Boucle infinie de l'éditeur
	while (continuer)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			continuer = 0;
			break;
		case sf::Event::MouseButtonPressed :
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				// On met l'objet actuellement choisi (mur, caisse...) à l'endroit du clic
				carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
				clicGaucheEnCours = 1; // On active un booléen pour retenir qu'un bouton est enfoncé
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) // Le clic droit sert à effacer
			{
				carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = VIDE;
				clicDroitEnCours = 1;
			}
			break;
		case sf::Event::MouseButtonReleased : // On désactive le booléen qui disait qu'un bouton était enfoncé
			if (event.button.button == SDL_BUTTON_LEFT)
				clicGaucheEnCours = 0;
			else if (event.button.button == SDL_BUTTON_RIGHT)
				clicDroitEnCours = 0;
			break;
		case sf::Event::MouseMoved :
			if (clicGaucheEnCours) // Si on déplace la souris et que le bouton gauche de la souris est enfoncé
			{
				carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objetActuel;
			}
			else if (clicDroitEnCours) // Pareil pour le bouton droit de la souris
			{
				carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
			}
			break;
		case sf::Event::KeyPressed :
			switch (event.key.code)
			{
			case sf::Keyboard::isKeyPressed(sf::Keyboard::Escape):
				continuer = 0;
				break;
			case sf::Keyboard::isKeyPressed(sf::Keyboard::S):
				sauvegarderNiveau(carte);
				break;
			case sf::Keyboard::isKeyPressed(sf::Keyboard::C):
				chargerNiveau(carte);
				break;
			case sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1):
				objetActuel = MUR;
				break;
			case sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2):
				objetActuel = CAISSE;
				break;
			case sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3):
				objetActuel = OBJECTIF;
				break;
			case sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4):
				objetActuel = MARIO;
				break;
			//Pour que le joueur puisse quand meme jouer si son clavier n'a pas de pad : 
			case sf::Keyboard::isKeyPressed(sf::Keyboard::Num1):
				objetActuel = MUR;
				break;
			case sf::Keyboard::isKeyPressed(sf::Keyboard::Num2):
				objetActuel = CAISSE;
				break;
			case sf::Keyboard::isKeyPressed(sf::Keyboard::Num3):
				objetActuel = OBJECTIF;
				break;
			case sf::Keyboard::isKeyPressed(sf::Keyboard::Num4):
				objetActuel = MARIO;
				break;
			}
			break;
		}

		// Effacement de l'écran
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

		// Placement des objets à l'écran
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
				case OBJECTIF:
					SDL_BlitSurface(objectif, NULL, ecran, &position);
					break;
				case MARIO:
					SDL_BlitSurface(mario, NULL, ecran, &position);
					break;
				}
			}
		}

		// Mise à jour de l'écran
		//SDL_Flip(ecran);
	}

	//SDL_FreeSurface(mur);
	//SDL_FreeSurface(caisse);
	//SDL_FreeSurface(objectif);
	//SDL_FreeSurface(mario);
}
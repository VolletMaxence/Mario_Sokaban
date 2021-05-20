#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "constantes.h"
#include "editeur.h"
#include "fichiers.h"


void editeur(sf::RenderWindow* window)
{
	using namespace std;

	sf::Sprite vide, mur, caisse, caisseOK, objectif, mario;
	sf::Sprite *TotalSprite[6] = { &vide, &mur, &caisse, &caisseOK, &objectif, &mario };


	int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
	int objetActuel = MUR, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	// Chargement des objets et du niveau
	sf::Texture Tvide;
	if (!Tvide.loadFromFile("image/vide.png"))
	{
		cout << "L'image du vide n'a pas chargé";
	}
	vide.setTexture(Tvide);

	sf::Texture Tmur;
	if (!Tmur.loadFromFile("image/mur.jpg"))
	{
		cout << "L'image du mur n'a pas chargé";
	}
	mur.setTexture(Tmur); 

	sf::Texture Tcaisse;
	if (!Tcaisse.loadFromFile("image/caisse.jpg"))
	{
		cout << "L'image de la caisse n'a pas chargé";
	}
	caisse.setTexture(Tcaisse);

	sf::Texture Tobjectif;
	if (!Tobjectif.loadFromFile("image/objectif.png"))
	{
		cout << "L'image de l'objectif n'a pas chargé";

	}
	objectif.setTexture(Tobjectif);

	sf::Texture TcaisseOK;
	if (!Tobjectif.loadFromFile("image/caisse_ok.jpg"))
	{
		cout << "L'image de l'caisse_ok n'a pas chargé";

	}
	caisseOK.setTexture(TcaisseOK);

	sf::Texture Tmario;
	if(!Tmario.loadFromFile("image/mario_bas.gif"))
	{
		cout << "L'image de Mario n'a pas chargé";
	}
	mario.setTexture(Tmario);


	//Touche pour les differents éléments
	while(continuer==1)
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			sf::Sprite objetSelectionner;

			if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
			{
				objetSelectionner.setTexture(Tmur);
			}
			if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
			{
				objetSelectionner.setTexture(Tcaisse);
			}
			if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
			{
				objetSelectionner.setTexture(Tobjectif);
			}
			if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
			{
				objetSelectionner.setTexture(Tmario);
			}

			
			//Sauvegarde et chargement du niveau
			if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				continuer = 0;
			}
			if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				sauvegarderNiveau(carte);
				continuer = 0;
			}
			if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			{
				chargerNiveau(carte);
			}

		}

		//Placement objet
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		sf::FloatRect Position;
		for (int ligne = 0; ligne < NB_BLOCS_LARGEUR; ligne++) {
			for (int colonne = 0; colonne < NB_BLOCS_HAUTEUR; colonne++)
			{
				int x = mousePosition.x / TAILLE_BLOC;
				int y = mousePosition.y / TAILLE_BLOC;
				Position.top = colonne * TAILLE_BLOC;
				Position.left = ligne * TAILLE_BLOC;
				if (event.type == sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					carte[x][y] = objetActuel;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Sprite objetSelectionner;

					objetSelectionner.setTexture(Tvide);
					carte[x][y] = objetActuel;
				}
				sf::Sprite* sprite = TotalSprite[carte[ligne][colonne]];
				sprite->setPosition(Position.left, Position.top);
				window->draw(*sprite);
			}
		}

		
		window->draw(caisse);
		window->draw(caisseOK);
		window->draw(mur);
		window->draw(objectif);
		window->draw(mario);
		


		window->display();
	}

}
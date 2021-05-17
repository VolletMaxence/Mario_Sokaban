#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "constantes.h"
#include "editeur.h"
#include "fichiers.h"
//#include "jeu.h"




int main(int argc, char **argv[])
{
	using namespace std;

	sf::RenderWindow window(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32), "My window de BG");

	//Texture du menu
	sf::Texture texture;
	if (!texture.loadFromFile("image/menu.jpg"))
	{
		cout << "L'image du menu n'a pas charg�";
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);


	// on fait tourner le programme jusqu'� ce que la fen�tre soit ferm�e
	while (window.isOpen())
	{

		//Event pour naviguer entre les options
		sf::Event event;

		// on inspecte tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente it�ration
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			// �v�nement "fermeture demand�e" : on ferme la fen�tre
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				if (event.key.code == sf::Keyboard::Numpad1 || event.key.code == sf::Keyboard::Num1) //Ajout du 1 de la barre pour les joueurs sans pad
				{
					//Envoie vers la page de jeu
					//jouer(&window);
				}
				if (event.key.code == sf::Keyboard::Numpad2 || event.key.code == sf::Keyboard::Num2) //Ajout du 2 de la barre pour les joueurs sans pad
				{
					//Envoie vers l'editeur de niveau
					editeur(&window);
				}
			}
		}
		window.clear(sf::Color::Black);
		window.draw(sprite);
		window.display();
	}
	return 0;
}

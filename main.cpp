#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "constantes.h"
#include "jeu.h"
#include "editeur.h"

int main(int argc, char *argv[])
{
	*ecran = NULL;

	//Texture du menu
	sf::RenderWindow window{sf::VideoMode(800, 600), "My window de BG"};
	sf::Texture texture;
	if(!texture.loadFromFile("image/menu.jpg"));

	sf::Sprite sprite;
	sprite.setTexture(texture);

	//Event pour naviguer entre les options
	sf::Event event;

	sf::VideoMode::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32);

	ecran = sf::VideoMode::getDesktopMode();

	// on fait tourner le programme jusqu'� ce que la fen�tre soit ferm�e
	while (window.isOpen())
	{
		window.draw(sprite);

		// on inspecte tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente it�ration
		sf::Event event;
		while (window.pollEvent(event))
		{
			// �v�nement "fermeture demand�e" : on ferme la fen�tre
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if(event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Numpad1 || event.key.code == sf::Keyboard::Num1) //Ajout du 1 de la barre pour les joueurs sans pad
				{
					//Envoie vers la page de jeu
					jouer(ecran);
				}
				else if (event.key.code == sf::Keyboard::Numpad2 || event.key.code == sf::Keyboard::Num2) //Ajout du 2 de la barre pour les joueurs sans pad
				{
					//Envoie vers l'editeur de niveau
					editeur(ecran);
				}
			}
		}

		window.display();
	}

	return 0;
}
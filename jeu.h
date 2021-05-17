#ifndef DEF_JEU
#define DEF_JEU

void jouer(sf::RenderWindow* ecran);
void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::RectangleShape *pos, int direction);
void deplacerCaisse(int *premiereCase, int *secondeCase);


#endif
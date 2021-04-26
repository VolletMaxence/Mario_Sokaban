#ifndef DEF_JEU
#define DEF_JEU

void jouer(sf::RenderWindow window);
void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction);
void deplacerCaisse(int *premiereCase, int *secondeCase);


#endif
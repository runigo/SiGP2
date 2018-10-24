/*
Copyright octobre 2018, Stephan Runigo
runigo@free.fr
SiGP 2.2  simulateur de gaz parfait
Ce logiciel est un programme informatique servant à simuler un gaz et à
en donner une représentation graphique. Il permet d'observer une détente
de Joule ainsi que des transferts thermiques avec des thermostats.
Ce logiciel est régi par la licence CeCILL soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA
sur le site "http://www.cecill.info".
En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée. Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard l'attention de l'utilisateur est attirée sur les risques
associés au chargement, à l'utilisation, à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant des connaissances informatiques approfondies. Les
utilisateurs sont donc invités à charger et tester l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/

#ifndef _CAPTEURS_
#define _CAPTEURS_

#include "../donnees/constantes.h"
#include <SDL2/SDL.h>

typedef struct CapteursT capteursT;
	struct CapteursT
		{
/*
		SDL_Point point[2048] = {{0}};
	static int       i = 0;

	point[i].x = p.coord2.x;
	point[i].y = p.coord2.y;

	if(++i > 2048)
		i = 0;

	SDL_SetRenderDrawColor(rendu, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(rendu, point, i);
    SDL_Point coord1;
    SDL_Point coord2;
*/
		SDL_Point capteur[DUREE_CAPTEURS][CAPTEURS];
		int yZero[CAPTEURS]; // Positon de l'origine
		int xZero[CAPTEURS]; // Positon de l'origine
		};

int capteursInitialise(capteursT * capteurs);

int capteursMiseAJour(capteursT * capteurs, int numero);
int capteursRotatifs(capteursT * capteurs);
int capteursTriangles(capteursT * capteurs);
int capteursLineaires(capteursT * capteurs);

#endif

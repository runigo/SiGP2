
/*
Copyright avril 2018, Stephan Runigo
runigo@free.fr
SiGP 2.0  simulateur de gaz parfait
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
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement,  à l'utilisation,  à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant  des  connaissances  informatiques approfondies. Les
utilisateurs sont donc invités à charger  et  tester  l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/

#include "graphique.h"

int graphiqueDestruction(graphiqueT * graphique)
	{
	SDL_DestroyRenderer((*graphique).rendu);
	return 0;
	}


int graphiqueInitialisation(graphiqueT * graphique, interfaceT * interface, int taille, int fond)
	{
	(void)taille;
		// Création du rendu
	(*graphique).rendu = SDL_CreateRenderer((*interface).fenetre, -1 , 
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(NULL == (*graphique).rendu)
		{
		fprintf(stderr, "interfaceInitialisation : Erreur SDL_CreateRenderer : %s \n", SDL_GetError());
		return EXIT_FAILURE;
		}


	//SDL_Color orange = {255, 127, 40, 255};
	(*graphique).fond.r = fond;
	(*graphique).fond.g = fond;
	(*graphique).fond.b = fond;
	(*graphique).fond.a = 255;
	(*graphique).contraste.r = 255-fond;
	(*graphique).contraste.g = 255-fond;
	(*graphique).contraste.b = 255-fond;
	(*graphique).contraste.a = 255;
	(*graphique).orange.r = 255;
	(*graphique).orange.g = 127;
	(*graphique).orange.b = 40;
	(*graphique).orange.a = 255;
	(*graphique).gris.r = 127;
	(*graphique).gris.g = 127;
	(*graphique).gris.b = 127;
	(*graphique).gris.a = 255;
	(*graphique).cyan.r = 127;
	(*graphique).cyan.g = 40;
	(*graphique).cyan.b = 255;
	(*graphique).cyan.a = 255;
	(*graphique).vert.r = 173;
	(*graphique).vert.g = 255;
	(*graphique).vert.b = 47;
	(*graphique).vert.a = 255;

	//SDL_Texture *particule;

	SDL_Surface *image = 0;

	image = SDL_LoadBMP("./interface/particule.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, particule.bmp : %s\n",SDL_GetError());
		return 0;
		}
	(*graphique).particule = SDL_CreateTextureFromSurface((*graphique).rendu, image);
	SDL_FreeSurface(image);
	if ((*graphique).particule == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

		// Activation de la transparence
	//SDL_BLENDMODE_NONE || SDL_BLENDMODE_BLEND || SDL_BLENDMODE_ADD || SDL_BLENDMODE_MOD
	if(SDL_SetTextureBlendMode((*graphique).particule, SDL_BLENDMODE_MOD) < 0)
		fprintf(stderr, "grapheInitialisation : Erreur SDL_SetRenderDrawBlendMode : %s.", SDL_GetError());

	return 0;
}

int graphiqueNettoyage(graphiqueT * graphique)
	{
	//int fond = (*graphique).fond;
	SDL_SetRenderDrawColor((*graphique).rendu, (*graphique).fond.r, (*graphique).fond.g, (*graphique).fond.b, 0);//SDL_ALPHA_OPAQUE
	SDL_RenderClear((*graphique).rendu);
	//SDL_SetRenderDrawColor((*graphique).rendu, 255-(*graphique).fond.r, 255-(*graphique).fond.g, 255-(*graphique).fond.b, 0);
	return 0;
	}

int graphiqueMiseAJour(graphiqueT * graphique)
	{
	SDL_RenderPresent((*graphique).rendu);
	return 0;
	}

int graphiqueChangeCouleur(graphiqueT * graphique, SDL_Color couleur)
	{
	if(SDL_SetRenderDrawColor((*graphique).rendu, couleur.r, couleur.g, couleur.b, couleur.a) < 0)
	return -1;
	//if(SDL_RenderClear(renderer) < 0)
		//return -1;
	return 0;  
	}

void graphiqueDessineGraphe(graphiqueT * graphique, grapheT * graphe)
	{
	int i, x, y;
	//int rayon = (*graphe).rayon;
	int centrage = 4;
	//SDL_Rect coordonnee = {0, 0, (*graphique).taille, (*graphique).taille};
	SDL_Rect coordonnee = {0, 0, 8, 8};

	  //fprintf(stderr, "Particules\n");
		// Particules
	//graphiqueChangeCouleur(graphique, (*graphique).orange);
	for(i=0;i<NOMBRE;i++)
		{/*
		x=(*graphe).ancienAbscisse[i];
		y=(*graphe).ancienOrdonnee[i];
		coordonnee.x = x - centrage;
		coordonnee.y = y - centrage;*/
		//SDL_RenderCopy((*graphique).rendu, (*graphique).particule, NULL, &coordonnee);
		//X=(*graphe).actuelAbscisse[i];
		//Y=(*graphe).actuelOrdonnee[i];
		//coordonnee.x = X - centrage;
		//coordonnee.y = Y - centrage;
		//SDL_RenderCopy((*graphique).rendu, (*graphique).particule, NULL, &coordonnee);
		//SDL_RenderDrawLine((*graphique).rendu, X, Y, x, y);
		x=(*graphe).nouveauAbscisse[i];
		y=(*graphe).nouveauOrdonnee[i];
		coordonnee.x = x - centrage;
		coordonnee.y = y - centrage;
		SDL_RenderCopy((*graphique).rendu, (*graphique).particule, NULL, &coordonnee);
		//SDL_RenderDrawLine((*graphique).rendu, X, Y, x, y);
		}

		// Parois horizontales
	//graphiqueLigneDroite((*graphe).ax, (*graphe).dy, (*graphe).cx, (*graphe).dy, couleurTrace1);
	//graphiqueLigneDroite((*graphe).ax, (*graphe).gy, (*graphe).cx, (*graphe).gy, couleurTrace1);
	graphiqueChangeCouleur(graphique, (*graphique).contraste);

	SDL_RenderDrawLine((*graphique).rendu, (*graphe).ax, (*graphe).dy, (*graphe).cx, (*graphe).dy);
	SDL_RenderDrawLine((*graphique).rendu, (*graphe).ax, (*graphe).gy, (*graphe).cx, (*graphe).gy);
		// Parois verticales
	//graphiqueLigneDroite((*graphe).ax, (*graphe).dy, (*graphe).ax, (*graphe).gy, couleurTrace1);
	//graphiqueLigneDroite((*graphe).cx, (*graphe).dy, (*graphe).cx, (*graphe).gy, couleurTrace1);
	graphiqueChangeCouleur(graphique, (*graphique).contraste);

	SDL_RenderDrawLine((*graphique).rendu, (*graphe).ax, (*graphe).dy, (*graphe).ax, (*graphe).gy);
	SDL_RenderDrawLine((*graphique).rendu, (*graphe).cx, (*graphe).dy, (*graphe).cx, (*graphe).gy);

		// Paroi centrale
	if((*graphe).cloison != 0)
		{
		//graphiqueLigneDroite((*graphe).bx, (*graphe).dy, (*graphe).bx, (*graphe).ey, couleurTrace1);
		//graphiqueLigneDroite((*graphe).bx, (*graphe).fy, (*graphe).bx, (*graphe).gy, couleurTrace1);
	graphiqueChangeCouleur(graphique, (*graphique).contraste);

	SDL_RenderDrawLine((*graphique).rendu, (*graphe).bx, (*graphe).dy, (*graphe).bx, (*graphe).ey);
	SDL_RenderDrawLine((*graphique).rendu, (*graphe).bx, (*graphe).fy, (*graphe).bx, (*graphe).gy);
		}

	return;
	}


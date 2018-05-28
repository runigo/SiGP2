
/*
Copyright mai 2018, Stephan Runigo
runigo@free.fr
SiGP 2.1  simulateur de gaz parfait
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


int graphiqueCreation(graphiqueT * graphique, interfaceT * interface)
	{
	int largeur;
	int hauteur;
	SDL_GetWindowSize((*interface).fenetre, &largeur, &hauteur);
	(*graphique).largeur=largeur;
	(*graphique).hauteur=hauteur;

	(*graphique).taille=TAILLE;

		// Création du rendu
	(*graphique).rendu = SDL_CreateRenderer((*interface).fenetre, -1 , 
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(NULL == (*graphique).rendu)
		{
		fprintf(stderr, "interfaceInitialisation : Erreur SDL_CreateRenderer : %s \n", SDL_GetError());
		return EXIT_FAILURE;
		}

	int fond = 10;
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

	int retour = 0;

	SDL_Surface *image = 0;

	image = SDL_LoadBMP("./interface/particule.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, particule.bmp : %s\n",SDL_GetError());
		retour = 0;
		}
	(*graphique).particule = SDL_CreateTextureFromSurface((*graphique).rendu, image);
	SDL_FreeSurface(image);
	if ((*graphique).particule == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour = 0;
		}

		// Activation de la transparence
	//SDL_BLENDMODE_NONE || SDL_BLENDMODE_BLEND || SDL_BLENDMODE_ADD || SDL_BLENDMODE_MOD
	if(SDL_SetTextureBlendMode((*graphique).particule, SDL_BLENDMODE_MOD) < 0)
		fprintf(stderr, "grapheInitialisation : Erreur SDL_SetRenderDrawBlendMode : %s.", SDL_GetError());

	SDL_Surface *panneau = 0;

	panneau = SDL_LoadBMP("./interface/sigp.bmp");
	if (!panneau)
		{
		fprintf(stderr,"ERREUR chargement image, sigp.bmp : %s\n",SDL_GetError());
		retour = 1;
		}
	(*graphique).SiGP = SDL_CreateTextureFromSurface((*graphique).rendu, panneau);
	SDL_FreeSurface(panneau);
	if ((*graphique).SiGP == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour = 2;
		}

	SDL_Surface *lumiereVerte = 0;

	lumiereVerte = SDL_LoadBMP("./interface/lumiereVerte.bmp");
	if (!lumiereVerte)
		{
		fprintf(stderr,"ERREUR chargement image, lumiereVerte.bmp : %s\n",SDL_GetError());
		retour = 5;
		}
	(*graphique).lumiereVerte = SDL_CreateTextureFromSurface((*graphique).rendu, lumiereVerte);
	SDL_FreeSurface(lumiereVerte);
	if ((*graphique).lumiereVerte == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour = 6;
		}

	SDL_Surface *lumiereRouge = 0;

	lumiereRouge = SDL_LoadBMP("./interface/lumiereRouge.bmp");
	if (!lumiereRouge)
		{
		fprintf(stderr,"ERREUR chargement image, lumiereRouge.bmp : %s\n",SDL_GetError());
		retour = 7;
		}
	(*graphique).lumiereRouge = SDL_CreateTextureFromSurface((*graphique).rendu, lumiereRouge);
	SDL_FreeSurface(lumiereRouge);
	if ((*graphique).lumiereRouge == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour = 8;
		}


	return retour;
}

int graphiqueNettoyage(graphiqueT * graphique)
	{
	SDL_RenderClear((*graphique).rendu);
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
		{return -1;}
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
	for(i=0;i<NOMBRE;i++)
		{
		x=(*graphe).abscisse[i];
		y=(*graphe).ordonnee[i];
		coordonnee.x = x - centrage;
		coordonnee.y = y - centrage;
		SDL_RenderCopy((*graphique).rendu, (*graphique).particule, NULL, &coordonnee);
		}

	graphiqueChangeCouleur(graphique, (*graphique).contraste);

		// Parois horizontales

	SDL_RenderDrawLine((*graphique).rendu, (*graphe).ax, (*graphe).dy, (*graphe).cx, (*graphe).dy);
	SDL_RenderDrawLine((*graphique).rendu, (*graphe).ax, (*graphe).gy, (*graphe).cx, (*graphe).gy);
	SDL_RenderDrawLine((*graphique).rendu, (*graphe).ax, (*graphe).dy-1, (*graphe).cx, (*graphe).dy-1);
	SDL_RenderDrawLine((*graphique).rendu, (*graphe).ax, (*graphe).gy+1, (*graphe).cx, (*graphe).gy+1);

		// Parois verticales

	SDL_RenderDrawLine((*graphique).rendu, (*graphe).ax, (*graphe).dy, (*graphe).ax, (*graphe).gy);
	SDL_RenderDrawLine((*graphique).rendu, (*graphe).cx, (*graphe).dy, (*graphe).cx, (*graphe).gy);
	SDL_RenderDrawLine((*graphique).rendu, (*graphe).ax-1, (*graphe).dy, (*graphe).ax-1, (*graphe).gy);
	SDL_RenderDrawLine((*graphique).rendu, (*graphe).cx+1, (*graphe).dy, (*graphe).cx+1, (*graphe).gy);

		// Paroi centrale
	if((*graphe).cloison != 0)
		{
		SDL_RenderDrawLine((*graphique).rendu, (*graphe).bx, (*graphe).dy, (*graphe).bx, (*graphe).ey);
		SDL_RenderDrawLine((*graphique).rendu, (*graphe).bx, (*graphe).fy, (*graphe).bx, (*graphe).gy);
		SDL_RenderDrawLine((*graphique).rendu, (*graphe).bx-1, (*graphe).dy, (*graphe).bx-1, (*graphe).ey);
		SDL_RenderDrawLine((*graphique).rendu, (*graphe).bx-1, (*graphe).fy, (*graphe).bx-1, (*graphe).gy);
		}

	return;
	}


/*
Copyright octobre 2018, Stephan Runigo
runigo@free.fr
SiGP 2.1.5  simulateur de gaz parfait
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

#include "graphe.h"
int grapheMiseAJourLongueur(grapheT * graphe, int largeur, int hauteur)
	{
			// Points du montage
		//	
		//			ax	bx	cx
		//
		//		dy	-----------------
		//			|	|	|
		//		ey	|	-	|
		//		fy	|	-	|
		//			|	|	|
		//		gy	-----------------

	(*graphe).zoneX=0.8394*largeur;
	(*graphe).zoneY=0.61562*hauteur;
	float longueur=2*(*graphe).zoneY;

	if((*graphe).zoneX<longueur) longueur=(*graphe).zoneX;

	float X = longueur/2 - MARGE - (*graphe).taille - TRAIT_ENCEINTE - TRAIT_CLOISON/2;

	(*graphe).facteur=X/HAUTEUR;

		// Absisses
	(*graphe).bx = longueur/2;
		if((*graphe).cloison==0)
			{
			(*graphe).ax = (*graphe).bx - X;// -(*graphe).taille/4
			(*graphe).cx = (*graphe).bx + X + TRAIT_CLOISON/2 +(*graphe).taille/4;
			}
		else
			{
			(*graphe).ax = (*graphe).bx - X - TRAIT_CLOISON/2 -(*graphe).taille/2;
			(*graphe).cx = (*graphe).bx + X + TRAIT_CLOISON/2 +(*graphe).taille/2;
			}

		// Ordonnées
	(*graphe).dy = MARGE+TRAIT_ENCEINTE;
	(*graphe).gy = MARGE+TRAIT_ENCEINTE+X+(*graphe).taille/2;

	(*graphe).ey = 0.5*((*graphe).dy+(*graphe).gy) - (*graphe).trou;
	(*graphe).fy = 0.5*((*graphe).dy+(*graphe).gy) + (*graphe).trou;

	return 0;
	}

int grapheInitialise(grapheT * graphe)
	{
	int i;

	(*graphe).taille = TAILLE_MIN + 1;
	(*graphe).facteur=(0.8394*FENETRE_X/2 - MARGE -3-1.5*(*graphe).taille)/HAUTEUR;

	for(i=0;i<(NOMBRE);i++)
		{
		(*graphe).abscisse[i]=LARGEUR/2;
		(*graphe).ordonnee[i]=HAUTEUR/2;
		(*graphe).droite[i]=1;
		}

		fprintf(stderr, " Initialisation du graphe\n");
			// Points du montage
		//	
		//			ax	bx	cx
		//
		//		dy	-----------------
		//			|	|	|
		//		ey	|	-	|
		//		fy	|	-	|
		//			|	|	|
		//		gy	-----------------

		// Absisses
	(*graphe).ax = MARGE/2;
	(*graphe).bx = LARGEUR/2;
	(*graphe).cx = LARGEUR - MARGE/2;

		// Ordonnées
	(*graphe).dy = MARGE/2;
	(*graphe).ey = HAUTEUR/2 - RAYON_TROU;
	(*graphe).fy = HAUTEUR/2 + RAYON_TROU;
	(*graphe).gy = HAUTEUR - MARGE/2;


	(*graphe).zoneX=0.8394*FENETRE_X;
	(*graphe).zoneY=0.8546*FENETRE_Y;

	(*graphe).taille = TAILLE_MIN*(*graphe).facteur;
	(*graphe).cloison = 0;	//
	(*graphe).thermostat = 0;	// 
	(*graphe).trou = RAYON_TROU;
	(*graphe).demon = 0;	// O ou 1

	return 0;
	}

int grapheMiseAJourTrou(grapheT * graphe)
	{
	(*graphe).ey = 0.5*((*graphe).dy+(*graphe).gy) - (*graphe).trou;
	(*graphe).fy = 0.5*((*graphe).dy+(*graphe).gy) + (*graphe).trou;
	return 0;
	}

//////////////////////////////////////////////////////////////////


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

#include "graphe.h"

int grapheInitialise(grapheT * graphe)
	{
	int i;

	(*graphe).rayon = TAILLE/2;
	if((*graphe).rayon < 1) (*graphe).rayon = 1;

	for(i=0;i<(NOMBRE);i++)
		{
		(*graphe).abscisse[i]=LARGEUR/2;
		(*graphe).ordonnee[i]=HAUTEUR/2;
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

	(*graphe).cloison = 0;	//
	(*graphe).thermostat = 0;	// 
	(*graphe).trou = RAYON_TROU;

	return 0;
	}

int grapheChangeTrou(grapheT * graphe, int trou)
	{
	(*graphe).ey = HAUTEUR/2 - trou;
	(*graphe).fy = HAUTEUR/2 + trou;
	return 0;
	}

//////////////////////////////////////////////////////////////////

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

#include "capteurs.h"

int capteursInitialise(capteursT * capteurs, int largeur, int hauteur)
	{
	int i, j;
	int x, y;
	for(j=0;j<CAPTEURS;j++)
		{
		(*capteurs).capteur[j].yZero=300; // Positon de l'origine capteur[CAPTEURS]
		(*capteurs).capteur[j].xZero=200+100*j; // Positon de l'origine
		for(i=0;i<DUREE_CAPTEURS;i++)
			{
			x=300 + i + j*100;
			y=300 + (int)(50*sin(i/1.9));
			(*capteurs).capteur[j].gauche[i].x=x;
			(*capteurs).capteur[j].gauche[i].y=y;
			(*capteurs).capteur[j].droite[i].x= x+50;
			(*capteurs).capteur[j].droite[i].y=y+50;
			}
		}
	for(j=0;j<CAPTEURS;j++)
		{
		(*capteurs).capteur[j].largeur = largeur; // axe x
		(*capteurs).capteur[j].hauteur = hauteur; // axe y
		}
/*
 	capteursMiseAJourLongueur(capteurs, FENETRE_X, FENETRE_Y);

	float a;
	int k, x0;
	for(j=0;j<CAPTEURS/2;j++)
		{
		k=2*j;
		x0=(*capteurs).xZero[k];
		a=(float)(largeur+x0) / (float)(DUREE_CAPTEURS);
		for(i=0;i<DUREE_CAPTEURS;i++)
			{
			(*capteurs).capteur[i][2*j].x=(int)(a*i)+x0;
			(*capteurs).capteur[i][2*j+1].x=(int)(a*i)+x0;
			}
		}
*/
	return 0;
	}

int capteursMiseAJourLongueur(capteursT * capteurs, int largeur, int hauteur)
	{
	(void)largeur;
	(void)hauteur;
	(void)capteurs;
/*
	(*capteurs).capteur[j].yZero=500; // Température à gauche
	(*capteurs).capteur[j].xZero=100; // 	x

	(*capteurs).capteur[j].yZero=500; // Température à droite
	(*capteurs).capteur[j].xZero[1]=100; // x
*/
	(*capteurs).capteur[1].yZero=500; // Nombre à gauche
	(*capteurs).capteur[1].xZero=200; // x

/*
	(*capteurs).capteur[j].yZero[4]=500; // l. p. m. à gauche
	(*capteurs).capteur[j].xZero[4]=300; // x

	(*capteurs).capteur[j].yZero[5]=500; // l. p. m. à droite
	(*capteurs).capteur[j].xZero[5]=300; // x
*/
	//(*capteurs).hauteur=(int)(0.1393568*hauteur); // longueur de l'axe y 91 / 653
/*
	(*capteurs).capteur[0].yZero=(int)(0.797856049*hauteur); // Température à gauche
	(*capteurs).capteur[0].xZero=(int)(0.06822107*largeur); // 	x

	(*capteurs).capteur.yZero[1]=(int)(0.797856049*hauteur); // Température à droite
	(*capteurs).capteur.xZero[1]=(int)(0.06822107*largeur); // x

	(*capteurs).capteur.yZero[2]=(int)(0.797856049*hauteur); // Nombre à gauche
	(*capteurs).capteur.xZero[2]=(int)(0.255613126*largeur); // x

	(*capteurs).capteur.yZero[3]=(int)(0.797856049*hauteur); // Nombre à droite
	(*capteurs).capteur.xZero[3]=(int)(0.255613126*largeur); // x

	(*capteurs).capteur.yZero[4]=(int)(0.797856049*hauteur); // l. p. m. à gauche
	(*capteurs).capteur.xZero[4]=(int)(0.45164076*largeur); // x

	(*capteurs).capteur.yZero[5]=(int)(0.797856049*hauteur); // l. p. m. à droite
	(*capteurs).capteur.xZero[5]=(int)(0.45164076*largeur); // x

	(*capteurs).capteur.largeur=(int)(0.1849776*largeur); // longueur de l'axe x 164 165 165 / 892
	(*capteurs).capteur.hauteur=(int)(0.1393568*hauteur); // longueur de l'axe y 91 / 653
*/
/*
	float a;
	int i, j, k, x0;
	for(j=0;j<CAPTEURS/2;j++)
		{
		k=2*j;
		x0=(*capteurs).xZero[k];
		a=(float)((*capteurs).largeur+x0) / (float)(DUREE_CAPTEURS);
		for(i=0;i<DUREE_CAPTEURS;i++)
			{
			(*capteurs).capteur[i][2*j].x=(int)(a*i)+x0;
			(*capteurs).capteur[i][2*j+1].x=(int)(a*i)+x0;
			}
		}
*/
	return 0;
	}


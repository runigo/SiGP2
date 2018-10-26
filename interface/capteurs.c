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
	for(i=0;i<CAPTEURS;i++)
		{
		(*capteurs).yZero[i]=0; // Positon de l'origine
		(*capteurs).xZero[i]=0; // Positon de l'origine
		for(j=0;j<DUREE_CAPTEURS;j++)
			{
			(*capteurs).capteur[j][i].x=largeur;
			(*capteurs).capteur[j][i].y=hauteur;
			}
		}
	return 0;
	}

int capteursMiseAJourLongueur(capteursT * capteurs, int largeur, int hauteur)
	{
	(*capteurs).yZero[0]=(int)(0.797856049*largeur); // Température à gauche
	(*capteurs).xZero[0]=(int)(0.06822107*hauteur); // 	x

	(*capteurs).yZero[1]=(int)(0.797856049*largeur); // Température à droite
	(*capteurs).xZero[1]=(int)(0.06822107*hauteur); // x

	(*capteurs).yZero[2]=(int)(0.797856049*largeur); // Nombre à gauche
	(*capteurs).xZero[2]=(int)(0.255613126*hauteur); // x

	(*capteurs).yZero[3]=(int)(0.797856049*largeur); // Nombre à droite
	(*capteurs).xZero[3]=(int)(0.255613126*hauteur); // x

	(*capteurs).yZero[4]=(int)(0.797856049*largeur); // l. p. m. à gauche
	(*capteurs).xZero[4]=(int)(0.45164076*hauteur); // x

	(*capteurs).yZero[5]=(int)(0.797856049*largeur); // l. p. m. à droite
	(*capteurs).xZero[5]=(int)(0.45164076*hauteur); // x

	(*capteurs).largeur=(int)(0.1849776*largeur); // longueur de l'axe x 164 165 165 / 892
	(*capteurs).hauteur=(int)(0.1393568*hauteur); // longueur de l'axe y 91 / 653

			//(*capteurs).capteur[j][i].x=(int);
/*	int i, j;
	for(i=0;i<CAPTEURS;i++)
		{
		for(j=0;j<DUREE_CAPTEURS;j++)
			{
			(*capteurs).capteur[j][i].x=(int);
			}
		}
*/
	return 0;
	}


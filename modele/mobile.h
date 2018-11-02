/*
Copyright novembre 2018, Stephan Runigo
runigo@free.fr
SiGP 2.2.2  simulateur de gaz parfait
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

#ifndef _MOBILE_
#define _MOBILE_

#include "vecteur.h"
#include "montage.h"

typedef struct MobileT mobileT;
	struct MobileT
		{
		vecteurT ancien;
		vecteurT actuel;
		vecteurT nouveau;

		float ec;
		float vitesse;
		float lpm;

		int nom;
		int dernier;
		int collision;
		int droite;

		

		int diametre;
		float diamCarre;
		};

void mobileInitialise(mobileT * mobile, montageT * montage, int nom, int diametre, float vitesse);
void mobileIncremente(mobileT * mobile);
int mobileIncrementeLibreParcoursMoyen(mobileT * mobile);

float mobileLibreParcoursMoyen(mobileT * mobile);

float mobileEnergieCinetique(mobileT * mobile);
float mobileModuleVitesse(mobileT * mobile);

void mobileInertie(mobileT * mobile);

void mobileParoi(mobileT * mobile, montageT * montage);
void mobileCollision(mobileT * m1, mobileT * m2);
void mobileTransparent(mobileT * m1, mobileT * m2);
void mobileOpaque(mobileT * mobile);

void mobileAffiche(mobileT * mobile);

#endif

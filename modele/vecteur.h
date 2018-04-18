
/*
Copyright septembre 2017, Stephan Runigo
runigo@free.fr
SiGP 1.3.3  simulateur de gaz parfait
Ce logiciel est un programme informatique servant à simuler un gaz parfait
et à en donner une représentation graphique. Il permet d'observer une détente
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

#ifndef _VECTEUR_
#define _VECTEUR_

#include "aleatoire.h"

typedef struct VecteurT vecteurT;
	struct VecteurT
		{
		double x;
		double y;
		};

void vecteurDifference(vecteurT * v1, vecteurT * v2, vecteurT * v); // v = v1 - v2
void vecteurSomme(vecteurT * v1, vecteurT * v2, vecteurT * v); // v = v1 + v2
void vecteurMultiplie(vecteurT * v, float lambda); // v = lambda * v

double vecteurScalaire(vecteurT * v1, vecteurT * v2);

double vecteurVectoriel(vecteurT * v1, vecteurT * v2);

void vecteurRotation(vecteurT * initial, vecteurT * tourner, double angle);
void vecteurRotationAleatoire(vecteurT * initial, vecteurT * tourner);
void vecteurUnitaireAleatoire(vecteurT * vect);

#endif

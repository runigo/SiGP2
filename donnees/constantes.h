
/*
Copyright mai 2018, Stephan Runigo
runigo@free.fr
SiGP 2.1  simulateur de gaz parfait
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

#ifndef _CONSTANTES_
#define _CONSTANTES_

//#include "unistd.h"

#include <assert.h>

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


#define PI 3.14159265359
#define DEUXPI 6.28318530718

	//	PARAMÈTRES GRAPHIQUES


#define TEMPS_AFFICHAGE 70 // Durée entre les affichages en ms

//#define FENETRE_X 1158 // Largeur de la fenêtre
//#define FENETRE_Y 714 // Hauteur de la fenêtre
#define FENETRE_X 892 // Largeur de la fenêtre
#define FENETRE_Y 550 // Hauteur de la fenêtre

#define BOUTON_COMMANDES 17 // Nombres de petits boutons
#define ROTATIF_COMMANDES 5 // Nombre de boutons rotatifs

#define LINEAIRE_COMMANDES 3 // Nombres de commandes linéaires
#define TRIANGLE_COMMANDES 21 // Nombres de commandes triangulaires

#define ROTATION_PSI 0.00733 // Vitesse de la rotation du graphisme

#define RATIO_H_L 0.436 // Ratio Hauteur sur Largeur de la chaîne
//#define RATIO_C_X 0.491 // Ratio Centrage X Sans Menu
//#define RATIO_C_Y 0.751 // Ratio Centrage Y Sans Menu
#define RATIO_C_X 0.399 // Ratio Centrage X Avec Menu
#define RATIO_C_Y 0.851 // Ratio Centrage Y Avec Menu
#define RATIO_R_MIN 0.21 // Ratio Distance minimal
#define RATIO_R_MAX 0.99 // Ratio Distance maximal

#define MARGE 49 // Marge fenêtre-montage

#define TAILLE_MASSE 8 // Diamètre des masses


	//	PARAMÈTRES DU SYSTÈME

#define ALEA 77 // Taille du tableau de nombre aléatoire

#define LARGEUR 700 // Largeur du système
#define HAUTEUR 350 // Hauteur du système

#define NOMBRE 149 // Nombre de particules
#define TAILLE 5 // Taille implicite des particules
#define TAILLE_MAX 19 // Taille maximale des particules

#define RAYON_TROU 7 // Rayon implicite du trou dans la cloison

#define DUREE_MAX 99 // Nombre d'itération du système par affichage
#define DUREE 1 // Nombre d'itération initial

#define TEMPERATURE_MAX 19666.1 // Température maximale
#define TEMPERATURE_MIN 0.000003 // Température minimale

#define TEMPERATURE 7.7;	// Température initiale
#define TEMPERATURE_GAUCHE 0.03;	// Température thermostat gauche
#define TEMPERATURE_DROIT 77;	// Température thermostat droit

#endif
/////////////////////////////////////////////////////////////

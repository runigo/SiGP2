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

#include "projection.h"

int projectionInitialise(projectionT * projection)
	{
	(*projection).logTrou = 1.0 / log( (HAUTEUR/2) );
	(*projection).logParticule = 1.0 / log( TAILLE_MAX/TAILLE_MIN );
	(*projection).logTemperature = 1.0 / log( TEMPERATURE_MAX/TEMPERATURE_MIN );
	(*projection).logGauche = 1.0 / log( TEMPERATURE_MAX/TEMPERATURE_MIN );
	(*projection).logDroite = 1.0 / log( TEMPERATURE_MAX/TEMPERATURE_MIN );
	return 0;
	}

int projectionAffiche(projectionT * projection)
	{
	fprintf(stderr, "  (*projection).logTrou   = %f\n",(*projection).logTrou);
	fprintf(stderr, "   (*projection).logParticule  = %f\n",(*projection).logParticule);
	fprintf(stderr, "  (*projection).logTemperature   = %f\n",(*projection).logTemperature);
	fprintf(stderr, "  (*projection).logGauche   = %f\n",(*projection).logGauche);
	fprintf(stderr, "  (*projection).logDroite   = %f\n",(*projection).logDroite);
	return 0;
	}

float projectionAbsolue(float valeur)
	{
	if(valeur<0) return -valeur;
	return valeur;
	}

int projectionSystemeCommandes(systemeT * systeme, projectionT * projection, commandesT * commandes, int duree, int mode)
	{
		// Projette le système sur les commandes

	float theta;
	float ratioRotatif = 0.9;

				//	Projection sur les boutons rotatifs
	 //	Rayon du trou
	theta = DEUXPI * (*projection).logTrou * log( (*systeme).montage.trou +1);
	(*commandes).rotatifPositionX[0]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[0]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	 //	Taille des particules
	theta = DEUXPI * (*projection).logParticule * log( (*systeme).diametre / TAILLE_MIN );
	(*commandes).rotatifPositionX[1]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[1]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Température
	theta = DEUXPI * (*projection).logTemperature * log( (*systeme).montage.thermostat.temperature / TEMPERATURE_MIN );
	(*commandes).rotatifPositionX[2]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[2]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Température gauche
	theta = DEUXPI * (*projection).logTemperature * log( (*systeme).montage.thermostat.gauche / TEMPERATURE_MIN );
	(*commandes).rotatifPositionX[3]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[3]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Température droite
	theta = DEUXPI * (*projection).logTemperature * log( (*systeme).montage.thermostat.droite / TEMPERATURE_MIN );
	(*commandes).rotatifPositionX[4]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[4]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Nombre
	theta = PI;
	//(*commandes).rotatifPositionX[5]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	//(*commandes).rotatifPositionY[5]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));
	(*commandes).rotatifPositionX[5]=0;
	(*commandes).rotatifPositionY[5]=0;


	int i;

		// Remise à zéro des boutons
	for(i=0;i<BOUTON_COMMANDES;i++) (*commandes).boutonEtat[i]=0;

		// Sélection des boutons activés
	switch((*systeme).montage.paroiCentrale)	//	Cloison centrale
		{
		case 1:
			(*commandes).boutonEtat[0]=1;break; // 32	Cloison
		case 2:
			(*commandes).boutonEtat[1]=1;break; // 62	Trou
		case 0:
			(*commandes).boutonEtat[3]=1;break; // 88 	Supprim.
		default:
			;
		}

	if((*systeme).montage.demonMaxwell==1)
			(*commandes).boutonEtat[2]=1; // 	Démon

	switch((*systeme).montage.thermostat.actif)	//	0:système isolé, 1:température uniforme, 2:températures gauche-droite
		{
		case 0:
			(*commandes).boutonEtat[4]=1;break; // système isolé
		case 1:
			(*commandes).boutonEtat[5]=1;break; // température uniforme
		case 2:
			(*commandes).boutonEtat[6]=1;break; // températures gauche-droite
		default:
			;
		}

	switch((*systeme).montage.thermostat.etatGauche)	//	Température gauche
		{
		case 1:
			(*commandes).boutonEtat[7]=1;break; //	Marche
		case 0:
			(*commandes).boutonEtat[8]=1;break; //	Arrêt
		default:
			;
		}

	switch((*systeme).montage.thermostat.etatDroite)	//	Température droite
		{
		case 1:
			(*commandes).boutonEtat[9]=1;break; //	Marche
		case 0:
			(*commandes).boutonEtat[10]=1;break; //	Arrêt
		default:
			;
		}

		// Remise à zéro des boutons triangulaire
	for(i=0;i<TRIANGLE_COMMANDES;i++) (*commandes).triangleEtat[i]=0;

	if(mode>0)
		{
		(*commandes).triangleEtat[7]=2;
		}

	if(duree==1)
		{
		(*commandes).triangleEtat[8]=1;
		}
	else
		{
		if(duree==DUREE_MAX)
			{
			(*commandes).triangleEtat[11]=2;
			}
		else
			{
			(*commandes).triangleEtat[9]=-1;
			(*commandes).lineairePositionX=(int)((*commandes).a * duree + (*commandes).b);
			}
		}

	return 0;
	}

int projectionSystemeCapteurs(systemeT * systeme, projectionT * projection, capteursT * capteurs)
	{
	(void)projection;
	(void)systeme;
	(void)capteurs;
		//	Projection du système sur le graphe
/*
	(*graphe).cloison = (*systeme).montage.paroiCentrale;
	(*graphe).trou = (*graphe).facteur*(*systeme).montage.trou;
	(*graphe).demon = (*systeme).montage.demonMaxwell;	// O ou 1
	(*graphe).thermostat = (*systeme).montage.thermostat.actif;	// O, 1 ou 2.
*/
	int i, j;
	for(i=0;i<CAPTEURS;i++)
		{
		(*capteurs).yZero[i]=0; // Positon de l'origine
		(*capteurs).xZero[i]=0; // Positon de l'origine
		for(j=0;j<DUREE_CAPTEURS;j++)
			{
			(*capteurs).capteur[j][i].x=600+35*i+5*j;
			(*capteurs).capteur[j][i].y=200+33*i+3*j;
			}
		}
/*
	graphiqueChangeCouleur(graphique, (*graphique).orange);
	SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[0], DUREE_CAPTEURS);

	graphiqueChangeCouleur(graphique, (*graphique).gris);
	SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[1], DUREE_CAPTEURS);

	graphiqueChangeCouleur(graphique, (*graphique).cyan);
	SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[2], DUREE_CAPTEURS);

	graphiqueChangeCouleur(graphique, (*graphique).contraste);
	SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[3], DUREE_CAPTEURS);

	graphiqueChangeCouleur(graphique, (*graphique).vert);
	SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[4], DUREE_CAPTEURS);

	graphiqueChangeCouleur(graphique, (*graphique).contraste);
	SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[5], DUREE_CAPTEURS);
*/
	return 0;
	}

void projectionSystemeGraphe(systemeT * systeme, projectionT * projection, grapheT * graphe)
	{
	(void)projection;
		//	Projection du système sur le graphe
	(*graphe).cloison = (*systeme).montage.paroiCentrale;
	(*graphe).trou = (*graphe).facteur*(*systeme).montage.trou;
	(*graphe).demon = (*systeme).montage.demonMaxwell;	// O ou 1
	(*graphe).thermostat = (*systeme).montage.thermostat.actif;	// O, 1 ou 2.

	(*graphe).taille = 1.9*((*systeme).diametre+1); // Diametre des particules
	if((*graphe).taille < 1)
		{(*graphe).taille = 1;}

				// Projection des particules
	int i;
	for(i=0;i<(NOMBRE);i++)
		{

		(*graphe).abscisse[i] = (*graphe).bx + (0.5*(*systeme).mobile[i].droite-0.25) * (TRAIT_CLOISON + (*graphe).taille) + (*graphe).facteur*(*systeme).mobile[i].nouveau.x;
		//(*graphe).abscisse[i] = (*graphe).bx + (0.5*(*systeme).mobile[i].droite-0.25) * (*graphe).taille + (*graphe).facteur*(*systeme).mobile[i].nouveau.x;

		if((*graphe).abscisse[i]>(*graphe).zoneX || (*graphe).abscisse[i]<0)
			{
			(*graphe).abscisse[i] = (*graphe).zoneX/2;
			}

		(*graphe).ordonnee[i] = 0.5*((*graphe).dy+(*graphe).gy) + (*graphe).facteur*(*systeme).mobile[i].nouveau.y;

		if((*graphe).ordonnee[i]>(*graphe).zoneY || (*graphe).ordonnee[i]<0)
			{
			(*graphe).ordonnee[i] = (*graphe).zoneY/2;
			}
		}
	return;
	}

//////////////////////////////////////////////////////////////////////////////

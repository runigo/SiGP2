/*
Copyright octobre 2018, Stephan Runigo
runigo@free.fr
SiGP 2.1.3  simulateur de gaz parfait
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
	(*commandes).rotatifPositionX[5]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[5]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));
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
			(*commandes).boutonEtat[2]=1;break; // 88 	Max
		default:
			;
		}

	if((*systeme).montage.demonMaxwell==1)
			(*commandes).boutonEtat[3]=1; // 	Démon

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

		// Sélection des boutons activés
	/*switch((*projection).initialisation)	//	
		{
		case 3:
			(*commandes).triangleEtat[0]=1;break; // 1
		case 1:
			(*commandes).triangleEtat[1]=1;break; // 2
		case 0:
			(*commandes).triangleEtat[2]=1;break; // 3
		case -1:
			(*commandes).triangleEtat[3]=1;break; // 1
		case -3:
			(*commandes).triangleEtat[4]=1;break; // 2
		case 0:
			(*commandes).triangleEtat[5]=1;break; // 3
		case -1:
			(*commandes).triangleEtat[6]=1;break; // 4
		default:
			;
		}*/

			(*commandes).triangleEtat[0]=0; // 1
			(*commandes).triangleEtat[1]=1; // 2
			(*commandes).triangleEtat[2]=2; // 3

			(*commandes).triangleEtat[3]=3; // 1
			(*commandes).triangleEtat[4]=-1; // 2
			(*commandes).triangleEtat[5]=-2; // 3
			(*commandes).triangleEtat[6]=-3; // 4
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

void projectionSystemeGraphe(systemeT * systeme, projectionT * projection, grapheT * graphe)
	{
	(void)projection;
		//	Projection du système sur le graphe
	int i;
	int demiLargeur = LARGEUR/2;
	int demiHauteur = HAUTEUR/2;

	(*graphe).cloison = (*systeme).montage.paroiCentrale;

	(*graphe).trou = (*systeme).montage.trou;

	(*graphe).taille = (*systeme).diametre;
	if((*graphe).taille < 1)
		{(*graphe).taille = 1;}

	for(i=0;i<(NOMBRE);i++)
		{

				// Projection du système
		(*graphe).abscisse[i] = demiLargeur + (*systeme).mobile[i].nouveau.x;

		if((*graphe).abscisse[i]>LARGEUR || (*graphe).abscisse[i]<0)
			{
			(*graphe).abscisse[i] = LARGEUR/2;
			}

		(*graphe).ordonnee[i] = demiHauteur + (*systeme).mobile[i].nouveau.y;

		if((*graphe).ordonnee[i]>HAUTEUR || (*graphe).ordonnee[i]<0)
			{
			(*graphe).ordonnee[i] = HAUTEUR/2;
			}
		}
	return;
	}

int projectionInitialiseLongueurs(projectionT * projection, int hauteur, int largeur)
	{		// Initialise les longueur de la projection
	(*projection).hauteur = hauteur;
	(*projection).largeur = largeur;
	return 0;
	}

//////////////////////////////////////////////////////////////////////////////

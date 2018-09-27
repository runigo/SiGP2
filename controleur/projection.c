
/*
Copyright septembre 2018, Stephan Runigo
runigo@free.fr
SiGP 2.1.2  simulateur de gaz parfait
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

int projectionSystemeCommandes(systemeT * systeme, projectionT * projection, commandesT * commandes, int duree, int mode)
	{
		// Projette le système sur les commandes

	(void)systeme;
	(void)projection;
	(void)commandes;
	(void)duree;
	(void)mode;

/*
		MODELE SiCP
	float theta;
	float ratioRotatif = 0.9;

				//	Projection sur les boutons rotatifs
	 //	Couplage
	theta = DEUXPI * (*projection).logCouplage * log( (*systeme).couplage / (COUPLAGE_MIN * (*systeme).nombre) );
	(*commandes).rotatifPositionX[0]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[0]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	theta = DEUXPI * (*projection).logDissipation * log( (*systeme).dissipation/DISSIPATION_MIN );
	(*commandes).rotatifPositionX[1]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[1]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Amplitude du moteur josephson
	theta = DEUXPI * (*projection).logJosephson * log( projectionAbsolue((*systeme).moteurs.courant/JOSEPHSON_MIN) );
	(*commandes).rotatifPositionX[2]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[2]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Amplitude du moteur périodique
	theta = DEUXPI * (*projection).logAmplitude * log( (*systeme).moteurs.amplitude/AMPLITUDE_MIN );
	(*commandes).rotatifPositionX[3]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[3]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Fréquence du moteurs
	theta = DEUXPI * (*projection).logFrequence * log( (*systeme).moteurs.frequence/FREQUENCE_MIN );
	(*commandes).rotatifPositionX[4]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[4]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

		//int rotatifPositionX[ROTATIF_COMMANDES]; // Position du bouton rotatif
		//int rotatifPositionY[ROTATIF_COMMANDES];


	int i;
	for(i=0;i<BOUTON_COMMANDES;i++) (*commandes).boutonEtat[i]=0;

		//int libreFixe;		//	0 : périodiques 1 : libres, 2 : fixes, 
							//		3 libre-fixe, 4 fixe-libre
	switch((*systeme).libreFixe)	//	
		{
		case 0:
			(*commandes).boutonEtat[0]=1;break; // 32	Périodique
		case 1:
			(*commandes).boutonEtat[1]=1;break; // 62	Libre
		case 2:
			(*commandes).boutonEtat[2]=1;break; // 88 	Fixe
		case 3:
			(*commandes).boutonEtat[3]=1;break; // 115	Mixte
		case 4:
			(*commandes).boutonEtat[3]=1;break; // 115	Mixte
		default:
			;
		}

	//	int modeDissipation;	//	0 : nulle 1 : uniforme, 2 : extrémité absorbante.
	switch((*systeme).modeDissipation)	//	
		{
		case 0:
			(*commandes).boutonEtat[5]=1;break; // 198	Nulle
		case 1:
			(*commandes).boutonEtat[4]=1;break; // 167	Uniforme
		case 2:
			(*commandes).boutonEtat[6]=1;break; // 230	Extrémité
		default:
			;
		}

	//(*commandes).boutonEtat[4]=1;
	//(*commandes).boutonEtat[5]=1;
	//(*commandes).boutonEtat[6]=1;

	if((*systeme).moteurs.josephson > 0.0)
		{
		(*commandes).boutonEtat[7]=1; // 284	Marche
		(*commandes).boutonEtat[9]=1; // 339	Droite
		}
	else
		{
		if((*systeme).moteurs.josephson < 0.0)
			{
			(*commandes).boutonEtat[7]=1; // 284	Marche
			(*commandes).boutonEtat[10]=1; // 367	Gauche
			}
		else
			{
			(*commandes).boutonEtat[8]=1; // 311	Arrêt
			}
		}

	switch((*systeme).moteurs.generateur)	//	0:eteint, 1:sinus, 2:carre, 3:impulsion
		{
		case 0:
			(*commandes).boutonEtat[11]=1;break; // 421	Arrêt
		case 1:
			(*commandes).boutonEtat[12]=1;break; // 449	Sinus
		case 2:
			(*commandes).boutonEtat[13]=1;break; // 481	Carré
		case 3:
			(*commandes).boutonEtat[14]=1;break; // 509	Impulsion
		default:
			;
		}
	//(*commandes).boutonEtat[15]=0; // 536	Fluxon
	//(*commandes).boutonEtat[16]=0; // 563	Anti F.

	for(i=0;i<TRIANGLE_COMMANDES;i++) (*commandes).triangleEtat[i]=0;

	switch((*projection).rotation)	//	
		{
		case 3:
			(*commandes).triangleEtat[0]=1;break; // 
		case 1:
			(*commandes).triangleEtat[1]=1;break; // 
		case 0:
			(*commandes).triangleEtat[2]=0;break; // 
		case -1:
			(*commandes).triangleEtat[3]=1;break; // 
		case -3:
			(*commandes).triangleEtat[4]=1;break; // 
		default:
			;
		}
	if(duree<100)
		{
			(*commandes).triangleEtat[5]=1;
			(*commandes).triangleEtat[6]=1;
		}
	else
		{
		if(duree>100)
			{
			(*commandes).triangleEtat[9]=1;
			(*commandes).triangleEtat[10]=1;
			}
		else
			{
			(*commandes).triangleEtat[8]=1;
			}
		}
	if(mode<0)
		{
		(*commandes).triangleEtat[7]=2;
		}
*/
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

	(*graphe).rayon = (*systeme).diametre/2;
	if((*graphe).rayon < 1)
		{(*graphe).rayon = 1;}

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

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

#include "commandes.h"

int commandesInitialiseBoutons(commandesT * commandes, int largeur, int hauteur)
	{

	//	PANNEAU DROIT

		 // Zone des boutons rotatifs
	(*commandes).rotatifs=(int)(0.833333333333*largeur); // 965 / 1158
		// BOUTONS ROTATIFS SUIVANT X
	(*commandes).rotatifX=(int)(0.020725388601*largeur); // 823       D-G = 24 / 1158 // Rayon suivant X
	(*commandes).rotatifsCentre=(int)(0.892918825561*largeur); // 1034 // Positon X des boutons rotatifs
		// BOUTONS ROTATIFS SUIVANT Y
	(*commandes).rotatifY=(int)(0.0322128851541*hauteur); // 23 / 714	Rayon suivant Y
	(*commandes).rotatifCentre[0]=(int)(0.145427286357*hauteur); //	Trou
	(*commandes).rotatifCentre[1]=(int)(0.389805097451*hauteur); // Température
	(*commandes).rotatifCentre[2]=(int)(0.5712143928*hauteur); // Gauche
	(*commandes).rotatifCentre[3]=(int)(0.751124437781*hauteur); // Droite
	(*commandes).rotatifCentre[4]=(int)(0.917541229385*hauteur); // Nombre

		 // Zone des petits boutons
	(*commandes).boutons=(int)(0.946459412781*largeur); // 1096 / 1158
		// PETITS BOUTONS SUIVANT X
	(*commandes).boutonX=(int)(0.0120898100173*largeur); // Rayon suivant X // 14 / 1158
	(*commandes).boutonsCentre=(int)(0.964594127807*largeur); // 1117 // Positon X des petits boutons
		// PETITS BOUTONS SUIVANT Y
	(*commandes).boutonY=(int)(0.0168067226891*largeur); // Rayon suivant Y // 12 / 667
	(*commandes).boutonCentre[0]=(int)(0.0584707646177*hauteur); // CLoison
	(*commandes).boutonCentre[1]=(int)(0.110944527736*hauteur); // 74 Trou
	(*commandes).boutonCentre[2]=(int)(0.16191904048*hauteur); // 108 Max
	(*commandes).boutonCentre[3]=(int)(0.212893553223*hauteur); // 142 Démon
	(*commandes).boutonCentre[4]=(int)(0.335832083958*hauteur); // 224 Arrêt
	(*commandes).boutonCentre[5]=(int)(0.388305847076*hauteur); // 259 1 T.
	(*commandes).boutonCentre[6]=(int)(0.440779610195*hauteur); // 294 2 T.

	(*commandes).boutonCentre[7]=(int)(0.538230884558*hauteur); // 359	Marche
	(*commandes).boutonCentre[8]=(int)(0.592203898051*hauteur); // 395	Arrêt

	(*commandes).boutonCentre[9]=(int)(0.721139430285*hauteur); // 481	Marche
	(*commandes).boutonCentre[10]=(int)(0.7736131934*hauteur); // 516	Arrêt



	//	PANNEAU BAS

		 // Zone du panneau
	(*commandes).bas=(int)(0.855742296919*hauteur); // 611 / 714

		// BOUTONS LINEAIRES SUIVANT Y
	(*commandes).lineaireY=(int)(0.0392156862745*hauteur); // 693-636/2 =  / 714 // Rayon suivant Y
	(*commandes).lineairesCentre=(int)(0.958181818182*hauteur); // 693+636/2 =  / 714 // Position Y des boutons linéaires
		// BOUTONS LINEAIRES SUIVANT X
	(*commandes).lineaireX=(int)(0.0306563039724*largeur); // 332-261/2 / 1158	Rayon suivant X
	(*commandes).lineaireCentre[0]=(int)(0.20067264574*largeur); // 261	Hauteur
	(*commandes).lineaireCentre[1]=(int)(0.20067264574*largeur); // 332	Distance
	(*commandes).lineaireCentre[2]=(int)(0.257847533632*largeur); // 414+596/2	Simulation < temps réèl
	(*commandes).lineaireCentre[3]=(int)(0.406950672646*largeur); // 414+596/2	Simulation > temps réèl	

		// BOUTONS TRIANGULAIRES SUIVANT Y
	(*commandes).triangleY=(int)(0.0168067226891*hauteur); // Rayon suivant Y // 12 / 714
	(*commandes).trianglesCentre=(int)(0.920168067227*hauteur); // 657 // Position Y des petits triangles
	(*commandes).trianglesLumiere=(int)(0.960784313725*hauteur); // 685 // Position Y des lumière
		// BOUTONS TRIANGULAIRES SUIVANT X
	(*commandes).triangleX=(int)(0.0120898100173*largeur); // Rayon suivant X // 14 / 1159
	(*commandes).triangleCentre[0]=(int)(0.0379637618637*largeur); // 44	1
	(*commandes).triangleCentre[1]=(int)(0.0672993960311*largeur); // 78	2
	(*commandes).triangleCentre[2]=(int)(0.0949094046592*largeur); // 110 	3

	(*commandes).triangleCentre[3]=(int)(0.150129421915*largeur); // 174	1
	(*commandes).triangleCentre[4]=(int)(0.178602243313*largeur); // 207	2
	(*commandes).triangleCentre[5]=(int)(0.207075064711*largeur); // 240	3
	(*commandes).triangleCentre[6]=(int)(0.236410698878*largeur); // 274	4

	(*commandes).triangleCentre[7]=(int)(0.314063848145*largeur); // 364	pause
	(*commandes).triangleCentre[8]=(int)(0.355478861087*largeur); // 412	Min
	(*commandes).triangleCentre[9]=(int)(0.388265746333*largeur); // 450	Moins
	(*commandes).triangleCentre[10]=(int)(0.416738567731*largeur); // 483	Plus
	(*commandes).triangleCentre[11]=(int)(0.451251078516*largeur); // 	Max


		//	Vitesse de la simulation

	(*commandes).a=(0.277*largeur-0.23*largeur)/(DUREE-2);
	//(*commandes).a=(((*commandes).triangleCentre[6]-(*commandes).triangleCentre[5])/(DUREE-2)));
	(*commandes).b=0.23*largeur-(*commandes).a;	//	Droite duree < DUREE
	//(*commandes).b=((*commandes).triangleCentre[5]-(*commandes).a);	//	Droite duree < DUREE
	(*commandes).A=(0.42*largeur-0.38*largeur)/(DUREE_MAX-DUREE-1);
	//(*commandes).A=(((*commandes).triangleCentre[10]-(*commandes).triangleCentre[9])/(DUREE_MAX-DUREE-1));
	(*commandes).B=0.38*largeur-(*commandes).A*(DUREE+1);	//	Droite duree > DUREE
	//(*commandes).B=((*commandes).triangleCentre[9]-(*commandes).A*(DUREE+1));	//	Droite duree > DUREE

	return 0;
	}

int commandesInitialiseSouris(commandesT * commandes, int sourisX, int sourisY)
	{
		// POSITION DE LA SOURIS
	(*commandes).sourisX = sourisX; // position X de la souris
	(*commandes).sourisY = sourisY; // position Y de la souris
		 // Rayon des petits boutons
	int rayonX=(*commandes).boutonX;
	int rayonY=(*commandes).boutonY;

		 
	if(sourisX>(*commandes).rotatifs)
		{
		if(sourisX<(*commandes).boutons)// Zone des boutons rotatifs
			{
			rayonX=(*commandes).rotatifX;
			rayonY=(*commandes).rotatifY;
			}
		}
	else 
		{
		if(sourisY>(*commandes).bas) // Zone du bas
			{
			rayonX=(*commandes).triangleX;
			rayonY=(*commandes).triangleY;
			}
		}
		//fprintf(stderr, "%d %d\n", sourisX, sourisY);

	(*commandes).sourisGauche = sourisX-rayonX; // position X de la souris - RayonBoutonX
	(*commandes).sourisDroite = sourisX+rayonX; // position X de la souris + RayonBoutonX
	(*commandes).sourisHaut = sourisY-rayonY; // position Y de la souris - RayonBoutonY
	(*commandes).sourisBas = sourisY+rayonY; // position Y de la souris + RayonBoutonY

		//fprintf(stderr, "Commandes : %d %d\n", (*commandes).sourisX, (*commandes).sourisY);
		//fprintf(stderr, "Commandes : %d %d\n", sourisX, sourisY);
	return 0;
	}

int commandeBoutons(commandesT * commandes)
	{
	int i;
	if((*commandes).boutonsCentre>(*commandes).sourisGauche && (*commandes).boutonsCentre<(*commandes).sourisDroite)
		{
		for(i=0;i<BOUTON_COMMANDES;i++)
			{
			if((*commandes).boutonCentre[i]>(*commandes).sourisHaut && (*commandes).boutonCentre[i]<(*commandes).sourisBas)
				return i;
			}
		}
	return -1;
	}

int commandeRotatifs(commandesT * commandes)
	{
	int i;
	if((*commandes).rotatifsCentre>(*commandes).sourisGauche && (*commandes).rotatifsCentre<(*commandes).sourisDroite)
		{
		for(i=0;i<ROTATIF_COMMANDES;i++)
			{
			if((*commandes).rotatifCentre[i]>(*commandes).sourisHaut && (*commandes).rotatifCentre[i]<(*commandes).sourisBas)
				return i;
			}
		}
	return -1;
	}

int commandeTriangles(commandesT * commandes)
	{
	int i;
	if((*commandes).trianglesCentre>(*commandes).sourisHaut && (*commandes).trianglesCentre<(*commandes).sourisBas)
		{
		for(i=0;i<TRIANGLE_COMMANDES;i++)
			{
			if((*commandes).triangleCentre[i]>(*commandes).sourisGauche && (*commandes).triangleCentre[i]<(*commandes).sourisDroite)
				return i;
			}
		}
	return -1;
	}

int commandeLineaires(commandesT * commandes)
	{
	int i;
	if((*commandes).lineairesCentre>(*commandes).sourisHaut && (*commandes).lineairesCentre<(*commandes).sourisBas)
		{
		for(i=0;i<LINEAIRE_COMMANDES;i++)
			{
			if((*commandes).lineaireCentre[i]>(*commandes).sourisGauche && (*commandes).lineaireCentre[i]<(*commandes).sourisDroite)
				return i;
			}
		}
	return -1;
	}

//////////////////////////////////////////////////////////////////

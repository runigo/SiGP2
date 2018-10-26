/*
Copyright octobre 2018, Stephan Runigo
runigo@free.fr
SiGP 2.2  simulateur de gaz parfait
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

#include "observables.h"

int observablesMiseAJourAmplitude(observablesT * observables);

int observablesMiseAJourNombre(observablesT * observables, systemeT * systeme);
int observablesMiseAJourLibreParcoursMoyen(observablesT * observables, systemeT * systeme);
int observablesMiseAJourTemperature(observablesT * observables, systemeT * systeme);

int observablesInitialise(observablesT * observables)
	{
	//(void) largeur;, int largeur, int hauteur
	//(void) hauteur;
	int i, j;
	for(i=0;i<CAPTEURS;i++)
		{
		for(j=0;j<DUREE_CAPTEURS;j++)
			{
			(*observables).observable[j][i]=0;
			}
		}

	(*observables).index=0;

	return 0;
	}

int observablesMiseAJourAmplitude(observablesT * observables)
	{
	int i, j;
	float max = 0.0;

	for(j=0;j<CAPTEURS;j++)
		{
		for(i=0;i<DUREE_CAPTEURS;i++)
			{
			if((*observables).observable[i][j] > max)
				{
				max = (*observables).observable[i][j];
				}
			}
		(*observables).maximum[j] = max;
		}

	return 0;
	}


int observablesMiseAJour(observablesT * observables, systemeT * systeme)
	{		// Mise à jour des observables

		// Évolution de l'index
	(*observables).index ++;
	//fprintf(stderr, "(*observables).index = %d\n", (*observables).index);

	if((*observables).index==DUREE_CAPTEURS)
		{
		(*observables).index=0;
		}

	observablesMiseAJourNombre(observables,systeme);

	observablesMiseAJourLibreParcoursMoyen(observables, systeme);

	observablesMiseAJourTemperature(observables, systeme);

	observablesMiseAJourAmplitude(observables);

	return 0;
	}

int observablesAffiche(observablesT * observables)
	{
	printf("\nSTATISTIQUES\n");

	printf("	temperature à gauche %f \n", (*observables).observable[(*observables).index][0]);
	printf("	temperature à droite %f \n\n", (*observables).observable[(*observables).index][1]);
	printf("	nombre à gauche %f \n", (*observables).observable[(*observables).index][2]);
	printf("	nombre à droite %f \n\n", (*observables).observable[(*observables).index][3]);
	printf("	libre parcours moyen à gauche %f \n", (*observables).observable[(*observables).index][4]);
	printf("	libre parcours moyen à droite %f \n\n", (*observables).observable[(*observables).index][5]);
	return 0;
	}

int observablesMiseAJourNombre(observablesT * observables, systemeT * systeme)
	{
	int i;
	int nbGauche=0;
	int nbDroite=0;

	for(i=0;i<NOMBRE;i++)
		{
		if((*systeme).mobile[i].droite==0)
			{
			nbGauche ++;
			}
		else
			{
			nbDroite ++;
			}
		}

	(*observables).observable[(*observables).index][2]=nbGauche;
	(*observables).observable[(*observables).index][3]=nbDroite;

	return 0;
	}

int observablesMiseAJourTemperature(observablesT * observables, systemeT * systeme)
	{
	int i;
	double ecGauche=0.0;
	double ecDroite=0.0;

	for(i=0;i<NOMBRE;i++)
		{
		if((*systeme).mobile[i].droite==0)
			{
			ecGauche=ecGauche+mobileEnergieCinetique(&(*systeme).mobile[i]);
			}
		else
			{
			ecDroite=ecDroite+mobileEnergieCinetique(&(*systeme).mobile[i]);
			}
		}

	if((*observables).observable[(*observables).index][2]!=0.0)
		{
		(*observables).observable[(*observables).index][0]=ecGauche/(*observables).observable[(*observables).index][2];
		}
	else
		{
		(*observables).observable[(*observables).index][0]=ecGauche;
		}

	if((*observables).observable[(*observables).index][3]!=0.0)
		{
		(*observables).observable[(*observables).index][1]=ecDroite/(*observables).observable[(*observables).index][3];
		}
	else
		{
		(*observables).observable[(*observables).index][1]=ecDroite;
		}

	return 0;
	}

int observablesMiseAJourLibreParcoursMoyen(observablesT * observables, systemeT * systeme)
	{
	int i;
	double lpmGauche=0.0;
	double lpmDroite=0.0;

	for(i=0;i<NOMBRE;i++)
		{
		if((*systeme).mobile[i].droite==0)
			{
			lpmGauche = lpmGauche + (*systeme).mobile[i].lpm;
			}
		else
			{
			lpmDroite = lpmDroite + (*systeme).mobile[i].lpm;
			}
		}

	if((*observables).observable[(*observables).index][2]!=0.0)
		{
		(*observables).observable[(*observables).index][4]=lpmGauche/(*observables).observable[(*observables).index][2];
		}
	else
		{
		(*observables).observable[(*observables).index][0]=lpmGauche;
		}

	if((*observables).observable[(*observables).index][3]!=0.0)
		{
		(*observables).observable[(*observables).index][5]=lpmDroite/(*observables).observable[(*observables).index][3];
		}
	else
		{
		(*observables).observable[(*observables).index][5]=lpmDroite;
		}

	return 0;
	}
/*
double observableEcartCinetique(systemeT * systeme)
	{
	int i;
	double moyenne, ecp, ecart;
	ecart=0.0;
	moyenne=observablesEnergieCinetique(systeme)/NOMBRE;
	for(i=0;i<NOMBRE;i++)
		{
		ecp=((*systeme).mobile[i].ec)-moyenne;
		ecp=ecp*ecp;
		ecart=ecart+ecp;
		}
	ecart=sqrt(ecart);
	return ecart;
	}
*/

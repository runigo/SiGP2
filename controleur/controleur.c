
/*
Copyright avril 2018, Stephan Runigo
runigo@free.fr
SiGP 1.4  simulateur de gaz parfait
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

#include "controleur.h"

void controleurEvolution(controleurT * controleur);
int controleurProjection(controleurT * controleur);
int controleurEvolutionSysteme(controleurT * controleur);
int controleurConstructionGraphique(controleurT * controleur);
int controleurActionClavier(controleurT * controleur);

int controleurTraiteEvenement(controleurT * controleur);

int controleurClavier(controleurT * controleur);
int controleurClavierMaj(controleurT * controleur);
int controleurClavierCtrl(controleurT * controleur);
int controleurSouris(controleurT * controleur);
void controleurBoutonSouris(controleurT * controleur, int appui);

void controleurChangeMode(controleurT * controleur);
void controleurChangeVitesse(controleurT * controleur, float facteur);

int controleurDestruction(controleurT * control)
	{
	fprintf(stderr, "Suppression de l'horloge\n");
	horlogeSuppression(&(*control).horloge);

	fprintf(stderr, "Suppression du rendu\n");
	graphiqueDestruction(&(*control).graphique);

	fprintf(stderr, "Suppression de la fenêtre\n");
	interfaceDestruction(&(*control).interface);

	fprintf(stderr, "Sortie de la SDL\n");
	interfaceQuitteSDL();

	return 0;
	}


int controleurSimulationGraphique(controleurT * controleur)
	{
		//fprintf(stderr, "Entrée dans la boucle SDL\n");
	do	{
			//fprintf(stderr, "Prise en compte des actions clavier\n");
		controleurActionClavier(controleur);
		}
	while((*controleur).sortie == 0);

	return 0;
	}

int controleurActionClavier(controleurT * controleur)
	{
	int sortie = 0;
		//fprintf(stderr, "Traitement des évenements, mode %d\n", (*controleur).option.mode);
	if(SDL_WaitEvent(&(*controleur).interface.evenement))
		{
		sortie += controleurTraiteEvenement(controleur);
		}
	if(sortie != 0)
		{
		fprintf(stderr, "sortie <> 0\n");
		(*controleur).sortie = 1;
		}
	return sortie;
	}

void controleurEvolution(controleurT * controleur)
	{
	//printf("Entrée dans controleurEvolution, SDL_GetTicks() = %d\n",(int)(SDL_GetTicks()));

		//fprintf(stderr, "    Durée entre affichage = %d\n",horlogeChronoDuree(&(*controleur).horloge));
	horlogeChronoDepart(&(*controleur).horloge);

		//fprintf(stderr, "\nProjection du système sur la représentation graphique");
	controleurProjection(controleur);
		//fprintf(stderr, "    Durée = %d\n",horlogeChronoDuree(&(*controleur).horloge));

	if((*controleur).mode > 0)
		{
			horlogeChronoDepart(&(*controleur).horloge);
			//fprintf(stderr, "Evolution temporelle du systeme");
			controleurEvolutionSysteme(controleur);
			//fprintf(stderr, "    Durée = %d\n",horlogeChronoDuree(&(*controleur).horloge));
		}

	horlogeChronoDepart(&(*controleur).horloge);

		//fprintf(stderr, "Mise à jour de la fenêtre graphique");
	controleurConstructionGraphique(controleur);
		//fprintf(stderr, "    Durée = %d\n",horlogeChronoDuree(&(*controleur).horloge));

	//horlogeChronoDepart(&(*controleur).horloge);
	//fprintf(stderr, "    Durée des évolutions = %d\n",horlogeChronoDuree(&(*controleur).horloge));
	//printf("Sortie de controleurEvolution, SDL_GetTicks() = %d\n",(int)(SDL_GetTicks()));
		//fprintf(stderr, "    Durée entre affichage = %d\n",horlogeChronoDuree(&(*controleur).horloge));

	return;
	}

int controleurProjection(controleurT * controleur)
	{
		// Projection du système sur le graphique
	projectionSystemeGraphe(&(*controleur).systeme,&(*controleur).graphe);

	return (*controleur).sortie;
	}

int controleurEvolutionSysteme(controleurT * controleur)
	{
		// Évolution du système
	systemeEvolue(&(*controleur).systeme, (*controleur).duree);

	return 0;
	}

int controleurConstructionGraphique(controleurT * controleur)
	{

		//fprintf(stderr, "Nettoyage de l'affichage\n");
	graphiqueNettoyage(&(*controleur).graphique);

		//fprintf(stderr, "Dessin des graphes\n");
	graphiqueDessineGraphe(&(*controleur).graphique, &(*controleur).graphe);

		//fprintf(stderr, "Mise à jour de l'affichage\n");
	graphiqueMiseAJour(&(*controleur).graphique);

	return (*controleur).sortie;
	}

int controleurTraiteEvenement(controleurT * controleur)
	{
	int sortie = 0;
	switch((*controleur).interface.evenement.type)
		{
		case SDL_QUIT:
			sortie = 1;break;
		case SDL_MOUSEMOTION:
			sortie = controleurSouris(controleur);break;
		case SDL_MOUSEBUTTONDOWN:
			controleurBoutonSouris(controleur, 1);break;
		case SDL_MOUSEBUTTONUP:
			controleurBoutonSouris(controleur, 0);break;
		case SDL_USEREVENT:
			controleurEvolution(controleur);break;
		case SDL_KEYDOWN:
			{
			if ((((*controleur).interface.evenement.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT)
			|| (((*controleur).interface.evenement.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT))
				{
				sortie = controleurClavierMaj(controleur);break;
				}
			else
				{
				if ((((*controleur).interface.evenement.key.keysym.mod & KMOD_LSHIFT) == KMOD_LCTRL)
				|| (((*controleur).interface.evenement.key.keysym.mod & KMOD_RSHIFT) == KMOD_RCTRL))
					{
					sortie = controleurClavierCtrl(controleur);break;
					}
				else
					{
					sortie = controleurClavier(controleur);break;
					}
				}
			}
		default:
			;
		}

	if(sortie != 0)
		{
		fprintf(stderr, "sortie <> 0\n");
		(*controleur).sortie = 1;
		}
	return sortie;
	}

void controleurChangeMode(controleurT * controleur)
	{
	(*controleur).mode=-(*controleur).mode;

	return;
	}

void controleurChangeVitesse(controleurT * controleur, float facteur)
	{
	if(facteur > 0.0)
		{
		if( (*controleur).duree > DUREE_MAX && facteur > 1 )
			{
			printf("Duree maximale atteinte. ");
			}
		else
			{
			if( (*controleur).duree > 11 )
				{
				(*controleur).duree = (*controleur).duree * facteur;
				}
			else
				{
				if( facteur > 1)
					{
					(*controleur).duree ++;
					}
				else
					{
					if( (*controleur).duree > 1 )
						{
						(*controleur).duree --;
						}
					else
						{
						printf("Duree minimale atteinte. ");
						}
					}
				}
			}
		}
	else
		{
		if(facteur > -5.0)
			{
			(*controleur).duree=1;
			}
		else
			{
			(*controleur).duree=DUREE_MAX;
			}
		}
	printf("Duree = %d\n", (*controleur).duree);
	return;
	}

int controleurClavier(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{

	// Sortie

		case SDLK_ESCAPE:
			(*controleur).sortie = 1;break;

    // Mode : attente d'un evenement / pas d'attente

		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeMode(controleur);break;

	// Vitesse de la simulation
		case SDLK_KP_PLUS:
			controleurChangeVitesse(controleur, 1.1);break;
		case SDLK_KP_MINUS:
			controleurChangeVitesse(controleur, 0.91);break;
		case SDLK_F9:
			controleurChangeVitesse(controleur, -1.0);break;
			//(*controleur).duree=1;break;
		case SDLK_F10:
			controleurChangeVitesse(controleur, 0.91);break;
		case SDLK_F11:
			controleurChangeVitesse(controleur, 1.1);break;
		case SDLK_F12:
			controleurChangeVitesse(controleur, -10.0);break;
			//(*controleur).duree=DUREE_MAX;break;

	// Diametre des particules

		case SDLK_e:
			systemeChangeDiametre(&(*controleur).systeme, 1.1);break;
		case SDLK_d:
			systemeChangeDiametre(&(*controleur).systeme, 0.9);break;

	// Taille du trou

		case SDLK_a:
			montageChangeTrou(&(*controleur).systeme.montage, 1.1);break;
		case SDLK_q:
			montageChangeTrou(&(*controleur).systeme.montage, 0.9);break;
		case SDLK_z:
			montageChangeTrou(&(*controleur).systeme.montage, -2);break;
		case SDLK_s:
			montageChangeTrou(&(*controleur).systeme.montage, -1);break;

		case SDLK_w:	//	Pas de cloison central
			systemeChangeCloison(&(*controleur).systeme, 0);break;
		case SDLK_x:	//	Cloison fermée
			systemeChangeCloison(&(*controleur).systeme, 1);break;
		case SDLK_c:	//	Cloison percée
			systemeChangeCloison(&(*controleur).systeme, 2);break;
		case SDLK_v:	//	cloison percée et démon de Maxwell
			systemeChangeCloison(&(*controleur).systeme, -1);break;
		case SDLK_b:	//	Démon de Maxwell
			systemeChangeCloison(&(*controleur).systeme, -1);break;
		case SDLK_n:	//	Trou max et démon de Maxwell
			systemeChangeCloison(&(*controleur).systeme, -2);break;

	// Thermostat

		case SDLK_o:	//	Système isolé
			thermostatChangeEtat(&(*controleur).systeme.montage.thermostat, 0);break;
		case SDLK_i:	//	Système thermostaté symétrique
			thermostatChangeEtat(&(*controleur).systeme.montage.thermostat, 1);break;
		case SDLK_k:	//	Système  thermostaté gauche-droite
			thermostatChangeEtat(&(*controleur).systeme.montage.thermostat, 2);break;
		case SDLK_l:	//	Erreur
			thermostatChangeEtat(&(*controleur).systeme.montage.thermostat, 3);break;

		case SDLK_p:	//	Valeur de la température
			thermostatChangeTemperature(&(*controleur).systeme.montage.thermostat, 1.7);break;
		case SDLK_m:	//	
			thermostatChangeTemperature(&(*controleur).systeme.montage.thermostat, 0.6);break;

		case SDLK_u:	//	Température à droite
			thermostatChangeTemperatureDroite(&(*controleur).systeme.montage.thermostat,1.9);break;
		case SDLK_j:	//	Température à droite
			thermostatChangeTemperatureDroite(&(*controleur).systeme.montage.thermostat,0.51);break;
		case SDLK_y:	//	Température à gauche
			thermostatChangeTemperatureGauche(&(*controleur).systeme.montage.thermostat,1.9);break;
		case SDLK_h:	//	Température à gauche
			thermostatChangeTemperatureGauche(&(*controleur).systeme.montage.thermostat,0.51);break;


  // Initialiser le système

		case SDLK_F1:
			systemeInitialisePosition(&(*controleur).systeme);
			break;

  // Afficher les informations

		case SDLK_F5:	//	
			observablesAfficheEnergie(&(*controleur).systeme);
			break;
		case SDLK_F6:	//	
			thermostatAfficheThermostat(&(*controleur).systeme.montage.thermostat);
			break;

		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurClavierMaj(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{

	// Sortie

		case SDLK_ESCAPE:
			(*controleur).sortie = 1;break;

    // Mode : attente d'un evenement / pas d'attente

		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeMode(controleur);break;


	// Réinitialisation du système
		// Lecture des fichier
		case SDLK_a:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme);break;
	/*	case SDLK_z:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 1);break;
		case SDLK_e:
			fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 2);break;
			fichierFonction(&(*controleur).systeme, 2);break;//Triangle
		case SDLK_r:
			fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 3);break;
			fichierFonction(&(*controleur).systeme, 3);break;//Triangle
		case SDLK_t:
			fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 4);break;
			fichierFonction(&(*controleur).systeme, 4);break;//Triangle
		case SDLK_y:
			fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 5);break;
			fichierFonction(&(*controleur).systeme, 5);break;//Triangle
		case SDLK_u:
			fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 6);break;
			fichierFonction(&(*controleur).systeme, 6);break;//Triangle
		case SDLK_i:
			fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 7);break;
			fichierFonction(&(*controleur).systeme, 7);break;//Triangle


		case SDLK_q:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 10);break;
		case SDLK_s:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 11);break;
		case SDLK_d:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 12);break;
		case SDLK_f:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 13);break;
		case SDLK_g:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 14);break;
		case SDLK_h:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 15);break;
		case SDLK_j:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 16);break;
		case SDLK_k:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierLecture(&(*controleur).systeme, 17);break;

		case SDLK_o:
			//fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 8);break;
		case SDLK_p:
			//fprintf(stderr, "Réinitialisation du système\n");
			controleurChangeSensibilite(&(*controleur), 1.1);break;
			//fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 9);break;
		case SDLK_l:
			//fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 18);break;
		case SDLK_m:
			controleurChangeSensibilite(&(*controleur), 0.91);break;
			//fprintf(stderr, "Réinitialisation du système\n");
			//fichierLecture(&(*controleur).systeme, 19);break;


		// Ecriture des fichiers
		// Ecriture des fichiers
		case SDLK_w:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 10);break;
		case SDLK_x:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 11);break;
		case SDLK_c:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 12);break;
		case SDLK_v:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 13);break;
		case SDLK_b:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 14);break;
		case SDLK_n:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 15);break;
		case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierLecture(&(*controleur).systeme, );break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierLecture(&(*controleur).systeme, );break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierLecture(&(*controleur).systeme, );break;
		case SDLK_:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierLecture(&(*controleur).systeme, );break;
		case SDLK_:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierLecture(&(*controleur).systeme, );break;*/

		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurClavierCtrl(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
	// Sortie
		case SDLK_ESCAPE:
			(*controleur).sortie = 1;break;
	// Mode : attente d'un evenement / pas d'attente
		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeMode(controleur);break;

	// Enregistrement
		// Sauvegarde du système fichierEcriture sans effet
	/*	case SDLK_a:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 0);break;
		case SDLK_z:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 1);break;
		case SDLK_e:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 2);break;
		case SDLK_r:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 3);break;
		case SDLK_t:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 4);break;
		case SDLK_y:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 5);break;
		case SDLK_u:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 6);break;
		case SDLK_i:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 7);break;
		case SDLK_o:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 8);break;
		case SDLK_p:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 9);break;
		case SDLK_q:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 10);break;
		case SDLK_s:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 11);break;
		case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 12);break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 13);break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 14);break;
		case SDLK_h:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 15);break;


		// Ecriture des fichiers
		case SDLK_w:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 10);break;
		case SDLK_x:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 11);break;
		case SDLK_c:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 12);break;
		case SDLK_v:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 13);break;
		case SDLK_b:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 14);break;
		case SDLK_n:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, 15);break;
		case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, );break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, );break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, );break;
		case SDLK_:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, );break;
		case SDLK_:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, );break;*/

		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurSouris(controleurT * controleur)
	{
	float x, y;
	if((*controleur).appui==1)
		{
		x=-0.01*(float)((*controleur).interface.evenement.motion.xrel);
		y=0.1*HAUTEUR*(float)((*controleur).interface.evenement.motion.yrel);
		//fprintf(stderr, "controleurSouris yrel = %d , x = %f\n", (*controleur).evenement.motion.yrel, x);
		//fprintf(stderr, "controleurSouris xrel = %d , y = %f\n", (*controleur).evenement.motion.xrel, y);
		(void)x;(void)y;
		}
	return (*controleur).sortie;
	}

void controleurBoutonSouris(controleurT * controleur, int appui)
	{
	(*controleur).appui=appui;
	return;
	}
//////////////////////////////////////////////////////////////////////////////////////

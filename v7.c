#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h> //utilisation de FLT_MAX pour les moyennes

#define TAILLE_MAX_LIGNE 256
#define TAILLE_MAX_NOM_ATHLETE 20

typedef struct {
    char date[9];
    float temps;
    char epreuve[TAILLE_MAX_LIGNE];
} Athlete;

/*INFOS FONCTIONS
info_entrainement() récupère toutes les infos d'un entrainement pour un athlete sélectionné / fonctionne avec afficher_entrainement
ajout_entrainement() crée un nouvel entraînement en fonction d'un athlète, l'utilisateur entre la date, le temps de l'entraînement et la discipline
resume_temps() écrit la moyenne, le temps max et le temps minimum de l'athlete sélectionné pour une discipline donnée
trouver_meilleurs_athletes() lit les fichiers des athlètes, calcule leurs temps moyens, les trier et afficher les trois meilleurs.
*/


void info_entrainement(const char* ligne, Athlete* pentrainement) {
    // Utiliser sscanf pour extraire la date et le temps
    sscanf(ligne, "%8s %f", pentrainement->date, &pentrainement->temps);		

    // Copier le reste de la ligne pour l'épreuve
    const char* debut_epreuve = ligne + 14; 
    strncpy(pentrainement->epreuve, debut_epreuve, TAILLE_MAX_LIGNE - 1);
    pentrainement->epreuve[TAILLE_MAX_LIGNE - 1] = '\0'; // Assurer la terminaison de la chaîne
}


void afficher_entrainement(int numero_ligne) {
	
	int ligne_actuelle = 1;
    
	//ouverture du fichier en fonction du nom de l'athlète
	//--------------------------------------------------------
	char athlete_demande [TAILLE_MAX_NOM_ATHLETE]; //athlète recherché par l'entraîneur
	printf ("Entrez le nom de l'athlete que vous souhaitez :\n");
	scanf ("%s", athlete_demande);
	char nom_fichier [TAILLE_MAX_NOM_ATHLETE];
	sprintf(nom_fichier, "%s.txt", athlete_demande);  //créer le nom du fichier
	
    FILE *f = fopen(nom_fichier, "r"); //mode lecture car on récupère juste des infos

    if (f == NULL) {
        perror("Probleme ouverture fichier"); //code d'erreur + texte entre guillemets renvoyés
        exit(1);
    }
	//--------------------------------------------------------
	
	
    char ligne[TAILLE_MAX_LIGNE];
    Athlete pentrainement;
	
    // Lire chaque ligne du fichier
    while (fgets(ligne, sizeof(ligne), f)) {
        // Enlever le saut de ligne à la fin de la ligne lue (si présent)
        ligne[strcspn(ligne, "\n")] = 0;

        // Lire les données de l'entraînement à partir de la ligne
        info_entrainement(ligne, &pentrainement);
        ligne_actuelle++;
		
        if (ligne_actuelle == numero_ligne) {
            printf("Date : %s\n", pentrainement.date);
            printf("Temps : %.3f\n", pentrainement.temps);
            printf("Epreuve : %s\n", pentrainement.epreuve);
            printf("\n");
            break;
        }
    }
	
    fclose(f);
}



char* ajout_entrainement() {

    char nouvelle_date[9];
    float nouveau_temps;
    char nouvelle_epreuve[TAILLE_MAX_LIGNE];

    // Demander le nom de l'athlète
    char athlete_demande[TAILLE_MAX_NOM_ATHLETE];
    printf("Entrez le nom de l'athlete que vous souhaitez :\n");
    scanf("%s", athlete_demande);

    // Créer le nom du fichier
    char nom_fichier[TAILLE_MAX_NOM_ATHLETE];
    sprintf(nom_fichier, "%s.txt", athlete_demande);

    // Ouvrir le fichier en mode ajout
    FILE *f = fopen(nom_fichier, "a");
    if (f == NULL) {
        perror("Probleme ouverture fichier");
        exit(1);
    }

    // Positionner le curseur de fichier à la fin du fichier
    if (fseek(f, 0, SEEK_END) != 0) {
        perror("Erreur lors du positionnement du curseur dans le fichier");
        fclose(f);
        exit(1);
    }

    // Demander la date de l'entraînement
    printf("Entrez le nouvel entrainement au format JJ/MM/AA\n");
    scanf("%8s", nouvelle_date);

    // Demander le temps de l'entraînement
    printf("Entrez le nouveau temps au format 00.000\n");
    scanf("%f", &nouveau_temps);

    // Lire la ligne complète pour l'épreuve
    printf("Entrez la discipline\n");
    getchar(); // Pour consommer le caractère de nouvelle ligne laissé par le scanf précédent
    fgets(nouvelle_epreuve, TAILLE_MAX_LIGNE, stdin);				//info internet ; stdin est un pointeur de type FILE* qui représente le flux d'entrée standard en C. stdin est utilisé pour lire les données entrées par l'utilisateur depuis le clavier;

    // Écrire les données dans le fichier
    fprintf(f, "%s%.3f%s", nouvelle_date, nouveau_temps, nouvelle_epreuve);

    fclose(f);
    return "Ajout de ligne confirmé";
}



float resume_temps(char epreuve_demandee[TAILLE_MAX_LIGNE], char athlete_demande [TAILLE_MAX_NOM_ATHLETE]) {
    
	
	//ouverture du fichier en fonction du nom de l'athlète
	//--------------------------------------------------------
	 //athlète recherché par l'entraîneur
	
	char nom_fichier [TAILLE_MAX_NOM_ATHLETE];
	sprintf(nom_fichier, "%s.txt", athlete_demande);  //créer le nom du fichier
	
    FILE *f = fopen(nom_fichier, "r"); //mode lecture car on récupère juste des infos

    if (f == NULL) {
        perror("Probleme ouverture fichier"); //code d'erreur + texte entre guillemets renvoyés
        exit(1);
    }
	//--------------------------------------------------------
	
	char ligne[TAILLE_MAX_LIGNE];
	
	float min_temps = FLT_MAX;
	float max_temps = 0;
    float somme_temps = 0;
    int nombre_entrainements = 0;
	
	Athlete pentrainement;

    	
	// Lire chaque ligne du fichier
    while (fgets(ligne, sizeof(ligne), f)) {
        // Enlever le saut de ligne à la fin de la ligne lue (si présent)
        ligne[strcspn(ligne, "\n")] = 0;

        // Lire les données de l'entraînement à partir de la ligne
        info_entrainement(ligne, &pentrainement);

        // Vérifier si l'épreuve de l'entraînement correspond à l'épreuve demandée
        if (strcmp(pentrainement.epreuve, epreuve_demandee) == 0) {
            // Ajouter le temps de cet entraînement à la somme totale
            if (pentrainement.temps < min_temps){
			min_temps = pentrainement.temps;
		}
		if (pentrainement.temps > max_temps){
			max_temps = pentrainement.temps;
		}
			
			somme_temps += pentrainement.temps;
            nombre_entrainements++;
        }
    }
	
    fclose(f);

    // Calculer la moyenne des temps
    if (nombre_entrainements > 0) {
		
		printf ("minimmum : %.3f\nmaximum : %.3f\nmoyenne : %.3f\n", min_temps, max_temps, (somme_temps / nombre_entrainements));
        return somme_temps / nombre_entrainements;	
    }
	
	else {
		printf ("aucun entrainement trouvé pour cette epreuve");
        return 0; // Retourner 0 si aucun entraînement pour cette épreuve n'a été trouvé
    }
}



int main() {
	
    int choix;  //stocker le choix de l'utilisateur
	int numero_ligne; //pour la fonction info_entrainement
	char athlete_demande[TAILLE_MAX_NOM_ATHLETE];
	char epreuve_demandee[TAILLE_MAX_LIGNE];
	
    do {
        // Affichage du menu principal
        printf("\nMenu:\n");
        printf("1) Ajouter un entrainement\n");
        printf("2) Afficher les infos d'un entrainement\n");
        printf("3) Afficher le resume des temps d'un athlete\n");
        //printf("4) Trouver les meilleurs athletes pour une epreuve\n");
        printf("0) Quitter\n\n");
        printf("Entrez votre choix: ");

        // Lecture du choix de l'utilisateur
        if (scanf("%d", &choix) != 1) {
            // Si la lecture échoue
            while (getchar() != '\n');  // Vider le buffer d'entrée
            choix = -1;  // Valeur invalide pour forcer la réaffichage du menu
        }

        // Exécution 
        switch (choix) {
			
            case 1:
		ajout_entrainement();
                break;
				
            case 2:
                printf("Entrez le numero d'entrainement voulu :\n");
                scanf("%d", &numero_ligne);
                getchar(); // Pour absorber le caractère de saut de ligne restant
                afficher_entrainement(numero_ligne+1);
		break;
	
            case 3:
		printf ("Entrez le nom de l'athlete que vous souhaitez :\n");
		scanf ("%s", athlete_demande);
		    
		printf("Entrez le nom de l'epreuve pour laquelle vous souhaitez calculer la moyenne des temps :\n");
		scanf("%s", epreuve_demandee);
	
                resume_temps(epreuve_demandee, athlete_demande);
		break;
				
           /* case 4:
            break;	*/	
				
            case 0:
                printf("Au revoir!\n");  // Message de sortie
                break;
				
            default:
                // Si le choix est invalide, afficher un message d'erreur
                printf("Choix invalide, veuillez reessayer.\n");
        }
    } while (choix != 0);  // Répéter le menu jusqu'à ce que l'utilisateur choisisse de quitter (choix 0)


    return 0;  // Retourner 0 pour indiquer que le programme s'est terminé avec succès
}

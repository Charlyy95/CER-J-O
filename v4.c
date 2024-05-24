#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX_LIGNE 30 // Longueur maximale d'une ligne, un nom et un prénom feront moins de 30 caractères
#define MAX_ATHLETES 100 // Le nombre maximal d'athletes

/*INFOS FONCTIONS
info_entrainement() écrit toutes les infos d'un entrainement pour un athlete sélectionné
ajout_entrainement() crée un nouvel entraînement en fonction d'un athlète, l'utilisateur entre la date et le temps de l'entraînement
resume_temps_athlete() écrit la moyenn, le temps max et le temps minimum de l'athlete sélectionné
calculer_moyenne() lit les fichiers des athletes (précisément leur temps) et calcule leur temps moyen pour une épreuve demandée ou donnée
trouver_meilleurs_athletes() lit les fichiers des athlètes, calcule leurs temps moyens, les trier et afficher les trois meilleurs.
*/





// Définition de la structure
typedef struct {
    char nom[TAILLE_MAX_LIGNE];
    char epreuve[TAILLE_MAX_LIGNE];
    char date[9];
    char temps_seconde[TAILLE_MAX_LIGNE];
	float temps;			//utile pour convertir le temps en float après
} Athlete;

void info_entrainement(){
	
	int numero_ligne;
	int ligne_actuelle = 1;
	
	//ouverture du fichier en focntion du nom de l'athlète
	//--------------------------------------------------------
	char athlete_demande [TAILLE_MAX_LIGNE]; //athlète recherché par l'entraîneur
	printf ("Entrez le nom de l'athlete que vous souhaitez :\n");
	scanf ("%s", athlete_demande);
	char nom_fichier [TAILLE_MAX_LIGNE];
	sprintf(nom_fichier, "%s.txt", athlete_demande);  //créer le nom du fichier
	
    FILE *f = fopen(nom_fichier, "r"); //mode lecture car on récupère juste des infos

    if (f == NULL) {
        perror("Probleme ouverture fichier"); //code d'erreur + texte entre guillemets renvoyés
        exit(1);
    }
	//--------------------------------------------------------
	
    Athlete donnees; // Structure pour stocker les données de l'athlète
    
    printf("Entrez le numero d'entrainement voulu :\n");
    scanf("%d", &numero_ligne);
    getchar(); // Pour absorber le caractère de saut de ligne restant

    // Déterminer quelle partie de la structure à remplir en fonction du numéro de la ligne
    
	//Parcours du fichier dans son intégralité
	//--------------------------------------------------------
	fgets(donnees.nom, TAILLE_MAX_LIGNE, f);
	fgets(donnees.epreuve, TAILLE_MAX_LIGNE, f);
	
    while ((fgets(donnees.date, 9, f)!= NULL)&&(fgets(donnees.temps_seconde, TAILLE_MAX_LIGNE, f))!= NULL) {
        
		ligne_actuelle++;
		if (ligne_actuelle == numero_ligne+1) {
			break;
		}
	}

    if (ligne_actuelle < numero_ligne+1) {
        printf("L'entrainement n'existe pas.\n");
        exit(2);
    }
	//--------------------------------------------------------
	

    // Afficher les données de la structure
    printf("Entrainement numero :  %d \n", numero_ligne);
    printf("Nom de l'athlete : %s", donnees.nom);
    printf("Epreuve : %s", donnees.epreuve);
    printf("Date : %s \n", donnees.date);
    printf("Temps : %s\n", donnees.temps_seconde);
	
	donnees.temps = atof (donnees.temps_seconde); //conversion du temps récupéré (char) en float
	
	fclose(f);
}


void ajout_entrainement(){
	
	char nouvelle_date [9];
	char nouveau_temps [7];
	
	//ouverture du fichier en focntion du nom de l'athlète
	//--------------------------------------------------------
	char athlete_demande [TAILLE_MAX_LIGNE]; //athlète recherché par l'entraîneur
	printf ("Entrez le nom de l'athlete que vous souhaitez :\n");
	scanf ("%s", athlete_demande);
	char nom_fichier [TAILLE_MAX_LIGNE];
	sprintf(nom_fichier, "%s.txt", athlete_demande);  //créer le nom du fichier
	
    FILE *f = fopen(nom_fichier, "a"); //mode ajout car on rajoute des entraînements à la fin du fichier

    if (f == NULL) {
        perror("Probleme ouverture fichier"); //code d'erreur + texte entre guillemets renvoyés
        exit(1);
    }
	//--------------------------------------------------------
	
	// Positionner le curseur de fichier à la fin du fichier
    if (fseek(f, 0, SEEK_END) != 0) {
        perror("Erreur lors du positionnement du curseur dans le fichier");
        fclose(f);
	}
	// Demander la date de l'entraînement
    printf("Entrez le nouvel entrainement au format JJ/MM/AA\n");
    scanf("%8s", nouvelle_date); // Limite à 8 caractères (format JJ/MM/AA)
    fprintf(f, "\n%s", nouvelle_date);
    
    // Demander le temps de l'entraînement
    printf("Entrez le nouveau temps au format 00.000\n");
    scanf("%6s", nouveau_temps); // Limite à 6 caractères (format 00.000)
    fprintf(f, " %s", nouveau_temps); // Ajoute le temps sur la même ligne que la date
    
    fclose(f);
}

void resume_temps_athlete(){
	
	int numero_ligne;
	int ligne_actuelle = 1;
	float somme_temps = 0;
	float min_temps = 1000;
	float max_temps = 0;
	
	//ouverture du fichier en focntion du nom de l'athlète
	//--------------------------------------------------------
	char athlete_demande [TAILLE_MAX_LIGNE]; //athlète recherché par l'entraîneur
	printf ("Entrez le nom de l'athlete que vous souhaitez :\n");
	scanf ("%s", athlete_demande);
	char nom_fichier [TAILLE_MAX_LIGNE];
	sprintf(nom_fichier, "%s.txt", athlete_demande);  //créer le nom du fichier
	
    FILE *f = fopen(nom_fichier, "r"); //mode lecture car on récupère juste des infos

    if (f == NULL) {
        perror("Probleme ouverture fichier"); //code d'erreur + texte entre guillemets renvoyés
        exit(1);
    }
	//--------------------------------------------------------
	
	Athlete donnees; // Structure pour stocker les données de l'athlète
	
	//Parcours du fichier dans son intégralité
	//--------------------------------------------------------
	fgets(donnees.nom, TAILLE_MAX_LIGNE, f);
	fgets(donnees.epreuve, TAILLE_MAX_LIGNE, f);
	
    while ((fgets(donnees.date, 9, f)!= NULL)&&(fgets(donnees.temps_seconde, TAILLE_MAX_LIGNE, f))!= NULL) {
        
		donnees.temps = atof (donnees.temps_seconde); //conversion du temps récupéré (char) en float 
		if (donnees.temps < min_temps){
			min_temps = donnees.temps;
		}
		if (donnees.temps > max_temps){
			max_temps = donnees.temps;
		}
		
		somme_temps+= donnees.temps;
		ligne_actuelle++;
		
		
		if (ligne_actuelle == numero_ligne+1) {
			break;
		}
	//printf ("%.3f s\n", donnees.temps);		ligne pour écrire chaque temps 1 par 1
	}
	
	printf ("moyenne des temps : %.3f s\n", (somme_temps/(ligne_actuelle-1)));
	printf ("temps minimum : %.3f s\n", min_temps);
	printf ("temps maximum : %.3f s\n", max_temps);
	//recupérer temps athlete puis max, min, moyenne.
	
	
	//--------------------------------------------------------
	
}

float calculer_moyenne(FILE *f, const char *epreuve) {
    char date[9], temps_seconde[TAILLE_MAX_LIGNE], epreuve_temp[TAILLE_MAX_LIGNE];
    float temps, somme_temps = 0;
    int nb_entrainements = 0;

    // Lire le nom et l'épreuve de l'athlète
    fgets(epreuve_temp, TAILLE_MAX_LIGNE, f); // Lire le nom 
    fgets(epreuve_temp, TAILLE_MAX_LIGNE, f); // Lire l'épreuve 

    // Lire les dates et les temps de l'athlète
    while ((fgets(date, 9, f) != NULL) && (fgets(temps_seconde, TAILLE_MAX_LIGNE, f) != NULL)) {
        temps = atof(temps_seconde); // Convertir le temps de chaîne de caractères en nombre flottant
        if (strncmp(epreuve_temp, epreuve, strlen(epreuve)) == 0) { // Comparer les epreuves
            somme_temps += temps; // Ajouter le temps à la somme des temps
            nb_entrainements++; // Augmenter le compteur d'entraînements
        }
    }

    return (nb_entrainements > 0) ? (somme_temps / nb_entrainements) : 0; //Ajouter les temps et diviser par le nombre d'entraînements pour obtenir la moyenne,retourner la moyenne des temps
}

void trouver_meilleurs_athletes(const char *epreuve) {
    Athlete athletes[MAX_ATHLETES];
    int nb_athletes = 0;
    char nom_fichier[TAILLE_MAX_LIGNE];
    char nom_athlete[TAILLE_MAX_LIGNE];

    // Lire les fichiers des athlètes
    while (1) {
        printf("Entrez le nom de l'athlete (ou 'fin' pour terminer) :\n");
        scanf("%s", nom_athlete);
        if (strcmp(nom_athlete, "fin") == 0) break; // Si l'utilisateur entre "fin", arrêter la lecture

        sprintf(nom_fichier, "%s.txt", nom_athlete); // Créer le nom du fichier à partir du nom de l'athlète
        FILE *f = fopen(nom_fichier, "r"); // Ouvrir le fichier en mode lecture
        if (f == NULL) {
            perror("Probleme ouverture fichier");
            continue; // Si le fichier ne peut pas être ouvert, afficher un message d'erreur et passer au suivant
        }

        float moyenne = calculer_moyenne(f, epreuve); // Calculer la moyenne des temps pour l'épreuve grace a la fonction créée auparavant
        fclose(f); // Fermer le fichier

        if (moyenne > 0) {
            strcpy(athletes[nb_athletes].nom, nom_athlete); // Copier le nom de l'athlète
            strcpy(athletes[nb_athletes].epreuve, epreuve); // Copier le nom de l'épreuve
            athletes[nb_athletes].temps = moyenne; // Enregistrer la moyenne des temps
            nb_athletes++; // Incrémenter le nombre d'athlètes
        }
    }

    // Trier les athlètes par temps moyen
    for (int i = 0; i < nb_athletes - 1; i++) {
        for (int j = i + 1; j < nb_athletes; j++) {
            if (athletes[i].temps > athletes[j].temps) {
                Athlete temp = athletes[i]; // variable temporaire temp pour pouvoir echanger les athletes si par exemple l'athlète à la position i a un temps moyen supérieur à celui de la position j
                athletes[i] = athletes[j];
                athletes[j] = temp;
            }
        }
    }

    // Afficher les trois meilleurs athlètes
    printf("Les trois meilleurs athlètes pour l'épreuve %s sont:\n", epreuve);
    for (int i = 0; i < 3 && i < nb_athletes; i++) {
        printf("%s avec un temps moyen de %.3f secondes\n", athletes[i].nom, athletes[i].temps);
    }
}


int main() {
    int choix;  //stocker le choix de l'utilisateur
    char epreuve[TAILLE_MAX_LIGNE];  //stocker le nom de l'épreuve
    char athlete[TAILLE_MAX_LIGNE];  //stocker le nom de l'athlète

    do {
        // Affichage du menu principal
        printf("\nMenu:\n");
        printf("1) Ajouter un entrainement\n");
        printf("2) Afficher les infos d'un entrainement\n");
        printf("3) Afficher le resume des temps d'un athlete\n");
        printf("4) Calculer la moyenne des temps pour une epreuve\n");
        printf("5) Trouver les meilleurs athletes pour une epreuve\n");
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
                
				if (ajout_entrainement() == "ajout de ligne confirme"){	//confirmation du bon déroulement de la fonction
					printf ("Ajout de ligne confirme\n");
				}
                break;
            case 2:
                info_entrainement();  // Afficher les informations d'un entrainement
                break;
            case 3:
                resume_temps_athlete();  // Afficher le résumé des temps d'un athlète
                break;
            case 4:
                // Calculer la moyenne des temps pour une épreuve
                printf("Entrez l'epreuve pour laquelle vous voulez calculer la moyenne des temps :\n");
                scanf("%s", epreuve);
                printf("Entrez le nom de l'athlete :\n");
                scanf("%s", athlete);
                {
                    // Blocs pour déclarer des variables locales
                    char nom_fichier[TAILLE_MAX_LIGNE];  
                    sprintf(nom_fichier, "%s.txt", athlete);  // Créer le nom du fichier pour l'athlète
                    FILE *f = fopen(nom_fichier, "r");  // Ouvrir le fichier en mode lecture
                    if (f != NULL) {
                        // Si le fichier est ouvert avec succès
                        float moyenne = calculer_moyenne(f, epreuve);  // Calculer la moyenne des temps
                        printf("La moyenne des temps pour l'epreuve %s est %.3f secondes.\n", epreuve, moyenne);
                        fclose(f);  // Fermer le fichier
                    } else {
                        perror("Probleme ouverture fichier");  // Afficher un message d'erreur si le fichier ne peut pas être ouvert
                    }
                }
                break;
            case 5:
                // Trouver les meilleurs athlètes pour une épreuve
                printf("Entrez l'épreuve pour laquelle vous voulez trouver les meilleurs athlètes :\n");
                scanf("%s", epreuve);
                trouver_meilleurs_athletes(epreuve);  // Appeler la fonction pour trouver les meilleurs athlètes
                break;
            case 0:
                printf("Au revoir!\n");  // Message de sortie
                break;
            default:
                // Si le choix est invalide, afficher un message d'erreur
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 0);  // Répéter le menu jusqu'à ce que l'utilisateur choisisse de quitter (choix 0)

    return 0;  // Retourner 0 pour indiquer que le programme s'est terminé avec succès
}



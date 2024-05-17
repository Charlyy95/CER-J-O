#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX_LIGNE 30 // Longueur maximale d'une ligne, un nom et un prénom feront moins de 30 caractères

/*INFOS FONCTIONS
info_entrainement() écrit toutes les infos d'un entrainement pour un athlete sélectionné
ajout_entrainement() crée un nouvel entraînement en fonction d'un athlète, l'utilisateur entre la date et le temps de l'entraînement
resume_temps_athlete écrit la moyenn, le temps max et le temps minimum de l'athlete sélectionné

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
	printf ("le temps est de %.3f secondes \n", donnees.temps);
	
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

int main() {
    
	//ajout_entrainement();
	//info_entrainement();
	//resume_temps_athlete();
	
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX_LIGNE 30 // Longueur maximale d'une ligne

// Définition de la structure
typedef struct {
    char nom[TAILLE_MAX_LIGNE];
    char epreuve[TAILLE_MAX_LIGNE];
    char premiers_8[9];
    char caracteres_10_11[TAILLE_MAX_LIGNE];
} Athlete;

void info_entrainement(){
	
	char athlete_demande [TAILLE_MAX_LIGNE];
	
	printf ("Entrez le nom de l'athlete que vous souhaitez :\n");
	scanf ("%s", athlete_demande);
	char nom_fichier [TAILLE_MAX_LIGNE];
	sprintf(nom_fichier, "%s.txt", athlete_demande);  //créer le nom du fichier
	
    FILE *f = fopen(nom_fichier, "r"); 

    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
	rewind(f);
	
	
    Athlete donnees; // Structure pour stocker les données de l'athlète
    int numero_ligne;
    printf("Entrez le numero d'entrainement voulu :\n");
    scanf("%d", &numero_ligne);
    getchar(); // Pour absorber le caractère de saut de ligne restant

    // Déterminer quelle partie de la structure à remplir en fonction du numéro de la ligne
    int ligne_actuelle = 1;
	
	fgets(donnees.nom, TAILLE_MAX_LIGNE, f);
	fgets(donnees.epreuve, TAILLE_MAX_LIGNE, f);
	
    while ((fgets(donnees.premiers_8, 9, f)!= NULL)&&(fgets(donnees.caracteres_10_11, TAILLE_MAX_LIGNE, f))!= NULL) {
        
		ligne_actuelle++;
		if (ligne_actuelle == numero_ligne+1) {
			break;
		}
	}

    if (ligne_actuelle < numero_ligne+1) {
        printf("L'entrainement n'existe pas.\n");
        exit(EXIT_FAILURE);
    }

    // Afficher les données de la structure
    printf("Entrainement numero :  %d \n", numero_ligne);
    printf("Nom de l'athlete : %s", donnees.nom);
    printf("Epreuve : %s", donnees.epreuve);
    printf("Date : %s \n", donnees.premiers_8);
    printf("Temps : %s", donnees.caracteres_10_11);
	
	fclose(f);
}


int main() {
    
	
	info_entrainement();
	
    return 0;
}
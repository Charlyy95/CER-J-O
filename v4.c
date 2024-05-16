#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX_LIGNE 30 // Longueur maximale d'une ligne, un nom et un prénom feront moins de 30 caractères

/*INFOS FONCTIONS
info_entrainement() écrit toutes les infos d'un entrainement pour un athlete sélectionné 
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
	
    FILE *f = fopen(nom_fichier, "r"); 

    if (f == NULL) {
        perror("Probleme ouverture fichier"); //code d'erreur + t"exte entre guillemets renvoyés
        exit(1);
    }
	//--------------------------------------------------------
	
    Athlete donnees; // Structure pour stocker les données de l'athlète
    
    printf("Entrez le numero d'entrainement voulu :\n");
    scanf("%d", &numero_ligne);
    getchar(); // Pour absorber le caractère de saut de ligne restant

    // Déterminer quelle partie de la structure à remplir en fonction du numéro de la ligne
    
	
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

    // Afficher les données de la structure
    printf("Entrainement numero :  %d \n", numero_ligne);
    printf("Nom de l'athlete : %s", donnees.nom);
    printf("Epreuve : %s", donnees.epreuve);
    printf("Date : %s \n", donnees.date);
    printf("Temps : %s", donnees.temps_seconde);
	
	donnees.temps = atof (donnees.temps_seconde); //conversion du temps récupéré (char) en float 
	printf ("le temps est de %.3f secondes \n", donnees.temps);
	
	fclose(f);
}


void ajout_entrainement(){
	
	//ouverture du fichier en focntion du nom de l'athlète
	//--------------------------------------------------------
	char athlete_demande [TAILLE_MAX_LIGNE]; //athlète recherché par l'entraîneur
	printf ("Entrez le nom de l'athlete que vous souhaitez :\n");
	scanf ("%s", athlete_demande);
	char nom_fichier [TAILLE_MAX_LIGNE];
	sprintf(nom_fichier, "%s.txt", athlete_demande);  //créer le nom du fichier
	
    FILE *f = fopen(nom_fichier, "a"); 

    if (f == NULL) {
        perror("Probleme ouverture fichier"); //code d'erreur + t"exte entre guillemets renvoyés
        exit(1);
    }
	//--------------------------------------------------------
	
	// Positionner le curseur de fichier à la fin du fichier
    if (fseek(f, 0, SEEK_END) != 0) {
        perror("Erreur lors du positionnement du curseur de fichier");
        fclose(f);
	}
	fprintf (f, "05/06/07 14.562\n");
	
	fclose(f);
}

int main() {
    
	ajout_entrainement();
	//info_entrainement();
	
    return 0;
}

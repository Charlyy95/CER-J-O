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

// Fonction pour vérifier le format de la date (JJ/MM/AA)
int verifier_format_date(const char* date) {
    int jour, mois, annee;
    return sscanf(date, "%2d/%2d/%2d", &jour, &mois, &annee) == 3;
}

// Fonction pour vérifier la validité de l'épreuve
int verifier_epreuve(const char* epreuve) {
    return strcmp(epreuve, "100m") == 0 || strcmp(epreuve, "400m") == 0 || strcmp(epreuve, "5000m") == 0;
}

// Fonction pour vérifier le format du temps (00.000)
int verifier_format_temps(float temps) {
    return temps >= 0.0 && temps < 100.0;
}

// Fonction pour récupérer les informations d'un entraînement à partir d'une ligne du fichier
void info_entrainement(const char* ligne, Athlete* pentrainement) {
    // Utiliser sscanf pour extraire la date et le temps
    sscanf(ligne, "%8s%f", pentrainement->date, &pentrainement->temps);		

    // Copier le reste de la ligne pour l'épreuve
    const char* debut_epreuve = ligne + 14; 
    strncpy(pentrainement->epreuve, debut_epreuve, TAILLE_MAX_LIGNE - 1);
    pentrainement->epreuve[TAILLE_MAX_LIGNE - 1] = '\0'; // Assurer la terminaison de la chaîne
}

// Fonction pour afficher les informations d'un entraînement spécifique
void afficher_entrainement(int numero_ligne) {
    int ligne_actuelle = 1;

    char athlete_demande[TAILLE_MAX_NOM_ATHLETE];
    printf("Entrez le nom de l'athlete que vous souhaitez :\n");
    scanf("%s", athlete_demande);
    char nom_fichier[TAILLE_MAX_NOM_ATHLETE];
    sprintf(nom_fichier, "%s.txt", athlete_demande);  //créer le nom du fichier

    FILE* f = fopen(nom_fichier, "r"); //mode lecture car on récupère juste des infos

    if (f == NULL) {
        perror("Probleme ouverture fichier"); //gestion des erreurs de fichier
        exit(1);
    }

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

// Fonction pour ajouter un nouvel entraînement
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
    FILE* f = fopen(nom_fichier, "a");
    if (f == NULL) {
        perror("Probleme ouverture fichier"); //gestion des erreurs de fichier
        exit(1);
    }

    // Positionner le curseur de fichier au début
    rewind(f);

    // Demander et vérifier la date de l'entraînement
    do {
        printf("Entrez la date au format JJ/MM/AA: ");
        scanf("%8s", nouvelle_date);
        if (!verifier_format_date(nouvelle_date)) {
            printf("Format de date incorrect. Veuillez entrer une date valide.\n");
        }
    } while (!verifier_format_date(nouvelle_date));

    // Demander et vérifier le temps de l'entraînement
    do {
        printf("Entrez le nouveau temps au format 00.000: ");
        scanf("%f", &nouveau_temps);
        if (!verifier_format_temps(nouveau_temps)) {
            printf("Format de temps incorrect. Veuillez entrer un temps valide.\n");
        }
    } while (!verifier_format_temps(nouveau_temps));

    // Demander et vérifier l'épreuve
    do {
        printf("Entrez la discipline (100m, 400m, 5000m): ");
        scanf("%s", nouvelle_epreuve);
        if (!verifier_epreuve(nouvelle_epreuve)) {
            printf("Epreuve incorrecte. Veuillez entrer une discipline valide.\n");
        }
    } while (!verifier_epreuve(nouvelle_epreuve));

    // Écrire les données dans le fichier
    fprintf(f, "%s %.3f %s\n", nouvelle_date, nouveau_temps, nouvelle_epreuve);

    fclose(f);
    return "Ajout de ligne confirmé";
}

// Fonction pour calculer et afficher le résumé des temps pour une épreuve donnée
float resume_temps(char epreuve_demandee[TAILLE_MAX_LIGNE], char athlete_demande[TAILLE_MAX_NOM_ATHLETE]) {
    char nom_fichier[TAILLE_MAX_NOM_ATHLETE];
    sprintf(nom_fichier, "%s.txt", athlete_demande);  //créer le nom du fichier

    FILE* f = fopen(nom_fichier, "r"); //mode lecture car on récupère juste des infos

    if (f == NULL) {
        perror("Probleme ouverture fichier"); //gestion des erreurs de fichier
        exit(1);
    }
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
              if (pentrainement.temps < min_temps) {
                  min_temps = pentrainement.temps;
              }
              if (pentrainement.temps > max_temps) {
                  max_temps = pentrainement.temps;
              }

              somme_temps += pentrainement.temps;
              nombre_entrainements++;
          }
      }

      fclose(f);

      // Calculer la moyenne des temps
      if (nombre_entrainements > 0) {
          printf("Minimum : %.3f\nMaximum : %.3f\nMoyenne : %.3f\n", min_temps, max_temps, (somme_temps / nombre_entrainements));
          return somme_temps / nombre_entrainements;
      } else {
          printf("Aucun entraînement trouvé pour cette épreuve.\n");
          return 0; // Retourner 0 si aucun entraînement pour cette épreuve n'a été trouvé
      }
  }

  int main() {
      int choix;  // Stocker le choix de l'utilisateur
      int numero_ligne; // Pour la fonction info_entrainement
      char athlete_demande[TAILLE_MAX_NOM_ATHLETE];
      char epreuve_demandee[TAILLE_MAX_LIGNE];

      do {
          // Affichage du menu principal
          printf("\nMenu:\n");
          printf("1) Ajouter un entrainement\n");
          printf("2) Afficher les infos d'un entrainement\n");
          printf("3) Afficher le resume des temps d'un athlete\n");
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
                  printf("Entrez le nom de l'athlete que vous souhaitez :\n");
                  scanf("%s", athlete_demande);

                  printf("Entrez le nom de l'epreuve pour laquelle vous souhaitez calculer la moyenne des temps :\n");
                  scanf("%s", epreuve_demandee);

                  resume_temps(epreuve_demandee, athlete_demande);
                  break;

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

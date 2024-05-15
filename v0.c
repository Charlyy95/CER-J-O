#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char nom;
	char epreuve;
	char date;
	float temps;	
}athlete;


int main(){
	char *nom="Mayer.txt";
	// ouvrir le fichier 
	FILE* f = fopen(nom, "r");
	if(f==NULL){
		printf ("fichier non-trouvé");
		exit(1);
	}
	// recuperer une ligne
	signed char texte [256]; //taille max de la ligne
	while (fgets (texte, 255, f)!=NULL){
		printf("");
	}
	printf ("%s", texte);

	fclose (f);
	return 0;

}

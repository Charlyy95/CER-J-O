#include <stdio.h>
#include <stdlib.h>


int main(){
	char *nom="Mayer.txt";
	// ouvrir le fichier 
	FILE* f = fopen(nom, "r");
	if(f==NULL){
		printf ("fichier non-trouvé");
		exit(1);
	}
	// recuperer une ligne
	signed char texte [256];
	while (fgets (texte, 255, f)!=NULL){
		printf ("%s\n", texte);
	}

	fclose (f);
	return 0;
}

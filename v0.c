#include <stdio.h>
#include <stdlib.h>


int main(){
	char *nom="Mayer.txt";
	// ouvrir le fichier 
	FILE* fichier =fopen(nom, "r");
	if(fichier==NULL){
		exit(1);
	}
	// recuperer un caractère
	
	int a;
	a=fgetc(fichier);
	printf ("%c", a);
	
	while(a!=EOF){
		printf("%c\n",a);
		a=fgetc(fichier);
	}
	
	return 0;
}

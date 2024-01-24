#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PRODUIT 100
#define MAX_CODE 100

void AjouterProduit(char Code[][MAX_CODE], int Quantite[], int* NB, char* code, int quantite) {
    int i;

    // Vérification si le produit existe
    for (i = 0; i < *NB; i++) {
        if (strcmp(Code[i], code) == 0) { //ajouter la quantité dans le cas d'existance de produit 
            Quantite[i] += quantite;
            printf("Le produit a été ajouté au stock avec une quantité de %d.\n", quantite);
            return;
        }
    }

    if (*NB < MAX_PRODUIT) { // reussite de trouvee une place a stockee le produit
        strcpy(Code[*NB], code); // le code est copier dans Code[NB] 
        Quantite[*NB] = quantite;
        (*NB)++;// incrémentation de 1 pour ajoutedu nouveau produit
        printf("Le produit a été ajouté au stock avec une quantité de %d.\n", quantite);
    } else {
        printf("Le stock est plein.\n");
    }
}

void RetireProduit(char Code[][MAX_CODE], int Quantite[], int* NB, char* code, int quantite) {
    int index = -1;
    int i;

    for (i = 0; i < *NB; i++) {
        if (strcmp(Code[i], code) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Le produit n'existe pas.\n");
    } else if (Quantite[index] < quantite) {
        printf("La quantité demandée est supérieure à la quantité en stock.\n");
    } else {
        Quantite[index] -= quantite;
        printf("La quantité %d a été retirée du stock.\n", quantite);
    }

    if (Quantite[index] == 0) { 	// si la quantite en stock est 0 , supp le produit du stock
        for (i = index; i < *NB - 1; i++) {// deplacer les elment vers indice index pour remplir le vide
            strcpy(Code[i], Code[i+1]);
            Quantite[i] = Quantite[i + 1];
        }
        (*NB)--;
    }
}

void AffichageTotal(char Code[][MAX_CODE], int Quantite[], int NB) {
    int i;
    printf("Stock à afficher :\n");
    for (i = 0; i < NB; i++) {
        printf("Code : %s, Quantité : %d\n", Code[i], Quantite[i]);
    }
}

int main() {
    char Code[MAX_PRODUIT][MAX_CODE];
    int Quantite[MAX_PRODUIT];
    int NB = 0;

    char code[MAX_CODE];
    int quantite;
    int choix;
    do {
    	printf("\n1 - Ajouter un produit\n");
        printf("2 - Retirer un produit\n");
        printf("3 - Afficher le stock total\n");
        printf("\nChoix : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                printf("\nAjouter un produit :\n");
                printf("Entrer le code : ");
                scanf("%s", code);
                printf("Entrer la quantité : ");
                scanf("%d", &quantite);
                AjouterProduit(Code, Quantite, &NB, code, quantite);
                break;
            case 2:
                printf("\nRetirer un produit :\n");
                printf("Entrer le code : ");
                scanf("%s", code);
                printf("Entrer la quantité : ");
                scanf("%d", &quantite);
                RetireProduit(Code, Quantite, &NB, code, quantite);
                break;
            case 3:
                printf("\nAffichage du stock total :\n");
                AffichageTotal(Code, Quantite, NB);
                break;
            default:
                printf("\nERREUR : Choix invalide.\n");
                break;
        }
    }while (choix != 0);
        
    return 0;
}

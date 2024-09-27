#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
   int ligne;
   int colonne;
}coordonees;

void initGrille(char **Grille, int nbLignes, int nbColonnes)
{
    for (int i = 0; i < nbLignes; i++)
    {
        for (int j = 0; j < nbColonnes; j++)
        {
            Grille[i][j] = ' ';
        }  
    }
}

void setValue(char **Grille, coordonees coord, char value)
{
        Grille[coord.ligne-1][coord.colonne-1] = value; 
}

int checkCoordonees(char **Grille, coordonees coord, int nbLignes , int nbColonnes)
{
    if (coord.ligne-1 < 0 || coord.ligne-1 > nbLignes-1 || coord.colonne-1 < 0 || coord.colonne-1 > nbColonnes-1) {
        printf("Erreur : Coordonnees hors limites !\n");
        return 0; 
    }

    if(Grille[coord.ligne-1][coord.colonne-1] != ' ')
    {
        printf("Erreur : Casse deja prise !\n");
        return 0;
    }
    return 1 ;
}

void display(char **Grille, int nbLignes, int nbColonnes)
{
    for (int i = 0; i < nbLignes; i++)
    {
       if (i != 0) printf("-----------\n");  
        for (int j = 0; j < nbColonnes; j++)
        {
            if(j == 0){
                printf(" %c ", Grille[i][j]);
            }else{
                printf("| %c ", Grille[i][j]);
            }
        }
        printf("\n");
    } 
}


int endGame(char **Grille, int nbLignes, int nbColonnes)
{
    // Verifie les lignes
    for (int i = 0; i < nbLignes; i++)
    {
        if (Grille[i][0] != ' ' && Grille[i][0] == Grille[i][1] && Grille[i][1] == Grille[i][2])  return 1; // Victoire
    }

    // Verifie les colonnes
    for (int j = 0; j < nbColonnes; j++)
    {
        if (Grille[0][j] != ' ' && Grille[0][j] == Grille[1][j] && Grille[1][j] == Grille[2][j]) return 1; // Victoire
    }

    // Verifie la diagonale gauche
    if (Grille[0][0] != ' ' && Grille[0][0] == Grille[1][1] && Grille[1][1] == Grille[2][2]) return 1; // Victoire
    
    // Verifie la diagonale droite
    if (Grille[0][2] != ' ' && Grille[0][2] == Grille[1][1] && Grille[1][1] == Grille[2][0]) return 1; // Victoire
    
    // Verifie si la grille est remplie
    for (int i = 0; i < nbLignes; i++) {
        for (int j = 0; j < nbColonnes; j++) {
            if (Grille[i][j] == ' ') {
                return 0; 
            }
        }
    }

    return -1; // Match nul
}



int main()
{
    static int nblignes = 3;
    static int nbColonnes = 3;

    //Allocation dynamique de la grille 
    char **Grille = (char **)malloc(nblignes*sizeof(char*));
    for (int i = 0; i < nblignes; i++)
    {
        Grille[i] = (char *)malloc(nbColonnes*sizeof(char));
    }
   
    static int joueur = 1 ;
    coordonees coord ;
    char joueur1 = 'X';
    char joueur2 = 'O';
    int res;
    initGrille(Grille,nblignes,nbColonnes);

    while (1)
    {

        printf("Joueur %d :\n",joueur);
        display(Grille,nblignes,nbColonnes);

        do
        {
            do
            {
                printf("Ligne : ");
                res = scanf("%d", &coord.ligne);
                if(res != 1){
                    printf("Merci de ne pas mettre de lettre !\n");
                    while(getchar() != '\n');
                }
            } while (res != 1);
            
            do
            {
                printf("Colonne : ");
                res = scanf("%d", &coord.colonne);
                if(res != 1){
                    printf("Merci de ne pas mettre de lettre !\n");
                    while(getchar() != '\n');
            }
            } while (res != 1);
            
            
        } while (checkCoordonees(Grille, coord,nblignes,nbColonnes) != 1);

        setValue(Grille,coord, joueur == 1 ? joueur1 : joueur2);
            

        if(endGame(Grille,nblignes,nbColonnes) == 1){
            printf("-------------------------------\n");
            printf("Victoire du Joueur %d!\n",joueur);
            display(Grille,nblignes,nbColonnes);
            break;
        }else if(endGame(Grille,nblignes,nbColonnes) == -1)
        {
            printf("-------------------------------\n");
            printf("Match null\n");
            display(Grille,nblignes,nbColonnes);
            break;
        }

        // Passer au joueur suivant
        joueur = (joueur == 1) ? 2 : 1;
        printf("\n");
    }

    // Liberer la memoire
    for (int i = 0; i < nblignes; i++) {
        free(Grille[i]);
    }
    free(Grille);

    return 0;
}

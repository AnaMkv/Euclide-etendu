#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    while (1) {
        printf("Saisissez vos deux nombres pour calculer le PGCD (ou 'exit' pour quitter) : ");
        int a, b;
        char cmd[100];
        fgets(cmd, sizeof(cmd) / sizeof(char), stdin);
        if (strncmp(cmd, "exit", 4) == 0)
            return 0;
        if (sscanf(cmd, "%d %d", &a, &b) != 2) {
            printf("Entrée invalide. Veuillez entrer deux nombres.\n");
            continue;
        }
        printf("Voulez-vous afficher les étapes de l'algorithme ? (Oui/Non) : ");
        char reponse[4];
        fgets(reponse, sizeof(reponse) / sizeof(char), stdin);
        for (int i = 0; i < strlen(reponse); ++i)
            reponse[i] = (char)tolower(reponse[i]);
        int affichage = strncmp(reponse, "oui", 3) == 0;
        int x1 = 1, y1 = 0, x2 = 0, y2 = 1;
        if (affichage)
            printf("Ligne    x    y   ax+by   quotient\n");
        int ligne = 1;
        if (affichage) {
            printf("L%d   %4d %4d    %4d\n", ligne++, x1, y1, a);
            printf("L%d   %4d %4d    %4d    %4d\n", ligne++, x2, y2, b, a / b);
        }
        int abkp = a, bbkp = b;
        int x[100], y[100], tabaxby[100], quot[100], ind = 0;
        while (b != 0) {
            int quotient = a / b;
            quot[ind] = quotient;
            int reste = a % b;
            int tmpx = x1 - quotient * x2;
            int tmpy = y1 - quotient * y2;
            x1 = x2;
            y1 = y2;
            x2 = tmpx;
            y2 = tmpy;
            x[ind] = x2;
            y[ind] = y2;
            a = b;
            b = reste;
            int axby = abkp * x2 + bbkp * y2;
            tabaxby[ind++] = axby;
        }
        if (affichage) {
            for(int i = 0; i < ind; ++i) {
                if(tabaxby[i] != 0)
                    printf("L%d   %4d %4d    %4d    %4d\n", ligne++, x[i], y[i], tabaxby[i], quot[i+1]);
                else
                    printf("L%d                %4d\n", ligne++, tabaxby[i]);
            }
        }
        printf("Le PGCD de %d et %d est %d.\n", abkp, bbkp, a);
        printf("%d*%d + %d*%d = %d\n", x1, abkp, y1, bbkp, a);
        printf("\n");
        fflush(stdin);
    }
}
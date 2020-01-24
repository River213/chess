#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "szachy.c"

int main()
{
    pole plansza[8][8];
    char kom1[10], kom2[10];
    pozycja poz1, poz2;
    czyjaTura tura;

    char *blad;

    restart:
    
    tura = bialy;

    uzupelnijPlansze(plansza);

    system("clear");
    system("clear");
    
    while(1){

        rysujPlansze(plansza);
        if(tura == bialy){
            printf("Ruch bialego: ");
        }
        else if(tura == czarny){
            printf("Ruch czarnego: ");
        }


        scanf("%s", kom1);

        if(strcmp(kom1, "EXIT")    == 0)    return 0;
        if(strcmp(kom1, "RESTART") == 0)    goto restart;

        scanf("%s", kom2);

        if(strcmp(kom2, "EXIT")    == 0)    return 0;
        if(strcmp(kom2, "RESTART") == 0)    goto restart;

        poz1.x = kom1[0] - 'A';
        poz1.y = kom1[1] - '0' -1;
        poz2.x = kom2[0] - 'A';
        poz2.y = kom2[1] - '0' -1;


        system("clear");
        system("clear");

        blad = sprawdzRuch(plansza, poz1, poz2, tura);
        if(blad == 0){
            if(tura == t_bialy) tura = t_czarny;
            else                tura = t_bialy;

            zmienPozycje(plansza, poz1, poz2);
        }else{
            printf( kolorCzerwony "Error - %s %s %s\n" kolorBialy , blad, kom1, kom2);
        }
    }


    return 0;
}

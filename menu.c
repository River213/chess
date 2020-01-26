#include "menu.h"

int menu(){
    char kom  = '0';
    
    while(kom != '3'){
        system("clear");
        system("clear");
                                                 

        printf("  ____    _____     _       ____   _   _  __   __\n");
        printf(" / ___|  |__  /    / \\     / ___| | | | | \\ \\ / /\n");
        printf(" \\___ \\    / /    / _ \\   | |     | |_| |  \\ V / \n");
        printf("  ___) |  / /_   / ___ \\  | |___  |  _  |   | |  \n");
        printf(" |____/  /____| /_/   \\_\\  \\____| |_| |_|   |_|  \n\n\n");
        printf("1.                   Graj          \n");
        printf("2.                 Jak Grac        \n");
        printf("3.                   Wyjdz         \n");
        printf("numer opcji - ");
        scanf("%c", &kom);
        if(kom == '1'){

            if(gra() == 1) return 0;

            system("clear");
            system("clear");

        }else if(kom == '2'){

            jakGrac();
            
        }
    }
    return 0;
}

void jakGrac(){

    system("clear");
    system("clear");                                          

    printf("  ____    _____     _       ____   _   _  __   __\n");
    printf(" / ___|  |__  /    / \\     / ___| | | | | \\ \\ / /\n");
    printf(" \\___ \\    / /    / _ \\   | |     | |_| |  \\ V / \n");
    printf("  ___) |  / /_   / ___ \\  | |___  |  _  |   | |  \n");
    printf(" |____/  /____| /_/   \\_\\  \\____| |_| |_|   |_|  \n\n\n");

    printf(" Aby poruszyc pionkiem trzeba wpisac jego pozycje oraz pozycje na ktora ma sie ruszyc np. \"D7 D5\"\n");
    printf(" Dodatkowe komendy:         \n");
    printf(" -\"RESTART\" resetuje gre  \n");
    printf(" -\"MENU\" wraca do menu    \n");
    printf(" -\"EXIT\" wylacza gre      \n");
    printf("\n");
    printf("Kliknij dowolny klawisz zaby wrocic do menu");
    getchar();
    getchar();

}

int gra(){

    pole plansza[8][8];
    char kom1[10] = "", kom2[10] = "";
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

        if(strcmp(kom1, "EXIT")    == 0)    return 1;
        if(strcmp(kom1, "RESTART") == 0)    goto restart;
        if(strcmp(kom1, "MENU") == 0)       return 0;

        scanf("%s", kom2);

        if(strcmp(kom2, "EXIT")    == 0)    return 1;
        if(strcmp(kom2, "RESTART") == 0)    goto restart;
        if(strcmp(kom2, "MENU") == 0)       return 0;

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
            printf( kolorCzerwony "%s %s %s\n" kolorBialy , blad, kom1, kom2);
        }
    }

    return 0;
}


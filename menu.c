#include "menu.h"

int menu(){
    char kom  = '0';
    
    while(kom != '3'){

        clear();      

        printf("  ____    _____     _       ____   _   _  __   __\n");
        printf(" / ___|  |__  /    / \\     / ___| | | | | \\ \\ / /\n");
        printf(" \\___ \\    / /    / _ \\   | |     | |_| |  \\ V / \n");
        printf("  ___) |  / /_   / ___ \\  | |___  |  _  |   | |  \n");
        printf(" |____/  /____| /_/   \\_\\  \\____| |_| |_|   |_|  \n\n\n");
        printf("1.                   Graj          \n");
        printf("2.                 Jak Grac        \n");
        printf("3.                   Wyjdz         \n");
        printf("numer opcji -");
        printf(" ");
        scanf("%c", &kom);

        if(kom == '1'){

            if(gra() == 1) return 0;

        }else if(kom == '2'){

            jakGrac();
            
        }
    }
    return 0;
}

void jakGrac(){

    clear();                                    

    printf("  ____    _____     _       ____   _   _  __   __\n");
    printf(" / ___|  |__  /    / \\     / ___| | | | | \\ \\ / /\n");
    printf(" \\___ \\    / /    / _ \\   | |     | |_| |  \\ V / \n");
    printf("  ___) |  / /_   / ___ \\  | |___  |  _  |   | |  \n");
    printf(" |____/  /____| /_/   \\_\\  \\____| |_| |_|   |_|  \n\n\n");

    printf(" Aby poruszyc pionkiem trzeba wpisac jego pozycje oraz pozycje na ktora ma sie ruszyc np. \"d7 d5\"\n");
    printf(" Dodatkowe komendy:         \n");
    printf(" -\"restart\" resetuje gre  \n");
    printf(" -\"menu\" wraca do menu    \n");
    printf(" -\"exit\" wylacza gre      \n");
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

    clear();
    
    while(1){

        if(sprawdzMat(plansza, tura) != 0){
            printf( kolorCzerwony "SZACH MAT - ");
            if(tura == t_bialy) printf("gracz czarny wygrywa!\n" kolorBialy);
            else                printf("gracz bialy wygrywa!\n"  kolorBialy);
            rysujPlansze(plansza);
            printf("kliknij dowolny klawisz aby przejsc do menu");
            getchar();
            getchar();
            return 0;
        }

        rysujPlansze(plansza);
        if(tura == t_bialy){
            printf("Ruch bialego: ");
        }
        else if(tura == t_czarny){
            printf("Ruch czarnego: ");
        }

        


        scanf("%s", kom1);

        if(strcmp(kom1, "exit")    == 0)    return 1;
        if(strcmp(kom1, "restart") == 0)    goto restart;
        if(strcmp(kom1, "menu") == 0)       return 0;

        scanf("%s", kom2);

        if(strcmp(kom2, "exit")    == 0)    return 1;
        if(strcmp(kom2, "restart") == 0)    goto restart;
        if(strcmp(kom2, "menu") == 0)       return 0;

        poz1.x = kom1[0] - 'a';
        poz1.y = kom1[1] - '0' -1;
        poz2.x = kom2[0] - 'a';
        poz2.y = kom2[1] - '0' -1;


        clear();

        blad = sprawdzRuch(plansza, poz1, poz2, tura);
        if(blad == 0){
            if(tura == t_bialy) tura = t_czarny;
            else                tura = t_bialy;

            zmienPozycje(plansza, poz1, poz2);
        }else{
            printf( kolorCzerwony "%s \"%s %s\"\n" kolorBialy , blad, kom1, kom2);
        }

    }

    return 0;
}


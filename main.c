#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define kolorBialy      "\033[0m"
#define kolorCzarnego   "\033[40m"
#define kolorBialego    "\033[47m\033[30m"
#define kolorCzerwony   "\033[31m"

typedef enum{
    t_bialy, t_czarny
}czyjaTura;

typedef enum{
    bialy,  ///na polu jest bialy pionek
    czarny, ///czarny
    puste   ///pole jest puste
}typPola;

typedef enum{
    pion, skoczek, goniec, wieza, hetman, krol
}typPionka;

typedef struct Pole{
    typPola typ;
    typPionka pionek;
}pole;

char zwrocCharPola(pole pol){
    if(pol.typ == puste) return ' ';

    switch(pol.pionek){
    case pion:      return 'i';
    case skoczek:   return 's';
    case wieza:     return 'w';
    case goniec:    return 'g';
    case hetman:    return 'h';
    case krol:      return 'k';
    }
}

void uzupelnijPlansze(pole plansza[8][8]){
    for(int x=0; x<8; x++){
            plansza[x][0].typ = czarny;
            plansza[x][1].typ = czarny;
            plansza[x][1].pionek = pion;
            plansza[x][6].typ = bialy;
            plansza[x][7].typ = bialy;
            plansza[x][6].pionek = pion;
    }

    plansza[0][0].pionek = wieza;
    plansza[1][0].pionek = skoczek;
    plansza[2][0].pionek = goniec;
    plansza[3][0].pionek = hetman;
    plansza[4][0].pionek = krol;
    plansza[5][0].pionek = goniec;
    plansza[6][0].pionek = skoczek;
    plansza[7][0].pionek = wieza;

    plansza[0][7].pionek = wieza;
    plansza[1][7].pionek = skoczek;
    plansza[2][7].pionek = goniec;
    plansza[3][7].pionek = hetman;
    plansza[4][7].pionek = krol;
    plansza[5][7].pionek = goniec;
    plansza[6][7].pionek = skoczek;
    plansza[7][7].pionek = wieza;

    for(int y=2; y<6; y++){
        for(int x=0; x<8; x++){
            plansza[x][y].typ = puste;
        }
    }
}

void rysujPlansze(pole plansza[8][8]){

    printf("+----------------------------------------------+\n");
    printf("|     A    B    C    D    E    F    G    H     |\n");
    printf("|   ----------------------------------------   |\n");
    for(int y=0; y<8; y++){
        printf("| %i ", y+1);
        for(int x=0; x<8; x++){
            if(plansza[x][y].typ == czarny){
                printf("|" kolorCzarnego  " %c " kolorBialy "|", zwrocCharPola(plansza[x][y]));
            }else if(plansza[x][y].typ == bialy){
                printf("|" kolorBialego " %c " kolorBialy "|", zwrocCharPola(plansza[x][y]));
            }else{
                printf("|   |");
            }

        }
        printf(" %i |\n", y+1);
        printf("|   ----------------------------------------   |");
        printf("\n");
    }
    printf("|     A    B    C    D    E    F    G    H     |\n");
    printf("+----------------------------------------------+\n");
}

int zmienPozycje(pole plansza[8][8], char poz1[2], char poz2[2]){
    int x1, x2, y1, y2;
    x1 = poz1[0] -'A';
    y1 = poz1[1] - '0' -1;
    x2 = poz2[0] -'A';
    y2 = poz2[1] - '0' -1;

    plansza[x2][y2] = plansza[x1][y1];
    plansza[x1][y1].typ = puste;

    return 0;
}

char *sprawdzRuch(pole plansza[8][8], char poz1[2], char poz2[2], czyjaTura tura){
    int x1, x2, y1, y2;
    x1 = poz1[0] -'A';
    y1 = poz1[1] - '0' -1;
    x2 = poz2[0] -'A';
    y2 = poz2[1] - '0' -1;

    /*for(int y=0; y<8; y++){
        for(int x=0; x<8; x++){
            if(plansza[x][y].typ == czarny)
        }
    }*/

    printf("pozycje - x1-%i y1-%i | x2-%i y2-%i\n", x1, y1, x2, y2);

    pole pole1 = plansza[x1][y1];
    pole pole2 = plansza[x2][y2];

    if(x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7 || y2 < 0 || x2 > 7 || y2 < 0 || y2 > 7)
        return "blad wprowadzenia";
    if(  !((pole1.typ == bialy && tura == t_bialy) || (pole1.typ == czarny && tura == t_czarny))  )
        return "zle wybrany pionek";
    if(pole1.typ == pole2.typ)
        return "cel ustawiony na wlany pionek";

    switch(pole1.pionek){
    case(pion):
        if((!( x1 == x2 && pole2.typ == puste && (
        (((y2 == y1+1) || (y1 == 1 && y2 == 3 && plansza[x1][2].typ == puste && plansza[x1][3].typ == puste)) && tura == t_czarny) ||
        (((y2 == y1-1) || (y1 == 6 && y2 == 4 && plansza[x1][5].typ == puste && plansza[x1][4].typ == puste)) && tura == t_bialy)) ))
        &&
        (! ((y2 == y1-1 && (x2 == x1+1 || x2 == x1-1) && pole2.typ == czarny && tura == t_bialy) ||
            (y2 == y1+1 && (x2 == x1+1 || x2 == x1-1) && pole2.typ == bialy  && tura == t_czarny))))
            return "zly ruch pionem";
        break;
    case(wieza):
        if(y1 == y2){
            if(x2 > x1)
                for(int i = x2-1; i > x1; i--){
                    if(plansza[i][y1].typ != puste) return "zly ruch wieza (po drodze jest pion)";
                }
            else
                for(int i = x2+1; i < x1; i++){
                    if(plansza[i][y1].typ != puste) return "zly ruch wieza (po drodze jest pion)";
                }
        }else if(x1 == x2){
            if(y2 > y1)
                for(int i = y2-1; i > y1; i--){
                    if(plansza[x1][i].typ != puste) return "zly ruch wieza (po drodze jest pion)";
                }
            else
                for(int i = y2+1; i < y1; i++){
                    if(plansza[x1][i].typ != puste) return "zly ruch wieza (po drodze jest pion)";
                }
        }else{
            return "zly ruch wieza (wieza sie tak nie porusza)";

        }
        break;
    case(skoczek):
        if(! (((y2 == y1+2 || y2 == y1-2) && (x2 == x1-1 || x2 == x1+1)) ||
              ((x2 == x1+2 || x2 == x1-2) && (y2 == y1-1 || y2 == y1+1))) )
           return "zly ruch skoczkiem";
        break;
    case(goniec):
        if(abs(y1 - y2) != abs(x1 - x2))
            return "zly ruch goncem";
        if(x1>x2 && y1>y2)
            for(int i=1; i<(y1-y2); i++){
                if(plansza[x1 - i][y1 - i].typ != puste)
                    return "zly ruch goncem er-1";
            }
        else if(x1<x2 && y1>y2)
            for(int i=1; i<(y1-y2); i++){
                if(plansza[x1 + i][y1 - i].typ != puste)
                    return "zly ruch goncem er-2";
            }
        else if(x1>x2 && y1<y2)
            for(int i=1; i<(y2-y1); i++){
                if(plansza[x1 - i][y1 + i].typ != puste)
                    return "zly ruch goncem er-3";
            }
        else
            for(int i=1; i<(y2-y1); i++){
                if(plansza[x1 + i][y1 + i].typ != puste)
                    return "zly ruch goncem er-4";
            }

        break;
    case(hetman):
        if(abs(y1 - y2) == abs(x1 - x2)){
            if(x1>x2 && y1>y2)
                for(int i=1; i<(y1-y2); i++){
                    if(plansza[x1 - i][y1 - i].typ != puste)
                        return "zly ruch hetmanem er-1";
                }
            else if(x1<x2 && y1>y2)
                for(int i=1; i<(y1-y2); i++){
                    if(plansza[x1 + i][y1 - i].typ != puste)
                        return "zly ruch hetmanem er-2";
                }
            else if(x1>x2 && y1<y2)
                for(int i=1; i<(y2-y1); i++){
                    if(plansza[x1 - i][y1 + i].typ != puste)
                        return "zly ruch hetmanem er-3";
                }
            else
                for(int i=1; i<(y2-y1); i++){
                    if(plansza[x1 + i][y1 + i].typ != puste)
                        return "zly ruch hetmanem er-4";
                }
        }else if(y1 == y2){
            if(x2 > x1)
                for(int i = x2-1; i > x1; i--){
                    if(plansza[i][y1].typ != puste) return "zly ruch hetmanem";
                }
            else
                for(int i = x2+1; i < x1; i++){
                    if(plansza[i][y1].typ != puste) return "zly ruch wieza hetmanem)";
                }
        }else if(x1 == x2){
            if(y2 > y1)
                for(int i = y2-1; i > y1; i--){
                    if(plansza[x1][i].typ != puste) return "zly ruch wieza hetmanem";
                }
            else
                for(int i = y2+1; i < y1; i++){
                    if(plansza[x1][i].typ != puste) return "zly ruch wieza hetmanem";
                }
        }else
            return "hetamn sie tak nie porusza";
        break;
    case(krol):
        if(!(abs(x1 - x2) <= 1 && abs(y1 -y2) <= 1))
            return "zly ruch krolem";
        break;
    }

    return 0;
}

char *sprawdzMat(pole plansza[8][8], int x, int y, czyjaTura tura){
    
    if(tura == t_bialy){
        

    }else{

    }
}


int main()
{
    pole plansza[8][8];
    char poz1[10], poz2[3];
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


        scanf("%s", poz1);

        if(strcmp(poz1, "exit")    == 0)    return 0;
        if(strcmp(poz1, "restart") == 0)    goto restart;

        scanf("%s", poz2);

        system("clear");
        system("clear");

        blad = sprawdzRuch(plansza, poz1, poz2, tura);
        if(blad == 0){
            if(tura == t_bialy) tura = t_czarny;
            else                tura = t_bialy;

            zmienPozycje(plansza, poz1, poz2);
        }else{
            printf( kolorCzerwony "Error - %s %s %s\n" kolorBialy , blad, poz1, poz2);
        }
    }


    return 0;
}

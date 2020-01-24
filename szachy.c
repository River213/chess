#include "szachy.h"

char zwrocCharPola(pole pol){
    if(pol.typ == puste) return ' ';

    switch(pol.pionek){
    case pion:      return 'i';
    case skoczek:   return 's';
    case wieza:     return 'w';
    case goniec:    return 'g';
    case hetman:    return 'H';
    case krol:      return 'K';
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

int zmienPozycje(pole plansza[8][8], pozycja poz1, pozycja poz2){

    plansza[poz2.x][poz2.y] = plansza[poz1.x][poz1.y];
    plansza[poz1.x][poz1.y].typ = puste;

    return 0;
}

char *sprawdzRuch(pole plansza[8][8], pozycja poz1, pozycja poz2, czyjaTura tura){

    if(sprawdzSzach(plansza, poz1, poz2, tura) != 0)
        return "jest szach";
    
    if(sprawdzBicie(plansza,  poz1, poz2, tura) != 0)
        return "jest bicie";
    
    return 0;
}

char *sprawdzBicie(pole plansza[8][8], pozycja poz1, pozycja poz2, czyjaTura tura){

    //printf("pozycje - poz1.x-%i poz1.y-%i | poz2.x-%i poz2.y-%i\n", poz1.x, poz1.y, poz2.x, poz2.y);

    pole pole1 = plansza[poz1.x][poz1.y];
    pole pole2 = plansza[poz2.x][poz2.y];

    if(poz1.x < 0 || poz1.x > 7 || poz1.y < 0 || poz1.y > 7 || poz2.y < 0 || poz2.x > 7 || poz2.y < 0 || poz2.y > 7)
        return "blad wprowadzenia";
    if(  !((pole1.typ == bialy && tura == t_bialy) || (pole1.typ == czarny && tura == t_czarny))  )
        return "zle wybrany pionek";
    if(pole1.typ == pole2.typ)
        return "cel ustawiony na wlany pionek";

    switch(pole1.pionek){
    case(pion):
        if((!( poz1.x == poz2.x && pole2.typ == puste && (
        (((poz2.y == poz1.y+1) || (poz1.y == 1 && poz2.y == 3 && plansza[poz1.x][2].typ == puste && plansza[poz1.x][3].typ == puste)) && tura == t_czarny) ||
        (((poz2.y == poz1.y-1) || (poz1.y == 6 && poz2.y == 4 && plansza[poz1.x][5].typ == puste && plansza[poz1.x][4].typ == puste)) && tura == t_bialy)) ))
        &&
        (! ((poz2.y == poz1.y-1 && (poz2.x == poz1.x+1 || poz2.x == poz1.x-1) && pole2.typ == czarny && tura == t_bialy) ||
            (poz2.y == poz1.y+1 && (poz2.x == poz1.x+1 || poz2.x == poz1.x-1) && pole2.typ == bialy  && tura == t_czarny))))
            return "zly ruch pionem";
        break;
    case(wieza):
        if(poz1.y == poz2.y){
            if(poz2.x > poz1.x)
                for(int i = poz2.x-1; i > poz1.x; i--){
                    if(plansza[i][poz1.y].typ != puste) return "zly ruch wieza (po drodze jest pion)";
                }
            else
                for(int i = poz2.x+1; i < poz1.x; i++){
                    if(plansza[i][poz1.y].typ != puste) return "zly ruch wieza (po drodze jest pion)";
                }
        }else if(poz1.x == poz2.x){
            if(poz2.y > poz1.y)
                for(int i = poz2.y-1; i > poz1.y; i--){
                    if(plansza[poz1.x][i].typ != puste) return "zly ruch wieza (po drodze jest pion)";
                }
            else
                for(int i = poz2.y+1; i < poz1.y; i++){
                    if(plansza[poz1.x][i].typ != puste) return "zly ruch wieza (po drodze jest pion)";
                }
        }else{
            return "zly ruch wieza (wieza sie tak nie porusza)";

        }
        break;
    case(skoczek):
        if(! (((poz2.y == poz1.y+2 || poz2.y == poz1.y-2) && (poz2.x == poz1.x-1 || poz2.x == poz1.x+1)) ||
              ((poz2.x == poz1.x+2 || poz2.x == poz1.x-2) && (poz2.y == poz1.y-1 || poz2.y == poz1.y+1))) )
           return "zly ruch skoczkiem";
        break;
    case(goniec):
        if(abs(poz1.y - poz2.y) != abs(poz1.x - poz2.x))
            return "zly ruch goncem";
        if(poz1.x>poz2.x && poz1.y>poz2.y)
            for(int i=1; i<(poz1.y-poz2.y); i++){
                if(plansza[poz1.x - i][poz1.y - i].typ != puste)
                    return "zly ruch goncem er-1";
            }
        else if(poz1.x<poz2.x && poz1.y>poz2.y)
            for(int i=1; i<(poz1.y-poz2.y); i++){
                if(plansza[poz1.x + i][poz1.y - i].typ != puste)
                    return "zly ruch goncem er-2";
            }
        else if(poz1.x>poz2.x && poz1.y<poz2.y)
            for(int i=1; i<(poz2.y-poz1.y); i++){
                if(plansza[poz1.x - i][poz1.y + i].typ != puste)
                    return "zly ruch goncem er-3";
            }
        else
            for(int i=1; i<(poz2.y-poz1.y); i++){
                if(plansza[poz1.x + i][poz1.y + i].typ != puste)
                    return "zly ruch goncem er-4";
            }

        break;
    case(hetman):
        if(abs(poz1.y - poz2.y) == abs(poz1.x - poz2.x)){
            if(poz1.x>poz2.x && poz1.y>poz2.y)
                for(int i=1; i<(poz1.y-poz2.y); i++){
                    if(plansza[poz1.x - i][poz1.y - i].typ != puste)
                        return "zly ruch hetmanem er-1";
                }
            else if(poz1.x<poz2.x && poz1.y>poz2.y)
                for(int i=1; i<(poz1.y-poz2.y); i++){
                    if(plansza[poz1.x + i][poz1.y - i].typ != puste)
                        return "zly ruch hetmanem er-2";
                }
            else if(poz1.x>poz2.x && poz1.y<poz2.y)
                for(int i=1; i<(poz2.y-poz1.y); i++){
                    if(plansza[poz1.x - i][poz1.y + i].typ != puste)
                        return "zly ruch hetmanem er-3";
                }
            else
                for(int i=1; i<(poz2.y-poz1.y); i++){
                    if(plansza[poz1.x + i][poz1.y + i].typ != puste)
                        return "zly ruch hetmanem er-4";
                }
        }else if(poz1.y == poz2.y){
            if(poz2.x > poz1.x)
                for(int i = poz2.x-1; i > poz1.x; i--){
                    if(plansza[i][poz1.y].typ != puste) return "zly ruch hetmanem";
                }
            else
                for(int i = poz2.x+1; i < poz1.x; i++){
                    if(plansza[i][poz1.y].typ != puste) return "zly ruch wieza hetmanem)";
                }
        }else if(poz1.x == poz2.x){
            if(poz2.y > poz1.y)
                for(int i = poz2.y-1; i > poz1.y; i--){
                    if(plansza[poz1.x][i].typ != puste) return "zly ruch wieza hetmanem";
                }
            else
                for(int i = poz2.y+1; i < poz1.y; i++){
                    if(plansza[poz1.x][i].typ != puste) return "zly ruch wieza hetmanem";
                }
        }else
            return "hetamn sie tak nie porusza";
        break;
    case(krol):
        if(!(abs(poz1.x - poz2.x) <= 1 && abs(poz1.y -poz2.y) <= 1))
            return "zly ruch krolem";
        break;
    }

    return 0;
}

char *sprawdzSzach(pole plansza[8][8], pozycja poz1, pozycja poz2, czyjaTura tura){

    pole pol1_zap = plansza[poz1.x][poz1.y];
    pole pol2_zap = plansza[poz2.x][poz2.y];

    plansza[poz2.x][poz2.y] = plansza[poz1.x][poz1.y];
    plansza[poz1.x][poz1.y].typ = puste;

    pozycja poz_Krola;

    for(int y=0; y<8; y++){
        for(int x=0; x<8; x++){
            if(plansza[x][y].pionek == krol && ((plansza[x][y].typ == czarny && tura == t_czarny) || (plansza[x][y].typ == bialy && tura == t_bialy))){
                poz_Krola.x = x;
                poz_Krola.y = y;
                x = 8;
                y = 8;
            }

        }
    }

    pozycja poz_i;
        
    for(int y=0; y<8; y++){
        for(int x=0; x<8; x++){
            poz_i.x = x; 
            poz_i.y = y;

            if(plansza[x][y].typ == czarny && tura == t_bialy){
                
                if(sprawdzBicie(plansza, poz_i, poz_Krola, czarny) == 0){

                    plansza[poz1.x][poz1.y] = pol1_zap;
                    plansza[poz2.x][poz2.y] = pol2_zap;
                    return "nie mozasz sie ruszyc jest krol jest atakowany!";
                }

            }else if(plansza[x][y].typ == bialy && tura == t_czarny){

                if(sprawdzBicie(plansza, poz_i, poz_Krola, bialy) == 0){
                    
                    plansza[poz1.x][poz1.y] = pol1_zap;
                    plansza[poz2.x][poz2.y] = pol2_zap;
                    return "nie mozasz sie ruszyc jest krol jest atakowany!";
                }
            }
        }
    }
    plansza[poz1.x][poz1.y] = pol1_zap;
    plansza[poz2.x][poz2.y] = pol2_zap;

    return 0;
}

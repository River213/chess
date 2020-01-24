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

typedef struct Pozycja{
    int x;
    int y;
}pozycja;

char zwrocCharPola(pole pol);

void uzupelnijPlansze(pole plansza[8][8]);

void rysujPlansze(pole plansza[8][8]);

int zmienPozycje(pole plansza[8][8], pozycja poz1, pozycja poz2);

char *sprawdzRuch(pole plansza[8][8], pozycja poz1, pozycja poz2, czyjaTura tura);

char *sprawdzBicie(pole plansza[8][8], pozycja poz1, pozycja poz2, czyjaTura tura);

char *sprawdzSzach(pole plansza[8][8], pozycja poz1, pozycja poz2, czyjaTura tura);
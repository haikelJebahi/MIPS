#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//1024 octet = 8192 bits
//512octet = 4096 bits
//1ko = 8kbits
//0.5ko = 4kbits
//1ko = 8kbit
char memoire[16][512];

struct registres {
    char name[4];
    int r[16];
};
typedef struct registres Registre;

struct bancDeRegistres {
    Registre r[16];
};
typedef struct bancDeRegistres BancRegistres;


//INITIALISER UN BANC DE REGISTRE
BancRegistres * creerBanc()
{
    BancRegistres *br = NULL;
    br = (BancRegistres*) malloc(sizeof(BancRegistres));
    int i=0;

    while(i<16)
    {
        Registre * r = NULL;
        r = (Registre *) malloc(sizeof(Registre));
        r->name[0] = 'r';
        if(i>9)
        {
            r->name[1] = '1';
            r->name[2] = i-10 +48;
            r->name[3] = '\0';
        }
        else
        {
            r->name[1] = i + 48;
            r->name[2] = '\0';
        }
        br->r[i] = *r;
        i++;
    }
    printf("Création des registres !\n");
    return br;
}

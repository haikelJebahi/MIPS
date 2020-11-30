#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registre.c"

int nbLigne = 0;
int nbFonction = 0;

struct nosFonctions {
    char name[20];
    int ligne;
};
typedef struct nosFonctions Fonction;

struct tabFonctions {

    Fonction *fonc;

};
typedef struct tabFonctions TabFonc;


// howmuch = combien de ":" il y a
int howMuch(char *tab, char a) {
    int i = 0;
    int c = 0;
    while (tab[i] != '\0') {
        if (tab[i] == a) {
            c++;
        }
        i++;
    }
    return c;
}


TabFonc *defineFonction(char lines[nbLigne][20], char *tab) {
    TabFonc *tabRetour = NULL;
    tabRetour = (TabFonc *) malloc(sizeof(TabFonc));

    Fonction *f = NULL;
    f = (Fonction *) malloc(howMuch(tab, ':') * sizeof(Fonction));

    int nbFonction = 0;
    int i = 0;

    while (i != nbLigne) {
        if (howMuch(lines[i], ':') > 0) {
            char *pointer;
            pointer = strchr(lines[i], ':');
            *pointer = '\0';
            strcpy(f[nbFonction].name, lines[i]);
            f[nbFonction].ligne = i + 1;
            nbFonction++;
        }
        i++;
    }
    tabRetour->fonc = f;

    return tabRetour;
}


void lafonctionquisauve(char *str) {
    int i = 0;
    while (str[i]) {
        printf("%d\n", (int) str[i]);
        i++;
    }
}

int searchFonction(TabFonc *t, char *nom) {
    int i = 0;
    while (i != nbFonction) {
        if (strcmp(t->fonc[i].name, nom) == 0) {
            return t->fonc[i].ligne;
        }
        i++;
    }
    return 0;
}

//TRANSFORME L'OPCODE EN BINAIRE
int opcodeBinary(char *opcode) {
    if (strcmp(opcode, "add") == 0) {
        return 0101;
    } else if (strcmp(opcode, "addi") == 0) {
        return 0111;
    } else if (strcmp(opcode, "sub") == 0) {
        return 0110;
    } else if (strcmp(opcode, "mul") == 0) {
        return 1011;
    } else if (strcmp(opcode, "lw") == 0) {
        return 1001;
    } else if (strcmp(opcode, "sw") == 0) {
        return 1110;
    } else if (strcmp(opcode, "beq") == 0) {
        return 0010;
    } else if (strcmp(opcode, "bne") == 0) {
        return 1100;
    } else if (strcmp(opcode, "j") == 0) {
        return 1101;
    } else if (strcmp(opcode, "exit") == 0) {
        return 1111;
    } else {
        return 9;
    }
}

//OBTENIR CHAQUE ARGUMENT DANS UNE INSTRUCTIONS
void getArgument(char *ligne, int a, char *arg){
    int i = 0;
    int j = 0;

    while (ligne[i] != '\0')
    {
        if (a == -1)
        {
            arg[j-1] = '\0';
            break;
        }
        else if (ligne[i] == ' ') {
            a--;
        }
        else if (a == 0){
            arg[j] = ligne[i];
            j++;
        }
        i++;
    }
    arg[j] = '\0';
}

//RENVOIE L'INDICE DU REGISTRE
int registreAdresse(char *argRegistre)
{
  char a[1];
  char b[1];
  a[0]= argRegistre[1];
  b[0] = argRegistre[2];

  int sum;

  if(a[0] == '1')
  { 
     if(b[0] == '\0')
     {
       return 1;
     }
     else
     {
       sum= atoi(b);
       return 10+sum;
     }
  }
  else
  { 
    sum= atoi(a);
    return sum;
  }
  return -1;
}

//RENVOIE LE BINAIRE DE L'INDICE DU REGISTRE
void binaryRegistre(int indice,int *tab)
{
  int a=0;

  for (int i = 5; i >= 0; i--)
  {
    if ((indice >> a) & 1)
    {
      tab[i] =1;
    }
    else
    {
      tab[i] =0;
    }
    a++;
  }
}

//TRANSFORM UNE DECIMAL EN BINAIRE
int decimalRegistre(int * tabBinaire)
{
    int decimal = 0;
    int multiplier[6] = {32,16,8,4,2,1};
    for (int i = 5; i >= 0; i--){
        if (tabBinaire[i] == 1)
        {
            decimal = multiplier[i] + decimal;
        }
    }
    return decimal;
}

//fetch
void monSwitch(int opcode, char *memoire, BancRegistres* bancR,int ligne)
{
  char a[5];
  char b[5];
  char c[5];
  int i;
  int y;
  int x;
  int tab1[6];
  int tab2[6];
  
    switch (opcode)
    {
        case 0101: //add
            getArgument(memoire, 1, a);
            getArgument(memoire, 2, b);
            getArgument(memoire, 3, c);

            printf("a = %s\n", a);
            printf("b = %s\n", b);
            printf("c = %s\n", c);
            
            binaryRegistre(registreAdresse(b),tab1);
            binaryRegistre(registreAdresse(c),tab2);

            
            bancR->r[registreAdresse(a)].r[0] = 0;
            bancR->r[registreAdresse(a)].r[1] = 1;
            bancR->r[registreAdresse(a)].r[2] = 0;
            bancR->r[registreAdresse(a)].r[3] = 1;
          
            y=0;
            for(i=4;i<10;i++)
            {
              bancR->r[registreAdresse(a)].r[i] = tab1[y];
              y++;
            }
            x = 0;

            for(i=10;i<16;i++)
            {
              bancR->r[registreAdresse(a)].r[i] = tab2[x];
              x++;
            }
            printf("%s : ",bancR->r[registreAdresse(a)].name);
            for(i=0;i<16;i++)
            {
              printf("%d",bancR->r[registreAdresse(a)].r[i]);
              
            }
            printf("\n");
            break;
        case 0111: //addi
            getArgument(memoire, 1, a);
            getArgument(memoire, 2, b);
            getArgument(memoire, 3, c);

            printf("a = %s\n", a);
            printf("b = %s\n", b);
            printf("c = %s\n", c);
            
            binaryRegistre(registreAdresse(b),tab1);
            binaryRegistre(ligne,tab2);

            
            bancR->r[registreAdresse(a)].r[0] = 0;
            bancR->r[registreAdresse(a)].r[1] = 1;
            bancR->r[registreAdresse(a)].r[2] = 1;
            bancR->r[registreAdresse(a)].r[3] = 1;
          
            y=0;
            for(i=4;i<10;i++)
            {
              bancR->r[registreAdresse(a)].r[i] = tab1[y];
              y++;
            }
            x = 0;

            for(i=10;i<16;i++)
            {
              bancR->r[registreAdresse(a)].r[i] = tab2[x];
              x++;
            }
            printf("%s : ",bancR->r[registreAdresse(a)].name);
            for(i=0;i<16;i++)
            {
              printf("%d",bancR->r[registreAdresse(a)].r[i]);
              
            }
            printf("\n");
 
           break;
        case 0110: //sub
            getArgument(memoire, 1, a);
            getArgument(memoire, 2, b);
            getArgument(memoire, 3, c);

            printf("a = %s\n", a);
            printf("b = %s\n", b);
            printf("c = %s\n", c);
            
            binaryRegistre(registreAdresse(b),tab1);
            binaryRegistre(registreAdresse(c),tab2);

            
            bancR->r[registreAdresse(a)].r[0] = 0;
            bancR->r[registreAdresse(a)].r[1] = 1;
            bancR->r[registreAdresse(a)].r[2] = 1;
            bancR->r[registreAdresse(a)].r[3] = 0;
          
            y=0;
            for(i=4;i<10;i++)
            {
              bancR->r[registreAdresse(a)].r[i] = tab1[y];
              y++;
            }
            x = 0;

            for(i=10;i<16;i++)
            {
              bancR->r[registreAdresse(a)].r[i] = tab2[x];
              x++;
            }
            printf("%s : ",bancR->r[registreAdresse(a)].name);
            for(i=0;i<16;i++)
            {
              printf("%d",bancR->r[registreAdresse(a)].r[i]);
              
            }
            printf("\n");
            break;
        case 1011: //mul
            getArgument(memoire, 1, a);
            getArgument(memoire, 2, b);
            getArgument(memoire, 3, c);

            printf("a = %s\n", a);
            printf("b = %s\n", b);
            printf("c = %s\n", c);
            
            binaryRegistre(registreAdresse(b),tab1);
            binaryRegistre(registreAdresse(c),tab2);

            
            bancR->r[registreAdresse(a)].r[0] = 1;
            bancR->r[registreAdresse(a)].r[1] = 0;
            bancR->r[registreAdresse(a)].r[2] = 1;
            bancR->r[registreAdresse(a)].r[3] = 1;
          
            y=0;
            for(i=4;i<10;i++)
            {
              bancR->r[registreAdresse(a)].r[i] = tab1[y];
              y++;
            }
            x = 0;

            for(i=10;i<16;i++)
            {
              bancR->r[registreAdresse(a)].r[i] = tab2[x];
              x++;
            }
            printf("%s : ",bancR->r[registreAdresse(a)].name);
            for(i=0;i<16;i++)
            {
              printf("%d",bancR->r[registreAdresse(a)].r[i]);
              
            }
            printf("\n");
            break;
        case 1001:
            printf("lw");
            break;
        case 1110:
            printf("sw");
            break;
        case 0010: //beq
            getArgument(memoire, 1, a);
            getArgument(memoire, 2, b);
            getArgument(memoire, 3, c);

            printf("a = %s\n", a);
            printf("b = %s\n", b);
            printf("c = %s\n", c);
            
            binaryRegistre(registreAdresse(b),tab1);
            binaryRegistre(ligne,tab2);

            
            bancR->r[registreAdresse(a)].r[0] = 0;
            bancR->r[registreAdresse(a)].r[1] = 0;
            bancR->r[registreAdresse(a)].r[2] = 1;
            bancR->r[registreAdresse(a)].r[3] = 0;
          
            y=0;
            for(i=4;i<10;i++)
            {
              bancR->r[registreAdresse(a)].r[i] = tab1[y];
              y++;
            }
            x = 0;

            for(i=10;i<16;i++)
            {
              bancR->r[registreAdresse(a)].r[i] = tab2[x];
              x++;
            }
            printf("%s : ",bancR->r[registreAdresse(a)].name);
            for(i=0;i<16;i++)
            {
              printf("%d",bancR->r[registreAdresse(a)].r[i]);
              
            }
            printf("\n");
            break;
        case 1100: //bne
            getArgument(memoire, 1, a);
            getArgument(memoire, 2, b);
            getArgument(memoire, 3, c);

            printf("a = %s\n", a);
            printf("b = %s\n", b);
            printf("c = %s\n", c);
            
            binaryRegistre(registreAdresse(b),tab1);
            binaryRegistre(ligne,tab2);

            
            bancR->r[registreAdresse(a)].r[0] = 1;
            bancR->r[registreAdresse(a)].r[1] = 1;
            bancR->r[registreAdresse(a)].r[2] = 0;
            bancR->r[registreAdresse(a)].r[3] = 0;
          
            y=0;
            for(i=4;i<10;i++)
            {
              bancR->r[registreAdresse(a)].r[i] = tab1[y];
              y++;
            }
            x = 0;

            for(i=10;i<16;i++)
            {
              bancR->r[registreAdresse(a)].r[i] = tab2[x];
              x++;
            }
            printf("%s : ",bancR->r[registreAdresse(a)].name);
            for(i=0;i<16;i++)
            {
              printf("%d",bancR->r[registreAdresse(a)].r[i]);
              
            }
            printf("\n");
            break;
        case 1101: //j
           
            binaryRegistre(ligne,tab1);

            bancR->r[registreAdresse(a)].r[0] = 1;
            bancR->r[registreAdresse(a)].r[1] = 1;
            bancR->r[registreAdresse(a)].r[2] = 0;
            bancR->r[registreAdresse(a)].r[3] = 1;
          
            y=0;
            for(i=4;i<10;i++)
            {
              bancR->r[registreAdresse(a)].r[i] = tab2[y];
              y++;
            }
            x = 0;

            for(i=10;i<16;i++)
            {
              bancR->r[registreAdresse(a)].r[i] = 0;
              x++;
            }
            printf("%s : ",bancR->r[registreAdresse(a)].name);
            for(i=0;i<16;i++)
            {
              printf("%d",bancR->r[registreAdresse(a)].r[i]);
              
            }
            printf("\n");
            break;
        case 1111:
            for(i=0;i<16;i++)
            {
              bancR->r[15].r[i] = 1;
            }
            break;
        default: printf("Error OPCODE");
    }
}

int opcodeTrue(int *opcode,int a, int b, int c, int d)
{
    if(opcode[0] == a && opcode[1] == b  && opcode[2] == c  && opcode[3] == d)
    {
      return 1;
    }
    else
    {
      return 0;
    }
}

int main(int argc, char *argv[])
{
  //FETTTTCCHCHHCHHH
    FILE *fichier = NULL;
    BancRegistres * bancR = creerBanc();
    fichier = fopen(argv[1], "r+");
    if (fichier != NULL) {
        char a;
        char tab[4096];
        int i = 0;

        while (a != EOF) {
            a = fgetc(fichier);
            if (a > 0 && a < 127) {
                tab[i] = a;
                i++;
            }
        }
        tab[i] = '\0';

        fclose(fichier);

        const char *separators = "\n";

        nbLigne = howMuch(tab, 10);
        nbFonction = howMuch(tab, ':');

        char ligne[nbLigne][20];

        char *strToken = strtok(tab, separators);

        i = 0;

        while (strToken != NULL) {
            //printf ( "%s\n", strToken );
            strcpy(ligne[i], strToken);
            i++;
            // On demande le token suivant.
            strToken = strtok(NULL, separators);
        }

        TabFonc *m = defineFonction(ligne, tab);

        int ligneMain = searchFonction(m, "main");

        
        i=0;
        while (ligneMain < m->fonc[1].ligne - 1) 
        {
            int j = 0;
            char opcode[10];

            while (ligne[ligneMain][j] != '\0') {
                if (ligne[ligneMain][j] == ' ') {
                    break;
                }
                opcode[j] = ligne[ligneMain][j];
                j++;
            }
            printf("\n");

            opcode[j] = '\0';

            strcpy(memoire[i],ligne[ligneMain]);
            //DECODE
            printf("Instruction %d\n",ligneMain);
            monSwitch(opcodeBinary(opcode), memoire[i],bancR,ligneMain);
            printf("\n");
            i++;
            ligneMain = ligneMain + 1;
        }

        //EXECUTE
        i=0;
        int opcode[4];
        int tabBinaire1[6];
        int tabBinaire2[6];
        int boucle = 0;
        int registreTemp[16];

        for(i=0; i<16;i++)
        {
          int id;
           for(id=0;id<4;id++)
          { 
            opcode[id] = bancR->r[i].r[id];    
          }
          
          //addi
          if(opcodeTrue(opcode, 0, 1, 1,1) == 1)
          {
            int iTab = 0;
            for(boucle = 4;boucle<10;boucle++)
            {
              tabBinaire1[iTab] = bancR->r[i].r[boucle];
              iTab++;
            }

            iTab = 0;
            for(boucle = 10;boucle<16;boucle++)
            {
              tabBinaire2[iTab] = bancR->r[i].r[boucle];
              iTab++;
            }

            
            int arg1 = decimalRegistre(tabBinaire1);
            int arg2 = decimalRegistre(tabBinaire2)-1;


            char cara[5];
            getArgument(memoire[arg2], 3, cara);

            registreTemp[i]  = atoi(cara);
          }
          //add
          else if(opcodeTrue(opcode, 0, 1, 0,1) == 1)
          {
            int iTab = 0;
            for(boucle = 4;boucle<10;boucle++)
            {
              tabBinaire1[iTab] = bancR->r[i].r[boucle];
              iTab++;
            }     
 
            iTab = 0;
            for(boucle = 10;boucle<16;boucle++)
            {
              tabBinaire2[iTab] = bancR->r[i].r[boucle];
              iTab++;
            }

            
            int arg1 = decimalRegistre(tabBinaire1);
            int arg2 = decimalRegistre(tabBinaire2);

            char cara[5];

            registreTemp[i]  = registreTemp[arg1] + registreTemp[arg2];
            printf("Résultat instruction %d = %d\n",i, registreTemp[i]);
          } 
          //sub
        else if(opcodeTrue(opcode, 0, 1, 1,0) == 1)
        {
            int iTab = 0;
            for(boucle = 4;boucle<10;boucle++)
            {
              tabBinaire1[iTab] = bancR->r[i].r[boucle];
              iTab++;
            }     
            printf("\n");
            iTab = 0;
            for(boucle = 10;boucle<16;boucle++)
            {
              tabBinaire2[iTab] = bancR->r[i].r[boucle];
              iTab++;
            }
            printf("\n");
            
            int arg1 = decimalRegistre(tabBinaire1);
            int arg2 = decimalRegistre(tabBinaire2);

            char cara[5];

            registreTemp[i]  = registreTemp[arg1] - registreTemp[arg2];
            printf("Résultat instruction %d = %d\n",i, registreTemp[i]);
        }
        //mul
        else if(opcodeTrue(opcode, 1, 0, 1,1) == 1)
        {
            int iTab = 0;
            for(boucle = 4;boucle<10;boucle++)
            {
              tabBinaire1[iTab] = bancR->r[i].r[boucle];
              iTab++;
            }     
            printf("\n");
            iTab = 0;
            for(boucle = 10;boucle<16;boucle++)
            {
              tabBinaire2[iTab] = bancR->r[i].r[boucle];
              iTab++;
            }
            printf("\n");
            
            int arg1 = decimalRegistre(tabBinaire1);
            int arg2 = decimalRegistre(tabBinaire2);

            char cara[5];

            registreTemp[i]  = registreTemp[arg1] * registreTemp[arg2];
            printf("Résultat instruction %d = %d\n",i, registreTemp[i]);
        }
        else if(opcodeTrue(opcode, 1, 1, 1,1) == 1)
        { 
          printf("QUITTER\n");
        }
       

        }
        printf("\n");


    } else {
        printf("Error : file is empty");
    }
    return 0;
}



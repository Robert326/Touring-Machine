/* BOLFA ROBERT-ION - 314CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* definire lista dublu inlantuita cu santinela */

typedef struct celula2 {
    char info;
    struct celula2 *pre, *urm;
} TCelula2, *TLista2;

typedef struct celula_stiva {
    TLista2 info;
    struct celula_stiva *urm;
} TCelulaStiva, *TStiva;

typedef struct celula {  /// STRUCTURA CELULA PENTRU LISTA SIMPLA
    char *info;
    struct celula *urm;
} TCelula, *TLista;

typedef struct coada {  /// STRUCTURA COZII
    TLista inc, sf;
} TCoada;

typedef struct Banda {
    TLista2 deget, inceput;
} TCelulaBanda, *TBanda;

void DistrugeLista(TLista *aL);
void DistrugeQ(TCoada *c);
TLista2 AlocCelula2(char x);
TLista2 InitLista2();
void AfisareLista2(TLista2 L);
void DistrugeLista2(TLista2 *aL);
int ExtrageQ(TCoada *c, char *element);
int InsertQ(TCoada *c, char *x);
TCoada *InitQ();
void DistrugeS(TStiva *vf);
int Pop(TStiva *vf, TLista2 *element);
int Adauga_Element_Stiva(TStiva *vf, TLista2 pozitie);
TStiva InitS(void);
int InsertL2(TLista2 L, char x);
void SHOW(TBanda B, FILE *file_name);
TBanda InitB();
void MOVE_RIGHT(TBanda banda, TStiva *undo);
void MOVE_LEFT(TBanda banda, TStiva *undo);
int MOVE_RIGHT_CHAR(TBanda banda, char x);
int MOVE_LEFT_CHAR(TBanda banda, char x, FILE *filename);
void WRITE(TBanda banda, char x);
int INSERT_LEFT(TBanda banda, char x, FILE *filename);
void INSERT_RIGHT(TBanda banda, char x);
void SHOW_CURRENT(TBanda banda, FILE *file_name);
void UNDO(TBanda banda, TStiva *stiva_undo, TStiva *stiva_redo);
void REDO(TBanda banda, TStiva *stiva_undo, TStiva *stiva_redo);
void DistrugeB(TBanda banda);
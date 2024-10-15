/* BOLFA ROBERT-ION - 314CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functii.h"

/* Aloca un element de tip TCelula2 si returneaza pointerul aferent */
TLista2 AlocCelula2(char x) {
    TLista2 aux = (TLista2)malloc(sizeof(TCelula2));
    if (!aux) {
        return NULL;
    }

    aux->info = x;
    aux->pre = aux->urm = NULL;

    return aux;
}

/* Creeaza santinela pentru lista folosita */
TLista2 InitLista2() {
    TLista2 aux = (TLista2)malloc(sizeof(TCelula2));
    if (!aux) {
        return NULL;
    }

    aux->info = 0; /* informatia din santinela are valoarea 0 */
    aux->pre = NULL;
    aux->urm = NULL;

    return aux;
}

/* Distrugere lista */
void DistrugeLista2(TLista2 *aL) {
    TLista2 p = (*aL)->urm, aux;
    while (p != NULL) { /* distrugere elementele listei */
        aux = p;
        p = p->urm;
        free(aux);
    }

    free(*aL); /* distrugere santinela */
    *aL = NULL;
}

int InsertL2(TLista2 L, char x) {  /// INSERAREA IN LISTA DUBLU INLANTUITA
    TLista2 p = L->urm;
    TLista2 aux = NULL;
    aux = AlocCelula2(x);
    if (p == NULL) {
        p = L;
        p->urm = aux;
        aux->pre = p;
    } else

    {
        aux->urm = p;
        aux->pre = p->pre;
        p->pre->urm = aux;
        p->pre = aux;
    }
}

TStiva InitS(void) { return NULL; }  /// INITIALIZEZI STIVA CU ASTA

int Adauga_Element_Stiva(TStiva *vf,
                         TLista2 pozitie) {            /// ADAUGA ELEMENT IN STIVA
    TStiva aux = (TStiva)malloc(sizeof(TCelulaStiva)); /* 1 */
    if (!aux) return 0;
    aux->info = pozitie;
    if (vf == NULL)
        aux->urm = NULL;
    else
        aux->urm = *vf; /* 2 */
    *vf = aux;          /* 3 */
    return 1;
}

int Pop(TStiva *vf, TLista2 *element) {  /// SCOATE ELEMENT DIN STIVA
    TStiva aux;
    if (*vf == NULL) return 0;
    *element = (*vf)->info; /* 1 */
    aux = *vf;              /* 2 */
    *vf = aux->urm;         /* 3 */
    free(aux);              /* 4 */
    return 1;
}

void DistrugeS(TStiva *vf) {  /// DISTRUGE STIVA
    TStiva aux;
    while (*vf) {
        aux = *vf;
        *vf = (*vf)->urm;
        free(aux);
    }
}

TCoada *InitQ() {  /// INITIALIZAREA COZII
    TCoada *c;
    c = (TCoada *)malloc(sizeof(TCoada));
    c->inc = NULL;
    c->sf = NULL;
}
int InsertQ(TCoada *c, char *x) {                 /// INSERAREA ELEMENT IN COADA
    TLista aux = (TLista)malloc(sizeof(TCelula)); /* 1 */
    aux->info = malloc(87 * sizeof(char));
    if (!aux) return 0;
    if (c->inc == NULL) {
        strcpy(aux->info, x);
        aux->urm = NULL;
        c->inc = aux; /* 2 */
        c->sf = aux;  /* 3 */
    } else {
        strcpy(aux->info, x);
        aux->urm = NULL;
        c->sf->urm = aux; /* 2 */
        c->sf = aux;      /* 3 */
    }
    return 1;
}

int ExtrageQ(TCoada *c,
             char *element) {  /// FCT PT EXTRAGERE UN ELEMENT DIN COADA
    TLista aux;
    if (c->inc != c->sf) {
        aux = c->inc; /* 1 */
        strcpy(element, aux->info);
        c->inc = aux->urm; /* 2 */
        free(aux->info);
        free(aux); /* 3 */
    } else {
        aux = c->inc; /* 1 */
        strcpy(element, aux->info);
        free(aux->info);
        free(aux); /* 2 */
        c->inc = NULL;
        c->sf = NULL; /* 3a, 3b */
    }
}

void DistrugeQ(TCoada *c) {
    TLista p;
    p = c->inc;    /* 1 */
    c->inc = NULL; /* 2 */
    c->sf = NULL;
    DistrugeLista(&p);
    free(c);
}

/* Dezalocare memorie lista */
void DistrugeLista(TLista *aL) {  /// DISTRUGERE LISTA SIMPLA
    TLista aux;
    while (*aL) { /* *aL != NULL, dereferentiere adresa aL */
        aux = *aL;
        *aL = (*aL)->urm;
        free(aux->info);
        free(aux);
    }
}

TBanda InitB() {  /// FUNCTIA PT INITIALIZAREA BENZII CARE PUNE SI CARACTERUL #
    TBanda Banda;
    Banda = (TBanda)(malloc(sizeof(TCelulaBanda)));
    Banda->deget = InitLista2();
    Banda->inceput = Banda->deget;
    InsertL2(Banda->deget, '#');
    Banda->deget = Banda->deget->urm;
}

void SHOW(TBanda B, FILE *file_name) {  /// FUNCTIA PT AFISAREA BENZII
    TLista2 p = B->inceput->urm;
    while (p != NULL) { /* parcurgere lista */
        if (p == B->deget)
            fprintf(file_name, "|%c|", p->info);
        else
            fprintf(file_name, "%c", p->info);
        p = p->urm;
    }
    fprintf(file_name, "\n");
}

void MOVE_LEFT(TBanda banda, TStiva *undo) {
    if (banda->deget != banda->inceput->urm) {
        Adauga_Element_Stiva(undo, banda->deget);
        banda->deget = banda->deget->pre;
        /// ma misc o pozitie mai la stanga doar in cazul in care in partea stanga nu am santinela
    }
}

void MOVE_RIGHT(TBanda banda, TStiva *undo) {
    Adauga_Element_Stiva(undo, banda->deget);
    if (banda->deget->urm == NULL)  /// ma misc la dreapta o pozitie, iar daca in dreapta nu am celula inserez una si mut degetul
    {
        InsertL2(banda->deget, '#');
        banda->deget = banda->deget->urm;
    } else {
        banda->deget = banda->deget->urm;
    }
}

int MOVE_LEFT_CHAR(TBanda banda, char x, FILE *filename) {
    /// ma misc la stanga doar daca nu am santinela in stanga si daca nu am ajuns la caracter
    /// iar daca nu am ajuns la caracter tin minte adresa de inceput si ma misc cu degetul inapoi
    TLista2 adresa = banda->deget;
    while (banda->deget != banda->inceput->urm && banda->deget->info != x) {
        banda->deget = banda->deget->pre;
    }
    if (banda->deget->info != x) {
        fprintf(filename, "ERROR\n");
        while (banda->deget != adresa) {
            banda->deget = banda->deget->urm;
        }
        return 0;
    }
}

int MOVE_RIGHT_CHAR(TBanda banda, char x) {
    while (banda->deget->info != x && banda->deget->urm != NULL) {
        banda->deget = banda->deget->urm;
    }
    if (banda->deget->info != x) {
        InsertL2(banda->deget, '#');
        banda->deget = banda->deget->urm;
        return 0;
    }
}

void WRITE(TBanda banda, char x) {
    banda->deget->info = x;
}

int INSERT_LEFT(TBanda banda, char x, FILE *filename) {
    TLista2 aux = NULL;
    if (banda->deget != banda->inceput->urm)
        aux = AlocCelula2(x);  /// verific daca pot sa inserez in stanga ca sa nu aloc celula degeaba
    if (banda->deget == banda->inceput->urm) {
        fprintf(filename, "ERROR\n");
        return 0;
    } else {
        aux->urm = banda->deget;
        aux->pre = banda->deget->pre;
        banda->deget->pre->urm = aux;
        banda->deget->pre = aux;
        banda->deget = banda->deget->pre;
    }
}

void INSERT_RIGHT(TBanda banda, char x) {
    TLista2 aux = NULL;
    aux = AlocCelula2(x);
    if (banda->deget->urm == NULL) {
        banda->deget->urm = aux;
        aux->pre = banda->deget;
    } else {
        aux->urm = banda->deget->urm;
        aux->pre = banda->deget;
        banda->deget->urm->pre = aux;
        banda->deget->urm = aux;
    }
    banda->deget = banda->deget->urm;
}

void SHOW_CURRENT(TBanda banda, FILE *file_name) {
    fprintf(file_name, "%c", banda->deget->info);
    fprintf(file_name, "\n");
}

void UNDO(TBanda banda, TStiva *stiva_undo, TStiva *stiva_redo) {
    TLista2 ultima_pozitie;
    Adauga_Element_Stiva(stiva_redo, banda->deget);
    Pop(stiva_undo, &ultima_pozitie);
    banda->deget = ultima_pozitie;
}

void REDO(TBanda banda, TStiva *stiva_undo, TStiva *stiva_redo) {
    TLista2 ultima_pozitie;
    Adauga_Element_Stiva(stiva_undo, banda->deget);
    Pop(stiva_redo, &ultima_pozitie);
    banda->deget = ultima_pozitie;
}

void DistrugeB(TBanda banda) {
    DistrugeLista2(&banda->inceput);
    free(banda);
}
/* BOLFA ROBERT-ION - 314CB */

#include "functii.h"

int main() {
    TBanda b;
    TStiva stiva_undo, stiva_redo;
    char input_filename[] = "touring.in";
    char output_filename[] = "touring.out";
    FILE *in = fopen(input_filename, "rt");
    FILE *out = fopen(output_filename, "wt");
    stiva_undo = InitS();
    stiva_redo = InitS();
    char *s;
    s = malloc(69 * sizeof(char));
    char *c;
    c = malloc(69 * sizeof(char));
    int n = 0;
    unsigned i = 0;
    b = InitB();
    TCoada *coada;
    coada = InitQ();
    fscanf(in, "%d", &n);
    fgets(s, 69, in);
    /// citesc n-ul care reprezinta numarul de instructiuni care vor fi citite
    for (i = 0; i < n; i++) {
        fgets(s, 69, in);
        if (strcmp(s, "MOVE_RIGHT\n") == 0 || strcmp(s, "MOVE_LEFT\n") == 0 ||
            strstr(s, "MOVE_RIGHT_CHAR") != NULL || strstr(s, "MOVE_LEFT_CHAR") != NULL ||
            strstr(s, "INSERT_LEFT") != NULL || strstr(s, "INSERT_RIGHT") != NULL ||
            strstr(s, "WRITE") != NULL)
            /// in if-ul de mai sus verific daca sunt operatii de update ca sa le pun in coada
            InsertQ(coada, s);
        else {  /// in caz contrar iau instructiunea din coada si o execut
            /// iar mai jos verific ce instructiune este
            if (strcmp(s, "SHOW\n") == 0)
                SHOW(b, out);
            else if (strcmp(s, "SHOW_CURRENT\n") == 0)
                SHOW_CURRENT(b, out);
            else if (strcmp(s, "UNDO\n") == 0)
                UNDO(b, &stiva_undo, &stiva_redo);
            else if (strcmp(s, "REDO\n") == 0)
                REDO(b, &stiva_undo, &stiva_redo);
            else if (strcmp(s, "EXECUTE\n") == 0) {
                ExtrageQ(coada, c);
                if (strcmp(c, "MOVE_RIGHT\n") == 0)
                    MOVE_RIGHT(b, &stiva_undo);
                else if (strcmp(c, "MOVE_LEFT\n") == 0)
                    MOVE_LEFT(b, &stiva_undo);
                else if (strstr(c, "MOVE_LEFT_CHAR") != NULL)
                    MOVE_LEFT_CHAR(b, c[15], out);
                else if (strstr(c, "MOVE_RIGHT_CHAR") != NULL)
                    MOVE_RIGHT_CHAR(b, c[16]);
                else if (strstr(c, "INSERT_LEFT") != NULL)
                    INSERT_LEFT(b, c[12], out);
                else if (strstr(c, "INSERT_RIGHT") != NULL)
                    INSERT_RIGHT(b, c[13]);
                else if (strstr(c, "WRITE") != NULL)
                    WRITE(b, c[6]);
            }
        }
    }
    DistrugeQ(coada);
    DistrugeS(&stiva_redo);
    DistrugeS(&stiva_undo);
    DistrugeB(b);
    free(c);
    free(s);
    fclose(in);
    fclose(out);
}
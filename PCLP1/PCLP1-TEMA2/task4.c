#include "./utils.h"

void SolveTask4(void *info, int nr_avioane, int nr_obstacole, int *x, int *y, int N) {
    // TODO(student) : Stuff
    int const numar13 = 13;
    int nr = 0, ok = 0;
    for (int i = 0; i < nr_avioane; i++) {
        unsigned short l = *(unsigned short *)info;  //  linia
        unsigned short c = *(unsigned short *)(info + sizeof(unsigned short));  //  coloana
        unsigned char dir = *(unsigned char *)(info + 2 * sizeof(unsigned short));  //  directia
        unsigned char t = *(unsigned char *)(info + 2 * sizeof(unsigned short) + sizeof(unsigned char));  //  tipul
        ok = 0;  //  presupunem ca nu exista obstacol
        int* var1 = x;
        int* var2 = y;
        for (int j=0; j < nr_obstacole; j++) {
            int linieobs = *(int*)(var1);
            int coloanaobs = *(int*)(var2);
            if (t == '1') {
                if (dir == 'N') {
                    if ((linieobs <= l + 3 && coloanaobs <= c + 1 && coloanaobs >= c - 1) ||
                    (linieobs <= l + 1 && coloanaobs <= c + 2 && coloanaobs >= c - 2)) {
                        ok = 1;
                    }
                }
                if (dir == 'S') {
                    if ((linieobs >= l - 3 && coloanaobs <=c + 1 && coloanaobs >= c - 1) ||
                    (linieobs >= l - 1 && coloanaobs <= c + 2 && coloanaobs >= c - 2)) {
                        ok = 1;
                    }
                }
                if (dir == 'W') {
                    if ((linieobs >= l - 1 && linieobs <= l + 1 && coloanaobs <= c + 3) ||
                    (linieobs >= l - 2 && linieobs <= l + 2 && coloanaobs <= c+1)) {
                        ok = 1;
                    }
                }
                if (dir == 'E') {
                    if ((linieobs >= l - 1 && linieobs <= l + 1 && coloanaobs >= c - 3) ||
                    (linieobs >= l - 2 && linieobs <= l + 2 && coloanaobs >= c - 1)) {
                        ok = 1;
                    }
                }
            } else {
                if (dir == 'N') {
                    if ((linieobs <= l + 4 && coloanaobs >= c - 2 && coloanaobs <= c + 2) ||
                    (linieobs <= l + 2 && coloanaobs >= c - 3 && coloanaobs <= c + 3)) {
                        ok = 1;
                    }
                }
                if (dir == 'S') {
                    if ((linieobs >= l - 4 && coloanaobs >= c - 2 && coloanaobs <= c + 2) ||
                    (linieobs >= l - 2 && coloanaobs >= c - 3 && coloanaobs <= c + 3)) {
                        ok = 1;
                    }
                }
                if (dir == 'W') {
                    if ((linieobs >= l - 2 && linieobs <= l + 2 && coloanaobs <= c+4) ||
                    (linieobs >= l - 3 && linieobs <= l + 3 && coloanaobs <= c + 2)) {
                        ok = 1;
                    }
                }
                if (dir == 'E') {
                    if ((linieobs >= l - 2 && linieobs <= l + 2 && coloanaobs >= c - 4) ||
                    (linieobs >= l-3 && linieobs <= l +3  && coloanaobs >= c - 2)) {
                        ok = 1;
                    }
                }
            }
            var1 = var1 + 1;
            var2 = var2 + 1;
        }

        if (ok == 0)
            nr++;
        info = info + numar13;
    }
    printf("%d\n", nr);
}

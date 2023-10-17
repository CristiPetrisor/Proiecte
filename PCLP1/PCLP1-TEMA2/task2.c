#include "./utils.h"

void SolveTask2(void *info, int nr_avioane, int N, char **mat) {
    // TODO(student) : Stuff
    int const numar13 = 13;
    for (int i = 0; i <= nr_avioane; i++) {
        unsigned short x = *(unsigned short *)info;  //  linia
        unsigned short y = *(unsigned short *)(info + sizeof(unsigned short));  //  coloana
        unsigned char dir = *(unsigned char *)(info + 2 * sizeof(unsigned short));  //  directia
        unsigned char t = *(unsigned char *)(info + 2 * sizeof(unsigned short) + sizeof(unsigned char));  //  tipul

        if (t == '1') {
            if (dir == 'N') {
                mat[x][y] = '*';
                mat[x + 1][y - 2] = '*';
                mat[x + 1][y - 1] = '*';
                mat[x + 1][y] = '*';
                mat[x + 1][y + 1] = '*';
                mat[x + 1][y + 2] = '*';
                mat[x + 2][y] = '*';
                mat[x + 3][y - 1] = '*';
                mat[x + 3][y] = '*';
                mat[x + 3][y + 1] = '*';
            }

            if (dir == 'S') {
                mat[x][y] = '*';
                mat[x - 1][y] = '*';
                mat[x - 1][y - 2] = '*';
                mat[x - 1][y - 1] = '*';
                mat[x - 1][y + 1] = '*';
                mat[x - 1][y + 2] = '*';
                mat[x - 2][y] = '*';
                mat[x - 3][y - 1] = '*';
                mat[x - 3][y] = '*';
                mat[x - 3][y + 1] = '*';
            }

            if (dir == 'W') {
                mat[x][y] = '*';
                mat[x][y + 1] = '*';
                mat[x - 1][y + 1] = '*';
                mat[x - 2][y + 1] = '*';
                mat[x + 1][y + 1] = '*';
                mat[x + 2][y + 1] = '*';
                mat[x][y + 2] = '*';
                mat[x][y + 3] = '*';
                mat[x + 1][y + 3] = '*';
                mat[x - 1][y + 3] = '*';
            }

            if (dir == 'E') {
                mat[x][y] = '*';
                mat[x][y - 1] = '*';
                mat[x + 2][y - 1] = '*';
                mat[x + 1][y - 1] = '*';
                mat[x - 2][y - 1] = '*';
                mat[x - 1][y - 1] = '*';
                mat[x][y - 2] = '*';
                mat[x][y - 3] = '*';
                mat[x + 1][y - 3] = '*';
                mat[x - 1][y - 3] = '*';
            }
        } else {
            if (dir == 'N') {
                mat[x][y] = '*';
                mat[x + 1][y - 1] = '*';
                mat[x + 1][y] = '*';
                mat[x + 1][y + 1] = '*';
                mat[x + 2][y + 3] = '*';
                mat[x + 2][y + 2] = '*';
                mat[x + 2][y + 1] = '*';
                mat[x + 2][y] = '*';
                mat[x + 2][y - 3] = '*';
                mat[x + 2][y - 2] = '*';
                mat[x + 2][y - 1] = '*';
                mat[x + 3][y] = '*';
                mat[x + 4][y - 2] = '*';
                mat[x + 4][y - 1] = '*';
                mat[x + 4][y] = '*';
                mat[x + 4][y + 2] = '*';
                mat[x + 4][y + 1] = '*';
            }

            if (dir == 'S') {
                mat[x][y] = '*';
                mat[x - 1][y - 1] = '*';
                mat[x - 1][y] = '*';
                mat[x - 1][y + 1] = '*';
                mat[x - 2][y + 3] = '*';
                mat[x - 2][y + 2] = '*';
                mat[x - 2][y + 1] = '*';
                mat[x - 2][y] = '*';
                mat[x - 2][y - 3] = '*';
                mat[x - 2][y - 2] = '*';
                mat[x - 2][y - 1] = '*';
                mat[x - 3][y] = '*';
                mat[x - 4][y - 2] = '*';
                mat[x - 4][y - 1] = '*';
                mat[x - 4][y] = '*';
                mat[x - 4][y + 2] = '*';
                mat[x - 4][y + 1] = '*';
            }

            if (dir == 'W') {
                mat[x][y] = '*';
                mat[x][y + 1] = '*';
                mat[x - 1][y + 1] = '*';
                mat[x + 1][y + 1] = '*';
                mat[x][y + 2] = '*';
                mat[x - 3][y + 2] = '*';
                mat[x - 2][y + 2] = '*';
                mat[x - 1][y + 2] = '*';
                mat[x + 3][y + 2] = '*';
                mat[x + 2][y + 2] = '*';
                mat[x + 1][y + 2] = '*';
                mat[x][y + 3] = '*';
                mat[x][y + 4] = '*';
                mat[x + 2][y + 4] = '*';
                mat[x + 1][y + 4] = '*';
                mat[x - 2][y + 4] = '*';
                mat[x - 1][y + 4] = '*';
            }

            if (dir == 'E') {
                mat[x][y] = '*';
                mat[x][y - 1] = '*';
                mat[x - 1][y - 1] = '*';
                mat[x + 1][y - 1] = '*';
                mat[x][y - 2] = '*';
                mat[x - 3][y - 2] = '*';
                mat[x - 2][y - 2] = '*';
                mat[x - 1][y - 2] = '*';
                mat[x + 3][y - 2] = '*';
                mat[x + 2][y - 2] = '*';
                mat[x + 1][y - 2] = '*';
                mat[x][y - 3] = '*';
                mat[x][y - 4] = '*';
                mat[x - 2][y - 4] = '*';
                mat[x - 1][y - 4] = '*';
                mat[x + 2][y - 4] = '*';
                mat[x + 1][y - 4] = '*';
            }
        }
        info = info + numar13;
    }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                printf("%c ", mat[i][j]);
            printf("\n");
        }
}

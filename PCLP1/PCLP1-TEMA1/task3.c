#include "utils.h"

int main() {
    int i = 0, N = 0;
    float r = 0;
    scanf("%d", &N);
    float numere[N];
    for (i = 0; i < N; i++)
        scanf("%f", &numere[i]);
    int operanzi[N];
    char operand[N];
    scanf("%s", operand);
    int const val_1 = 1, val_2 = 2, val_3 = 3, val_4 = 4, val_5 = 5;
    for (i = 0; i < N - 1; i++) {
        if (operand[i] == '+')
            operanzi[i] = val_1;
        if (operand[i] == '-')
            operanzi[i] = val_2;
        if (operand[i] == '*')
            operanzi[i] = val_3;
        if (operand[i] == '/')
            operanzi[i] = val_4;
        if (operand[i] == '#')
            operanzi[i] = val_5;
    }

    for (i = 0; i < N - 1; i++) {
        if (operanzi[i] == val_3) {
            r = numere[i] * numere[i + 1];
            numere[i + 1] = r;
            int poz = i;
            for (int j = poz; j < N - 1; j++) {
                numere[j] = numere[j + 1];
                operanzi[j] = operanzi[j + 1];
            }
            N--;
            i--;
        } else {
            if (operanzi[i] == val_4) {
            r = numere[i] / numere[i + 1];
            numere[i + 1] = r;
            int poz = i;
            for (int j = poz; j < N - 1; j++) {
                numere[j] = numere[j + 1];
                operanzi[j] = operanzi[j + 1];
            }
            N--;
            i--;
        }
    }
    }

    for (i = 0; i < N - 1; i++) {
        if (operanzi[i] == val_5) {
            r = (numere[i] + numere[i + 1]) * (numere[i] + numere[i + 1]);
            numere[i + 1] = r;
            int poz = i;
            for (int j = poz; j < N - 1; j++) {
                numere[j] = numere[j + 1];
                operanzi[j] = operanzi[j + 1];
            }
            N--;
            i--;
        }}

    for (i = 0; i < N - 1; i++)
        if (operanzi[i] == val_1) {
            r = numere[i] + numere[i + 1];
            numere[i + 1] = r;
            int poz = i;
            for (int j = poz; j < N - 1; j++) {
                numere[j] = numere[j + 1];
                operanzi[j] = operanzi[j + 1];
            }
            N--;
            i--;
        } else {
            if (operanzi[i] == val_2) {
            r = numere[i] - numere[i + 1];
            numere[i + 1] = r;
            int poz = i;
            for (int j = poz; j < N - 1; j++) {
                numere[j] = numere[j + 1];
                operanzi[j] = operanzi[j + 1];
            }
            N--;
            i--;
        }
        }

    printf("%f\n", r);
}

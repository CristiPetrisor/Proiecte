#include "utils.h"

int main() {
    int i = 0, N = 0;
    float r = 0;
    scanf("%d", &N);
    float numere[N];
    for (i = 0; i < N; i++)
        scanf("%f", &numere[i]);
    char operand[N];
    scanf("%s", operand);

    r = numere[0];
    for (i = 0; i < N - 1; i++) {
        if (operand[i] == '+')
            r = r + numere[i + 1];
        if (operand[i] == '-')
            r = r - numere[i + 1];
        if (operand[i] == '*')
            r = r * numere[i + 1];
        if (operand[i] == '/')
            r = r / numere[i + 1];
    }
        printf("%f\n", r);
}

#include "./utils.h"

void SolveTask1(void *info, int nr_avioane) {
    // TODO(student) : Stuff
    int const numar13 = 13;
    for (int i = 1; i <= nr_avioane; i++) {
        printf("(");
        printf("%hu, %hu", *(unsigned short *)info, *(unsigned short *)(info + sizeof(unsigned short)));
        printf(")\n");
        printf("%c\n", *(unsigned char *)(info + 2 * sizeof(unsigned short)));
        printf("%c", *(unsigned char *)(info + 2 * sizeof(unsigned short) + sizeof(unsigned char)));
        printf("%c", *(unsigned char *)(info + 2 * sizeof(unsigned short) + sizeof(unsigned char) + 1));
        printf("%c", *(unsigned char *)(info + 2 * sizeof(unsigned short) + sizeof(unsigned char) + 2));
        printf("%c\n", *(unsigned char*)(info + 2 * sizeof(unsigned short) + sizeof(unsigned char) + 3));
        printf("%d\n", *(unsigned int*)(info + 2 * sizeof(unsigned short) + sizeof(unsigned char) + 4));
        info = info + numar13;
        printf("\n");
    }
}

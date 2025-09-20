#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *fp = fopen("test_data/sample.txt", "w");
    if (!fp) return 1;

    srand(time(NULL));
    size_t size = 1024 * 1024;

    for (size_t i = 0; i < size; i++) {
        char c = 'A' + rand() % 26;
        fputc(c, fp);
    }

    fclose(fp);
    return 0;
}

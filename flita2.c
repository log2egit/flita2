#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
int main() {
    FILE *file_ptr;
    file_ptr = fopen("matrix.txt", "r");
    char buffer_str[64];
    int len;
    int *matrix = NULL;
    int n = 0;
    while (fgets(buffer_str, 64, file_ptr) != NULL) {
        n++;
        len = (strlen(buffer_str))/2;
        matrix = (int*)realloc(matrix, n*len*sizeof(int));
        for (int i = 0; i < len; i++) {
            *(matrix + len*(n-1) + i) = buffer_str[i*2]-'0';
        }
    }
    fclose(file_ptr);
    file_ptr = fopen("graph.txt", "w");
    fputs("graph graphname {\n", file_ptr);
    for (int i = 0; i < n; i++) {
        fprintf(file_ptr, "%c;\n", 'a'+i);
    };
    for (int i = 0; i < len; i++) {
        int start = -1;
        int end = -1;
        for (int j = 0; j < n; j++) {

            if ((*(matrix + j*len + i) == 1) && (start == -1)) {
                start = j;
                end = j;
            }
            else if (*(matrix + j*len + i) == 1) {
                end = j;
            }
        }
        fprintf(file_ptr, "%c -- %c;\n", start+'a', end+'a');
    }
    fputs("}", file_ptr);
    fclose(file_ptr);
    system("dot -Tpng graph.txt > graph_img.png");
    return 0;
}

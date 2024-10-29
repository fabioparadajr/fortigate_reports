#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
char* ler_arquivo(const char* nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    // Alocar memória para armazenar o conteúdo do arquivo
    char *conteudo = malloc(BUFFER_SIZE);
    if (!conteudo) {
        perror("Erro ao alocar memória");
        fclose(file);
        return NULL;
    }

    size_t total_lido = 0;
    size_t lido;

    // Ler o arquivo em partes
    while ((lido = fread(conteudo + total_lido, 1, BUFFER_SIZE - total_lido, file)) > 0) {
        total_lido += lido;
    }

    // Adiciona um terminador nulo
    conteudo[total_lido] = '\0';

    fclose(file);
    return conteudo;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_BUFFER 100

// 1. Leitura segura do buffer
void ler_string(char buffer[], int tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

// 2. Mascaramento de dados sensiveis
void mascarar_dados(char dado[]) {
    int tamanho = strlen(dado);
    if (tamanho <= 4) return;

    int limite = tamanho - 4;
    for (int i = 0; i < limite; i++) {
        dado[i] = '*';
    }
}



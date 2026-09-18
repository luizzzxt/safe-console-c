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
// 3. Validacao de complexidade de senha
int validar_senha(char senha[]) {
    int tamanho = strlen(senha);
    if (tamanho < 8) return 0;

    int tem_maiuscula = 0;
    int tem_minuscula = 0;
    int tem_digito = 0;

    for (int i = 0; i < tamanho; i++) {
        if (isupper(senha[i])) tem_maiuscula = 1;
        else if (islower(senha[i])) tem_minuscula = 1;
        else if (isdigit(senha[i])) tem_digito = 1;
    }

    return tem_maiuscula && tem_minuscula && tem_digito;
}

int main() {
    char dado[TAM_BUFFER];
    char senha[TAM_BUFFER];
    
    printf("Digite um CPF/Cartao: ");
    ler_string(dado, TAM_BUFFER);
    mascarar_dados(dado);
    printf("Dado mascarado: %s\n\n", dado);
    
    printf("Digite uma senha para validar: ");
    ler_string(senha, TAM_BUFFER);
    if (validar_senha(senha)) {
        printf("Status: SENHA FORTE!\n");
    } else {
        printf("Status: SENHA FRACA!\n");
    }
    // Teste da Cifra de Cesar (Etapa 2)
    printf("Digite um texto para cifrar (Cesar): ");
    ler_string(texto, TAM_BUFFER);
    printf("Digite o deslocamento: ");
    scanf("%d", &deslocamento);
    
    cifrar_cesar(texto, deslocamento);
    printf("Texto Cifrado: %s\n", texto);
    
    return 0;
}

    
    
    return 0;
}


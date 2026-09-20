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
// ETAPA 2: CIFRAS DE SEGURANÇA

   // 4. Cifra de Cesar
void cifrar_cesar(char texto[], int deslocamento) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (isalpha(texto[i])) {
            char base = isupper(texto[i]) ? 'A' : 'a';
            texto[i] = (texto[i] - base + deslocamento) % 26 + base;
        }
    }
}
// 5. Cifra XOR (Simetrica)
void cifrar_xor(char texto[], char chave) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = texto[i] ^ chave;
        printf("Status: SENHA FRACA!\n");
    }
}
    
 int main() {
    char dado[TAM_BUFFER];
    char senha[TAM_BUFFER];
    char texto[TAM_BUFFER];
    int deslocamento;
    char chave_xor = 'K';

    // --- TESTES DA ETAPA 1 ---
    printf("Digite um CPF/Cartao: ");
    ler_string(dado, TAM_BUFFER);
    mascarar_dados(dado);
    printf("Dado mascarado: %s\n\n", dado);

    printf("Digite uma senha para validar: ");
    ler_string(senha, TAM_BUFFER);
    if (validar_senha(senha)) {
        printf("Status: SENHA FORTE!\n\n");
    } else {
        printf("Status: SENHA FRACA!\n\n");
    }

    // --- TESTES DA ETAPA 2 ---
    // Cifra de Cesar
    printf("Digite um texto para cifrar (Cesar): ");
    ler_string(texto, TAM_BUFFER);
    printf("Digite o deslocamento: ");
    scanf("%d", &deslocamento);
    getchar(); // Limpa o '\n' pendente do scanf na memoria

    cifrar_cesar(texto, deslocamento);
    printf("Texto Cifrado (Cesar): %s\n\n", texto);

    // Cifra XOR
    printf("Digite um texto para cifrar (XOR): ");
    ler_string(texto, TAM_BUFFER);

    cifrar_xor(texto, chave_xor);
    printf("Texto Cifrado (XOR): %s\n", texto);

    cifrar_xor(texto, chave_xor); // Aplica novamente para decifrar
    printf("Texto Decifrado (XOR): %s\n", texto);

    return 0;
}

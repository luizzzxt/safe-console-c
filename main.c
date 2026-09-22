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

// Funcao auxiliar para limpar o buffer do stdin apos o scanf
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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
        if (isupper((unsigned char)senha[i])) tem_maiuscula = 1;
        else if (islower((unsigned char)senha[i])) tem_minuscula = 1;
        else if (isdigit((unsigned char)senha[i])) tem_digito = 1;
    }

    return tem_maiuscula && tem_minuscula && tem_digito;
}

// 4. Cifra de Cesar (Trata deslocamentos positivos e negativos)
void cifrar_cesar(char texto[], int deslocamento) {
    deslocamento = deslocamento % 26;
    for (int i = 0; texto[i] != '\0'; i++) {
        if (isalpha((unsigned char)texto[i])) {
            char base = isupper((unsigned char)texto[i]) ? 'A' : 'a';
            texto[i] = (texto[i] - base + deslocamento + 26) % 26 + base;
        }
    }
}

// 5. Cifra XOR (Simetrica)
void cifrar_xor(char texto[], char chave) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = texto[i] ^ chave;
    }
}

int main(void) {
    char dado[TAM_BUFFER];
    char senha[TAM_BUFFER];
    char texto[TAM_BUFFER];
    int deslocamento;
    char chave_xor = 'K';
    int opcao;

    do {
        printf("\n================ MENU DE SEGURANCA ================\n");
        printf("1. Mascarar Dado Sensivel (CPF/Cartao)\n");
        printf("2. Validar Complexidade de Senha\n");
        printf("3. Cifrar Texto (Cifra de Cesar)\n");
        printf("4. Cifrar/Decifrar Texto (Cifra XOR)\n");
        printf("0. Sair\n");
        printf("===================================================\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limpar_buffer();
            printf("Opcao invalida! Tente novamente.\n");
            continue;
        }
        limpar_buffer(); // Limpa o '\n' residual

        switch (opcao) {
            case 1:
                printf("\nDigite o dado sensivel (CPF/Cartao): ");
                ler_string(dado, TAM_BUFFER);
                mascarar_dados(dado);
                printf("Dado mascarado: %s\n", dado);
                break;

            case 2:
                printf("\nDigite a senha para validar: ");
                ler_string(senha, TAM_BUFFER);
                if (validar_senha(senha)) {
                    printf("Status: SENHA FORTE!\n");
                } else {
                    printf("Status: SENHA FRACA!\n");
                }
                break;

            case 3:
                printf("\nDigite o texto para cifrar (Cesar): ");
                ler_string(texto, TAM_BUFFER);
                printf("Digite o deslocamento: ");
                if (scanf("%d", &deslocamento) == 1) {
                    limpar_buffer();
                    cifrar_cesar(texto, deslocamento);
                    printf("Resultado: %s\n", texto);
                } else {
                    limpar_buffer();
                    printf("Deslocamento invalido.\n");
                }
                break;

            case 4:
                printf("\nDigite o texto para aplicar a Cifra XOR: ");
                ler_string(texto, TAM_BUFFER);

                cifrar_xor(texto, chave_xor);
                printf("Texto Cifrado: %s\n", texto);

                cifrar_xor(texto, chave_xor);
                printf("Texto Decifrado: %s\n", texto);
                break;

            case 0:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}

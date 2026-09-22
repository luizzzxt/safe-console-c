#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define TAM_BUFFER 100
#define MAX_LOGS 50
#define TAM_LOG 150

// ==========================================
// ESTRUTURA DE LOGS E AUDITORIA (ETAPA 3)
// ==========================================
char logs[MAX_LOGS][TAM_LOG];
int total_logs = 0;

void registrar_log(const char *acao) {
    if (total_logs < MAX_LOGS) {
        snprintf(logs[total_logs], TAM_LOG, "[LOG %02d] %s", total_logs + 1, acao);
        total_logs++;
    }
}

void exibir_relatorio_auditoria(void) {
    printf("\n--- RELATORIO DE AUDITORIA (LOGS) ---\n");
    if (total_logs == 0) {
        printf("Nenhum registro encontrado.\n");
        return;
    }
    for (int i = 0; i < total_logs; i++) {
        printf("%s\n", logs[i]);
    }
}

void buscar_logs(const char *termo) {
    printf("\n--- BUSCA DE LOGS (Termo: '%s') ---\n", termo);
    int encontrados = 0;
    for (int i = 0; i < total_logs; i++) {
        if (strstr(logs[i], termo) != NULL) {
            printf("%s\n", logs[i]);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("Nenhum log correspondente encontrado.\n");
    }
}

// ==========================================
// FUNÇÕES AUXILIARES E ETAPA 1
// ==========================================

// Leitura segura do buffer e sanitização
void ler_string(char buffer[], int tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

// Limpeza rigorosa do buffer do teclado
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Mascaramento de dados sensiveis
void mascarar_dados(char dado[]) {
    int tamanho = strlen(dado);
    if (tamanho <= 4) return;

    int limite = tamanho - 4;
    for (int i = 0; i < limite; i++) {
        dado[i] = '*';
    }
}

// Validacao de complexidade de senha
int validar_senha(char senha[]) {
    int tamanho = strlen(senha);
    if (tamanho < 8) return 0;

    int tem_maiuscula = 0, tem_minuscula = 0, tem_digito = 0;

    for (int i = 0; i < tamanho; i++) {
        if (isupper((unsigned char)senha[i])) tem_maiuscula = 1;
        else if (islower((unsigned char)senha[i])) tem_minuscula = 1;
        else if (isdigit((unsigned char)senha[i])) tem_digito = 1;
    }

    return tem_maiuscula && tem_minuscula && tem_digito;
}

// ==========================================
// ETAPA 2: CIFRAS DE SEGURANÇA E HEX
// ==========================================

void cifrar_cesar(char texto[], int deslocamento) {
    deslocamento = deslocamento % 26;
    for (int i = 0; texto[i] != '\0'; i++) {
        if (isalpha((unsigned char)texto[i])) {
            char base = isupper((unsigned char)texto[i]) ? 'A' : 'a';
            texto[i] = (texto[i] - base + deslocamento + 26) % 26 + base;
        }
    }
}

void cifrar_xor(char texto[], char chave) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = texto[i] ^ chave;
    }
}

void exibir_hexadecimal(const char *texto) {
    printf("Hexadecimal: ");
    for (int i = 0; texto[i] != '\0'; i++) {
        printf("%02X ", (unsigned char)texto[i]);
    }
    printf("\n");
}

// ==========================================
// FUNCIONALIDADE EXTRA: GERADOR DE SENHAS
// ==========================================

void gerar_senha_forte(char destino[], int tamanho) {
    if (tamanho < 8) tamanho = 8;
    if (tamanho >= TAM_BUFFER) tamanho = TAM_BUFFER - 1;

    const char maiusculas[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char minusculas[] = "abcdefghijklmnopqrstuvwxyz";
    const char numeros[] = "0123456789";
    const char especiais[] = "!@#$%^&*()_+-=";
    const char todos[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=";

    destino[0] = maiusculas[rand() % strlen(maiusculas)];
    destino[1] = minusculas[rand() % strlen(minusculas)];
    destino[2] = numeros[rand() % strlen(numeros)];
    destino[3] = especiais[rand() % strlen(especiais)];

    for (int i = 4; i < tamanho; i++) {
        destino[i] = todos[rand() % strlen(todos)];
    }

    // Embaralhamento Fisher-Yates
    for (int i = tamanho - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = destino[i];
        destino[i] = destino[j];
        destino[j] = temp;
    }
    destino[tamanho] = '\0';
}

// ==========================================
// FLUXO PRINCIPAL
// ==========================================

int main(void) {
    srand((unsigned int)time(NULL));

    char dado[TAM_BUFFER], senha[TAM_BUFFER], texto[TAM_BUFFER], termo[TAM_BUFFER];
    int deslocamento, opcao, tam_senha_extra;
    char chave_xor = 'K';

    registrar_log("Sistema SafeConsole iniciado.");

    do {
        printf("\n================ MENU DE SEGURANCA ================\n");
        printf("1. Mascarar Dado Sensivel (CPF/Cartao)\n");
        printf("2. Validar Complexidade de Senha\n");
        printf("3. Cifrar Texto (Cifra de Cesar)\n");
        printf("4. Cifrar/Decifrar Texto (Cifra XOR + HEX)\n");
        printf("5. Visualizar Relatorio de Auditoria (Logs)\n");
        printf("6. Buscar no Historico de Logs\n");
        printf("7. [EXTRA] Gerar Senha Forte Aleatoria\n");
        printf("0. Sair\n");
        printf("===================================================\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limpar_buffer();
            printf("Opcao invalida!\n");
            continue;
        }
        limpar_buffer();

        switch (opcao) {
            case 1:
                printf("\nDigite o dado sensivel: ");
                ler_string(dado, TAM_BUFFER);
                mascarar_dados(dado);
                printf("Dado mascarado: %s\n", dado);
                registrar_log("Executado mascaramento de dados.");
                break;

            case 2:
                printf("\nDigite a senha para validar: ");
                ler_string(senha, TAM_BUFFER);
                if (validar_senha(senha)) {
                    printf("Status: SENHA FORTE!\n");
                    registrar_log("Validacao de senha: Forte.");
                } else {
                    printf("Status: SENHA FRACA!\n");
                    registrar_log("Validacao de senha: Fraca.");
                }
                break;

            case 3:
                printf("\nDigite o texto para Cifra de Cesar: ");
                ler_string(texto, TAM_BUFFER);
                printf("Digite o deslocamento: ");
                if (scanf("%d", &deslocamento) == 1) {
                    limpar_buffer();
                    cifrar_cesar(texto, deslocamento);
                    printf("Resultado: %s\n", texto);
                    registrar_log("Executada Cifra de Cesar.");
                } else {
                    limpar_buffer();
                    printf("Deslocamento invalido.\n");
                }
                break;

            case 4:
                printf("\nDigite o texto para Cifra XOR: ");
                ler_string(texto, TAM_BUFFER);

                cifrar_xor(texto, chave_xor);
                printf("Texto Cifrado (String): %s\n", texto);
                exibir_hexadecimal(texto);

                cifrar_xor(texto, chave_xor);
                printf("Texto Decifrado: %s\n", texto);
                registrar_log("Executada Cifra XOR com saida HEX.");
                break;

            case 5:
                exibir_relatorio_auditoria();
                break;

            case 6:
                printf("\nDigite o termo para buscar nos logs: ");
                ler_string(termo, TAM_BUFFER);
                buscar_logs(termo);
                break;

            case 7:
                printf("\nDigite o tamanho da senha (minimo 8): ");
                if (scanf("%d", &tam_senha_extra) == 1) {
                    limpar_buffer();
                    if (tam_senha_extra < 8) {
                        printf("Aviso: Ajustando tamanho para o minimo seguro de 8 caracteres.\n");
                        tam_senha_extra = 8;
                    }
                    gerar_senha_forte(senha, tam_senha_extra);
                    printf("\n---> Senha Gerada: %s <---\n", senha);
                    registrar_log("Gerada senha forte aleatoria.");
                } else {
                    limpar_buffer();
                    printf("\nErro: Digite apenas um numero inteiro valido!\n");
                }
                break;

            case 0:
                registrar_log("Sistema encerrado.");
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}

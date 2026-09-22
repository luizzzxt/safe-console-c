#  SafeConsole - Aplicação em C para Segurança, Criptografia e Auditoria

## 👥 Integrantes e Divisão de Contribuições

* **Luiz:** Responsável pela implementação da leitura segura de dados (`ler_string`), sanitização de buffers e mascaramento de dados sensíveis. Desenvolveu a estrutura da matriz de auditoria de logs em memória (Etapa 3), organizou a documentação do projeto e gerenciou o repositório no GitHub.

* **Vinicius:** Responsável pela lógica do validador de complexidade de senhas e pelo desenvolvimento das cifras criptográficas (César e XOR com exibição Hexadecimal). Construiu a estrutura do menu interativo com tratamento de erros de digitação e implementou o gerador de senhas fortes com o algoritmo de *Fisher-Yates*.

O **SafeConsole** é um sistema em C focado em **programação defensiva**, **sanitização de entradas**, **proteção de dados sensíveis**, **criptografia simétrica e clássica** e **rastreabilidade via auditoria de logs**.

O projeto foi desenvolvido como requisito acadêmico, estruturado com um menu interativo completo, gestão rigorosa de buffer e prevenção de *undefined behaviors*.

---

## 📋 Sumário
- [Funcionalidades Principais](#-funcionalidades-principais)
- [Estrutura do Código e Detalhamento Técnico](#-estrutura-do-código-e-detalhamento-técnico)
- [Boas Práticas e Programação Defensiva](#-boas-práticas-e-programação-defensiva)
- [Como Compilar e Executar](#-como-compilar-e-executar)
- [Integrantes e Divisão de Contribuições](#-integrantes-e-divisão-de-contribuições)

---

##  Funcionalidades Principais

* **Etapa 1 — Sanitização, Mascaramento e Senhas:**
  * Leitura segura de dados para evitar *buffer overflow*.
  * Sanitização de entrada removendo o caractere de quebra de linha (`\n`).
  * Mascaramento *in-place* de dados sensíveis (ex: CPF e cartões), preservando apenas os 4 últimos dígitos.
  * Validação de complexidade de senhas (tamanho mínimo, maiúsculas, minúsculas e números).

* **Etapa 2 — Cifras de Segurança e Exibição Hexadecimal:**
  * **Cifra de César:** Deslocamento alfabético modular com suporte a valores positivos e negativos.
  * **Cifra XOR:** Criptografia simétrica bitwise acompanhada de exibição em formato **Hexadecimal** (`%02X`) para tratamento seguro de caracteres não imprimíveis.

* **Etapa 3 — Matriz de Logs em Memória e Auditoria:**
  * Registrador de eventos na memória dinâmica/estática através de matriz bidimensional.
  * Relatório completo de auditoria para inspeção de operações realizadas.
  * Mecanismo de busca por termos específicos no histórico de logs.

* **Funcionalidade Extra — Gerador de Senhas Fortes:**
  * Geração aleatória de senhas com *seed* temporal (`time.h`), embaralhamento via algoritmo de *Fisher-Yates* e validação automática.

---

## Estrutura do Código e Detalhamento Técnico

### 1. Leitura Segura e Sanitização (`ler_string`)
* **Descrição:** Garante a leitura controlada de strings.
* **Técnica:** Utiliza `fgets` limitado ao tamanho do buffer. Trata a string calculando o comprimento via `strlen` e substitui o `\n` pelo caractere nulo `\0`, impedindo quebras de linha indesejadas no fluxo do programa.

### 2. Limpeza de Buffer Auxiliar (`limpar_buffer`)
* **Descrição:** Previne a contaminação de entradas após leituras numéricas.
* **Técnica:** Utiliza um laço `while ((c = getchar()) != '\n' && c != EOF)` para consumir eventuais resíduos deixados no `stdin` por chamadas da função `scanf`.

### 3. Mascaramento de Dados Sensíveis (`mascarar_dados`)
* **Descrição:** Oculta informações privadas diretamente na memória do vetor.
* **Técnica:** Altera os caracteres do índice `0` até `tamanho - 4` para o caractere `'*'`, garantindo a conformidade visual de privacidade de dados.

### 4. Validador de Senhas (`validar_senha`)
* **Descrição:** Analisa os requisitos mínimos de força da senha.
* **Técnica:** Verifica comprimento mínimo de 8 caracteres e aplica casting `(unsigned char)` junto às funções `<ctype.h>` (`isupper`, `islower`, `isdigit`) para assegurar tratamento correto de caracteres estendidos.

### 5. Cifra de César (`cifrar_cesar`)
* **Descrição:** Algoritmo de substituição alfabética circular.
* **Técnica:** Aplica a fórmula matemática:  
  `texto[i] = (texto[i] - base + deslocamento + 26) % 26 + base`  
  A adição do valor `26` permite operar corretamente com deslocamentos negativos mantendo a rotação no alfabeto ASCII.

### 6. Cifra XOR com Saída Hexadecimal (`cifrar_xor` / `exibir_hexadecimal`)
* **Descrição:** Operação binária de substituição simétrica (*OU Exclusivo*).
* **Técnica:** Altera os bits através do operador `^`. Por gerar caracteres não imprimíveis, a função auxiliar `exibir_hexadecimal` imprime os valores formatados em bytes Hex (`%02X`).

### 7. Sistema de Auditoria e Logs (`registrar_log`, `exibir_relatorio_auditoria`, `buscar_logs`)
* **Descrição:** Módulo de rastreabilidade do sistema.
* **Técnica:** Armazena os eventos do sistema na matriz `logs[MAX_LOGS][TAM_LOG]`. Permite consulta sequencial do relatório e busca de padrões utilizando a função `strstr`.

---

## 🛡️ Boas Práticas e Programação Defensiva

1. **Prevenção contra Buffer Overflow:** Substituição total de funções inseguras como `gets()` e `scanf("%s")` por `fgets()` parametrizado.
2. **Validação de Retorno em `scanf`:** O menu e as opções checam se a leitura numérica foi bem-sucedida (`if (scanf(...) != 1)`), evitando loops infinitos em caso de digitação de letras.
3. **Robustez de Tipos:** Uso de `unsigned char` na checagem de caracteres para evitar *undefined behavior* em arquiteturas específicas.
4. **Criptografia e Caracteres Invisíveis:** Exibição em Hexadecimal na Cifra XOR para evitar corrupção visual do terminal ao manipular bytes nulos ou de controle.

---

## 🛠️ Como Compilar e Executar

### Pré-requisitos
* Compilador C (**GCC**, **Clang** ou similar) instalado.

### Comando para Compilação
```bash
gcc -Wall -Wextra -std=c99 main.c -o safe_console

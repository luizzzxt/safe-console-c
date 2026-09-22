# safe-console-c
Sistema de Cifragem, Sanitização e Logs de Segurança em C - AV1 CÉSAR School

## Integrantes do Grupo
Luiz — Implementação do módulo de higienização de buffer, mascaramento de dados e estruturação do controle de versão.

Vinicius — Implementação do módulo de validação de senhas, lógica matemática da Cifra de César e integração do menu interativo no main.

# 🛡️ SafeConsole - Aplicação em C para Segurança e Criptografia

O **SafeConsole** é um programa em C focado em práticas de **programação defensiva**, **sanitização de entradas**, **proteção de dados sensíveis** e **criptografia clássica e simétrica**. 

O projeto foi desenvolvido como requisito acadêmico, dividindo-se em módulos funcionais acessíveis por um menu interativo e construído com tratamento rigoroso de ponteiros e memória.

---

## 📋 Sumário
- [Funcionalidades](#-funcionalidades)
- [Estrutura do Código e Detalhamento Técnico](#-estrutura-do-código-e-detalhamento-técnico)
- [Como Compilar e Executar](#-como-compilar-e-executar)
- [Conceitos de Segurança Aplicados](#-conceitos-de-segurança-aplicados)
- [Integrantes e Contribuições](#-integrantes-e-contribuições)

---

## 🚀 Funcionalidades

1. **Higienização e Sanitização de Entrada:** Leitura segura de strings via terminal, impedindo estouro de buffer (*buffer overflow*) e eliminando a quebra de linha (`\n`).
2. **Mascaramento de Dados Sensíveis:** Ocultação de dados privados (como CPF ou número de cartão), mantendo apenas os últimos 4 dígitos visíveis.
3. **Validação de Complexidade de Senhas:** Análise rigorosa de senhas para verificar a presença de letras maiúsculas, minúsculas e números.
4. **Cifra de César:** Algoritmo de substituição alfabética com suporte a deslocamentos positivos e negativos e rotação modular.
5. **Cifra XOR:** Criptografia simétrica baseada no operador de nível de bit *OU Exclusivo*, permitindo cifrar e decifrar com a mesma chave.

---

## 🔍 Estrutura do Código e Detalhamento Técnico

### 1. Leitura Segura e Sanitização (`ler_string`)
* **Assinatura:** `void ler_string(char buffer[], int tamanho)`
* **Descrição:** Substitui a leitura insegura via `scanf("%s")` pelo uso do `fgets`.
* **Funcionamento:** O `fgets` limita a leitura ao tamanho máximo alocado no vetor. A função utiliza `strlen` para localizar o final do texto lido e substitui o caractere de quebra de linha `\n` (deixado ao pressionar Enter) pelo caractere nulo `\0`, sanitizando a string.

### 2. Limpeza de Buffer Auxiliar (`limpar_buffer`)
* **Assinatura:** `void limpar_buffer(void)`
* **Descrição:** Função utilitária para consumo de resíduos no fluxo de entrada padrão (`stdin`).
* **Funcionamento:** Executa um laço `while` até consumir o caractere `\n` ou `EOF`. Isso previne que chamadas anteriores do `scanf` deixem o caractere Enter no buffer, o que faria as leituras seguintes de texto serem ignoradas.

### 3. Mascaramento de Dados (`mascarar_dados`)
* **Assinatura:** `void mascarar_dados(char dado[])`
* **Descrição:** Anonimiza dados na própria memória (in-place).
* **Funcionamento:** Calcula o comprimento total da string. Se o comprimento for maior que 4, calcula a posição `limite = tamanho - 4` e substitui todos os caracteres do índice `0` até `limite - 1` por asteriscos (`*`), preservando a identificação dos últimos 4 dígitos.

### 4. Validação de Senha (`validar_senha`)
* **Assinatura:** `int validar_senha(char senha[])`
* **Descrição:** Avalia os critérios de força da senha informada.
* **Funcionamento:** Exige tamanho mínimo de 8 caracteres. Percorre a string avaliando caractere por caractere através das funções `<ctype.h>` (`isupper`, `islower`, `isdigit`). É aplicado o *casting* `(unsigned char)` para garantir portabilidade com caracteres estendidos. Retorna `1` caso atinja todos os critérios ou `0` caso contrário.

### 5. Cifra de César (`cifrar_cesar`)
* **Assinatura:** `void cifrar_cesar(char texto[], int deslocamento)`
* **Descrição:** Aplica criptografia por substituição.
* **Funcionamento:** Utiliza a fórmula matemática de aritmética modular:
  $$\text{NovoCaractere} = ((\text{caractere} - \text{base} + \text{deslocamento}) \pmod{26} + 26) \pmod{26} + \text{base}$$
  O termo `+ 26` garante o funcionamento correto mesmo quando o usuário insere um deslocamento negativo. Mantém intactos símbolos, números e o padrão de maiúsculas/minúsculas.

### 6. Cifra XOR (`cifrar_xor`)
* **Assinatura:** `void cifrar_xor(char texto[], char chave)`
* **Descrição:** Criptografia simétrica baseada em operações bitwise.
* **Funcionamento:** Percorre a string aplicando o operador XOR (`^`) entre a representação binária de cada caractere e a chave de criptografia. Por ser uma operação involutiva, aplicar a função uma segunda vez com a mesma chave recupera o texto original.

---

## 🛠️ Como Compilar e Executar

### Pré-requisitos
* Compilador C (como **GCC** ou **Clang**) instalado.

### Passos
1. Clone o repositório:
   ```bash
   git clone [https://github.com/luizzzxt/safe-console-c.git](https://github.com/luizzzxt/safe-console-c.git)
   cd safe-console-c

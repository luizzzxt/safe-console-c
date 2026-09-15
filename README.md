# safe-console-c
Sistema de Cifragem, Sanitização e Logs de Segurança em C - AV1 CÉSAR School

## Integrantes do Grupo
* Luiz Carlos Barbosa Neto
* 
---
## Resumo do Projeto

O programa foi desenvolvido em C para demonstrar a aplicação de práticas básicas de segurança e manipulação de dados.

### Etapa 1
* Leitura de dados sem estouro de buffer usando fgets.
* Mascaramento de dados para ocultar números de CPF ou cartão, exibindo apenas os 4 últimos dígitos.
* Validação de senha para verificar se possui no mínimo 8 caracteres, com letras maiúsculas, minúsculas e números.

### Etapa 2
* Cifra de César para criptografia por deslocamento de caracteres.
* Cifra XOR para criptografia usando chave de caractere.
---
## Compilação e Execução

### No terminal (GCC)
gcc main.c -o safe_console
./safe_console

### No OnlineGDB
1. Selecione a linguagem C.
2. Cole o código do arquivo main.c no editor.
3. Clique em Run.

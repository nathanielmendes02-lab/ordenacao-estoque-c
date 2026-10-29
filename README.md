# Ordenação de Estoque do Supermercado

## Objetivo
Este projeto usa os algoritmos de ordenação Bubble Sort e Quick Sort para organizar produtos de um supermercado por quantidade em estoque.

## Situação-problema
Um supermercado precisa identificar rapidamente quais itens têm pouco estoque e quais precisam de reposição. Para isso, é necessário ordenar os produtos pela quantidade em estoque, em ordem crescente.

## Funcionalidades
- Cadastro de 12 produtos com código, nome, quantidade em estoque e preço
- Ordenação com Bubble Sort
- Ordenação com Quick Sort
- Comparação entre os dois algoritmos
- Exibição dos produtos antes e depois da ordenação
- Contagem de comparações e trocas

## Como compilar
No terminal, dentro da pasta do projeto:

```bash
gcc ordenacao_estoque.c -o ordenacao_estoque
```

## Como executar
Linux/macOS:

```bash
./ordenacao_estoque
```

Windows (PowerShell):

```powershell
.\ordenacao_estoque.exe
```

## Como usar o programa
Ao abrir o programa, será exibido um menu:

1. Ordenar com Bubble Sort
2. Ordenar com Quick Sort
3. Comparar os dois algoritmos
0. Sair

## Bubble Sort
O Bubble Sort compara pares adjacentes e troca os elementos quando estão fora de ordem. Esse processo é repetido várias vezes até que o vetor fique totalmente ordenado.

- Complexidade no pior caso: O(n²)
- É simples de entender, mas menos eficiente para listas grandes

## Quick Sort
O Quick Sort usa a estratégia de dividir para conquistar. Ele escolhe um pivô, organiza os elementos menores à esquerda e maiores à direita, e repete esse processo recursivamente.

- Complexidade média: O(n log n)
- Geralmente é mais rápido que Bubble Sort em listas maiores

## Exemplo de saída
Ao escolher a opção 3, o programa mostra a comparação final dos dois algoritmos:

```text
Algoritmo      Comparacoes   Trocas   Verificacao
-----------------------------------------------------
Bubble Sort    65            38       OK
Quick Sort     32            18       OK
```

## Observação
Os dados iniciais são os mesmos para os dois algoritmos, então a comparação mostra de forma clara a diferença na quantidade de operações realizadas.

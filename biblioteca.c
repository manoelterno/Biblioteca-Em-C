#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void menu()
{
    printf("---MENU PRINCIPAL---\n\n");
    printf("Digite sua escolha\n");
    printf("1 - Usuario\n");
    printf("2 - Livro\n");
    printf("3 - Reserva\n");
    printf("4 - Relatorios\n");
    printf("5 - Sair\n\n");
}

typedef struct data
{
    int dia, mes, ano;
} Data;

typedef struct autor
{
    char nome[30];
    char instituicao[30];
    struct Autor *prox; // c. Autores (Lista de Autor)
} Autor;

typedef struct livro
{
    // identificadores sao apenas numeros inteiros q vao somando 1 por 1 a cada nova adição
    int identificador;
    char titulo[50];
    Autor *autores; // c. Autores (Lista de Autor)
    int ano;
    int edicao;
    char editora[30];
} Livro;

typedef struct usuario
{
    int identificador;
    char nome[30];
    char endereco[50];
    int telefone;
} Usuario;

typedef struct reserva
{
    Data inicio;
    Data fim;
    Usuario *usuario_responsavel;
    Livro *livro_reservado;
} Reserva;

int main()
{
    int escolha;
    while(1)
    {
        system("cls");
        menu();
        scanf("%d", &escolha);
    }   
    return 0;
}

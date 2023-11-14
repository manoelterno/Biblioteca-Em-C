#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    struct usuario *prox;
} Usuario;

typedef struct reserva
{
    Data inicio;
    Data fim;
    Usuario *usuario_responsavel;
    Livro *livro_reservado;
} Reserva;

void adicionar_usuario();
void menu_usuario();
void menu();
void imprimir_usuarios();
void menu_relatorio();

void imprimir_usuarios(Usuario **usuarios)
{
    Usuario *atual = *usuarios;
    
    if (atual == NULL)
    {
        printf("A lista de usuarios esta vazia.\n");
    }
    else
    {
        while (atual != NULL)
        {
            printf("ID: %d, Nome: %s, Endereco: %s, Telefone: %d\n", atual->identificador, atual->nome, atual->endereco, atual->telefone);
            atual = atual->prox;
        }
    }
    system("pause");
}

void menu_relatorio(Usuario **usuarios)
{
    int escolha = 0;
    while (escolha != 4)
    {
        system("cls");
        printf("---RELATORIOS---\n\n");
        printf("Digite sua escolha\n");
        printf("1 - Listar usuarios\n");
        printf("2 - Listar livros\n");
        printf("3 - Listar reservas\n");
        printf("4 - Voltar\n\n");
        scanf("%d", &escolha);
        getchar();
        switch (escolha)    
        {
        case 1:
            // endereco de usuarios na main
            imprimir_usuarios(usuarios);
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        }
    }
}

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

// preciso passar o endereço do ponteiro usuarios para modifica-lo na main (ponteiro de ponteiro)
void menu_usuario(Usuario **usuarios, int *quantidade_usuarios)
{
    int escolha = 0;
    while (escolha != 4)
    {
        system("cls");
        printf("---USUARIOS---\n\n");
        printf("Digite sua escolha\n");
        printf("1 - Adicionar usuario\n");
        printf("2 - Editar usuario\n");
        printf("3 - Excluir usuario\n");
        printf("4 - Voltar\n\n");
        scanf("%d", &escolha);
        getchar();
        switch (escolha)    
        {
        case 1:
            // endereco de usuarios na main
            adicionar_usuario(usuarios, quantidade_usuarios);
            break;
        case 2:
            // editar_usuario();
            break;
        case 3:
            // adicionar_usuario();
            break;
        }
    }
}

void adicionar_usuario(Usuario **usuarios, int *quantidade_usuarios)
{
    Usuario *novoUsuario = (Usuario *)malloc(sizeof(Usuario));
    system("cls");
    printf("Digite os dados do usuario:\n\n");
    printf("Nome do usuario: ");
    // mesma coisa que gets(*novoUsuario.nome);
    gets(novoUsuario->nome);
    printf("Endereco do usuario: ");
    gets(novoUsuario->endereco);
    printf("Telefone do usuario: ");
    scanf("%d", &novoUsuario->telefone);
    novoUsuario->identificador = *quantidade_usuarios + 1;
    *quantidade_usuarios = *quantidade_usuarios + 1;
    novoUsuario->prox = *usuarios;
    *usuarios = novoUsuario;
}

int main()
{
    Usuario *usuarios = NULL;
    int escolha = 0;
    int quantidade_usuarios = 0;
    // quantidade_livros = 0, quantidade_reservas = 0;
    while (escolha != 5)
    {
        system("cls");
        menu();
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1:
            menu_usuario(&usuarios, &quantidade_usuarios);
            break;
        case 2:
            // menu_livro();
            break;
        case 3:
            // menu_usuario();
            break;
        case 4:
            menu_relatorio(&usuarios);
            break;
        default:
            break;
        }
    }
    return 0;
}

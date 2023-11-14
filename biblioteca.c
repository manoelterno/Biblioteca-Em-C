#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void adicionar_usuario();
void menu_usuario();
void menu();
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
    // com certeza é melhor string do q int
    int telefone;
} Usuario;

typedef struct reserva
{
    Data inicio;
    Data fim;
    Usuario *usuario_responsavel;
    Livro *livro_reservado;
} Reserva;


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

void menu_usuario(Usuario *usuarios, int *quantidade_usuarios)
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
            adicionar_usuario(usuarios, quantidade_usuarios);
            break;
        case 2:
            //editar_usuario();
            break;
        case 3:
            //adicionar_usuario();
            break;
        }
    }
}

void adicionar_usuario(Usuario *usuarios, int *quantidade_usuarios)
{
    system("cls");
    printf("Digite os dados do usuario:\n\n");
    // uma forma de adicionar que funciona (foi testado):
    /*
    scanf("Nome: %s Endereco: %s Telefone: %d", usuarios[*quantidade_usuarios].nome, usuarios[*quantidade_usuarios].endereco, 
    &usuarios[*quantidade_usuarios].telefone);
    usuarios[*quantidade_usuarios].identificador = *quantidade_usuarios + 1;
    */
    printf("Nome do usuario: ");
    gets(usuarios[*quantidade_usuarios].nome);
    printf("Endereco do usuario: ");
    gets(usuarios[*quantidade_usuarios].endereco);
    printf("Telefone do usuario: ");
    scanf("%d", &usuarios[*quantidade_usuarios].telefone);
    usuarios[*quantidade_usuarios].identificador = *quantidade_usuarios + 1;
    *quantidade_usuarios = *quantidade_usuarios + 1;
}
int main()
{
   // Livro livros[20];
    Usuario usuarios[10];
  //  Reserva reservas[20];
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
            menu_usuario(usuarios, &quantidade_usuarios);
            break;
        case 2:
            // menu_livro();
            break;
        case 3:
            // menu_usuario();
            break;
        case 4:
            //  menu_relatorio();
            break;
        default:
            break;
        }
    }
    return 0;
}

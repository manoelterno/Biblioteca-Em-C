/*
    @Trabalho Lógica de Programação
    @Autores: Guilherme Lopes e João Manoel
    @Curso: Engenharia de Computação
    @Problema: Banco de Dados de uma Biblioteca
*/

//BIBLIOTECAS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//MACROS
#define MAX 50

//STRUCTS
typedef struct data
{
    int dia, mes, ano;
} Data;

typedef struct autor
{
    char nome[MAX];
    struct Autor *prox;
} Autor;

typedef struct livro
{
    int identificador;
    int ano;
    int edicao;
    char titulo[MAX];
    char editora[MAX];
    struct livro *prox; 
    Autor *autores; 
} Livro;

typedef struct usuario
{
    long int telefone;
    int identificador;
    char nome[MAX];
    char endereco[MAX];
    struct usuario *prox;
} Usuario;

typedef struct reserva
{
    Data inicio;
    Data fim;
    Livro *livro_reservado;
    Usuario *usuario_responsavel;
} Reserva;

//PRÓTOTIPOS DAS FUNÇÕES
void menu(); //Função responsável por mostrar o menu principal

void menu_usuario(); //Função responsável por mostrar as opcoes sobre o que pode ser feito com os usuarios
void adicionar_usuario(); //Funcao para adicionar um usuario ao banco de dados
void excluir_usuario(); //Funcao para excluir um usuario ao banco de dados
void editar_usuario(); //Funcao para editar um usuario ao banco de dados
void liberar_usuarios(); //Desalocar a memoria alocada para a lista de usuarios

void menu_livro(); //Função responsável por mostrar as opcoes sobre o que pode ser feito com os livros
void adicionar_livro(); //Funcao para adicionar um livro ao banco de dados
void excluir_livro(); //Funcao para excluir um livro ao banco de dados
void editar_livro(); //Funcao para editar um livro ao banco de dados
void liberar_livros(); //Desalocar a memoria alocada para a lista de livros

void adicionar_autor(); //Funcao para adicionar um autor a um determinado livro
void editar_autores();  //Funcao para editar os autores de um livro do banco de dados
void liberar_autores(); //Desalocar a memoria alocada para a lista de autores

void menu_reserva(); //Função responsável por mostrar as opcoes sobre o que pode ser feito com as reservas
void adicionar_reserva(); //Funcao para adicionar uma reserva ao banco de dados
void excluir_reserva(); //Funcao para excluir uma reserva ao banco de dados
void editar_reserva();  //Funcao para editar uma reserva ao banco de dados

void menu_relatorio(); // Função responsável por mostrar as opções sobre as diferentes listagens que é possível fazer
void imprimir_usuarios(); //Funcao para listar os usuario do banco de dados
void imprimir_livros(); //Funcao para listar os livros do banco de dados
void imprimir_autores(); //Funcao para listar os autores de um determinado livro do banco de dados
void imprimir_reservas(); //Funcao para listar as reservas do banco de dados

//MAIN
int main()
{
    Reserva *reservas = NULL;
    Usuario *usuarios = NULL;
    Livro *livros = NULL;
    int escolha = 0;
    int quantidade_usuarios = 0, quantidade_livros = 0, quantidade_reservas = 0;

    while (escolha != 5)
    {
        system("cls");

        menu();
        scanf("%d", &escolha);
        getchar();
        
        switch (escolha)
        {
        case 1:
            menu_usuario(&usuarios, &quantidade_usuarios);
            break;
        case 2:
            menu_livro(&livros, &quantidade_livros);
            break;
        case 3:
            menu_reserva(&usuarios, &livros,  &reservas, &quantidade_reservas);
            break;
        case 4:
            menu_relatorio(&usuarios, &livros, &reservas);
            break;
        case 5:
            break;
        default:
            printf("Opcao Invalida.\n");
            system("pause");
            break;
        }
    }
    
    liberar_usuarios(&usuarios);
    liberar_livros(&livros);
    return 0;
}

//FUNÇÕES

void menu()
{
    printf("---MENU PRINCIPAL---\n\n");
    printf("1 - Usuario\n");
    printf("2 - Livro\n");
    printf("3 - Reserva\n");
    printf("4 - Relatorios\n");
    printf("5 - Sair\n\n");
    printf("Digite sua escolha: ");
}

void menu_usuario(Usuario **usuarios, int *quantidade_usuarios)
{
    int escolha = 0;

    while (escolha != 4)
    {
        system("cls");

        printf("---USUARIOS---\n\n");
        printf("1 - Adicionar usuario\n");
        printf("2 - Editar usuario\n");
        printf("3 - Excluir usuario\n");
        printf("4 - Voltar\n\n");
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);
        getchar();

        switch (escolha)
        {
        case 1:
            adicionar_usuario(usuarios, quantidade_usuarios);
            break;
        case 2:
            editar_usuario(usuarios);
            break;
        case 3:
            excluir_usuario(usuarios);
            break;
        case 4:
            break;
        default:
            printf("Opcao Invalida.\n");
            system("pause");
            break;
        }
    }
}

void adicionar_usuario(Usuario **usuarios, int *quantidade_usuarios)
{
    Usuario *novoUsuario = (Usuario *)malloc(sizeof(Usuario));

    system("cls");

    printf("---ADICIONAR USUARIO---\n\n");
    printf("Digite os dados do usuario:\n\n");
    printf("Nome do usuario: ");
    gets(novoUsuario->nome);

    printf("Endereco do usuario: ");
    gets(novoUsuario->endereco);

    printf("Telefone do usuario: ");
    scanf("%ld", &novoUsuario->telefone);
    getchar();

    novoUsuario->identificador = *quantidade_usuarios + 1;
    *quantidade_usuarios = *quantidade_usuarios + 1;
    novoUsuario->prox = *usuarios;
    *usuarios = novoUsuario;
}

void excluir_usuario(Usuario **usuarios)
{
    int id, v=1;

    system("cls");

    printf("---EXCLUIR USUARIO---\n\n");
    printf("Digite o identificador do usuario: ");
    scanf("%d", &id);
    getchar();

    Usuario *usuario_atual = *usuarios;
    Usuario *usuario_anterior = NULL;

    while (usuario_atual != NULL)
    {
        if (usuario_atual->identificador == id)
        {
            v = 0;
            if (usuario_anterior == NULL)
                *usuarios = usuario_atual->prox;
            else
                usuario_anterior->prox = usuario_atual->prox; 
            free(usuario_atual);
            break;
        }
        usuario_anterior = usuario_atual;
        usuario_atual = usuario_atual->prox;
    }

    if (v)
        printf("\nUsuario nao encontrado\n");
    else
        printf("\nUsuario excluido com sucesso\n");

    system("pause");
}

void editar_usuario(Usuario **usuarios)
{
    int id;

    system("cls");
    
    printf("---EDITAR USUARIO---\n\n");
    printf("Digite o identificador do usuario: ");
    scanf("%d", &id);
    getchar();

    Usuario *usuario_atual = *usuarios;

    while (usuario_atual != NULL)
    {
        if(usuario_atual->identificador == id)
        {
            printf("\nNome atual: %s\n", usuario_atual->nome);
            printf("Digite o novo nome do usuario: ");
            gets(usuario_atual->nome);

            printf("\nEndereco atual: %s\n", usuario_atual->endereco);
            printf("Digite o novo endereco do usuario: ");
            gets(usuario_atual->endereco);

            printf("\nTelefone atual: %ld\n", usuario_atual->telefone);
            printf("Digite o novo telefone do usuario: ");
            scanf("%ld", &usuario_atual->telefone);
            getchar();
            break;
        }
        usuario_atual = usuario_atual->prox;
    }
}

void imprimir_usuarios(Usuario **usuarios)
{
    Usuario *usuario_atual = *usuarios;

    if (usuario_atual == NULL)
    {
        printf("A lista de usuarios esta vazia.\n");
    }
    else
    {
        while (usuario_atual != NULL)
        {
            printf("\nID: %d, Nome: %s, Endereco: %s, Telefone: %ld\n", usuario_atual->identificador, usuario_atual->nome, usuario_atual->endereco, usuario_atual->telefone);
            usuario_atual = usuario_atual->prox;
        }
    }
    system("pause");
}

void liberar_usuarios(Usuario **usuarios)
{
    Usuario *usuario_atual = *usuarios;
    Usuario *prox_usuario = NULL;

    while (usuario_atual != NULL)
    {
        prox_usuario = usuario_atual->prox;
        free(usuario_atual);
        usuario_atual = prox_usuario;
    }
}

void menu_livro(Livro **livros, int *quantidade_livros){
    int escolha = 0;

    while (escolha != 4)
    {
        system("cls");

        printf("---LIVROS---\n\n");
        printf("1 - Adicionar livro\n");
        printf("2 - Editar livro\n");
        printf("3 - Excluir livro\n");
        printf("4 - Voltar\n\n");
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);
        getchar();

        switch (escolha)
        {
        case 1:
            adicionar_livro(livros, quantidade_livros);
            break;
        case 2:
            editar_livro(livros);
            break;
        case 3:
            excluir_livro(livros);
            break;
        case 4:
            break;
        default:
            printf("Opcao Invalida.\n");
            system("pause");
        }
    }
}

void adicionar_livro(Livro **livros, int *quantidade_livros)
{
    system("cls");

    Livro *novoLivro = (Livro *)malloc(sizeof(Livro));

    novoLivro->autores = NULL;

    printf("---ADICIONAR Livro---\n\n");
    printf("Digite os dados do livro:\n\n");

    printf("Titulo do livro: ");
    gets(novoLivro->titulo);

    printf("Editora do livro: ");
    gets(novoLivro->editora);

    printf("Ano do livro: ");
    scanf("%d", &novoLivro->ano);
    getchar();

    printf("Edicao do livro: ");
    scanf("%d", &novoLivro->edicao);
    getchar();

    novoLivro->identificador = *quantidade_livros + 1;
    *quantidade_livros = *quantidade_livros + 1;
    adicionar_autor(&novoLivro);

    novoLivro->prox = *livros;
    *livros = novoLivro;
}

void excluir_livro(Livro **livros)
{
    Livro *livro_atual = *livros;
    Livro *livro_anterior = NULL;
    int id, v=1;

    system("cls");

    printf("---EXCLUIR LIVRO---\n\n");
    printf("Digite o identificador do livro: ");
    scanf("%d", &id);
    getchar();

    while (livro_atual != NULL)
    {
        if (livro_atual->identificador == id)
        {
            v = 0;
            if (livro_anterior == NULL)
                *livros = livro_atual->prox;
            else
                livro_anterior->prox = livro_atual->prox; 
            liberar_autores(&livro_atual);
            free(livro_atual);
            break;
        }
        livro_anterior = livro_atual;
        livro_atual = livro_atual->prox;
    }

    if (v)
        printf("\nLivro nao encontrado\n");
    else
        printf("\nLivro excluido com sucesso\n");

    system("pause");
}

void editar_livro(Livro **livros)
{
    int id;

    system("cls");
    
    printf("---EDITAR LIVRO---\n\n");
    printf("Digite o identificador do livro: ");
    scanf("%d", &id);
    getchar();

    Livro *livro_atual = *livros;

    while (livro_atual != NULL)
    {
        if(livro_atual->identificador == id)
        {
            printf("\nTitulo atual: %s\n", livro_atual->titulo);
            printf("Digite o novo titulo do livro: ");
            gets(livro_atual->titulo);

            printf("\nEditora atual: %s\n", livro_atual->editora);
            printf("Digite a nova editora do livro: ");
            gets(livro_atual->editora);

            printf("\nAno atual: %d\n", livro_atual->ano);
            printf("Digite o novo ano do livro: ");
            scanf("%d", &livro_atual->ano);
            getchar();

            printf("\nEdicao atual: %d\n", livro_atual->edicao);
            printf("Digite a nova edicao do livro: ");
            scanf("%d", &livro_atual->edicao);
            getchar();

            editar_autores(&livro_atual);
            break;
        }
        *livro_atual = *livro_atual->prox;
    }
}

void imprimir_livros(Livro **livros)
{
    Livro *livro_atual = *livros;

    if (livro_atual == NULL)
    {
        printf("A lista de livros esta vazia.");
    }
    else
    {
        while (livro_atual != NULL)
        {
            printf("\nID: %d, Ano: %d, Edicao: %d, Titulo: %s, Editora: %s\n", livro_atual->identificador, livro_atual->ano, livro_atual->edicao, livro_atual->titulo, livro_atual->editora);
            imprimir_autores(&livro_atual);
            livro_atual = livro_atual->prox;
        }
        
    }
    system("pause");
}

void liberar_livros(Livro **livros) 
{
    Livro *livro_atual = *livros;
    Livro *prox_livro = NULL;

    while (livro_atual != NULL)
    {
        liberar_autores(&livro_atual);
        prox_livro = livro_atual->prox;
        free(livro_atual);
        livro_atual = prox_livro;
    }
}

void adicionar_autor(Livro **livro_sel)
{
    int quantidade;
    Livro *livro_atual = *livro_sel;
    Autor *autor_atual = livro_atual->autores;

    printf("Digite a quantidade de autores do livro: ");
    scanf("%d", &quantidade);
    getchar();

    for (int i = 1; i <= quantidade; i++)
    {
        autor_atual = malloc(sizeof(Autor));
        printf("Digite o nome do autor %d: ", i);
        gets(autor_atual->nome);
        autor_atual->prox = livro_atual->autores;
        livro_atual->autores = autor_atual;
    }
}

void imprimir_autores(Livro **livro_sel)
{
    Livro *livro_atual = *livro_sel;
    Autor *autor_atual = livro_atual->autores;
    printf("Autores:");
    while (autor_atual != NULL)
    {
        if(autor_atual->prox == NULL)
            printf(" %s", autor_atual->nome);
        else
            printf(" %s,", autor_atual->nome);
        autor_atual = autor_atual->prox;
    }
    printf("\n");
}   

void liberar_autores(Livro **livro_sel)
{
    Livro *livro_atual = *livro_sel;
    Autor *prox_autor = NULL;
    Autor *autor_atual = livro_atual->autores;

    while (autor_atual != NULL)
    {
        prox_autor = autor_atual->prox;
        free(autor_atual);
        autor_atual = prox_autor;
    }
    

}

void editar_autores(Livro **livro_sel)
{
    Livro *livro_atual = *livro_sel;
    Autor *autor_atual = livro_atual->autores;
    int cont = 1;
    while(autor_atual != NULL)
    {
        printf("Autor %d atual: %s\n", cont, autor_atual->nome);
        printf("Digite o novo nome do autor %d: ", cont);
        gets(autor_atual->nome);
        autor_atual = autor_atual->prox;
        cont++;
    }
}

void menu_reserva(Usuario **usuarios, Livro **livros, Reserva **reservas, int *quantidade_reservas)
{
     int escolha = 0;

    while (escolha != 4)
    {
        system("cls");

        printf("---RESERVAS---\n\n");
        printf("1 - Adicionar reserva\n");
        printf("2 - Editar reserva\n");
        printf("3 - Excluir reserva\n");
        printf("4 - Voltar\n\n");
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);
        getchar();

        switch (escolha)
        {
        case 1:
            adicionar_reserva();
            break;
        case 2:
            editar_reserva();
            break;
        case 3:
            excluir_reserva();
            break;
        case 4:
            break;
        default:
            printf("Opcao Invalida.\n");
            system("pause");
            break;
        }
    }
}

void adicionar_reserva()
{

}

void excluir_reserva()
{

}

void editar_reserva()
{

}

void imprimir_reservas()
{

}

void menu_relatorio(Usuario **usuarios, Livro **livros, Reserva **reservas)
{
    int escolha = 0;

    while (escolha != 4)
    {
        system("cls");
        printf("---RELATORIOS---\n\n");
        printf("1 - Listar usuarios\n");
        printf("2 - Listar livros\n");
        printf("3 - Listar reservas\n");
        printf("4 - Voltar\n\n");
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);
        getchar();

        switch (escolha)
        {
        case 1:
            // endereco de usuarios na main
            imprimir_usuarios(usuarios);
            break;
        case 2:
            imprimir_livros(livros);
            break;
        case 3:
            imprimir_reservas();
            break;
        }
    }
}
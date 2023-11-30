/*
    @Trabalho Lógica de Programação
    @Autores: Guilherme Lopes e João Manoel
    @Curso: Engenharia de Computação
    @Problema: Banco de Dados de uma Biblioteca
*/

// BIBLIOTECAS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// MACROS
#define MAX 75

// STRUCTS
typedef struct data
{
    int dia, mes, ano;
} Data;

typedef struct autor
{
    char nome[MAX];
    struct autor *prox;
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
    int identificador;
    char telefone[MAX];
    char nome[MAX];
    char endereco[MAX];
    struct usuario *prox;
} Usuario;

typedef struct reserva
{
    int identificador;
    Data inicio;
    Data fim;
    int id_livro;
    int id_usuario;
    struct reserva *prox;
} Reserva;

// PRÓTOTIPOS DAS FUNÇÕES
void menu(); // Função responsável por mostrar o menu principal

void menu_usuario();      // Função responsável por mostrar as opcoes sobre o que pode ser feito com os usuarios
void adicionar_usuario(); // Funcao para adicionar um usuario ao banco de dados
void excluir_usuario();   // Funcao para excluir um usuario ao banco de dados
void editar_usuario();    // Funcao para editar um usuario ao banco de dados
void liberar_usuarios();  // Desalocar a memoria alocada para a lista de usuarios

void menu_livro();      // Função responsável por mostrar as opcoes sobre o que pode ser feito com os livros
void adicionar_livro(); // Funcao para adicionar um livro ao banco de dados
void excluir_livro();   // Funcao para excluir um livro ao banco de dados
void editar_livro();    // Funcao para editar um livro ao banco de dados
void liberar_livros();  // Desalocar a memoria alocada para a lista de livros

void adicionar_autor(); // Funcao para adicionar um autor a um determinado livro
void editar_autores();  // Funcao para editar os autores de um livro do banco de dados
void liberar_autores(); // Desalocar a memoria alocada para a lista de autores

void menu_reserva();      // Função responsável por mostrar as opcoes sobre o que pode ser feito com as reservas
void adicionar_reserva(); // Funcao para adicionar uma reserva ao banco de dados
void excluir_reserva();   // Funcao para excluir uma reserva ao banco de dados
void editar_reserva();    // Funcao para editar uma reserva ao banco de dados
void liberar_reservas();

void menu_relatorio();    // Função responsável por mostrar as opções sobre as diferentes listagens que é possível fazer
void imprimir_usuarios(); // Funcao para listar os usuario do banco de dados
void imprimir_livros();   // Funcao para listar os livros do banco de dados
void imprimir_autores();  // Funcao para listar os autores de um determinado livro do banco de dados
void imprimir_reservas(); // Funcao para listar as reservas do banco de dados

int verificar_id_livro();
int verificar_id_usuario();

// MAIN
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
            menu_reserva(&usuarios, &livros, &reservas, &quantidade_reservas);
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
    liberar_reservas(&reservas);
    return 0;
}

// FUNÇÕES

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
    gets(novoUsuario->telefone);

    novoUsuario->identificador = *quantidade_usuarios + 1;
    *quantidade_usuarios = *quantidade_usuarios + 1;
    novoUsuario->prox = *usuarios;
    *usuarios = novoUsuario;
}

void excluir_usuario(Usuario **usuarios)
{
    int id, v = 1;

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
        if (usuario_atual->identificador == id)
        {
            printf("\nNome atual: %s\n", usuario_atual->nome);
            printf("Digite o novo nome do usuario: ");
            gets(usuario_atual->nome);

            printf("\nEndereco atual: %s\n", usuario_atual->endereco);
            printf("Digite o novo endereco do usuario: ");
            gets(usuario_atual->endereco);

            printf("\nTelefone atual: %s\n", usuario_atual->telefone);
            printf("Digite o novo telefone do usuario: ");
            gets(usuario_atual->telefone);

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
            printf("\nID: %d, Nome: %s, Endereco: %s, Telefone: %s\n", usuario_atual->identificador, usuario_atual->nome, usuario_atual->endereco, usuario_atual->telefone);
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

void menu_livro(Livro **livros, int *quantidade_livros)
{
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

    printf("---ADICIONAR LIVRO---\n\n");
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
    int id, v = 1;

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
        if (livro_atual->identificador == id)
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
        if (autor_atual->prox == NULL)
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
    while (autor_atual != NULL)
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
            adicionar_reserva(usuarios, livros, reservas, quantidade_reservas);
            break;
        case 2:
            editar_reserva(usuarios, livros, reservas);
            break;
        case 3:
            excluir_reserva(reservas);
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

int verificar_id_livro(Livro **livros, int id)
{
    Livro *atual = *livros;
    int verificar = 1; // falso se encontrar o ID
    while(atual != NULL)
    {
        if (atual->identificador == id)
        {
            verificar = 0;
            break;
        }
        atual = atual->prox;
    }
    if (verificar)
    {
        printf("ID invalido, digite novamente: ");
    }
    return verificar;
}

int verificar_id_usuario(Usuario **usuarios, int id)
{
    Usuario *atual = *usuarios;
    int verificar = 1; // falso se encontrar o ID
    while(atual != NULL)
    {
        if (atual->identificador == id)
        {
            verificar = 0;
            break;

        }
        atual = atual->prox;
    }
    if (verificar)
    {
        printf("ID invalido, digite novamente: ");
    }
    return verificar;
}

void adicionar_reserva(Usuario **usuarios, Livro **livros, Reserva **reservas, int *quantidade_reservas)
{
    system("cls");
    int id, tempo;
    Reserva *novaReserva = malloc(sizeof(Reserva));
    printf("---ADICIONAR RESERVA---\n\n");
    printf("Digite os dados da reserva:\n\n");

    printf("ID do livro reservado: ");
    do
    {
        scanf("%d", &id);
        getchar();
    } while (verificar_id_livro(livros, id));
    novaReserva->id_livro = id;

    printf("ID do usuario responsavel pela reserva: ");
    do
    {
        scanf("%d", &id);
        getchar();
    } while (verificar_id_usuario(usuarios, id));
    novaReserva->id_usuario = id;

    printf("Dia do inicio da reserva: ");
    scanf("%d", &tempo);
    getchar();
    novaReserva->inicio.dia = tempo;
    printf("Mes do inicio da reserva: ");
    scanf("%d", &tempo);
    getchar();
    novaReserva->inicio.mes = tempo;
    printf("Ano do inicio da reserva: ");
    scanf("%d", &tempo);
    getchar();
    novaReserva->inicio.ano = tempo;

    printf("Dia do fim da reserva: ");
    scanf("%d", &tempo);
    getchar();
    novaReserva->fim.dia = tempo;
    printf("Mes do fim da reserva: ");
    scanf("%d", &tempo);
    getchar();
    novaReserva->fim.mes = tempo;
    printf("Ano do fim da reserva: ");
    scanf("%d", &tempo);
    getchar();
    novaReserva->fim.ano = tempo;

    novaReserva->identificador = *quantidade_reservas + 1;
    *quantidade_reservas = *quantidade_reservas + 1;

    novaReserva->prox = *reservas;
    *reservas = novaReserva;
}

void excluir_reserva(Reserva **reservas)
{
    Reserva *reserva_atual = *reservas;
    Reserva *reserva_anterior = NULL;
    int id, v = 1;

    system("cls");

    printf("---EXCLUIR RESERVA---\n\n");
    printf("Digite o identificador da reserva: ");
    scanf("%d", &id);
    getchar();

    while (reserva_atual != NULL)
    {
        if (reserva_atual->identificador == id)
        {
            v = 0;
            if (reserva_anterior == NULL)
                *reservas = reserva_atual->prox;
            else
                reserva_anterior->prox = reserva_atual->prox;
            free(reserva_atual);
            break;
        }
        reserva_anterior = reserva_atual;
        reserva_atual = reserva_atual->prox;
    }

    if (v)
        printf("\nReserva nao encontrada\n");
    else
        printf("\nReserva excluida com sucesso\n");

    system("pause");
}

void editar_reserva(Usuario **usuarios, Livro **livros, Reserva **reservas)
{
    int id, id_temp;

    system("cls");

    printf("---EDITAR RESERVA---\n\n");
    printf("Digite o identificador da reserva: ");
    scanf("%d", &id);
    getchar();

    Reserva *reserva_atual = *reservas;

    while (reserva_atual != NULL)
    {
        if (reserva_atual->identificador == id)
        {
            printf("\nID do usuario atual: %d\n", reserva_atual->id_usuario);
            printf("Digite o novo ID do usuario responsavel pela reserva: ");
            do
            {
                scanf("%d", &id_temp);
                getchar();
            } while (verificar_id_usuario(usuarios, id_temp));
            reserva_atual->id_usuario = id_temp;

            printf("\nID do livro atual: %d\n", reserva_atual->id_livro);
            printf("Digite o novo ID do livro reservado: ");
            do
            {
                scanf("%d", &id_temp);
                getchar();
            } while (verificar_id_livro(livros, id_temp));
            reserva_atual->id_livro = id_temp;

            printf("\nDia do inicio da reserva atual: %d\n", reserva_atual->inicio.dia);
            printf("Digite o novo dia do inicio da reserva: ");
            scanf("%d", &reserva_atual->inicio.dia);
            getchar();

            printf("\nMEs do inicio da reserva atual: %d\n", reserva_atual->inicio.mes);
            printf("Digite o novo mes do inicio da reserva: ");
            scanf("%d", &reserva_atual->inicio.mes);
            getchar();

            printf("\nAno do inicio da reserva atual: %d\n", reserva_atual->inicio.ano);
            printf("Digite o novo ano do inicio da reserva: ");
            scanf("%d", &reserva_atual->inicio.ano);
            getchar();

            printf("\nDia do fim da reserva atual: %d\n", reserva_atual->fim.dia);
            printf("Digite o novo dia do inicio da reserva: ");
            scanf("%d", &reserva_atual->fim.dia);
            getchar();

            printf("\nMes do fim da reserva atual: %d\n", reserva_atual->fim.mes);
            printf("Digite o novo mes do inicio da reserva: ");
            scanf("%d", &reserva_atual->fim.mes);
            getchar();

            printf("\nAno do fim da reserva atual: %d\n", reserva_atual->fim.ano);
            printf("Digite o novo ano do inicio da reserva: ");
            scanf("%d", &reserva_atual->fim.ano);
            getchar();

            break;
        }
        *reserva_atual = *reserva_atual->prox;
    }
}

void imprimir_reservas(Reserva **reservas, Usuario **usuarios, Livro **livros)
{
    Reserva *reserva_atual = *reservas;
    Usuario *usuario_atual;
    Livro *livro_atual;
    if (reserva_atual == NULL)
    {
        printf("A lista de reservas esta vazia.\n");
    }
    else
    {
        while (reserva_atual != NULL)
        {
            livro_atual = *livros;
            usuario_atual = *usuarios;
            while (usuario_atual != NULL)
            {
                if (usuario_atual->identificador == reserva_atual->id_usuario)
                    break;
                usuario_atual = usuario_atual->prox;
            }
            while (livro_atual != NULL)
            {
                if (livro_atual->identificador == reserva_atual->id_livro)
                    break;
                livro_atual = livro_atual->prox;
            }
            printf("\nID reserva: %d, ID livro: %d, Titulo do livro: %s, ID usuario: %d, Nome do usuario: %s\n", reserva_atual->identificador, reserva_atual->id_livro, livro_atual->titulo, reserva_atual->id_usuario, usuario_atual->nome);
            printf("Data inicio: %02d/%02d/%04d, Data fim: %02d/%02d/%04d\n", reserva_atual->inicio.dia, reserva_atual->inicio.mes, reserva_atual->inicio.ano, reserva_atual->fim.dia, reserva_atual->fim.mes, reserva_atual->fim.ano);
            reserva_atual = reserva_atual->prox;
        }
    }
    system("pause");
}

void liberar_reservas(Reserva **reservas)
{
    Reserva *reserva_atual = *reservas;
    Reserva *prox_reserva = NULL;

    while (reserva_atual != NULL)
    {
        prox_reserva = reserva_atual->prox;
        free(reserva_atual);
        reserva_atual = prox_reserva;
    }
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
            imprimir_usuarios(usuarios);
            break;
        case 2:
            imprimir_livros(livros);
            break;
        case 3:
            imprimir_reservas(reservas, usuarios, livros);
            break;
        case 4:
            break;
        default:
            printf("Opcao Invalida.\n");
            system("pause");
        }
    }
}

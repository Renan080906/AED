#ifndef Sistema_h
#define Sistema_h
#include <stdio.h>

typedef struct{
    int codigo;
    char titulo[100];
    char autor[100];
    int anoPublicacao;
    int quantidadedisp;
} Biblioteca;

typedef struct {
    int codigoLivro;
    char nomeLeitor[100];
    char data[20]; // dd/mm/aaaa
} Emprestimo;

void limparTela();
int Lerinfo(Biblioteca *livro, int linhas, FILE *bib);
void cadastrarLivro(Biblioteca livro, FILE *arq);
void listarLivros(int linhas, FILE *arq);
void pesquisarPorAutor(char autorPesquisa[], FILE *arq);
void pesquisarPorTitulo(char tituloPesquisa[], FILE *arq);
void registrarEmprestimo(Emprestimo emprestimo, int codigoLivro, FILE *arqemp);
void registrarDevolucao(int codigoLivro, char Leitor[100], FILE *arq);
void relatorioEmprestimos();


#endif
#include "Sistema.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void removerLinhas(char *txt){
    txt[strcspn(txt, "\n")] = 0;
}

void limparTela(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void limparBuffer() { //Limpar buffer após scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int Lerinfo(Biblioteca *livro, int linhas, FILE *bib){
    Biblioteca *temp = malloc(linhas * sizeof(Biblioteca));
    for(int i = 0; i < linhas; i++){
    
    fscanf(bib, "%d;%[^;];%[^;];%d;%d\n",
           &temp[i].codigo,
           temp[i].titulo,
           temp[i].autor,
           &temp[i].anoPublicacao,
           &temp[i].quantidadedisp);
    }


    limparTela();

    printf("Digite o codigo do livro: ");
    scanf("%d", &livro->codigo);
    getchar();
    for(int i = 0; i < linhas; i++){
        if(livro->codigo == temp[i].codigo)
        {
            printf("Codigo ja existente!\n");
            free(temp);
            getchar();
            return 1;
        }
    }

    printf("Digite o titulo do livro: ");
    while(strcmp(fgets(livro->titulo, 100, stdin), "\n") == 0);
    printf("Digite o autor do livro: ");
    while(strcmp(fgets(livro->autor, 100, stdin), "\n") == 0);

    printf("Digite o ano de publicacao do livro: ");
    scanf("%d", &livro->anoPublicacao);
    for(int i = 0; i < linhas; i++){
        int tamanhoAno = snprintf(NULL, 0, "%d", livro->anoPublicacao);
        if(tamanhoAno != 4){
            printf("Ano de publicacao invalido! Digite um ano com 4 digitos.\n");
            free(temp);
            getchar();
            return 1;
        }
    }

    limparBuffer();
    printf("Digite a quantidade disponivel do livro: ");
    scanf("%d", &livro->quantidadedisp);
    limparBuffer();
    free(temp);
    return 0;
}

void cadastrarLivro(Biblioteca livro, FILE *arq){
    removerLinhas(livro.titulo);
    removerLinhas(livro.autor);

    fprintf(arq, "%d;%s;%s;%d;%d\n", livro.codigo, livro.titulo, livro.autor, livro.anoPublicacao, livro.quantidadedisp);
}

void pesquisarPorAutor(char autorPesquisa[], FILE *arq){
    int encontrado = 0, tamanhoau, tamanhoti, diferencaau, diferencati, i = 0;
    removerLinhas(autorPesquisa);
    Biblioteca livro;
    arq = fopen("biblioteca.txt", "r");

    printf("%-3s | %-3s | %*s%s%*s | %*s%s%*s | %-4s | %-10s\n", "ID", "Cod", 4, "", "Titulo", 5, "", 5, "", "Autor", 5, "", "Ano", "Quantidade");
    printf("------------------------------------------------------------------------\n");

    while(fscanf(arq, "%d;%[^;];%[^;];%d;%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.anoPublicacao, &livro.quantidadedisp) != EOF){
        if(strcmp(livro.autor, autorPesquisa) == 0){
            tamanhoau = strlen(livro.autor);
            tamanhoti = strlen(livro.titulo);
            diferencaau = 15 - tamanhoau;
            diferencati = 15 - tamanhoti;
            int esquerdaau = diferencaau / 2;
            int direitaau = diferencaau - esquerdaau;
            int esquedati = diferencati / 2;
            int direitoti = diferencati - esquedati;
            printf("%-3d | %-3d | %*s%s%*s | %*s%s%*s | %-4d | %-10d\n", i+1, livro.codigo, esquedati, "", livro.titulo, direitoti, "", esquerdaau, "", livro.autor, direitaau, "", livro.anoPublicacao, livro.quantidadedisp);
            encontrado = 1;
        }
        i++;
    }
    
    if(encontrado == 0){
        printf("Nenhum livro encontrado para o autor: %s\n", autorPesquisa);
        printf("Aperte enter para tentar novamente.\n");
    }

    fclose(arq);
}

void pesquisarPorTitulo(char tituloPesquisa[], FILE *arq){
    int encontrado = 0, tamanhoau, tamanhoti, diferencaau, diferencati, i = 0;
    removerLinhas(tituloPesquisa);
    Biblioteca livro;
    arq = fopen("biblioteca.txt", "r");

    printf("%-3s | %-3s | %*s%s%*s | %*s%s%*s | %-4s | %-10s\n", "ID", "Cod", 4, "", "Titulo", 5, "", 5, "", "Autor", 5, "", "Ano", "Quantidade");
    printf("------------------------------------------------------------------------\n");

    while(fscanf(arq, "%d;%[^;];%[^;];%d;%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.anoPublicacao, &livro.quantidadedisp) != EOF && encontrado != 1){
        if(strcmp(livro.titulo, tituloPesquisa) == 0){
            tamanhoau = strlen(livro.autor);
            tamanhoti = strlen(livro.titulo);
            diferencaau = 15 - tamanhoau;
            diferencati = 15 - tamanhoti;
            int esquerdaau = diferencaau / 2;
            int direitaau = diferencaau - esquerdaau;
            int esquedati = diferencati / 2;
            int direitoti = diferencati - esquedati;
            printf("%-3d | %-3d | %*s%s%*s | %*s%s%*s | %-4d | %-10d\n", i+1, livro.codigo, esquedati, "", livro.titulo, direitoti, "", esquerdaau, "", livro.autor, direitaau, "", livro.anoPublicacao, livro.quantidadedisp);
            encontrado = 1;
        }
        i++;
    }
    
    if(encontrado == 0){
        printf("Nenhum livro encontrado para o titulo: %s\n", tituloPesquisa);
        printf("Aperte enter para tentar novamente.\n");
    }

    fclose(arq);
}

void registrarEmprestimo(Emprestimo e, int codigoLivro, FILE *arqemp){
    Biblioteca livro;
    FILE *bib = fopen("biblioteca.txt", "r"); //abre os arquivos
    FILE *temp = fopen("temp.txt", "w"); //abre os arquivos
    int encontrado = 0;

    if(!bib || !temp){
        printf("Erro ao abrir arquivos.\n"); // erro caso não abrir os 2 com sucesso
        return;
    }

    // LER E COPIAR TODAS AS LINHAS
    while(fscanf(bib, "%d;%[^;];%[^;];%d;%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.anoPublicacao, &livro.quantidadedisp) != EOF){
        
        if(livro.codigo == codigoLivro){ // verificar se o exemplar com o codigo digitado existe
            encontrado = 1;

            if(livro.quantidadedisp == 0){
                printf("Livro sem exemplares disponiveis.\n");
                fclose(bib);
                fclose(temp);
                remove("temp.txt");
                return;
            }

            if(livro.quantidadedisp > 0){ // verificar se tem em estoque
                livro.quantidadedisp--;   // reduz 1 exemplar
            }

        }

        // escreve a linha (atualizada ou não)
        fprintf(temp, "%d;%s;%s;%d;%d\n", livro.codigo, livro.titulo, livro.autor, livro.anoPublicacao, livro.quantidadedisp);
    }

    fclose(bib); //fecha o arquivo
    fclose(temp); //fecha o arquivo
    
    if(!encontrado){ // caso o livro não for encontrado
        printf("Livro nao encontrado.\n");
        remove("temp.txt"); // remove o arquivo
        return; // retorna
    }
    
    // Atualiza o arquivo biblioteca
    remove("biblioteca.txt");
    rename("temp.txt", "biblioteca.txt");

    // Salva o empréstimo
    arqemp = fopen("emprestimos.txt", "a");
    fprintf(arqemp, "%d;%s;%s\n", codigoLivro, e.nomeLeitor, e.data);
    fclose(arqemp); // fecha o arquivo

    printf("Emprestimo registrado com sucesso!\n");
}

void registrarDevolucao(int codigoLivro, char Leitor[100], FILE *arq, int NumeroEmprestimos){
    FILE *tempArq;         // Arquivo temporário para reescrever os dados
    FILE *emp;
    FILE *tempEmp;           // Arquivo temporário para reescrever os empréstimos
    Biblioteca livro;      // Variável modelo struct Biblioteca
    Emprestimo emprestimo; // Variável modelo struct Emprestimo
    int encontrado = 0;    // marca se o livro existe
    int empre = 0;

    arq = fopen("biblioteca.txt", "r");
    emp = fopen("emprestimos.txt", "r"); 
    tempArq = fopen("temp.txt", "w");
    tempEmp = fopen("tempEmp.txt", "w");

    // Lê o arquivo linha por linha
    while(fscanf(arq, "%d;%[^;];%[^;];%d;%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.anoPublicacao, &livro.quantidadedisp) != EOF){

        while(fscanf(emp, "%d;%[^;];%[^;]\n", &emprestimo.codigoLivro, emprestimo.nomeLeitor, emprestimo.data) == NumeroEmprestimos){
            if(emprestimo.codigoLivro != codigoLivro && strcmp(emprestimo.nomeLeitor, Leitor) != 0){
                fprintf(tempEmp, "%d;%s;%s\n", emprestimo.codigoLivro, emprestimo.nomeLeitor, emprestimo.data);
            }
            else{
                empre = 1; // marca que o empréstimo existe
            }
        }

        // Se o código do livro for o mesmo que o usuário quer devolver
        if(livro.codigo == codigoLivro && empre == 1){
            livro.quantidadedisp++;  // devolução: aumenta 1
            encontrado = 1;  // marca que o livro existe
        }

        // Reescreve no arquivo temporário os dados atualizados
        fprintf(tempArq, "%d;%s;%s;%d;%d\n", livro.codigo, livro.titulo, livro.autor, livro.anoPublicacao, livro.quantidadedisp);
    }


    // Fecha arquivos
    fclose(arq);
    fclose(tempArq);
    fclose(emp);
    fclose(tempEmp);

    if(encontrado == 0){
        printf("Codigo nao encontrado, nenhuma devolucao realizada.\n");
        remove("temp.txt");  // não substituir o arquivo
        return;
    }

    // Substitui o arquivo original pelo atualizado
    remove("biblioteca.txt");
    rename("temp.txt", "biblioteca.txt");
    remove("emprestimos.txt");
    rename("tempEmp.txt", "emprestimos.txt");

    getchar();
}

void relatorioEmprestimos(){
    // Abre o arquivo de emprestimos salvos
    FILE *arq = fopen("emprestimos.txt", "r");

    // Se o arquivo não existir, não tem nenhum empréstimo registrado
    if(!arq){
        printf("Nenhum emprestimo registrado ainda.\n");
        return;
    }

    Emprestimo e;   // struct Emprestimo pra guardar temporariamente os dados
    int codigo;     // guarda o código do livro lido do arquivo

    printf("\n======= RELATORIO DE EMPRESTIMOS =======\n\n");

    while(fscanf(arq, "%d;%99[^;];%19[^\n]\n",
                 &codigo,
                 e.nomeLeitor,
                 e.data) != EOF){

        // Mostro os dados na tela
        printf("Codigo do livro: %d\n", codigo);
        printf("Nome do leitor: %s\n", e.nomeLeitor);
        printf("Data: %s\n", e.data);
        printf("-------------------------------------\n");
    }

    // Fecha o arquivo
    fclose(arq);

    printf("\n=============   FIM   =============\n\n");
}


void listarLivros(int linhas, FILE *arq){
    arq = fopen("biblioteca.txt", "r"); //abre o arquivo

    int codigo, anoPublicacao, quantidadedisp, tamanhoau, tamanhoti, diferencaau, diferencati;
    char titulo[100], autor[100];

    printf("%-3s | %-3s | %*s%s%*s | %*s%s%*s | %-4s | %-10s\n", "ID", "Cod", 4, "", "Titulo", 5, "", 5, "", "Autor", 5, "", "Ano", "Quantidade");
    printf("------------------------------------------------------------------------\n");

    for(int i = 0; i < linhas; i++)
    {   
        if(fscanf(arq, "%d;%[^;];%[^;];%d;%d\n", &codigo, titulo, autor, &anoPublicacao, &quantidadedisp) != EOF){
            tamanhoau = strlen(autor);
            tamanhoti = strlen(titulo);
            diferencaau = 15 - tamanhoau;
            diferencati = 15 - tamanhoti;
            int esquerdaau = diferencaau / 2;
            int direitaau = diferencaau - esquerdaau;
            int esquedati = diferencati / 2;
            int direitoti = diferencati - esquedati;
            printf("%-3d | %-3d | %*s%s%*s | %*s%s%*s | %-4d | %-10d\n", i+1, codigo, esquedati, "", titulo, direitoti, "", esquerdaau, "", autor, direitaau, "", anoPublicacao, quantidadedisp);
        }
    }

    fclose(arq);
}
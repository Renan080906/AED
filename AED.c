#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Sistema.h"

int main(){
    FILE *arq;
    Biblioteca p;
    int decisao;
    int sair = 1;
    int linhas = 0;
    char auxiliar[100];
    char tipo;
    int buscar = 0;
    int codigo = 0; // variavel apra pedir codigo do livro

    while(sair != 0)
    {    
        limparTela();
        printf("================MENU================\n");
        printf("1 -> Cadastrar novo livro\n");
        printf("2 -> Listar todos os livros\n");
        printf("3 -> Buscar livro\n");
        printf("4 -> Registrar emprestimo\n");
        printf("5 -> Registrar devolucao\n");
        printf("6 -> Relatorio de emprestimos\n");
        printf("7 -> Sair\n");
        scanf("%d", &decisao);
        getchar();


        switch (decisao)
        {
            case 1:
                linhas = 0;
                arq = fopen("biblioteca.txt", "r"); //abre para contar linhas
                while(fgets(auxiliar, sizeof(auxiliar), arq) != NULL)
                {
                    linhas++;
                }
                fclose(arq);
                arq = fopen("biblioteca.txt", "r");
                if(Lerinfo(&p, linhas, arq) == 0){
                    fclose(arq);
                    arq = fopen("biblioteca.txt", "a");
                    cadastrarLivro(p, arq);
                    fclose(arq);
                    limparTela();
                    printf("Livro cadastrado com sucesso!\n");
                    getchar();
                }
                break;
            case 2: // listar todos os livros
                limparTela();
                linhas = 0; // Não duplicar linhas

                arq = fopen("biblioteca.txt", "r"); //abre para contar linhas
                while(fgets(auxiliar, sizeof(auxiliar), arq) != NULL)
                {
                    linhas++;
                }
                fclose(arq);
                arq = fopen("biblioteca.txt", "r"); // Abre o arquivo para a leitura
                listarLivros(linhas, arq);
                fclose(arq);
                getchar();
                break;
            case 3: // Buscar livro
                
                buscar = 0;

                while(buscar != 1)
                {
                    limparTela();
                    printf("Pesquisar por (a)utor ou (t)itulo? ");
                    scanf(" %c", &tipo);
                    getchar();
                    if(tipo == 'a')
                    {
                        char autorPesquisa[100];
                        printf("Digite o nome do autor: ");
                        fgets(autorPesquisa, sizeof(autorPesquisa), stdin);
                        pesquisarPorAutor(autorPesquisa, NULL); // arquivo não esta aberto ainda
                        buscar = 1;
                    } 
                    else
                    { 
                        if(tipo == 't'){
                            char tituloPesquisa[100];
                            printf("Digite o titulo do livro: ");
                            fgets(tituloPesquisa, sizeof(tituloPesquisa), stdin);
                            pesquisarPorTitulo(tituloPesquisa, NULL); // arquivo não esta aberto ainda
                            buscar = 1;
                        }
                        else{
                            printf("Opcao invalida! Tente novamente.\n");
                        }
                    } 
                }
                getchar();
                break;
            case 4: // Registrar emprestimo
                limparTela();
                Emprestimo e; // variavel com o modelo do struct emprestimo

                printf("Codigo do livro: "); // pede o codigo do livro
                scanf("%d", &codigo);
                getchar(); // limpa o /n

                printf("Nome do leitor: "); // pede o nome do leitor
                fgets(e.nomeLeitor, 100, stdin);
                e.nomeLeitor[strcspn(e.nomeLeitor, "\n")] = 0; // remove o /n
                
                int correto = 0;
                while(correto != 1){
                    printf("Data (dd/mm/aaaa): "); // Pede a data do emprestimo para o Leitor
                    fgets(e.data, 20, stdin);
                    e.data[strcspn(e.data, "\n")] = 0; // Pede a data do emprestimo para o Leitor
                    if(strlen(e.data) != 10)
                    {
                        printf("Data invalida! Tente novamente.\n");
                    } 
                    else 
                    {
                        correto = 1;
                    }
                }

                // chama a função registrar Emprestimo
                registrarEmprestimo(e, codigo, NULL);
                getchar();
                limparTela();
                break;
            case 5: // Registrar devolução
                limparTela();
                printf("Codigo do livro para devolucao: "); 
                scanf("%d", &codigo);
                getchar();
                printf("Nome do Leitor: ");
                fgets(auxiliar, sizeof(auxiliar), stdin);
                auxiliar[strcspn(auxiliar, "\n")] = 0; // remove o /n

                // chama a função registrar Devolução
                registrarDevolucao(codigo, auxiliar, NULL);
                getchar();
                break;
            case 6:
                limparTela();
                relatorioEmprestimos();  // Chama a função de Relatorio
                getchar();
                break;
            case 7: // Sair
                sair = 0;
                break;
        }
    }

    return 0;
}
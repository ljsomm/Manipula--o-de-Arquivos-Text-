#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//Matrizes Char ou Vetores String para armazenar email e nome advindos do arquivo
char nome[3][20];
char email[3][30];

int equalStrings(const char *str1, const char *str2, long size){//Comparador de Strings (Parametros: string1, string2, tamanho)
    short bol = 1;
    for(int i = 0; i < size && (str1[i] != '\0' || str2[i] != '\0'); i++){
        if(str1[i] != str2[i]){
            bol = 0;
        }
    }
    return(bol);
}

void readOnlyNames(){//Le apenas os nomes
    FILE *arquivo;
    arquivo = fopen("arq.txt", "rt");
    for(int i = 0; i < 3; i++){
            fread(nome[i], 1 , sizeof(nome[i]), arquivo);
    }
    fclose(arquivo);
}

void readData(){//Le todos os dados
    FILE *arquivo;
    arquivo = fopen("arq.txt", "rt");
    for(int i = 0; i < 3; i++){
            fread(nome[i], 1 , sizeof(nome[i]), arquivo);
    }
    for(int i = 0; i < 3; i++){
            fread(email[i], 1 , sizeof(email[i]), arquivo);
    }
    fclose(arquivo);
}

void writeData(){ //função para escrever nos arquivos
    FILE *arquivo;
    arquivo = fopen("arq.txt", "wt");
    for(int i = 0; i < 3; i++){
            fwrite(nome[i], 1, sizeof(nome[i]), arquivo);
    }
    for(int i = 0; i < 3; i++){
            fwrite(email[i], 1, sizeof(email[i]), arquivo);
    }
    fclose(arquivo);
}

void errorSet(const char *e){ //mudar a tela para caso ocorra algum erro
    system("color 4");
    printf("\n\n-->ERRO: %s", e);
    getch();
    system("cls");
    system("color 7");
}

void main(){
    FILE *arquivo;
    char src_nm[20], src_email[30], src_letter;
    short bol, opt, menu;
    system("color 7");
    setlocale(LC_ALL, "portuguese");
    do{
        system("cls");
        printf("+++++++++++++++| SEJA BEM-VINDO! |+++++++++++++++\n\n1 – Entrada de dados\n2 – Lista todos os dados na tela\n3 – Pesquisa um nome e mostra na tela\n4 – Pesquisa os nomes pela 1ª Letra e mostra todos na tela\n5 – Altera dados\n6 – Exclui dados\n7 - Sair\n\nInsira sua opção--> ");
        scanf("%d", &menu);
        system("cls");
        switch(menu){
            case 1:
                printf("=== ENTRADA DE DADOS ===\n");
                getchar();
                for(int i = 0; i<3 ; i++){
                    printf("\nInsira o %dº Nome--> ", i+1);
                    gets(nome[i]);
                    printf("Insira o %dº E-mail--> ", i+1);
                    gets(email[i]);
                }
                writeData();
                printf("\n\n--Tecle algo para voltar ao menu--");
                getch();
                break;
            case 2:
                readData();
                printf("=== LISTAGEM DE TODOS OS DADOS ===\n\nNomes:\n\n");
                for(int i = 0; i < 3; i++){
                     printf("--> %s\n", nome[i]);
                }
                printf("\nE-mails:\n\n");
                for(int i = 0; i < 3; i++){
                     printf("--> %s\n", email[i]);
                }
                printf("\n\n--Tecle algo para voltar ao menu--");
                getch();
                break;
            case 3:
                readOnlyNames();
                printf("=== PESQUISE UM NOME ===\n\nInsira o nome a ser pesquisado--> ");
                getchar();
                gets(src_nm);
                for(int i = 0; i < 3; i++){
                    bol = 1;
                    for(int j = 0; j < 20 && (nome[i][j] != '\0' || src_nm[j] != '\0'); j++){
                        if(nome[i][j] != src_nm[j]){
                            bol = 0;
                        }
                    }
                    if(bol){
                        printf("\nEncontrado--> %s", nome[i]);
                    }
                }
                printf("\n\n--Tecle algo para voltar ao menu--");
                getch();
                break;
            case 4:
                readOnlyNames();
                bol = 1;
                do{
                    printf("=== PESQUISE UM NOME COM SUA 1ª LETRA ===\n\nInsira a 1ª letra do nome--> ");
                    scanf(" %c", &src_letter);
                    if(!(src_letter >= 65 && src_letter <= 90) && !(src_letter >= 97 && src_letter <= 122)){
                        errorSet("O caracter digitado não condiz com uma letra!");
                    }
                }while(!(src_letter >= 65 && src_letter <= 90) && !(src_letter >= 97 && src_letter <= 122));
                printf("\nNomes com a primeira letra '%c':\n", src_letter);
                for(int i = 0; i < 3; i++){
                    if(src_letter >= 65 && src_letter <= 90){
                        if(nome[i][0] == src_letter || nome[i][0] == src_letter+32){
                            printf("\nEncontrado--> %s", nome[i]);
                            bol = 0;
                        }
                    }
                    else if(src_letter >= 97 && src_letter <= 122){
                        if(nome[i][0] == src_letter || nome[i][0] == src_letter-32){
                            printf("\nEncontrado--> %s", nome[i]);
                            bol = 0;
                        }
                    }
                }
                if(bol){
                    printf("\n-->NENHUM NOME ENCONTRADO COM ESTA LETRA");
                }
                printf("\n\n--Tecle algo para voltar ao menu--");
                getch();
                break;
            case 5:
                readData();
                printf("=== ALTERAR DADOS ===\n\nO que deseja alterar:\n\n1 - Nome\n2 - E-mail\n\nOpção--> ");
                scanf("%d", &opt);
                getchar();
                switch(opt){
                    case 1:
                            //nome
                            printf("Inserir o nome a ser alterado--> ");
                            gets(src_nm);
                            for(int i = 0; i < 3; i++){
                                if(equalStrings(src_nm, nome[i], sizeof(nome[i]))){
                                    printf("Inserir o novo nome--> ");
                                    gets(nome[i]);
                                }
                            }
                        break;
                    case 2:
                            //email
                            printf("Inserir o e-mail a ser alterado--> ");
                            gets(src_email);
                             for(int i = 0; i < 3; i++){
                                if(equalStrings(src_email, email[i], sizeof(email[i]))){
                                    printf("Insira o novo email--> ");
                                    gets(email[i]);
                                }
                             }
                        break;
                }
                writeData();
                printf("\n\n--Tecle algo para voltar ao menu--");
                getch();
                break;
            case 6:
                readData();
                printf("=== EXCLUIR DADOS ===\n\nO que deseja excluir:\n\n1 - Nome\n2 - E-mail\n\nOpção--> ");
                scanf("%d", &opt);
                getchar();
                switch(opt){
                    case 1:
                        //nome
                        printf("Inserir o nome que deseja excluir--> ");
                        gets(src_nm);
                        for(int i = 0; i < 3; i++){
                            if(equalStrings(src_nm, nome[i],sizeof(nome[i]))){
                                nome[i][0] = '\0';
                            }
                        }
                        break;
                    case 2:
                        //email
                        printf("Inserir o e-mail que deseja excluir--> ");
                        gets(src_email);
                        for(int i = 0; i < 3; i++){
                            if(equalStrings(src_email, email[i], sizeof(email[i]))){
                                email[i][0] = '\0';
                                puts(email[i]);
                            }
                        }
                        break;
                }
                writeData();
                printf("\n\n--Tecle algo para voltar ao menu--");
                getch();
                break;
            case 7:
                system("color a");
                printf("OBRIGADO POR USAR NOSSO SOFTWARE!\nDesenvolvido pelo Grupo 4 (Lucas Juan Souza, Gabriel Domiciano e Gustavo Rezende)");
                getch();
                exit(0);
                break;
        }
    }while(menu != 7);
}

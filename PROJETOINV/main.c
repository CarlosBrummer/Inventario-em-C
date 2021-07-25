#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Locale.h>
#include <windows.h>

typedef struct inventario INV1;

struct inventario
    {
        char componente[30];
        int valor;
        char referencia[15];
        int quantidade;
    };

void cabecalho();
void descadastro();
void cadastro();
void lista();
void pesquisa();
void coloracao();

main()

{
    coloracao();
    int chd;
    do
    {
        cabecalho();
        printf("                                     \(1\) - Cadastrar\n");
        printf("                                     \(2\) - Excluir cadastro\n");
        printf("                                     \(3\) - Pesquisar \n");
        printf("                                     \(4\) - Listar componentes\n");
        printf("                                     \(5\) - Sair do software\n\n");
        printf("                                     \(?\) - Escolha uma opcao: ");
        scanf("%d",&chd);

        switch(chd)
        {

            case 1:
                cadastro();
            break;

            case 2:
                descadastro();
            break;

            case 3:
                pesquisa();
            break;

            case 4:
                lista();
            break;

            case 5:
                printf("\n                                     \>\>\>\>\> Saindo do software!\n");
                getch();
            break;

            default:
                printf("\n                                     \>\>\>\>\> Valor invalido!\n");
                getch();
            break;
        }
    }while(chd !=5 );

}
void cabecalho()
{
    system("cls");
    printf("--------------------------------------------------------------------------------------------\n");
    printf("\t\t                              MENU\n");
    printf("--------------------------------------------------------------------------------------------\n\n");
}
void cadastro()
{
    FILE* arquivo;
    INV1 ccc;
    int chd;

    arquivo = fopen("banco_de_dados.txt", "ab");

    if(arquivo == NULL)

        {
            printf("Problemas na abertura do arquivo\n\n");
        }

    else
        {
            do //loop de cadastro
            {

                cabecalho();

                fflush(stdin);
                printf("                                  \>\>\> Digite o componente: ");
                gets(ccc.componente);

                printf("                                  \>\>\> Digite o valor: ");
                scanf("%d",&ccc.valor);
                getchar();

                fflush(stdin);
                printf("                                  \>\>\> Digite o referencia: ");
                gets(ccc.referencia);

                printf("                                  \>\>\> Digite a quantidade: ");
                scanf("%d",&ccc.quantidade);
                getchar();

                fwrite(&ccc, sizeof(INV1), 1, arquivo); //salva no arquivo os dados passados anteriormente
                fflush(stdin);
                printf("\n                                  \(0\) - SAIR DO PROGRAMA\n");
                printf("                                  \(1\) - CONTINUAR COM CADASTRO ");
                scanf("%d",&chd);
                getchar();


            }while(chd!=0);

        fclose(arquivo);
        }

}

void lista()
{
   FILE* arquivo;
   INV1 ccc;
   arquivo = fopen("banco_de_dados.txt", "rb");

   cabecalho();

   if(arquivo == NULL)

    {
        printf("                                 Problemas na abertura do arquivo\n\n");
    }

   else
   {
    while(fread(&ccc, sizeof(INV1), 1,arquivo) == 1)
        {
            printf("\t                          \>\>\> Componente: %s\n",ccc.componente);
            printf("\t                          \>\>\> Valor: %d\n",ccc.valor);
            printf("\t                          \>\>\> Referencia: %s\n",ccc.referencia);
            printf("\t                          \>\>\> Quantidade: %d\n",ccc.quantidade);
            printf("\n--------------------------------------------------------------------------------------------\n\n");
        }

   }
   fclose(arquivo);
   getch();
}

void pesquisa()
{
    FILE* arquivo;
    INV1 ccc;
    char componente[30];

    arquivo = fopen("banco_de_dados.txt", "rb"); //arquivo em leitura para binário
    cabecalho();

    if(arquivo == NULL)
        {
            printf("Problemas na abertura do arquivo!\n");
        }
    else
        {
            fflush(stdin);
            printf("                                  Digite o componente a pesquisar: ");
            gets(componente);
            putchar('\n');

            while(fread(&ccc, sizeof(INV1), 1, arquivo) == 1)// leitura do arquivo
                    {
                        if(strcmp(componente, ccc.componente) == 0) // comparativo entre o componente solicitado por gets e o conteúdo de arquivo
                        {
                            printf("--------------------------------------------------------------------------------------------\n\n");
                            printf("\t                          \>\>\> Componente: %s\n",ccc.componente);
                            printf("\t                          \>\>\> Valor: %d\n",ccc.valor);
                            printf("\t                          \>\>\> Referencia: %s\n",ccc.referencia);
                            printf("\t                          \>\>\> Quantidade: %d\n",ccc.quantidade);
                            printf("\n--------------------------------------------------------------------------------------------\n\n");
                        }
                    }
        }
    fclose(arquivo);
    getch();
}

void descadastro()
{

    FILE* arq;
    FILE* temp;// aruivo temporário para repassar informaçoes atualizadas
    INV1 ccc;
    char componente[30];

    arq = fopen("banco_de_dados.txt","rb");//abrir em modo rb leitura binaria
    temp = fopen("ttt.txt","wb");//abrir em modo wb ele limpa e grava binario

    if(arq==NULL&&temp==NULL)//verifica se abriu corretamente
        {
            printf("Problemas na abertura do arquivo!\n");
            getch();
        }
    else
        {
            cabecalho();
            fflush(stdin);
            printf("                                  Digite o componente a deletar: ");
            gets(componente);// componente a comparar
            putchar('\n');

            while(fread(&ccc,sizeof(INV1),1,arq)==1) //leitura do *arq
                {
                    if(strcmp(componente,ccc.componente)==0) //comparacao entre o componente digitado e o salvo no arquivo *arq
                        {
                            printf("--------------------------------------------------------------------------------------------\n\n");
                            printf("\t                          \>\>\> Componente: %s\n",ccc.componente);
                            printf("\t                          \>\>\> Valor: %d\n",ccc.valor);
                            printf("\t                          \>\>\> Referencia: %s\n",ccc.referencia);
                            printf("\t                          \>\>\> Quantidade: %d\n",ccc.quantidade);
                            printf("\n--------------------------------------------------------------------------------------------\n");
                        }
                    else
                        {
                            fwrite(&ccc,sizeof(INV1),1,temp);//gravando os dados no arquivo temp
                        }
                }

            fclose(arq);//fechar o arq
            fclose(temp);//fechar o temp
            fflush(stdin);
            printf("\n                                  Deseja deletar (s/n)? ");

            if(getche()=='s')
                    {

                        if(remove("banco_de_dados.txt")==0&&rename("ttt.txt","banco_de_dados.txt")==0) // remover o arquivo "banco_de_dados.txt" e renomear o arquivo "ttt.txt" para "banco_de_dados.txt"
                            {
                                printf("\nOperacao realizada com sucesso!");
                            }
                        else
                            {
                                remove("ttt.txt");//remover o arquivo ttt se acondicao foi "n" na hora de deletar
                            }
                    }
            fclose(temp);
            fclose(arq);
            getch();
        }

}

void coloracao()
{
    system("color 09");
}

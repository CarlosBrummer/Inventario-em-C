#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Locale.h>
#include <windows.h>
#define master 999

typedef struct inventario INV1; //setando um apontador para a struct

struct inventario //struct do banco de dados
    {
        char componente[30]; // compontente, que sera usado como parametro de busca
        int valor;           // valor do componente
        char referencia[15]; // referencia do componente, por exemplo ohms para restistores
        int quantidade;      // quantidade do componente
    };

void cabecalho();
void descadastro();
void cadastro();
void lista();
void pesquisa();
void coloracao();

main()

{
    coloracao(); //setando a função de coloração
    int chd, senha, temporizacao; // chd é o comando para navegar no menu
    do // abertura de um menu com entrada para as funções
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
                {
                    putchar('\n');
                    printf("                                     DIGITE A SENHA MASTER PARA ACESSO! "); // SENHA 999
                    scanf("%d",&senha);

                if(senha == master)
                    {
                    descadastro();
                    }

                else
                    {
                        putchar('\n');
                        printf("                                     SENHA INVALIDA!");
                        for(temporizacao=0; temporizacao<1E9; temporizacao++);
                    }
                }
            break;

            case 3:
                pesquisa();
            break;

            case 4:
                lista();
            break;

            case 5:
                printf("\n                                     >>>>> Saindo do software!\n");
                getch();
            break;

            default:
                printf("\n                                     >>>>> Valor invalido!\n");
                getch();
            break;
        }
    }while(chd !=5 );

}
void cabecalho()
{
    system("cls");
    printf("--------------------------------------------------------------------------------------------\n");
    printf("\t\t                       BANCO DE COMPONENTES\n");
    printf("--------------------------------------------------------------------------------------------\n\n");
}
void cadastro()
{
    FILE* arquivo; // fazendo um ponteiro para a mémoria de em arquivo, que pode ser acessado via código fonte
    INV1 ccc;
    int chd;

    arquivo = fopen("banco_de_dados.txt", "ab"); // abrindo o arquivo

    if(arquivo == NULL)

        {
            printf("Problemas na abertura do arquivo\n\n"); // verificando nulidade
        }

    else
        {
            do //loop de cadastro
            {

                cabecalho();

                fflush(stdin);
                printf("                                  >>> Digite o componente: ");
                gets(ccc.componente); //incorporando a struct na variável componente

                printf("                                  >>> Digite o valor: ");
                scanf("%d",&ccc.valor); //incorporando a struct na variável valor
                getchar();

                fflush(stdin);
                printf("                                  >>> Digite o referencia: ");
                gets(ccc.referencia); //incorporando a struct na variável referencia

                printf("                                  >>> Digite a quantidade: ");
                scanf("%d",&ccc.quantidade); //incorporando a struct na variável quantidade
                getchar();

                fwrite(&ccc, sizeof(INV1), 1, arquivo); //salva no arquivo os dados passados anteriormente
                fflush(stdin);
                printf("\n                                  \(0\) - SAIR DO MENU DE CADASTRO\n");
                printf("                                  \(1\) - CONTINUAR COM CADASTRO ");
                scanf("%d",&chd);
                getchar();


            }while(chd!=0);

        fclose(arquivo); // saindo do arquivo *arq
        }

}

void lista()
{
   FILE* arquivo;
   INV1 ccc;
   arquivo = fopen("banco_de_dados.txt", "rb"); // abertura em leitura para binário

   cabecalho();

   if(arquivo == NULL)

    {
        printf("Problemas na abertura do arquivo\n\n");
    }

   else
   {
    while(fread(&ccc, sizeof(INV1), 1,arquivo) == 1) // lê os valores salvos nas estruturas
        {
            printf("\t                          >>> Componente: %s\n",ccc.componente);
            printf("\t                          >>> Valor: %d\n",ccc.valor);
            printf("\t                          >>> Referencia: %s\n",ccc.referencia);
            printf("\t                          >>> Quantidade: %d\n",ccc.quantidade);
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
    char componente[30]; //componente de comparação

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

            while(fread(&ccc, sizeof(INV1), 1, arquivo) == 1)// leitura do arquivo da struct
                    {
                        if(strcmp(componente, ccc.componente) == 0) // comparativo entre o componente solicitado por gets e o conteúdo de arquivo
                        {
                            printf("--------------------------------------------------------------------------------------------\n\n");
                            printf("\t                          >>> Componente: %s\n",ccc.componente);
                            printf("\t                          >>> Valor: %d\n",ccc.valor);
                            printf("\t                          >>> Referencia: %s\n",ccc.referencia);
                            printf("\t                          >>> Quantidade: %d\n",ccc.quantidade);
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
    char componente[30]; // arquivo de comparação para encontrar a struct dentro do arquivo

    arq = fopen("banco_de_dados.txt","rb");//abrir em modo rb leitura binaria
    temp = fopen("ttt.txt","wb");//abrir em wb para gravar binario

    if(arq==NULL&&temp==NULL)//verifica se abriu corretamente os dois arquivos
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

            // para descadastrar usei dois arquivos, em que salva tudo aquilo que não seja o componente desejado no arquivo temporario(2),
            // enquanto o principal continua igual, se o usuario realmente querer descadastrar, troco o arquivo principal pelo 2;
            // fazendo com que no arquivo esteja tudo menos o componente citado

            while(fread(&ccc,sizeof(INV1),1,arq)==1) //leitura do *arq
                {
                    if(strcmp(componente,ccc.componente)==0) //comparacao entre o componente digitado e o salvo no arquivo *arq
                        {
                            printf("--------------------------------------------------------------------------------------------\n\n");
                            printf("\t                          >>> Componente: %s\n",ccc.componente);
                            printf("\t                          >>> Valor: %d\n",ccc.valor);
                            printf("\t                          >>> Referencia: %s\n",ccc.referencia);
                            printf("\t                          >>> Quantidade: %d\n",ccc.quantidade);
                            printf("\n--------------------------------------------------------------------------------------------\n");
                        }
                    else
                        {
                            fwrite(&ccc,sizeof(INV1),1,temp);//gravando os dados sem a struct do compoente citado no arquivo temp
                        }
                }

            fclose(arq);//fechar o arq
            fclose(temp);//fechar o temp
            fflush(stdin);
            printf("\n                                  Deseja deletar (s/n)? ");

            if(getche()=='s')
                    {

                        if(remove("banco_de_dados.txt")==0&&rename("ttt.txt","banco_de_dados.txt")==0) // trocando os arquivos, removendo o 1 e renomeando o 2 para se tornar o 1
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
    system("color 09");// coloração podendo ser trocada no código fonte para valores até FF em hexa
}

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>

float PESO_MATERIAL_FECHAMENTO();
float CALC_ALVENARIA(float COMPRIMENTO, float H_ALVENARIA);
//float REVESTIMENTOS();

int main(){

float PD, COMPRIMENTO, ESPESSURA, H_VIGA, H_LAJE, H_ALVENARIA, PESO_ALVENARIA, TIPO_MATERIAL, AREA_TOTAL_ALVENARIA, VOLUME_ALVENARIA, PESO_TOTAL_REVESTIMENTO, REVESTIMENTOS, PESO_TOTAL_PAREDE;
int TIPO_VIGA;
char DESCONTAR_VIGA, OP, OP2;

setlocale(LC_ALL, "Portuguese"); //configura caracteres da língua portuguesa
printf("                    +-----------------------------------------------------------------------------+\n");
printf("                    |  Pontifícia Universidade Católica de Minas Gerais - campus Poços de Caldas  |\n");
printf("                    |              Ciência da Computação - Laboratório de AED II                  |\n");
printf("                    |                                                                             |\n");
printf("                    |  Projeto Final: Programa que Calcula a Carga Linear de Parade para          |\n");
printf("                    |  Auxiliar Profissionais da Construção Civil nos Calculos Estruturais        |\n");
printf("                    |  Alunos: João Marcelo Danza & Tuanne Assenço                                |\n");
printf("                    +-----------------------------------------------------------------------------+\n\n");
printf("\n   Aperte qualquer tecla para iniciar o programa...\n\n");
getchar();
system("cls");

OP = 'S';
OP2 = 'N';

while(OP == 'S')
{
    while(OP2 == 'N')
    {
        TIPO_MATERIAL = PESO_MATERIAL_FECHAMENTO(); //***Arquivo: Materiais_Alvenaria***
        printf("\n\n*OBS.: UTILIZAR VÍRGULA COMO SEPARADOR DECIMAL PARA A ENTRADA DAS DIMENSOES*");
        printf("\n\nQUAL O PE-DIREITO?: ");
        scanf("%f", &PD);

        printf("\nDESCONTAR ALTURA DA VIGA PARA O CALCULO DA ALVENARIA? (S-SIM, N-NAO): ");
        DESCONTAR_VIGA = toupper(getche());
        getchar();

        if (DESCONTAR_VIGA == 'S')
        {
                printf("\n\nQUAL A ALTURA DA VIGA?: ");
                scanf("%f", &H_VIGA);

                printf("\nQUAL O TIPO DE VIGA?\n\n");
                printf("1 - COM LAJE EMBUTIDA NA PARTE SUPERIOR\n");
                printf("2 - COM LAJE EMBUTIDA NA PARTE INFERIOR\n");
                printf("3 - COM LAJE APOIADA\n");
                printf("4 - VIGA INVERTIDA\n");
                printf("\nDigite sua opção: ");
                scanf("%d", &TIPO_VIGA);

                    switch (TIPO_VIGA)
                    {
                        case 1:
                        printf("\nQUAL A ALTURA DA LAJE?: ");
                        scanf("%f", &H_LAJE);
                        getchar();

                        H_ALVENARIA = PD - (H_VIGA - H_LAJE);
                        break;

                        case 2:
                        H_ALVENARIA = PD;
                        getchar();
                        break;

                        case 3:
                        H_ALVENARIA = PD - H_VIGA;
                        getchar();
                        break;

                        case 4:
                        H_ALVENARIA = PD;
                        getchar();
                        break;

                        default:
                        printf("OPCAO INVALIDA");
                        getchar();
                    }
        } else
            H_ALVENARIA = PD;

        OP2 = 'S';
    }
        printf("\n\nQUAL O COMPRIMENTO DA PAREDE?: ");
        scanf("%f", &COMPRIMENTO);
        getchar();

        printf("\nQUAL A ESPESSURA DA PAREDE (SOMENTE ALVENARIA)?: ");
        scanf("%f", &ESPESSURA);
        getchar();


        AREA_TOTAL_ALVENARIA = CALC_ALVENARIA(COMPRIMENTO, H_ALVENARIA); //***Arquivo: Alvenaria

        VOLUME_ALVENARIA = AREA_TOTAL_ALVENARIA*ESPESSURA;
        printf("\nVolume alvenaria: %.2f", VOLUME_ALVENARIA);

        //PESO_ALVENARIA = VOLUME_ALVENARIA*TIPO_MATERIAL/COMPRIMENTO;

        //printf("-------------------------------------------------");
        //printf("PESO DA ALVENARIA (kN/m) = ", PESO_ALVENARIA);
        //printf("-------------------------------------------------");

        //PESO_TOTAL_REVESTIMENTO = (REVESTIMENTOS()*AREA_TOTAL_ALVENARIA)/COMPRIMENTO; ***Arquivo: Revestimentos***
        //printf("*****PESO TOTAL DO REVESTIMENTO (kN/m)=", PESO_TOTAL_REVESTIMENTO);


        //PESO_TOTAL_PAREDE = PESO_ALVENARIA + PESO_TOTAL_REVESTIMENTO;
        //printf("************************************************");
        //printf("* PESO TOTAL DA PAREDE (kN/m)=", PESO_TOTAL_PAREDE);
        //printf("************************************************");

    printf("\n\nDESEJA EFETUAR OS CALCULOS PARA OUTRA PAREDE (S-SIM, N-NAO)\n");
    OP = toupper(getche());

    if (OP == 'S')
    {
    printf("\n\nDESEJA MANTER OS DADOS DO MATERIAL DA PAREDE, PE-DIREITO, ALTURA DA VIGA E LAJE ANTERIORMENTE INFORMADOS? (S-SIM, N-NAO)\n\n");
    OP2 = toupper(getche());
    printf("\n\n");
    }
}

return(0);
}

float PESO_MATERIAL_FECHAMENTO()
{
    //___   declaração de variáveis locais   ___//
    char OP;
    int OP_Material, i;

    typedef struct {
        int id;
        char nome[50];
        float peso;
    } sMat_Alvenaria;

    sMat_Alvenaria vMat_Alvenaria[3];

        vMat_Alvenaria[0].id = 1;
        strcpy(vMat_Alvenaria[0].nome, "Bloco de Concreto Vazado");
        vMat_Alvenaria[0].peso = 14;

        vMat_Alvenaria[1].id = 2;
        strcpy(vMat_Alvenaria[1].nome, "Tijolo Furado");
        vMat_Alvenaria[1].peso = 13;

        vMat_Alvenaria[2].id = 3;
        strcpy(vMat_Alvenaria[2].nome, "Tijolo Maciço");
        vMat_Alvenaria[2].peso = 18;

    //___   apresentação do menu de opções   ___//
    printf("Materiais cadastrados:\n\n");

    printf(" ID              Material           kN/m3");
    printf("\n________________________________________________\n");
    printf("\n");
        for(i = 0;i < 3; i++)
        {
            printf("%d.       ",vMat_Alvenaria[i].id);
            printf("%s         ",vMat_Alvenaria[i].nome);
            printf("%.2f\n", vMat_Alvenaria[i].peso);
        }

        printf("\n\nVocê deseja acrescentar outro material? (S-SIM, N-NAO): ");
        OP = toupper(getche());
        getchar();
        do
        {
            if(OP != 'S' && OP != 'N')
            {
                printf("Opção inválida, digite novamente sua opção: ");
                OP = toupper(getche());
            }
            if(OP == 'S')
            {
                //implementar a lista.(loading****)
            }
            else
            {
                system("cls");
                printf("Materiais cadastrados:\n\n");

                printf(" ID              Material           kN/m3");
                printf("\n________________________________________________\n");
                printf("\n");
                    for(i = 0;i < 3; i++)
                    {
                        printf("%d.       ",vMat_Alvenaria[i].id);
                        printf("%s         ",vMat_Alvenaria[i].nome);
                        printf("%.2f\n", vMat_Alvenaria[i].peso);
                    }
                printf("\n\nSelecione a sua opção: ");
                scanf("%d", &OP_Material);

            }
        }while (OP != 'S' && OP != 'N');

    getchar();
    return(vMat_Alvenaria[OP_Material-1].peso);
}

float CALC_ALVENARIA(float COMPRIMENTO, float H_ALVENARIA)
{
    float ABERTURA();

    float AREA_PARC_ALVENARIA, AREA_TOTAL_ALVENARIA, AREA_ABERTURAS;

    AREA_PARC_ALVENARIA = H_ALVENARIA*COMPRIMENTO;

    AREA_ABERTURAS = ABERTURA();

    AREA_TOTAL_ALVENARIA = AREA_PARC_ALVENARIA-AREA_ABERTURAS;

system("cls");
printf("-------------------------------------------------");
printf("\nAREA TOTAL DA ALVENARIA (m2)= %.2f", AREA_TOTAL_ALVENARIA);

return(AREA_TOTAL_ALVENARIA);
}

float ABERTURA()
{
    float B, H, AREA_ABERTURA, ABERTURA;
    char ABERT;

    printf("\nA PAREDE POSSUI ALGUMA ABERTURA? (S-SIM ; N-NAO): ");
    ABERT = toupper(getche());
    getchar();

    AREA_ABERTURA = 0;

    while(ABERT == 'S')
    {
        printf("\nDIGITE A MEDIDA DA BASE DA ABERTURA (m): ");
        scanf("%f", &B);
        getchar();
        printf("\nDIGITE A MEDIDA DA ALTURA DA ABERTURA (m): ");
        scanf("%f", &H);
        getchar();

        AREA_ABERTURA = AREA_ABERTURA + (B*H);

        printf("\nA PAREDE POSSUI MAIS ALGUMA ABERTURA? (S-SIM ; N-NAO): ");
        ABERT = toupper(getche());
        getchar();
    }

    return(AREA_ABERTURA);
}

    //chamada de bibliotecas para o funcionamento ideal do programa
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include "revestimentos.h"
#include "materiais.h"
#include "calculo_alvenaria.h"

    //declaração global do escopo de funções que o projeto utiliza
float peso_material_fechamento();    //função para retornar valor do peso do material escolhido pelo usuário
float revestimentos();    //função para retornar valor do peso de revestimento escolhido pelo usuário
float calc_alvenaria(float comprimento, float h_alvenaria);    //função para retornar o resultado do calculo da área total da alvenaria

int main()
{
    MessageBox(NULL, "       Pontifícia Universidade Católica de Minas Gerais - Poços de Caldas\n                       Ciência da Computação - Laboratório de AED II\n\n             Programa que Calcula a Carga Linear de Parede para Auxiliar                        Profissionais da Construção Civil nos Calculos Estruturais\n\n                               João Marcelo Danza & Tuanne Assenço", "Projeto Final", MB_OK);

        //declaração de variáveis locais utilizadas para o funcionamento do programa
    float pd, comprimento, espessura, h_viga, h_laje, h_alvenaria, peso_alvenaria, area_total_alvenaria, volume_alvenaria, peso_total_revestimento, peso_total_parede, tipo_material;
    int tipo_viga;
    char descontar_viga, op, op2, buf[1024];

    setlocale(LC_ALL, "Portuguese");    //configura caracteres da língua portuguesa
    op = 'S';
    op2 = 'N';

    while(op == 'S')
    {
        while(op2 == 'N')
        {
            tipo_material = peso_material_fechamento();    //*** Arquivo: materiais.h *** Código para inserção e seleção de materiais para a parede. Retorna o peso do material selecionado
            printf("\n\n\n *OBS.: UTILIZAR VÍRGULA COMO SEPARADOR DECIMAL PARA A ENTRADA DAS DIMENSOES*");
            printf("\n\n - Insira o valor do Pé-Direito (m): ");
            scanf("%f", &pd);

            printf("\n - Deseja DESCONTAR a altura da viga para o cálculo da alvenaria? (S-SIM ; N-NÃO): ");    //Possibilidade de descontar a altura da viga presente no topo da parede
            descontar_viga = toupper(getche());
            getchar();

            if (descontar_viga == 'S')
            {
                printf("\n\n - Qual a ALTURA da Viga? (m): ");
                scanf("%f", &h_viga);
                getchar();

                printf("\n   - Qual o TIPO de viga?\n\n");
                printf("   1 - Com laje embutida na parte superior\n");
                printf("   2 - Com laje embutida na parte inferior\n");
                printf("   3 - Com laje apoiada\n");
                printf("   4 - Viga invertida\n");
                printf("\n   Digite o número da sua opção: ");
                scanf("%d", &tipo_viga);

                switch (tipo_viga)
                {
                case 1:
                    printf("\n   - Qual a ALTURA da laje? (m): ");
                    scanf("%f", &h_laje);
                    getchar();

                    h_alvenaria = pd - (h_viga - h_laje);
                    break;

                case 2:
                    h_alvenaria = pd;
                    getchar();
                    break;

                case 3:
                    h_alvenaria = pd - h_viga;
                    getchar();
                    break;

                case 4:
                    h_alvenaria = pd;
                    getchar();
                    break;

                default:
                    printf("\n Opção inválida...");
                    getchar();
                }
            }
            else
                h_alvenaria = pd;

            op2 = 'S';
        }
        printf("\n\n - Qual o COMPRIMENTO da parede? (m): ");
        scanf("%f", &comprimento);
        getchar();

        printf("\n - Qual a ESPESSURA da parede (somente alvenaria)? (m): ");
        scanf("%f", &espessura);
        getchar();


        area_total_alvenaria = calc_alvenaria(comprimento, h_alvenaria);    //*** Arquivo: calculo_alvenaria.h *** Calcula a área total da alvenaria, caso haja alguma abertura na parede

        volume_alvenaria = area_total_alvenaria*espessura;
        peso_alvenaria = volume_alvenaria*tipo_material/comprimento;

        //Exibe os resultados obtidos em uma MessageBox
        snprintf(buf, 1024, "Área total da alvenaria (m2) = %.2f\nVolume alvenaria (m3) = %.2f\nPeso da alvenaria (kN/m) = %.2f",area_total_alvenaria, volume_alvenaria, peso_alvenaria);
        MessageBox(NULL, buf, "Alvenaria", MB_OK);

        printf("\n\n-------------------------------------------------");
        printf("\n Área total da alvenaria (m2) = %.2f", area_total_alvenaria);
        printf("\n-------------------------------------------------");

        printf("\n-------------------------------------------------\n");
        printf(" Volume alvenaria (m3) = %.2f", volume_alvenaria);
        printf("\n-------------------------------------------------");

        printf("\n-------------------------------------------------\n");
        printf(" Peso da alvenaria (kN/m) = %.2f", peso_alvenaria);
        printf("\n-------------------------------------------------");

        printf("\n\n Pressione ENTER para informar os REVESTIMENTOS...");
        getchar();

        peso_total_revestimento = (revestimentos()*area_total_alvenaria)/comprimento;    //*** Arquivo: revestimentos.h *** Código para inserção e seleção de revestimentos para a parede. Retorna o peso dos revestimentos selecionados

        //Exibe os resultados obtidos em uma MessageBox
        snprintf(buf, 1024, "Peso total do revestimento (kN/m) = %.2f", peso_total_revestimento);
        MessageBox(NULL, buf, "Revestimento", MB_OK);

        printf("\n\n-------------------------------------------------\n");
        printf(" Peso total do revestimento (kN/m) = %.2f", peso_total_revestimento);
        printf("\n-------------------------------------------------");
        getchar();

        system("cls");
        peso_total_parede = peso_alvenaria + peso_total_revestimento;   //variável que recebe o peso total da parede (material + revestimentos)

        //Exibe os resultados obtidos em uma MessageBox
        snprintf(buf, 1024, "Peso total da parede (kN/m) = %.2f", peso_total_parede);
        MessageBox(NULL, buf, "Resultado", MB_OK);

        printf(" ************************************************\n");
        printf(" *      Peso total da parede (kN/m) = %.2f      *", peso_total_parede);    //Valor do peso total da parede por metro linear (Resultado e objetivo do Programa)
        printf("\n ************************************************\n");

        printf("\n\n Deseja efetuar os cálculos para outra parede? (S-SIM, N-NAO): ");
        op = toupper(getche());

        if (op == 'S')
        {
            printf("\n\nDeseja manter os dados do material da parede, pé-direito, altura da viga e laje anteriormente informados? (S-SIM, N-NAO)\n\n");
            op2 = toupper(getche());
            printf("\n\n");
        }
    }

    //Exibe uma mensagem ao término da execução em uma MessageBox
    MessageBox(NULL, "Agradecemos por utilizar nosso programa!", "Projeto Final", MB_OK);

    return (0);
}

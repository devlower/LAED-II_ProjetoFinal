typedef struct sMat_Revest
{
    int id;    //codigo do revestimento
    float peso;    //peso do revestimento
    char nome[50];    //nome do revestimento
    struct sMat_Revest *proximo;    //proximo elemento da lista encadeada de revestimentos
}  TsMat_Revest;

void inserirMatRevest(TsMat_Revest **inicio, int cont);
void listarMatRevest(TsMat_Revest *inicio);
float selecaoMatRevest(TsMat_Revest *inicio);
int cont;

float revestimentos()
{
    TsMat_Revest *inicio = NULL;        //Ponteiro para a inicio da lista
    TsMat_Revest *noatual;               //Ponteiro a ser usado para percorrer a lista
    char op;                            //guarda a op��o do usu�rio para o switch case:

    for(cont=1; cont<5; cont++)
    {
        inserirMatRevest(&inicio,cont);     //Fun��o que insere revestimentos em uma lista default para exibi��o ao usu�rio
    }
    cont--;

    do
    {
        system("cls");
        printf(" Lista de revestimentos cadastrados no sistema:");
        listarMatRevest(inicio);
        printf("\n\n - Se voc� desejar INSERIR mais algum material - Digite (I)");
        printf("\n - Se voc� deseja SELECIONAR o tipo de material - Digite (S)");
        printf("\n\n Sua op��o: ");
        op = toupper(getche());    //le a opcao do usuario
        switch(op)
        {
        case 'I':
            cont++;
            inserirMatRevest(&inicio, cont);    //Fun��o que permite que o usu�rio insira mais revestimentos na lista default
            break;

        case 'S':
            return(selecaoMatRevest(inicio));   //retorna o peso do revestimento selecionado para a fun��o principal (main)
            break;  

        default:
            printf("\n\nOp��o inv�lida...\n\n");
            getchar();
        }
        fflush(stdin);    //limpa o buffer de entrada
    }
    while (op != 'S');

    //desaloca a memoria alocada para os elementos da lista
    noatual = inicio;
    while (noatual != NULL)
    {
        inicio = noatual->proximo;
        free(noatual);
        noatual = inicio;
    }
}

//lista todos os elementos presentes na lista encadeada
void listarMatRevest (TsMat_Revest *noatual)
{
    printf("\n\n ID                 Revestimento                 Peso (kN)\n");
    printf("________________________________________________________________");
    while(noatual != NULL)    //enquanto nao chega no fim da lista
    {
        printf("\n %d.                  %s                     %.2f kN", noatual->id, noatual->nome, noatual->peso);
        noatual = noatual->proximo;    //faz noatual apontar para o proximo no
    }
}

//fun��o para inserir um novo no, ao final da lista
void inserirMatRevest (TsMat_Revest **inicio, int CONT)
{
    TsMat_Revest *noatual, *novono;
    int cod;
    float peso;
    char nome[50];

    if (*inicio == NULL && CONT==1)     //se ainda n�o existe nenhum revestimento na lista default
    {
        cod=1;
        strcpy(nome, "Chapisco");
        peso=19;

        //cria o no inicio e insere os dados do primeiro revestimento
        *inicio = (TsMat_Revest *) malloc(sizeof(TsMat_Revest));
        (*inicio)->id = cod;
        strcpy((*inicio)->nome, nome);
        (*inicio)->peso = peso;
        (*inicio)->proximo = NULL;
    }

    if(CONT>1 && CONT<5)    //cria mais 3 n�s na lista e insere os dados dos revestimentos para exibi��oo ao usu�rio
    {
        if(CONT==2)
        {
            cod=2;
            strcpy(nome, "Embo�o");
            peso=19;
        }

        if(CONT==3)
        {
            cod=3;
            strcpy(nome, "Reboco");
            peso=19;
        }

        if(CONT==4)
        {
            cod=4;
            strcpy(nome, "Argamassa + Azulejo");
            peso=40;
        }

        noatual = *inicio;
        while(noatual->proximo != NULL)
            noatual = noatual->proximo;    //ao final do while, noatual aponta para o ultimo no

        novono = (TsMat_Revest *) malloc(sizeof(TsMat_Revest));    //aloca mem�ria para o novo n� e depois ocorre a inser��o dos dados do revestimento
        novono->id = cod;
        strcpy(novono->nome, nome);
        novono->peso = peso;
        novono->proximo = NULL;
        noatual->proximo = novono;    //faz o ultimo no apontar para o novo no
    }

    //se ja existem elementos na lista, deve percorre-la at� o seu final e inserir o novo elemento
    if(CONT>4)
    {
        //atribui um codigo sequencial ao revestimento que ser� cadastrado pelo usu�rio e solicita a inser��o dos dados
        cod=CONT;
        getchar();
        printf("\n Nome do revestimento: ");
        gets(nome);
        printf("\n Peso do revestimento(kN): ");
        scanf("%f", &peso);
        getchar();

        noatual = *inicio;
        while(noatual->proximo != NULL)
            noatual = noatual->proximo;    //ao final do while, noatual aponta para o ultimo no
        novono = (TsMat_Revest *) malloc(sizeof(TsMat_Revest));    //aloca memoria para o novo no e depois ocorre a inser��o dos dados do revestimento
        novono->id = cod;
        strcpy(novono->nome, nome);
        novono->peso = peso;
        novono->proximo = NULL;
        noatual->proximo = novono;    //faz o ultimo no apontar para o novo n�, possibilitando a inser��o de novos revestimentos pelo usu�rio
    }
}

float selecaoMatRevest (TsMat_Revest *noatual)  //Fun��o que permite a sele��o dos revestimentos que ser�o utilizados nos c�lculos
{
    float peso_parc_revest = 0;
    float esp_revest = 0;
    char continuar = 'S', lados;
    int revestID, n_lados;
    TsMat_Revest *primeiroNo;       //ponteiro para o primeiro n� da lista de materiais

    primeiroNo = noatual;           //guarda o endere�o do primeiro no atual, que aqui � o primeiro da lista, na variavel primeiroNo, que ser� uilizado na recursividade da fun��o

    while(continuar == 'S')     //Permite ao usu�rio a utiliza��o de m�ltiplos revestimentos � parede
    {
        noatual = primeiroNo;

        listarMatRevest(primeiroNo); //chama novamente a fun��o que lista os revestimentos para nova escolha, caso o usu�rio digite um ID que n�o consta na lista

        printf("\n\n - Selecione o revestimento pelo n�medo do seu ID: ");
        scanf("%d", &revestID);

        while(noatual != NULL && noatual->id != revestID)    //enquanto nao chega no fim da lista e n�o encontra o revestimento selecionado pelo usu�rio
        {
            noatual = noatual->proximo;
        }

        if(noatual == NULL)     //Caso o ID informado pelo usu�rio n�o seja encontrado, exibe a mensagem 
        {
        printf("\nMaterial n�o existente ou n�o cadastrado.");  
        noatual = primeiroNo;                                      //Redefine o n� atual (que estava no fim da lista) novamente como o primeiro
        selecaoMatRevest (primeiroNo);       //chama a fun��o sele��o recursivamente at� o usu�rio informar um ID de revestimento existente na lista
        }

        system("cls");
        printf("Material selecionado: \n\n ID: %d.      Material: %s      Peso: %.2f kN", noatual->id, noatual->nome, noatual->peso);

        if (revestID == 4)
            esp_revest = 1;
        else
        {
            printf("\n\n - Qual a espessura do Revestimento(cm)?: ");
            scanf("%f", &esp_revest);

            printf("\n - O revestimento ser� utilizado nos dois lados da parede? (S-SIM, N-NAO): ");
            lados = toupper(getche());
            getchar();

            if (lados == 'S')
                n_lados = 2;

            else
                n_lados = 1;

        }
        peso_parc_revest = peso_parc_revest + ((noatual->peso)*(esp_revest/100)*(n_lados));
        printf("\n\n - Deseja aplicar outro Revestimento? (S-SIM ; N-NAO): ");
        continuar = toupper(getche());
        getchar();
        noatual = noatual->proximo;
    }

    return (peso_parc_revest);      //retorna o peso parcial dos revestimentos escolhidos para a fun��o principal (main)
}

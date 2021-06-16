typedef struct sMat_Alvenaria
{
    int id;    //codigo do material
    float peso;    //peso do material
    char nome[50];    //nome do material
    struct sMat_Alvenaria *proximo;    //proximo elemento da lista encadeada de materiais
}  TsMat_Alvenaria;

void inserirMatParede(TsMat_Alvenaria **inicio, int cont);
void listarMatParede(TsMat_Alvenaria *inicio);
float selecaoMatParede(TsMat_Alvenaria *inicio);
int cont;

float peso_material_fechamento()
{
    TsMat_Alvenaria *inicio = NULL;    //ponteiro para o inicio da lista
    TsMat_Alvenaria *noatual;    //ponteiro a ser usado para percorrer a lista no momento de desalocar seus elementos
    char op;    //guarda a opção do usuário para o switch case:

    for(cont=1; cont<4; cont++)
    {
        inserirMatParede(&inicio,cont);
    }
    cont--;

    do
    {
        system("cls");
        printf(" Lista de materiais cadastrados no sistema:");
        listarMatParede(inicio);
        printf("\n\n - Se você desejar INSERIR mais algum material - Digite (I)");
        printf("\n - Se você deseja SELECIONAR o tipo de material - Digite (S)");
        printf("\n\n Sua opção: ");
        op = toupper(getche());    //le a opcao do usuario
        switch(op)
        {
        case 'I':
            cont++;
            inserirMatParede(&inicio, cont);
            break;

        case 'S':
            return(selecaoMatParede(inicio));
            break;  //retorna o peso do material selecionado para a função principal (main)

        default:
            printf("\n\nOpção inválida...\n\n");
            getchar();
        }
        fflush(stdin);    //limpa o buffer de entrada
    }
    while (op != 'S' );

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

void listarMatParede (TsMat_Alvenaria *noatual)
{
    printf("\n\n ID                 Material                 Peso (kN)\n");
    printf("________________________________________________________________\n");
    while(noatual != NULL)    //enquanto nao chega no fim da lista
    {
        printf("\n %d.            %s               %.2f kN", noatual->id, noatual->nome, noatual->peso);
        noatual = noatual->proximo;    //faz noatual apontar para o proximo no
    }
}

    //funcao para inserir um novo no, ao final da lista

void inserirMatParede (TsMat_Alvenaria **inicio, int CONT)
{
    TsMat_Alvenaria *noatual, *novono;
    int cod;
    float peso;
    char nome[50];

    if (*inicio == NULL && CONT==1)    //se ainda nao existe nenhum material na lista
    {
        cod=1;
        strcpy(nome, "Bloco de Concreto Vazado");
        peso=14;

            //cria o no inicio
        *inicio = (TsMat_Alvenaria *) malloc(sizeof(TsMat_Alvenaria));
        (*inicio)->id = cod;
        strcpy((*inicio)->nome, nome);
        (*inicio)->peso = peso;
        (*inicio)->proximo = NULL;

    }

    if(CONT>1 && CONT<4)
    {
        if(CONT==2)
        {
            cod=2;
            strcpy(nome, "Tijolo Furado");
            peso=13;
        }

        if(CONT==3)
        {
            cod=3;
            strcpy(nome, "Tijolo Macico");
            peso=18;
        }

        noatual = *inicio;
        while(noatual->proximo != NULL)
            noatual = noatual->proximo;    //ao final do while, noatual aponta para o ultimo no

        novono = (TsMat_Alvenaria *) malloc(sizeof(TsMat_Alvenaria));    //aloca memoria para o novo no
        novono->id = cod;
        strcpy(novono->nome, nome);
        novono->peso = peso;
        novono->proximo = NULL;
        noatual->proximo = novono;    //faz o ultimo no apontar para o novo no
    }

        //se ja existem elementos na lista, deve percorre-la ate' o seu final e inserir o novo elemento

    if(CONT>3)
    {
            //atribui um codigo sequencial ao material cadastrado
        cod=CONT;
        getchar();
        printf("\n Nome do material: ");
        gets(nome);
        printf("\n Peso do material(kN): ");
        scanf("%f", &peso);
        getchar();

        noatual = *inicio;
        while(noatual->proximo != NULL)
            noatual = noatual->proximo;    //ao final do while, noatual aponta para o ultimo no
        novono = (TsMat_Alvenaria *) malloc(sizeof(TsMat_Alvenaria));    //aloca memoria para o novo no
        novono->id = cod;
        strcpy(novono->nome, nome);
        novono->peso = peso;
        novono->proximo = NULL;
        noatual->proximo = novono;    //faz o ultimo no apontar para o novo no
    }
}

float selecaoMatParede (TsMat_Alvenaria *noatual)
{
    int matID;

    printf("\n\n - Selecione o material pelo númedo do seu ID: ");
    scanf("%d", &matID);

    while(noatual != NULL)    //enquanto nao chega no fim da lista
    {
        if(noatual->id == matID)
        {
            system("cls");
            printf(" Material selecionado: \n\n ID: %d.      Material: %s      Peso: %.2f kN", noatual->id, noatual->nome, noatual->peso);
            return (noatual->peso);
        }
        noatual = noatual->proximo;    //faz noatual apontar para o proximo no
    }
}

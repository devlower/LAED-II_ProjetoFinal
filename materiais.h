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
    TsMat_Alvenaria *noatual;    //ponteiro a ser usado para percorrer a lista
    char op;    //guarda a opção do usu?rio para o switch case:

    for(cont=1; cont<4; cont++)
    {
        inserirMatParede(&inicio,cont); //Fun??o que insere materiais em uma lista default para exibi??o ao usu?rio
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
            inserirMatParede(&inicio, cont);    //Fun??o que permite que o usu?rio insira mais materiais na lista default
            break;

        case 'S':
            return(selecaoMatParede(inicio));   //retorna o peso do material selecionado para a fun??o principal (main)
            break;  

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

    if (*inicio == NULL && CONT==1)    //se ainda n?o existe nenhum material na lista default
    {
        cod=1;
        strcpy(nome, "Bloco de Concreto Vazado");
        peso=14;

        //cria o no inicio e insere os dados do primeiro material
        *inicio = (TsMat_Alvenaria *) malloc(sizeof(TsMat_Alvenaria));
        (*inicio)->id = cod;
        strcpy((*inicio)->nome, nome);
        (*inicio)->peso = peso;
        (*inicio)->proximo = NULL;

    }

    if(CONT>1 && CONT<4)    //cria mais 2 n?s na lista e insere os dados dos materiais para exibi??o ao usu?rio
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
            strcpy(nome, "Tijolo Maci?o");
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

    //se ja existem elementos na lista, deve percorre-la at? o seu final e inserir o novo elemento
    if(CONT>3)
    {
        //atribui um codigo sequencial ao material que ser? cadastrado pelo usu?rio e solicita a inser??o dos dados
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
        novono = (TsMat_Alvenaria *) malloc(sizeof(TsMat_Alvenaria));    //aloca mem?ria para o novo n? e depois ocorre a inser??o dos dados do material
        novono->id = cod;
        strcpy(novono->nome, nome);
        novono->peso = peso;
        novono->proximo = NULL;
        noatual->proximo = novono;    //faz o ultimo no apontar para o novo n?, possibilitando a inser??o de novos materiais pelo usu?rio
    }
}

float selecaoMatParede (TsMat_Alvenaria *noatual)   //Fun??o que permite a sele??o do material que ser? utilizado nos c?lculos
{
    int matID;

    printf("\n\n - Selecione o material pelo n?mero do seu ID: ");
    scanf("%d", &matID);

    while(noatual != NULL)    //enquanto nao chega no fim da lista
    {
        if(noatual->id == matID)    //condi??o para que o n? que possui o ID do material selecionado pelo usu?rio seja encontrado
        {
            system("cls");
            printf(" Material selecionado: \n\n ID: %d.      Material: %s      Peso: %.2f kN", noatual->id, noatual->nome, noatual->peso);
            return (noatual->peso); //retorna o peso do material escolhido para a fun??o principal (main)
        }
        noatual = noatual->proximo;    //faz noatual apontar para o proximo n?, caso o n? que possui o ID do material selecionado pelo usu?rio ainda n?o tenha sido encontrado
    }
}

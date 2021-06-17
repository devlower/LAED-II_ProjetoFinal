float calc_alvenaria(float comprimento, float h_alvenaria)
{
    float abertura();

    float area_parc_alvenaria, area_total_alvenaria, area_aberturas;

    area_parc_alvenaria = h_alvenaria*comprimento;

    area_aberturas = abertura();

    area_total_alvenaria = area_parc_alvenaria-area_aberturas;

    return(area_total_alvenaria);   //retorna a área total da alvenaria, com o desconto da área de alguma abertura para a função principal (main)
}

float abertura()    //Função que desconta a ?rea de uma abertura presente na parede
{
    float b, h, area_abertura;
    char op;

    printf("\n - A parede possui alguma ABERTURA? (S-SIM ; N-NAO): ");
    op = toupper(getche());
    getchar();

    area_abertura = 0;

    while(op == 'S')
    {
        printf("\n - Digite a medida da BASE da abertura (m): ");
        scanf("%f", &b);
        getchar();
        printf("\n - Digite a medida da ALTURA da abertura (m): ");
        scanf("%f", &h);
        getchar();

        area_abertura = area_abertura + (b*h);

        printf("\n - A parede possui mais alguma abertura? (S-SIM ; N-NAO): ");
        op = toupper(getche());
        getchar();
    }

    return(area_abertura);
}

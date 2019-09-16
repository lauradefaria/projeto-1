#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#define ESC 27
#define CIMA 72
#define BAIXO 80
#define ENTER 13
#define QNT_IMOVEIS 101
#define FLUSH fflush(stdin)
int escolha;

typedef struct{ //struct com atributos bem genericos pra poder armazenar os 3 tipos de imoveis
	char tituloImovel[QNT_IMOVEIS], endereco[51], bairro[31], cidade[31],  posicao[26];
	int numero, CEP, pavimentos, numeroQuartos, andar, numVagasGaragem, tipo, tipoPagamento, disponibilidade;  //se disponibilidade == 0 esta disponivel, se == 1 esta ocupado
	double  valor, valorCondominio, areaTerreno, areaConstruida;
}tImovel;

//array do tipo tImovel para ser os imoveis disponiveis na imobiliaria
tImovel casas[QNT_IMOVEIS];
tImovel apartamentos[QNT_IMOVEIS];
tImovel terrenos[QNT_IMOVEIS];
void iniciador(void){
	char caracter;
	int i, j, k, contador = 0, flag;

	FILE *casasPtr;
	FILE *apartamentosPtr;
	FILE *terrenosPtr;

	printf("\t\t\tAguarde...\n");

	if((casasPtr = fopen("casas.txt", "r")) == NULL)
		printf("Arquivo nao encontrado");
	else{
		i = 0;
		while(!feof(casasPtr)){
			fgets(casas[i].tituloImovel, 101, casasPtr);
			fgets(casas[i].cidade, 30, casasPtr);
			fgets(casas[i].bairro, 30, casasPtr);
			fgets(casas[i].endereco, 50, casasPtr);
			fscanf(casasPtr, "%d %d %lf %lf %d %d %d %lf", &casas[i].CEP, &casas[i].numero, &casas[i].areaTerreno, &casas[i].areaConstruida, &casas[i].pavimentos, &casas[i].numeroQuartos, &casas[i].tipoPagamento, &casas[i].valor);
			i++;
		}

		fclose(casasPtr);
	}

	if((apartamentosPtr = fopen("apartamentos.txt", "r")) == NULL)
		printf("Arquvo de apartamentos nao encontrado");
	else{
		j = 0;
		while(!feof(apartamentosPtr)){
			fgets(apartamentos[j].tituloImovel, 101, apartamentosPtr);
			fgets(apartamentos[j].posicao, 25, apartamentosPtr);
			fgets(apartamentos[j].cidade, 30, apartamentosPtr);
			fgets(apartamentos[j].bairro, 30, apartamentosPtr);
			fgets(apartamentos[j].endereco, 50, apartamentosPtr);
			fscanf(apartamentosPtr, "%d %d %d %lf %d %d %lf %lf %d", &apartamentos[j].CEP, &apartamentos[j].numero, &apartamentos[j].andar, &apartamentos[j].areaTerreno, &apartamentos[j].numeroQuartos, &apartamentos[j].tipoPagamento, &apartamentos[j].valor, &apartamentos[j].valorCondominio, &apartamentos[j].numVagasGaragem);
			j++;
		}

		fclose(apartamentosPtr);

	}

	if((terrenosPtr = fopen("terrenos.txt", "r")) == NULL)
		printf("Arquivo de terrenos nao encontrado");
	else{
		k = 0;
		while(!feof(terrenosPtr)){
			fgets(terrenos[k].tituloImovel, 101, terrenosPtr);
			fgets(terrenos[k].cidade, 30, terrenosPtr);
			fgets(terrenos[k].bairro, 30, terrenosPtr);
			fgets(terrenos[k].endereco, 50, terrenosPtr);
			fscanf(terrenosPtr, "%d %d %lf %d %lf", &terrenos[k].numero, &terrenos[k].CEP, &terrenos[k].areaTerreno, &terrenos[k].tipoPagamento, &terrenos[k].valor);
			k++;
		}

		fclose(terrenosPtr);

	}

	return;
}
void imprimeImovel(int numero, char letra){           //recebe como parâmetro o numero onde se localiza o imóvel e seu tipo
    switch(letra){
        case 'c':                                     //caso o imóvel seja uma casa
            printf("\tInformacoes sobre o imovel: %s\n\n", casas[numero].tituloImovel);
            printf("Casa disponivel para %s com %d pavimentos e %d quartos\nLocalizada no endereco: %s, %d - %d\n%s em %s\n", (casas[numero].tipoPagamento == 1) ? "venda" : "aluguel", casas[numero].pavimentos, casas[numero].numeroQuartos, casas[numero].endereco, casas[numero].numero, casas[numero].CEP, casas[numero].bairro, casas[numero].cidade);
			printf("Area do terreno: %.3lf(m²)        Area construida: %.3lf(m²)\n", casas[numero].areaTerreno, casas[numero].areaConstruida);
            printf("Valor %s: R$%.2lf\n\n",(casas[numero].tipoPagamento == 1) ? "Total" : "do aluguel", casas[numero].valor);
			break;
        case 'a':                                    //caso o imóvel seja um apartamento
            printf("\tInformacoes sobre o imovel: %s\n\n", apartamentos[numero].tituloImovel);
			printf("Apartamento disponivel para %s na posicao %s\nLocalizada no endereco: %s, %d - %d\n%s em %s\n", (apartamentos[numero].tipoPagamento == 1) ? "venda" : "aluguel",  apartamentos[numero].posicao, apartamentos[numero].endereco, apartamentos[numero].numero, apartamentos[numero].CEP, apartamentos[numero].bairro, apartamentos[numero].cidade);
			printf("Este imovel esta no %d andar e possui tamanho %.3lf (m²), tendo %d quartos\n", apartamentos[numero].andar, apartamentos[numero].areaTerreno, apartamentos[numero].numeroQuartos);
			printf("Valor %s: R$%.2lf     ",(apartamentos[numero].tipoPagamento == 1) ? "Total" : "do aluguel", apartamentos[numero].valor);
			printf("Valor do condominio: R$%.2lf\n", apartamentos[numero].valorCondominio);
			printf("Quantidade de vagas na garagem: %d\n\n", apartamentos[numero].numVagasGaragem);
			break;
        case 't':                                    //caso o imóvel seja um terreno
            printf("\tInformacoes sobre o imovel: %s\n\n", terrenos[numero].tituloImovel);
			printf("Terreno disponivel para %s\nLocalizado no endereco: %s, %d - %d\n %s em %s\n", (terrenos[numero].tipoPagamento == 1) ? "venda" : "aluguel", terrenos[numero].endereco, terrenos[numero].numero, terrenos[numero].CEP, terrenos[numero].bairro, terrenos[numero].cidade);
            printf("Tamanho: %.3lf(m²)\n", terrenos[numero].areaTerreno);
            printf("Valor: R$%.2lf\n\n", terrenos[numero].valor);
            break;
        default:
            break;
    }
}

void cadastraCasa(void){

	FILE *casasPtr;
    system("cls");

	if((casasPtr = fopen("casas.txt", "a+")) == NULL){
		printf("Arquivo de casas nao encontrado\n");
	}
	else{
        int i, a;
        for(i = 0; i < (QNT_IMOVEIS-1); i++){
            if(casas[i].areaTerreno == 0){
            cadastro:
                system("cls");
                a = 0;
                printf("Insira o titulo de anuncio da casa: \n");
                    fgets(casas[i].tituloImovel, QNT_IMOVEIS, stdin);


                    if(strlen(casas[i].tituloImovel) > 100){                                     //quando o titulo ultrapassa o tamanho
                        printf("O titulo do anuncio esta muito grande! Tente reformula-lo\n");  //    da string
                        printf("\nPressione qualquer tecla para voltar\n");
                        getch();
                        goto cadastro;
                    }
                    else{
                        fprintf(casasPtr, "%s", casas[i].tituloImovel);
                        printf("Insira a cidade em que a casa se localiza: \n");
                        fgets(casas[i].cidade, 30, stdin);
                        fprintf(casasPtr, "%s", casas[i].cidade);

                        printf("Insira o bairro da casa: \n");
                        fgets(casas[i].bairro, 30, stdin);
                        fprintf(casasPtr, "%s", casas[i].bairro);

                        printf("Insira o endereco: \n");
                        fgets(casas[i].endereco, 50, stdin);
                        fprintf(casasPtr, "%s", casas[i].endereco);

                        printf("Insira o CEP da casa: ");
                        scanf("%d", &casas[i].CEP);
                        fprintf(casasPtr, "%d\n", casas[i].CEP);

                        printf("Insira o numero da casa: ");
                        scanf("%d", &casas[i].numero);
                        fprintf(casasPtr, "%d\n", casas[i].numero);

                        printf("Insira a area do terreno(m²):");
                        scanf("%lf", &casas[i].areaTerreno);
                        fprintf(casasPtr, "%lf\n", casas[i].areaTerreno);

                        printf("Insira a area construida do imovel(m²): ");
                        scanf("%lf", &casas[i].areaConstruida);
                        fprintf(casasPtr, "%lf\n", casas[i].areaConstruida);

                        printf("Insira a quantidade de pavimentos da casa: ");
                        scanf("%d", &casas[i].pavimentos);
                        fprintf(casasPtr, "%d\n", casas[i].pavimentos);

                        printf("Insira a quantidade de quartos da casa: ");
                        scanf("%d", &casas[i].numeroQuartos);
                        fprintf(casasPtr, "%d\n", casas[i].numeroQuartos);

                        resposta:
                            printf("Esta casa e para vender (1) ou para alugar (2)? ");
                            scanf("%d", &casas[i].tipoPagamento);
                            fprintf(casasPtr, "%d\n", casas[i].tipoPagamento);

                            if((casas[i].tipoPagamento==1) || (casas[i].tipoPagamento==2)){
                                printf("Insira o valor %s",(casas[i].tipoPagamento == 1) ? "da casa: " : "do aluguel: ");
                                scanf("%lf", &casas[i].valor);
                                fprintf(casasPtr, "%lf\n", casas[i].valor);
                            }
                            else{
                                goto resposta;
                            }

                        }
                        a++;
                        break;
                }
            }
        if(a == 0){                                                       //caso não tenha cadastrado nenhum imovel
            system("cls");
            printf("Nao e possivel adicionar mais imoveis! Todas as vagas estao ocupadas\n");
        }
	}

    printf("\nAperte ESC para voltar ao MENU");
    escolha=getch();                                                         //enquanto a tecla ESC não for presionada,
    while(escolha!=ESC){                                                      //      ele fica estático
        escolha=getch();
    }
}
void cadastraApt(void){

	FILE *apartamentosPtr;
    system("cls");

	if((apartamentosPtr = fopen("apartamentos.txt", "a+")) == NULL){
		printf("Arquivo de apartamentos nao encontrado");
		getch();
	}
	else{

        int i, a;
        for(i = 0; i < 100; i++){
            if(apartamentos[i].areaTerreno == 0){
            cadastro:
                system("cls");
                a = 0;
                printf("Insira o titulo de anuncio do apartamento: \n");
                fgets(apartamentos[i].tituloImovel, 101, stdin);

                if(strlen(apartamentos[i].tituloImovel) > 100){                              //quando o titulo ultrapassa o tamanho
                    printf("O titulo do anuncio esta muito grande!Tente reformula-lo\n");    //    da string
                    printf("\nPressione qualquer tecla para voltar\n");
                    getch();
                    goto cadastro;
                }else{
                    fprintf(apartamentosPtr, "%s", apartamentos[i].tituloImovel);
                    printf("Insira a posicao em que o apartamento se localiza: \n");
                    fgets(apartamentos[i].posicao, 25, stdin);
                    fprintf(apartamentosPtr, "%s", apartamentos[i].posicao);

                    printf("Insira a cidade em que o apartamento se localiza: \n");
                    fgets(apartamentos[i].cidade, 30, stdin);
                    fprintf(apartamentosPtr, "%s", apartamentos[i].cidade);

                    printf("Insira o bairro do apartamento: \n");
                    fgets(apartamentos[i].bairro, 30, stdin);
                    fprintf(apartamentosPtr, "%s", apartamentos[i].bairro);

                    printf("Insira o endereco: \n");
                    fgets(apartamentos[i].endereco, 50, stdin);
                    fprintf(apartamentosPtr, "%s", apartamentos[i].endereco);

                    printf("Insira o CEP do apartamento: ");
                    scanf("%d", &apartamentos[i].CEP);
                    fprintf(apartamentosPtr, "%d\n", apartamentos[i].CEP);

                    printf("Insira o numero do apartamento: ");
                    scanf("%d", &apartamentos[i].numero);
                    fprintf(apartamentosPtr, "%d\n", apartamentos[i].numero);

                    printf("Insira em qual andar fica o apartamento: ");
                    scanf("%d", &apartamentos[i].andar);
                    fprintf(apartamentosPtr, "%d\n", apartamentos[i].andar);

                    printf("Insira o tamanho do apartamento(m²): ");
                    scanf("%lf", &apartamentos[i].areaTerreno);
                    fprintf(apartamentosPtr, "%lf\n", apartamentos[i].areaTerreno);

                    printf("Insira a quantidade de quartos do apartamento: ");
                    scanf("%d", &apartamentos[i].numeroQuartos);
                    fprintf(apartamentosPtr, "%d\n", apartamentos[i].numeroQuartos);

                    resposta:
                        printf("Este apartamento e para vender (1) ou para alugar (2)? ");
                        scanf("%d", &apartamentos[i].tipoPagamento);

                        if((apartamentos[i].tipoPagamento==1) || (apartamentos[i].tipoPagamento==2)){
                            printf("Insira o valor %s",(apartamentos[i].tipoPagamento == 1) ? "do apartamento: " : "do aluguel: ");
                            scanf("%lf", &apartamentos[i].valor);
                            fprintf(apartamentosPtr, "%d\n", apartamentos[i].tipoPagamento);
                            fprintf(apartamentosPtr, "%lf\n", apartamentos[i].valor);
                        }
                        else{
                            goto resposta;
                        }

                    printf("Insira o valor do condominio: ");
                    scanf("%lf", &apartamentos[i].valorCondominio);
                    fprintf(apartamentosPtr, "%lf\n", apartamentos[i].valor);


                    printf("Insira a quantidade de vagas na garagem: ");
                    scanf("%d", &apartamentos[i].numVagasGaragem);
                    fprintf(apartamentosPtr, "%d\n", apartamentos[i].numVagasGaragem);

                }
                a++;
                break;
            }
        }

        if(a == 0){                                                       //caso não tenha cadastrado nenhum imovel
            system("cls");
            printf("Nao e possivel adicionar mais imoveis! Todas as vagas estao ocupadas\n");
        }
	}
    printf("\nAperte ESC para voltar ao MENU");
    escolha=getch();                                                         //enquanto a tecla ESC não for presionada,
    while(escolha!=ESC){                                                      //      ele fica estático
        escolha=getch();
    }
}
void cadastraTer(void){

	FILE *terrenosPtr;
    system("cls");

	if((terrenosPtr = fopen("terrenos.txt", "a+")) == NULL)
		printf("Arquivo de terrenos nao encontrado\n\n");
	else{
		int i, a;

		for(i = 0; i < 100; i++){
			if(terrenos[i].areaTerreno == 0){
				cadastro:
					system("cls");
					a = 0;
					printf("Insira o titulo de anuncio do terreno: \n");
                    fgets(terrenos[i].tituloImovel, 101, stdin);

                    if(strlen(terrenos[i].tituloImovel) > 100){                                 //quando o titulo ultrapassa o tamanho
                        printf("O titulo do anuncio esta muito grande!Tente reformula-lo\n");   //     da string
                        printf("\nPressione qualquer tecla para voltar\n");
                        getch();
                        goto cadastro;
                    }else{
                        fprintf(terrenosPtr, "%s", terrenos[i].tituloImovel);
                        printf("Insira a cidade em que o terreno se localiza: \n");
                        fgets(terrenos[i].cidade, 30, stdin);
                        fprintf(terrenosPtr, "%s", terrenos[i].cidade);

                        printf("Insira o bairro do terreno: \n");
                        fgets(terrenos[i].bairro, 30, stdin);
                        fprintf(terrenosPtr, "%s", terrenos[i].bairro);

                        printf("Insira o endereco: \n");
                        fgets(terrenos[i].endereco, 50, stdin);
                        fprintf(terrenosPtr, "%s", terrenos[i].endereco);

                        printf("Insira o numero do terreno: ");
                        scanf("%d", &terrenos[i].numero);
                        fprintf(terrenosPtr, "%d\n", terrenos[i].numero);

                        printf("Insira o CEP do terreno: ");
                        scanf("%d", &terrenos[i].CEP);
                        fprintf(terrenosPtr, "%d\n", terrenos[i].CEP);

                        printf("Insira o tamanho do terreno(m²): ");
                        scanf("%lf", &terrenos[i].areaTerreno);
                        fprintf(terrenosPtr, "%lf\n", terrenos[i].areaTerreno);

                        resposta:
                            printf("Este terreno e para vender (1) ou para alugar (2)? ");
                            scanf("%d", &terrenos[i].tipoPagamento);
                            fprintf(terrenosPtr, "%d\n", terrenos[i].tipoPagamento);

                            if((terrenos[i].tipoPagamento==1) || (terrenos[i].tipoPagamento==2)){
                                printf("Insira o valor %s",(terrenos[i].tipoPagamento == 1) ? "do terreno: " : "do aluguel: ");
                                scanf("%lf", &terrenos[i].valor);
                                fprintf(terrenosPtr, "%lf\n", terrenos[i].valor);
                            }
                            else{
                                goto resposta;
                            }
                    }
                a++;
                break;
            }
        }

        if(a == 0){                                                       //caso não tenha cadastrado nenhum imovel
            system("cls");
            printf("Nao e possivel adicionar mais imoveis! Todas as vagas estao ocupadas\n");
        }
	}
    printf("\nAperte ESC para voltar ao MENU");
    escolha=getch();                                                         //enquanto a tecla ESC não for presionada,
    while(escolha!=ESC){                                                      //      ele fica estático
        escolha=getch();
    }
}

void buscaBairro(void){
    char bairro[101];
    int i, soma = 0;

    system("cls");
    printf("---------=========Busca por Bairro=========---------\n");
    printf("Digite o bairro a ser pesquisado: \n");                      //recebe do usuário o nome do bairro para pesquisa e o compara com
    fgets(bairro, 101, stdin);                                                 //todos os imóveis disponíveis e caso ache, chama a função para imprimi-lo
    system("cls");

    for(i = 0; i < QNT_IMOVEIS; i++){
        if((casas[i].areaTerreno > 0) && (!strcmp(bairro, casas[i].bairro))){
            imprimeImovel(i,'c');
            soma++;
       }
    }

    for(i = 0; i < QNT_IMOVEIS; i++){
        if((apartamentos[i].areaTerreno > 0) && !strcmp(bairro, apartamentos[i].bairro)){
            imprimeImovel(i,'a');
            soma++;
        }
    }

    for(i = 0; i < QNT_IMOVEIS; i++){
        if((terrenos[i].areaTerreno > 0) && !strcmp(bairro, terrenos[i].bairro)){
            imprimeImovel(i,'t');
            soma++;
        }
    }

    if(soma == 0){                                                               //caso não haja nenhum imóvel com o termo procurado, a variável
        printf("Nao ha imoveis disponiveis nesse bairro\n\n");               //                soma não é incrementada
    }

    printf("aperte ESC para voltar ao MENU");
    escolha=getch();
    while(escolha!=ESC){
        escolha=getch();
    }
}
void buscaTitulo(void){
    char titulo[101];
    int i, soma = 0;

    system("cls");
    printf("---------=========Busca por Titulo=========---------\n");             //recebe do usuário o nome do bairro para pesquisa e o compara com
    printf("Digite o titulo a ser pesquisado:\n");                                //todos os imóveis disponíveis e caso ache, chama a função para imprimi-lo
    fgets(titulo, 101, stdin);
    system("cls");

    for(i = 0; i < QNT_IMOVEIS; i++){
        if((casas[i].areaTerreno > 0) && (!strcmp(titulo, casas[i].tituloImovel))){
            imprimeImovel(i,'c');
            soma++;
       }
    }

    for(i = 0; i < QNT_IMOVEIS; i++){
        if((apartamentos[i].areaTerreno > 0) && (!strcmp(titulo, apartamentos[i].tituloImovel))){
            imprimeImovel(i,'a');
            soma++;
        }
    }

    for(i = 0; i < QNT_IMOVEIS; i++){
        if((terrenos[i].areaTerreno > 0) && (!strcmp(titulo, terrenos[i].tituloImovel))){
            imprimeImovel(i,'t');
            soma++;
        }
    }

    if(soma == 0){                                                              //caso não haja nenhum imóvel com o termo procurado, a variável
        printf("Nao ha imoveis disponiveis com esse titulo\n\n");               //                soma não é incrementada
    }

    printf("aperte ESC para voltar ao MENU");
    escolha=getch();
    while(escolha!=ESC){
        escolha=getch();
    }
}
void buscaValor(void){
    double valor;
    int i, soma = 0;

    system("cls");
    printf("---------=========Busca por Valor=========---------\n");              //recebe do usuário o nome do bairro para pesquisa e o compara com
    printf("Digite o valor a ser pesquisado:\n");                                 //todos os imóveis disponíveis e caso ache, chama a função para imprimi-lo
    scanf("%lf", &valor);
    system("cls");

    for(i = 0; i < QNT_IMOVEIS; i++){
        if((casas[i].areaTerreno > 0) && (valor == casas[i].valor)){
            imprimeImovel(i,'c');
            soma++;
       }
    }

    for(i = 0; i < QNT_IMOVEIS; i++){
        if((apartamentos[i].areaTerreno > 0) && (valor == apartamentos[i].valor)){
            imprimeImovel(i,'a');
            soma++;
        }
    }

    for(i = 0; i < QNT_IMOVEIS; i++){
        if((terrenos[i].areaTerreno > 0) && (valor == terrenos[i].valor)){
            imprimeImovel(i,'t');
            soma++;
        }
    }

    if(soma == 0){                                                                 //caso não haja nenhum imóvel com o termo procurado, a variável
        printf("Nao ha imoveis disponiveis com esse valor\n\n");               //                soma não é incrementada
    }

    printf("aperte ESC para voltar ao MENU");
    escolha=getch();
    while(escolha!=ESC){
        escolha=getch();
    }
}

void mostrarCasa(char letra){
	int i, a = 0;
	system("cls");
    switch(letra){
        case 'v':
            for(i = 0; i < 100; i++){
                if(casas[i].areaTerreno > 0){
                    if(casas[i].tipoPagamento==1){
                        imprimeImovel(i,'c');
                        a++;
                    }
                }
            }
            break;
        default:
            for(i = 0; i < 100; i++){
                if(casas[i].areaTerreno > 0){
                    if(casas[i].tipoPagamento==2){
                        imprimeImovel(i,'c');
                        a++;
                    }
                }
            }
            break;
    }


    if(a == 0){
        printf("Nao possuimos nenhuma casa para %s\n", (letra=='v') ? "venda" : "aluguel");
    }

    printf("\nTecle ESC para voltar\n");

        final:
            escolha = getch();
            if(escolha == ESC){
                return;
            }
            else{
                goto final;
            }
}
void mostrarApt(char letra){
	int i, a = 0;
	system("cls");

    switch(letra){
        case 'v':
            for(i = 0; i < 100; i++){
                 if(apartamentos[i].areaTerreno > 0){
                    if(apartamentos[i].tipoPagamento==1){
                        imprimeImovel(i,'a');
                        a++;
                    }
                }
            }
            break;
        default:
            for(i = 0; i < 100; i++){
                if(apartamentos[i].areaTerreno > 0){
                    if(apartamentos[i].tipoPagamento==2){
                        imprimeImovel(i,'a');
                        a++;
                    }
                }
            }
            break;
    }


    if(a == 0){
        printf("Nao possuimos nenhuma apartamento para %s\n", (letra=='v') ? "venda" : "aluguel");
    }
    printf("\nTecle ESC para voltar\n");

    final:
        escolha = getch();

        if(escolha == ESC)
            return;
        else
            goto final;
}
void mostrarTerreno(char letra){
	int i, a = 0;
	system("cls");

	switch(letra){
        case 'v':
            for(i = 0; i < 100; i++){
                if(terrenos[i].areaTerreno > 0){
                    if(terrenos[i].tipoPagamento==1){
                        imprimeImovel(i,'t');
                        a++;
                    }
                }
            }
            break;
        default:
            for(i = 0; i < 100; i++){
                if(terrenos[i].areaTerreno > 0){
                    if(terrenos[i].tipoPagamento==2){
                        imprimeImovel(i,'t');
                        a++;
                    }
                }
            }
            break;
    }

	if(a == 0){
		printf("Nao foram encontrados terrenos disponiveis para %s\n", (letra=='v') ? "venda" : "aluguel");
	}
    printf("\nTecle ESC para voltar\n");

    final:
        escolha = getch();

        if(escolha == ESC)
            return;
        else
            goto final;
}
void tipo(char letra){
    int variavelConsulta=1, flag=0;

	while(flag==0){
		system("cls");
		switch(variavelConsulta){
			case 1:
				printf("---------========Imoveis Disponiveis========-------------\n"
					   "\t\tVenda\n"
					   "\tAluguel\n\n\n"
					   "\tPara voltar ao MENU pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
					    switch(letra){
					        case 'c':
                                mostrarCasa('v');
                                break;
                            case 'a':
                                mostrarApt('v');
                                break;
                            default:
                                mostrarTerreno('v');
                                break;
					    }
                        variavelConsulta=0;
						break;
					case CIMA:
						variavelConsulta=3;
						break;
					case BAIXO:
						variavelConsulta=2;
						break;
					case ESC:
						variavelConsulta=0;
						break;
					default:
						continue;
				}
				break;
            case 2:
				printf("---------========Imoveis Disponiveis========-------------\n"
					   "\tVenda\n"
					   "\t\tAluguel\n\n\n"
					   "\tPara voltar ao MENU pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
					    switch(letra){
					        case 'c':
                                mostrarCasa('a');
                                break;
                            case 'a':
                                mostrarApt('a');
                                break;
                            default:
                                mostrarTerreno('a');
                                break;
					    }
                        variavelConsulta=0;
						break;
					case CIMA:
						variavelConsulta=1;
						break;
					case BAIXO:
						variavelConsulta=3;
						break;
					case ESC:
						variavelConsulta=0;
						break;
					default:
						continue;
				}
				break;
           default:
				flag=1;
				break;
		}
	}
}

void edicaoCasa(void){
	int a, i, achados;
    int numero, CEP;

	system("cls");
	printf("Insira o numero da casa que desejas editar: ");
    scanf("%d", &numero);

	printf("Digite o CEP em que a casa se localiza: ");
	scanf("%d", &CEP);

    system("cls");
    a = 0;
    for(i = 0; i < 100; i++){
        if(casas[i].areaTerreno > 0){
            if((casas[i].CEP == CEP) && (casas[i].numero == numero)){
                imprimeImovel(i,'c');
                achados = i;
                a++;
            }
        }
    }

    switch(a){
        case 0:
            printf("\nNao foram encontrados casas neste local\n\nTecle ESC para voltarao menu\n");

            while(1){
                escolha = getch();
                if(escolha == ESC){
                    break;
                }
            }
            break;
        default:
            printf("\n\nDeseja editar esta casa? (1 - sim, 2 - nao): \n");

            REsposta:
            scanf("%d", &escolha);

            if((escolha != 1) && (escolha!= 2)){
                printf("\nResposta invalida! Digite novamente\n\nAperte qualquer tecla");
                system("pause");
                system("cls");
                goto REsposta;
            }
            else if(escolha == 1){
                char novoTitulo[101], novoBairro[31], novoEndereco[50], novaCidade[31];
                int j;

                system("cls");
                printf("Insira o numero da casa: ");
                scanf("%d", &casas[achados].numero);

                printf("Insira o titulo de anuncio da casa:\n");
                fgets(novoTitulo, 101, stdin);
                novoTitulo[strlen(novoTitulo) -1] = '\0';
                for(j = 0; j < 101; j++){
                    casas[achados].tituloImovel[j] = novoTitulo[j];
                }

                printf("Insira a cidade em que a casa se localiza:\n");
                fgets(novaCidade, 31, stdin);
                novaCidade[strlen(novaCidade) -1] = '\0';
                for(j = 0; j < 31; j++){
                    casas[achados].cidade[j] = novaCidade[j];
                }

                printf("Insira o bairro da casa:\n");
                fgets(novoBairro, 31, stdin);
                novoBairro[strlen(novoBairro) -1] = '\0';
                for(j = 0; j < 31; j++){
                    casas[achados].bairro[j] = novoBairro[j];
                }

                printf("Insira o endereco da casa:\n");
                fgets(novoEndereco, 50, stdin);
                novoEndereco[strlen(novoEndereco) -1] = '\0';
                for(j = 0; j < 50; j++){
                    casas[achados].endereco[j] = novoEndereco[j];
                }

                printf("Insira o CEP da casa: ");
                scanf("%d", &casas[achados].CEP);

                printf("Insira o tamanho da area do terreno da casa? (m²): ");
                scanf("%lf", &casas[achados].areaTerreno);

                printf("Insira o tamanho da area do construida da casa? (m²): ");
                scanf("%lf", &casas[achados].areaConstruida);

                printf("Insira a quantidade de pavimentos da casa: ");
                scanf("%d", &casas[achados].pavimentos);

                printf("Insira o numero de quartos da casa: ");
                scanf("%d", &casas[achados].numeroQuartos);

                resposta:
                        printf("Esta casa e para vender (1) ou para alugar (2)? ");
                        scanf("%d", &casas[achados].tipoPagamento);

                        if((casas[achados].tipoPagamento==1) || (casas[achados].tipoPagamento==2)){
                            printf("Insira o valor %s",(casas[achados].tipoPagamento == 1) ? "da casa: " : "do aluguel: ");
                            scanf("%lf", &casas[achados].valor);
                        }
                        else{
                            goto resposta;
                        }
        }
        break;
    }

	int contador = 0;

	for(i = 0; i < 100; i++){
		if(casas[i].areaTerreno != 0){
			contador++;
		}
	}

	FILE *casasPtr;

	if((casasPtr = fopen("casas.txt", "w")) == NULL)
		printf("Houve um problema ao abrir o arquivo");
	else{
		for(i = 0; i < contador; i++){
			fprintf(casasPtr, "%s", casas[i].tituloImovel);
			fprintf(casasPtr, "%s" , casas[i].cidade);
			fprintf(casasPtr, "%s", casas[i].bairro);
			fprintf(casasPtr, "%s", casas[i].endereco);
			fprintf(casasPtr, "%d\n%d\n%lf\n%lf\n%d\n%d\n%d\n%lf\n", casas[i].CEP, casas[i].numero, casas[i].areaTerreno, casas[i].areaConstruida, casas[i].pavimentos, casas[i].numeroQuartos, casas[i].tipoPagamento, casas[i].valor);
		}

		fclose(casasPtr);
	}
}
void edicaoApt(void){
	int a, i, achados;
    int numero, numeroDoAndar, CEP;
	system("cls");

    printf("Insira o numero do edificio: ");
    scanf("%d", &numero);

    printf("Insira o numero do andar: ");
    scanf("%d", &numeroDoAndar);

	printf("Insira o CEP em que o apartamento se localiza: ");
	scanf("%d", &CEP);

    a = 0;
    system("cls");
    for(i = 0; i < 100; i++){
        if(apartamentos[i].areaTerreno > 0){
            if(((apartamentos[i].CEP == CEP) && (apartamentos[i].numero == numero)) && (apartamentos[i].andar == numeroDoAndar)){
                imprimeImovel(i,'a');
                achados = i;
                a++;
            }
        }
    }

    switch(a){
        case 0:
            printf("Nao foram encontrados apartamentos neste bairro\nTecle ESC para voltar\n");

            while(escolha != ESC){
                escolha = getch();
            }
            break;
        default:

            REsposta:
            printf("Deseja editar este apartamento? (1 - sim, 2 - nao): \n");
            scanf("%d", &escolha);

            if(escolha!= 1 && escolha!= 2){
                system("cls");
                printf("Resposta invalida! Digite novamente\n\n(Aperte qualquer tecla para continuar)");
                getch();
                system("cls");
                goto REsposta;
            }
            else if(escolha == 1){
                char novoTitulo[101], novoBairro[31], novoEndereco[50], novaCidade[31], novaPosicao[26];
                int j;

                system("cls");
                printf("Insira o numero do apartamento: ");
                scanf("%d", &apartamentos[achados].numero);

                printf("Insira o titulo de anuncio do apartamento:\n");
                fgets(novoTitulo, 101, stdin);
                novoTitulo[strlen(novoTitulo) -1] = '\0';
                for(j = 0; j < 101; j++){
                    apartamentos[achados].tituloImovel[j] = novoTitulo[j];
                }

                printf("Insira a posicao em que o edificio se localiza:\n");
                fgets(novaPosicao, 26, stdin);
                novaPosicao[strlen(novaPosicao) -1] = '\0';
                for(j = 0; j < 26; j++){
                    apartamentos[achados].posicao[j] = novaPosicao[j];
                }

                printf("Insira a cidade em que o apartamento se localiza:\n");
                fgets(novaCidade, 31, stdin);
                for(j = 0; j < 31; j++){
                    apartamentos[achados].cidade[j] = novaCidade[j];
                }

                printf("Insira o bairro do edificio:\n");
                fgets(novoBairro, 31, stdin);
                novoBairro[strlen(novoBairro) -1] = '\0';
                for(j = 0; j < 31; j++){
                    apartamentos[achados].bairro[j] = novoBairro[j];
                }

                printf("Insira o endereco do edificio:\n");
                fgets(novoEndereco, 50, stdin);
                novoEndereco[strlen(novoEndereco) -1] = '\0';
                for(j = 0; j < 50; j++){
                    apartamentos[achados].endereco[j] = novoEndereco[j];
                }

                printf("Insira o CEP do apartamento: ");
                scanf("%d", &apartamentos[achados].CEP);

                printf("Insira em qual andar fica o apartamento: ");
                scanf("%d", &apartamentos[achados].andar);

                printf("Insira o tamanho do apartamento(m²): ");
                scanf("%lf", &apartamentos[achados].areaTerreno);

                printf("Insira a quantidade de quartos do apartamento: ");
                scanf("%d", &apartamentos[achados].numeroQuartos);

                printf("Insira a quantidade de vagas na garagem: ");
                scanf("%d", &apartamentos[achados].numVagasGaragem);

                resposta:
                    printf("Este apartamento e para vender (1) ou para alugar (2)? ");
                    scanf("%d", &apartamentos[achados].tipoPagamento);

                    if((apartamentos[achados].tipoPagamento==1) || (apartamentos[achados].tipoPagamento==2)){
                        printf("Insira o valor %s",(apartamentos[achados].tipoPagamento == 1) ? "do apartamento: " : "do aluguel: ");
                        scanf("%lf", &apartamentos[achados].valor);
                    }
                    else{
                        goto resposta;
                    }

                printf("Insira o valor do condominio: ");
                scanf("%lf", &apartamentos[achados].valorCondominio);
            }
            break;
    }

	FILE *apartamentosPtr;

	if((apartamentosPtr = fopen("apartamentos.txt", "w")) == NULL)
		printf("Houve um erro ao abrir o arquivo\n");
	else{
		int contador = 0;

		for(i = 0; i < 100; i++){
			if(apartamentos[i].areaTerreno != 0)
				contador++;
		}

		for(i = 0; i < contador; i++){
			fprintf(apartamentosPtr, "%s", apartamentos[i].tituloImovel);
			fprintf(apartamentosPtr, "%s", apartamentos[i].posicao);
			fprintf(apartamentosPtr, "%s", apartamentos[i].cidade);
			fprintf(apartamentosPtr, "%s", apartamentos[i].bairro);
			fprintf(apartamentosPtr, "%s", apartamentos[i].endereco);
			fprintf(apartamentosPtr, "%d\n%d\n%d\n%lf\n%d\n%d\n%lf\n%lf\n%d", apartamentos[i].CEP, apartamentos[i].numero, apartamentos[i].andar, apartamentos[i].areaTerreno, apartamentos[i].numeroQuartos, apartamentos[i].tipoPagamento, apartamentos[i].valor, apartamentos[i].valorCondominio, apartamentos[i].numVagasGaragem);
		}

		fclose(apartamentosPtr);
	}
}
void edicaoTer(void){
	int a = 0, i, achados;
    int numero, CEP;

	system("cls");
	printf("Insira o CEP em que o terreno se localiza: ");
	scanf("%d", &CEP);

    printf("Insira o numero do terreno que desejas editar: ");
    scanf("%d", &numero);

    a = 0;
    system("cls");
    for(i = 0; i < 100; i++){
        if(terrenos[i].areaTerreno > 0){
            if((terrenos[i].CEP == CEP) && (terrenos[i].numero == numero)){
                imprimeImovel(i,'t');
                achados = i;
                a++;
            }
        }
    }

    switch(a){
        case 0:
            printf("\nNao foram encontrados terrenos neste bairro\nTecle ESC para voltar ao menu\n");

            while(1){
                escolha = getch();
                if(escolha == ESC){
                    break;
                }
            }
            break;
        default:
        printf("Deseja editar este terreno? (1 - sim, 2 - nao): \n");

        REsposta:
        scanf("%d", &escolha);

        if(escolha!= 1 && escolha!= 2){
            printf("Resposta invalida! Digite novamente\n\nAperte qualquer tecla\n");
            system("pause");
            system("cls");
            goto REsposta;
        }
        else if(escolha == 1){
            char novoTitulo[101], novoBairro[31], novoEndereco[50], novaCidade[31];
            int j;

            system("cls");
            printf("Insira o numero do terreno: ");
            scanf("%d", &terrenos[achados].numero);

            printf("Insira o titulo de anuncio do terreno:\n");
            fgets(novoTitulo, 101, stdin);
            novoTitulo[strlen(novoTitulo) -1] = '\0';
            for(j = 0; j < 101; j++){
                terrenos[achados].tituloImovel[j] = novoTitulo[j];
            }

            printf("Insira a cidade em que o terreno se localiza:\n");
            fgets(novaCidade, 31, stdin);
            novaCidade[strlen(novaCidade) -1] = '\0';
            for(j = 0; j < 31; j++){
                terrenos[achados].cidade[j] = novaCidade[j];
            }

            printf("Insira o bairro do terreno:\n");
            fgets(novoBairro, 31, stdin);
            novoBairro[strlen(novoBairro) -1] = '\0';
            for(j = 0; j < 31; j++){
                terrenos[achados].bairro[j] = novoBairro[j];
            }

            printf("Insira o endereco do terreno:\n");
            fgets(novoEndereco, 50, stdin);
            novoEndereco[strlen(novoEndereco) -1] = '\0';
            for(j = 0; j < 50; j++){
                terrenos[achados].endereco[j] = novoEndereco[j];
            }

            printf("Insira o CEP do terreno: ");
            scanf("%d", &terrenos[achados].CEP);

            printf("Insira o tamanho da area do terreno? (m²): ");
            scanf("%lf", &terrenos[achados].areaTerreno);

            resposta:
                printf("Este terreno e para vender (1) ou para alugar (2)? ");
                scanf("%d", &terrenos[achados].tipoPagamento);

                if((terrenos[achados].tipoPagamento==1) || (terrenos[achados].tipoPagamento==2)){
                    printf("Insira o valor %s",(terrenos[achados].tipoPagamento == 1) ? "do terreno: " : "do aluguel: ");
                    scanf("%lf", &terrenos[achados].valor);
                }
                else{
                    goto resposta;
                }
        }
    }


	FILE *terrenosPtr;

	if((terrenosPtr = fopen("terrenos.txt", "w")) == NULL)
		printf("Houve um problema ao abrir o arquivo\n");
	else{
		int contador = 0;
		for(i = 0; i < 100; i++){
			if(terrenos[i].areaTerreno != 0)
				contador++;
		}

		for(i = 0; i < contador; i++){
			fprintf(terrenosPtr, "%s", terrenos[i].tituloImovel);
			fprintf(terrenosPtr, "%s", terrenos[i].cidade);
			fprintf(terrenosPtr, "%s", terrenos[i].bairro);
			fprintf(terrenosPtr, "%s", terrenos[i].endereco);
			fprintf(terrenosPtr, "%d\n%d\n%lf\n%d\n%lf\n", terrenos[i].numero, terrenos[i].CEP, terrenos[i].areaTerreno, terrenos[i].tipoPagamento, terrenos[i].valor);
		}

		fclose(terrenosPtr);
	}
}

void remocao(char letra){
	int a = 0, i, achados;
    int numero, andar, CEP;
    int contador = 0;

	system("cls");
	printf("Insira o numero do imovel: ");
	scanf("%d", &numero);

	printf("Insira o CEP em que o imovel se localiza:\n");
	scanf("%d", &CEP);

    switch(letra){
        case 'c':
            system("cls");
            for(i = 0; i < 100; i++){
                if(casas[i].areaTerreno > 0){
                    if((casas[i].CEP == CEP) && (casas[i].numero == numero)){
                        imprimeImovel(i,'c');
                        achados = i;
                        a++;
                    }
                }
            }
            if(a != 0){
                Resposta:
                    printf("Deseja remover este imovel? (1 - sim ou 2 -nao):\n");

                    scanf("%d", &escolha);
                    if((escolha != 1) && (escolha!= 2)){
                        system("cls");
                        printf("Resposta invalida! Digite novamente\n\n(Aperte qualquer tecla para continuar)");
                        getch();
                        system("cls");
                        goto Resposta;
                    }
                if(escolha == 1){
                    casas[achados].areaTerreno = -1;
                    FILE *casasPtr;

                    contador = 0;

                    if((casasPtr = fopen("casas.txt", "w")) == NULL){
                        printf("Erro ao ler o arquivo\n");
                    }
                    else{
                        for(i = 0; i < 100; i++){
                            if(casas[i].areaTerreno != 0)
                                contador++;
                        }

                        for(i = 0; i < contador; i++){
                            if(casas[i].areaTerreno != -1 && casas[i].areaTerreno != 0){
                                fprintf(casasPtr, "%s", casas[i].tituloImovel);
                                fprintf(casasPtr, "%s" , casas[i].cidade);
                                fprintf(casasPtr, "%s", casas[i].bairro);
                                fprintf(casasPtr, "%s", casas[i].endereco);
                                fprintf(casasPtr, "%d\n%d\n%lf\n%lf\n%d\n%d\n%d\n%lf\n", casas[i].CEP, casas[i].numero, casas[i].areaTerreno, casas[i].areaConstruida, casas[i].pavimentos, casas[i].numeroQuartos, casas[i].tipoPagamento, casas[i].valor);
                            }
                        }

                        fclose(casasPtr);
                    }
                }
            }
            break;
        case 'a':
            printf("Insira o andar do imovel: ");
            scanf("%d", &andar);

            system("cls");
            for(i = 0; i < 100; i++){
                if(apartamentos[i].areaTerreno > 0){
                    if((apartamentos[i].CEP == CEP) && (apartamentos[i].numero == numero) && (apartamentos[i].andar == andar)){
                        imprimeImovel(i,'a');
                        achados = i;
                        a++;
                    }
                }
            }
            if(a != 0){
                resposta:
                    printf("Deseja remover este imovel? (1 - sim ou 2 -nao):\n");

                    scanf("%d", &escolha);
                    if((escolha != 1) && (escolha!= 2)){
                        system("cls");
                        printf("Resposta invalida! Digite novamente\n\n(Aperte qualquer tecla para continuar)");
                        getch();
                        system("cls");
                        goto resposta;
                    }

                if(escolha == 1){
                    apartamentos[achados].areaTerreno = -1;
                    FILE *apartamentosPtr;

                    if((apartamentosPtr = fopen("apartamentos.txt", "w")) == NULL){
                        printf("Erro ao ler o arquivo\n");
                    }
                    else{
                        contador = 0;

                        for(i = 0; i < 100; i++){
                            if(apartamentos[i].areaTerreno != 0)
                                contador++;
                        }

                        for(i = 0; i < contador; i++){
                            if(apartamentos[i].areaTerreno != -1 && apartamentos[i].areaTerreno != 0){
                                fprintf(apartamentosPtr, "%s", apartamentos[i].tituloImovel);
                                fprintf(apartamentosPtr, "%s", apartamentos[i].posicao);
                                fprintf(apartamentosPtr, "%s", apartamentos[i].cidade);
                                fprintf(apartamentosPtr, "%s", apartamentos[i].bairro);
                                fprintf(apartamentosPtr, "%s", apartamentos[i].endereco);
                                fprintf(apartamentosPtr, "%d\n%d\n%d\n%lf\n%d\n%d\n%lf\n%lf\n%d", apartamentos[i].CEP, apartamentos[i].numero, apartamentos[i].andar, apartamentos[i].areaTerreno, apartamentos[i].numeroQuartos, apartamentos[i].tipoPagamento, apartamentos[i].valor, apartamentos[i].valorCondominio, apartamentos[i].numVagasGaragem);
                            }
                        }

                        fclose(apartamentosPtr);
                    }
                }
            }
            break;
        default:
            system("cls");
            for(i = 0; i < 100; i++){
                if(terrenos[i].areaTerreno > 0){
                    if((terrenos[i].CEP == CEP) && (terrenos[i].numero == numero)){
                        imprimeImovel(i,'t');
                        achados = i;
                        a++;
                    }
                }
            }
            if(a != 0){
                decisao:
                    printf("Deseja remover este imovel? (1 - sim ou 2 -nao):\n");
                    scanf("%d", &escolha);
                    if((escolha != 1) && (escolha!= 2)){
                        printf("\nResposta invalida! Digite novamente\n\n(Aperte qualquer tecla para continuar)");
                        getch();
                        system("cls");
                        goto decisao;
                    }

                if(escolha == 1){
                    terrenos[achados].areaTerreno = -1;

                    FILE *terrenosPtr;

                    if((terrenosPtr = fopen("terrenos.txt", "w")) == NULL)
                        printf("Erro ao ler o arquivo\n");
                    else{
                        contador = 0;

                        for(i = 0; i < 100; i++){
                            if(terrenos[i].areaTerreno != 0)
                                contador++;
                        }

                        for(i = 0; i < contador; i++){
                            if(terrenos[i].areaTerreno != -1 && terrenos[i].areaTerreno != 0){
                                fprintf(terrenosPtr, "%s", terrenos[i].tituloImovel);
                                fprintf(terrenosPtr, "%s", terrenos[i].cidade);
                                fprintf(terrenosPtr, "%s", terrenos[i].bairro);
                                fprintf(terrenosPtr, "%s", terrenos[i].endereco);
                                fprintf(terrenosPtr, "%d\n%d\n%lf\n%d\n%lf\n", terrenos[i].numero, terrenos[i].CEP, terrenos[i].areaTerreno, terrenos[i].tipoPagamento, terrenos[i].valor);
                            }
                        }

                        fclose(terrenosPtr);
                    }
                }
            }
            break;
    }

    system("cls");
    if(a == 0){
        printf("Nao foi encontrado nenhum imovel neste bairro\n");
    }
    else{
        printf("Imovel excluido!\n");
    }

    printf("\nTecle ESC para voltar ao menu");

    while(escolha!=ESC){
        escolha = getch();
    }
}

void remover(void){
    int variavelRemover=1, flag=0;

	while(flag==0){
		system("cls");
		switch(variavelRemover){
			case 1:
				printf("-----------------Remover---------------------\n"
					   "\t\tCasa\n"
					   "\tApartamento\n"
					   "\tTerreno\n\n\n"
					   "\tPara voltar ao MENU pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
                        remocao('c');
                        variavelRemover=0;
						break;
					case CIMA:
						variavelRemover=3;
						break;
					case BAIXO:
						variavelRemover=2;
						break;
					case ESC:
						variavelRemover=0;
						break;
					default:
						continue;
				}
				break;
            case 2:
				printf("-----------------Remover---------------------\n"
					   "\tCasa\n"
					   "\t\tApartamento\n"
					   "\tTerreno\n\n\n"
					   "\tPara voltar ao MENU pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
                        remocao('a');
                        variavelRemover=0;
						break;
					case CIMA:
						variavelRemover=1;
						break;
					case BAIXO:
						variavelRemover=3;
						break;
					case ESC:
						variavelRemover=0;
						break;
					default:
						continue;
				}
				break;
            case 3:
				printf("-----------------Remover---------------------\n"
					   "\tCasa\n"
					   "\tApartamento\n"
					   "\t\tTerreno\n\n\n"
					   "\tPara voltar ao MENU pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
                        remocao('t');
                        variavelRemover=0;
						break;
					case CIMA:
						variavelRemover=2;
						break;
					case BAIXO:
						variavelRemover=1;
						break;
					case ESC:
						variavelRemover=0;
						break;
					default:
						continue;
				}
				break;
            default:
				flag=1;
				break;
		}
	}
}
void editar(void){
    int variavelEditar=1, flag=0;

	while(flag==0){
		system("cls");
		switch(variavelEditar){
			case 1:
				printf("-----------------Editar---------------------\n"
					   "\t\tCasa\n"
					   "\tApartamento\n"
					   "\tTerreno\n\n\n"
					   "\tPara voltar ao MENU pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
                        edicaoCasa();
                        variavelEditar=0;
						break;
					case CIMA:
						variavelEditar=3;
						break;
					case BAIXO:
						variavelEditar=2;
						break;
					case ESC:
						variavelEditar=0;
						break;
					default:
						continue;
				}
				break;
            case 2:
				printf("-----------------Editar---------------------\n"
					   "\tCasa\n"
					   "\t\tApartamento\n"
					   "\tTerreno\n\n\n"
					   "\tPara voltar ao MENU pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
                        edicaoApt();
                        variavelEditar=0;
						break;
					case CIMA:
						variavelEditar=1;
						break;
					case BAIXO:
						variavelEditar=3;
						break;
					case ESC:
						variavelEditar=0;
						break;
					default:
						continue;
				}
				break;
            case 3:
				printf("-----------------Editar---------------------\n"
					   "\tCasa\n"
					   "\tApartamento\n"
					   "\t\tTerreno\n\n\n"
					   "\tPara voltar ao MENU pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
                        edicaoTer();
                        variavelEditar=0;
						break;
					case CIMA:
						variavelEditar=2;
						break;
					case BAIXO:
						variavelEditar=1;
						break;
					case ESC:
						variavelEditar=0;
						break;
					default:
						continue;
				}
				break;
            default:
				flag=1;
				break;
		}
	}
}
void consultar(void){
    int variavelConsulta=1, flag=0;

	while(flag==0){
		system("cls");
		switch(variavelConsulta){
			case 1:
				printf("-----------------Imoveis Disponiveis---------------------\n"
					   "\t\tCasa\n"
					   "\tApartamento\n"
					   "\tTerreno\n\n\n"
					   "\tPara voltar ao MENU pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
                        tipo('c');
                        variavelConsulta=0;
						break;
					case CIMA:
						variavelConsulta=3;
						break;
					case BAIXO:
						variavelConsulta=2;
						break;
					case ESC:
						variavelConsulta=0;
						break;
					default:
						continue;
				}
				break;
            case 2:
				printf("-----------------Imoveis Disponiveis---------------------\n"
					   "\tCasa\n"
					   "\t\tApartamento\n"
					   "\tTerreno\n\n\n"
					   "\tPara voltar ao MENU pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
                        tipo('a');
                        variavelConsulta=0;
						break;
					case CIMA:
						variavelConsulta=1;
						break;
					case BAIXO:
						variavelConsulta=3;
						break;
					case ESC:
						variavelConsulta=0;
						break;
					default:
						continue;
				}
				break;
            case 3:
				printf("-----------------Imoveis Disponiveis---------------------\n"
					   "\tCasa\n"
					   "\tApartamento\n"
					   "\t\tTerreno\n\n\n"
					   "\tPara voltar ao MENU pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
                        tipo('t');
                        variavelConsulta=0;
						break;
					case CIMA:
						variavelConsulta=2;
						break;
					case BAIXO:
						variavelConsulta=1;
						break;
					case ESC:
						variavelConsulta=0;
						break;
					default:
						continue;
				}
				break;
            default:
				flag=1;
				break;
		}
	}
}
void buscar(void){
	int variavelBusca=1, flag=0;

	while(flag==0){
		system("cls");
		switch(variavelBusca){
			case 1:
				printf("----------------------Busca-------------------------\n"
					   "\t\tBairro\n"
					   "\tTitulo\n"
					   "\tValor\n\n\n"
					   "\tPara voltar ao MENU pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
						buscaBairro();
                        variavelBusca=0;
						break;
					case CIMA:
						variavelBusca=3;
						break;
					case BAIXO:
						variavelBusca=2;
						break;
					case ESC:
						variavelBusca=0;
						break;
					default:
						continue;
				}
				break;
			case 2:
				printf("----------------------Busca-------------------------\n"
					   "\tBairro\n"
					   "\t\tTitulo\n"
					   "\tValor\n\n\n"
					   "\tPara voltar ao MENU pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
						buscaTitulo();
						variavelBusca=0;
						break;
					case CIMA:
						variavelBusca=1;
						break;
					case BAIXO:
						variavelBusca=3;
						break;
					case ESC:
						variavelBusca=0;
						break;
					default:
						continue;
				}
				break;
			case 3:
				printf("----------------------Busca-------------------------\n"
					   "\tBairro\n"
					   "\tTitulo\n"
					   "\t\tValor\n\n\n"
					   "\tPara voltar ao MENU pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
						buscaValor();
						variavelBusca=0;
						break;
					case CIMA:
						variavelBusca=2;
						break;
					case BAIXO:
						variavelBusca=1;
						break;
					case ESC:
						variavelBusca=0;
						break;
					default:
						continue;
				}
				break;
			default:
				flag=1;
				break;
		}
	}
}
void cadastrar(void){
    int variavelCadastro=1,flag=0;

    while(flag==0){
        system("cls");
        switch(variavelCadastro){     //switch para navegar no menu 'cadastro', sendo 'variavelCadastro' o comando
           case 1:
                printf("-------------------Cadastrar----------------------\n\n"
                    "\t\tCasa\n"
                    "\tTerreno\n"
                    "\tApartamento\n\n\n"
                    "\tAperte ESC para voltar ao MENU\n");

                escolha=getch();
                switch(escolha){
					case ENTER:
						cadastraCasa();
						variavelCadastro=0;
						break;
					case CIMA:
						variavelCadastro=3;
						break;
					case BAIXO:
						variavelCadastro=2;
						break;
					case ESC:
						variavelCadastro=0;
						break;
					default:
						continue;
				}

                break;
            case 2:
                printf("-------------------Cadastrar----------------------\n\n"
                    "\tCasa\n"
                    "\t\tTerreno\n"
                    "\tApartamento\n\n\n"
                    "\tAperte ESC para voltar ao MENU\n");

                escolha=getch();
                switch(escolha){
                    case ENTER:
						cadastraTer();
						variavelCadastro=0;
						break;
					case CIMA:
						variavelCadastro=1;
						break;
					case BAIXO:
						variavelCadastro=3;
						break;
					case ESC:
						variavelCadastro=0;
						break;
					default:
						continue;
				}
                break;
            case 3:
                printf("-------------------Cadastrar----------------------\n\n"
                    "\tCasa\n"
                    "\tTerreno\n"
                    "\t\tApartamento\n\n\n"
                    "\tAperte ESC para voltar ao MENU\n");

                escolha=getch();
                switch(escolha){
                    case ENTER:
						cadastraApt();
						variavelCadastro=0;
						break;
					case CIMA:
						variavelCadastro=2;
						break;
					case BAIXO:
						variavelCadastro=1;
						break;
					case ESC:
						variavelCadastro=0;
						break;
					default:
						continue;
				}
                break;
            default:
                flag=1;
                break;
        }
    }
}
int Menu(void){
	int variavelMenu=1, flag=0;
	printf("\a");


	while(flag==0){                        //enquanto a bandeira permanecer em 0, significa que o usuário não pediu para sair do programa
		system("cls");
		switch(variavelMenu){              //navegar pelo 'MENU'
			case 1:
				printf("\t\t\t\tMenu\n"
					   "\t\tCadastrar\n"
					   "\tConsultar\n"
					   "\tBuscar imovel\n"
					   "\tRemover\n"
					   "\tEditar\n\n\n"
					   "\tPara encerrar o programa, pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:                 //Caso clique em ENTER,sse dirige para a função 'CADASTRO'
                        cadastrar();
						break;
					case CIMA:
						variavelMenu=5;
						break;
					case BAIXO:
						variavelMenu=2;
						break;
					case ESC:
						variavelMenu=0;
						break;
					default:
						continue;
				}
				break;
			case 2:
				printf("\t\t\t\tMenu\n"
					   "\tCadastrar\n"
					   "\t\tConsultar\n"
					   "\tBuscar imovel\n"
					   "\tRemover\n"
					   "\tEditar\n\n\n"
					   "\tPara encerrar o programa, pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
						consultar();                 //Caso clique em ENTER,sse dirige para a função 'CONSULTA'
						break;
					case CIMA:
						variavelMenu=1;
						break;
					case BAIXO:
						variavelMenu=3;
						break;
					case ESC:
						variavelMenu=0;
						break;
					default:
						continue;
				}
				break;
			case 3:
				printf("\t\t\t\tMenu\n"
					   "\tCadastrar\n"
					   "\tConsultar\n"
					   "\t\tBuscar imovel\n"
					   "\tRemover\n"
					   "\tEditar\n\n\n"
					   "\tPara encerrar o programa, pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
						buscar();                   //Caso clique em ENTER,sse dirige para a função 'BUSCA'
						break;
					case CIMA:
						variavelMenu=2;
						break;
					case BAIXO:
						variavelMenu=4;
						break;
					case ESC:
						variavelMenu=0;
						break;
					default:
						continue;
				}
				break;
			case 4:
				printf("\t\t\t\tMenu\n"
					   "\tCadastrar\n"
					   "\tConsultar\n"
					   "\tBuscar imovel\n"
					   "\t\tRemover\n"
					   "\tEditar\n\n\n"
					   "\tPara encerrar o programa, pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
                        remover();                      //Caso clique em ENTER,sse dirige para a função 'REMOVER'
						break;
					case CIMA:
						variavelMenu=3;
						break;
					case BAIXO:
						variavelMenu=5;
						break;
					case ESC:
						variavelMenu=0;
						break;
					default:
						continue;
				}
				break;
			case 5:
				printf("\t\t\t\tMenu\n"
					   "\tCadastrar\n"
					   "\tConsultar\n"
					   "\tBuscar imovel\n"
					   "\tRemover\n"
					   "\t\tEditar\n\n\n"
					   "\tPara encerrar o programa, pressione ESC\n");

				escolha= getch();
				switch(escolha){
					case ENTER:
						editar();
						break;
					case CIMA:
						variavelMenu=4;
						break;
					case BAIXO:
						variavelMenu=1;
						break;
					case ESC:
						variavelMenu=0;
						break;
					default:
						continue;
				}
				break;
			default:
				flag=1;
				break;
		}
	}
	return 0;
}
int main(void){
    iniciador();
	if(!Menu())

    return 0;
}

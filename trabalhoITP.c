#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
/*NOTA: quando quadrinho é lido, o valor de 'lido' é 1. caso contrário lido = 0
Formato do Quadrinho : 
    titulo(%s) numeroRevista(%d) lido(%d) dia(%d) mes(%d) ano(%d) personagem(%s)
*/
typedef struct {
    char titulo[200];
    int numero;
    int dia,mes,ano;
    int lido;
    char personagens[500];
}Quadrinho;
//Só para ter uma sensação de espera :p
void frescura(char* palavra){
    for(int c = 0; c < 3;c++){
        printf("%s ",palavra);
        for(int j = 0; j<3;j++){
            printf(".");
            Sleep(300);
        }
        printf("\r");
        for (int j = 0; j < 60; j++) {
            printf(" "); // apaga a linha anterior
        }
        printf("\r");
    }
    printf("\n");
    fflush(stdin);
}
//Reparei que na função cinco irei printar nesse formato varias vezes
void printarQuadrinho(int posicao,Quadrinho* quadrinhos){
            printf("Titulo : %s     ",quadrinhos[posicao].titulo);
            printf("numero : %d     ",quadrinhos[posicao].numero);
            if(quadrinhos[posicao].lido==0){
                printf("Lido : NAO");
            }else{
                printf("Lido : SIM");
            }
            printf("    Data : %02d/%02d/%d\n",quadrinhos[posicao].dia,quadrinhos[posicao].mes,quadrinhos[posicao].ano);
}
int carregarDados(Quadrinho* quadrinhos){
    FILE* dados = fopen("dados01.txt","r");
    int cont = 0;//serve para saber quantos quadrinhos tenho na minha base de dados
    if(dados==NULL){
        printf("Base de dados Vazia");
    }else{
        while(feof(dados)==0){
            
            if(fgetc(dados)=='\n'){
                cont++;
            }     
        }
        fclose(dados);
        realloc(quadrinhos,cont*sizeof(int));
        //como já verifiquei que o arquivo é != de NULL não preciso verificar novamente
        //LEMBRETE: dar o free na função de sair 
        FILE* base = fopen("dados01.txt","r");
        cont = 0;
        do{
            fscanf(base,"%s %d %d %d %d %d %[^\n]s",quadrinhos[cont].titulo,&quadrinhos[cont].numero,&quadrinhos[cont].lido,&quadrinhos[cont].dia,&quadrinhos[cont].mes,&quadrinhos[cont].ano,quadrinhos[cont].personagens);
            
            cont++;
            
        }while(feof(base)==0);
        if(quadrinhos[0].numero==0){
            printf("Base de dados vazia\n");
        }
         
    }
    return cont-1;

}
void  addQuadrinho(int* tamanho, Quadrinho* qud){
    int igual = 0;
    char nomeTitulo[200];
    int numRev=05;
    int dia,mes, ano;
    char elenco[500];
    fflush(stdin);
    printf("Digite o titulo da obra : ");
    scanf("%[^\n]s",nomeTitulo);
    printf("Digite o numero da revista, data (dia/mes/ano) e elenco da obra : ");
    scanf("%d %d %d %d %[^\n]s\n",&numRev,&dia,&mes,&ano,elenco); 
    //Se tiver alguma revista igual, igual fica com 1
    for(int c = 0; c <*tamanho;c++){
        
        if(qud[c].numero==numRev && strcmp(nomeTitulo,qud[c].titulo)==0){
            igual = 1;
        }
    }
    if(igual!=0){
        printf("Revista já cadastrada!");
    }else{ 

        realloc(qud,*tamanho+1*sizeof(Quadrinho));

        strcpy(qud[*tamanho].titulo,nomeTitulo);
        strcpy(qud[*tamanho].personagens,elenco);
        qud[*tamanho].numero = numRev;
        qud[*tamanho].dia = dia;
        qud[*tamanho].mes = mes;
        qud[*tamanho].ano = ano; 
        *tamanho +=1;

        FILE* arqui = fopen("dados01.txt","a+");
        
        if(arqui==NULL){
            printf("Problema ao abrir arquivo!");
        }else{
            fprintf(arqui,"%s %d %d %d %d %d %s\n",nomeTitulo,numRev,0,dia,mes,ano,elenco);  
        }
        fclose(arqui);
    }       

}
void removerQuadrinho(int* tamanho,Quadrinho* quadri){
    char titulo [200];
    int num = 0;
    int pos = 0; //salva a posição do vetor na qual o elemento foi removido
    /*Variáves com o prefixo 'auxi' são variáveis auxiliares que irão guardar os dados
    da ultima posição do vetor dinâmico*/
    char auxiTitulo[200],auxiElenco[200];
    int auxiNum,auxiDia,auxiMes,auxiLido,auxiAno;

    fflush(stdin);
    
    scanf("%s %d",titulo,&num);
    FILE* arquivo = fopen("dados01.txt","w");
    if(arquivo==NULL){
        printf("erro ao abrir arquivo");
    }else{
        int a;
        for( a= 0; a< *tamanho; a++){
            if(titulo!=quadri[a].titulo && num!=quadri[a].numero){
                fprintf(arquivo,"%s %d %d %d %d %d %s\n",quadri[a].titulo,quadri[a].numero,quadri[a].lido,quadri[a].dia,quadri[a].mes,quadri[a].ano,quadri[a].personagens);
            }else{
                *tamanho-=1;//Ajusta o tamanho do vetor dinamico.
            }
        }


    }

        fclose(arquivo);
        carregarDados(quadri);
}
void consulQuedrinho(int* tamanho, Quadrinho* quadrinho){
    char titulo[200];
    int numero;
    int igual = 0;
    int a = 0;
    fflush(stdin);
    printf("Digite o nome do quadrinho : ");
    gets(titulo);
    printf("Digite o numero do quadrinho : ");
    scanf("%d",&numero);
    for(a;a<*tamanho;a++){
        if(strcmp(titulo,quadrinho[a].titulo)==0 && numero == quadrinho[a].numero){
            igual=1;
            break;
        }
    }
    
    if(igual==1){
        printf("Nome : %s\n",quadrinho[a].titulo);
        printf("Numero : %d     Data : %d/%d/%d\n",quadrinho[a].numero,quadrinho[a].dia,quadrinho[a].mes,quadrinho[a].ano);
        printf("Elenco : %s\n",quadrinho[a].personagens);
    }else{
        printf("MEEEN, Digitou errado ou ta procurando coisa que nao existe,o famoso paranoico");
    }
}

void marcarLido(int* tamanho,Quadrinho* quadrinho){
    //Falta escrever no arquivo
    char titulo[200];
    int numero;
    int a = 0;
    int igual = 0;
    printf("Digite o nome do quadrinho\n");
    fflush(stdin);

    gets(titulo);
    printf("Digite o numero da revista\n");
    scanf("%d",&numero);

    for(a;a<*tamanho;a++){
        if(strcmp(titulo,quadrinho[a].titulo)==0 && numero==quadrinho[a].numero){
            igual = 1;
            break;
        }
    }
    
    if(igual==1){
        if(quadrinho[a].lido==0){
            quadrinho[a].lido = 1;
            frescura("Marcando Quadrinho");

            //escrevendo no arquivo
            FILE* arquivo = fopen("dados01.txt","w");
    
            if(arquivo==NULL){
                printf("Erro ao abrir arquivo");
            }else{
            for(int c=0 ; c<*tamanho;c++){
                   fprintf(arquivo,"%s %d",quadrinho[c].titulo,quadrinho[c].numero);
                   fprintf(arquivo," %d %d",quadrinho[c].lido,quadrinho[c].dia);
                   fprintf(arquivo," %d %d",quadrinho[c].mes,quadrinho[c].ano);
                   fprintf(arquivo," %s\n",quadrinho[c].personagens);             
            }
            frescura("Escrevendo no arquivo");
            fclose(arquivo);

        }
        }else{
            printf("Quadrinho Ja marcado");
        }
    }else{
        printf("Quadrinho nao encontrado");
    }
   
}
//fazendo o subMenu da 5
void menuCinco(){
    printf("----------------------\n");
    printf("| Listar quadrinho : |\n");
    printf("| 1 - Por ano        |\n");
    printf("| 2 - Por periodo    |\n");
    printf("| 3 - Por personagem |\n");
    printf("| 4 - Por Titulo     |\n");
    printf("| 5 - Por lidos      |\n");
    printf("----------------------\n");

}
void porAno(int* tamanho,Quadrinho* quadrinhos){
    printf("Consulta por ano\n");
    int ano = 0;
    
    printf("Digite o ano(Ex:1985)\n");
    scanf("%d",&ano);
    printf("\n");
    for(int c = 0; c<*tamanho;c++){

        if(ano==quadrinhos[c].ano){
            printarQuadrinho(c,quadrinhos);
        }
    }


}
void porPeriodo(int* tamanho,Quadrinho* quadrinhos){
    int mesIni,anoIni;//mes e ano inicial
    int mesFin,anoFin;//mes e ano Final
    printf("Consulta por periodo\n");
    
    printf("Digite o mes e ano inicial\n");
    scanf("%d %d",&mesIni,&anoIni);

    printf("Digite o mes e ano final\n");
    scanf("%d %d",&mesFin,&anoFin);
    for(int c = 0; c<*tamanho;c++){
        //Irei verificar pelo ano
        if(anoIni < quadrinhos[c].ano && quadrinhos[c].ano<anoFin){
            printarQuadrinho(c,quadrinhos);
        }else if(anoIni==quadrinhos[c].ano && mesIni<=quadrinhos[c].mes || anoFin==quadrinhos[c].ano && quadrinhos[c].mes <= mesFin){
            printarQuadrinho(c,quadrinhos);
        }
        
    }
   
    
}
void porPersonagem(int* tamanho,Quadrinho* quadrinhos){
    //Falta Fazer
    char persona[100];
    
    fflush(stdin);
    gets(persona);
    
}
void porTitulo(int* tamanho, Quadrinho* quadrinhos){
    char titulo[200];
    printf("Digite o titulo do quadrinho\n");
    fflush(stdin);
    gets(titulo);

    for(int c = 0; c< *tamanho;c++){
        if(strcmp(titulo,quadrinhos[c].titulo)==0){
            printarQuadrinho(c,quadrinhos);
        }
    }

}
void porLidos(int* tamanho,Quadrinho* quadrinhos){
    for(int c = 0; c<*tamanho;c++){
        if(quadrinhos[c].lido==1){
            printarQuadrinho(c,quadrinhos);
        }

    }
}
//Minha listagem vai seguir o seguinte formato: titulo numero lido dia/mes/ano
void consultaGerais(int* tamanho, Quadrinho* quadrinhos){
    int escolha;
    menuCinco();
    //Usei só para ter certeza que vai dar bom
    fflush(stdin);
    scanf("%d",&escolha);
    
    switch(escolha){
        case 1: porAno(tamanho,quadrinhos);break;
        case 2: porPeriodo(tamanho,quadrinhos);break;
        case 3: porPersonagem(tamanho,quadrinhos);break;
        case 4: porTitulo(tamanho,quadrinhos);break;
        case 5: porLidos(tamanho,quadrinhos);break;
    }


}

int main(){
    int escolha = 0;
    int c = 0;
    Quadrinho* quadrinhos = calloc(2 , sizeof(Quadrinho));//espaço padrão
    while(escolha!=7){
        printf("\n1 - Casarregar base de dados\n");
        printf("2 - Adicionar um quadrinho\n");
        printf("3 - Remover um quadrinho\n");
        printf("4 - Consulta um quadrinho\n");
        printf("5 - Consultas gerais\n");
        printf("6 - Marcar como lido\n");
        printf("7 - Sair\n");

        scanf("%d",&escolha);
        switch(escolha){
            case 1: c = carregarDados(quadrinhos);break; // c irá guardar a quantidade de quadrinhos.
            case 2:addQuadrinho(&c,quadrinhos);break;//irei usar o c aqui para adicionar uma nova hq já no vetor alocado.
            case 3:removerQuadrinho(&c,quadrinhos);break;
            case 4:consulQuedrinho(&c,quadrinhos);break;
            case 5: consultaGerais(&c,quadrinhos);break;
            case 6: marcarLido(&c,quadrinhos);break;
            case 7: free(quadrinhos);
                    frescura("SAINDO");
                break;
            case 8: 
                for(int a = 0; a < c;a++){
                    printf("%s %d %d %d/%d/%d %s\n",quadrinhos[a].titulo,quadrinhos[a].numero,quadrinhos[a].lido,quadrinhos[a].dia,quadrinhos[a].mes,quadrinhos[a].ano,quadrinhos[a].personagens);
                }
                break;

        }
        



    }


    return 0;
}
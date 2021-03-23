//Você deve escrever um programa para controle de uma locadora de automóveis
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAM 100
//Definindo as structs para salvar os daddos
//Struct carros guarda todos os dados relacionados diretamente ao carro
typedef struct carros{
    int id_Carro,espaco;
    char placa[25],fabricante[30],modelo[30];
    char categoria[40],ar;
    int km;
}car;
typedef struct reserva{
    char data[30],dataF[30];
}reservas;
//Struct dados relaciona os dados  sobre o carro e sobre sua disponibilidade para o controle da locadora
typedef struct Dados{
    car carro;
    reservas data;
    char disp;
    int link;
}dados;
dados lista[TAM];
int leituraMain(){
    puts("Bem vindo ao manual!");
    //Inicializa sempre como 0 para que entre no loop do while e mostre o manual para o usuário
    int operando = 0;
    while(operando <= 0 || operando >= 11){
        printf("1-> Inserir um novo carro no cadastro\n2-> Remover um carro do cadastro\n3-> Listar carros de uma determinada categoria que estejam disponíveis em uma determinada data\n4-> Listar carros que estejam disponíveis hoje\n5-> Verificar quando um determinado carro deve ser devolvido\n");
        printf("6-> Fazer a reserva de um carro de uma determinada categoria para um certo período\n7-> Liberar a reserva de um carro quando não ocorrer sua retirada no dia reservado\n8-> Atualizar os dados de um veículo no seu retorno\n9-> Fechar o programa atualizando o arquivo de cadastro\n");
        scanf("%d",&operando);
    }
    return operando;
}
void zerar(){
    //Função para limpeza de lixo de memória e melhor controle sobre o código
    int k;
    for(k = 0; k < TAM ; k++){
        lista[k].carro.espaco = 0;
        lista[k].carro.id_Carro = 0;
        lista[k].carro.km = 0;
        lista[k].carro.ar = ' ';
        strcpy(lista[k].carro.categoria," ");
        strcpy(lista[k].carro.fabricante," ");
        strcpy(lista[k].carro.modelo," ");
        strcpy(lista[k].carro.placa," ");
        strcpy(lista[k].data.data,"0/0/0");
        strcpy(lista[k].data.dataF,"0/0/0");
        lista[k].disp = ' ';
        lista[k].link = -1;
    }
 }
//A Função manutenção é para auxiliar o usuário durante as escolhas mostrando as opções
void manutencao(int *Qtd,int *head){
    //aux como head para que eu comece da primeira posição de um cadastro existente
    int aux = *head;
        while(aux < *Qtd){
            int aux2 = aux;
            while(lista[aux2-1].link == -1){
                aux2--;
            }
            aux2--;
            if(aux == *head){
                //como não existe cadastro "atrás" do cadastro de head, indentifiquei a necessidade desta verificação para mudar o valor dos indices que serão utilizados
                 printf("\nCarro-> Indice: %d\nId carro: %d\nKm: %d\nCategoria: %s\nModelo: %s\nFabricante: %s\nLINK: %d\n",*head,lista[aux].carro.id_Carro,lista[aux].carro.km,lista[aux].carro.categoria,lista[aux].carro.modelo,lista[aux].carro.fabricante,lista[aux].link);
            }
            else if(lista[aux].link != -1){
                printf("\nCarro-> Indice: %d\nId carro: %d\nKm: %d\nCategoria: %s\nModelo: %s\nFabricante: %s\nLINK: %d\n",lista[aux2].link,lista[aux].carro.id_Carro,lista[aux].carro.km,lista[aux].carro.categoria,lista[aux].carro.modelo,lista[aux].carro.fabricante,lista[aux].link);
            }
            aux++;
        }
    return;
}
//incialmente lendo os dados do arquivo para inicialização do programa
void leituraArq(int *Qtd, int *head, int *Cont){
    int i = 0;
    FILE *fp;
    //aux permite que o caractere \n no arquivo não seja lido pelas strings
    char aux,linha[100];
    //dados dentro do arquivo estarão neste formato, portanto, a leitura de arquivo se adequou à este 
    // ID_carro Placa Fabricante Modelo
    // Disponibilidade(S/N) Categoria Num_ocupantes Ar_condicionado(S/N)
    // Quilometragem
    // Início_reserva Final_reserva (no formato nn/nn/nnnn se houver reserva 
    // ou uso e 0/0/0 indicando que não há reserva)
    //verifica se o arquivo foi aberto com sucesso, pois fopen retorna um ponteiro do tipo FILE, caso este seja NULL, então ocorreu erro
    if((fp = fopen("listacarros.dat","r+"))== NULL){
        puts("Arquivo não aberto com sucesso\n");
        return;
    }
    else{
        //Loop para que chegue até o fim do arquivo
        while(!feof(fp)){
            //leitura da primeira linha com auxilio da Var. aux para "\n", e armazenamento nas variáveis
            //uso do fgets para facilitar à modificação dos valores parar variáveis por conta dos espaços e \n
            fgets(linha, 199, fp);
            sscanf(linha, "%d %s %s %s",&lista[i].carro.id_Carro,lista[i].carro.placa,lista[i].carro.fabricante,lista[i].carro.modelo);
            strcpy(linha, "");
            fgets(linha, 199, fp);
            sscanf(linha, "%c %s %d %c",&lista[i].disp, lista[i].carro.categoria, &lista[i].carro.espaco, &lista[i].carro.ar);
            strcpy(linha, "");
            fgets(linha, 199, fp);
            sscanf(linha, "%d", &lista[i].carro.km);
            strcpy(linha, "");
            fgets(linha, 199, fp);
            sscanf(linha,"%s %s", lista[i].data.data,lista[i].data.dataF);
            strcpy(linha, "");
            //aqui fazemos a conexão entre as estruturas
            lista[i].link = i+1;
            i++;
        }
        //apontamento para -1 indicando que não será lida
        printf("Valor de i: %d\n",i);
        lista[i].link = -1;
        //como arquivo lê uma a mais, por conta do tempo para indentificação do erro e saida do loop, é ncessário reduzir um na posição atual
        i--;
        printf("Valor de i: %d\n",i-1);
        lista[i-1].link = -2;
    }
    *head = 0;
    *Qtd = i;
    *Cont = i;
     // após efetuada toda leitura, o arquivo deve ser fechado.
    fclose(fp);
    return;
}
void inserir(int *Qtdc,int *head,int *Cont){
    system("clear");
    // i recebe Qtdc que é a quantidade de cadastros, para que comece a leitura da posição correta
    int i = *Qtdc;
    puts("Bem vindo a área de inserção de um novo cadastro");
    //TAM é o máximo de cadastros possíveis
    if(i == TAM){
        puts("Limite de cadastro atingido");
        return;
    }
    //while faz as verificações de entrada, necessárias para casos de mau uso ou para deslizes
        setbuf(stdin,NULL);
        printf("Digite o ID do novo carro\n");
        scanf("%d",&lista[i].carro.id_Carro);
        while(lista[i].carro.id_Carro < 0){
            printf("Digite o ID do novo carro, validos apenas valores positivos\n");
            scanf("%d",&lista[i].carro.id_Carro);
        }
        setbuf(stdin,NULL);
        printf("Digite o espaço do novo carro\n");
        scanf("%d",&lista[i].carro.espaco);
        while(lista[i].carro.espaco < 0){
            printf("Digite o espaço do novo carro, valor positivo\n");
            scanf("%d",&lista[i].carro.espaco);
        }
        setbuf(stdin,NULL);
        puts("Digite a Placa do novo carro");
        scanf("%s",lista[i].carro.placa);
        setbuf(stdin,NULL);
        puts("Digite o Fabricante do novo carro");
        scanf("%s",lista[i].carro.fabricante);
        setbuf(stdin,NULL);
        puts("Digite o Modelo do novo carro");
        scanf("%s",lista[i].carro.modelo);
        setbuf(stdin,NULL);
        puts("Digite a Categoria do novo carro");
        puts("Categorias Válidas: Compacto, Médio, Grande, SUV, Minivan.");
        scanf("%s",lista[i].carro.categoria);
        while(strcmp(lista[i].carro.categoria,"Compacto") != 0 && strcmp(lista[i].carro.categoria,"Médio") != 0 && strcmp(lista[i].carro.categoria,"SUV") != 0 && strcmp(lista[i].carro.categoria,"Minivan") != 0 && strcmp(lista[i].carro.categoria,"Grande") != 0){
            puts("Categorias Válidas: Compacto, Médio, Grande, SUV, Minivan.");
            scanf("%s",lista[i].carro.categoria);
        }
        setbuf(stdin,NULL);
        puts("Possui ar condicionado S/N");
        scanf("%c",&lista[i].carro.ar);
        while(lista[i].carro.ar != 'N' && lista[i].carro.ar != 'S'){
            setbuf(stdin,NULL);
            puts("Entradas válidas,por favor S/N");
            setbuf(stdin,NULL);
            scanf("%c",&lista[i].carro.ar);
        }
        puts("Digite a quilometragem do novo carro");
        scanf("%d",&lista[i].carro.km);
        while(lista[i].carro.km < 0){
            puts("Digite a quilometragem do novo carro, valores positivos");
            scanf("%d",&lista[i].carro.km);
        }
        setbuf(stdin,NULL);
        puts("Carro já disponível para alugar?S/N");
        scanf("%c",&lista[i].disp);
        setbuf(stdin,NULL);
        while(lista[i].disp != 'N' && lista[i].disp != 'S'){
            setbuf(stdin,NULL);
            puts("Carro já disponível para alugar?S/N");
            scanf("%c",&lista[i].disp);  
        }
        strcpy(lista[i].data.data,"0/0/0");
        strcpy(lista[i].data.dataF,"0/0/0");
        lista[i].link = -2;
        printf("valor de Cont : %d\n",*Cont);
        i++;
        *Qtdc = i;
        (*Cont)++;
        //definindo x como valor de head para facilitar a passagem de parâmetros para a funçao de manutenção(ler comentários sobre)
        int x = *head;
        printf("valor de Cont : %d\n",*Cont);
        //chamada da função manuntencao para auxiliar o usuário à ver os cadastros disponíveis
        setbuf(stdin,NULL);
        manutencao(&i,&x);  
        setbuf(stdin,NULL); 
        //getchar para usuário permanecer o tempo desejado nesta função
        puts("Pressione enter para continuar");
        getchar();
   return;
}
void remover(int *Qtdc, int *head,int *Cont){
    int i = *Qtdc;
    int j = *head,indice;
    //verifica se todos os cadastros foram apagados
    if(*Cont == 0){
        puts("Todos os registros foram apagados");
        return;
    }
    //chama a função manutenção para auxiliar o usuário nas escolhas
    manutencao(&i,&j);
    puts("Digite qual carro você deseja apagar os registros, digite o indice");
    scanf("%d",&indice);
    //novamente, while para validação da entrada
    while(indice < 0 || indice > i){
        puts("Inválido, digite novamente\n");
        scanf("%d",&indice);
    }
    printf("Indice: %d\n",indice);
    if(lista[indice].link  == -1){
        puts("Não existe tal cadastro no sistema\n");
        return;
    }
    //Se for a cabeça do programa, necessitaremos de alterar seu valor e indicar a próxima cabeça
    if(indice == *head){
        puts("Eu vim aqui\n");
        *head = lista[*head].link;
        lista[indice].link = -1;
        while(lista[indice+1].link == -1){
            indice++;
        }
        *(head) = indice+1;
        (*Cont)--;
    }
    // se estivermos apagando a tail do nosso código, necessitaremos de alteração do valor,
    if(lista[indice].link == -2){
        puts("Eu vim aqui2\n");
        lista[indice].link = -1;
        (*Cont)--;
        int aux = *head;
        while(lista[aux].link != indice){
            aux++;
        }
        lista[aux].link = -2;
    }
    //indicamos em outra posição 
    else if(indice != *head && lista[indice].link != -2){
        puts("Eu vim aqui3\n");
        //anteriormente tinhamos aux2 = *head, logo teriamos o problema citado na apresentação de hoje, logo com a inicialização de indice 
        // e caminhando para trás com os indices encontro os valores corretos
        int aux2 = indice;
        int aux1 = indice;
        if(lista[aux1+1].link == -2){
            aux1++;
        }
        else{
            while(lista[aux1+1].link == -1){
             aux1++;
        }
            aux1++;
        }
        while(lista[aux2-1].link != -1){
             aux2--;
        }
        aux2--;
        printf("Valor de aux2: %d\n",aux2);
        lista[aux2].link = aux1;
         lista[indice].link = -1;
        (*Cont)--;
    }
    puts("eU");
    setbuf(stdin,NULL); 
    //getchar para usuário permanecer o tempo desejado nesta função
    puts("Pressione enter para continuar");
    getchar();
    return;
}
// OBS: para uma letra maiscula basta somar modulo de 64 + letra que desejamos em maiúscula
void mostrar(int *Qtdc,int op, int *head){
    //Devido à logicas parecidas, utilizei de um operador de controle para utilizar a mesma função
    if(op == 0){
        system("clear");
        int j = *head,i = *Qtdc;
        int dia,mes,ano;
        int dia1,dia2,mes1,mes2,ano1,ano2;
        char categ[20],c,data[30];
        puts("Digite a categoria que deseja ver"); 
        scanf("%s",categ);
        puts("Digite a data no formato 0/0/0"); 
        scanf("%s",data);  
        sscanf(data,"%d %c %d %c %d",&dia,&c,&mes,&c,&ano);
        while(dia < 0 || dia > 31 || mes < 0 || mes > 12 || ano < 0){
            puts("Digite a data no formato dd/mm/aa, Dia(0-31) || Mês(1-12) || Ano(ano>0)"); 
            scanf("%s",data);  
            sscanf(data,"%d %c %d %c %d",&dia,&c,&mes,&c,&ano);
        }
        while(j < i){
            //como ano é mor na questão de análise de data, portanto começamos com ela e logo após vamos aos casos envolvendo os meses
            if((ano == ano1 && ano == ano2) && strcmp(lista[j].carro.categoria,categ) == 0 && lista[j].disp == 'S'){
                if(mes > mes1 && mes < mes2){
                    printf("Carro: %d, %s, %s não disponívelA\n",lista[j].carro.id_Carro,lista[j].carro.modelo,lista[j].carro.categoria);
                }
                else if(mes == mes1){
                    printf("Carro: %d, %s, %s não disponívelA\n",lista[j].carro.id_Carro,lista[j].carro.modelo,lista[j].carro.categoria);
                }
                else if(mes == mes2 && dia <= dia2){
                    printf("Carro: %d, %s, %s não disponívelA\n",lista[j].carro.id_Carro,lista[j].carro.modelo,lista[j].carro.categoria);   
                }
                else{
                   printf("Disponível: Id_Carro: %d\nModelo:%s\nPlaca:%s\nFabricante:%s\nEspaço:%d\nKM:%d\n\n\n",lista[j].carro.id_Carro,lista[j].carro.modelo,lista[j].carro.placa,lista[j].carro.fabricante,lista[j].carro.espaco,lista[j].carro.km); 
                }
              }
            else if((ano1 < ano2 && ano1 == ano) && strcmp(lista[j].carro.categoria,categ) == 0){
                    printf("Carro: %d, %s, %s não disponívelB\n",lista[j].carro.id_Carro,lista[j].carro.modelo,lista[j].carro.categoria);
                }
            else if((ano1 < ano2 && ano == ano2) && (mes1 <= mes && mes <= mes2) && (dia1 <= dia && dia <= dia2) && strcmp(lista[j].carro.categoria,categ) == 0){
                    printf("Carro: %d, %s, %s não disponível\n",lista[j].carro.id_Carro,lista[j].carro.modelo,lista[j].carro.categoria);

                }
                //caso nenhum dos casos seja verdadeiro, mostramos o carro com disponibilidade
            else if(strcmp(lista[j].carro.categoria,categ) == 0 && lista[j].disp == 'S'){
                printf("Disponível: Id_Carro: %d\nModelo:%s\nPlaca:%s\nFabricante:%s\nEspaço:%d\nKM:%d\n",lista[j].carro.id_Carro,lista[j].carro.modelo,lista[j].carro.placa,lista[j].carro.fabricante,lista[j].carro.espaco,lista[j].carro.km);
                } 
            j++;
        }
        setbuf(stdin,NULL);
        puts("Digite enter para continuar");
        setbuf(stdin,NULL);
        getchar();
        return;
    }
    //caso seja no dia atual, pegamos a data do sistema
    if(op == 1){
        system("clear");
    //variáveis para controle e verificação de disponibilidade
        int dia, mes, ano;
        int dia1,dia2,mes1,mes2,ano1,ano2;
        int j = *head,i = *Qtdc,aux =*head;
        char c;
    //variável do tipo time_t para armazenar a data
        time_t dataatual;
        struct tm * timeinfo;
    //obtendo o tempo em segundos    
        time(&dataatual);
    //para converter de segundos para o tempo local  
    //utilizamos a função localtime 
        timeinfo = localtime(&dataatual);
        dia = timeinfo->tm_mday;
        mes = (timeinfo->tm_mon)+1;
        ano = (timeinfo->tm_year)+1900;
        printf("Data %d/%d/%d\n",dia,mes,ano);
        setbuf(stdin,NULL);
        puts("Pressione enter para confirmar e seguir");
        getchar();
        manutencao(&i,&aux);
        printf("\n\n");
        while(j < i){
            sscanf(lista[j].data.data,"%d %c %d %c %d",&dia1,&c,&mes1,&c,&ano1);
            sscanf(lista[j].data.dataF,"%d %c %d %c %d",&dia2,&c,&mes2,&c,&ano2);
              if((ano == ano1 && ano == ano2)){
                if(mes > mes1 && mes < mes2){
                    printf("Carro: %d, %s, %s não disponívelA\n",lista[j].carro.id_Carro,lista[j].carro.modelo,lista[j].carro.categoria);
                }
                else if(mes == mes1){
                    printf("Carro: %d, %s, %s não disponívelA\n",lista[j].carro.id_Carro,lista[j].carro.modelo,lista[j].carro.categoria);
                }
                else if(mes == mes2 && dia <= dia2){
                    printf("Carro: %d, %s, %s não disponívelA\n",lista[j].carro.id_Carro,lista[j].carro.modelo,lista[j].carro.categoria);   
                }
                else{
                   printf("Disponível: Id_Carro: %d\nModelo:%s\nPlaca:%s\nFabricante:%s\nEspaço:%d\nKM:%d\n\n\n",lista[j].carro.id_Carro,lista[j].carro.modelo,lista[j].carro.placa,lista[j].carro.fabricante,lista[j].carro.espaco,lista[j].carro.km); 
                }
              }
            else if((ano1 < ano2 && ano1 == ano)){
                    printf("Carro: %d, %s, %s não disponívelB\n",lista[j].carro.id_Carro,lista[j].carro.modelo,lista[j].carro.categoria);
                }
            else if((ano1 < ano2 && ano == ano2) && (mes1 <= mes && mes <= mes2) && (dia1 <= dia && dia <= dia2)){
                    printf("Carro: %d, %s, %s não disponível\n",lista[j].carro.id_Carro,lista[j].carro.modelo,lista[j].carro.categoria);

                }
                else{
                    printf("Disponível: Id_Carro: %d\nModelo:%s\nPlaca:%s\nFabricante:%s\nEspaço:%d\nKM:%d\n",lista[j].carro.id_Carro,lista[j].carro.modelo,lista[j].carro.placa,lista[j].carro.fabricante,lista[j].carro.espaco,lista[j].carro.km);
                }      
                j++;   
            }
            setbuf(stdin,NULL); 
            puts("Digite enter para continuar");
            setbuf(stdin,NULL);
            getchar();
            return;
        }
}
void devolver(int *Qtd, int *head){
    int i = *Qtd,j=*head,id,cont = 0;
    system("clear");
    manutencao(&i,&j);
    //O uso do id para mostrar se um carro está disponível ou não é persistente por sua unicidade
    puts("\nDigite o id do carro que deseja ver e a data de retorno"); 
    scanf("%d",&id);
    while(j < i){
        if(lista[j].carro.id_Carro == id && lista[j].link != -1 && (strcmp(lista[j].data.dataF,"0/0/0") != 0)){
            printf("Carro: %s de id(%d) deverá ser devolvido na data %s\n",lista[j].carro.modelo,lista[j].carro.id_Carro,lista[j].data.dataF);
            return;
        }
        else if(lista[j].carro.id_Carro == id && lista[j].link != -1 && (strcmp(lista[j].data.dataF,"0/0/0") == 0) && lista[j].disp == 'S'){
            printf("Carro: %s de id(%d) está aberto à reserva.\n",lista[j].carro.modelo,lista[j].carro.id_Carro);
            return;
        }
        if(lista[j].carro.id_Carro == id)
            cont++;
        j++;
    }
    if(cont == 0)
        puts("Id não coerente com nenhum carro");
    return;
}
void reserva(int *qtdC, int *head){
        int j = *head,i = *qtdC;
        char categ[30],dia[15],diaf[15],c;
        int dia1,dia2,mes1,mes2,ano1,ano2;
        int diau,mesu,anou,aux2;
        puts("Digite a categoria que você deseja reservar");
        scanf("%s",categ);
        puts("Digite a data para retirar o carro");
        scanf("%s",dia);
        setbuf(stdin,NULL);
        puts("Digite a data para devolução do carro");
        scanf("%s",diaf);
        setbuf(stdin,NULL);
        while(j < i){
            if(lista[j].link != -1 && (strcmp(lista[j].carro.categoria,categ) == 0) && lista[j].disp == 'S'){
                // como o sistem é para apenas uma reserva, apenas este caso se encaixa para realização de uma reserva
                if(strcmp(lista[j].data.data,"0/0/0") == 0){
                     printf("\nCarro disponivel: ");
                     printf("ID:%d || Categoria:%s || Modelo:%s\n",lista[j].carro.id_Carro,lista[j].carro.categoria,lista[j].carro.modelo);
                }
            }
            j++;
        }
        setbuf(stdin,NULL);
        puts("Digite o ID do carro que deseja reservar");
        scanf("%d",&aux2);
        //retornamos o valor de j para que possamos passar a última verificação
        j = *head;
        while(j < i){
            if(aux2 == lista[j].carro.id_Carro && lista[j].disp == 'S'){
                strcpy(lista[j].data.data,dia);
                strcpy(lista[j].data.dataF,diaf);
                puts("Reserva efetuada com sucesso");
            }
            j++;
        }

        setbuf(stdin,NULL); 
        puts("Digite enter para continuar");
        setbuf(stdin,NULL);
        getchar();
    return;
}
void libera(int *qtdC,int *head){
    system("clear");
    setbuf(stdin,NULL);
    int j = *head, i = *qtdC;
    char data[30];
    int aux;
    int ID;
    manutencao(&i,&j);
    //Novamente o uso de ID por sua unicidade
    puts("Digite o ID do carro desejado");
    scanf("%d",&ID);
    while(j < i){
        setbuf(stdin,NULL);
        strcpy(data,lista[j].data.dataF);
        if(lista[j].link != -1 && strcmp(data,"0/0/0") != 0 && lista[j].carro.id_Carro == ID){
            printf("carro: %s, marcado para ser entregue na data: %s\n",lista[j].carro.modelo,lista[j].data.data);
            puts("Confirmar a retirada do carro(0) ou liberar para reserva(1)");
            scanf("%d",&aux);
            setbuf(stdin,NULL);
            if(aux == 1){
                setbuf(stdin,NULL);
                strcpy(lista[j].data.data,"0/0/0");
                strcpy(lista[j].data.dataF,"0/0/0");
                puts("cadastro liberado com sucesso");
                setbuf(stdin,NULL);
            }
            else if(aux == 0){
                puts("Obrigado por usar nossos serviços");
            }
        }
        j++;
    }
return;
}
void atualiza(int *Qtdc,int *head){
    int i = *Qtdc;
    int j = *head;
    manutencao(&i,&j);
    int indice;
    //Considerados aqui apenas as informaçoes pertinentes para um retorno de um carro e manutenção do código
    puts("\nDigite o indice do veículo devolvido");
    scanf("%d",&indice);
    setbuf(stdin,NULL);
    puts("Carro ainda está para alugar?(S/N)\n");
    scanf("%c",&lista[indice].disp);
    while(lista[j].disp != 'S' && lista[j].disp != 'N'){
        setbuf(stdin,NULL);
        puts("Apenas entradas por favor, S/N");
        scanf("%c",&lista[indice].disp);
    }
    setbuf(stdin,NULL);
    puts("Digite a nova Quilometragem");
    scanf("%d",&lista[indice].carro.km);
    while(lista[indice].carro.km < 0){
        puts("Atualize o valor da KM corretamente por favor");
        scanf("%d",&lista[indice].carro.km);
    }
    setbuf(stdin,NULL);
    strcpy(lista[indice].data.data,"0/0/0");
    strcpy(lista[indice].data.dataF,"0/0/0");
    setbuf(stdin,NULL);
    puts("Ar condicinado ainda funciona?S/N");
    scanf("%c",&lista[indice].carro.ar);
    while(lista[indice].carro.ar != 'S' && lista[indice].carro.ar != 'N'){
        setbuf(stdin,NULL);
        puts("Apenas entradas válidas por favor, S/N");
        scanf("%c",&lista[indice].carro.ar);
    }
    setbuf(stdin,NULL);
    puts("Dados atualizados com sucesso");
    return;
}
void attarq(int *Qtdc, int *head){
    int i = *Qtdc, j = *head;
    FILE *fp;
    fp = fopen("listacarros.dat","w+");
    if(fp == NULL){
        puts("Não possivel abrir o arquivo");
    }
    //FOrmato de escrita no arquivo
    // ID_carro Placa Fabricante Modelo
    // Disponibilidade(S/N) Categoria Num_ocupantes Ar_condicionado(S/N)
    // Quilometragemj
    // Início_reserva Final_reserva (no formato nn/nn/nnnn se houver reserva 
    // ou uso e 0/0/0 indicando que não há reserva)
    else{
        while(j < i){
            if(lista[j].link != -1){
               fprintf(fp,"%d %s %s %s\n",lista[j].carro.id_Carro,lista[j].carro.placa,lista[j].carro.fabricante,lista[j].carro.modelo);
               fprintf(fp,"%c %s %d %c\n",lista[j].disp,lista[j].carro.categoria,lista[j].carro.espaco,lista[j].carro.ar);
               fprintf(fp,"%d\n",lista[j].carro.km);
               fprintf(fp,"%s %s\n",lista[j].data.data,lista[j].data.dataF);
            }
            j++;
        }
    }
    fclose(fp);
    getchar();
    puts("Arquivo fechado com sucesso\n");
    return;
}
int main (){
    int qtdC=0,qtdcB;
    int operador,aux = 0;
    int head;
    int a = 0;
    zerar();
    leituraArq(&qtdC,&head,&qtdcB);
    //primeira inicialização para entrada no loop do menu
    operador = leituraMain();
    while(aux == 0){
        switch(operador){
            //Manual utilizando-se switch case
            case 1: inserir(&qtdC,&head,&qtdcB); operador = leituraMain(); break;
            case 2: remover(&qtdC,&head,&qtdcB); operador = leituraMain(); break;
            case 3: mostrar(&qtdC,0,&head); operador = leituraMain(); break;
            case 4: mostrar(&qtdC,1,&head); operador = leituraMain(); break;
            case 5: devolver(&qtdC,&head); operador = leituraMain();break;
            case 6: reserva(&qtdC,&head); operador = leituraMain();break;
            case 7: libera(&qtdC,&head); operador = leituraMain();break;
            case 8: atualiza(&qtdC,&head); operador = leituraMain(); break;
            case 9: attarq(&qtdC,&head); puts("até...");aux = 1; break;
            default: puts("Valor inválido"); operador = leituraMain(); break;
        }
    }
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>




typedef struct{
   int codigo, ano, estadoaluga;
   char modelo[50], placa[10];
   float diaria;
}CARRO;
   
typedef struct{
   int codigo;
   char nome[50], senha[20];
}FUNCIONARIO;

typedef struct {
    char CPF[14];
    char telefone[15];
    char nome[50];
    char endereco[100];
    char data[10];
    int vazio,codigo,empresaparceira,idade, diascort;
} CLIENTE;


int menu(int op); 														// CONTEM O MENU INICIAL DO PROGRAMA;
void opcao(int op, CARRO *carro, FUNCIONARIO  *func, CLIENTE *cliente);	// CONTEM A CHAMADA DAS FUNCOES DE ACORDO COM A OPCAO SELECIONADA;
void alugacarro(CARRO *carro, FUNCIONARIO  *func, CLIENTE *cliente);														// CONTEM O PROCESSO DE LOCACAO DE VEICULO;
void controlefuncionario(FUNCIONARIO  *func);							// GERENCIA OS FUNCIONARIOS CADASTRADOS NO SISTEMA(CADASTRA-EDITA-LISTA-APAGA);
void controlecliente(CLIENTE *cliente);									// GERENCIA OS CLIENTES CADASTRADOS NO SISTEMA(CADASTRA-EDITA-LISTA-APAGA);

void Cadastracliente(CLIENTE *cliente);

void controlecarro(CARRO *carro);										// GERENCIA OS CARROS CADASTRADOS NO SISTEMA(CADASTRA-EDITA-LISTA-APAGA);
void zerafunc(CARRO *carro, FUNCIONARIO *func, CLIENTE *cliente);		// INICIALIZA O VETOR DE STRUCTS DE CADASTRO DE CARROS, FUNCIONARIOS;

int verificavazio(CARRO *carro);										// VERIFICA SE O VETOR DE STRUCTS DE CARRO ESTA VAZIO E RETORNA UM INT;
int verificafuncvazio(FUNCIONARIO *func);								// VERIFICA SE O VETOR DE STRUCTS DE FUNCIONARIO ESTA VAZIO E RETORNA UM INT;
int verificaclientevazio(CLIENTE *cliente);								// VERIFICA SE O VETOR DE STRUCTS DE CLIENTE ESTA VAZIO E RETORNA UM INT;






void zerafunc(CARRO *carro, FUNCIONARIO *func, CLIENTE *cliente){													
	
	int i;
	printf("ZERA..."); 
	
	for(i=0;i<50;i++)			// ZERA TODAS AS POSICOES DOS CARROS
	{
		carro[i].codigo = 0;   
	}
	for(i=0;i<20;i++)			// ZERA TODAS AS POSICOES DOS FUNCIONARIOS
	{
		func[i].codigo = 0;   
	}
	for(i=0;i<500;i++)			// ZERA TODAS AS POSICOES DOS CLIENTES
	{
		cliente[i].codigo = 0;   
	}
	
	printf("Todas as Posicoes zeradas com sucesso!");
	getch();

}


int main() 				
{
    int opt, a=0, i;
    CARRO carro[50];
    FUNCIONARIO func[20];
	CLIENTE cliente[500];


	zerafunc(carro, func, cliente); 			// INICIALIZA O VETOR DE STRUCTS
	
	
    do{  						
		opt=menu(a);     						//MOSTRA O MENU DE OPCOES
        opcao(opt, carro, func, cliente); 		//DIRECIONA A OPCAO AS FUNCOES
    }while(opt);								//ATE QUE O USUARIO DIGITE ZERO
    
    system("PAUSE");
    return 0;
}

int menu(int a)
{
    int opt;
    system("cls");
    printf("Escolha a opcao\n");
    printf("0. Sair\n");
    printf("1. Alugar carro\n");
    printf("2. Controle Funcionarios\n");
    printf("3. Controle Clientes\n");
    printf("4. Controle Carros\n");
    printf("\nOpcao: "); scanf("%d", &opt);
    
    return opt;
}

void opcao(int op, CARRO *carro, FUNCIONARIO *func, CLIENTE *cliente)
{
    
	
	switch(op){
        case 0:
            break;
            
        case 1:
            alugacarro(carro, func, cliente);
            break;
            
        case 2:
            controlefuncionario(func);
            break;
            
        case 3:
            controlecliente(cliente);
            break;
            
        case 4:
            controlecarro(carro);
            break;
            
        default:
            printf("Comando invalido!\n\n");
            getch();
    }
}
void alugacarro(CARRO *carro, FUNCIONARIO  *func, CLIENTE *cliente)
{
   // 4.RECOLHE DADOS DO CLIENTE [OK]; 5. ALUGA;
    // 6. GERA O TICKET[OUTRA FUNCAO]; 7. MOSTRA O FOLHETO[OUTRA FUNCAO];
    // IDOSO = 10% DESCONTO  EMPRESAS PARCEIRAS DA ONG 5% DESCONTO   A CADA 5 DIAS, GANHA 1 DE CORTESIA;
	int i=0, j=0, selectcarro=0, selectcliente=0, cad=0, achou=0, errot=0, cont=0, tecla=0, diagratuito=0, diasuso=0, diasloc=0;
	int erro, dias=0,atual=0, x, codcarro=0, codcliente=0;
	float precof;
	
	struct tm  ts;
	struct tm  ts1;
	char	   datadev[80];
	char	   datual[80];
	
	time_t  now;
	time_t 	devolucao;
	
	
	system("cls");
	fflush(stdin);
    
    do{ 			//VERIFICA EXISTENCIA DO CODIGO DIGITADO, MOSTRANDO NA TELA OS JA CADASTRADOS
						
						
						cont=0;
            			errot = 0;
            			achou = 0;
						for(i=0;i<50;i++){ 	
							if(carro[i].codigo != 0)
                       	 	printf("COD: <%d> - %s / %d / R$%.2f \n\n\n", carro[i].codigo, carro[i].modelo, carro[i].ano, carro[i].diaria);
                		}
					
						printf("Digite o codigo do carro a Alugar: ");
            			scanf("%d", &selectcarro);
            			
            				if(selectcarro==0){
            					printf("\n\nCarro nao encontrado!\n Digite o 1 para digitar cod. novamente ou 0 para sair: ");
								scanf("%d", &tecla);
									
								if(tecla== 0){
									break;
								}else{
									errot=1;                       
									system("cls"); 	
								}
							}else{
								for(i=0;i<50;i++){  // ACHANDO O CODIGO DIGITADO, MANTEM O VALOR DO INDICE PARA FAZER ALTERACOES
            						if(carro[i].codigo == selectcarro){
            							achou = 1;
            							codcarro=i;
            							printf("Carro escolhido com sucesso!  \n\n");
    									getch();
										break;
									}else{
										cont++;		// SENAO, CONTINUA SOMANDO UM CONTADOR DOS DIFERENTES
									}
								}
								
								if(cont==50){	//APOS NAO ENCONTRAR O CODIGO DIGITADO OU SE FOR 0 , MOSTRA MENSAGEM DE ERRO
									printf("\n\nCarro nao encontrado!\n Digite o 1 para digitar cod. novamente ou 0 para sair: ");
									scanf("%d", &tecla);
										
									if(tecla== 0){
										break;
									}else{
										errot=1;                       
										system("cls"); 	
									}		
								}	
							}
            			}while((errot != 0 )&& (achou != 1));
    
    
    if(achou!=0){ //COM A ESCOLHA FEITA, VERIFICAMOS O CADASTRO DE CLIENTE SE JA TEM
		
		system("cls"); 
    	printf("Cliente possui cadastro: 1.Sim 2.Nao < >\b\b");
    	scanf("%d", &cad);
		
		if(cad==2){  //SE N TIVER CADASDTRO CRIA;
    		Cadastracliente(cliente);
    		alugacarro(carro, func, cliente); 		//DEPOIS DE REALIZADO O CADASTRO RETORNA AO PROCESSO DE ESCOLHA
		}
		else{  // SE TIVER CADASTRO CONTINUA;
			system("cls"); 
			printf("Continuando...  \n\n");
			//BUSCAR CLIENTE E SABER O INDICE
			
			do{ 		// VERIFICA O CLIENTE PARA PROCEDER A LOCACAO;
						cont=0;
            			errot = 0;
            			achou = 0;
						for(i=0;i<500;i++){ 	
							if(cliente[i].codigo != 0)
                       	 		printf("COD: <%d> - %s / %s \n\n\n", cliente[i].codigo, cliente[i].nome, cliente[i].telefone);
                		}
					
						printf("Digite o codigo do Cliente a selecionar: ");
            			scanf("%d", &selectcliente);
            			
            				if(selectcliente==0){
            					printf("\n\nCliente nao encontrado!\n Digite o 1 para digitar cod. novamente ou 0 para sair: ");
								scanf("%d", &tecla);
									
								if(tecla== 0){
									break;
								}else{
									errot=1;                       
									system("cls"); 	
								}
							}else{
								for(i=0;i<500;i++){  // ACHANDO O CODIGO DIGITADO, MANTEM O VALOR DO INDICE PARA FAZER ALTERACOES
            						if(cliente[i].codigo == selectcliente){
            							achou = 1;
            							codcliente=i;
										break;
									}else{
										cont++;		// SENAO, CONTINUA SOMANDO UM CONTADOR DOS DIFERENTES
									}
								}
								
								if(cont==500){	//APOS NAO ENCONTRAR O CODIGO DIGITADO OU SE FOR 0 , MOSTRA MENSAGEM DE ERRO
									printf("\n\nCliente nao encontrado!\n Digite o 1 para digitar cod. novamente ou 0 para sair: ");
									scanf("%d", &tecla);
										
									if(tecla== 0){
										break;
									}else{
										errot=1;                       
										system("cls"); 	
									}		
								}	
							}
            }while((errot != 0 )&& (achou != 1));
            
            
			if(achou!=0){
					system("cls"); 	
					for(i=0;i<50;i++){  
		            	if(carro[i].codigo == selectcarro){//ECIBE O CARRO ESCOLHIDO 
		            		printf("COD: <%d> - %s / %d / R$%.2f \n\n\n", carro[i].codigo, carro[i].modelo, carro[i].ano, carro[i].diaria);
						}
					}	
					printf("Deseja alocar por quantos dias? < >\b\b");  //DIAS DE USO
					scanf("%d", &diasloc);
					
					if(diasloc>=5){ //CALCULA OS DIAS GRATIS
						diagratuito = (diasloc/5); 
						cliente[codcliente].diascort = (cliente[codcliente].diascort + diagratuito);  //ARMAZENA SOMANDO AOS DIAS GRATIS ACUMULADOS
					}
					diasuso=0;
					if(cliente[codcliente].diascort>0){  // SE CLIENTE TIVER DIAS GRATUITOS, PERGUNTA SE QUER USAR
						do{
							erro=0;
							printf("O cliente %s possui %d dia(s) gratuito(s).\n", cliente[codcliente].nome, cliente[codcliente].diascort);
							printf("Deseja usar quantos dias gratuitos: ");
							scanf("%d", &diasuso);
							
							if(diasuso>cliente[codcliente].diascort){
								printf("O cliente possui apenas %d dias gratuitos. Digite novamente!\n", cliente[codcliente].diascort);
								erro=1;
							}	
						}while(erro!=0);
					}
					fflush(stdin);
					
					//BORA MOSTRAR O TICKET:
					
					
					dias= diasloc+diasuso; 
					x = (dias*86400); //transforma dias em timestamp;
					
					printf("%d\n", dias); // ok!!!
					printf("%d\n", x);
					
					
					
					time(&now);
					printf("No timestamp:  %d\n", now);
					time(&devolucao);
					printf("No timestamp:  %d\n", devolucao);	
					devolucao=(now + x);
					
					ts = *localtime(&now); //MOSTRA A DATA-HORA ATUAL
					strftime(datual, sizeof(datual), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
					
					system("cls"); 
					printf("\t\t\t LEGAL RENT A CAR - TICKET\n\n"); 
					printf("Data/Hora Local: ");
					printf("%s\n\n", datual);
					
					printf("CLIENTE: %s \t\t\t PlACA: %s", cliente[codcliente].nome, carro[codcarro].placa);
					printf("\n\n\n\n");
					
					precof=(diasloc*carro[codcarro].diaria);
					printf("Preco: %.2f\n", precof);
					
					float desc=0,total;
					if(cliente[codcliente].idade>=60){
						desc=0.10;
					}
					if(cliente[codcliente].empresaparceira==1){
						desc=desc+0.05;
					}
					
					desc=(precof*desc);
					total=(precof-desc);
					
					printf("Desconto: %.2f\n", desc);
					printf("Total: %.2f \n",total);
					printf("\n\n\n\n");
					
					ts1= *gmtime(&devolucao);//MOSTRA A DATA-HORA DE DEVOLUCAO
					strftime(datadev, sizeof(datadev), "%a %Y-%m-%d %H:%M:%S %Z", &ts1);
					printf("Data/Hora Devolucao: ");
					printf("%s\n", datadev);
					printf("\n\n\n\n\t\tOBRIGADO PELA PREFERENCIA! VOLTE SEMPRE!");
					carro[codcarro].estadoaluga=1;					
					
					getch();
					
				
			}
		}
	}
    
    
    
}



void controlefuncionario(FUNCIONARIO *func) // GERENCIA (CRIA, EDITA E EXCLUI) OS FUNCIONARIOS NO SISTEMA
{
    int optf=0, i=0, j=0,errot=0, optt=0, achou=0;
    int cont=0, ver=0;
    int cod=0;
    char a=0, c;
    int x=2;
	char novonome[50], novasenha[20];
	char conf;
    int tecla=-1;
   
    
  
    
    
    
    do{			// REPETE O MENU DE OPCOES ATE QUE A OPCAO ZERO SEJA PRESSIONADA OU ENQUANTO A OPCAO DIGITADA ESTIVER ERRADA
    	optf=0;
        system("cls");
		printf("Escolha uma das opcoes abaixo: \n");
        printf("0. Voltar ao Menu Inicial\n\n\n");
        printf("1. Cadastra Funcionario\n");
        printf("2. Edita Funcionario\n");
        printf("3. Mostrar todos os Funcionarios\n");
        printf("4. Exclui Funcionario\n");
        printf("Opcao: "); 
		scanf("%d", &optf);
        
        
		switch (optf)
		{
                
            case 0:
            		
				break;
            	
            case 1: // CADASTRA FUNCIONARIO
               	
               	
				cont=0;
               	system("cls");	
                for(i=0;i<20;i++){ 		
                    if (func[i].codigo==0) 	// BUSCA POSICAO VAZIA PARA SOBRESCREVER	
                        break;
                    else
                    	cont++;	// CONTA QUANTOS FUNCIONARIOS FORAM CADASTRADOS PARA DEPOIS VERIFICAR SE O LIMITE FOI ATINGIDO
            	}
                
				if(cont==20)
                	printf("LIMITE ATINGIDO! APAGUE ALGUM CADASTRO PARA PROSSEGUIR.\n");
                else{
					printf("UTILIZANDO O CODIGO DE MEMORIA: %d \n", i);
					printf("RECEBENDO COD... \n\n");
                	cont=0;
                
                	for(j=0;j<20;j++){ // CONTA QUANTOS FUNCIONARIOS CADASTRADOS EXISTEM
                		if(func[j].codigo != 0)
                			cont++;	
					}		
                	if(cont==0){		// SE NAO EXISTEM CARROS NO SISTEMA, RECEBERA O CODIGO N-1
						printf("PRIMEIRO CADASTRO, YES! \n\n");
						func[i].codigo = 1;
					}else{				// CASO CONTRARIO RECEBERA O CODIGO EM ORDEM CRESCENTE, SOMANDO SE 1 AO TOTAL DE CARROS CADASTRADOS
						printf("ATE O MOMENTO COM %d FUNCIONARIOS CADASTRADOS. \n\n", cont);
                		func[i].codigo = cont + 1;
					}
				 	
                	printf("Digite o Nome do Funcionario: \n");
                	scanf(" %[^\n]s", func[i].nome);
					setbuf(stdin, NULL);
                	
                	
					printf("Digite uma nova Senha: \n"); // LEITURA DA SENHA IMPRIMINDO ASTERISCOS
                	do{
           					c=getch();
           					if(isprint(c)){       //Analisa se o valor da variável c é imprimivel
          					 	func[i].senha[a]=c;  //Se for, armazena o caractere 
          					 	a++;
           						printf("*");          //imprime o * Anterisco
           					}else if(c==8&&a){     //8 é o caractere / na tabela ASCII, && a analisa se a é diferente de 0
           						func[i].senha[a]='\0';
           						a--;
           						printf("\b \b");       //Apagando o caractere digitado
           					}				 
       				}while(c!=13);             //13 é o valor de ENTER na tabela ASCII
       					func[i].senha[a]='\0';
      				 	system("cls");  
       					printf("\n\nCadastro efetuado com sucesso...\n\n");
                	
                	
                	
					printf("FUNCIONARIO CRIADO COM SUCESSO!\n");
					getch();
				}
            break;
                
                
            case 2:  //FUNCAO EDITA FUNCIONARIO
            
            	ver = verificafuncvazio(func);  //RETORNA SE O VETOR DE FUNCIONARIOS ESTA VAZIO
            	
            	if(ver!=1){// SE NAO HA CARROS CADASTRADOS, NAO TEM OQ EDITAR.
            			system("cls");	
					do{ 			//VERIFICA EXISTENCIA DO CODIGO DIGITADO, MOSTRANDO NA TELA OS JA CADASTRADOS
						
						
						cont=0;
            			errot = 0;
            			achou = 0;
						for(i=0;i<20;i++){ 	
							if(func[i].codigo != 0)
                       	 	printf("COD: <%d> - %s \n\n\n", func[i].codigo, func[i].nome);
                		}
					
						printf("Digite o codigo do Funcionario a editar: ");
            			scanf("%d", &i);
            			
            				if(i==0){
            					printf("\n\nFuncionario nao encontrado!\n Digite o 1 para digitar cod. novamente ou 0 para sair: ");
								scanf("%d", &tecla);
									
								if(tecla== 0){
									break;
								}else{
									errot=1;                       
									system("cls"); 	
								}
							}else{
								for(j=0;j<20;j++){  // ACHANDO O CODIGO DIGITADO, MANTEM O VALOR DO INDICE PARA FAZER ALTERACOES
            						if(func[j].codigo == i){
            							achou = 1;
            							printf("ACHOU NA POSICAO %d", j);
            							getch();
										break;
									}else{
										cont++;		// SENAO, CONTINUA SOMANDO UM CONTADOR DOS DIFERENTES
									}
								}
								
								if(cont==20){	//APOS NAO ENCONTRAR O CODIGO DIGITADO OU SE FOR 0 , MOSTRA MENSAGEM DE ERRO
									printf("\n\nFuncionario nao encontrado!\n Digite o 1 para digitar cod. novamente ou 0 para sair: ");
									scanf("%d", &tecla);
										
									if(tecla== 0){
										break;
									}else{
										errot=1;                       
										system("cls"); 	
									}		
								}	
							}
            			}while((errot != 0 )&& (achou != 1));
            		
            		if(achou== 1){ //SE O USUARIO DECIDIU PROCEDER E EDITAR:
            			do{
            				errot=0;
							system("cls");
							printf("COD: <%d> - %s \n\n\n", func[j].codigo, func[j].nome);
							printf("Escolha uma das opcoes abaixo: \n");
        					printf("<0> Voltar ao Menu Inicial\n");
        					printf("<1> Editar Nome\n");
        					printf("<2> Editar Senha\n");
        					printf("Opcao: "); 
							scanf("%d", &optt);
							
							switch(optt){
									
								case 0:
									controlefuncionario(func);
									break;
								
								case 1:			// ALTERANDO O NOME:
										
										printf("Digite o novo nome: \n");
                						scanf(" %[^\n]s", novonome);
										setbuf(stdin, NULL);
                						
										printf("\nTem certeza? <s/n> ");
            							fflush(stdin);
										scanf("%c", &conf);
    			
										if((conf == 's')||(conf=='S')){
    			        					strcpy(func[j].nome, novonome);
    			        					
    			        					printf("\nDados alterados com sucesso! \n");
    			        					getch();
										}else{
											printf("Operacao abortada! \n");
    			            				getch();
											break;
										}		
									break;
								
								case 2:			// ALTERANDO SENHA
									
    			            			printf("Digite uma nova Senha: \n"); // LEITURA DA SENHA IMPRIMINDO ASTERISCOS
                						do{
           										c=getch();
           										if(isprint(c)){       //Analisa se o valor da variável c é imprimivel
          					 						novasenha[a]=c;  //Se for, armazena o caractere 
          					 						a++;
           											printf("*");          //imprime o * Anterisco
           										}else if(c==8&&a){     //8 é o caractere / na tabela ASCII, && a analisa se a é diferente de 0
           											novasenha[a]='\0';
           											a--;
           											printf("\b \b");       //Apagando o caractere digitado
           										}				 
       									}while(c!=13);             //13 é o valor de ENTER na tabela ASCII
       									novasenha[a]='\0';
      				 					system("cls");  
       									
										
										
										
										
										
										printf("\nTem certeza? <s/n> ");
    			        				fflush(stdin);
										scanf("%c", &conf);
    			
										if(conf == 's'){
    			        					strcpy(func[j].senha, novasenha);
    			        					printf("\nDados alterados com sucesso! \n");
    			        					getch();
										}else{
											printf("\n\t\t\tOperacao abortada! \n");
    		            					getch();
											break;
										}
									break;
									
								default:
										printf("Opcao invalida! Tente novamente.");
										getch();
										errot++;
								break;
							}
						}while((optt!=0 ) && (errot !=0) );	// REPETE ENQUANTO O USUARIO NAO PEDIR PRA SAIR OU DIGITA OPCAO ERRADA
					}
				}else{
					printf("\nNenhum Funcionario cadastrado!\n");
					getch();
				}
					
			 break;
                
                
            case 3:
            	ver = verificafuncvazio(func);// SE NAO HA CARROS CADASTRADOS, NAO TEM OQ LISTAR
            	
            	if(ver!=1){
				
					system("cls");	
					for(i=0;i<20;i++){ 		//MOSTRANDO NA TELA TODOS OS CARROS GRAVADOS;
                   	 		if(func[i].codigo != 0)
                   	    		 printf("COD: <%d> - %s \n\n\n", func[i].codigo, func[i].nome);
                	}
                	printf("\nAperte qualquer tecla para continuar.\n");
					getch();
            	}else{
					printf("\nNenhum Funcionario cadastrado!\n");
					getch();
				}
						
            break;
            
            
            case 4:		// DELETAR CADASTRO
            		
            	ver = verificafuncvazio(func); // SE NAO HA FUNCIONARIOS CADASTRADOS, NAO TEM OQ DELETAR
            	
            	if(ver!=1){
            		system("cls");	
					do{ 			//VERIFICA EXISTENCIA DO CODIGO DIGITADO, MOSTRANDO NA TELA OS JA CADASTRADOS
						
						
						cont=0;
            			errot = 0;
            			achou = 0;
						for(i=0;i<20;i++){ 	
							if(func[i].codigo != 0)
                       	 	printf("COD: <%d> - %s / \n\n\n", func[i].codigo, func[i].nome);
                		}
					
						printf("Digite o codigo do Funcionario a deletar: ");
            			scanf("%d", &i);
            			
            				if(i==0){
            					printf("\n\nCarro nao encontrado!\n Digite o 1 para digitar cod. novamente ou 0 para sair: ");
								scanf("%d", &tecla);
									
								if(tecla== 0){
									break;
								}else{
									errot=1;                       
									system("cls"); 	
								}
							}else{
								for(j=0;j<20;j++){  // ACHANDO O CODIGO DIGITADO, MANTEM O VALOR DO INDICE PARA FAZER ALTERACOES
            						if(func[j].codigo == i){
            							achou = 1;
            							printf("ACHOU NA POSICAO %d", j);
            							getch();
										break;
									}else{
										cont++;		// SENAO, CONTINUA SOMANDO UM CONTADOR DOS DIFERENTES
									}
								}
								
								if(cont==20){	//APOS NAO ENCONTRAR O CODIGO DIGITADO OU SE FOR 0 , MOSTRA MENSAGEM DE ERRO
									printf("\n\nCarro nao encontrado!\n Digite o 1 para digitar cod. novamente ou 0 para sair: ");
									scanf("%d", &tecla);
										
									if(tecla== 0){
										break;
									}else{
										errot=1;                       
										system("cls"); 	
									}		
								}	
							}
            			}while((errot != 0 )&& (achou != 1));
            	
            		if(achou==1){ // SO CONTINUA A OPERACAO SE O USUARIO NAO APERTOU PARA SAIR ANTERIORMENTE
            			printf("\nTem certeza? <s/n> ");
            			fflush(stdin);
						scanf("%c", &conf);
            			
            			
						if((conf == 's')||(conf == 'S')){
            				func[j].codigo = 0;
            				printf("\nDados deletados com sucesso! \n");
            				getch();
						}else{
							printf("Operacao abortada! \n");
                			getch();
							break;
						}
					}
				}else{
					printf("\nNenhum Funcionario cadastrado!\n");	
					getch();	
				}
				
            break;
            
            default:
            	printf("Comando invalido!\n\n");
            	getch();
            
                
     	}	
    }while (optf!=0);	
    
}

void controlecliente(CLIENTE *cliente) // GERENCIA (CRIA, EDITA E EXCLUI) OS CLIENTES NO SISTEMA
{
    int opt=0, i=0, j=0,errot=0, optt=0, achou=0;
    int cont=0, ver=0;
    int cod=0;
    char a=0, c;
    int x=2;
	char conf;
    int tecla=-1;
   	
   	//PARA FAZER AS COMPARACOES DO MODO EDITAR CADASTRO DE CLIENTE
   	char novonome[50], novoCPF[14], novoEndereco[100], novoData[10], novoTEL[15];
   
    
  
    
    
    
    do{			// REPETE O MENU DE OPCOES ATE QUE A OPCAO ZERO SEJA PRESSIONADA OU ENQUANTO A OPCAO DIGITADA ESTIVER ERRADA
    	opt=0;
        system("cls");
        printf("Escolha uma das opcoes abaixo: \n");
        printf("0. Voltar ao Menu Inicial\n\n\n");
        printf("1. Cadastra Cliente\n");
        printf("2. Editar Cliente\n");
        printf("3. Mostrar todos os Clientes\n");
        printf("4. Exclui Cliente\n");
        printf("Opcao: ");
        scanf("%d", &opt);


        switch (opt)
        {

        case 0:
            break;

        case 1: // CADASTRA CLIENTE
				Cadastracliente(cliente);
            break;
                
                
            case 2:  //FUNCAO EDITA CLIENTE
            
            	ver = verificaclientevazio(cliente);  //RETORNA SE O VETOR DE FUNCIONARIOS ESTA VAZIO
            	
            	if(ver!=1){// SE NAO HA CARROS CADASTRADOS, NAO TEM OQ EDITAR.
            			system("cls");	
					do{ 			//VERIFICA EXISTENCIA DO CODIGO DIGITADO, MOSTRANDO NA TELA OS JA CADASTRADOS
						
						
						cont=0;
            			errot = 0;
            			achou = 0;
						for(i=0;i<500;i++){ 	
							if(cliente[i].codigo != 0)
                       	 		printf("COD: <%d> - %s / %s \n\n\n", cliente[i].codigo, cliente[i].nome, cliente[i].telefone);
                		}
					
						printf("Digite o codigo do Cliente a editar: ");
            			scanf("%d", &i);
            			
            				if(i==0){
            					printf("\n\nCliente nao encontrado!\n Digite o 1 para digitar cod. novamente ou 0 para sair: ");
								scanf("%d", &tecla);
									
								if(tecla== 0){
									break;
								}else{
									errot=1;                       
									system("cls"); 	
								}
							}else{
								for(j=0;j<500;j++){  // ACHANDO O CODIGO DIGITADO, MANTEM O VALOR DO INDICE PARA FAZER ALTERACOES
            						if(cliente[j].codigo == i){
            							achou = 1;
            							printf("ACHOU NA POSICAO %d", j);
            							getch();
										break;
									}else{
										cont++;		// SENAO, CONTINUA SOMANDO UM CONTADOR DOS DIFERENTES
									}
								}
								
								if(cont==500){	//APOS NAO ENCONTRAR O CODIGO DIGITADO OU SE FOR 0 , MOSTRA MENSAGEM DE ERRO
									printf("\n\nCarro nao encontrado!\n Digite o 1 para digitar cod. novamente ou 0 para sair: ");
									scanf("%d", &tecla);
										
									if(tecla== 0){
										break;
									}else{
										errot=1;                       
										system("cls"); 	
									}		
								}	
							}
            			}while((errot != 0 )&& (achou != 1));
            		
            		if(achou== 1){ //SE O USUARIO DECIDIU PROCEDER E EDITAR:
            			do{
            				errot=0;
							system("cls");
							printf("COD: <%d> - %s \n\n\n", cliente[j].codigo, cliente[j].nome);
							printf("Escolha uma das opcoes abaixo: \n");
        					printf("0. Voltar ao Menu Inicial\n");
        					printf("1. Editar Nome\n");
        					printf("2. Editar CPF\n");
        					printf("3. Editar Tel.\n");
        					printf("4. Editar Endereco\n");
        					printf("5. Editar Data Nasc.\n");
							printf("Opcao: "); 
							scanf("%d", &optt);
							
							switch(optt){
									
								case 0:
									controlecliente(cliente);
									break;
								
								case 1:			// ALTERANDO O NOME:
										
										printf("Digite o novo nome: \n");
                						scanf("%s", novonome);
										printf("\nTem certeza? <s/n> ");
            							fflush(stdin);
										scanf("%c", &conf);
    			
										if((conf == 's')||(conf=='S')){
    			        					strcpy(cliente[j].nome, novonome);
    			        					
    			        					printf("\nDados alterados com sucesso! \n");
    			        					getch();
										}else{
											printf("Operacao abortada! \n");
    			            				getch();
											break;
										}		
									break;
								
								case 2:			// ALTERANDO CPF
										printf("Digite o novo CPF: \n");
                						scanf("%s", novonome);
										printf("\nTem certeza? <s/n> ");
            							fflush(stdin);
										scanf("%c", &conf);
    			
										if((conf == 's')||(conf=='S')){
    			        					strcpy(cliente[j].CPF, novoCPF);
    			        					
    			        					printf("\nDados alterados com sucesso! \n");
    			        					getch();
										}else{
											printf("Operacao abortada! \n");
    			            				getch();
											break;
										}		
									break;
								
								case 3:			// ALTERANDO TELEFONE
										printf("Digite o novo TEL: \n");
                						scanf("%s", novoTEL);
										printf("\nTem certeza? <s/n> ");
            							fflush(stdin);
										scanf("%c", &conf);
    			
										if((conf == 's')||(conf=='S')){
    			        					strcpy(cliente[j].telefone, novoTEL);
    			        					
    			        					printf("\nDados alterados com sucesso! \n");
    			        					getch();
										}else{
											printf("Operacao abortada! \n");
    			            				getch();
											break;
										}		
									break;
								
								case 4:			// ALTERANDO ENDERECO
										printf("Digite o novo Endereco: \n");
                						scanf("%s", novoEndereco);
										printf("\nTem certeza? <s/n> ");
            							fflush(stdin);
										scanf("%c", &conf);
    			
										if((conf == 's')||(conf=='S')){
    			        					strcpy(cliente[j].endereco, novoEndereco);
    			        					
    			        					printf("\nDados alterados com sucesso! \n");
    			        					getch();
										}else{
											printf("Operacao abortada! \n");
    			            				getch();
											break;
										}		
									break;	
								
								case 5:			// ALTERANDO DATA DE NASC
										printf("Digite o novo Data Nascimento: \n");
                						scanf("%s", novoData);
										printf("\nTem certeza? <s/n> ");
            							fflush(stdin);
										scanf("%c", &conf);
    			
										if((conf == 's')||(conf=='S')){
    			        					strcpy(cliente[j].data, novoData);
    			        					
    			        					printf("\nDados alterados com sucesso! \n");
    			        					getch();
										}else{
											printf("Operacao abortada! \n");
    			            				getch();
											break;
										}		
									break;
									
								default:
										printf("Opcao invalida! Tente novamente.");
										getch();
										errot++;
								break;
							}
						}while((optt!=0 ) && (errot !=0) );	// REPETE ENQUANTO O USUARIO NAO PEDIR PRA SAIR OU DIGITA OPCAO ERRADA
					}
				}else{
					printf("\nNenhum Cliente cadastrado!\n");
					getch();
				}
					
			 break;
                
                
            case 3:
            	ver = verificaclientevazio(cliente);// SE NAO HA CARROS CADASTRADOS, NAO TEM OQ LISTAR
            	
            	if(ver!=1){
				
					system("cls");	
					for(i=0;i<500;i++){ 		//MOSTRANDO NA TELA TODOS OS CARROS GRAVADOS;
                   	 		if(cliente[i].codigo != 0)
                   	    		 printf("COD: <%d> - %s / %s \n\n\n", cliente[i].codigo, cliente[i].nome, cliente[i].telefone);
                	}
                	printf("\nAperte qualquer tecla para continuar.\n");
					getch();
            	}else{
					printf("\nNenhum Cliente cadastrado!\n");
					getch();
				}
						
            break;
            
            
            case 4:		// DELETAR CADASTRO
            		
            	ver = verificaclientevazio(cliente); // SE NAO HA CLIENTE CADASTRADOS, NAO TEM OQ DELETAR
            	
            	if(ver!=1){
            		system("cls");	
					do{ 			//VERIFICA EXISTENCIA DO CODIGO DIGITADO, MOSTRANDO NA TELA OS JA CADASTRADOS
						
						
						cont=0;
            			errot = 0;
            			achou = 0;
						for(i=0;i<500;i++){ 	
							if(cliente[i].codigo != 0)
                       	 	printf("COD: <%d> - %s \n\n\n", cliente[i].codigo, cliente[i].nome);
                		}
					
						printf("Digite o codigo do Cliente a deletar: ");
            			scanf("%d", &i);
            			
            				if(i==0){
            					printf("\n\nCliente nao encontrado!\n Digite o 1 para digitar cod. novamente ou 0 para sair: ");
								scanf("%d", &tecla);
									
								if(tecla== 0){
									break;
								}else{
									errot=1;                       
									system("cls"); 	
								}
							}else{
								for(j=0;j<500;j++){  // ACHANDO O CODIGO DIGITADO, MANTEM O VALOR DO INDICE PARA FAZER ALTERACOES
            						if(cliente[j].codigo == i){
            							achou = 1;
            							printf("ACHOU NA POSICAO %d", j);
            							getch();
										break;
									}else{
										cont++;		// SENAO, CONTINUA SOMANDO UM CONTADOR DOS DIFERENTES
									}
								}
								
								if(cont==500){	//APOS NAO ENCONTRAR O CODIGO DIGITADO OU SE FOR 0 , MOSTRA MENSAGEM DE ERRO
									printf("\n\nCarro nao encontrado!\n Digite o 1 para digitar cod. novamente ou 0 para sair: ");
									scanf("%d", &tecla);
										
									if(tecla== 0){
										break;
									}else{
										errot=1;                       
										system("cls"); 	
									}		
								}	
							}
            			}while((errot != 0 )&& (achou != 1));
            	
            		if(achou==1){ // SO CONTINUA A OPERACAO SE O USUARIO NAO APERTOU PARA SAIR ANTERIORMENTE
            			printf("\nTem certeza? <s/n> ");
            			fflush(stdin);
						scanf("%c", &conf);
            			
            			
						if((conf == 's')||(conf == 'S')){
            				cliente[j].codigo = 0;
            				printf("\nDados deletados com sucesso! \n");
            				getch();
						}else{
							printf("Operacao abortada! \n");
                			getch();
							break;
						}
					}
				}else{
					printf("\nNenhum Cliente cadastrado!\n");	
					getch();	
				}
				
            break;
            
            default:
            	printf("Comando invalido!\n\n");
            	getch();
            
                
     	}	
    }while (opt!=0);	
}



void controlecarro(CARRO *carro) // GERENCIA (CRIA, EDITA E EXCLUI) OS CARROS NO SISTEMA RECEBENDO O ENDERECO DA STRUCT LA DO MAIN
{
    int optc=0, i=0, j=0,erro=0, optt=0, achou=0;
    int cont=0, ver=0, sair=0, errot;
    int cod=0;
    int x=3;
    
	char novomodelo[50];
	char conf ,novaplaca[10];
    int novoano, tecla=-1;
    float novadiaria;
    
  
    
    
    
    do{			// REPETE O MENU DE OPCOES ATE QUE A OPCAO ZERO SEJA PRESSIONADA OU ENQUANTO A OPCAO DIGITADA ESTIVER ERRADA
    	optc=0;
        system("cls");
		printf("Escolha uma das opcoes abaixo: \n");
        printf("0. Voltar ao Menu Inicial\n\n\n");
        printf("1. Cadastra Carro\n");
        printf("2. Edita Carro\n");
        printf("3. Mostrar todos os Carros\n");
        printf("4. Exclui Carro\n");
        printf("Opcao: "); 
		scanf("%d", &optc);
        
        
		switch (optc)
		{
                
            case 0:
            	
				break;
            	
            case 1: // CADASTRA CARRO
               	
               	
				cont=0;
               	system("cls");	
                for(i=0;i<50;i++){ 		
                    if (carro[i].codigo==0) 	// BUSCA POSICAO VAZIA PARA SOBRESCREVER	
                        break;
                    else
                    	cont++;	// CONTA QUANTOS CARROS FORAM CADASTRADOS PARA DEPOIS VERIFICAR SE O LIMITE FOI ATINGIDO
            	}
                
				if(cont==50)
                	printf("LIMITE ATINGIDO! APAGUE ALGUM CADASTRO PARA PROSSEGUIR.\n");
                else{
					printf("UTILIZANDO O CODIGO DE MEMORIA: %d \n", i);
					printf("RECEBENDO COD... \n\n");
                	cont=0;
                
                	for(j=0;j<50;j++){ // CONTA QUANTOS CARROS CADASTRADOS EXISTEM
                		if(carro[j].codigo != 0)
                			cont++;	
					}		
                	if(cont==0){		// SE NAO EXISTEM CARROS NO SISTEMA, RECEBERA O CODIGO N-1
						printf("PRIMEIRO CADASTRO, YES! \n\n");
						carro[i].codigo = 1;
					}else{				// CASO CONTRARIO RECEBERA O CODIGO EM ORDEM CRESCENTE, SOMANDO SE 1 AO TOTAL DE CARROS CADASTRADOS
						printf("ATE O MOMENTO COM %d CARRO CADASTRADO. \n\n", cont);
                		carro[i].codigo = cont + 1;
					}
				 	
                	printf("Digite o Modelo do Carro: \n");
                	scanf("%s", carro[i].modelo);
                	printf("Digite o Ano do Carro: \n");
                	scanf("%d", &carro[i].ano);
                	printf("Digite a Placa do Carro: \n");
                	scanf("%s", carro[i].placa);
                	printf("Digite o Preco da Diaria: \n");
                	scanf("%f", &carro[i].diaria);
                	carro[i].estadoaluga=0; 				// DEFINE O CARRO LIVRE PAR SER ALUGADO;
					printf("CARRO CRIADO COM SUCESSO!\n");
					getch();
				}
            break;
                
                
            case 2:  //FUNCAO EDITA CARRO
            
            	ver = verificacarrovazio(carro); // SE NAO HA CARROS CADASTRADOS, NAO TEM OQ EDITAR.
            	
            	if(ver!=1){
            		system("cls");	
					do{ 			//VERIFICA EXISTENCIA DO CODIGO DIGITADO, MOSTRANDO NA TELA OS JA CADASTRADOS
						
						
						cont=0;
            			erro = 0;
            			achou = 0;
						for(i=0;i<50;i++){ 	
							if(carro[i].codigo != 0)
                       	 	printf("COD: <%d> - %s / %d / R$%.2f \n\n\n", carro[i].codigo, carro[i].modelo, carro[i].ano, carro[i].diaria);
                		}
					
						printf("Digite o codigo do carro a editar: ");
            			scanf("%d", &i);
            			
            				if(i==0){
            					printf("\n\nCarro nao encontrado!\n Digite o 1 para digitar cod. novamente ou 0 para sair: ");
								scanf("%d", &tecla);
									
								if(tecla== 0){
									break;
								}else{
									errot=1;                       
									system("cls"); 	
								}
							}else{
								for(j=0;j<50;j++){  // ACHANDO O CODIGO DIGITADO, MANTEM O VALOR DO INDICE PARA FAZER ALTERACOES
            						if(carro[j].codigo == i){
            							achou = 1;
            							printf("ACHOU NA POSICAO %d", j);
            							getch();
										break;
									}else{
										cont++;		// SENAO, CONTINUA SOMANDO UM CONTADOR DOS DIFERENTES
									}
								}
								
								if(cont==50){	//APOS NAO ENCONTRAR O CODIGO DIGITADO OU SE FOR 0 , MOSTRA MENSAGEM DE ERRO
									printf("\n\nCarro nao encontrado!\n Digite o 1 para digitar cod. novamente ou 0 para sair: ");
									scanf("%d", &tecla);
										
									if(tecla== 0){
										break;
									}else{
										errot=1;                       
										system("cls"); 	
									}		
								}	
							}
            			}while((errot != 0 )&& (achou != 1));
            		
            		if(achou==1){
            			
					
            			do{
            				erro=0;
							system("cls");
							printf("COD: <%d> - %s / %d / R$%.2f \n\n\n", carro[j].codigo, carro[j].modelo, carro[j].ano, carro[j].diaria);
							printf("Escolha uma das opcoes abaixo: \n");
        					printf("<0> Voltar ao Menu Inicial\n");
        					printf("<1> Editar Modelo\n");
        					printf("<2> Editar Ano\n");
        					printf("<3> Editar Placa\n");
							printf("<4> Editar Diaria\n");
        					printf("Opcao: "); 
							scanf("%d", &optt);
							
							switch(optt){
									
								case 0:
									controlecarro(carro);
									break;
								
								case 1:			// ALTERANDO O MODELO DO CARRO:
										
										printf("Digite o novo modelo do Carro: \n");
                						scanf("%s", novomodelo);
										printf("\nTem certeza? <s/n> ");
            							fflush(stdin);
										scanf("%c", &conf);
    			
										if((conf == 's')||(conf == 'S')){
    			        					strcpy(carro[j].modelo, novomodelo);
    			        					
    			        					printf("\nDados alterados com sucesso! \n");
    			        					getch();
										}else{
											printf("Operacao abortada! \n");
    			            				getch();
											break;
										}		
									break;
								
								case 2:			// ALTERANDO O ANO DO CARRO:
										
										printf("Digite o novo ano do Carro: \n");
    			            			scanf("%d", &novoano);
										printf("\nTem certeza? <s/n> ");
    			        				fflush(stdin);
										scanf("%c", &conf);
    			
										if((conf == 's')||(conf == 'S')){
    			        					carro[j].ano = novoano;
    			        					printf("\nDados alterados com sucesso! \n");
    			        					getch();
										}else{
											printf("\n\t\t\tOperacao abortada! \n");
    		            					getch();
											break;
										}
									break;
									
								case 3:			// ALTERANDO A PLACA DO CARRO:
										
										printf("Digite a nova Placa do Carro: \n");
    		            				scanf("%s", novaplaca);
										printf("\nTem certeza? <s/n> ");
    		        					fflush(stdin);
										scanf("%c", &conf);
    			
										if((conf == 's')||(conf == 'S')){
    			        					strcpy(carro[j].placa, novaplaca);
    			        					printf("\nDados alterados com sucesso! \n");
    			        					getch();
										}else{
											printf("\n\t\t\tOperacao abortada! \n");
        		        					getch();
											break;
										}		
								break;
								
								case 4:			// ALTERANDO A DIARIA DO CARRO:
										
										printf("Digite a nova Diaria do Carro: \n");
    		            				scanf("%f", &novadiaria);
										printf("\nTem certeza? <s/n> ");
    		        					fflush(stdin);
										scanf("%c", &conf);
    			
										if((conf == 's')||(conf == 'S')){
    			        					carro[j].diaria = novadiaria;
    			        					printf("\nDados alterados com sucesso! \n");
    			        					getch();
										}else{
											printf("\n\t\t\tOperacao abortada! \n");
        		        					getch();
											break;
										}		
								break;
							
								default:
										printf("Opcao invalida! Tente novamente.");
										getch();
										erro++;
								break;
							}
						}while((optt!=0 ) && (erro !=0) );	// REPETE ENQUANTO O USUARIO NAO PEDIR PRA SAIR OU DIGITA OPCAO ERRADA
					}
				}else{
					printf("\nNenhum carro cadastrado!\n");
					getch();
				}
					
			 break;
                
                
            case 3:
            	ver = verificacarrovazio(carro); // SE NAO HA CARROS CADASTRADOS, NAO TEM OQ LISTAR
            	
            	if(ver!=1){
				
					system("cls");	
					for(i=0;i<50;i++){ 		//MOSTRANDO NA TELA TODOS OS CARROS GRAVADOS;
                   	 		if(carro[i].codigo != 0)
                   	    		 printf("COD: <%d> - %s / %d / R$%.2f \n\n\n", carro[i].codigo, carro[i].modelo, carro[i].ano, carro[i].diaria);
                	}
                	printf("\nAperte qualquer tecla para continuar.\n");
					getch();
            	}else{
					printf("\nNenhum carro cadastrado!\n");
					getch();
				}
						
            break;
            
            
            case 4:		// DELETAR CADASTRO
            		
            	ver = verificacarrovazio(carro); // SE NAO HA CARROS CADASTRADOS, NAO TEM OQ DELETAR
            	
            	if(ver!=1){
            		system("cls");	
					do{ 			//VERIFICA EXISTENCIA DO CODIGO DIGITADO, MOSTRANDO NA TELA OS JA CADASTRADOS
						
						
						cont=0;
            			errot = 0;
            			achou = 0;
						for(i=0;i<50;i++){ 	
							if(carro[i].codigo != 0)
                       	 	printf("COD: <%d> - %s / %d / R$%.2f \n\n\n", carro[i].codigo, carro[i].modelo, carro[i].ano, carro[i].diaria);
                		}
					
						printf("Digite o codigo do carro a Deletar: ");
            			scanf("%d", &i);
            			
            				if(i==0){
            					printf("\n\nCarro nao encontrado!\n Digite o 1 para digitar cod. novamente ou 0 para sair: ");
								scanf("%d", &tecla);
									
								if(tecla== 0){
									break;
								}else{
									errot=1;                       
									system("cls"); 	
								}
							}else{
								for(j=0;j<50;j++){  // ACHANDO O CODIGO DIGITADO, MANTEM O VALOR DO INDICE PARA FAZER ALTERACOES
            						if(carro[j].codigo == i){
            							achou = 1;
            							printf("ACHOU NA POSICAO %d", j);
            							getch();
										break;
									}else{
										cont++;		// SENAO, CONTINUA SOMANDO UM CONTADOR DOS DIFERENTES
									}
								}
								
								if(cont==50){	//APOS NAO ENCONTRAR O CODIGO DIGITADO OU SE FOR 0 , MOSTRA MENSAGEM DE ERRO
									printf("\n\nCarro nao encontrado!\n Digite o 1 para digitar cod. novamente ou 0 para sair: ");
									scanf("%d", &tecla);
										
									if(tecla== 0){
										break;
									}else{
										errot=1;                       
										system("cls"); 	
									}		
								}	
							}
            			}while((errot != 0 )&& (achou != 1));
            	
            		if(achou==1){ // SO CONTINUA A OPERACAO SE O USUARIO NAO APERTOU PARA SAIR ANTERIORMENTE
            			printf("\nTem certeza? <s/n> ");
            			fflush(stdin);
						scanf("%c", &conf);
            			
            			
						if((conf == 's')||(conf == 'S')){
            				carro[j].codigo = 0;
            				printf("\nDados deletados com sucesso! \n");
            				getch();
						}else{
							printf("Operacao abortada! \n");
                			getch();
							break;
						}
					}
				}else{
					printf("\nNenhum carro cadastrado!\n");	
					getch();	
				}
				
            break;
            
            default:{
            		printf("Comando invalido!\n\n");
            		getch();
				}
            	
            
                
     	}	
    }while (optc!=0);	
    
}

void Cadastracliente(CLIENTE *cliente){
	
	int i, j, 

            cont=0;
            system("cls");
            
            
            for(i=0; i<500; i++) {
                if (cliente[i].codigo==0) 	// BUSCA POSICAO VAZIA PARA SOBRESCREVER
                    break;
                else
                    cont++;	// CONTA QUANTOS CLIENTES FORAM CADASTRADOS PARA DEPOIS VERIFICAR SE O LIMITE FOI ATINGIDO
            }

            if(cont==500)
                printf("LIMITE ATINGIDO! APAGUE ALGUM CADASTRO PARA PROSSEGUIR.\n");
            else{
                //printf("UTILIZANDO O CODIGO DE MEMORIA: %d \n", i);
                //printf("RECEBENDO COD... \n\n");
                cont=0;

                for(j=0; j<500; j++) { // CONTA QUANTOS CLIENTES CADASTRADOS EXISTEM
                    if(cliente[j].codigo != 0)
                        cont++;
                }
                if(cont==0) {		// SE NAO EXISTEM CLIENTES NO SISTEMA, RECEBERA O CODIGO N-1
                    //printf("PRIMEIRO CADASTRO, YES! \n\n");
                    cliente[i].codigo = 1;
                } else {				// CASO CONTRARIO RECEBERA O CODIGO EM ORDEM CRESCENTE, SOMANDO SE 1 AO TOTAL DE CLIENTES CADASTRADOS
                    //printf("ATE O MOMENTO COM %d CLIENTES CADASTRADOS. \n\n", cont);
                    cliente[i].codigo = cont + 1;
                }
				
				 printf("\t\t\tNOVO CADASTRO DE CLIENTE\n\n\n");
				printf("Empresa Parceira: 1.Sim 2.Nao \n");
                scanf("%d", &cliente[i].empresaparceira);
				
                printf("Digite o Nome do Cliente: \n");
            	scanf(" %[^\n]s", cliente[i].nome);
				setbuf(stdin, NULL);
            
            
                printf("Digite Idade do Cliente: \n");
                scanf("%d", &cliente[i].idade);
				
				
				printf("Digite o CPF/CNPJ ex:595.223.138-90: \n");
				scanf(" %s", cliente[i].CPF);  
                
                
                printf("Digite o Telefone: \n");
				scanf(" %s", cliente[i].telefone);
				
				printf("Digite o Endereco: \n");
				scanf(" %[^\n]s", cliente[i].endereco);
				setbuf(stdin, NULL);
				
				printf("Digite a Data de Nascimento: \n"); //DATA DE NASCIMENTO
				scanf(" %s", cliente[i].data);
			
				printf("CLIENTE CRIADO COM SUCESSO!\n");
                getch();
            }	
}





int verificacarrovazio(CARRO *carro){   // VERIFICACAO SE AINDA NENHUM CADASTRO DE CARRO FOI FEITO. 
	int i, cont = 0;				// SERA UTIL QUANDO FOR EDITAR, LISTAR A APAGAR CARROS, FUNCIONARIOS E CLIENTES
									// POIS SE NAO HOUVEREM CADASTROS, AS 3 OPCOES JA ENCERRAM MOSTRANDO QUE NAO HA NADA NO SISTEMA
		for(i=0;i<50;i++){ 		
            if (carro[i].codigo==0) 	// SOMA AS POSICOES VAZIAS	
                cont++;
		}
		if(cont==50){ // SE TODAS AS POSICOES ENCONTRAM-SE VAZIAS, AVISA COM 1 ;
			return 1;
		}else{
			return 0; // SENAO AVISA COM 0;
		}
}


int verificafuncvazio(FUNCIONARIO *func){ 
	int i, cont=0;
	
			for(i=0;i<20;i++){ 		
        	if (func[i].codigo==0) 	// SOMA AS POSICOES VAZIAS	
                cont++;
			}
			if(cont==20){ // SE TODAS AS POSICOES ENCONTRAM-SE VAZIAS, AVISA COM 1 ;
				return 1;
			}else{
				return 0; // SENAO AVISA COM 0;
			}
}

int verificaclientevazio(CLIENTE *cliente) {
    int i, cont=0;

    for(i=0; i<500; i++) {
        if (cliente[i].codigo==0) 	// SOMA AS POSICOES VAZIAS
            cont++;
    }
    if(cont==500) { // SE TODAS AS POSICOES ENCONTRAM-SE VAZIAS, AVISA COM 1 ;
        return 1;
    } else {
        return 0; // SENAO AVISA COM 0;
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

//LISTA LIGADA DE COMPONENTES
typedef struct reg{
	int cod;
	char nome[100];
	float preco;
	struct reg *next;
}*COMP;

//MENU
void menu() {
	printf("*****************[SISTEMA REPRESENTAÇÃO COMPONENTES ELETRÓNICOS] *******************\n");
	printf("*                                                                                  *\n");
	printf("* \t\t1. Inserir um novo componente                                      *\n");
	printf("* \t\t2. Listar componentes                                              *\n");
	printf("* \t\t3. Pesquisar componente por número                                 *\n");
	printf("* \t\t4. Pesquisar componente por nome                                   *\n");
	printf("* \t\t5. Alterar componente                                              *\n");
	printf("* \t\t6. Remover componente                                              *\n");
	printf("* \t\t7. Definir equipamento eletrónico                                  *\n");
	printf("* \t\t8. Consultar equipamento eletrónico e seu custo total              *\n");
	printf("* \t\t9. Guardar componentes em ficheiro                                 *\n");
	printf("* \t\t0. Sair                                                            *\n");
	printf("*                                                                           	   *\n");
	printf("*                            $ Informática Médica $                                *\n");
	printf("**************************** $ IPCA-EST 2017-2018 $ ********************************\n");
}

int cod_returner(COMP start){
	int cod=0;
	COMP ptr=start;
	if(start==NULL) return 1;
	else{
		while(start!=NULL){	
			cod=start->cod;
			start=start->next;
			
			}
		return cod+1;
	}
}


//INSERIR COMPONENTE ELETRONICO NA LISTA LIGADA
COMP InsComp(COMP start, int cod, char nome[], float preco){
	COMP aux=NULL;
	if(start!=NULL) start->next=InsComp(start->next,cod, nome, preco);	
	else{
		start = (COMP) malloc (sizeof(struct reg));
		start->cod=cod;
		strcpy(start->nome, nome);
		start->preco=preco;
		start->next=NULL;
		return(start);
	}
}

//LISTAR COMPONENTES DA LIStA 
void listar(COMP start){
	int cont=0;
	while(start!=NULL){
		printf("\tCódigo:%i\n\tNome:%s\n\tPreço:%.2f\n\n",start->cod, start->nome, start->preco);
		start=start->next;
		cont++;
	}
	printf("\nComponentes registados: %i\n", cont);
}

void listar1(COMP start){
	printf("\tCódigo->Nome");
	while(start!=NULL){
		printf("\n\t     %i->%s",start->cod, start->nome);
		start=start->next;
	}
}

//PROCURAR POR NOME NA LISTA
int pesquisa_nome(COMP start, char nome[]){
	int k=0, cont=0, find=0;
	while(start!=NULL){
		cont=0;
		for(k=0;k<strlen(nome);k++){
			if(start->nome[k]==nome[k])cont++;
		}
		
		if(cont==strlen(nome)){
			printf("\n\tCódigo:%i\n\tNome:%s\n\tPreço:%.2f\n\n",start->cod, start->nome, start->preco);
			find=1;
		}
		start=start->next;
	}
	return find;
}

// PESQUISAR POR CODIGO 
int pesquisa_cod(COMP start, int cod){
	int find=0;
	while(start!=NULL){
		if(start->cod==cod){
		printf("\n\tCódigo:%i\n\tNome:%s\n\tPreço:%.2f\n\n",start->cod, start->nome, start->preco);
		find=1;
		} 
		start=start->next;
	}
	return find;
}

// ALTERAR COMPONENTE
COMP alt_comp(COMP start, int cod){
	int find=0, opcao=0;
	COMP ptr=start;
	while(start!=NULL){
		if(start->cod==cod){
			find=1;
			printf("\n\tCódigo:%i\n\t1:Nome:%s\n\t2:Preço:%.2f\n\n",start->cod, start->nome, start->preco);
			printf("\n\tIntroduza o numero do campo que deseja alterar:");
			scanf("%i", &opcao);	
			switch(opcao){
				case 1:printf("\tInsira novo nome:"); 
						fflush(stdin);
						strupr(gets(start->nome));
						break;
				case 2: printf("\tInsira novo preço:");
						scanf("%f", &start->preco);
						break;
				default: printf("\n\t CAMPO INVÁLIDO\n");
			}
			printf("\n\t*COMPONENTE ALTERADO COM SUCESSO*");
		}
		start=start->next;
		}if(find==0) printf("\n\tNão foram encontrados componentes com esse código\n\nPressione uma tecla qualquer para voltar ao menu\n");
	
	return ptr;
}

//APAGAR COMPONENTE
COMP  del (COMP ptr, int value){
	COMP aux, act, ant;
	
	if(ptr->cod==value){  
		aux=ptr;
		ptr=ptr->next;
		free(aux);
		return(ptr);
	}
	
	else{ant=ptr;
		act=ptr;
		while((act!=NULL)&&(act->cod!=value)){
			ant=act;
			act=act->next;
		}
		if(act!=NULL){
			ant->next = act->next;
			free(act);
			return(ptr);
		}
	else return(ptr);
}
}







// GUARDAR LISTA DE COMPONENTES EM FICHEIRO

void save(COMP ptr){
	FILE *file;
	file = fopen("Lista Componentes.txt", "w");
	if(file!=NULL){
		while(ptr!=NULL){
		fprintf(file, "%i\n%s\n%f\n",ptr->cod, ptr->nome, ptr->preco);
		ptr=ptr->next;
		}
	}
	fclose(file);
}

// LER FICHEIRO DA LISTA DE COMPONENTES
COMP read_file(COMP ptr) {
	FILE *file;
	int cod;
	char nome[100];
	float preco;
	file = fopen("Lista Componentes.txt", "r");
	while (fscanf(file, "%i\n%s\n%f\n", &cod, &nome, &preco)!=EOF) {
		ptr=InsComp(ptr, cod, nome, preco);
		}
	fclose(file);
	return ptr;
}

// ARVORE N-ARIA 
typedef struct registo{
 int cod;
 int id;
 char des[30];
 float preco;
 struct registo * irmaos;
 struct registo * filhos;
} * AG;

AG inserirFilho(AG apt, int cod, int id, int idFilho, char dFilho[30], float preco, float preco2, int cod2){
	AG novo;
  if (apt == NULL) 
  {novo = (AG) malloc(sizeof(struct registo));
  novo->cod=cod;
   novo->id = idFilho;
   strcpy(novo->des,dFilho);
   novo->preco=preco;
   novo->irmaos = NULL;
   novo->filhos = NULL;
   return(novo);
  }

  else if (apt->cod==cod)
  {novo = (AG) malloc(sizeof(struct registo));
   novo->cod=cod2;
   novo->id = idFilho;
   strcpy(novo->des,dFilho);
   novo->preco=preco2;
   novo->irmaos = apt->filhos;
   novo->filhos = NULL;
   apt->filhos = novo;
   return(apt);
  }
  else {
   inserirFilho(apt->filhos,cod,id,idFilho,dFilho,preco, preco2, cod2);
   inserirFilho(apt->irmaos,cod,id,idFilho,dFilho,preco, preco2, cod2);
   return(apt);
  }
}


// Listar todos os registos da árvore
void listarTodos(AG apt)
{if (apt!=NULL)
 {AG filhos=apt->filhos;
  while (filhos!=NULL)
  {printf("(%d) %i-%s-%.2f  ->  %i-%s-%.2f (%i)\n",apt->cod,apt->id,apt->des,apt->preco,filhos->id,filhos->des,filhos->preco,filhos->cod);
   filhos=filhos->irmaos;
  }
  listarTodos(apt->filhos);
  listarTodos(apt->irmaos);
 }
}


AG equipamento (AG ptr, COMP ptr1){
	int pai, filho, registo_pai, i=2, id, find=0, find2=0;
	COMP ptr2=ptr1, aux=NULL;
	while(find!=1){
		ptr1=ptr2;
	printf("[DEFINIR EQUIPAMENTO ELETRÓNICO]\n\n");
	printf("Componentes Registados:\n");
	listar1(ptr1);
	if(ptr==NULL){
		printf("\n\nQue componente deseja colocar no topo da arvore? (1º REGISTO):");
		scanf("%i", &pai);
		while(ptr1!=NULL){
			if(ptr1->cod==pai){
			aux=ptr1;
			find=1;
			} 
			ptr1=ptr1->next;
		}
		if(find==1) ptr=inserirFilho(ptr,1,0,aux->cod,aux->nome,aux->preco, 0, 0);
		else{ 
			printf("\n\t COMPONENTE NÂO EXISTE\n\tTENTE NOVAMENTE");
			system("pause > nul");
			system("cls");		
		} 
	}
	}
		printf("\n\t\tTopo da árvore  -  %i-%s\n", aux->cod, aux->nome);
		printf("\n\tEscreva a ligação no formato (nºregisto pai->código componente filho)\n\t\tExemplo (1->5)\n\n\tNOTAS:\n\t\tInsira 0 para terminar\n");
		printf("\t\tSe o registo pai introduzido não existir, nenhuma ligação não feita\n\nFazer ligações:\n");
		while(scanf("%i->%i", &pai, &filho)==2){
			ptr1=ptr2;
			find2=0;
			while(ptr1!=NULL){
				if(ptr1->cod==filho) {
					aux=ptr1;	
					find2=1;
				}
				ptr1=ptr1->next;
			}
			if(find2==1){
				ptr=inserirFilho(ptr,pai,0,filho,aux->nome,0,aux->preco,i);
				printf("\tRegisto %i criado\n\n", i);
				i++;
			}else{
				printf("\tComponente filho não existe.  A ligação não foi feita\n");
			}
	}
	return ptr;
}

float custototal(AG ptr){
	if(ptr==NULL) return 0;
	return(ptr->preco + custototal(ptr->filhos)+custototal(ptr->irmaos));
}



int main(int argc, char *argv[]) {
	COMP start=NULL;
	AG start_tree;
	int cod=0, opcao=1;
	char nome[100];
	float price=0;
	char opcaoc;

	
	setlocale(LC_ALL, "Portuguese");
	
	start=read_file(start);
	while(opcao!=0){
		
		system("cls");
		menu();
		printf("---->Introduza a opção:");
		scanf("%i", &opcao);
		system("cls");		
		switch(opcao){
			case 1: printf("[INSERIR NOVO COMPONENTE]\n\n");
					printf("\tNOTA: Por predefinição, o código do componente é gerado automaticamente por ordem crescente\n\n");
					cod=cod_returner(start);
					printf("\tCódigo:%i\n", cod);
					printf("\tIntroduza o nome do componente:");
					fflush(stdin);
					gets(nome);
					strupr(nome);
					printf("\tIntroduza o preço do componente:");
					scanf("%f", &price);
					start=InsComp(start, cod, nome, price);
					printf("\n\n\t\t*Componente inserido com sucesso*\n");
					system("pause > nul");
					break;
			
			case 2: if(start==NULL) printf("Ainda não foram registados componentes\n\n*Pressione uma tecla qualquer para voltar ao menu*\n");
					else {
					printf("[COMPONENTES REGISTADOS]\n\n");
					listar(start);
					printf("\n\n\t\t*Listagem completa*\n");	
					}
					system("pause > nul");
					break;
		
			case 3: if(start==NULL) printf("Ainda não foram registados componentes\n\n*Pressione uma tecla qualquer para voltar ao menu*\n");
					else{
					printf("[PROCURAR COMPONENTE PELO NUMERO]\n\n");
					printf("\tInsira o número a procurar:");
					scanf("%i", &cod);
					if(pesquisa_cod(start, cod)==0) printf("\n\tNão foram encontrados componentes com esse código\n\n");
					else printf("\n\t\t*COMPONENTE ENCONTRADO COM SUCESSO*");
					}
					system("pause > nul");
					break;
			
			case 4: if(start==NULL) printf("Ainda não foram registados componentes\n\n*Pressione uma tecla qualquer para voltar ao menu*\n");
					else{
					printf("[PROCURAR COMPONENTE POR NOME]\n\n");
					printf("\tInsira o nome a procurar:");
					fflush(stdin);
					gets(nome);
					strupr(nome);
					if(pesquisa_nome(start, nome)==0) printf("\n\tNão foram encontrados componentes com esse nome\n\n");
					else printf("\n\t\t*COMPONENTE ENCONTRADO COM SUCESSO*");
					}
					system("pause > nul");
					break;
			
			case 5: if(start==NULL) printf("Ainda não foram registados componentes\n\n*Pressione uma tecla qualquer para voltar ao menu*\n");
					else{
					printf("[ALTERAR DADOS DE UM COMPONENTE]\n\n");
					printf("\tInsira o código do componente que desjea alterar:");
					scanf("%i", &cod);
					start=alt_comp(start, cod);
					}
					system("pause > nul");
					break; 
			case 6: if(start==NULL) printf("Ainda não foram registados componentes\n\n*Pressione uma tecla qualquer para voltar ao menu*\n");
					else{
						printf("APAGAR UM COMPONENTE]\n\n");
						printf("\tInsira o código do componente que deseja apagar:");	
						scanf("%i", &cod);
						if(pesquisa_cod(start, cod)==0) printf("\n\tNão foram encontrados componentes com esse código\n\n");
						else{
							printf("\tPressione ""y"" para apagar este componente");
							fflush(stdin);
							scanf("%c", &opcaoc);
							if(opcaoc=='y'){
								start=del(start, cod);
								printf("\n\n\t\t*COMPONENTE APAGADO COM SUCESSO*");
							}else printf("\n\n\t\t*O COMPONENTE NÃO FOI APAGADO*");
						}
					}
					system("pause > nul");
					break;
			case 7: if(start==NULL) printf("Não é possivel criar um equipamento sem componentes registados\n\n*Pressione uma tecla qualquer para voltar ao menu*\n");
					else{
						if(start_tree!=NULL) printf("Já foi construída uma árvore nesta sessão");
						else{
							start_tree=equipamento(start_tree, start);
							printf("\n\n\t\t*ÁRVORE DO EQUIPAMENTO CONSTRUÍDA COM SUCESSO*");
						}
					}
					system("pause > nul");
					break;
			case 8: if(start_tree==NULL) printf("Ainda não foi construída uma árvore nesta sessão");
					else{
						printf("[LIGAÇÕES DA ÁRVORE DO EQUIPAMENTO ELETRÓNICO]\n\n");
						printf("FORMATO:\n\t(Registo) codigo-nome-preço  ->  codigo-nome-preço (Registo)\n\n");
						listarTodos(start_tree);
						printf("\n\n\tCusto total do equipamento=%.2f", custototal(start_tree));
					}
					system("pause > nul");
					break;
			case 9: save(start);
					break;
			default:
				printf("\n\t\t*OPÇÃO INVÁLIDA, PRESSIONE UMA TECLA QUALQUER PARA TENTAR NOVAMENTE*\n");
				system("pause > nul");
				system("cls");
				break;
		}
	}
	return 0;
}

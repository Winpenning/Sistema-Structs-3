#include <stdio.h>
#include <stdlib.h>

typedef struct _no{
	void *e;
	struct _no *prox;
}No;

typedef struct _lista{
	No *primeiro;
	No *ultimo;
	int tamanho;
}Lista;

typedef struct _personagem{
    int id;
    char nome[20];
    char descricao[100];
}Personagem;

typedef struct _Anime{
    int id;
    char nome[30];
    char genero[30];

    Lista *personagem;
    int numPersonagens;
}Anime;

typedef struct _Estudio{
    int id;
    char nome[30];
    char heaquarter[30];
    
    Lista *anime;
    int numAnimes;
}Estudio;
// FUNÇÃO DE INTERFACE
void interface();
// FUNÇÕES DE LISTA
Lista* criarLista();
void inserir(Lista *lista, void *novoElemento);
void InfoLista(Lista *lista);
int remover(Lista *lista, int pos);
// FUNÇÕES DE BUSCA
Estudio* buscarEstudio(Lista *lista, int pos);
Anime* buscarAnime(Lista *lista, int pos);
Personagem* buscarPesonagem(Lista *lista, int pos);
int buscarposicaoIDAnime(Lista *lista, int id);
int buscarPosicaoIDPersoagem(Lista *lista, int id);
// FUNÇÕES DE LISTAGEM
void listarEstudios(Lista *lista);
void listarAnimes(Lista *lista);
void listarPersonagens(Lista *lista);
// FUNÇÕES DE ADIÇÃO
Estudio* addEstudio(int numEstudio);
Anime* addAnime(int numanime);
Personagem* addPersonagem(int numPesonagem);

int main(){
    int m = 1,op = 0, switch2, numEstudios = 0, numAnimes = 0, numPersonagens = 0, listIDestudio, listIDanime;
    int AlterEstudio, AlterAnime, AlterPersonagem;
    Lista *estudio = criarLista();
    Lista *anime = criarLista();
    Lista *personagem = criarLista();
    

    while(m==1){
        interface();
        printf("--> ");
        scanf("%d", &op);
        switch(op){
        case 1:
           if (numEstudios <= 0){
            printf(" -- SEM ESTUDIOS ADICIONADOS! --\n");
           }
           else{
            listarEstudios(estudio);
           }
        break;
        case 2:
            inserir(estudio, ((void*)addEstudio(numEstudios)));
            numEstudios++;
        break;
        case 3:  
            printf("1) Exibir todos os animes\n");
            printf("2) Exibir animes de um estudio\n");
            scanf("%d", &switch2);
            switch(switch2){
            case 1:
                if (numAnimes <= 0){
                printf(" -- SEM ANIMES ADICIONADOS! --\n");
                }
                else{
                listarAnimes(anime);
                }
            break;
            case 2:
                if (numEstudios <= 0){
                   printf(" -- SEM ESTUDIOS ADICIONADOS! --\n");
                   break;
                }
                else{
                   listarEstudios(estudio);
                }
                printf("\n\n");
                printf("Digite o id do estudio:");
                scanf("%d", &listIDestudio);
                
                if (buscarEstudio(estudio,listIDestudio)->numAnimes <= 0){
                printf("-- SEM ANIMES RELACIONADOS AO ESTUDIO --\n");
                }
                else{
                    listarAnimes(buscarEstudio(estudio,listIDestudio)->anime);
                }
            break;
            }
        break;
        case 4:
            inserir(anime, ((void*)addAnime(numAnimes))); 
            numAnimes++;
        break;
        case 5:       
            printf("1) Exibir todos os personagens\n");
            printf("2) Exibir personagens de um anime\n");
            scanf("%d", &switch2);
        switch(switch2){
                case 1:           
                    if (numPersonagens <= 0)
                        {
                        printf(" -- SEM PERSONAGENS ADICIONADOS! --\n");
                        }
                        else
                        {
                        listarPersonagens(personagem);
                        }
                break;
                case 2:
                    if (numAnimes <= 0){
                        printf(" -- SEM ANIMES ADICIONADOS! --\n");
                        break;
                    }
                    else{
                       listarAnimes(anime);
                    }
                    printf("\n\n");
                    printf("Digite o id do anime\n");
                    scanf("%d", &listIDanime);
                    if (buscarAnime(anime, listIDanime)->numPersonagens <= 0){
                        printf(" -- O ANIME NÃO POSSUI PERSONAGEM CADASTRADO! --\n");
                    }
                    else{
                        listarPersonagens((buscarAnime(anime, listIDanime)->personagem));
                    }
                break;
            }
            
        break;
        case 6:
           inserir(personagem, ((void*)addPersonagem(numPersonagens)));
           numPersonagens++;
        break;
        case 7:
            listarEstudios(estudio);
            printf("\nDigite o id do estudio que voce deseja relacionar um anime\n");
            scanf("%d", &AlterEstudio);
            listarAnimes(anime);
            printf("\nDigite o id do anime do estudo: ");
            scanf("%d", &AlterAnime);
            inserir(buscarEstudio(estudio, AlterEstudio)->anime, buscarAnime(anime, AlterAnime));
            buscarEstudio(estudio, AlterEstudio)->numAnimes++;
            printf(" -- ANIME RELACIONADO COM SUCESSO! --\n");
        break;
        case 8:
            listarAnimes(anime);
            printf("\nDigite o id do anime que voce deseja relacionar um personagem: ");
            scanf("%d", &AlterAnime);
            listarPersonagens(personagem);
            printf("digite o id do personagem do anime: ");
            scanf("%d", &AlterPersonagem);
            inserir(buscarAnime(anime, AlterAnime)->personagem, buscarPesonagem(personagem, AlterPersonagem));
            buscarAnime(anime,AlterAnime)->numPersonagens++;
            printf(" -- PERSONAGEM RELACIONADO COM SUCESSO\n");
        break;
        case 9:
            listarEstudios(estudio);
            printf("Digite o id do estudio desejado: ");
            scanf("%d", &AlterEstudio);
            listarAnimes(buscarEstudio(estudio,AlterEstudio)->anime);
            printf("Digite o ID do anime que deseja remover: ");
            scanf("%d", &AlterAnime);
            if(AlterAnime<0 || AlterAnime>numAnimes){
                printf("opcao de anime invalida\n");
            }
            else{
                Estudio *e = buscarEstudio(estudio,AlterEstudio);
                int posL = buscarposicaoIDAnime(e->anime,AlterAnime);
                remover(e->anime, posL);
                e->numAnimes--;
                printf(" -- REMOVIDO COM SUCESSO! --\n");
            }
        break;
        case 10:
            listarAnimes(anime);
            printf("\nDigite o id do anime que voce deseja relacionar um personagem: ");
            scanf("%d", &AlterAnime);
            listarPersonagens(buscarAnime(anime,AlterAnime)->personagem);
            printf("digite o id do personagem do anime: ");
            scanf("%d", &AlterPersonagem);
            if(AlterPersonagem<0 || AlterPersonagem>numPersonagens){
                printf("opcao de personagem invalida");
            }
            else{
                Anime *a = buscarAnime(anime, AlterAnime);
                int posP = buscarPosicaoIDPersoagem(a->personagem, AlterPersonagem);
                remover(a->personagem, posP);
                a->numPersonagens--;
                printf(" -- REMOVIDO COM SUCESSO! --\n");
            }
        break;
        
        default:
        printf("Opção invalida\n");
        };
    }
return 0;
}

void interface(){
    puts("01) Exibir Estudios\n");
    puts("02) Adicionar Estudio\n");
    puts("03) Exibir Animes\n");
    puts("04) adicionar Anime\n");
    puts("05) Exibir personagens\n");
    puts("06) adicionar personagens\n");
    puts("07) Adicionar Anime para um Estudio\n");
    puts("08) Adicionar personagem para Anime\n");
    puts("09) Remover Anime de um Estudio\n");
    puts("10) Remover personagem de Anime\n");
}

Lista* criarLista(){
	Lista *novaLista = (Lista*) malloc(sizeof(Lista));
	novaLista->primeiro = NULL;
	novaLista->ultimo = NULL;
	novaLista->tamanho = 0;
	return novaLista;
}

void inserir(Lista *lista, void *novoElemento){
	No *novoNo = (No*) malloc(sizeof(No));
	novoNo->e = novoElemento;
	novoNo->prox = NULL;

	if(lista->tamanho == 0){
		lista->primeiro = novoNo;
		lista->ultimo = novoNo;
		lista->tamanho++;
	}else{
		lista->ultimo->prox = novoNo;
		lista->ultimo = novoNo;
		lista->tamanho++;
	}
}

void InfoLista(Lista *lista){
	printf("end lista: %p\nend primeiro: %p\nend ultimo: %p\ntamanho: %d\n",
		lista, lista->primeiro, lista->ultimo, lista->tamanho);
	printf("\n");
}

int remover(Lista *lista, int pos){
	if(pos < 0 || pos>= lista->tamanho)
		return -1;
	No *removido;
	if(lista->tamanho == 1 && pos == 0){
		removido = lista->primeiro;
		free(removido);
		lista->primeiro = NULL;
		lista->ultimo = NULL;
		lista->tamanho--;
		return 0;
	}
	if(pos == 0){
		removido = lista->primeiro;
		lista->primeiro = lista->primeiro->prox;
		free(removido);
		lista->tamanho--;
		return 0;
	}
	No *aux = lista->primeiro;
	int i;
	for(i=0; i<pos-1; i++){
		aux = aux->prox;
	}
	removido = aux->prox;
	aux->prox = aux->prox->prox;
	free(removido);
	if(lista->tamanho-1 == pos){
		lista->ultimo = aux;
	}
	lista->tamanho--;
	return 0;
}

Estudio* buscarEstudio(Lista *lista, int pos){
	int i;
	if(pos < 0 || pos>= lista->tamanho)
		return NULL;
	No *aux = lista->primeiro;
	for(i=0; i<pos; i++)
		aux = aux->prox;
	return aux->e;
}

Anime* buscarAnime(Lista *lista, int pos){
	int i;
	if(pos < 0 || pos>= lista->tamanho)
		return NULL;
	No *aux = lista->primeiro;
	for(i=0; i<pos; i++)
		aux = aux->prox;
	return aux->e;
}

Personagem* buscarPesonagem(Lista *lista, int pos){
	int i;
	if(pos < 0 || pos>= lista->tamanho)
		return NULL;
	No *aux = lista->primeiro;
	for(i=0; i<pos; i++)
		aux = aux->prox;
	return aux->e;
}

int buscarposicaoIDAnime(Lista *lista, int id){
    int i=0;
	No *aux = lista->primeiro;
    Anime *l;
    l = (Anime*)aux->e;
	while(l->id!=id){
        aux = aux->prox;
        l = (Anime*)aux->e;
        i++;
    }
		
	return i;
}

int buscarPosicaoIDPersoagem(Lista *lista, int id){
        int i=0;
	No *aux = lista->primeiro;
    Personagem *l;
    l = (Personagem*)aux->e;
	while(l->id!=id){
        aux = aux->prox;
        l = (Personagem*)aux->e;
        i++;
    }
		
	return i;
}

void listarEstudios(Lista *lista){
    No *aux = lista->primeiro;
    Estudio *a;
    printf("id\tnome\tHeadquarter\n");
    while(aux != NULL){
        a = (Estudio*) aux->e;
        printf("%d\t%s\t%s\n",a->id ,a->nome, a->heaquarter);
        aux = aux->prox;
    }
    printf("\n\n");
}

void listarAnimes(Lista *lista){
    No *aux = lista->primeiro;
    Anime *l;
    printf("id\tnome\tGenero\n");
    while(aux != NULL){
        l = (Anime*) aux->e;
        printf("%d\t%s\t%s\n", l->id, l->nome, l->genero);
        aux = aux->prox;
    }
    printf("\n\n");
}

void listarPersonagens(Lista *lista){
    No *aux = lista->primeiro;
    Personagem *p;
    printf("id     nome         descricao\n");
    while(aux != NULL){
        p = (Personagem*) aux->e;
        printf("%d  -   %s          %s \n", p->id, p->nome, p->descricao);
        aux = aux->prox;
    }
    printf("\n\n");
}

Estudio* addEstudio(int numEstudio){
    Estudio *estudio;
    estudio = malloc(sizeof(Estudio));
    estudio->id = numEstudio;
    printf("Digite o nome do Estudio: ");
    scanf(" %[^\n]s", estudio->nome);
    printf("Headquarter: ");
    scanf(" %[^\n]s", estudio->heaquarter);
    printf("\nEstudio adicionado com sucesso\n");
    
    estudio->numAnimes = 0;
    estudio->anime = criarLista();
    return estudio;
}

Anime* addAnime(int numanime){
    Anime *anime;
    anime = malloc(sizeof(Anime));
    anime->id = numanime;
    
    printf("Digite o nome do anime: ");
    scanf(" %[^\n]s", anime->nome);
    printf("digite o genero do anime: ");
    scanf(" %[^\n]s", anime->genero);
    printf("\nanime adicionado com sucesso\n");
   
    anime->personagem = criarLista();
    anime->numPersonagens = 0;
    return anime;
}

Personagem* addPersonagem(int numPesonagem){
    Personagem* personagem;
    personagem = malloc(sizeof(Personagem));
    personagem->id = numPesonagem;
    printf("Digite o nome do personagem: ");
    scanf(" %[^\n]s", personagem->nome);
    printf("Digite a descricao do personagem: ");
    scanf(" %[^\n]s", personagem->descricao);
    printf("\n personagem adicionado com sucesso\n");
    return personagem;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TAM_VET 10

typedef struct {
	int registro;
	char nome[128];
	int anosExperiencia;
	char especialidade[64];
} Tatuador;

typedef struct {
	long long int cpf;
	char nome[128];
	int idade;
	char tipoPele[64];
	int numeroTatuagens;
} Cliente;

typedef struct {
	int dia;
	int mes;
	int ano;
} Data;

typedef struct {
	int idTatuagem;
	Data data;
	int registroTatuador;
	long long int cpfCliente;
	int valor; // Em centavos
} Sessao;

// Funções de menu
int menuPrincipal();
int menuTatuadores();
int menuClientes();
int menuSessoes();
int menuCampoTatuador();
int menuCampoCliente();
int menuCampoSessao();

// Funções de tela
void telaTatuadores(Tatuador*, int*, int*, Sessao*, int*, int*);
void telaClientes(Cliente*, int*, int*, Sessao*, int*, int*);
void telaSessoes(Sessao*, int*, int*, Tatuador*, int*, int*, Cliente*, int*, int*);

// Funções de Tatuadores
void carregarTatuadores(Tatuador*, int*, int*);
void cadastrarTatuador(Tatuador*, int*, int*);
void alterarTatuador(Tatuador*, int*, int*, Sessao*, int*, int*);
void consultarTatuador(Tatuador*, int*, int*);
void removerTatuador(Tatuador*, int*, int*, Sessao*, int*, int*);
void listarTatuadores(Tatuador*, int*, int*);
void realocarTatuadores(Tatuador*, int*, int*);
void salvarTatuadores(Tatuador*, int*, int*);
int buscarTatuador(int, Tatuador*, int*, int*);
void imprimirTatuador(Tatuador*);

// Funções de Clientes
void carregarClientes(Cliente*, int*, int*);
void cadastrarCliente(Cliente*, int*, int*);
void alterarCliente(Cliente*, int*, int*, Sessao*, int*, int*);
void consultarCliente(Cliente*, int*, int*);
void removerCliente(Cliente*, int*, int*, Sessao*, int*, int*);
void listarClientes(Cliente*, int*, int*);
void realocarClientes(Cliente*, int*, int*);
void salvarClientes(Cliente*, int*, int*);
int buscarCliente(long long int, Cliente*, int*, int*);
void imprimirCliente(Cliente*);

// Funções de Sessões
void carregarSessoes(Sessao*, int*, int*);
void cadastrarSessao(Sessao*, int*, int*, Tatuador*, int*, int*, Cliente*, int*, int*);
void alterarSessao(Sessao*, int*, int*, Tatuador*, int*, int*, Cliente*, int*, int*);
void removerSessao(Sessao*, int*, int*, Tatuador*, int*, int*, Cliente*, int*, int*);
void mostrarSessoes(Sessao*, int*, int*, Tatuador*, int*, int*, Cliente*, int*, int*);
void gerarRelatorioSessoes(Sessao*, int*, int*, Tatuador*, int*, int*, Cliente*, int*, int*);
void realocarSessoes(Sessao*, int*, int*);
void salvarSessoes(Sessao*, int*, int*);
int buscarSessao(int, Sessao*, int*, int*);
void imprimirSessao(Sessao*, Tatuador*, Cliente*);

// Funções auxiliares
int validarData(Data*);
int compararDatas(Data*, Data*);

int main(){
	// Vetores de estrutura
	Tatuador *tatuadores = (Tatuador*) malloc(sizeof(Tatuador)*TAM_VET);
	Cliente *clientes = (Cliente*) malloc(sizeof(Cliente)*TAM_VET);
	Sessao *sessoes = (Sessao*) malloc(sizeof(Sessao)*TAM_VET);
	
	// Variáveis de controle
	int capTatuadores = TAM_VET;
	int capClientes = TAM_VET;
	int capSessoes = TAM_VET;
	
	int tamTatuadores = 0;
	int tamClientes = 0;
	int tamSessoes = 0;
	
	// Carrega dados do arquivo
	carregarTatuadores(tatuadores, &capTatuadores, &tamTatuadores);
	carregarClientes(clientes, &capClientes, &tamClientes);
	carregarSessoes(sessoes, &capSessoes, &tamSessoes);
	
	// Flag para continuar
	int continua = 1;
	
	// Laço do programa
	while(continua){
		switch(menuPrincipal()){
		case 1:
			telaTatuadores(tatuadores, &capTatuadores, &tamTatuadores, sessoes, &capSessoes, &tamSessoes);
			break;
		case 2:
			telaClientes(clientes, &capClientes, &tamClientes, sessoes, &capSessoes, &tamSessoes);			
			break;
		case 3:
			telaSessoes(sessoes, &capSessoes, &tamSessoes, tatuadores, &capTatuadores, &tamTatuadores, clientes, &capClientes, &tamClientes);
			break;
		case 4:
			listarTatuadores(tatuadores, &capTatuadores, &tamTatuadores);
			break;
		case 5:
			listarClientes(clientes, &capClientes, &tamClientes);
			break;
		case 6:
			mostrarSessoes(sessoes, &capSessoes, &tamSessoes, tatuadores, &capTatuadores, &tamTatuadores, clientes, &capClientes, &tamClientes);
			break;
		case 7:
			gerarRelatorioSessoes(sessoes, &capSessoes, &tamSessoes, tatuadores, &capTatuadores, &tamTatuadores, clientes, &capClientes, &tamClientes);
			break;
		case 8:
			// Nao continua o programa
			continua = 0;
			break;			
		}	
	}
	
	// Salva o conteudo dos vetores de registros em arquivos
	salvarTatuadores(tatuadores, &capTatuadores, &tamTatuadores);
	salvarClientes(clientes, &capClientes, &tamClientes);
	salvarSessoes(sessoes, &capSessoes, &tamSessoes);
	
	return 0;
}

int menuPrincipal(){
	int opcao;
	printf("[MENU PRINCIPAL]\n");
	printf("[1] Tatuadores...\n");
	printf("[2] Clientes...\n");
	printf("[3] Sessoes...\n");
	printf("[4] Listar todos os tatuadores\n");
	printf("[5] Listar todos os clientes\n");
	printf("[6] Mostrar todas as sessoes...\n");
	printf("[7] Gerar relatorio de sessoes...\n");
	printf("[8] Sair\n");
	
	// Laço de validação
	while(1){
		printf(">>> ");
		scanf("%d", &opcao);
		fflush(stdin);
		printf("\n"); // Quebra de linha
		
		if(opcao > 0 && opcao < 9)
			return opcao;
			
		printf("Opcao invalida! Tente novamente.\n\n");
	}
}

// Funções de Tatuadores

int menuTatuadores(){
	int opcao;
	printf("[MENU: TATUADORES]\n");
	printf("[1] Cadastrar tatuador\n");
	printf("[2] Alterar tatuador\n");
	printf("[3] Consultar tatuador\n");
	printf("[4] Remover atuador\n");
	printf("[5] Voltar\n");
	
	// Laço de validação
	while(1){
		printf(">>> ");
		scanf("%d", &opcao);
		fflush(stdin);
		printf("\n"); // Quebra de linha
		
		if(opcao > 0 && opcao < 6)
			return opcao;
			
		printf("Opcao invalida! Tente novamente.\n\n");
	}
}

int menuClientes(){
	int opcao;
	printf("[MENU: CLIENTES]\n");
	printf("[1] Cadastrar cliente\n");
	printf("[2] Alterar cliente\n");
	printf("[3] Consultar cliente\n");
	printf("[4] Remover cliente\n");
	printf("[5] Voltar\n");
	
	// Laço de validação
	while(1){
		printf(">>> ");
		scanf("%d", &opcao);
		fflush(stdin);
		printf("\n"); // Quebra de linha
		
		if(opcao > 0 && opcao < 6)
			return opcao;
			
		printf("Opcao invalida! Tente novamente.\n\n");
	}
}

int menuSessoes(){
	int opcao;
	printf("[MENU: SESSOES]\n");
	printf("[1] Marcar sessao\n");
	printf("[2] Alterar sessao\n");
	printf("[3] Remover sessao\n");
	printf("[4] Voltar\n");
	
	// Laço de validação
	while(1){
		printf(">>> ");
		scanf("%d", &opcao);
		fflush(stdin);
		printf("\n"); // Quebra de linha
		
		if(opcao > 0 && opcao < 6)
			return opcao;
			
		printf("Opcao invalida! Tente novamente.\n\n");
	}
}

int menuCampoTatuador(){
	int opcao;
	
	printf("[1] Numero de registro\n");
	printf("[2] Nome\n");
	printf("[3] Anos de experiencia\n");
	printf("[4] Especialidade\n");
	printf("[5] Voltar\n");
	
	// Laço de validação
	while(1){
		printf(">>> ");
		scanf("%d", &opcao);
		fflush(stdin);
		printf("\n"); // Quebra de linha
		
		if(opcao > 0 && opcao < 6)
			return opcao;
			
		printf("Opcao invalida! Tente novamente.\n\n");
	}
}

int menuCampoCliente(){
	int opcao;
	
	printf("[1] CPF\n");
	printf("[2] Nome\n");
	printf("[3] Idade\n");
	printf("[4] Tipo de pele\n");
	printf("[5] Numero de tatuagens\n");
	printf("[6] Voltar\n");
	
	// Laço de validação
	while(1){
		printf(">>> ");
		scanf("%d", &opcao);
		fflush(stdin);
		printf("\n"); // Quebra de linha
		
		if(opcao > 0 && opcao < 7)
			return opcao;
			
		printf("Opcao invalida! Tente novamente.\n\n");
	}
}

int menuCampoSessao(){
	int opcao;
	
	printf("[1] ID\n");
	printf("[2] Data\n");
	printf("[3] Tatuador\n");
	printf("[4] Cliente\n");
	printf("[5] Valor\n");
	printf("[6] Voltar\n");
	
	// Laço de validação
	while(1){
		printf(">>> ");
		scanf("%d", &opcao);
		fflush(stdin);
		printf("\n"); // Quebra de linha
		
		if(opcao > 0 && opcao < 7)
			return opcao;
			
		printf("Opcao invalida! Tente novamente.\n\n");
	}
}

void telaTatuadores(Tatuador *tatuadores, int *capTatuadores, int *tamTatuadores,
					Sessao *sessoes, int *capSessoes, int *tamSessoes
				   ){
	int continua = 1;
	
	// Laço do programa
	while(continua){
		switch(menuTatuadores()){
		case 1:
			cadastrarTatuador(tatuadores, capTatuadores, tamTatuadores);
			break;
		case 2:
			alterarTatuador(tatuadores, capTatuadores, tamTatuadores, sessoes, capSessoes, tamSessoes);
			break;
		case 3:
			consultarTatuador(tatuadores, capTatuadores, tamTatuadores);
			break;
		case 4:
			removerTatuador(tatuadores, capTatuadores, tamTatuadores, sessoes, capSessoes, tamSessoes);
			break;			
		case 5:
			// Nao continua o programa
			continua = 0;
			break;			
		}	
	}
}


void telaClientes(Cliente *clientes, int *capClientes, int *tamClientes,
				  Sessao *sessoes, int *capSessoes, int *tamSessoes
				 ){
	int continua = 1;
	
	// Laço do programa
	while(continua){
		switch(menuClientes()){
		case 1:
			cadastrarCliente(clientes, capClientes, tamClientes);
			break;
		case 2:
			alterarCliente(clientes, capClientes, tamClientes, sessoes, capSessoes, tamSessoes);
			break;
		case 3:
			consultarCliente(clientes, capClientes, tamClientes);
			break;
		case 4:
			removerCliente(clientes, capClientes, tamClientes, sessoes, capSessoes, tamSessoes);
			break;			
		case 5:
			// Nao continua o programa
			continua = 0;
			break;			
		}	
	}
}

void telaSessoes(Sessao *sessoes, int *capSessoes, int *tamSessoes,
				 Tatuador *tatuadores, int *capTatuadores, int *tamTatuadores,
				 Cliente *clientes, int *capClientes, int *tamClientes
				){
					
	int continua = 1;
	
	// Laço do programa
	while(continua){
		switch(menuSessoes()){
		case 1:
			cadastrarSessao(sessoes, capSessoes, tamSessoes, tatuadores, capTatuadores, tamTatuadores, clientes, capClientes, tamClientes);
			break;
		case 2:
			alterarSessao(sessoes, capSessoes, tamSessoes, tatuadores, capTatuadores, tamTatuadores, clientes, capClientes, tamClientes);
			break;
		case 3:
			removerSessao(sessoes, capSessoes, tamSessoes, tatuadores, capTatuadores, tamTatuadores, clientes, capClientes, tamClientes);
			break;			
		case 4:
			// Nao continua o programa
			continua = 0;
			break;			
		}	
	}
}

void carregarTatuadores(Tatuador *tatuadores, int *capacidade, int *tamanho){	
	// Tenta abrir o arquivo tatuadores.bin
	FILE *pArquivo = fopen("tatuadores.bin", "rb");
	
	// Se o arquivo não existir, cria arquivo:
	if(pArquivo == NULL){
		printf("Criando arquivo 'tatuadores.bin'...\n\n");
		
		pArquivo = fopen("tatuadores.bin", "wb");
		
		// Verifica se criou corretamente
		if(pArquivo == NULL)
			printf("ERRO: Nao foi possivel criar o arquivo 'tatuadores.bin'...\n\n");
			
		fclose(pArquivo);
		
		return;
	}
	
	// Cria um ponteiro de tatuador
	Tatuador t;
	
	// Repete indefinidamente
	while (1) {
		// Se não for possivel ler, quebra laço
		if(fread(&t, sizeof(Tatuador), 1, pArquivo) != 1)
			break;
		
		// Copia conteudo
		tatuadores[*tamanho] = t;
		
		// Incrementa tamanho
		*tamanho += 1;	
		
		// Verifica se é necessário realocar memória para vetor
		realocarTatuadores(tatuadores, capacidade, tamanho);
    }
}

void cadastrarTatuador(Tatuador* tatuadores, int* capacidade, int* tamanho){
	// Cria um novo tatuador
	Tatuador tatuador;
	char op;
	
	printf("[CADASTRAR TATUADOR]\n");
	
	// Laço de validação do registro
	while(1){
		// Lê registro
		printf("Registro: ");
		scanf("%d", &tatuador.registro);
		fflush(stdin);
					
		if(buscarTatuador(tatuador.registro, tatuadores, capacidade, tamanho) != -1){
			printf("ERRO: numero de registro ja cadastrado! Ler novo registro? (S/N)\n>>> ");
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's')
				continue;
			
			printf("\nOperacao cancelada.\n\n");
			return;
		}
		
		break;
	}
	
	// Obtem nome
	printf("Nome: ");
	fgets(tatuador.nome, 128, stdin);
	
	// Remove quebra de linha
	tatuador.nome[strlen(tatuador.nome) - 1] = 0;
	
	// Obtem anos de experiência
	printf("Anos de experiencia: ");
	scanf("%d", &tatuador.anosExperiencia);
	fflush(stdin);
	
	// Obtem especialidade
	printf("Especialidade: ");
	fgets(tatuador.especialidade, 64, stdin);
	
	// Remove quebra de linha
	tatuador.especialidade[strlen(tatuador.especialidade) - 1] = 0;
		
	printf("\nDeseja cadastrar tatuador? (S/N)\n>>> ");
	
	op = getc(stdin);
	fflush(stdin);
			
	if(op == 'S' || op == 's'){
		tatuadores[*tamanho] = tatuador;
		*tamanho += 1;
		printf("\nTatuador cadastrado com sucesso!\n\n");
		
		// Verifica se é necessário realocar memória para vetor
		realocarTatuadores(tatuadores, capacidade, tamanho);
		
		return;
	}
	
	// Encerra
	printf("\nOperacao cancelada.\n\n");
	return;
}

void alterarTatuador(Tatuador *tatuadores, int *capTatuadores, int *tamTatuadores,
					 Sessao *sessoes, int *capSessoes, int *tamSessoes
					){
	int i, registroTatuador, idxTatuador;
	int novoRegistro, novoAnosExperiencia;
	char op, novoNome[128], novaEspecialidade[64];
	printf("[ALTERAR TATUADOR]\n\n");
	
	// Validação do registro
	while(1){
		printf("Registro do Tatuador: ");
		scanf("%d", &registroTatuador);
		fflush(stdin);
		
		idxTatuador = buscarTatuador(registroTatuador, tatuadores, capTatuadores, tamTatuadores);
		if(idxTatuador == -1){
			printf("ERRO: numero de registro nao encontrado! Ler novo registro? (S/N)\n>>> ");
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's')
				continue;
			
			printf("\nOperacao cancelada.\n\n");
			return;
		}
		
		break;
	}
			
	while(1){
		// Registro encontrado, imprime informações do tatuador:
		
		printf("\nTatuador encontrado:\n");
		imprimirTatuador(&tatuadores[idxTatuador]);
		
		printf("\nQual campo deve ser alterado?\n\n");
	
		switch(menuCampoTatuador()){
		case 1: // Alterar Registro
			
			// Validação do novo registro
			while(1){
				printf("Novo registro: ");
				scanf("%d", &novoRegistro);
				fflush(stdin);
				
				if(buscarTatuador(novoRegistro, tatuadores, capTatuadores, tamTatuadores) != -1){
					printf("ERRO: numero de registro ja cadastrado! Ler novo registro? (S/N)\n>>> ");
					op = getc(stdin);
					fflush(stdin);
				
					if(op == 'S' || op == 's')
					continue;
				
					printf("\nOperacao cancelada.\n\n");
					return;
				}
				
				break;
			}
			
			// Alteração do registro			
			printf("\nDeseja alterar o registro do tatuador de [%d] para [%d]? (S/N)\n>>> ",tatuadores[idxTatuador].registro, novoRegistro);
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's'){
				// Altera o registro em todos as sessoes marcadas
				for(i = 0; i < *tamSessoes; i++)
					if(sessoes[i].registroTatuador == tatuadores[idxTatuador].registro)
						sessoes[i].registroTatuador = novoRegistro;
				
				// Altera o registro do tatuador
				tatuadores[idxTatuador].registro = novoRegistro;
				
				printf("\nRegistro atualizado com sucesso!\n\n");
				
			} else {
				printf("\nOperacao cancelada.\n");
			}
					
			break;
		case 2: // Alterar Nome
			printf("Novo nome: ");
			fgets(novoNome, 128, stdin);
			
			// Remove quebra de linha
			novoNome[strlen(novoNome) - 1] = 0;
			
			// Alteração do nome			
			printf("\nDeseja alterar o nome do tatuador de [%s] para [%s]? (S/N)\n>>> ",tatuadores[idxTatuador].nome, novoNome);
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's'){
				// Altera o nome do tatuador
				strcpy(tatuadores[idxTatuador].nome, novoNome);
				
				printf("\nNome atualizado com sucesso!\n\n");
				
			} else {
				printf("\nOperacao cancelada.\n");
			}
			
			break;
		case 3: // Alterar Anos de Experiência
			printf("Novo valor de anos de experiencia: ");
			scanf("%d", &novoAnosExperiencia);
			fflush(stdin);
			
			// Alteração dos anos de experiencia			
			printf("\nDeseja alterar os anos de experiencia do tatuador de [%d] para [%d]? (S/N)\n>>> ",tatuadores[idxTatuador].anosExperiencia, novoAnosExperiencia);
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's'){
				// Altera o nome do tatuador
				tatuadores[idxTatuador].anosExperiencia = novoAnosExperiencia;
				
				printf("\nAnos de experiencia atualizados com sucesso!\n\n");
				
			} else {
				printf("\nOperacao cancelada.\n");
			}
			
			break;
		case 4: // Alterar Especialidade
			printf("Nova especialidade: ");
			fgets(novaEspecialidade, 64, stdin);
			
			// Remove quebra de linha
			novaEspecialidade[strlen(novaEspecialidade) - 1] = 0;
			
			// Alteração de especialidade			
			printf("\nDeseja alterar a especialidade do tatuador de [%s] para [%s]? (S/N)\n>>> ",tatuadores[idxTatuador].especialidade, novaEspecialidade);
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's'){
				// Altera a especialidade do tatuador
				strcpy(tatuadores[idxTatuador].especialidade, novaEspecialidade);
				
				printf("\nEspecialidade atualizada com sucesso!\n\n");
				
			} else {
				printf("\nOperacao cancelada.\n");
			}
			
			break;
		case 5: // Voltar
			return;
		}
	}
}

void consultarTatuador(Tatuador *tatuadores, int *capacidade, int *tamanho){
	int i, registroTatuador, idxTatuador, encontrado;
	int registro, anosExperiencia;
	char op, nome[128], especialidade[64];
	
	
	printf("[CONSULTAR TATUADOR]\n");
	
	while(1){
		
		printf("\nPor qual campo deve ser consultado?\n\n");
		
		switch(menuCampoTatuador()){
		case 1: // Por registro
			
			// Laço da tela
			while(1){
				printf("Registro: ");
				scanf("%d", &registro);
				fflush(stdin);
				
				idxTatuador = buscarTatuador(registro, tatuadores, capacidade, tamanho);
				if(idxTatuador == -1){
					printf("Nenhum tatuador encontrado! Ler novo registro? (S/N)\n>>> ");
					op = getc(stdin);
					fflush(stdin);
				
					if(op == 'S' || op == 's')
					continue;
				
					printf("\nOperacao cancelada.\n\n");
					return;
				} 
				
				printf("\nResultados da consulta:\n\n");
				imprimirTatuador(&tatuadores[idxTatuador]);
								
				break;
			}
			
			break;
		case 2: // Por nome
			
			// Laço da tela
			while(1){
				printf("Nome: ");
				fgets(nome,128,stdin);
				fflush(stdin);
				
				// Remove quebra de linha
				nome[strlen(nome) - 1] = 0;				
				
				// Assume que não encontramos nenhum tatuador
				encontrado = 0;
				
				printf("\nResultados da consulta:\n\n");
				
				// Laço de busca
				for(i = 0; i < *tamanho; i++){
					if(strcmp(tatuadores[i].nome, nome) == 0){
						encontrado = 1;
						imprimirTatuador(&tatuadores[i]);
						printf("\n");
					}	
				}
				
				if(encontrado == 0){
					printf("Nenhum tatuador encontrado! Ler novo nome? (S/N)\n>>> ");
					op = getc(stdin);
					fflush(stdin);
				
					if(op == 'S' || op == 's')
					continue;
				
					printf("\nOperacao cancelada.\n\n");
					return;
				} 
				break;
			}
			
			break;
		case 3: // Por anos de experiencia
			
			// Laço da tela
			while(1){
				printf("Anos de experiencia: ");
				scanf("%d", &anosExperiencia);
				
				// Assume que não encontramos nenhum tatuador
				encontrado = 0;
				
				printf("\nResultados da consulta:\n\n");
				
				// Laço de busca
				for(i = 0; i < *tamanho; i++){
					if(tatuadores[i].anosExperiencia == anosExperiencia){
						encontrado = 1;
						imprimirTatuador(&tatuadores[i]);
						printf("\n");
					}	
				}
				
				if(encontrado == 0){
					printf("Nenhum tatuador encontrado! Ler novo valor para anos de experiencia? (S/N)\n>>> ");
					op = getc(stdin);
					fflush(stdin);
				
					if(op == 'S' || op == 's')
					continue;
				
					printf("\nOperacao cancelada.\n\n");
					return;
				} 
				break;
			}
			
			break;
		case 4: // Por especialidade
			
			// Laço da tela
			while(1){
				printf("Especialidade: ");
				fgets(especialidade,64,stdin);
				fflush(stdin);
				
				// Remove quebra de linha
				especialidade[strlen(especialidade) - 1] = 0;				
				
				// Assume que não encontramos nenhum tatuador
				encontrado = 0;
				
				printf("\nResultados da consulta:\n\n");
				
				// Laço de busca
				for(i = 0; i < *tamanho; i++){
					if(strcmp(tatuadores[i].especialidade, especialidade) == 0){
						encontrado = 1;
						imprimirTatuador(&tatuadores[i]);
						printf("\n");
					}	
				}
				
				if(encontrado == 0){
					printf("Nenhum tatuador encontrado! Ler nova especialidade? (S/N)\n>>> ");
					op = getc(stdin);
					fflush(stdin);
				
					if(op == 'S' || op == 's')
					continue;
				
					printf("\nOperacao cancelada.\n\n");
					return;
				} 
				break;
			}
			
			break;
		case 5: // Voltar
			return;
		}
	}	
}

void removerTatuador(Tatuador *tatuadores, int *capTatuadores, int *tamTatuadores,
					 Sessao *sessoes, int *capSessoes, int *tamSessoes
					){
	int i, registroTatuador, idxTatuador, podeSerRemovido;
	char op;
	printf("[REMOVER TATUADOR]\n\n");
	
	// Validação do registro
	while(1){
		printf("Registro do Tatuador: ");
		scanf("%d", &registroTatuador);
		fflush(stdin);
		
		idxTatuador = buscarTatuador(registroTatuador, tatuadores, capTatuadores, tamTatuadores);
		if(idxTatuador == -1){
			printf("ERRO: numero de registro nao encontrado! Ler novo registro? (S/N)\n>>> ");
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's')
				continue;
			
			printf("\nOperacao cancelada.\n\n");
			return;
		}
		
		break;
	}
	
	// Imprime o tatuador encontrado
	printf("\nTatuador encontrado:\n");
	imprimirTatuador(&tatuadores[idxTatuador]);
	
	// Encontrado o tatuador, verifica se ele pode ser removido. Assumimos inicialmente que pode:
	podeSerRemovido = 1;
	
	// Percorre as sessões verificando se ele está em alguma
	for(i = 0; i < *tamSessoes; i++)
		if(sessoes[i].registroTatuador == registroTatuador){
			podeSerRemovido = 0;
			break;
		}
			
	// Se pode ser removido, tenta remover
	if(podeSerRemovido){
		printf("Deseja remover o tatuador do sistema? (S/N)\n>>> ");
			op = getc(stdin);
			fflush(stdin);
		
			// Se sim, remove tatuador
			if(op == 'S' || op == 's'){
				// Diminui quantidade de tatuadores
				*tamTatuadores -= 1;
				
				// Move tatuadores na lista
				for(i = idxTatuador; i < *tamTatuadores; i++)
					tatuadores[i] = tatuadores[i+1];
					
				printf("\nTatuador removido com sucesso!\n\n");
				return;
			}
			
			// Caso contrário
			printf("\nOperacao cancelada.\n\n");
			return;
	} 
	
	// Caso contrário, não pode ser removido:
	
	printf("\nO tatuador nao pode ser removido do sistema! \n\n");	
	
}

void listarTatuadores(Tatuador *tatuadores, int *capacidade, int *tamanho){
	int i;
	printf("[LISTAR TODOS OS TATUADORES]\n\n");
	
	if(*tamanho == 0){
		printf("Lista de tatuadores vazia...\n\n");
		return;
	}
	
	for(i = 0; i < *tamanho; i++){
		imprimirTatuador(&tatuadores[i]);
		printf("\n"); // Quebra de linha
	}	
}

void salvarTatuadores(Tatuador *tatuadores, int *capacidade, int *tamanho){
	// Tenta abrir arquivo
	FILE *pArquivo = fopen("tatuadores.bin", "wb");
	
	// Se o arquivo não pode ser aberto, imprime mensagem e encerra
	if(pArquivo == NULL){
		printf("ERRO: nao eh possivel escrever o arquivo 'tatuadores.bin'.\n\n");
		return;
	}
	
	// Tenta escrever o vetor no arquivo. Se não conseguir imprime mensagem e retorna
	if(fwrite(tatuadores, sizeof(Tatuador), *tamanho, pArquivo) != *tamanho){
		printf("ERRO: nao eh possivel escrever registro no arquivo 'tatuadores.bin'.\n\n");
		return;
	}
	
	// Se conseguir, imprime mensagem e fecha arquivo.
	printf("%d registros salvos no arquivo 'tatuadores.bin'...\n", *tamanho);
			
	fclose(pArquivo);
}

void realocarTatuadores(Tatuador *tatuadores, int *capacidade, int *tamanho){
	// Verifica se vetor está cheio
	if(*tamanho == *capacidade){
		// Neste caso, aloca mais memória
		tatuadores = (Tatuador*) realloc(tatuadores, (*capacidade + TAM_VET) * sizeof(Tatuador));
		
		// Verifica se a realocação foi feita com sucesso
		if (tatuadores == NULL) {
		    printf("ERRO: Nao foi possivel realocar memoria para vetor 'tatuadores'...\n\n");
			return;
		}
		
		// Caso a realocação tenha sido feita com sucesso, atualiza capacidade
		*capacidade += TAM_VET;			
	}
			
}

void imprimirTatuador(Tatuador *tatuador){
	printf("Registro: %d\n", tatuador->registro);
	printf("Nome: %s\n", tatuador->nome);
	printf("Anos de experiencia: %d\n", tatuador->anosExperiencia);
	printf("Especialidade: %s\n", tatuador->especialidade);
}

int buscarTatuador(int registro, Tatuador *tatuadores, int *capacidade, int *tamanho){
	int i;
	for(i = 0; i < *tamanho; i++)
		if(tatuadores[i].registro == registro)
			return i;
			
	return -1;	
}

void carregarClientes(Cliente *clientes, int *capacidade, int *tamanho){
	// Tenta abrir o arquivo clientes.bin
	FILE *pArquivo = fopen("clientes.bin", "rb");
	
	// Se o arquivo não existir, cria arquivo:
	if(pArquivo == NULL){
		printf("Criando arquivo 'clientes.bin'...\n\n");
		
		pArquivo = fopen("clientes.bin", "wb");
		
		// Verifica se criou corretamente
		if(pArquivo == NULL)
			printf("ERRO: Nao foi possivel criar o arquivo 'clientes.bin'...\n\n");
			
		fclose(pArquivo);
		
		return;
	}
	
	// Cria um ponteiro de cliente
	Cliente c;
	
	// Repete indefinidamente
	while (1) {
		// Se não for possivel ler, quebra laço
		if(fread(&c, sizeof(Cliente), 1, pArquivo) != 1)
			break;
		
		// Copia conteudo
		clientes[*tamanho] = c;
		
		// Incrementa tamanho
		*tamanho += 1;	
		
		// Verifica se é necessário realocar memória para vetor
		// realocarClientes(clientes, capacidade, tamanho);
    }
	
}
void cadastrarCliente(Cliente *clientes, int *capacidade, int *tamanho){
	// Cria um novo cliente
	Cliente cliente;
	int i;
	char op;
	
	printf("[CADASTRAR CLIENTE]\n\n");
	
	// Laço de validação do CPF
	while(1){
		// Lê registro
		printf("CPF: ");
		scanf("%lld", &cliente.cpf);
		fflush(stdin);
		
		// Laço de validação do CPF
		if(buscarCliente(cliente.cpf, clientes, capacidade, tamanho) != -1){
			printf("ERRO: numero de CPF ja cadastrado! Ler novo CPF? (S/N)\n>>> ");
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's')
				continue;
			
			printf("\nOperacao cancelada.\n\n");
			return;
		}
		
		break;
	}
	
	// Obtem nome
	printf("Nome: ");
	fgets(cliente.nome, 128, stdin);
	
	// Remove quebra de linha
	cliente.nome[strlen(cliente.nome) - 1] = 0;
	
	// Obtem idade
	printf("Idade: ");
	scanf("%d", &cliente.idade);
	fflush(stdin);
	
	// Obtem tipo de pele
	printf("Tipo de pele: ");
	fgets(cliente.tipoPele, 64, stdin);
	
	// Remove quebra de linha
	cliente.tipoPele[strlen(cliente.tipoPele) - 1] = 0;
	
	// Obtem numero de tatuagens
	printf("Numero de tatuagens: ");
	scanf("%d", &cliente.numeroTatuagens);
	fflush(stdin);
	
	// Imprime informações do cliente:
	printf("\nInformacoes do cliente: \n\n");
	
	imprimirCliente(&cliente);
	
	printf("\nDeseja cadastrar cliente? (S/N)\n>>> ");
	
	op = getc(stdin);
	fflush(stdin);
			
	if(op == 'S' || op == 's'){
		clientes[*tamanho] = cliente;
		*tamanho += 1;
		printf("\nCliente cadastrado com sucesso!\n\n");
		
		// Verifica se é necessário realocar memória para vetor
		realocarClientes(clientes, capacidade, tamanho);
		
		return;
	}
	
	// Encerra
	printf("\nOperacao cancelada.\n\n");
	return;
}

void alterarCliente(Cliente *clientes, int *capClientes, int *tamClientes,
					 Sessao *sessoes, int *capSessoes, int *tamSessoes
					){
	int i, idxCliente;
	long long int cpfCliente, novoCpf;
	int novaIdade, novoNumeroTatuagens;
	char op, novoNome[128], novoTipoPele[64];
	printf("[ALTERAR CLIENTE]\n\n");
	
	// Validação do CPF
	while(1){
		printf("CPF do cliente: ");
		scanf("%lld", &cpfCliente);
		fflush(stdin);
		
		idxCliente = buscarCliente(cpfCliente, clientes, capClientes, tamClientes);
		if(idxCliente == -1){
			printf("ERRO: numero de CPF nao encontrado! Ler novo CPF? (S/N)\n>>> ");
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's')
				continue;
			
			printf("\nOperacao cancelada.\n\n");
			return;
		}
		
		break;
	}
			
	while(1){
		// CPF encontrado, imprime informações do tatuador:		
		printf("\nCliente encontrado:\n");
		imprimirCliente(&clientes[idxCliente]);
		
		printf("\nQual campo deve ser alterado?\n\n");
	
		switch(menuCampoCliente()){
		case 1: // Alterar CPF
			
			// Validação do novo CPF
			while(1){
				printf("Novo CPF: ");
				scanf("%lld", &novoCpf);
				fflush(stdin);
				
				if(buscarCliente(novoCpf, clientes, capClientes, tamClientes) != -1){
					printf("ERRO: numero de CPF ja cadastrado! Ler novo CPF? (S/N)\n>>> ");
					op = getc(stdin);
					fflush(stdin);
				
					if(op == 'S' || op == 's')
					continue;
				
					printf("\nOperacao cancelada.\n\n");
					return;
				}
				
				break;
			}
			
			// Alteração do CPF			
			printf("\nDeseja alterar o CPF do cliente de [%lld] para [%lld]? (S/N)\n>>> ", clientes[idxCliente].cpf, novoCpf);
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's'){
				// Altera o CPF em todos as sessoes marcadas
				for(i = 0; i < *tamSessoes; i++)
					if(sessoes[i].cpfCliente == clientes[idxCliente].cpf)
						sessoes[i].cpfCliente = novoCpf;
				
				// Altera o CPF do cliente
				clientes[idxCliente].cpf = novoCpf;
				
				printf("\nCPF atualizado com sucesso!\n\n");
				
			} else {
				printf("\nOperacao cancelada.\n");
			}
					
			break;
		case 2: // Alterar Nome
			printf("Novo nome: ");
			fgets(novoNome, 128, stdin);
			
			// Remove quebra de linha
			novoNome[strlen(novoNome) - 1] = 0;
			
			// Alteração do nome			
			printf("\nDeseja alterar o nome do cliente de [%s] para [%s]? (S/N)\n>>> ",clientes[idxCliente].nome, novoNome);
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's'){
				// Altera o nome do tatuador
				strcpy(clientes[idxCliente].nome, novoNome);
				
				printf("\nNome atualizado com sucesso!\n\n");
				
			} else {
				printf("\nOperacao cancelada.\n");
			}
			
			break;
		case 3: // Alterar idade
			printf("Nova idade: ");
			scanf("%d", &novaIdade);
			fflush(stdin);
			
			// Alteração dos anos de experiencia			
			printf("\nDeseja alterar idade do cliente de [%d] para [%d]? (S/N)\n>>> ",clientes[idxCliente].idade, novaIdade);
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's'){
				// Altera o nome do cliente
				clientes[idxCliente].idade = novaIdade;
				
				printf("\nIdade atualizados com sucesso!\n\n");
				
			} else {
				printf("\nOperacao cancelada.\n");
			}
			
			break;
		case 4: // Alterar Tipo de Pele
			printf("Novo tipo de pele: ");
			fgets(novoTipoPele, 64, stdin);
			
			// Remove quebra de linha
			novoTipoPele[strlen(novoTipoPele) - 1] = 0;
			
			// Alteração de tipo de pele			
			printf("\nDeseja alterar o tipo de pele do cliente de [%s] para [%s]? (S/N)\n>>> ",clientes[idxCliente].tipoPele, novoTipoPele);
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's'){
				// Altera a especialidade do tatuador
				strcpy(clientes[idxCliente].tipoPele, novoTipoPele);
				
				printf("\nTipo de pele atualizada com sucesso!\n\n");
				
			} else {
				printf("\nOperacao cancelada.\n");
			}
			
			break;
		case 5: // Alterar numero de tatuagens
			printf("Novo numero de tatuagens: ");
			scanf("%d", &novoNumeroTatuagens);
			fflush(stdin);
			
			// Alteração dos anos de experiencia			
			printf("\nDeseja alterar o numero de tatuagens do cliente de [%d] para [%d]? (S/N)\n>>> ",clientes[idxCliente].numeroTatuagens, novoNumeroTatuagens);
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's'){
				// Altera o nome do cliente
				clientes[idxCliente].numeroTatuagens = novoNumeroTatuagens;
				
				printf("\nNumero de tatuagens atualizados com sucesso!\n\n");
				
			} else {
				printf("\nOperacao cancelada.\n");
			}
			
			break;
		case 6: // Voltar
			return;
		}
	}
	
}

void consultarCliente(Cliente *clientes, int *capacidade, int *tamanho){
	int i, registroCliente, idxCliente, encontrado;
	long long int cpf;
	int idade, numeroTatuagens;
	char op, nome[128], tipoPele[64];
	
	
	printf("[CONSULTAR CLIENTES]\n");
	
	while(1){
		
		printf("\nPor qual campo deve ser consultado?\n\n");
		
		switch(menuCampoCliente()){
		case 1: // Por CPF
			
			// Laço da tela
			while(1){
				printf("CPF: ");
				scanf("%lld", &cpf);
				fflush(stdin);
				
				idxCliente = buscarCliente(cpf, clientes, capacidade, tamanho);
				if(idxCliente == -1){
					printf("Nenhum cliente encontrado! Ler novo CPF? (S/N)\n>>> ");
					op = getc(stdin);
					fflush(stdin);
				
					if(op == 'S' || op == 's')
					continue;
				
					printf("\nOperacao cancelada.\n\n");
					return;
				} 
				
				printf("\nResultados da consulta:\n\n");
				imprimirCliente(&clientes[idxCliente]);
								
				break;
			}
			
			break;
		case 2: // Por nome
			
			// Laço da tela
			while(1){
				printf("Nome: ");
				fgets(nome,128,stdin);
				fflush(stdin);
				
				// Remove quebra de linha
				nome[strlen(nome) - 1] = 0;				
				
				// Assume que não encontramos nenhum cliente
				encontrado = 0;
				
				printf("\nResultados da consulta:\n\n");
				
				// Laço de busca
				for(i = 0; i < *tamanho; i++){
					if(strcmp(clientes[i].nome, nome) == 0){
						encontrado = 1;
						imprimirCliente(&clientes[i]);
						printf("\n");
					}	
				}
				
				if(encontrado == 0){
					printf("Nenhum cliente encontrado! Ler novo nome? (S/N)\n>>> ");
					op = getc(stdin);
					fflush(stdin);
				
					if(op == 'S' || op == 's')
					continue;
				
					printf("\nOperacao cancelada.\n\n");
					return;
				} 
				break;
			}
			
			break;
		case 3: // Por idade
			
			// Laço da tela
			while(1){
				printf("Idade: ");
				scanf("%d", &idade);
				
				// Assume que não encontramos nenhum cliente
				encontrado = 0;
				
				printf("\nResultados da consulta:\n\n");
				
				// Laço de busca
				for(i = 0; i < *tamanho; i++){
					if(clientes[i].idade == idade){
						encontrado = 1;
						imprimirCliente(&clientes[i]);
						printf("\n");
					}	
				}
				
				if(encontrado == 0){
					printf("Nenhum cliente encontrado! Ler novo valor para idade? (S/N)\n>>> ");
					op = getc(stdin);
					fflush(stdin);
				
					if(op == 'S' || op == 's')
					continue;
				
					printf("\nOperacao cancelada.\n\n");
					return;
				} 
				break;
			}
			
			break;
		case 4: // Por tipo de pele
			
			// Laço da tela
			while(1){
				printf("Tipo de pele: ");
				fgets(tipoPele,64,stdin);
				fflush(stdin);
				
				// Remove quebra de linha
				tipoPele[strlen(tipoPele) - 1] = 0;				
				
				// Assume que não encontramos nenhum cliente
				encontrado = 0;
				
				printf("\nResultados da consulta:\n\n");
				
				// Laço de busca
				for(i = 0; i < *tamanho; i++){
					if(strcmp(clientes[i].tipoPele, tipoPele) == 0){
						encontrado = 1;
						imprimirCliente(&clientes[i]);
						printf("\n");
					}	
				}
				
				if(encontrado == 0){
					printf("Nenhum cliente encontrado! Ler novo tipo de pele? (S/N)\n>>> ");
					op = getc(stdin);
					fflush(stdin);
				
					if(op == 'S' || op == 's')
					continue;
				
					printf("\nOperacao cancelada.\n\n");
					return;
				} 
				break;
			}
			
			break;
			
		case 5: // Por numero de tatuagens
			
			// Laço da tela
			while(1){
				printf("Numero de tatuagens: ");
				scanf("%d", &numeroTatuagens);
				
				// Assume que não encontramos nenhum cliente
				encontrado = 0;
				
				printf("\nResultados da consulta:\n\n");
				
				// Laço de busca
				for(i = 0; i < *tamanho; i++){
					if(clientes[i].numeroTatuagens == numeroTatuagens){
						encontrado = 1;
						imprimirCliente(&clientes[i]);
						printf("\n");
					}	
				}
				
				if(encontrado == 0){
					printf("Nenhum cliente encontrado! Ler novo numero de tatuagens? (S/N)\n>>> ");
					op = getc(stdin);
					fflush(stdin);
				
					if(op == 'S' || op == 's')
					continue;
				
					printf("\nOperacao cancelada.\n\n");
					return;
				} 
				break;
			}
			
			break;
			
		case 6: // Voltar
			return;
		}
		
	}
}

void removerCliente(Cliente *clientes, int *capClientes, int *tamClientes,
					 Sessao *sessoes, int *capSessoes, int *tamSessoes
					){
	long long int cpfCliente;
	int i, idxCliente, podeSerRemovido;
	char op;
	printf("[REMOVER CLIENTE]\n\n");
	
	// Validação do CPF
	while(1){
		printf("CPF do Cliente: ");
		scanf("%lld", &cpfCliente);
		fflush(stdin);
		
		idxCliente = buscarCliente(cpfCliente, clientes, capClientes, tamClientes);
		if(idxCliente == -1){
			printf("ERRO: numero de CPF nao encontrado! Ler novo CPF? (S/N)\n>>> ");
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's')
				continue;
			
			printf("\nOperacao cancelada.\n\n");
			return;
		}
		
		break;
	}
	
	// Imprime o cliente encontrado
	printf("\nCliente encontrado:\n");
	imprimirCliente(&clientes[idxCliente]);
	
	// Encontrado o cliente, verifica se ele pode ser removido. Assumimos inicialmente que pode:
	podeSerRemovido = 1;
	
	// Percorre as sessões verificando se ele está em alguma
	for(i = 0; i < *tamSessoes; i++)
		if(sessoes[i].cpfCliente == cpfCliente){
			podeSerRemovido = 0;
			break;
		}
			
	// Se pode ser removido, tenta remover
	if(podeSerRemovido){
		printf("Deseja remover o cliente do sistema? (S/N)\n>>> ");
			op = getc(stdin);
			fflush(stdin);
		
			// Se sim, remove cliente
			if(op == 'S' || op == 's'){
				// Diminui quantidade de clientes
				*tamClientes -= 1;
				
				// Move clientes na lista
				for(i = idxCliente; i < *tamClientes; i++)
					clientes[i] = clientes[i+1];
					
				printf("\nCliente removido com sucesso!\n\n");
				return;
			}
			
			// Caso contrário
			printf("\nOperacao cancelada.\n\n");
			return;
	} 
	
	// Caso contrário, não pode ser removido:
	
	printf("\nO cliente nao pode ser removido do sistema! \n\n");	
	
}

void listarClientes(Cliente *clientes, int *capacidade, int *tamanho){
	int i;
	printf("[LISTAR TODOS OS CLIENTES]\n\n");
	
	if(*tamanho == 0){
		printf("Lista de cliente vazia...\n\n");
		return;
	}
	
	for(i = 0; i < *tamanho; i++){
		imprimirCliente(&clientes[i]);
		printf("\n"); // Quebra de linha
	}	
}

void realocarClientes(Cliente *clientes, int *capacidade, int *tamanho){
	// Verifica se vetor está cheio
	if(*tamanho == *capacidade){
		// Neste caso, aloca mais memória
		clientes = (Cliente*) realloc(clientes, (*capacidade + TAM_VET) * sizeof(Cliente));
		
		// Verifica se a realocação foi feita com sucesso
		if (clientes == NULL) {
		    printf("ERRO: Nao foi possivel realocar memoria para vetor 'clientes'...\n\n");
			return;
		}
		
		// Caso a realocação tenha sido feita com sucesso, atualiza capacidade
		*capacidade += TAM_VET;			
	}
}

void imprimirCliente(Cliente *cliente){
	printf("CPF: %lld\n", cliente->cpf);
	printf("Nome: %s\n", cliente->nome);
	printf("Idade: %d\n", cliente->idade);
	printf("Tipo de pele: %s\n", cliente->tipoPele);
	printf("Numero de tatuagens: %d\n", cliente->numeroTatuagens);
}

int buscarCliente(long long int cpf, Cliente *clientes, int *capacidade, int *tamanho){
	int i;
	for(i = 0; i < *tamanho; i++)
		if(clientes[i].cpf == cpf)
			return i;
			
	return -1;	
}

void salvarClientes(Cliente *clientes, int *capacidade, int *tamanho){
	// Tenta abrir arquivo
	FILE *pArquivo = fopen("clientes.bin", "wb");
	
	// Se o arquivo não pode ser aberto, imprime mensagem e encerra
	if(pArquivo == NULL){
		printf("ERRO: nao eh possivel escrever o arquivo 'clientes.bin'.\n\n");
		return;
	}
	
	// Tenta escrever o vetor no arquivo. Se não conseguir imprime mensagem e retorna
	if(fwrite(clientes, sizeof(Cliente), *tamanho, pArquivo) != *tamanho){
		printf("ERRO: nao eh possivel escrever registro no arquivo 'clientes.bin'.\n\n");
		return;
	}
	
	// Se conseguir, imprime mensagem e fecha arquivo.
	printf("%d registros salvos no arquivo 'clientes.bin'...\n", *tamanho);
			
	fclose(pArquivo);
}

void carregarSessoes(Sessao *sessoes, int *capacidade, int *tamanho){
	// Tenta abrir o arquivo sessoes.bin
	FILE *pArquivo = fopen("sessoes.bin", "rb");
	
	// Se o arquivo não existir, cria arquivo:
	if(pArquivo == NULL){
		printf("Criando arquivo 'sessoes.bin'...\n\n");
		
		pArquivo = fopen("sessoes.bin", "wb");
		
		// Verifica se criou corretamente
		if(pArquivo == NULL)
			printf("ERRO: Nao foi possivel criar o arquivo 'sessoes.bin'...\n\n");
			
		fclose(pArquivo);
		
		return;
	}
	
	// Cria um ponteiro de sessao
	Sessao s;
	
	// Repete indefinidamente
	while (1) {
		// Se não for possivel ler, quebra laço
		if(fread(&s, sizeof(Sessao), 1, pArquivo) != 1)
			break;
		
		// Copia conteudo
		sessoes[*tamanho] = s;
		
		// Incrementa tamanho
		*tamanho += 1;	
		
		// Verifica se é necessário realocar memória para vetor
		// realocarClientes(clientes, capacidade, tamanho);
    }
	
}

void cadastrarSessao(Sessao *sessoes, int *capSessoes, int *tamSessoes,
					 Tatuador *tatuadores, int *capTatuadores, int *tamTatuadores,
					 Cliente *clientes, int *capClientes, int *tamClientes
					){
	// Cria uma nova sessao
	Sessao sessao;
	int i, idIgual = 0, tatuadorEncontrado = 0, clienteEncontrado = 0;
	int registroTatuador, idxTatuador, idxCliente;
	long long int cpfCliente;
	double valor;
	char op;
	
	printf("[CADASTRAR SESSAO]\n\n");
	
	// Laço de validação do ID da tatuagem
	while(1){
		// Lê ID da tatuagem
		printf("ID da Tatuagem: ");
		scanf("%lld", &sessao.idTatuagem);
		fflush(stdin);
		
		// Laço de validação do ID da tatuagem
		if(buscarSessao(sessao.idTatuagem, sessoes, capSessoes, tamSessoes) != -1){
			printf("ERRO: ID da tatuagem ja cadastrado! Ler novo ID? (S/N)\n>>> ");
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's')
				continue;
			
			printf("\nOperacao cancelada.\n\n");
			return;
		}
		
		break;
	}
	
	// Laço de validação para a data da sessão
	while(1) {
		// Obtem data
		printf("[Data da sessao]\n");
		
		printf("Dia: ");
		scanf("%d", &sessao.data.dia);
		
		printf("Mes: ");
		scanf("%d", &sessao.data.mes);
		
		printf("Ano: ");
		scanf("%d", &sessao.data.ano);
		fflush(stdin);
		
		// Se a data é valida, quebra laço
		if(validarData(&sessao.data))
			break;
		
		// Caso contrário, verifica se deve continuar a leitura de uma nova data
		printf("ERRO: Data invalida! Ler nova data? (S/N)\n>>> ");
		op = getc(stdin);
		fflush(stdin);
		
		if(op == 'S' || op == 's')
			continue;
		
		printf("\nOperacao cancelada.\n\n");
		return;
				
	}
	
	// Laço de validação do tatuador
	while(1){
		printf("Registro do tatuador: ");
		scanf("%d", &registroTatuador);
		fflush(stdin);
		
		// Laço de validação do registro do tatuador
		idxTatuador = buscarTatuador(registroTatuador, tatuadores, capTatuadores, tamTatuadores);
		if(idxTatuador == -1){
			printf("ERRO: tatuador nao encontrado! Ler novo registro do tatuador? (S/N)\n>>> ");
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's')
				continue;
			
			printf("\nOperacao cancelada.\n\n");
			return;
		}
		
		sessao.registroTatuador = registroTatuador;
		break;
	}
	
	// Laço de validação do cliente
	while(1){
		printf("CPF do cliente: ");
		scanf("%lld", &cpfCliente);
		fflush(stdin);
		
		// Laço de validação do registro do cliente
		idxCliente = buscarCliente(cpfCliente, clientes, capClientes, tamClientes);
		if(idxCliente == -1){
			printf("ERRO: cliente nao encontrado! Ler novo CPF do cliente? (S/N)\n>>> ");
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's')
				continue;
			
			printf("\nOperacao cancelada.\n\n");
			return;
		}
		
		sessao.cpfCliente = cpfCliente;
		break;
	}
	
	while(1){
		printf("Valor da sessao: R$ ");
		scanf("%lf", &valor);	
		fflush(stdin);
		
		if(valor < 0){
			printf("ERRO: valor nao pode ser negativo! Ler novo valor? (S/N)\n>>> ");
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's')
				continue;
			
			printf("\nOperacao cancelada.\n\n");
			return;
		}
		
		sessao.valor = (int) (100*valor + 0.05);
		break;	
	}
	
	// Imprime informações do sessão:
	printf("\nInformacoes da sessao: \n\n");
	
	imprimirSessao(&sessao, &tatuadores[idxTatuador], &clientes[idxCliente]);
	
	printf("\nDeseja marcar sessao? (S/N)\n>>> ");
	
	op = getc(stdin);
	fflush(stdin);
			
	if(op == 'S' || op == 's'){
		sessoes[*tamSessoes] = sessao;
		*tamSessoes += 1;
		printf("\nSessao marcada com sucesso!\n\n");
		
		// Verifica se é necessário realocar memória para vetor
		realocarSessoes(sessoes, capSessoes, tamSessoes);
		
		return;
	}
	
	// Encerra
	printf("\nOperacao cancelada.\n\n");
	return;
	
}

void alterarSessao(Sessao *sessoes, int *capSessoes, int *tamSessoes,
				   Tatuador *tatuadores, int *capTatuadores, int *tamTatuadores,
				   Cliente *clientes, int *capClientes, int *tamClientes
				  ){
	int idTatuagem, idxSessao, idxTatuador, idxCliente, novoIdTatuagem, novoValor, idxNovoTatuador, idxNovoCliente;
	Data novaData;
	long long int novoCpfCliente;
	int novoRegistroTatuador;
	char op;
	double valorDouble;
	printf("[ALTERAR SESSAO]\n\n");
	
	// Validação do ID da tatuagem,
	while(1){
		printf("ID da tatuagem: ");
		scanf("%d", &idTatuagem);
		fflush(stdin);
		
		idxSessao = buscarSessao(idTatuagem, sessoes, capSessoes, tamSessoes);
		if(idxSessao == -1){
			printf("ERRO: ID da tatuagem nao encontrado! Ler novo ID? (S/N)\n>>> ");
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's')
				continue;
			
			printf("\nOperacao cancelada.\n\n");
			return;
		}
		
		break;
	}
			
	while(1){
		// ID da tatuagem encontrado, imprime informações da sessao:		
		printf("\nSessao encontrada:\n");
		
		// Busca tatuador e cliente da sessao
		idxTatuador = buscarTatuador(sessoes[idxSessao].registroTatuador, tatuadores, capTatuadores, tamTatuadores);
		idxCliente = buscarCliente(sessoes[idxSessao].cpfCliente, clientes, capClientes, tamClientes);
		
		imprimirSessao(&sessoes[idxSessao],&tatuadores[idxTatuador],&clientes[idxCliente]);
		
		printf("\nQual campo deve ser alterado?\n\n");
	
		switch(menuCampoSessao()){
		case 1: // Alterar ID da tatuagem
			
			// Validação do novo ID da tatuagem
			while(1){
				printf("Novo ID da tatuagem: ");
				scanf("%d", &novoIdTatuagem);
				fflush(stdin);
				
				if(buscarSessao(novoIdTatuagem, sessoes, capSessoes, tamSessoes) != -1){
					printf("ERRO: numero de ID da tatuagem ja cadastrado! Ler novo ID? (S/N)\n>>> ");
					op = getc(stdin);
					fflush(stdin);
				
					if(op == 'S' || op == 's')
					continue;
				
					printf("\nOperacao cancelada.\n\n");
					return;
				}
				
				break;
			}
			
			// Alteração do ID da tatuagem			
			printf("\nDeseja alterar o ID da tatuagem de [%d] para [%d]? (S/N)\n>>> ", sessoes[idxSessao].idTatuagem, novoIdTatuagem);
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's'){
				// Altera o ID da tatuagem
				sessoes[idxSessao].idTatuagem = novoIdTatuagem;
				
				printf("\nID da tatuagem atualizado com sucesso!\n\n");
				
			} else {
				printf("\nOperacao cancelada.\n");
			}
					
			break;
		case 2: // Alterar data
			
			// Validação da data
			while(1){
				printf("Nova data\n");
				printf("Dia: ");
				scanf("%d", &novaData.dia);
				fflush(stdin);
				
				printf("Mes: ");
				scanf("%d", &novaData.mes);
				fflush(stdin);
				
				printf("Ano: ");
				scanf("%d", &novaData.ano);
				fflush(stdin);
				
				if(!validarData(&novaData)){
					printf("ERRO: dada invalida! Ler nova data? (S/N)\n>>> ");
					op = getc(stdin);
					fflush(stdin);
				
					if(op == 'S' || op == 's')
					continue;
				
					printf("\nOperacao cancelada.\n\n");
					return;
				}
				
				break;
			}
			
			// Alteração da data	
			printf("\nDeseja alterar a data da tatuagem de [%02d/%02d/%04d] para [%02d/%02d/%04d]? (S/N)\n>>> ", sessoes[idxSessao].data.dia, sessoes[idxSessao].data.mes, sessoes[idxSessao].data.ano, novaData.dia, novaData.mes, novaData.ano);
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's'){
				// Altera a data da tatuagem
				sessoes[idxSessao].data = novaData;
				
				printf("\nData da tatuagem atualizado com sucesso!\n\n");
				
			} else {
				printf("\nOperacao cancelada.\n");
			}
			
			break;
		case 3: // Alterar Tatuador
		
			// Validação do tatuador
			while(1){
				printf("Registro do novo tatuador: ");
				scanf("%d", &novoRegistroTatuador);
				fflush(stdin);
				
				idxNovoTatuador = buscarTatuador(novoRegistroTatuador, tatuadores, capTatuadores, tamTatuadores);
				if(idxNovoTatuador == -1){
					printf("ERRO: registro de tatuador nao encontrado! Ler novo registro? (S/N)\n>>> ");
					op = getc(stdin);
					fflush(stdin);
				
					if(op == 'S' || op == 's')
					continue;
				
					printf("\nOperacao cancelada.\n\n");
					return;
				}
				
				break;
			}
			
			// Alteração do registro
			printf("\nDeseja alterar o tatuador de [%d %s] para [%d %s]? (S/N)\n>>> ", tatuadores[idxTatuador].registro, tatuadores[idxTatuador].nome, tatuadores[idxNovoTatuador].registro, tatuadores[idxNovoTatuador].nome);
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's'){
				// Altera o registro do tutuador
				sessoes[idxSessao].registroTatuador = novoRegistroTatuador;
				
				printf("\nTatuador atualizado com sucesso!\n\n");
				
			} else {
				printf("\nOperacao cancelada.\n");
			}
			
			break;
		case 4: // Alterar Cliente			
		
			// Validação do cliente
			while(1){
				printf("CPF do novo cliente: ");
				scanf("%lld", &novoCpfCliente);
				fflush(stdin);
				
				idxNovoCliente = buscarCliente(novoCpfCliente, clientes, capClientes, tamClientes);
				if(idxNovoCliente == -1){
					printf("ERRO: CPF do cliente nao encontrado! Ler novo CPF? (S/N)\n>>> ");
					op = getc(stdin);
					fflush(stdin);
				
					if(op == 'S' || op == 's')
					continue;
				
					printf("\nOperacao cancelada.\n\n");
					return;
				}
				
				break;
			}
			
			// Alteração do CPF
			printf("\nDeseja alterar o cliente de [%lld %s] para [%lld %s]? (S/N)\n>>> ", clientes[idxCliente].cpf, clientes[idxCliente].nome, clientes[idxNovoCliente].cpf, clientes[idxNovoCliente].nome);
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's'){
				// Altera o CPF do cliente
				sessoes[idxSessao].cpfCliente = novoCpfCliente;
				
				printf("\nCliente atualizado com sucesso!\n\n");
				
			} else {
				printf("\nOperacao cancelada.\n");
			}
		
			break;
		case 5: // Alterar valor
		
			printf("Novo Valor: R$ ");
			scanf("%lf", &valorDouble);
			fflush(stdin);
			
			// Converte para inteiro
			novoValor = (int)(valorDouble*100 + 0.5);
				
			// Alteração do ID da tatuagem			
			printf("\nDeseja alterar o valor da tatuagem de [R$ %d,%02d] para [R$ %d,%02d]? (S/N)\n>>> ", sessoes[idxSessao].valor / 100, sessoes[idxSessao].valor % 100, novoValor / 100, novoValor % 100);
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's'){
				// Altera o ID da tatuagem
				sessoes[idxSessao].valor = novoValor;
				
				printf("\nValor da tatuagem atualizado com sucesso!\n\n");
				
			} else {
				printf("\nOperacao cancelada.\n");
			}
					
			break;
		case 6: // Voltar
			return;
		}
	}
	
}

void removerSessao(Sessao *sessoes, int *capSessoes, int *tamSessoes,
				   Tatuador *tatuadores, int *capTatuadores, int *tamTatuadores,
				   Cliente *clientes, int *capClientes, int *tamClientes
				  ){
	
	int i, idTatuagem, idxSessao, idxTatuador, idxCliente;
	char op;
	printf("[REMOVER SESSAO]\n\n");
	
	// Validação do ID da tatuagem,
	while(1){
		printf("ID da tatuagem: ");
		scanf("%d", &idTatuagem);
		fflush(stdin);
		
		idxSessao = buscarSessao(idTatuagem, sessoes, capSessoes, tamSessoes);
		if(idxSessao == -1){
			printf("ERRO: ID da tatuagem nao encontrado! Ler novo ID? (S/N)\n>>> ");
			op = getc(stdin);
			fflush(stdin);
			
			if(op == 'S' || op == 's')
				continue;
			
			printf("\nOperacao cancelada.\n\n");
			return;
		}
		
		break;
	}
	
	// Busca tatuador e cliente da sessao
	idxTatuador = buscarTatuador(sessoes[idxSessao].registroTatuador, tatuadores, capTatuadores, tamTatuadores);
	idxCliente = buscarCliente(sessoes[idxSessao].cpfCliente, clientes, capClientes, tamClientes);
	
	// Imprime a sessão encontrada
	printf("\nSessao encontrada:\n");
	imprimirSessao(&sessoes[idxSessao], &tatuadores[idxTatuador], &clientes[idxCliente]);
	
	printf("Deseja remover o sessao do sistema? (S/N)\n>>> ");
	op = getc(stdin);
	fflush(stdin);

	// Se sim, remove sessao
	if(op == 'S' || op == 's'){
		// Diminui quantidade de sessoes
		*tamSessoes -= 1;
		
		// Move sessoes na lista
		for(i = idxSessao; i < *tamSessoes; i++)
			sessoes[i] = sessoes[i+1];
			
		printf("\nSessao removida com sucesso!\n\n");
		return;
	}
	
	// Caso contrário
	printf("\nOperacao cancelada.\n\n");
	return;
}

void mostrarSessoes(Sessao *sessoes, int *capSessoes, int *tamSessoes,
					Tatuador *tatuadores, int *capTatuadores, int *tamTatuadores,
					Cliente *clientes, int *capClientes, int *tamClientes
				   ){
	int i;
	printf("[MOSTRAR TODAS AS SESSOES]\n\n");
	
	if(*tamSessoes == 0){
		printf("Lista de sessoes vazia...\n\n");
		return;
	}
	
	int idxTatuador, idxCliente;
	for(i = 0; i < *tamSessoes; i++){
		// Obtém tatuador e cliente da sessão
		idxTatuador = buscarTatuador(sessoes[i].registroTatuador, tatuadores, capTatuadores, tamTatuadores);
		idxCliente = buscarCliente(sessoes[i].cpfCliente, clientes, capClientes, tamClientes);
		
		imprimirSessao(&sessoes[i], &tatuadores[idxTatuador], &clientes[idxCliente]);
		printf("\n"); // Quebra de linha
	}	
	
}

void gerarRelatorioSessoes(Sessao *sessoes, int *capSessoes, int *tamSessoes,
						   Tatuador *tatuadores, int *capTatuadores, int *tamTatuadores,
						   Cliente *clientes, int *capClientes, int *tamClientes
						  ){
	Data dataInicial;
	int i, idxTatuador, idxCliente;
	char op;
	
	printf("[GERAR RELATORIO DE SESSOES]\n\n");
	// Valida a data inicial da sessão
	while(1) {
		// Obtem data
		printf("[Data inicial]\n");
		
		printf("Dia: ");
		scanf("%d", &dataInicial.dia);
		
		printf("Mes: ");
		scanf("%d", &dataInicial.mes);
		
		printf("Ano: ");
		scanf("%d", &dataInicial.ano);
		fflush(stdin);
		
		// Se a data é valida, quebra laço
		if(validarData(&dataInicial))
			break;
		
		// Caso contrário, verifica se deve continuar a leitura de uma nova data
		printf("ERRO: Data inicial invalida! Ler nova data? (S/N)\n>>> ");
		op = getc(stdin);
		fflush(stdin);
		
		if(op == 'S' || op == 's')
			continue;
		
		printf("\nOperacao cancelada.\n\n");
		return;
	}
	
	// Abre aquivo de texto:
	FILE *pArquivo = fopen("relatorio.txt", "w");
	
	if(pArquivo == NULL){
		printf("\nERRO: nao eh possivel criar arquivo 'relatiorio.txt'...\n\n");
		return;
	}
	
	for(i = 0; i < *tamSessoes; i++){
		// Se a data da sessao é posterior à data inicial
		if(compararDatas(&dataInicial, &sessoes[i].data) <= 0){
			// Imprimimos no arquivo:
			fprintf(pArquivo,"ID da Tatuagem: %d\n", sessoes[i].idTatuagem);
			fprintf(pArquivo,"Data da Sessão: %02d/%02d/%04d\n", sessoes[i].data.dia, sessoes[i].data.mes, sessoes[i].data.ano);
			fprintf(pArquivo,"Valor: R$ %d,%02d\n", sessoes[i].valor / 100, sessoes[i].valor % 100);
			
			// Encontra cliente e tatuador
			idxTatuador = buscarTatuador(sessoes[i].registroTatuador, tatuadores, capTatuadores, tamTatuadores);
			idxCliente = buscarCliente(sessoes[i].cpfCliente, clientes, capClientes, tamClientes);
			
			fprintf(pArquivo,"Nome do Cliente: %s\n", clientes[idxCliente].nome);
			fprintf(pArquivo,"CPF do Cliente: %lld\n", clientes[idxCliente].cpf);
			fprintf(pArquivo,"Idade do Cliente: %d\n", clientes[idxCliente].idade);
			
			fprintf(pArquivo,"Nome do Tatuador: %s\n", tatuadores[idxTatuador].nome);
			fprintf(pArquivo,"Registro do Tatuador: %d\n", tatuadores[idxTatuador].registro);
			fprintf(pArquivo,"Especialidade do Tatuador: %s\n\n", tatuadores[idxTatuador].especialidade);
		}
	}
	
	printf("\nArquivo de relatorio 'relatorio.txt' criado com sucesso!\n\n");
	
	fclose(pArquivo);	
}

void realocarSessoes(Sessao *sessoes, int *capacidade, int *tamanho){
	// Verifica se vetor está cheio
	if(*tamanho == *capacidade){
		// Neste caso, aloca mais memória
		sessoes = (Sessao*) realloc(sessoes, (*capacidade + TAM_VET) * sizeof(Sessao));
		
		// Verifica se a realocação foi feita com sucesso
		if (sessoes == NULL) {
		    printf("ERRO: Nao foi possivel realocar memoria para vetor 'sessoes'...\n\n");
			return;
		}
		
		// Caso a realocação tenha sido feita com sucesso, atualiza capacidade
		*capacidade += TAM_VET;			
	}
}

void salvarSessoes(Sessao *sessoes, int *capacidade, int *tamanho){
	// Tenta abrir arquivo
	FILE *pArquivo = fopen("sessoes.bin", "wb");
	
	// Se o arquivo não pode ser aberto, imprime mensagem e encerra
	if(pArquivo == NULL){
		printf("ERRO: nao eh possivel escrever o arquivo 'sessoes.bin'.\n\n");
		return;
	}
	
	// Tenta escrever o vetor no arquivo. Se não conseguir imprime mensagem e retorna
	if(fwrite(sessoes, sizeof(Sessao), *tamanho, pArquivo) != *tamanho){
		printf("ERRO: nao eh possivel escrever registro no arquivo 'sessoes.bin'.\n\n");
		return;
	}
	
	// Se conseguir, imprime mensagem e fecha arquivo.
	printf("%d registros salvos no arquivo 'sessoes.bin'...\n", *tamanho);
			
	fclose(pArquivo);
}

int buscarSessao(int idTatuagem, Sessao *sessoes, int *capacidade, int *tamanho){
	int i;
	for(i = 0; i < *tamanho; i++)
		if(sessoes[i].idTatuagem == idTatuagem)
			return i;
			
	return -1;	
}

void imprimirSessao(Sessao *sessao, Tatuador *tatuador, Cliente *cliente){
	printf("ID da tatuagem: %d\n", sessao->idTatuagem);
	printf("Data da sessao: %02d/%02d/%04d\n", sessao->data.dia, sessao->data.mes, sessao->data.ano);
	printf("Tatuador: %s\n", tatuador->nome);
	printf("Cliente: %s\n", cliente->nome);
	printf("Valor: R$ %d,%02d\n", sessao->valor / 100, sessao->valor % 100);
}

// Funções auxiliares
int validarData(Data* data){
	// Variáveis auxiliares para simpificar o código abaixo
	int dia = data->dia;
	int mes = data->mes;
	int ano = data->ano;
	
	// Não pode marcar sessao no passado nem num futuro distante
	if(ano < 2024 || ano > 2030)
		return 0;
	
	// Não pode marcar data em um dia inexistente
	if(dia < 1 || dia > 31)
		return 0;
	
	// Verifica os dias 31 em meses que tem 30 dias
	if (dia == 31 && (mes == 2 || mes == 4 || mes == 6 || mes == 9 || mes == 11))
		return 0;
	
	// Verifica o dia 30 no mês de fevereiro
	if (dia == 30 && mes == 2)
		return 0;
		
	// Verifica o dia 29 em fevereiro em anos não bissextos
	if (dia == 29 && mes == 2 && !((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)))
		return 0;
		
	// Se passou em todos os testes, a data é valida
	return 1;
}

int compararDatas(Data* data1, Data* data2){
	long long int data1_long = data1->dia + data1->mes * 16 + data1->ano * 512;
	long long int data2_long = data2->dia + data2->mes * 16 + data2->ano * 512;
	
	if(data1_long < data2_long)
		return -1;
	
	if(data1_long > data2_long)
		return 1;
		
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define ARQUIVO "departamentos.txt"


typedef struct {
    int numero;
    char nome[50];
    char cpf_gerente[15];
} Departamento;

// funcoes p verificacoes (gerente, numero/chave, nome do dpto)

int gerente_existe(const char *cpf) {
    FILE *fp = fopen("departamentos.txt", "r");
    if (!fp) return 0; // caso o arq n exista

    char linha[200], cpf_existente[15];
    int num;
    char nome[50];

    while (fgets(linha, sizeof(linha), fp)) {
        sscanf(linha, "%d;%[^;];%s", &num, nome, cpf_existente);
        if (strcmp(cpf_existente, cpf) == 0) {
            fclose(fp);
            return 1; // gerente ja existe, erro
        }
    }
    fclose(fp);
    return 0;
}

int numero_departamento_existe(int numero) {
    FILE *fp = fopen("departamentos.txt", "r");
    if (!fp) return 0;

    char linha[200];
    int num;
    char nome[50], cpf[15];

    while (fgets(linha, sizeof(linha), fp)) {
        sscanf(linha, "%d;%[^;];%s", &num, nome, cpf);
        if (num == numero) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int nome_departamento_existe(const char *nome, int ignorar_numero) {
    FILE *fp = fopen("departamentos.txt", "r");
    if (!fp) return 0;

    char linha[200], nome_lido[50], cpf[15];
    int numero;

    while (fgets(linha, sizeof(linha), fp)) {
        sscanf(linha, "%d;%[^;];%s", &numero, nome_lido, cpf);
        if (strcmp(nome_lido, nome) == 0 && numero != ignorar_numero) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// CRUD

void criar_departamento() {
    Departamento d;

    printf("Número do departamento: ");
    scanf("%d", &d.numero);

    if (numero_departamento_existe(d.numero)) {
        printf("Número de departamento já existe!\n");
        return;
    }

    printf("Nome do departamento: ");
    getchar(); fgets(d.nome, sizeof(d.nome), stdin);
    d.nome[strcspn(d.nome, "\n")] = '\0';

    if (nome_departamento_existe(d.nome, -1)) {
        printf("Nome de departamento já existe!\n");
        return;
    }    

    printf("CPF do gerente: ");
    scanf("%s", d.cpf_gerente);

    if (gerente_existe(d.cpf_gerente)) {
        printf("Esse funcionário já é gerente de outro departamento.\n");
        return;
    }

    FILE *fp = fopen("departamentos.txt", "a");
    if (!fp) {
        printf("Erro ao abrir arquivo de departamentos!\n");
        return;
    }

    fprintf(fp, "%d;%s;%s\n", d.numero, d.nome, d.cpf_gerente);
    fclose(fp);
    printf("Departamento criado com sucesso.\n");
}

void listar_departamentos() {
    FILE *fp = fopen("departamentos.txt", "r");
    if (!fp) {
        printf("Arquivo não encontrado.\n");
        return;
    }

    Departamento d;
    char linha[200];

    printf("\n--- Departamentos ---\n");
    while (fgets(linha, sizeof(linha), fp)) {
        sscanf(linha, "%d;%[^;];%s", &d.numero, d.nome, d.cpf_gerente);
        printf("Número: %d | Nome: %s | Gerente (CPF): %s\n",
               d.numero, d.nome, d.cpf_gerente);
    }

    fclose(fp);
}

void atualizar_departamento() {
    int numero_original;
    printf("Digite o número do departamento a ser atualizado: ");
    scanf("%d", &numero_original);

    FILE *fp = fopen("departamentos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    char linha[200];
    Departamento d;
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), fp)) {
        sscanf(linha, "%d;%[^;];%s", &d.numero, d.nome, d.cpf_gerente);

        if (d.numero == numero_original) {
            encontrado = 1;

            Departamento novo;

            printf("Novo número do departamento: ");
            scanf("%d", &novo.numero);
            if (novo.numero != numero_original && numero_departamento_existe(novo.numero)) {
                printf("Número de departamento já existe!\n");
                fputs(linha, temp); // Mantém o antigo
                continue;
            }

            printf("Novo nome do departamento: ");
            getchar(); fgets(novo.nome, sizeof(novo.nome), stdin);
            novo.nome[strcspn(novo.nome, "\n")] = '\0';

            if (nome_departamento_existe(novo.nome, numero_original)) {
                printf("Nome de departamento já existe!\n");
                fputs(linha, temp); // Mantém o antigo
                continue;
            }            

            printf("Novo CPF do gerente: ");
            scanf("%s", novo.cpf_gerente);
            if (strcmp(novo.cpf_gerente, d.cpf_gerente) != 0 &&
                gerente_existe(novo.cpf_gerente)) {
                printf("Esse funcionário já gerencia outro departamento!\n");
                fputs(linha, temp); // Mantém o antigo
                continue;
            }

            fprintf(temp, "%d;%s;%s\n", novo.numero, novo.nome, novo.cpf_gerente);
            printf("Departamento atualizado com sucesso.\n");

        } else {
            fputs(linha, temp); // Copia os departamentos que não serão atualizados
        }
    }

    fclose(fp);
    fclose(temp);

    remove("departamentos.txt");
    rename("temp.txt", "departamentos.txt");

    if (!encontrado) {
        printf("Departamento não encontrado.\n");
    }
}

void deletar_departamento() {
    int numero;
    printf("Digite o número do departamento a ser removido: ");
    scanf("%d", &numero);

    FILE *fp = fopen("departamentos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    char linha[200];
    int num;
    char nome[50], cpf[15];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), fp)) {
        sscanf(linha, "%d;%[^;];%s", &num, nome, cpf);
        if (num != numero) {
            fputs(linha, temp);
        } else {
            encontrado = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("departamentos.txt");
    rename("temp.txt", "departamentos.txt");

    if (encontrado)
        printf("Departamento removido com sucesso.\n");
    else
        printf("Departamento não encontrado.\n");
}

void main() {

    int opcao = -1;
    
    while (opcao != 0) {
        
        printf("\n--- Menu ---\n");
        printf("1. Criar departamento\n");
        printf("2. Listar departamentos\n");
        printf("3. Atualizar departamento\n");
        printf("4. Deletar departamento\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        
        scanf("%d", &opcao);

        if (opcao < 0 || opcao > 4) {
            printf("Opção inválida! Tente novamente.\n");
            continue;
        }

        if (opcao == 0) break; // Sair do loop se a opção for 0

        // Chama a função correspondente à opção escolhida
        switch(opcao) {
            case 1: criar_departamento(); break;
            case 2: listar_departamentos(); break;
            case 3: atualizar_departamento(); break;
            case 4: deletar_departamento(); break;
        }
    }
    printf("Saindo do programa...\n");
}
    
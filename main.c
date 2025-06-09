#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    char nome[50];
    char sexo[2];
    char conciencia[50];
    char Sinais_Vitais[50];
    char descricao_da_lesao[100];
    int idade[2];
    char data[50];
    char hora[10];
    char local[50];
    char tipo_acidente[50];
    char observacoes[200];
}Pessoa;
Pessoa pessoas[50] = {0};


int main(){
    int opc = 0,pacientes = 0,i = 0;
    printf("Bem Vindo Ao Sistema Ambulancia Escolha a Opcao\n");
    do{
        printf("[0]Registrar Acidente [1]Editar Acidente [2]Sair\n");
        scanf("%d",&opc);
        getchar();
        switch (opc)
        {
        case 0:
            printf("\nQuantos Pacientes Voce Quer Registrar?\n");
            scanf("%d",&pacientes);
            getchar();
            for(i = 0; i < pacientes; i++){
                char nomeArquivo[100];
                snprintf(nomeArquivo, sizeof(nomeArquivo), "Paciente_%d.txt", i+1);

                FILE *arquivo = fopen(nomeArquivo, "w");
                if (arquivo == NULL) {
                    printf("Erro ao criar o arquivo %s\n", nomeArquivo);
                    continue;
                }

                printf("Nome Do Paciente: ");

                fgets(pessoas[i].nome, sizeof(pessoas[i].nome), stdin);
                pessoas[i].nome[strcspn(pessoas[i].nome, "\n")] = 0;

                printf("Sexo do Paciente: ");
                getchar();

                fgets(pessoas[i].sexo, sizeof(pessoas[i].sexo), stdin);
                pessoas[i].sexo[strcspn(pessoas[i].sexo, "\n")] = 0;

                printf("Idade Do Paciente: ");

                fgets(pessoas[i].idade, sizeof(pessoas[i].idade), stdin);
                pessoas[i].idade[strcspn(pessoas[i].idade, "\n")] = 0;

                printf("Estado de Conciencia Do Paciente: ");

                fgets(pessoas[i].conciencia, sizeof(pessoas[i].conciencia), stdin);
                pessoas[i].conciencia[strcspn(pessoas[i].conciencia, "\n")] = 0;

                printf("Sinais Vitais Do Paciente: ");

                fgets(pessoas[i].Sinais_Vitais, sizeof(pessoas[i].Sinais_Vitais), stdin);
                pessoas[i].Sinais_Vitais[strcspn(pessoas[i].Sinais_Vitais, "\n")] = 0;

                printf("Descricao da Lesao Do Paciente: ");

                fgets(pessoas[i].nome, sizeof(pessoas[i].nome), stdin);
                pessoas[i].nome[strcspn(pessoas[i].nome, "\n")] = 0;

                printf("Data do Ocorrido: ");

                fgets(pessoas[i].data, sizeof(pessoas[i].data), stdin);
                pessoas[i].data[strcspn(pessoas[i].data, "\n")] = 0;

                printf("Hora do Ocorrido: ");

                fgets(pessoas[i].hora, sizeof(pessoas[i].hora), stdin);
                pessoas[i].hora[strcspn(pessoas[i].hora, "\n")] = 0;

                printf("Local do Ocorrido: ");

                fgets(pessoas[i].local, sizeof(pessoas[i].local), stdin);
                pessoas[i].local[strcspn(pessoas[i].local, "\n")] = 0;

                printf("Tipo do acidente: ");

                fgets(pessoas[i].tipo_acidente, sizeof(pessoas[i].tipo_acidente), stdin);
                pessoas[i].tipo_acidente[strcspn(pessoas[i].tipo_acidente, "\n")] = 0;

                printf("Observacoes: ");

                fgets(pessoas[i].observacoes, sizeof(pessoas[i].observacoes), stdin);
                pessoas[i].observacoes[strcspn(pessoas[i].observacoes, "\n")] = 0;

                fprintf(arquivo, "Nome: %s\n", pessoas[i].nome);
                fprintf(arquivo, "Sexo: %s\n", pessoas[i].sexo);
                fprintf(arquivo, "Idade: %s\n", pessoas[i].idade);
                fprintf(arquivo, "Estado de Conciencia: %s\n", pessoas[i].conciencia);
                fprintf(arquivo, "Sinais Vitais: %s\n", pessoas[i].Sinais_Vitais);
                fprintf(arquivo, "Descricao da Lesao: %s\n", pessoas[i].descricao_da_lesao);
                fprintf(arquivo, "Data: %s\n", pessoas[i].data);
                fprintf(arquivo, "Hora: %s\n", pessoas[i].hora);
                fprintf(arquivo, "Local: %s\n", pessoas[i].local);
                fprintf(arquivo, "Tipo: %s\n", pessoas[i].tipo_acidente);
                fprintf(arquivo, "Observacoes: %s\n", pessoas[i].observacoes);
                fclose(arquivo);
            }
            break;
        
        default:
            break;
        }
        
    }while (opc == 0);

    return 0;
}
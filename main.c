#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h>
#include <locale.h>

typedef struct{
    char nome[50];
    char sexo[10];
    char conciencia[50];
    char Sinais_Vitais[50];
    char descricao_da_lesao[100];
    char idade[10];
    char data[50];
    char hora[10];
    char local[50];
    char tipo_acidente[50];
    char observacoes[200];
} Pessoa;

Pessoa pessoas[50] = {0};

char* cadastro(char L_C, char nome[99], char senha[99]){
    char linha[256];
    char novo_nome[99];
    strcpy(novo_nome, nome);
    strcat(novo_nome, ".txt");

    if(L_C == 'L' || L_C == 'l'){
        FILE *arquivo = fopen(novo_nome, "r");
        if (arquivo == NULL) return "usuario_nao_cadastrado_ou_arquivo_nao_encontrado";

        if (fgets(linha, sizeof(linha), arquivo) != NULL){
            linha[strcspn(linha, "\r\n")] = '\0';
            fclose(arquivo);
            if(strcmp(linha, senha) == 0){
                return "usuario_logado";
            } else {
                return "senha_incorreta";
            }
        } else {
            fclose(arquivo);
            return "arquivo_vazio";
        }
    } else if(L_C == 'C' || L_C == 'c'){
        FILE *verifica = fopen(novo_nome, "r");
        if (verifica != NULL) {
            fclose(verifica);
            return "nome_existente";
        }
        FILE *criar = fopen(novo_nome, "w");
        if (criar == NULL) return "erro_no_arquivo";
        fprintf(criar, "%s", senha);
        fclose(criar);
        return "usuario_cadastrado";
    } else {
        return "parametro_[L_C]_errado";
    }
}
void limpar_console() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main(){
    int opc = 0, opc3 = 0, pacientes = 0, i = 0, m_p = 0;
    char login;
    char nm[99];
    char sn[99];
    char erro[50];
    setlocale(LC_ALL,"portuguese");
    while (m_p == 0)
    {   
        printf("||||||||||||||||||||||||||||||||||||\n");
        printf("Bem Vindo Ao Sistema Ambulancia\n");
        printf("||||||||||||||||||||||||||||||||||||\n");
        printf("Digite [L]ogin ou [C]adastro\n");
        scanf(" %c", &login);
        getchar();
        login = toupper(login);

        if(login == 'L'){
            while (opc3 == 0)
            {                    
                printf("||||||||||||||||||||||||||||||||||||\n");
                printf("Digite Seu Nome: ");
                fgets(nm, sizeof(nm), stdin);
                nm[strcspn(nm, "\r\n")] = '\0';
                printf("||||||||||||||||||||||||||||||||||||\n");
                printf("Agora Digite a Senha: ");
                fgets(sn, sizeof(sn), stdin);
                sn[strcspn(sn, "\r\n")] = '\0';
                printf("||||||||||||||||||||||||||||||||||||\n");
                strcpy(erro, cadastro(login, nm, sn));

                if(strcmp(erro, "usuario_logado") != 0){
                    limpar_console();
                    printf("Ocorreu o erro: %s\n", erro);
                    printf("Digite [1] para voltar ao Menu [0] Continuar no Login\n");
                    scanf("%d",&m_p);
                    getchar();
                    opc3 = m_p;
                } else {
                    printf("Login realizado com sucesso!\n");
                    opc3 = 1;
                    m_p = 1;
                }
            }           
        } else if (login == 'C') {
            while (opc3 == 0)
            {
                printf("||||||||||||||||||||||||||||||||||||\n");       
                printf("Digite Seu Nome: ");
                fgets(nm, sizeof(nm), stdin);
                nm[strcspn(nm, "\r\n")] = '\0';
                printf("||||||||||||||||||||||||||||||||||||\n");
                printf("Digite Sua Senha: ");
                fgets(sn, sizeof(sn), stdin);
                sn[strcspn(sn, "\r\n")] = '\0';
                printf("||||||||||||||||||||||||||||||||||||\n");
                strcpy(erro, cadastro(login, nm, sn));
                if(strcmp(erro, "usuario_cadastrado") != 0)
                {
                    limpar_console();
                    printf("Ocorreu o erro: %s\n", erro);
                    printf("Digite [1] para voltar ao Menu [0] Continuar no Login\n");
                    scanf("%d",&m_p);
                    getchar();
                    opc3 = m_p;                
                } 
                else
                {     
                    printf("Cadastro realizado com sucesso!\n");
                    opc3 = 1;
                    m_p = 1;
                }
            }     
        }
    }
    do{
        printf("\n[0] Registrar Acidente\n[1] Editar Acidente (nao implementado)\n[2] Sair\nEscolha: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {
        case 0:
            limpar_console();
            printf("\nQuantos Pacientes Você Quer Registrar?\n");
            scanf("%d", &pacientes);
            getchar();

            for(i = 0; i < pacientes; i++){
                char nomeArquivo[100];
                snprintf(nomeArquivo, sizeof(nomeArquivo), "Paciente_%d.txt", i+1);
                FILE *arquivo = fopen(nomeArquivo, "w");

                if (arquivo == NULL) {
                    printf("Erro ao criar o arquivo %s\n", nomeArquivo);
                    continue;
                }

                printf("Nome do Paciente: ");
                fgets(pessoas[i].nome, sizeof(pessoas[i].nome), stdin);
                pessoas[i].nome[strcspn(pessoas[i].nome, "\n")] = 0;

                printf("Sexo do Paciente: ");
                fgets(pessoas[i].sexo, sizeof(pessoas[i].sexo), stdin);
                pessoas[i].sexo[strcspn(pessoas[i].sexo, "\n")] = 0;

                printf("Idade do Paciente: ");
                fgets(pessoas[i].idade, sizeof(pessoas[i].idade), stdin);
                pessoas[i].idade[strcspn(pessoas[i].idade, "\n")] = 0;

                printf("Estado de Consciência: ");
                fgets(pessoas[i].conciencia, sizeof(pessoas[i].conciencia), stdin);
                pessoas[i].conciencia[strcspn(pessoas[i].conciencia, "\n")] = 0;

                printf("Sinais Vitais: ");
                fgets(pessoas[i].Sinais_Vitais, sizeof(pessoas[i].Sinais_Vitais), stdin);
                pessoas[i].Sinais_Vitais[strcspn(pessoas[i].Sinais_Vitais, "\n")] = 0;

                printf("Descrição da Lesão: ");
                fgets(pessoas[i].descricao_da_lesao, sizeof(pessoas[i].descricao_da_lesao), stdin);
                pessoas[i].descricao_da_lesao[strcspn(pessoas[i].descricao_da_lesao, "\n")] = 0;

                printf("Data do Ocorrido: ");
                fgets(pessoas[i].data, sizeof(pessoas[i].data), stdin);
                pessoas[i].data[strcspn(pessoas[i].data, "\n")] = 0;

                printf("Hora do Ocorrido: ");
                fgets(pessoas[i].hora, sizeof(pessoas[i].hora), stdin);
                pessoas[i].hora[strcspn(pessoas[i].hora, "\n")] = 0;

                printf("Local do Ocorrido: ");
                fgets(pessoas[i].local, sizeof(pessoas[i].local), stdin);
                pessoas[i].local[strcspn(pessoas[i].local, "\n")] = 0;

                printf("Tipo do Acidente: ");
                fgets(pessoas[i].tipo_acidente, sizeof(pessoas[i].tipo_acidente), stdin);
                pessoas[i].tipo_acidente[strcspn(pessoas[i].tipo_acidente, "\n")] = 0;

                printf("Observações: ");
                fgets(pessoas[i].observacoes, sizeof(pessoas[i].observacoes), stdin);
                pessoas[i].observacoes[strcspn(pessoas[i].observacoes, "\n")] = 0;

                fprintf(arquivo, "Nome: %s\n", pessoas[i].nome);
                fprintf(arquivo, "Sexo: %s\n", pessoas[i].sexo);
                fprintf(arquivo, "Idade: %s\n", pessoas[i].idade);
                fprintf(arquivo, "Estado de Consciência: %s\n", pessoas[i].conciencia);
                fprintf(arquivo, "Sinais Vitais: %s\n", pessoas[i].Sinais_Vitais);
                fprintf(arquivo, "Descrição da Lesão: %s\n", pessoas[i].descricao_da_lesao);
                fprintf(arquivo, "Data: %s\n", pessoas[i].data);
                fprintf(arquivo, "Hora: %s\n", pessoas[i].hora);
                fprintf(arquivo, "Local: %s\n", pessoas[i].local);
                fprintf(arquivo, "Tipo: %s\n", pessoas[i].tipo_acidente);
                fprintf(arquivo, "Observações: %s\n", pessoas[i].observacoes);
                fclose(arquivo);
            }
            break;

        case 2:
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida.\n");
            break;
        }

    } while (opc != 2);

    return 0;
}

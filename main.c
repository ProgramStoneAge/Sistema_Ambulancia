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

void limpar_console() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int encontrar_proximo_paciente() {
    char nomeArquivo[100];
    int i = 1;
    FILE *arquivo;

    while (1) {
        snprintf(nomeArquivo, sizeof(nomeArquivo), "Paciente_%d.txt", i);
        arquivo = fopen(nomeArquivo, "r");
        if (arquivo == NULL) {
            return i;
        } else {
            fclose(arquivo);
            i++;
        }
    }
}

void registro(int indice){
    FILE *arquivo;
    char nomeArquivo[100], linha[256];
    snprintf(nomeArquivo, sizeof(nomeArquivo), "Paciente_%d.txt", indice + 1);
    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    Pessoa temp;

    if (fgets(linha, sizeof(linha), arquivo)) sscanf(linha, "Nome: %[^\n]", temp.nome);
    if (fgets(linha, sizeof(linha), arquivo)) sscanf(linha, "Sexo: %[^\n]", temp.sexo);
    if (fgets(linha, sizeof(linha), arquivo)) sscanf(linha, "Idade: %[^\n]", temp.idade);
    if (fgets(linha, sizeof(linha), arquivo)) sscanf(linha, "Estado de Consciência: %[^\n]", temp.conciencia);
    if (fgets(linha, sizeof(linha), arquivo)) sscanf(linha, "Sinais Vitais: %[^\n]", temp.Sinais_Vitais);
    if (fgets(linha, sizeof(linha), arquivo)) sscanf(linha, "Descrição da Lesão: %[^\n]", temp.descricao_da_lesao);
    if (fgets(linha, sizeof(linha), arquivo)) sscanf(linha, "Data: %[^\n]", temp.data);
    if (fgets(linha, sizeof(linha), arquivo)) sscanf(linha, "Hora: %[^\n]", temp.hora);
    if (fgets(linha, sizeof(linha), arquivo)) sscanf(linha, "Local: %[^\n]", temp.local);
    if (fgets(linha, sizeof(linha), arquivo)) sscanf(linha, "Tipo: %[^\n]", temp.tipo_acidente);
    if (fgets(linha, sizeof(linha), arquivo)) sscanf(linha, "Observações: %[^\n]", temp.observacoes);

    fclose(arquivo);

    printf("\n==== Dados do Paciente %d ====\n", indice + 1);
    printf("Nome: %s\n", temp.nome);
    printf("Sexo: %s\n", temp.sexo);
    printf("Idade: %s\n", temp.idade);
    printf("Estado de Consciência: %s\n", temp.conciencia);
    printf("Sinais Vitais: %s\n", temp.Sinais_Vitais);
    printf("Descrição da Lesão: %s\n", temp.descricao_da_lesao);
    printf("Data: %s\n", temp.data);
    printf("Hora: %s\n", temp.hora);
    printf("Local: %s\n", temp.local);
    printf("Tipo do Acidente: %s\n", temp.tipo_acidente);
    printf("Observações: %s\n", temp.observacoes);
}

void mostrar_quantidade_pacientes() {
    int count = 0;
    char nomeArquivo[100];
    FILE *arquivo;

    for (int i = 1; i <= 50; i++) {
        snprintf(nomeArquivo, sizeof(nomeArquivo), "Paciente_%d.txt", i);
        arquivo = fopen(nomeArquivo, "r");
        if (arquivo != NULL) {
            fclose(arquivo);
            count++;
        } else {
            break;
        }
    }
    printf("Quantidade de Pacientes Registrados: %d\n", count);
}

void editar_todos_os_dados() {
    limpar_console();
    int i, pacienteEscolhido;
    char nomeArquivo[100];
    FILE *arquivo;

    mostrar_quantidade_pacientes();
    printf("\nDigite o número do paciente que deseja editar (1 a 50): ");
    scanf("%d", &pacienteEscolhido);
    getchar();

    if (pacienteEscolhido < 1 || pacienteEscolhido > 50) {
        printf("Número de paciente inválido.\n");
        return;
    }

    snprintf(nomeArquivo, sizeof(nomeArquivo), "Paciente_%d.txt", pacienteEscolhido);
    arquivo = fopen(nomeArquivo, "r+");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    for (i = 0; i < 1; i++) {
        printf("Qual Dado Você Deseja Editar?\n");
        printf("[1]Nome\n[2]Sexo\n[3]Idade\n[4]Estado de Consciência\n[5]Sinais Vitais\n");
        printf("[6]Descrição da Lesão\n[7]Data do Ocorrido\n[8]Hora do Ocorrido\n");
        printf("[9]Local do Ocorrido\n[10]Tipo do Acidente\n[11]Observações\n");
        printf("Escolha: ");
        int opcao;
        scanf("%d", &opcao);
        getchar();
        if (opcao < 1 || opcao > 11) {
            printf("Opção inválida.\n");
            fclose(arquivo);
            return;
        }
        switch (opcao) {
            case 1:
                printf("Digite o novo Nome: ");
                fgets(pessoas[pacienteEscolhido - 1].nome, sizeof(pessoas[pacienteEscolhido - 1].nome), stdin);
                pessoas[pacienteEscolhido - 1].nome[strcspn(pessoas[pacienteEscolhido - 1].nome, "\n")] = 0;
                fprintf(arquivo, "Nome: %s\n", pessoas[pacienteEscolhido - 1].nome);
                fseek(arquivo, 0, SEEK_SET);
                break;
            case 2:
                printf("Digite o novo Sexo: ");
                fgets(pessoas[pacienteEscolhido - 1].sexo, sizeof(pessoas[pacienteEscolhido - 1].sexo), stdin);
                pessoas[pacienteEscolhido - 1].sexo[strcspn(pessoas[pacienteEscolhido - 1].sexo, "\n")] = 0;
                fprintf(arquivo, "Sexo: %s\n", pessoas[pacienteEscolhido - 1].sexo);
                fseek(arquivo, 0, SEEK_SET);
                break;
            case 3:
                printf("Digite a nova Idade: ");
                fgets(pessoas[pacienteEscolhido - 1].idade, sizeof(pessoas[pacienteEscolhido - 1].idade), stdin);
                pessoas[pacienteEscolhido - 1].idade[strcspn(pessoas[pacienteEscolhido - 1].idade, "\n")] = 0;
                fprintf(arquivo, "Idade: %s\n", pessoas[pacienteEscolhido - 1].idade);
                fseek(arquivo, 0, SEEK_SET);
                break;
            case 4:
                printf("Digite o novo Estado de Consciência: ");
                fgets(pessoas[pacienteEscolhido - 1].conciencia, sizeof(pessoas[pacienteEscolhido - 1].conciencia), stdin);
                pessoas[pacienteEscolhido - 1].conciencia[strcspn(pessoas[pacienteEscolhido - 1].conciencia, "\n")] = 0;
                fprintf(arquivo, "Estado de Consciência: %s\n", pessoas[pacienteEscolhido - 1].conciencia);
                fseek(arquivo, 0, SEEK_SET);
                break;
            case 5:
                printf("Digite os novos Sinais Vitais: ");
                fgets(pessoas[pacienteEscolhido - 1].Sinais_Vitais, sizeof(pessoas[pacienteEscolhido - 1].Sinais_Vitais), stdin);
                pessoas[pacienteEscolhido - 1].Sinais_Vitais[strcspn(pessoas[pacienteEscolhido - 1].Sinais_Vitais, "\n")] = 0;
                fprintf(arquivo, "Sinais Vitais: %s\n", pessoas[pacienteEscolhido - 1].Sinais_Vitais);
                fseek(arquivo, 0, SEEK_SET);
                break;
            case 6:
                printf("Digite a nova Descrição da Lesão: ");
                fgets(pessoas[pacienteEscolhido - 1].descricao_da_lesao, sizeof(pessoas[pacienteEscolhido - 1].descricao_da_lesao), stdin);
                pessoas[pacienteEscolhido - 1].descricao_da_lesao[strcspn(pessoas[pacienteEscolhido - 1].descricao_da_lesao, "\n")] = 0;
                fprintf(arquivo, "Descrição da Lesão: %s\n", pessoas[pacienteEscolhido - 1].descricao_da_lesao);
                fseek(arquivo, 0, SEEK_SET);
                break;
            case 7:
                printf("Digite a nova Data do Ocorrido: ");
                fgets(pessoas[pacienteEscolhido - 1].data, sizeof(pessoas[pacienteEscolhido - 1].data), stdin);
                pessoas[pacienteEscolhido - 1].data[strcspn(pessoas[pacienteEscolhido - 1].data, "\n")] = 0;
                fprintf(arquivo, "Data do Ocorrido: %s\n", pessoas[pacienteEscolhido - 1].data);
                fseek(arquivo, 0, SEEK_SET);
                break;
            case 8:
                printf("Digite a nova Hora do Ocorrido: ");
                fgets(pessoas[pacienteEscolhido - 1].hora, sizeof(pessoas[pacienteEscolhido - 1].hora), stdin);
                pessoas[pacienteEscolhido - 1].hora[strcspn(pessoas[pacienteEscolhido - 1].hora, "\n")] = 0;
                fprintf(arquivo, "Hora do Ocorrido: %s\n", pessoas[pacienteEscolhido - 1].hora);
                fseek(arquivo, 0, SEEK_SET);
                break;
            case 9:
                printf("Digite o novo Local do Ocorrido: ");
                fgets(pessoas[pacienteEscolhido - 1].local, sizeof(pessoas[pacienteEscolhido - 1].local), stdin);
                pessoas[pacienteEscolhido - 1].local[strcspn(pessoas[pacienteEscolhido - 1].local, "\n")] = 0;
                fprintf(arquivo, "Local do Ocorrido: %s\n", pessoas[pacienteEscolhido - 1].local);
                fseek(arquivo, 0, SEEK_SET);
                break;
            case 10:
                printf("Digite o novo Tipo do Acidente: ");
                fgets(pessoas[pacienteEscolhido - 1].tipo_acidente, sizeof(pessoas[pacienteEscolhido - 1].tipo_acidente), stdin);
                pessoas[pacienteEscolhido - 1].tipo_acidente[strcspn(pessoas[pacienteEscolhido - 1].tipo_acidente, "\n")] = 0;
                fprintf(arquivo, "Tipo do Acidente: %s\n", pessoas[pacienteEscolhido - 1].tipo_acidente);
                fseek(arquivo, 0, SEEK_SET);
                break;
            case 11:
                printf("Digite as novas Observações: ");
                fgets(pessoas[pacienteEscolhido - 1].observacoes, sizeof(pessoas[pacienteEscolhido - 1].observacoes), stdin);
                pessoas[pacienteEscolhido - 1].observacoes[strcspn(pessoas[pacienteEscolhido - 1].observacoes, "\n")] = 0;
                fprintf(arquivo, "Observações: %s\n", pessoas[pacienteEscolhido - 1].observacoes);
                fseek(arquivo, 0, SEEK_SET);
                break;
            default:
                printf("Opção inválida.\n");
                fclose(arquivo); 
            break;
        }
    }
    fclose(arquivo);
    limpar_console();
}


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
        printf("\n[0]Registrar Acidente\n[1]Relatorio\n[2]Sair\n[3]Editar Relatório\nEscolha: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {
        case 0:
            limpar_console();           
            printf("\nQuantos Pacientes Você Quer Registrar?\n");
            scanf("%d", &pacientes);
            getchar();
            int proximo = encontrar_proximo_paciente();

            for(i = 0; i < pacientes; i++){
                int indice = proximo + i;
                char nomeArquivo[100];
                snprintf(nomeArquivo, sizeof(nomeArquivo), "Paciente_%d.txt", indice);
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
        case 1:
            limpar_console();
            printf("Qual Paciente Você Deseja Ver?\n");
            mostrar_quantidade_pacientes();
            printf("Digite o número do paciente para ver o relatório: ");
            scanf("%d", &i);
            getchar();
            if (i >= 1 && i <= 50)
                registro(i - 1);
            else
                printf("Número de paciente inválido!\n");
            break;
        case 2:
            printf("Saindo...\n");
            break;
        case 3:
            editar_todos_os_dados();
            break;
        default:
            printf("Opção inválida.\n");
            break;
        }

    } while (opc != 2);

    return 0;
}

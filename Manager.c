#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


void newFolder()
{
    char *name_folder = (char *)malloc(1024);
    char *command = (char *)malloc(2048);

    printf("\n\n[Criar uma Pasta]\nDigite o Nome da pasta de ate 24 caracteres: ");
    scanf("%s", name_folder);

    sprintf(command, "md %s", name_folder);
    system(command);

    free(command);
    free(name_folder);

    printf("Pasta Criada com Sucesso!\n\n");
}

void delFolder()
{
    char *name_folder = (char *) malloc(1024);
    char *command = (char *) malloc(2048);

    printf("\n\n[Deletar uma Pasta]\nDigite o Nome da pasta: ");
    scanf("%s", name_folder);

    sprintf(command, "if exist %s\\. (echo Apagando...) else (echo Pasta nao encontrada)", name_folder);
    system(command);

    FILE *fp = popen(command, "r");
    char result[128];
    fgets(result, sizeof(result), fp);
    pclose(fp);

    if (strstr(result, "Apagando...") != NULL)
    {
        memset(command, 0, sizeof(command));

        sprintf(command, "rmdir %s", name_folder);
        system(command);
        printf("Pasta %s apagada com sucesso\n\n", name_folder);
    }

    free(name_folder);
    free(command);
}

void dirSys() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    
    if (dir == NULL) {
        perror("Erro ao abrir o diretório");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

void infoSys() {
    FILE *fp;
    char buffer[128];

    fp = popen("systeminfo", "r");
    if (fp == NULL) {
        perror("Erro ao executar systeminfo");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer); 
    }

    pclose(fp);
}

void openBrowser() {
    system("start chrome"); // ;-;
}

void read_query_choose(int *QUERY)
{
    switch (*QUERY)
    {
    case 1:
        newFolder();
        break;
    case 2:
        delFolder();
        break;
    case 3:
        dirSys();
        break;
    case 4:
        infoSys();
        break;
    case 5:
        openBrowser();
        break;
    }
}

void menu_opcoes()
{
    system("cls");
    unsigned int response_menu;

    printf("1 - Criar uma Pasta\n");
    printf("2 - Deletar uma Pasta\n");
    printf("3 - Consultar diretorios\n");
    printf("4 - Consultar as informacoes do computador\n");
    printf("5 - Abrir o navegador Chrome\n");
    printf("0 - Sair.\n");

    scanf("%d", &response_menu);

    read_query_choose(&response_menu);
}

int main(void) {
    char yn;

    do {
        printf("ManagerSys For Windows...\n\n");
        printf("Digite Y para acessar o menu e N para parar\n> ");

        scanf(" %c", &yn);

        unsigned int QUERY_FNV_CMD;
        
        if(yn == 'y' || yn == 'Y') menu_opcoes();
        else if(yn == 'n' || yn == 'N') break;
    } while (yn != '0');

    return 0;
}
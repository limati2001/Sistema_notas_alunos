#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct
{
    char nome[50];
    float n1;
    float n2;
    float media;
} Aluno;

int main(void)
{

    Aluno alunos[MAX];
    int total = 0;
    int opcao;

    while (1)
    {
        printf("\n===Menu ===\n");
        printf("1 - Adicionar aluno: \n");
        printf("2- Listar alunos\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) //Adicionar alunos
        {
            if (total >= MAX)
            {
                printf("Limite atingido\n");
                continue;
            }
            printf("Nome do aluno: ");
            scanf("%49s", alunos[total].nome);

            printf("Nota 1: ");
            scanf("%f", &alunos[total].n1);

            printf("Nota 2: ");
            scanf("%f", &alunos[total].n2);

            total++;

            system("clear");
        }
        else if (opcao == 2) //Listar Alunos
        {
            system("clear");

            if (total == 0)
            {
                printf("\nNenhum aluno cadastrado.\n");
                continue;
            }

            printf("\n=== Lista ===\n");
            for (int i = 0; i < total; i++)
            {
                float media = (alunos[i].n1 + alunos[i].n2) / 2.0;
                printf("%s - Media: %.2f\n", alunos[i].nome, media);
            }
        }
        else if (opcao == 0)
        {
            break;
        }
        else
        {
            printf("Opcao invalida.\n");
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aluno.h"
#include "turma.h"

#define ARQ "alunos.dat"

static void limpar_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // limpa
    }
}

static void limpar_tela(void)
{
    // Linux
    system("clear");
}

// Persistencia em arquivo

static int salvar(const Aluno alunos[], int total)
{
    FILE *f = fopen(ARQ, "wb");
    if (!f)
    {
        return 0;
    }
    if (fwrite(&total, sizeof(int), 1, f) != 1)
    {
        fclose(f);
        return 0;
    }

    if (total > 0 && fwrite(alunos, sizeof(Aluno), (size_t)total, f) != (size_t)total)
    {
        fclose(f);
        return 0;
    }

    fclose(f);
    return 1;
}

static int carregar(Aluno alunos[], int *total)
{
    FILE *f = fopen(ARQ, "rb");
    if (!f)
    {
        *total = 0; // arquivo nao existe ainda
        return 1;
    }
    int t = 0;
    if (fread(&t, sizeof(int), 1, f) != 1)
    {
        fclose(f);
        return 0;
    }

    if (t < 0 || t > MAX)
    {
        fclose(f);
        return 0;
    }

    if (t > 0 && fread(alunos, sizeof(Aluno), (size_t)t, f) != (size_t)t)
    {
        fclose(f);
        return 0;
    }

    fclose(f);
    *total = t;
    return 1;
}

// ---------- Utilidades de busca ----------

static int encontrar_por_matricula(const Aluno alunos[], int total, int mat)
{
    for (int i = 0; i < total; i++)
    {
        if (alunos[i].matricula == mat)
            return i;
    }
    return -1;
}

// Operações

static void adicionar_aluno(Aluno alunos[], int *total)
{
    if (*total >= MAX)
    {
        printf("Limite atingido.\n");
        return;
    }

    Aluno a;

    printf("Matricula (int): ");
    if (scanf("%d", &a.matricula) != 1)
    {
        printf("Entrada invalida.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    if (encontrar_por_matricula(alunos, *total, a.matricula) != -1)
    {
        printf("Ja existe aluno com essa matricula.\n");
        return;
    }

    printf("Nome do aluno: ");

    if (fgets(a.nome, sizeof(a.nome), stdin) == NULL)
    {
        printf("Entrada invalida.\n");
        return;
    }

    a.nome[strcspn(a.nome, "\n")] = '\0';

    printf("Nota BIMESTRE 1: ");
    if (scanf("%f", &a.n1) != 1)
    {
        printf("Entrada invalida.\n");
        limpar_buffer();
        return;
    }

    printf("Nota BIMESTRE 2: ");
    if (scanf("%f", &a.n2) != 1)
    {
        printf("Entrada invalida.\n");
        limpar_buffer();
        return;
    }

    printf("Nota BIMESTRE 3: ");
    if (scanf("%f", &a.n3) != 1)
    {
        printf("Entrada invalida.\n");
        limpar_buffer();
        return;
    }

    printf("Nota BIMESTRE 4: ");
    if (scanf("%f", &a.n4) != 1)
    {
        printf("Entrada invalida.\n");
        limpar_buffer();
        return;
    }

    limpar_buffer();

    alunos[*total] = a;
    (*total)++;

    printf("Aluno adicionado!\n");
}

static void listar_alunos(const Aluno alunos[], int total)
{
    if (total == 0)
    {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("\n=== LISTA ===\n");
    printf("%-6s | %-20s | %5s | %5s | %5s | %5s | %5s\n", "MAT", "NOME", "N1", "N2", "N3","N4", "MED");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < total; i++)
    {
        printf("%-6d | %-20s | %5.1f | %5.1f | %5.1f | %5.1f | %5.1f\n",
               alunos[i].matricula,
               alunos[i].nome,
               alunos[i].n1,
               alunos[i].n2,
               alunos[i].n3,
               alunos[i].n4,
               Aluno_media(&alunos[i]));
    }
}

static void editar_notas(Aluno alunos[], int total)
{
    if (total == 0)
    {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    int mat;
    printf("Matricula do aluno a editar: ");
    if (scanf("%d", &mat) != 1)
    {
        printf("Entrada invalida.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    int idx = encontrar_por_matricula(alunos, total, mat);
    if (idx == -1)
    {
        printf("Aluno nao encontrado.\n");
        return;
    }

    printf("Editando %s (mat %d)\n", alunos[idx].nome, alunos[idx].matricula);
    printf("Nota BIMESTRE 1 atual: %.1f\n", alunos[idx].n1);
    printf("Nova Nota BIMESTRE 1: ");
    if (scanf("%f", &alunos[idx].n1) != 1)
    {
        printf("Entrada invalida.\n");
        limpar_buffer();
        return;
    }

    printf("Nota  BIMESTRE 2 atual: %.1f\n", alunos[idx].n2);
    printf("Nova Nota BIMESTRE 2: ");
    if (scanf("%f", &alunos[idx].n2) != 1)
    {
        printf("Entrada invalida.\n");
        limpar_buffer();
        return;
    }

    printf("Nota BIMESTRE 3 atual: %.1f\n", alunos[idx].n3);
    printf("Nova Nota BIMESTRE 3: ");
    if (scanf("%f", &alunos[idx].n3) != 1)
    {
        printf("Entrada invalida.\n");
        limpar_buffer();
        return;
    }

    printf("Nota 4 BIMESTRE atual: %.1f\n", alunos[idx].n4);
    printf("Nova Nota BIMESTRE4: ");
    if (scanf("%f", &alunos[idx].n4) != 1)
    {
        printf("Entrada invalida.\n");
        limpar_buffer();
        return;
    }

    limpar_buffer();
    printf("Notas atualizadas!\n");
}

static void remover_aluno(Aluno alunos[], int *total)
{
    if (*total == 0)
    {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    int mat;
    printf("Matricula do aluno a remover: ");
    if (scanf("%d", &mat) != 1)
    {
        printf("Entrada invalida.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    int idx = encontrar_por_matricula(alunos, *total, mat);
    if (idx == -1)
    {
        printf("Aluno nao encontrado.\n");
        return;
    }

    // “puxa” os itens da direita uma casa pra esquerda
    for (int i = idx; i < *total - 1; i++)
    {
        alunos[i] = alunos[i + 1];
    }
    (*total)--;

    printf("Aluno removido!\n");
}

// Menu

static void menu(void)
{
    printf("\n=== MENU ===\n");
    printf("1 - Adicionar aluno\n");
    printf("2 - Listar alunos\n");
    printf("3 - Editar notas\n");
    printf("4 - Remover aluno\n");
    printf("5 - Salvar agora\n");
    printf("0 - Salvar e sair\n");
    printf("Escolha: ");
}

int main(void)
{
    Turma turma = {0}; 
    Turma_carregar(&turma);

    Aluno alunos[MAX];
    int total = 0;

    if (!carregar(alunos, &total))
    {
        printf("Erro ao carregar %s (arquivo corrompido ou formato invalido).\n", ARQ);
        return 1;
    }

    int opcao;
    while (1)
    {
        menu();

        if (scanf("%d", &opcao) != 1)
        {
            printf("Entrada invalida.\n");
            limpar_buffer();
            continue;
        }
        limpar_buffer();

        if (opcao == 1)
        {
            limpar_tela();
            adicionar_aluno(alunos, &total);
        }
        else if (opcao == 2)
        {
            limpar_tela();
            listar_alunos(alunos, total);
        }
        else if (opcao == 3)
        {
            limpar_tela();
            editar_notas(alunos, total);
        }
        else if (opcao == 4)
        {
            limpar_tela();
            remover_aluno(alunos, &total);
        }
        else if (opcao == 5)
        {
            if (salvar(alunos, total))
                printf("Salvo em %s.\n", ARQ);
            else
                printf("Erro ao salvar.\n");
        }
        else if (opcao == 0)
        {
            if (!salvar(alunos, total))
                printf("Erro ao salvar.\n");
            else
                printf("Salvo em %s. Tchau!\n", ARQ);
            break;
        }
        else
        {
            printf("Opcao invalida.\n");
        }
    }

    return 0;
}
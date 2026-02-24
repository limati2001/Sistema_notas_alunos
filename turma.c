#include <stdio.h>
#include "turma.h"

#define ARQ "alunos.dat"

int Turma_carregar(Turma *self)
{
    FILE *f = fopen(ARQ, "rb");
    if (!f)
    {
        self->total = 0;
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

    if (t > 0 && fread(self->alunos, sizeof(Aluno), (size_t)t, f) != (size_t)t)
    {
        fclose(f);
        return 0;
    }

    fclose(f);
    self->total = t;
    return 1;
}

int Turma_salvar(const Turma *self)
{
    FILE *f = fopen(ARQ, "wb");
    if (!f) return 0;

    if (fwrite(&self->total, sizeof(int), 1, f) != 1)
    {
        fclose(f);
        return 0;
    }

    if (self->total > 0 && fwrite(self->alunos, sizeof(Aluno), (size_t)self->total, f) != (size_t)self->total)
    {
        fclose(f);
        return 0;
    }

    fclose(f);
    return 1;
}

void Turma_adicionar(Turma *self)
{
    // implementar
}

void Turma_remover(Turma *self, int matricula)
{
    // implementar
}

void Turma_listar(const Turma *self)
{
    // implementar
}
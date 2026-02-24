#ifndef TURMA_H
#define TURMA_H

#include "aluno.h"

#define MAX 2500

typedef struct {
    Aluno alunos[MAX];
    int total;
} Turma;

//void Turma_adicionar(Turma *self);
//void Turma_remover(Turma *self, int matricula);
//void Turma_listar(const Turma *self);
//int  Turma_salvar(const Turma *self);
//int  Turma_carregar(Turma *self);

#endif
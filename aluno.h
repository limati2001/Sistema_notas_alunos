#ifndef ALUNO_H
#define ALUNO_H

typedef struct
{
    int matricula;
    char nome[50];
    float n1;
    float n2;
    float n3;
    float n4;
    float media;
} Aluno;

float Aluno_media(const Aluno *a);

#endif
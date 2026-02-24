#include "aluno.h"

float Aluno_media(const Aluno *a) {
    return (a->n1 + a->n2 + a->n3 + a->n4) / 4.0f;
}
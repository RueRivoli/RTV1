#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vect
{
    float         x;
    float         y;
    float         z;
}               t_vect;


/*
** vector.c
*/

t_vect      *new_vect(float x, float y, float z);
float       scalar_product(t_vect *v1, t_vect *v2);
t_vect      *add_vect(t_vect *v1, t_vect *v2);
t_vect      *minus_vect(t_vect *v1, t_vect *v2);
t_vect      *normed_vector(t_vect *v1);
t_vect      *product_vectorial(t_vect *u, t_vect *v);
t_vect      *multiply_scalar(t_vect *v, float k);
float       distance(t_vect *v1, t_vect *v2);
float       min(float r, float s);
float       max(float r, float s);
float       norm(t_vect *v);
#endif

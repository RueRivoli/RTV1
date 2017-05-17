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
t_vect *add_vect(t_vect *v1, t_vect *v2);
t_vect *minus_vect(t_vect *v1, t_vect *v2);

#endif

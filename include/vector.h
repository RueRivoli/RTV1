/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 19:00:43 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/13 19:34:51 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct		s_vect
{
	float		x;
	float		y;
	float		z;
}					t_vect;

t_vect				normed_vect(t_vect *v1);
t_vect				multiply_scalar(t_vect v, float k);
float				distance(t_vect v1, t_vect v2);
float				min(float r, float s);
float				max(float r, float s);
float				norm(t_vect *v);
float				min_positiv(float r, float s);
float				min_positiv_s(float r, float s, float seuil);
void				rotation_vect_z(t_vect v, float angle);
void				rotation_vectx(t_vect v, float angle);
void				normed(t_vect *v);
float				scalar_product(t_vect v1, t_vect v2);
t_vect				new_vect(float x, float y, float z);
t_vect				add_vect(t_vect v1, t_vect v2);
t_vect				min_vect(t_vect v1, t_vect v2);
int					colin(t_vect v, t_vect w);
t_vect				vect_null(void);
int					equals_vect(t_vect v1, t_vect v2);
t_vect				add_vect_float(t_vect v, float f, int n);
t_vect				add_vect_rotation(t_vect v, float theta, int n);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:52:01 by fgallois          #+#    #+#             */
/*   Updated: 2017/10/11 14:23:30 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float		add_phi(t_env *env)
{
	t_vect	central;
	t_vect	basic;
	float	phi0;

	basic = vect_basic();
	central = vect_central(env);
	phi0 = phi(central) - phi(basic);
	return (phi0);
}

float		add_theta(t_env *env)
{
	t_vect	central;
	t_vect	basic;
	float	theta0;

	basic = vect_basic();
	central = vect_central(env);
	theta0 = theta(central) - theta(basic);
	return (theta0);
}

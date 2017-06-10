/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:52:01 by fgallois          #+#    #+#             */
/*   Updated: 2017/06/09 11:51:35 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float       add_phi(t_env *env)
{
	t_vect *central;
	t_vect *basic;
	float phi0;

	basic = vect_basic();
	central = vect_central(env);
	phi0 = phi(central) - phi(basic);
	free(basic);
	free(central);
	return (phi0);
}

float       add_theta(t_env *env)
{
	t_vect *central;
	t_vect *basic;
	float theta0;

	basic = vect_basic();
	central = vect_central(env);
	theta0 = theta(central) - theta(basic);
	free(basic);
	free(central);
	return (theta0);
}

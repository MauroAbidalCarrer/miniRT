/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 01:05:21 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/17 18:36:33 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

//return nb of solutions
//solutions must be a double [2]
int	solve_2nd_degree(double a, double b, double c, double *solutions)
{
	double	descriminant;

	descriminant = b * b - (4 * a * c);
	if (descriminant >= 0)
	{
		descriminant = sqrt(descriminant);
		solutions[CLOSEST] = (-b - descriminant) / (2 * a);
		solutions[FURTHEST] = (-b + descriminant) / (2 * a);
		return (2);
	}
	return (0);
}

double	sqrd(double a)
{
	return (a * a);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 00:24:35 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/07 18:34:01 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
/*
t_matrix	angles_to_rotation(t_vec angles)
{
	t_matrix	matrix;
	t_vec			angles_upward;
	t_vec			angles_sideway;

	angles_upward.x = 90.0 + angles.x;
	angles_upward.y = angles.y;
	angles_upward.z = 0;
	matrix.j = angles_to_vector(angles_upward);
	angles_sideway.x = 0.0;
	angles_sideway.y = angles.y + 90;
	angles_sideway.z = 0;
	matrix.i = angles_to_vector(angles_sideway);
	matrix.k = angles_to_vector(angles);
	return (matrix);
}
*/

//assuming that the up vector is (0, 1, 0)... up
t_matrix	dir_to_rotation(t_vec dir)
{
	t_matrix	m;

	m.i = new_v(-dir.z, 0, dir.x);
	m.j = cross(m.i, dir);
	m.k = dir;
	return (m);
}

t_vec	mult_vec_by_matrix(t_vec v, t_matrix mat)
{
	t_vec	new;

	new = new_v(0, 0, 0);
	new = sum(new, mul_d(mat.i, v.x));
	new = sum(new, mul_d(mat.j, v.y));
	new = sum(new, mul_d(mat.k, v.z));
	return (new);
}

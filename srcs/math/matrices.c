/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 00:24:35 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/16 15:41:19 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

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

/*
//consiering that the up vector is (0, 1, 0)... up
t_matrix	dir_to_rotation(t_vec dir)
{
	t_matrix m;

(void)dir;
	return (m);
}
*/

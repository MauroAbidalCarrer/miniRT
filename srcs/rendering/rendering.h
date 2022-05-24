/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:52:11 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/22 17:05:01 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "ft_math.h"
# include "mlx_colors.h"
# include "scene.h"

# ifndef BOOL
#  define BOOL uint8_t 
#  define FALSE 0
#  define TRUE 1
# endif
# ifndef RAYHIT
#  define RAYHIT
typedef struct s_rayhit
{
	t_col	albedo;
	t_vec	point;
	t_vec	normal;
	double	t;
}	t_rayhit;
# endif 

extern BOOL	test;

t_ray	mk_camray(t_camera cam, int x, int y);
BOOL	sphere_raycast(void *sphere, t_ray ray, t_rayhit *hit);
BOOL	plane_raycast(void *plane_ptr, t_ray ray, t_rayhit *hit);
BOOL	cylinder_raycast(void *cylinder_ptr, t_ray ray, t_rayhit *hit);
void	render_img(t_col *img, t_scene scene);
#endif

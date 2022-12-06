/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:52:11 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/06 19:06:35 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H
# include "ft_math.h"
# include "mlx_colors.h"
# include "scene.h"
# include "header.h"
# ifndef BOOL
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

# ifndef T_MLX
#  define T_MLX

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
}	t_mlx;
# endif
# ifndef T_TO_FREE
#  define T_TO_FREE

typedef struct s_to_free
{
	t_mlx	*mlx;
	t_list	*objs;
}	t_to_free;
int		ft_close(t_to_free *to_free);
# endif

t_ray	mk_camray(t_camera cam, int x, int y);
int		sphere_raycast(void *sphere, t_ray ray, t_rayhit *hit);
int		plane_raycast(void *plane_ptr, t_ray ray, t_rayhit *hit);
int		cylinder_raycast(void *cylinder_ptr, t_ray ray, t_rayhit *hit);
void	render_img(t_scene scene, t_mlx mlx, t_to_free *to_free);
int		are_hits(double *inters, t_rayhit *hit);
#endif

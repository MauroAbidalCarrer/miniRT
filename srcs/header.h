/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:37:06 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/06 19:02:42 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include "ft_math.h"
# include "mlx_colors.h"
# include "scene.h"
# include "parsing.h"
# include <float.h>
# include "libft.h"
# include "mlx.h"
# include <stdint.h>
# include <stdlib.h>
# include "rendering.h"
# define WIN_WIDTH 800
# define WIN_HEIGHT 800
# define HALF_WIDTH 400
# define HALF_HEIGHT 400
# define NEAR_PLANE 0.05

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
int	ft_close(t_to_free *to_free);
# endif

# ifndef BOOL
#  define FALSE 0
#  define TRUE 1
# endif
#endif

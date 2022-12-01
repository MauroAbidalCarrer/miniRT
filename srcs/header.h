/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:37:06 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/01 18:31:22 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define WIN_WIDTH 800
# define WIN_HEIGHT 800
# define HALF_WIDTH WIN_WIDTH / 2
# define HALF_HEIGHT WIN_HEIGHT / 2

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
}	t_mlx;

# include "parsing.h"
# include <float.h>
# include "libft.h"
# include "mlx.h"
# include "mlx_colors.h"
# include "ft_math.h"
# include "scene.h"
# include <stdint.h>
# include <stdlib.h>
# ifndef BOOL
#  define BOOL uint8_t 
#  define FALSE 0
#  define TRUE 1
# endif
# include "rendering.h"
#endif

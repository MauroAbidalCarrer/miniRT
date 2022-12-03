/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_colors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:14:59 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/03 21:19:53 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_COLORS_H
# define MLX_COLORS_H
# include <stdint.h>

typedef uint32_t	t_col;
//one channel is actually 8 bits long,
//but 16 isrequired for operation that exceed uint8 max
typedef uint16_t	t_channel;

t_col	mult_colors(t_col a, t_col b);
t_col	add_colors(t_col a, t_col b);
t_col	mult_color_scalar(t_col col, double scalar);

# define MAX_CHANNEL 255
# define BLACK 0
# define WHITE 0x00FFFFFF
# define GREY  0x00505050
# define BLUE  0x000000FF
# define GREEN 0x0000FF00
# define RED   0x00FF0000
# define RED_INDEX 0
# define BLUE_INDEX 2
# define GREEN_INDEX 1
#endif

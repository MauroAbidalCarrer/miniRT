/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:51:05 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/22 16:53:46 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAT_H
# define FT_MAT_H
# include <math.h>
//vectors
typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}				t_vec;
//vector-scalar operations
t_vec		div_d(t_vec v, double d);
t_vec		mul_d(t_vec v, double d);
//vector-vector operations
t_vec		sum(t_vec a, t_vec b);
t_vec		dif(t_vec a, t_vec b);
t_vec		mul(t_vec a, t_vec b);
double	dist(t_vec a, t_vec b);
double	sqrd_dist(t_vec a, t_vec b);
//div funciton already exists in stdlib
t_vec		di(t_vec num, t_vec denum);
t_vec		normalized(t_vec v);
//vector operation
double	magnitude(t_vec v);
double sqrd_mag(t_vec v);
double	dot(t_vec a, t_vec b);
//others
void	print_vec2(t_vec v);
void	print_vec3(t_vec v);
t_vec		angles_to_vector(t_vec angles);
t_vec	new_v(double x, double y, double z);

//matrices
typedef struct s_matrix
{
	t_vec	i;
	t_vec	j;
	t_vec	k;
}	t_matrix;

//t_matrix	angles_to_roatation(t_vec angles);
//t_matrix	dir_to_rotation(t_vec angles);

//algebra
//quadratic
# define DEG2RAD 0.0174533
# define CLOSEST 0
# define FURTHEST 1
int		solve_2nd_degree(double a, double b, double c, double *solutions);
double	sqrd(double a);

//ray
typedef struct s_ray
{
	t_vec	origin;
	t_vec	dir;
}	t_ray;

#endif

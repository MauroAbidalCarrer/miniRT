/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:45:01 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/06 19:01:04 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "header.h"
#define KEY_ESC_M 53
#define KEY_ESC_L 65307

static void	free_obj(void *obj_interface)
{
	free(((t_obj_interface *)obj_interface)->obj);
	free(obj_interface);
}

//should only be called after setup_scene
int	ft_close(t_to_free *to_free)
{
	t_mlx	mlx;

	mlx = *to_free->mlx;
	ft_lstclear(&to_free->objs, &free_obj);
	if (!mlx.ptr)
	{
		ft_putstr_fd("ERROR: could not create new window\n", 1);
		exit(1);
	}
	if (!mlx.win)
	{
		ft_putstr_fd("ERROR: could not init mlx\n", 1);
		exit(1);
	}
	mlx_destroy_window(mlx.ptr, mlx.win);
	free(mlx.ptr);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_to_free *to_free)
{
	if (keycode == KEY_ESC_M || keycode == KEY_ESC_L)
		ft_close(to_free);
	return (0);
}

void	setup_camera(t_camera *cam)
{
	cam->fov *= DEG_TO_RAD * 0.5;
	cam->fov_scalar = NEAR_PLANE * sin(cam->fov) / cos(cam->fov);
	cam->rotation = dir_to_rotation(cam->dir);
}

int	main(int ac, char **av)
{
	t_mlx		mlx;
	t_scene		scene;
	t_to_free	to_free;

	if (ac != 2)
	{
		ft_putstr_fd("ERROR: argument count should be one!\n", 1);
		exit(1);
	}
	parse_scene(av[1], &scene);
	setup_camera(&scene.camera);
	scene.light.intensity *= 100;
	to_free.objs = scene.objs;
	to_free.mlx = &mlx;
	mlx.ptr = mlx_init();
	if (mlx.ptr == NULL)
		ft_close(&to_free);
	mlx.win = mlx_new_window(mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (mlx.win == NULL)
		ft_close(&to_free);
	render_img(scene, mlx, &to_free);
	mlx_hook(mlx.win, 17, 1L << 2, &ft_close, &to_free);
	mlx_key_hook(mlx.win, &key_hook, &to_free);
	mlx_loop(mlx.ptr);
	ft_close(&to_free);
}

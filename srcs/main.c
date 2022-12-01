/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:45:01 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/01 18:30:47 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
/*
t_scene	setup_scene()
{
	t_scene		scene;

	scene.light.pos = new_v(-11, 8, 19);
	scene.light.intensity = 100;
	scene.camera.dir = new_v(0, 0, 1);
	scene.camera.pos = new_v(0, 0, 0);
	scene.camera.fov = 70.0;
	scene.ambiant_light = 0x00900A0F;

	scene.objs = malloc(sizeof(t_list));
	scene.objs->content = malloc(sizeof(t_obj_interface));
	((t_obj_interface *)scene.objs->content)->ray_caster = &sphere_raycast;
	((t_obj_interface *)scene.objs->content)->obj = malloc(sizeof(t_sphere));
	((t_sphere *)((t_obj_interface *)scene.objs->content)->obj)->center = new_v(5, 0, 17);
	((t_sphere *)((t_obj_interface *)scene.objs->content)->obj)->radius = 5;
	((t_sphere *)((t_obj_interface *)scene.objs->content)->obj)->albedo = 0x00601A5F;
	scene.objs->next = NULL;

	scene.objs->next = malloc(sizeof(t_list));
	scene.objs->next->content = malloc(sizeof(t_obj_interface));
	((t_obj_interface *)scene.objs->next->content)->ray_caster = &plane_raycast;
	((t_obj_interface *)scene.objs->next->content)->obj = malloc(sizeof(t_plane));
	((t_plane *)((t_obj_interface *)scene.objs->next->content)->obj)->pos = new_v(2, -5, 0);
	((t_plane *)((t_obj_interface *)scene.objs->next->content)->obj)->normal = new_v(1, 0, 0);
	((t_plane *)((t_obj_interface *)scene.objs->next->content)->obj)->albedo = 0x00601A5F;

	scene.objs->next->next = malloc(sizeof(t_list));
	scene.objs->next->next->content = malloc(sizeof(t_obj_interface));
	((t_obj_interface *)scene.objs->next->next->content)->ray_caster = &cylinder_raycast;
	((t_obj_interface *)scene.objs->next->next->content)->obj = malloc(sizeof(t_cylinder));
	((t_cylinder *)((t_obj_interface *)scene.objs->next->next->content)->obj)->pos = new_v(-2, -4, 15);
	((t_cylinder *)((t_obj_interface *)scene.objs->next->next->content)->obj)->dir = new_v(0, 1, 0);
	((t_cylinder *)((t_obj_interface *)scene.objs->next->next->content)->obj)->height = 3;
	((t_cylinder *)((t_obj_interface *)scene.objs->next->next->content)->obj)->radius = 2;
	((t_cylinder *)((t_obj_interface *)scene.objs->next->next->content)->obj)->albedo = 0x00601A5F;
	scene.objs->next->next->next = NULL;

	return (scene);
}
*/
# define KEY_ESC_M 53
# define KEY_ESC_L 65307
typedef struct s_to_free
{
	t_mlx	*mlx;
	t_list	*objs;
}	t_to_free;


static void free_obj(void *obj_interface)
{
	free(((t_obj_interface *)obj_interface)->obj);
	free(obj_interface);
}

//should only be called after setup_scene
static int close_window(t_to_free *to_free)
{
	int	status;
	t_mlx	mlx;

	mlx = *to_free->mlx;
	status = 0;
	ft_lstclear(&to_free->objs, &free_obj);
	if (mlx.ptr)
		free(mlx.ptr);
	else
	{
		ft_putstr_fd("ERROR: could not create new window\n", 1);
		status = 1;
	}
	if (mlx.win)
		mlx_destroy_window(mlx.ptr, mlx.win);
	else if (status == 0)
	{
		ft_putstr_fd("ERROR: could not init mlx\n", 1);
		status = 1;
	}
	exit(status);
	return (0);
}

int	key_hook(int keycode, t_to_free *to_free)
{
	if (keycode == KEY_ESC_M || keycode == KEY_ESC_L)
		close_window(to_free);
	return (0);
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
	to_free.objs = scene.objs;
	to_free.mlx = &mlx;
	mlx.ptr = mlx_init();
	if (mlx.ptr == NULL)
		close_window(&to_free);
	mlx.win = mlx_new_window(mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (mlx.win == NULL)
		close_window(&to_free);
	render_img(scene, mlx);
	mlx_hook(mlx.win, 17, 1L << 2, &close_window, &to_free);
	mlx_key_hook(mlx.win, &key_hook, &to_free);
	mlx_loop(mlx.ptr);
	close_window(&to_free);
}

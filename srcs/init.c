/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:38:07 by kanlee            #+#    #+#             */
/*   Updated: 2021/07/09 17:27:21 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "frame.h"
#include "key.h"
#include "mouse.h"
#include "utils.h"
#include "../libft/libft.h"

static void	julia_init(t_mlx *frame, int ac, char **av)
{
	frame->type = JULIASET;
	frame->julia_constant = (t_complex){0.285, 0};
	if (ac == 4)
	{
		frame->julia_constant = (t_complex){ft_atof(av[2]), ft_atof(av[3])};
		frame->julia_constant.real = clamp(frame->julia_constant.real,
			-1 * JULIA_CONST_LIMIT, JULIA_CONST_LIMIT);
		frame->julia_constant.imag = clamp(frame->julia_constant.imag,
			-1 * JULIA_CONST_LIMIT, JULIA_CONST_LIMIT);
	}
	else if (ac != 2)
	{
		printf("Julia set must have 0 or 2 double arguments.\n");
		printf("ex.\n0.2733 0.074\n-0.194 0.656\n0.3 0.04\n-0.12 0.74\n");
		exit(-1);
	}
	frame->center = (t_point){0, 0};
	frame->scale = IMG_WIDTH / 3;
	frame->it_max = 200;
}

int			set_fractal_type(t_mlx *frame, int ac, char **av)
{
	frame->center = (t_point){-0.5, 0};
	frame->scale = IMG_WIDTH / 3;
	frame->center = (t_point){-0.725703, 0.250738};
	frame->it_max = 50;
	frame->scale = 1104900.05530 * 200;
	frame->it_max = 1600;
//	frame->scale = 110 * 200;
//	frame->it_max = 200;
//	frame->center = (t_point){-1.985528, 0};
//	frame->center = (t_point){-1.996380, -0.000004};
	frame->center = (t_point){-0.015439, 1.020888};
//	frame->scale = IMG_WIDTH / 3;
//	frame->it_max = 50;
	if (ft_strequ(av[1], "mandelbrot") || ft_strequ(av[1], "m"))
		frame->type = MANDELBROT;
	else if (ft_strequ(av[1], "julia") || ft_strequ(av[1], "j"))
		julia_init(frame, ac, av);
	else if (ft_strequ(av[1], "koch"))
		frame->type = KOCH_SNOWFLAKE;
	else
		return (0);
	return (1);
}

static void load_julia_ctl_pad(t_mlx *frame)
{
	frame->julia_ctl_bg.img_ptr = mlx_xpm_file_to_image(frame->mlx,
		"assets/julia_ctl_bg.xpm",
		&frame->julia_ctl_bg.width, &frame->julia_ctl_bg.height);
	if (!frame->julia_ctl_bg.img_ptr)
	{
		printf("cannot load assets/julia_ctl_bg.xpm\n");
		exit(-1);
	}
	frame->julia_ctl_btn.img_ptr = mlx_xpm_file_to_image(frame->mlx,
		"assets/julia_ctl_btn.xpm",
		&frame->julia_ctl_btn.width, &frame->julia_ctl_btn.height);
	if (!frame->julia_ctl_btn.img_ptr)
	{
		printf("cannot load assets/julia_ctl_btn.xpm\n");
		exit(-1);
	}
	frame->julia_ctl_bg.imgdata = mlx_get_data_addr(
		frame->julia_ctl_bg.img_ptr, &frame->julia_ctl_bg.bpp,
		&frame->julia_ctl_bg.size_line, &frame->julia_ctl_bg.endian);
	frame->julia_ctl_btn.imgdata = mlx_get_data_addr(
		frame->julia_ctl_btn.img_ptr, &frame->julia_ctl_btn.bpp,
		&frame->julia_ctl_btn.size_line, &frame->julia_ctl_btn.endian);
}

void		init_frame(t_mlx *frame)
{
	frame->mlx = mlx_init();
	frame->upperleft.x = -2.0;
	frame->upperleft.y = 1.5;
	frame->upperleft.x = frame->center.x - IMG_WIDTH / frame->scale / 2;
	frame->upperleft.y = frame->center.y + IMG_HEIGHT / frame->scale / 2;
	frame->win = mlx_new_window(frame->mlx, IMG_WIDTH + MENU_WIDTH, IMG_HEIGHT,
		"fract-ol");
	frame->img.img_ptr = mlx_new_image(frame->mlx, IMG_WIDTH, IMG_HEIGHT);
	frame->img.imgdata = mlx_get_data_addr(frame->img.img_ptr,
			&frame->img.bpp, &frame->img.size_line, &frame->img.endian);
	frame->menu.img_ptr = mlx_new_image(frame->mlx, MENU_WIDTH, IMG_HEIGHT);
	frame->menu.imgdata = mlx_get_data_addr(frame->menu.img_ptr,
			&frame->menu.bpp, &frame->menu.size_line, &frame->menu.endian);
	frame->img_move.img_ptr = mlx_new_image(frame->mlx, IMG_WIDTH, IMG_HEIGHT);
	frame->img_move.imgdata = mlx_get_data_addr(frame->img_move.img_ptr,
			&frame->img_move.bpp, &frame->img_move.size_line, &frame->img_move.endian);
	frame->lbtn_pressed = 0;
	frame->zoom_mode = 0;
	frame->color_mode = 0;
	frame->julia_ctl_clicked = 0;
	if (frame->type == JULIASET)
		load_julia_ctl_pad(frame);
}

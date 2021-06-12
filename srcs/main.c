/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:38:07 by kanlee            #+#    #+#             */
/*   Updated: 2021/06/12 22:10:09 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "frame.h"
#include "key.h"
#include "mouse.h"
#include "../libft/libft.h"

static void	init_frame(t_mlx *frame)
{
	frame->mlx = mlx_init();
//	frame->width = IMG_WIDTH + MENU_WIDTH;
//	frame->height = IMG_HEIGHT;
	frame->upperleft.x = -2.0;
	frame->upperleft.y = 1.5;
	frame->center = (t_point){-0.5, 0};
	frame->scale = IMG_WIDTH / 3;
	frame->center = (t_point){-0.725703, 0.250738};
	frame->it_max = 50;
//	frame->scale = 1104900.05530* 200;
//	frame->it_max = 1600;
//	frame->scale = 110 * 200;
//	frame->it_max = 200;
	frame->upperleft.x = frame->center.x - IMG_WIDTH / frame->scale / 2;
	frame->upperleft.y = frame->center.y + IMG_HEIGHT / frame->scale / 2;
	frame->win = mlx_new_window(frame->mlx, IMG_WIDTH + MENU_WIDTH, IMG_HEIGHT, "fract-ol");
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
}

/*
** watch WM_DELETE_WINDOW event on Linux and DestroyNotify on MacOS
** to detect closing a window.
**
** On Linux, window goes blank when minimized and then restored.
** Redraw an image again when detects VisibilityNotify (15) and
** VisibilityChangeMask (1L<<16)
*/

#ifdef LINUX

#define BUTTONPRESS 4
#define BUTTONPRESSMASK 1L<<2
#define BUTTONRELEASE 5
#define BUTTONRELEASEMASK 1L<<3
#define MOTIONNOTIFY 6
#define POINTERMOTIONMASK 1L<<6
#define BUTTON1MOTIONMASK 1L<<8


static void	init_mlx_hook(t_mlx *frame)
{
	mlx_hook(frame->win, CLIENTMESSAGE, WM_DELETE_WINDOW, close_win, frame);
	mlx_hook(frame->win, KEYPRESS, 1L, key_pressed, frame);
//	mlx_hook(frame->win, VISIBILITYNOTIFY, (1L << 16), put_img_to_window, frame);
//	mlx_mouse_hook(frame->win, mouse_hook, frame);
	mlx_hook(frame->win, BUTTONPRESS, BUTTONPRESSMASK, mouse_press, frame);
	mlx_hook(frame->win, BUTTONRELEASE, BUTTONRELEASEMASK, mouse_release, frame);
	mlx_hook(frame->win, MOTIONNOTIFY, BUTTON1MOTIONMASK, mouse_move, frame);
}

#else

static void	init_mlx_hook(t_mlx *frame)
{
	mlx_hook(frame->win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, close_win, frame);
	mlx_hook(frame->win, KEYPRESS, 1L, key_pressed, frame);
	mlx_mouse_hook(frame->win, mouse_hook, frame);
}

#endif

int			close_win(t_mlx *param)
{
	int	i;

	if (param->win)
		mlx_destroy_window(param->mlx, param->win);
	exit(0);
}

int	set_fractal_type(t_mlx *frame, int ac, char **av)
{
	if (ft_strequ(av[1], "mandelbrot") || ft_strequ(av[1], "m"))
		frame->type = MANDELBROT;
	else if (ft_strequ(av[1], "julia") || ft_strequ(av[1], "j"))
	{
		frame->type = JULIASET;
		frame->julia_constant = (t_complex){0.285, 0};
		if (ac == 4)
			frame->julia_constant = (t_complex){ft_atof(av[2]), ft_atof(av[3])};
		else if (ac != 2)
		{
			printf("Julia set must have 0 or 2 double arguments.\n");
			printf("ex.\njulia 0.2733 0.074\njulia -0.194 0.656\njulia 0.3 0.04\njulia -0.12 0.74");
			exit(-1);
		}
	}
	else if (ft_strequ(av[1], "koch"))
		frame->type = KOCH_SNOWFLAKE;
	else
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_mlx frame;
#if 0
	if (ac < 0)
		perror("argument error");
#else
	if (ac < 2 || set_fractal_type(&frame, ac, av) <= 0) {
		printf("fractol <mandelbrot | julia [(double), (double)] | koch>\n");
		return (-1);
	}
#endif
	init_frame(&frame);
	render(&frame);
	init_mlx_hook(&frame);
	mlx_loop(frame.mlx);
	return (0);
}

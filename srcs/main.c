/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:38:07 by kanlee            #+#    #+#             */
/*   Updated: 2021/11/21 18:44:10 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "frame.h"
#include "key.h"
#include "mouse.h"
#include "utils.h"
#include "../libft/libft.h"

/*
** watch WM_DELETE_WINDOW event on Linux and DestroyNotify on MacOS
** to detect closing a window.
**
** On Linux, window goes blank when minimized and then restored.
** Redraw an image again when detects VisibilityNotify (15) and
** VisibilityChangeMask (1L<<16)
*/

#define VISIBILITYNOTIFY 15
#define BUTTONPRESS 4
#define BUTTONRELEASE 5
#define MOTIONNOTIFY 6

/*
** #define BUTTONPRESSMASK 1L<<2
** #define BUTTONRELEASEMASK 1L<<3
** #define POINTERMOTIONMASK 1L<<6
** #define BUTTON1MOTIONMASK 1L<<8
*/

#ifdef LINUX

static void	init_mlx_hook(t_mlx *frame)
{
	mlx_hook(frame->win, CLIENTMESSAGE, WM_DELETE_WINDOW, close_win, frame);
	mlx_hook(frame->win, KEYPRESS, 1L, key_pressed, frame);
	mlx_hook(frame->win, VISIBILITYNOTIFY, (1L << 16), img_to_window, frame);
	mlx_hook(frame->win, BUTTONPRESS, (1L << 2), mouse_press, frame);
	mlx_hook(frame->win, BUTTONRELEASE, (1L << 3), mouse_release, frame);
	mlx_hook(frame->win, MOTIONNOTIFY, (1L << 8), mouse_move, frame);
}

#else

static void	init_mlx_hook(t_mlx *frame)
{
	mlx_hook(frame->win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, close_win, frame);
	mlx_hook(frame->win, KEYPRESS, 1L, key_pressed, frame);
	mlx_hook(frame->win, BUTTONPRESS, (1L << 2), mouse_press, frame);
	mlx_hook(frame->win, BUTTONRELEASE, (1L << 3), mouse_release, frame);
	mlx_hook(frame->win, MOTIONNOTIFY, (1L << 8), mouse_move, frame);
}

#endif

int	close_win(t_mlx *param)
{
	if (param->win)
		mlx_destroy_window(param->mlx, param->win);
	mlx_destroy_image(param->mlx, param->img.img_ptr);
	mlx_destroy_image(param->mlx, param->img_move.img_ptr);
	exit(0);
}

int	main(int ac, char **av)
{
	t_mlx	frame;

	if (ac < 2 || set_fractal_type(&frame, ac, av) <= 0)
	{
		printf("fractol <mandelbrot | julia [double, double] | burningship>\n");
		return (-1);
	}
	init_frame(&frame);
	render(&frame);
	init_mlx_hook(&frame);
	mlx_loop(frame.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:38:07 by kanlee            #+#    #+#             */
/*   Updated: 2021/05/30 16:40:32 by kanlee           ###   ########.fr       */
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
	mlx_get_screen_size(frame->mlx, &frame->width, &frame->height);
	if (frame->width > SCREEN_WIDTH)
		frame->width = SCREEN_WIDTH;
	if (frame->height > SCREEN_HEIGHT)
		frame->height = SCREEN_HEIGHT;
	frame->upperleft.x = -2.0;
	frame->upperleft.y = 1.5;
	frame->center = (t_point){-1, 0};
	frame->scale = frame->width / 3;
	frame->it_max = 50;
	frame->upperleft.x = frame->center.x - frame->width / frame->scale / 2;
	frame->upperleft.y = frame->center.y + frame->height / frame->scale / 2;
	frame->win = mlx_new_window(frame->mlx, frame->width, frame->height, "fract-ol");
	frame->img.img_ptr = mlx_new_image(frame->mlx, frame->width, frame->height);
	frame->img.imgdata = mlx_get_data_addr(frame->img.img_ptr,
			&frame->img.bpp, &frame->img.size_line, &frame->img.endian);
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

static void	init_mlx_hook(t_mlx *frame)
{
	mlx_hook(frame->win, CLIENTMESSAGE, WM_DELETE_WINDOW, close_win, frame);
	mlx_hook(frame->win, KEYPRESS, 1L, key_pressed, frame);
//	mlx_hook(frame->win, VISIBILITYNOTIFY, (1L << 16), put_img_to_window, frame);
	mlx_mouse_hook(frame->win, mouse_hook, frame);
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

int	set_fractal_type(t_mlx *frame, char *av)
{
	if (ft_strequ(av, "mandelbrot"))
		frame->type = MANDELBROT;
	else if (ft_strequ(av, "julia"))
		frame->type = JULIASET;
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
	if (ac < 2 || set_fractal_type(&frame, av[1]) == 0) {
		printf("fractol <mandelbrot | julia>\n");
		return (-1);
	}
	printf("%s\n", av[1]);
#endif
	init_frame(&frame);
	render(frame);
	init_mlx_hook(&frame);
	mlx_loop(frame.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:38:07 by kanlee            #+#    #+#             */
/*   Updated: 2021/05/29 10:30:15 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "frame.h"
#include "key.h"
#include "mouse.h"

static void	init_frame(t_mlx *frame)
{
	int	screen_w;
	int	screen_h;

	frame->mlx = mlx_init();
	mlx_get_screen_size(frame->mlx, &screen_w, &screen_h);
	if (screen_w > 1024)
		screen_w = 1024;
	if (screen_h > 768)
		screen_h = 768;
	frame->win = mlx_new_window(frame->mlx, screen_w, screen_h, "fract-ol");
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

int	main(int ac, char **av)
{
	t_mlx frame;

	if (ac < 0)
		perror("argument error");
	init_frame(&frame);
	init_mlx_hook(&frame);
	mlx_loop(frame.mlx);
	return (0);
}

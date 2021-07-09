/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:34:56 by kanlee            #+#    #+#             */
/*   Updated: 2021/07/04 21:39:31 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame.h"
#include "key.h"
#include "utils.h"

static int	key_pressed2(int keycode, t_mlx *frame)
{
	if (keycode == KEY_Z)
	{
		frame->zoom_mode ^= 1;
		img_to_window(frame);
	}
	else if (keycode == KEY_C)
	{
		frame->color_mode = (frame->color_mode + 1) % 4;
		map_colors(frame);
		img_to_window(frame);
	}
	return (0);
}

int			key_pressed(int keycode, t_mlx *frame)
{
	if (keycode == KEY_ESC)
		close_win(frame);
	else if (keycode == KEY_COMMA || keycode == KEY_PERIOD)
	{
		if (keycode == KEY_COMMA)
			frame->it_max /= 1.1;
		else
			frame->it_max = (frame->it_max + 1) * 1.1;
		frame->it_max = clamp_i(frame->it_max, 1, 50000);
		render(frame);
	}
	else if (keycode == KEY_PLUS || keycode == KEY_NP_PLUS
			|| keycode == KEY_MINUS || keycode == KEY_NP_MINUS)
	{
		if (keycode == KEY_PLUS || keycode == KEY_NP_PLUS)
			zoom(frame);
		else
			dezoom(frame);
		render(frame);
	}
	else
		return (key_pressed2(keycode, frame));
	return (0);
}

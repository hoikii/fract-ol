/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:34:56 by kanlee            #+#    #+#             */
/*   Updated: 2021/05/31 00:32:22 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame.h"
#include "key.h"
#include <stdio.h>

int	key_pressed(int keycode, t_mlx *frame)
{
	if (keycode == KEY_ESC)
		close_win(frame);
	else if (keycode == KEY_COMMA || keycode == KEY_PERIOD)
	{
		if (keycode == KEY_COMMA)
			frame->it_max /= 2;
		else
			frame->it_max *= 2;
		if (frame->it_max <= 0)
			frame->it_max = 1;
		render(*frame);
	}
	else if (keycode == KEY_PLUS || keycode == KEY_NP_PLUS
			|| keycode == KEY_MINUS || keycode == KEY_NP_MINUS)
	{
		if (keycode == KEY_PLUS || keycode == KEY_NP_PLUS)
			frame->scale *= 2;
		else
			frame->scale /= 2;
		frame->upperleft.x = frame->center.x - frame->width / frame->scale / 2;
		frame->upperleft.y = frame->center.y + frame->height / frame->scale / 2;
		render(*frame);
	}

	return (0);
}


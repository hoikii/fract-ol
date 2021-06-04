/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:34:56 by kanlee            #+#    #+#             */
/*   Updated: 2021/06/04 23:10:52 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame.h"
#include "key.h"
#include <stdio.h>
#include <math.h>

int	key_pressed(int keycode, t_mlx *frame)
{
	printf("key=%d\n", keycode);
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
		{			frame->scale *= 1.1;
			frame->it_max = pow(1.6, log(frame->scale/200)/log(6)) * 50;
		}
		else
		{
			frame->scale *= 0.9;
			frame->it_max = pow(1.6, log(frame->scale/200)/log(6)) * 50;
		}
		frame->upperleft.x = frame->center.x - IMG_WIDTH / frame->scale / 2;
		frame->upperleft.y = frame->center.y + IMG_HEIGHT / frame->scale / 2;
		render(*frame);
	}

	return (0);
}


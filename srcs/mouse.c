/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:51:17 by kanlee            #+#    #+#             */
/*   Updated: 2021/06/02 17:16:23 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mouse.h"


int	mouse_hook(int btn, int click_x, int click_y, t_mlx *frame)
{
printf("btn=%d, x=%d, y=%d\n", btn, click_x, click_y);
	if (click_y <= 0)
		return (0);
	if (btn == MOUSE_LCLICK)
	{
		frame->center.x = frame->upperleft.x + click_x / frame->scale;
		frame->center.y = frame->upperleft.y - click_y / frame->scale;
	frame->upperleft.x = frame->center.x - frame->width / frame->scale / 2;
	frame->upperleft.y = frame->center.y + frame->height / frame->scale / 2;
		render(*frame);
	}
	else if (btn == MOUSE_WHEELDOWN || btn == MOUSE_WHEELUP)
	{
		frame->center.x = frame->upperleft.x + click_x / frame->scale;
		frame->center.y = frame->upperleft.y - click_y / frame->scale;

		if (btn == MOUSE_WHEELDOWN)
			frame->scale *= 2;
		else
			frame->scale /= 2;
		frame->upperleft.x = frame->center.x - frame->width / frame->scale / 2;
		frame->upperleft.y = frame->center.y + frame->height / frame->scale / 2;

		render(*frame);
	}

	return (0);
}

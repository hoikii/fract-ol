/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:51:17 by kanlee            #+#    #+#             */
/*   Updated: 2021/06/04 05:44:56 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mouse.h"


int	mouse_hook(int btn, int click_x, int click_y, t_mlx *frame)
{
printf("btn=%d, x=%d, y=%d\n", btn, click_x, click_y);
	if (click_y <= 0 || click_x < MENU_WIDTH)
		return (0);
	if (btn == MOUSE_LCLICK)
	{
		frame->center.x = frame->upperleft.x + (click_x - MENU_WIDTH) / frame->scale;
		frame->center.y = frame->upperleft.y - click_y / frame->scale;
	frame->upperleft.x = frame->center.x - IMG_WIDTH / frame->scale / 2;
	frame->upperleft.y = frame->center.y + IMG_HEIGHT / frame->scale / 2;
		render(*frame);
	}
	else if (btn == MOUSE_WHEELDOWN || btn == MOUSE_WHEELUP)
	{
		if (btn == MOUSE_WHEELDOWN)
		{
			frame->center.x = frame->upperleft.x + (click_x - MENU_WIDTH) / frame->scale;
			frame->center.y = frame->upperleft.y - click_y / frame->scale;
			frame->scale *= 1.1;
		}
		else
			frame->scale *= 0.9;
		frame->upperleft.x = frame->center.x - IMG_WIDTH / frame->scale / 2;
		frame->upperleft.y = frame->center.y + IMG_HEIGHT / frame->scale / 2;

		render(*frame);
	}

	return (0);
}

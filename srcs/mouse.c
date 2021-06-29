/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:51:17 by kanlee            #+#    #+#             */
/*   Updated: 2021/06/29 18:04:56 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mouse.h"


int	mouse_press(int btn, int click_x, int click_y, t_mlx *frame)
{
	if (click_y <= 0)
		return (0);
	if (JULIA_CTL_PAD_LEFT < click_x && click_x < JULIA_CTL_PAD_LEFT + frame->julia_ctl_bg.width && JULIA_CTL_PAD_TOP < click_y && click_y < JULIA_CTL_PAD_TOP + frame->julia_ctl_bg.height)
	{
		frame->julia_ctl_clicked = 1;
	int	bg_width;
	int	bg_height;
	t_point ctl_center;

	bg_width = frame->julia_ctl_bg.width;
	bg_height = frame->julia_ctl_bg.height;
	ctl_center = (t_point){JULIA_CTL_PAD_LEFT + bg_width / 2,
		JULIA_CTL_PAD_TOP + bg_height / 2};
	frame->julia_constant.real = (click_x - ctl_center.x) / (bg_width / 2) * JULIA_CONST_LIMIT;
	frame->julia_constant.imag = (ctl_center.y - click_y) / (bg_height / 2) * JULIA_CONST_LIMIT;

	render(frame);

	printf("c = %.2f %.2f\n", frame->julia_constant.real, frame->julia_constant.imag);
		return (0);
	}
	else if (click_x < MENU_WIDTH)
		return (0);
if (btn == MOUSE_LCLICK)
{
	frame->move_from = (t_point){click_x, click_y};
	frame->move_from_vp = frame->center;
	frame->lbtn_pressed = 1;
	return (0);
}
	if (btn == MOUSE_WHEELDOWN || btn == MOUSE_WHEELUP)
	{
		if (btn == MOUSE_WHEELDOWN)
		{
			frame->scale *= 1.1;
			if (frame->zoom_mode)
			{
				frame->center.x = frame->upperleft.x + (click_x - MENU_WIDTH) / frame->scale;
				frame->center.y = frame->upperleft.y - click_y / frame->scale;
			}
		}
		else
			frame->scale *= 0.9;
		frame->upperleft.x = frame->center.x - IMG_WIDTH / frame->scale / 2;
		frame->upperleft.y = frame->center.y + IMG_HEIGHT / frame->scale / 2;

		render(frame);
	}

	return (0);
}

int	mouse_release(int btn, int click_x, int click_y, t_mlx *frame)
{
	if (frame->julia_ctl_clicked)
	{
		frame->julia_ctl_clicked = 0;
		return 0;
	}
	if (btn == MOUSE_LCLICK && frame->lbtn_pressed)
	{
		printf("release: %d %d\n", click_x, click_y);
		int dx = click_x - frame->move_from.x;
		int dy = click_y - frame->move_from.y;
		frame->lbtn_pressed = 0;
		frame->center.x = frame->move_from_vp.x - (int)(click_x - frame->move_from.x) / frame->scale;
		frame->center.y = frame->move_from_vp.y + (int)(click_y - frame->move_from.y) / frame->scale;
		frame->upperleft.x = frame->center.x - IMG_WIDTH / frame->scale / 2;
		frame->upperleft.y = frame->center.y + IMG_HEIGHT / frame->scale / 2;
		render(frame);
	}
	return (0);
}

int	mouse_move(int click_x, int click_y, t_mlx *frame)
{
	if (frame->julia_ctl_clicked)
	{
		click_x = clamp(click_x, JULIA_CTL_PAD_LEFT, JULIA_CTL_PAD_LEFT + frame->julia_ctl_bg.width);
		click_y = clamp(click_y, JULIA_CTL_PAD_TOP, JULIA_CTL_PAD_TOP + frame->julia_ctl_bg.height);
	int	bg_width;
	int	bg_height;
	t_point ctl_center;

	bg_width = frame->julia_ctl_bg.width;
	bg_height = frame->julia_ctl_bg.height;
	ctl_center = (t_point){JULIA_CTL_PAD_LEFT + bg_width / 2,
		JULIA_CTL_PAD_TOP + bg_height / 2};
	frame->julia_constant.real = (click_x - ctl_center.x) / (bg_width / 2) * JULIA_CONST_LIMIT;
	frame->julia_constant.imag = (ctl_center.y - click_y) / (bg_height / 2) * JULIA_CONST_LIMIT;

	render(frame);

	printf("c = %.2f %.2f\n", frame->julia_constant.real, frame->julia_constant.imag);
		return (0);
	}

	int dx = click_x - frame->move_from.x;
	int dy = click_y - frame->move_from.y;
printf("move, x=%d, y=%d\n", dx, dy);
	int i = -1, j;
	while (++i < IMG_HEIGHT)
	{
		j = -1;
		while (++j < IMG_WIDTH)
		{
			int oi = i - dy;
			if (oi >= IMG_HEIGHT) oi = IMG_HEIGHT-1;
			if (oi < 0) oi = 0;
			int oj = j - dx;
			if (oj >= IMG_WIDTH) oj = IMG_WIDTH - 1;
			if (oj < 0) oj = 0;

			int oldpos = oi * frame->img.size_line + oj * frame->img.bpp / 8;
			int pos = i * frame->img.size_line + j * frame->img.bpp / 8;
			frame->img_move.imgdata[pos + 0] = frame->img.imgdata[oldpos + 0];
			frame->img_move.imgdata[pos + 1] = frame->img.imgdata[oldpos + 1];
			frame->img_move.imgdata[pos + 2] = frame->img.imgdata[oldpos + 2];
			frame->img_move.imgdata[pos + 3] = frame->img.imgdata[oldpos + 3];
		}
	}

	img_to_window(frame);

return (0);
}

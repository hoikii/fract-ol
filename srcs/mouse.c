/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:51:17 by kanlee            #+#    #+#             */
/*   Updated: 2021/07/09 18:39:33 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "frame.h"
#include "mouse.h"
#include "utils.h"

int	mouse_press2(int btn, int click_x, int click_y, t_mlx *frame)
{
	if (btn == MOUSE_WHEELDOWN)
	{
		if (frame->zoom_mode)
		{
			frame->center.x
				= frame->upperleft.x + (click_x - MENU_WIDTH) / frame->scale;
			frame->center.y = frame->upperleft.y - click_y / frame->scale;
		}
		zoom(frame);
	}
	else if (btn == MOUSE_WHEELUP)
		dezoom(frame);
	render(frame);
	return (0);
}

int	mouse_press(int btn, int click_x, int click_y, t_mlx *frame)
{
	if (click_y <= 0)
		return (0);
	if (btn == MOUSE_LCLICK && julia_pad_clicked(click_x, click_y, frame))
	{
		frame->julia_ctl_clicked = 1;
		return (update_julia_constant(click_x, click_y, frame));
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
	return (mouse_press2(btn, click_x, click_y, frame));
}

int	mouse_release(int btn, int click_x, int click_y, t_mlx *frame)
{
	int	dx;
	int	dy;

	if (frame->julia_ctl_clicked)
	{
		frame->julia_ctl_clicked = 0;
		return (0);
	}
	if (btn == MOUSE_LCLICK && frame->lbtn_pressed)
	{
		dx = click_x - frame->move_from.x;
		dy = click_y - frame->move_from.y;
		frame->lbtn_pressed = 0;
/*
		frame->center.x = frame->move_from_vp.x -
			(int)(click_x - frame->move_from.x) / frame->scale;
		frame->center.y = frame->move_from_vp.y +
			(int)(click_y - frame->move_from.y) / frame->scale;
*/
		frame->center.x = frame->move_from_vp.x - dx / frame->scale;
		frame->center.y = frame->move_from_vp.y + dy / frame->scale;
		frame->upperleft.x = frame->center.x - IMG_WIDTH / frame->scale / 2;
		frame->upperleft.y = frame->center.y + IMG_HEIGHT / frame->scale / 2;
		render(frame);
	}
	return (0);
}

void	move_image(int click_x, int click_y, t_mlx *frame)
{
	t_point	old;
	t_point	new;
	int		pos;
	int		oldpos;

	new.y = -1;
	while (++new.y < IMG_HEIGHT)
	{
		new.x = -1;
		while (++new.x < IMG_WIDTH)
		{
			old.y = new.y - (click_y - frame->move_from.y);
			old.x = new.x - (click_x - frame->move_from.x);
			old.y = clamp(old.y, 0, IMG_HEIGHT - 1);
			old.x = clamp(old.x, 0, IMG_WIDTH - 1);
			oldpos = old.y * frame->img.size_line + old.x * frame->img.bpp / 8;
			pos = new.y * frame->img.size_line + new.x * frame->img.bpp / 8;
			frame->img_move.imgdata[pos + 0] = frame->img.imgdata[oldpos + 0];
			frame->img_move.imgdata[pos + 1] = frame->img.imgdata[oldpos + 1];
			frame->img_move.imgdata[pos + 2] = frame->img.imgdata[oldpos + 2];
			frame->img_move.imgdata[pos + 3] = frame->img.imgdata[oldpos + 3];
		}
	}
/*
	i = -1;
	while (++i < IMG_HEIGHT)
	{
		j = -1;
		while (++j < IMG_WIDTH)
		{
			oi = i - (click_y - frame->move_from.y);
			oj = j - (click_x - frame->move_from.x);
			oi = clamp_i(oi, 0, IMG_HEIGHT - 1);
			oj = clamp_i(oj, 0, IMG_WIDTH - 1);
			int oldpos = oi * frame->img.size_line + oj * frame->img.bpp / 8;
			int pos = i * frame->img.size_line + j * frame->img.bpp / 8;
			frame->img_move.imgdata[pos + 0] = frame->img.imgdata[oldpos + 0];
			frame->img_move.imgdata[pos + 1] = frame->img.imgdata[oldpos + 1];
			frame->img_move.imgdata[pos + 2] = frame->img.imgdata[oldpos + 2];
			frame->img_move.imgdata[pos + 3] = frame->img.imgdata[oldpos + 3];
		}
	}
*/
	img_to_window(frame);
	return ;
}

int	mouse_move(int click_x, int click_y, t_mlx *frame)
{
	if (frame->julia_ctl_clicked)
	{
		click_x = clamp(click_x, JULIA_CTL_PAD_LEFT,
				JULIA_CTL_PAD_LEFT + frame->julia_ctl_bg.width);
		click_y = clamp(click_y, JULIA_CTL_PAD_TOP,
				JULIA_CTL_PAD_TOP + frame->julia_ctl_bg.height);
		return (update_julia_constant(click_x, click_y, frame));
	}
	move_image(click_x, click_y, frame);
	return (0);
}

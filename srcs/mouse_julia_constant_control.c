/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_julia_constant_control.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:51:17 by kanlee            #+#    #+#             */
/*   Updated: 2021/07/09 18:36:49 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame.h"

int	julia_pad_clicked(int click_x, int click_y, t_mlx *frame)
{
	if (JULIA_CTL_PAD_LEFT < click_x
		&& click_x < JULIA_CTL_PAD_LEFT + frame->julia_ctl_bg.width
		&& JULIA_CTL_PAD_TOP < click_y
		&& click_y < JULIA_CTL_PAD_TOP + frame->julia_ctl_bg.height)
		return (1);
	return (0);
}

int	update_julia_constant(int click_x, int click_y, t_mlx *frame)
{
	int		bg_width;
	int		bg_height;
	t_point	ctl_center;

	bg_width = frame->julia_ctl_bg.width;
	bg_height = frame->julia_ctl_bg.height;
	ctl_center = (t_point){JULIA_CTL_PAD_LEFT + bg_width / 2,
		JULIA_CTL_PAD_TOP + bg_height / 2};
	frame->julia_constant.real
		= (click_x - ctl_center.x) / (bg_width / 2) * JULIA_CONST_LIMIT;
	frame->julia_constant.imag
		= (ctl_center.y - click_y) / (bg_height / 2) * JULIA_CONST_LIMIT;
	render(frame);
	return (0);
}

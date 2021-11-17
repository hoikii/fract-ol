/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 16:09:49 by kanlee            #+#    #+#             */
/*   Updated: 2021/09/29 15:33:16 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame.h"
#include "color.h"

void	zoom(t_mlx *frame)
{
	frame->scale *= 1.1;
	frame->upperleft.x = frame->center.x - IMG_WIDTH / frame->scale / 2;
	frame->upperleft.y = frame->center.y + IMG_HEIGHT / frame->scale / 2;
}

void	dezoom(t_mlx *frame)
{
	frame->scale *= 0.9;
	frame->upperleft.x = frame->center.x - IMG_WIDTH / frame->scale / 2;
	frame->upperleft.y = frame->center.y + IMG_HEIGHT / frame->scale / 2;
}

double	clamp(double d, double min, double max)
{
	if (d < min)
		d = min;
	if (d > max)
		d = max;
	return (d);
}

int	clamp_i(int x, int min, int max)
{
	if (x < min)
		x = min;
	if (x > max)
		x = max;
	return (x);
}

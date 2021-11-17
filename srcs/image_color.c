/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:20:42 by kanlee            #+#    #+#             */
/*   Updated: 2021/09/30 00:15:02 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "frame.h"
#include "../libft/libft.h"
#include <stdio.h>

void	coloring(int i, int j, t_mlx *frame)
{
	double			cc;
	unsigned int	min;
	int				max;
	int				aa;
	int *histogram = frame->histogram;
	long long total_iterations = frame->total_iterations;

	min = frame->min_it;
	max = frame->max_it;
	cc = histogram[frame->iterations_per_pixel[i][j]] / (double)total_iterations;
	if (frame->color_mode == 0)
		put_pxl_to_image(j, i, frame, get_palette(cc * 15));
	else if (frame->color_mode == 1)
	{
		aa = frame->iterations_per_pixel[i][j];
		put_pxl_to_image(j, i, frame, get_palette(aa % 16));
	}
	else if (frame->color_mode == 2)
		put_pxl_to_image(j, i, frame, frame->color_table[(int)(cc * (max - min) + min)]);
	else if (frame->color_mode == 3)
	{
		aa = frame->iterations_per_pixel[i][j];
		if (cc > 0.7)
			put_pxl_to_image(j, i, frame, get_palette(cc * 15));
		else
			put_pxl_to_image(j, i, frame, get_palette((aa * 2) % 16));
		put_pxl_to_image(j, i, frame, (t_color){0, cc * 255, 0});
	}
}

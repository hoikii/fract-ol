/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_histogram.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:20:42 by kanlee            #+#    #+#             */
/*   Updated: 2021/11/21 16:04:57 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "frame.h"
#include "image_color.h"
#include "../libft/libft.h"

static void	check_iteration_range(t_mlx *frame, int *histogram)
{
	int	i;
	int	j;

	frame->min_it = -1;
	frame->max_it = 0;
	i = -1;
	while (++i < IMG_HEIGHT)
	{
		j = -1;
		while (++j < IMG_WIDTH)
		{
			histogram[frame->iterations_per_pixel[i][j]]++;
			if (frame->min_it > (unsigned int)frame->iterations_per_pixel[i][j])
				frame->min_it = frame->iterations_per_pixel[i][j];
			if (frame->max_it < frame->iterations_per_pixel[i][j])
				frame->max_it = frame->iterations_per_pixel[i][j];
		}
	}
}

void	set_gradiation_table(t_mlx *frame, int *histogram, t_color *color_table)
{
	int		i;
	int		it_range;
	t_color	rgb_start;
	t_color	rgb_end;

	check_iteration_range(frame, histogram);
	rgb_start = (t_color){250, 100, 0};
	rgb_end = (t_color){255, 255, 255};
	it_range = frame->max_it - frame->min_it;
	i = -1;
	while (++i < it_range)
	{
		color_table[i + frame->min_it].r = rgb_start.r
			+ (rgb_end.r - rgb_start.r) * (double)(i) / (it_range);
		color_table[i + frame->min_it].g = rgb_start.g
			+ (rgb_end.g - rgb_start.g) * (double)(i) / (it_range);
		color_table[i + frame->min_it].b = rgb_start.b
			+ (rgb_end.b - rgb_start.b) * (double)(i) / (it_range);
	}
}

static int	init_color_table(t_mlx *frame)
{
	int	i;

	frame->histogram = malloc(sizeof(int) * (frame->it_max + 1));
	frame->color_table = malloc(sizeof(t_color) * (frame->it_max + 1));
	if (!frame->histogram || !frame->color_table)
		return (0);
	ft_bzero(frame->histogram, sizeof(int) * (frame->it_max + 1));
	set_gradiation_table(frame, frame->histogram, frame->color_table);
	frame->total_iterations = 0;
	i = -1;
	while (++i <= frame->it_max)
	{
		frame->total_iterations += frame->histogram[i];
		frame->histogram[i] = frame->total_iterations;
	}
	return (1);
}

void	map_colors(t_mlx *frame)
{
	int			i;
	int			j;

	if (!init_color_table(frame))
		return ;
	i = -1;
	while (++i < IMG_HEIGHT)
	{
		j = -1;
		while (++j < IMG_WIDTH)
		{
			if (frame->iterations_per_pixel[i][j] == frame->it_max)
				put_pxl_to_image(j, i, frame, (t_color){0, 0, 0});
			else
				coloring(i, j, frame);
		}
	}
	free(frame->histogram);
	free(frame->color_table);
}

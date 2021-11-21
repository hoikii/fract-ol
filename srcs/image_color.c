/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:20:42 by kanlee            #+#    #+#             */
/*   Updated: 2021/11/21 15:54:47 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "frame.h"
#include "../libft/libft.h"

static void	color_histogram(int i, int j, t_mlx *frame)
{
	int			*histogram;
	long long	total_iterations;
	double		palette_idx;

	histogram = frame->histogram;
	total_iterations = frame->total_iterations;
	palette_idx = histogram[frame->iterations_per_pixel[i][j]]
		/ (double)total_iterations * 15;
	put_pxl_to_image(j, i, frame, get_palette(palette_idx));
}

static void	color_repeat(int i, int j, t_mlx *frame)
{
	int	palette_idx;

	palette_idx = frame->iterations_per_pixel[i][j] % 16;
	put_pxl_to_image(j, i, frame, get_palette(palette_idx));
}

static void	color_gradiation(int i, int j, t_mlx *frame)
{
	unsigned int	min;
	int				max;
	int				*histogram;
	long long		total_iterations;
	double			palette_idx;

	min = frame->min_it;
	max = frame->max_it;
	histogram = frame->histogram;
	total_iterations = frame->total_iterations;
	palette_idx = histogram[frame->iterations_per_pixel[i][j]]
		/ (double)total_iterations;
	put_pxl_to_image(j, i, frame, frame->color_table[
		(int)(palette_idx * (max - min) + min)]);
}

static void	color_green(int i, int j, t_mlx *frame)
{
	int			*histogram;
	long long	total_iterations;
	double		palette_idx;

	histogram = frame->histogram;
	total_iterations = frame->total_iterations;
	palette_idx = histogram[frame->iterations_per_pixel[i][j]]
		/ (double)total_iterations;
	put_pxl_to_image(j, i, frame, (t_color){0, palette_idx * 255, 0});
}

void	coloring(int i, int j, t_mlx *frame)
{
	int	mode;

	mode = frame->color_mode;
	if (mode == COLOR_PALETTE_HISTOGRAM)
		color_histogram(i, j, frame);
	else if (mode == COLOR_PALETTE_REPEAT)
		color_repeat(i, j, frame);
	else if (mode == COLOR_GRADIATION)
		color_gradiation(i, j, frame);
	else if (mode == COLOR_GREEN)
		color_green(i, j, frame);
}

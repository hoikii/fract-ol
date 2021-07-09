/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:20:42 by kanlee            #+#    #+#             */
/*   Updated: 2021/07/09 17:28:52 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "frame.h"
#include "../libft/libft.h"
#include <stdio.h>

void	prn_histogram(int *histogram, int it_max);

static void	put_julia_constant_ctl(t_mlx *frame)
{
	int		bg_width;
	int		bg_height;
	int		btn_width;
	t_point	ctl_center;

	bg_width = frame->julia_ctl_bg.width;
	bg_height = frame->julia_ctl_bg.height;
	ctl_center = (t_point){JULIA_CTL_PAD_LEFT + bg_width / 2,
		JULIA_CTL_PAD_TOP + bg_height / 2};
	btn_width = frame->julia_ctl_btn.width;
	mlx_put_image_to_window(frame->mlx, frame->win, frame->julia_ctl_bg.img_ptr,
		JULIA_CTL_PAD_LEFT, JULIA_CTL_PAD_TOP);
	mlx_put_image_to_window(frame->mlx, frame->win,
		frame->julia_ctl_btn.img_ptr,
		ctl_center.x + frame->julia_constant.real / JULIA_CONST_LIMIT
		* bg_width / 2 - btn_width / 2,
		ctl_center.y - frame->julia_constant.imag / JULIA_CONST_LIMIT
		* bg_height / 2 - btn_width / 2);
}

static void	str_join_put(t_mlx *frame, char *msg, char *data, int y)
{
	char	*str;

	str = ft_strjoin(msg, data);
	free(data);
	mlx_string_put(frame->mlx, frame->win, 10, y, 0x00ffffff, str);
	free(str);
}

static void	put_info(t_mlx *frame)
{
	char	*msg;

	mlx_put_image_to_window(frame->mlx, frame->win, frame->menu.img_ptr, 0, 0);
	str_join_put(frame, "max_iterations: ", ft_itoa(frame->it_max), 20);
	str_join_put(frame, "scale: ",
		ft_ftoa(frame->scale / (IMG_WIDTH / 3), 6), 40);
	str_join_put(frame, "1px = ", ft_ftoa(1 / frame->scale, 16), 60);
	str_join_put(frame, "center x: ", ft_ftoa(frame->center.x, 12), 80);
	str_join_put(frame, "center y: ", ft_ftoa(frame->center.y, 12), 100);
	if (frame->zoom_mode)
		msg = "zoom mode: follow mouse position";
	else
		msg = "zoom mode: fixed";
	mlx_string_put(frame->mlx, frame->win, 10, 120, 0x00ffffff, msg);
	mlx_string_put(frame->mlx, frame->win, 10, 160, 0x00ffffff,
		"julia constant");
	str_join_put(frame, "real part = ",
		ft_ftoa(frame->julia_constant.real, 5), 175);
	str_join_put(frame, "imaginary = ",
		ft_ftoa(frame->julia_constant.imag, 5), 190);
	if (frame->type == JULIASET)
		put_julia_constant_ctl(frame);
}

int		img_to_window(t_mlx *frame)
{
	if (frame->lbtn_pressed)
		mlx_put_image_to_window(frame->mlx, frame->win,
			frame->img_move.img_ptr, MENU_WIDTH, 0);
	else
		mlx_put_image_to_window(frame->mlx, frame->win,
			frame->img.img_ptr, MENU_WIDTH, 0);
	put_info(frame);
	return (0);
}

void	put_pxl_to_image(int x, int y, t_mlx *frame, t_color rgb)
{
	char	*imgdata;
	int		pos;
	int		color;

	color = mlx_get_color_value(frame->mlx, rgb_to_int(rgb));
	imgdata = frame->img.imgdata;
	pos = y * frame->img.size_line + x * frame->img.bpp / 8;
	*(unsigned int *)(&imgdata[pos]) = color;
}

void	calc_histogram(t_mlx *frame, int *histogram, t_color *color_table)
{
	int		i;
	int		j;
	int		it_range;
	t_color	rgb_start;
	t_color	rgb_end;

	frame->min_it = -1;
	frame->max_it = 0;
	i = -1;
	while (++i < IMG_HEIGHT)
	{
		j = -1;
		while (++j < IMG_WIDTH)
		{
			histogram[frame->iterations_per_pixel[i][j]]++;
			if (frame->min_it > frame->iterations_per_pixel[i][j])
				frame->min_it = frame->iterations_per_pixel[i][j];
			if (frame->max_it < frame->iterations_per_pixel[i][j])
				frame->max_it = frame->iterations_per_pixel[i][j];
		}
	}

	rgb_start = (t_color){250, 100, 0};
	rgb_end = (t_color){255, 255, 255};
	it_range = frame->max_it - frame->min_it;
	i = -1;
	while (++i < it_range)
	{
		color_table[i + frame->min_it].r = rgb_start.r +
			(rgb_end.r - rgb_start.r) * (double)(i) / (it_range);
		color_table[i + frame->min_it].g = rgb_start.g +
			(rgb_end.g - rgb_start.g) * (double)(i) / (it_range);
		color_table[i + frame->min_it].b = rgb_start.b +
			(rgb_end.b - rgb_start.b) * (double)(i) / (it_range);
	}
}

void	coloring(int i, int j, t_mlx *frame, int *histogram, t_color *color_table, long long total_iterations)
{
	double cc;
	unsigned int min;
	int max;
	int aa;

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
		put_pxl_to_image(j, i, frame, color_table[(int)(cc * (max - min) + min)]);
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

void	map_colors(t_mlx *frame)
{
	int		*histogram;
	long long	total_iterations;
	int i, j;
	t_color	*color_table;

	histogram = malloc(sizeof(int) * (frame->it_max + 1));
	if (!histogram)
		return ;
	ft_bzero(histogram, sizeof(int) * (frame->it_max + 1));
	color_table = malloc(sizeof(t_color) * (frame->it_max + 1));
	if (!color_table)
		return ;
	calc_histogram(frame, histogram, color_table);

	total_iterations = 0;
	i = -1;
	while (++i <= frame->it_max)
	{
		total_iterations += histogram[i];
		histogram[i] = total_iterations;
	}

	i = -1;
	while (++i < IMG_HEIGHT)
	{
		j = -1;
		while (++j < IMG_WIDTH)
		{
			if (frame->iterations_per_pixel[i][j] == frame->it_max)
			{
				put_pxl_to_image(j, i, frame, (t_color){0, 0, 0});
				continue ;
			}
			coloring(i, j, frame, histogram, color_table, total_iterations);
		}
	}
	free(histogram);
	free(color_table);
}

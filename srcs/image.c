/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:20:42 by kanlee            #+#    #+#             */
/*   Updated: 2021/06/27 20:35:34 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "frame.h"
#include "../libft/libft.h"
#include <stdio.h>

void prn_histogram(int *histogram, int it_max);

static void	put_info(t_mlx *frame)
{
	char *msg;

	mlx_put_image_to_window(frame->mlx, frame->win, frame->menu.img_ptr, 0, 0);
	msg = ft_strjoin("max_iterations: ", ft_itoa(frame->it_max));
	mlx_string_put(frame->mlx, frame->win, 10, 20, 0x00ffffff, msg);
	free(msg);
	msg = ft_strjoin("scale: ", ft_ftoa(frame->scale / (IMG_WIDTH / 3), 6));
	mlx_string_put(frame->mlx, frame->win, 10, 40, 0x00ffffff, msg);
	free(msg);
	msg = ft_strjoin("1px = ", ft_ftoa(1/frame->scale, 22));
	mlx_string_put(frame->mlx, frame->win, 10, 60, 0x00ffffff, msg);
	free(msg);
//	mlx_string_put(frame->mlx, frame->win, 10, 60, 0x00ffffff, "plot range");
//	msg = ft_strjoin(ft_ftoa(frame->center.x - IMG_WIDTH / frame->scale / 2, 6),
//			   " <= x <= ");
//	msg = ft_strjoin(msg, ft_ftoa(frame->center.x + IMG_WIDTH / frame->scale / 2, 6));
	msg = ft_strjoin("center x: ", ft_ftoa(frame->center.x, 12));
	mlx_string_put(frame->mlx, frame->win, 10, 80, 0x00ffffff, msg);
	free(msg);
	msg = ft_strjoin("center y: ", ft_ftoa(frame->center.y, 12));
	mlx_string_put(frame->mlx, frame->win, 10, 100, 0x00ffffff, msg);
	free(msg);
	if (frame->zoom_mode)
		msg = "zoom mode: follow mouse position";
	else
		msg = "zoom mode: fixed";
	mlx_string_put(frame->mlx, frame->win, 10, 120, 0x00ffffff, msg);

//	free(msg);
}

void	img_to_window(t_mlx *frame)
{
	if (frame->lbtn_pressed)
		mlx_put_image_to_window(frame->mlx, frame->win, frame->img_move.img_ptr, MENU_WIDTH, 0);
	else
		mlx_put_image_to_window(frame->mlx, frame->win, frame->img.img_ptr, MENU_WIDTH, 0);
	put_info(frame);

}

void	put_pxl_to_image(int x, int y, t_mlx *frame, t_color rgb)
{
	char *imgdata;
	int pos;
	int color;

	color = mlx_get_color_value(frame->mlx, rgb_to_int(rgb));
	imgdata = frame->img.imgdata;
	pos = y * frame->img.size_line + x * frame->img.bpp / 8;
	*(unsigned int *)(&imgdata[pos]) = color;
}

void	map_colors(t_mlx *frame)
{

	int		*histogram;
	long long	total_iterations;
	int i, j, k;
	double cc = 0;
	histogram = malloc(sizeof(int) * (frame->it_max + 1));
	if (!histogram)
		return ;
	ft_bzero(histogram, sizeof(int) * (frame->it_max + 1));

	unsigned int min = -1;
	int max = 0;
	i = -1;
	while (++i < IMG_HEIGHT)
	{
		j = -1;
		while (++j < IMG_WIDTH)
		{
			histogram[frame->iterations_per_pixel[i][j]]++;
			if (min > frame->iterations_per_pixel[i][j])
				min = frame->iterations_per_pixel[i][j];
			if (max < frame->iterations_per_pixel[i][j])
				max = frame->iterations_per_pixel[i][j];
		}

	}

		
int *hist = malloc(sizeof(int) * (frame->it_max + 1));
	total_iterations = 0;
	i = -1;
	while (++i <= frame->it_max)
	{
		hist[i] = histogram[i];
		total_iterations += histogram[i];
		histogram[i] = total_iterations;
	}

	t_color rgb_start = (t_color){250, 100, 0};
	t_color rgb_end = (t_color){255,255,255};
	t_color *color_table = malloc(sizeof(t_color) * (frame->it_max + 1));
	for (int q=min; q < max; q++)
	{
color_table[q].r = rgb_start.r + (rgb_end.r - rgb_start.r) * (double)(q-min) / (max-min);
color_table[q].g = rgb_start.g + (rgb_end.g - rgb_start.g) * (double)(q-min) / (max-min);
color_table[q].b = rgb_start.b + (rgb_end.b - rgb_start.b) * (double)(q-min) / (max-min);
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
			k = -1;
//			cc = 0;
//			while (++k <= frame->iterations_per_pixel[i][j])
//				cc += histogram[k];
//			cc /= total_iterations;
			cc = histogram[frame->iterations_per_pixel[i][j]] / (double)total_iterations;
			if (frame->color_mode == 0)
				put_pxl_to_image(j, i, frame, get_palette(cc * 15));
			else if (frame->color_mode == 1)
			{
				int aa = frame->iterations_per_pixel[i][j];
				put_pxl_to_image(j, i, frame, get_palette(aa % 16));
			}
			else if (frame->color_mode == 2)
				put_pxl_to_image(j, i, frame, color_table[(int)(cc * (max-min)+min)]);
			else if (frame->color_mode == 3)
			{
				int aa = frame->iterations_per_pixel[i][j];
				if (cc < 0.7)
					put_pxl_to_image(j, i, frame, get_palette(cc * 15));
				else
					put_pxl_to_image(j, i, frame, get_palette((aa*2) % 16));
			}

		}
	}
	prn_histogram(hist, frame->it_max);
printf("cneter = %lf, %lf\n", frame->center.x, frame->center.y);
	free(histogram);
	free(color_table);
}

void prn_histogram(int *histogram, int it_max)
{
	int i;
	int j;
	long long total;
	int max;


	int hist[11] = {0,};

	system("clear");
	i = -1;
	total = 0;
	max = 0;
	while (++i <= it_max)
	{
		total += histogram[i];
		hist[(int)((double)i / it_max * 10)] += histogram[i];
		if (max < histogram[i])
			max = histogram[i];
	}
	i = 19;
	while (i >= 0)
	{
		j = -1;
		while (++j < 11)
		{
			printf("   %c   ", (hist[j] / (double)total * 100 > i) ? '.' : ' ');
		}
		printf("\n");
		i -= 1;
	}
	j = -1;
	while (++j < 11)
		printf("=======");
	printf("\n");
	j = -1;
	while (++j < 11)
		printf("  %2d   ", j);
	printf("\n");
	j = -1;
	while (++j < 11)
		printf(" %4.1lf%% ", hist[j] / (double)total * 100);
	max=0;
	for (int q=0; q<=6; q++)
		max += hist[q];
	max += hist[10];
	printf("\ntotal: %lld\n0to6: %.1f%%\n", total, max / (double)total * 100);

}

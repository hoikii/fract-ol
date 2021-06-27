/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 16:38:51 by kanlee            #+#    #+#             */
/*   Updated: 2021/06/27 20:35:52 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "frame.h"

void	render_single(t_mlx *frame)
{
	int i;
	int j;

	if (frame->type == KOCH_SNOWFLAKE)
		return (koch_calc(frame));
	i = -1;
	while (++i < IMG_HEIGHT)
	{
		j = -1;
		while (++j < IMG_WIDTH)
		{
			if (frame->type == MANDELBROT)
				mandelbrot_calc(j, i, frame);
			else if (frame->type == JULIASET)
				julia_calc(j, i, frame);
		}
	}
//	img_to_window(frame);
}


void	*render_per_thread(void *arg)
{
	t_mlx	*frame = ((t_threads *)arg)->frame;
	int		tid = ((t_threads *)arg)->tid;
	int i;
	int j;
	int sign;
	int pos;

//	if (frame->type == KOCH_SNOWFLAKE)
//		return (koch_calc(frame));
	i = 0;
	sign = 1;
#if 1
	while (i < IMG_HEIGHT)
	{
		pos = IMG_HEIGHT / 2 + i * sign;
		if (sign > 0)
			i++;
		sign *= -1;
#else
	while (i++ < IMG_HEIGHT)
	{
		pos = i-1;
#endif
		if (i % THREADS_CNT != tid || pos < 0 || pos >= IMG_HEIGHT)
			continue;
		j = -1;
		while (++j < IMG_WIDTH)
		{
			if (frame->type == MANDELBROT)
				mandelbrot_calc(j, pos, frame);
			else if (frame->type == JULIASET)
				julia_calc(j, pos, frame);
		}
	if (tid == 0 && i % 1 == 0)
		img_to_window(frame);
	}
//	img_to_window(frame);
	pthread_exit(NULL);
}

void render_thread(t_mlx *frame)
{
	pthread_t	threads[THREADS_CNT];
	t_threads	arg[THREADS_CNT];
	int			i;

	i = -1;
	while (++i < THREADS_CNT)
	{
		arg[i].tid = i;
		arg[i].frame = frame;
		pthread_create(&threads[i], NULL, &render_per_thread, &arg[i]);
	}
	while (--i >= 0)
		pthread_join(threads[i], NULL);
}

void	render(t_mlx *frame)
{
	if (BONUS != 1 || THREADS_CNT <= 1)
		render_single(frame);
	else
		render_thread(frame);
	map_colors(frame);
	img_to_window(frame);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 16:38:51 by kanlee            #+#    #+#             */
/*   Updated: 2021/07/09 18:37:35 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "frame.h"

static void	render_single(t_mlx *frame)
{
	int	i;
	int	j;

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

#ifdef BONUS

static void	*render_per_thread(void *arg)
{
	t_mlx	*frame;
	int		tid;
	int		i;
	int		j;

	frame = ((t_threads *)arg)->frame;
	tid = ((t_threads *)arg)->tid;
	i = -1;
	while (++i < IMG_HEIGHT)
	{
		if (i % THREADS_CNT != tid)
			continue ;
		j = -1;
		while (++j < IMG_WIDTH)
		{
			if (frame->type == MANDELBROT)
				mandelbrot_calc(j, i, frame);
			else if (frame->type == JULIASET)
				julia_calc(j, i, frame);
		}
		if (tid == 0 && i % 1 == 0)
			img_to_window(frame);
	}
//	img_to_window(frame);
	pthread_exit(NULL);
}

static void	render_multithread(t_mlx *frame)
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
		render_multithread(frame);
	map_colors(frame);
	img_to_window(frame);
}

#else

void	render(t_mlx *frame)
{
	render_single(frame);
	map_colors(frame);
	img_to_window(frame);
}

#endif

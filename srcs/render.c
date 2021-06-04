/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 16:38:51 by kanlee            #+#    #+#             */
/*   Updated: 2021/06/03 15:59:02 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "frame.h"

void	render(t_mlx frame)
{
	int i;
	int j;

	if (frame.type == KOCH_SNOWFLAKE)
		return (koch_calc(frame));
	i = -1;
	while (++i < IMG_HEIGHT)
	{
		j = -1;
		while (++j < IMG_WIDTH)
		{
			if (frame.type == MANDELBROT)
				mandelbrot_calc(j, i, frame);
			else if (frame.type == JULIASET)
				julia_calc(j, i, frame);
		}
	}
	img_to_window(frame);
}

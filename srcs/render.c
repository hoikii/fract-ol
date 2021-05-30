/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 16:38:51 by kanlee            #+#    #+#             */
/*   Updated: 2021/05/30 16:53:13 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "frame.h"
#include "../libft/libft.h"

void	render(t_mlx frame)
{
	int i;
	int j;
	char *msg;

	i = -1;
	while (++i < frame.height)
	{
		j = -1;
		while (++j < frame.width)
		{
			if (frame.type == MANDELBROT)
				mandelbrot_calc(j, i, frame);
			else if (frame.type == JULIASET)
				julia_calc(j, i, frame);
		}
	}
	msg = ft_strjoin("max_iterations: ", ft_itoa(frame.it_max));
	mlx_put_image_to_window(frame.mlx, frame.win, frame.img.img_ptr, 0, 0);
	mlx_string_put(frame.mlx, frame.win, 11, 21, 0, msg);
	mlx_string_put(frame.mlx, frame.win, 10, 20, 0x00ffffff, msg);
	free(msg);
}

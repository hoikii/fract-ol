/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 13:28:35 by kanlee            #+#    #+#             */
/*   Updated: 2021/05/30 15:47:11 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame.h"
#include "color.h"
#include "../libft/libft.h"
#include <stdio.h>

int		is_mandelbrot(t_complex p, int it_max)
{
	t_complex	z = {0, 0};
	int			it;

	it = -1;
	while (++it < it_max)
	{
		z = c_add(c_square(z), p);
		if (c_abs_squared(z) >= 4.0)
			return (it);
	}
	return (0);
}

void	mandelbrot_calc(int screen_x, int screen_y, t_mlx frame)
{
	t_complex vp;
	char *imgdata;
	t_color rgb;
	int pos;
	int it;

	vp.real = frame.upperleft.x + screen_x / frame.scale;
	vp.imag = frame.upperleft.y - screen_y / frame.scale;

	it = is_mandelbrot(vp, frame.it_max);
	if (it)
	{
/*
		double quotient = (double)it / frame.it_max;
		int g = clamp(quotient * 255, 0, 255);
//		rgb = (t_color){0, 1, 0};
//		rgb.g = clamp(quotient * 255, 0, 255);
		if (quotient > 0.5)
			rgb = (t_color){g, 255, g};
		else
			rgb = (t_color){0, g, 0};
*/
		rgb = get_palette(it % 16);
		put_pxl_to_image(screen_x, screen_y, frame, rgb);
	}
	else
		put_pxl_to_image(screen_x, screen_y, frame, (t_color){0, 0, 0});

}

void	fractal_calc(t_mlx frame)
{
	int i;
	int j;
	char *msg;

	i = -1;
	while (++i < frame.height)
	{
		j = -1;
		while (++j < frame.width)
			mandelbrot_calc(j, i, frame);
	}
	msg = ft_strjoin("max_iterations: ", ft_itoa(frame.it_max));
	mlx_put_image_to_window(frame.mlx, frame.win, frame.img.img_ptr, 0, 0);
	mlx_string_put(frame.mlx, frame.win, 11, 21, 0, msg);
	mlx_string_put(frame.mlx, frame.win, 10, 20, 0x00ffffff, msg);
	free(msg);
}

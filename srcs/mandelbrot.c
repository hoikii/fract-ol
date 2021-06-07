/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 13:28:35 by kanlee            #+#    #+#             */
/*   Updated: 2021/06/07 19:04:34 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "frame.h"
#include "color.h"

/* With unoptimized version, We need five multiplications per each iterations.
 * (three for znext = z^2 + c, two for checking escape condition)
 * This can be reduced to three by caching (z.real)^2 and (z.imaginary)^2.
 *
 * znext.real = (z.real)^2 - (z.imag)^2 + c.real
 * znext.imag = 2 * z.real * z.imag + c.imag
 * escape if |znext|^2 = (z.real)^2 + (z.imag)^2 >= 2^2
*/

#if 0
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
#else

int		is_mandelbrot(t_complex c, int it_max)
{
	t_complex	z = {0, 0};
	int			it;
	double		zr_squared;
	double		zi_squared;

	zr_squared = 0;
	zi_squared = 0;
	it = -1;
	while (++it < it_max)
	{
		z.imag = (z.real + z.real) * z.imag + c.imag;
		z.real = zr_squared - zi_squared + c.real;
		zr_squared = z.real * z.real;
		zi_squared = z.imag * z.imag;
		if (zr_squared + zi_squared >= 4.0)
			return (it);
	}
	return (it);
}
#endif

int cclamp(double n) { if (n < 0) n = 0; if (n > 255) n = 255; return n;}

void	mandelbrot_calc(int screen_x, int screen_y, t_mlx *frame)
{
	t_complex vp;
	char *imgdata;
	t_color rgb;
	int pos;
	int it;

	vp.real = frame->upperleft.x + screen_x / frame->scale;
	vp.imag = frame->upperleft.y - screen_y / frame->scale;

	it = is_mandelbrot(vp, frame->it_max);
	if (it != frame->it_max)
	{
//			if (it > 0)
//				it = log(it) / log(frame->it_max) * 16;
			it = (double)it / frame->it_max * 16;
			rgb = get_palette(it);
//		else {
//			it = it / (double)frame->it_max * 100;
//			rgb = (t_color){cclamp(255-it * 2), cclamp(255-it*6), cclamp(255-it*1)};
//			rgb = (t_color){cclamp(255-it * 6), cclamp(255-it*2), cclamp(255-it*10)};
//		}
	put_pxl_to_image(screen_x, screen_y, frame, rgb);
	}
	else
		put_pxl_to_image(screen_x, screen_y, frame, (t_color){0, 0, 0});

}

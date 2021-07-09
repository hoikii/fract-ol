/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 13:28:35 by kanlee            #+#    #+#             */
/*   Updated: 2021/07/01 22:20:59 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "frame.h"
#include "color.h"

#define ZERO 0.0000000001

typedef struct	s_counter {
	t_complex	z_old;
	int			counter;
	int			counter_limit;
}				t_counter;

/*
** With unoptimized version, We need five multiplications per each iterations.
** (three for znext = z^2 + c, two for checking escape condition)
** This can be reduced to three by caching (z.real)^2 and (z.imaginary)^2.
**
** znext.real = (z.real)^2 - (z.imag)^2 + c.real
** znext.imag = 2 * z.real * z.imag + c.imag
** escape if |znext|^2 = (z.real)^2 + (z.imag)^2 >= 2^2
*/

/*
**int		is_mandelbrot(t_complex p, int it_max)
**{
**	t_complex	z;
**	int			it;
**
**	z = (t_complex){0, 0};
**	it = -1;
**	while (++it < it_max)
**	{
**		z = c_add(c_square(z), p);
**		if (c_abs_squared(z) >= 4.0)
**			return (it);
**	}
**	return (0);
**}
*/

static int		detect_cycle(t_complex z, t_counter *counter)
{
	if (fabs(z.real - counter->z_old.real) < ZERO
		&& fabs(z.imag - counter->z_old.imag) < ZERO)
		return (1);
	if (counter->counter == counter->counter_limit)
	{
		counter->z_old = z;
		counter->counter = 0;
		counter->counter_limit *= 2;
	}
	counter->counter++;
	return (0);
}

int				is_mandelbrot(t_complex c, int it_max)
{
	t_complex	z;
	int			it;
	double		zr_squared;
	double		zi_squared;
	t_counter	counter;

	z = (t_complex){0, 0};
	zr_squared = 0;
	zi_squared = 0;
	it = -1;
	counter.z_old = (t_complex){0, 0};
	counter.counter = 0;
	counter.counter_limit = 2;
	while (++it < it_max)
	{
		z.imag = (z.real + z.real) * z.imag + c.imag;
		z.real = zr_squared - zi_squared + c.real;
		zr_squared = z.real * z.real;
		zi_squared = z.imag * z.imag;
		if (zr_squared + zi_squared >= 4.0)
			return (it);
		if (detect_cycle(z, &counter))
			return (it_max);
	}
	return (it);
}

void			mandelbrot_calc(int screen_x, int screen_y, t_mlx *frame)
{
	t_complex	vp;
	char		*imgdata;
	t_color		rgb;
	int			pos;
	int			it;

	vp.real = frame->upperleft.x + screen_x / frame->scale;
	vp.imag = frame->upperleft.y - screen_y / frame->scale;
	it = is_mandelbrot(vp, frame->it_max);
	frame->iterations_per_pixel[screen_y][screen_x] = it;
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:50:53 by kanlee            #+#    #+#             */
/*   Updated: 2021/11/21 18:34:04 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "frame.h"

int	is_bship(t_complex c, int it_max)
{
	t_complex	z;
	t_complex znext;
	int			it;

	z = (t_complex){0, 0};
	it = -1;
	while (++it < it_max)
	{
		znext.real = z.real * z.real - z.imag * z.imag + c.real;
		znext.imag = 2 * fabs(z.real * z.imag) + c.imag;
		z = znext;
		if (c_abs_squared(z) >= 4.0)
			return (it);
	}
	return (0);
}

void	bship_calc(int screen_x, int screen_y, t_mlx *frame)
{
	t_complex	vp;
	int			it;

	vp.real = frame->upperleft.x + screen_x / frame->scale;
	vp.imag = frame->upperleft.y - screen_y / frame->scale;
	it = is_bship(vp, frame->it_max);
	frame->iterations_per_pixel[screen_y][screen_x] = it;
	return ;
}

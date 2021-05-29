/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 16:24:43 by kanlee            #+#    #+#             */
/*   Updated: 2021/05/29 16:41:44 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

t_complex	c_add(t_complex c1, t_complex c2)
{
	t_complex	c;

	c.real = c1.real + c2.real;
	c.imag = c1.imag + c2.imag;
	return (c);
}

t_complex	c_sub(t_complex c1, t_complex c2)
{
	t_complex	c;

	c.real = c1.real - c2.real;
	c.imag = c1.imag - c2.imag;
	return (c);
}

t_complex	c_square(t_complex c1)
{
	t_complex c;

	c.real = c1.real * c1.real - c1.imag * c1.imag;
	c.imag = 2 * c1.real * c1.imag;
	return (c);
}

double	c_abs_squared(t_complex c1)
{
	return (c1.real * c1.real + c1.imag * c1.imag);
}

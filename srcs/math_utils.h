/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 16:25:24 by kanlee            #+#    #+#             */
/*   Updated: 2021/06/30 18:20:18 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

typedef struct	s_complex {
	double	real;
	double	imag;
}				t_complex;

t_complex		c_add(t_complex c1, t_complex c2);
t_complex		c_sub(t_complex c1, t_complex c2);
t_complex		c_square(t_complex c1);
double			c_abs_squared(t_complex c1);

#endif

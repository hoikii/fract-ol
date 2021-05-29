/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 22:59:54 by kanlee            #+#    #+#             */
/*   Updated: 2021/05/29 23:17:30 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color {
	int r;
	int g;
	int b;
} t_color;

int	rgb_to_int(t_color rgb);
int	clamp(int x, int min, int max);

#endif

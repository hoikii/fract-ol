/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 22:59:54 by kanlee            #+#    #+#             */
/*   Updated: 2021/07/09 18:33:39 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color {
	int	r;
	int	g;
	int	b;
}				t_color;

int		rgb_to_int(t_color rgb);
t_color	get_palette(int i);

#endif

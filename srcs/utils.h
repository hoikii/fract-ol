/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 23:00:27 by kanlee            #+#    #+#             */
/*   Updated: 2021/07/09 17:25:08 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "frame.h"

void	zoom(t_mlx *frame);
void	dezoom(t_mlx *frame);
double	clamp(double d, double min, double max);
int		clamp_i(int x, int min, int max);

#endif

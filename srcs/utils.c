/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 16:09:49 by kanlee            #+#    #+#             */
/*   Updated: 2021/05/29 22:59:39 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame.h"
#include "color.h"

void	put_pxl_to_image(int x, int y, t_mlx frame, t_color rgb)
{
	char *imgdata;
	int pos;
	int color;

	color = mlx_get_color_value(frame.mlx, rgb_to_int(rgb));
	imgdata = frame.img.imgdata;
	pos = y * frame.img.size_line + x * frame.img.bpp / 8;
	*(unsigned int *)(&imgdata[pos]) = color;
}


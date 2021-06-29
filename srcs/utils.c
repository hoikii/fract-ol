/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 16:09:49 by kanlee            #+#    #+#             */
/*   Updated: 2021/06/29 23:04:18 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame.h"
#include "color.h"

void	zoom(t_mlx *frame)
{
	frame->scale *= 1.1;
//	frame->it_max = pow(1.6, log(frame->scale/200)/log(6)) * 50;
	frame->upperleft.x = frame->center.x - IMG_WIDTH / frame->scale / 2;
	frame->upperleft.y = frame->center.y + IMG_HEIGHT / frame->scale / 2;
}

void	dezoom(t_mlx *frame)
{
	frame->scale *= 0.9;
//	frame->it_max = pow(1.6, log(frame->scale/200)/log(6)) * 50;
	frame->upperleft.x = frame->center.x - IMG_WIDTH / frame->scale / 2;
	frame->upperleft.y = frame->center.y + IMG_HEIGHT / frame->scale / 2;
}


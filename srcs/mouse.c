/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:51:17 by kanlee            #+#    #+#             */
/*   Updated: 2021/05/28 12:54:56 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mouse.h"

int	mouse_hook(int btn, int click_x, int click_y, t_mlx *frame)
{
	printf("btn=%d, x=%d, y=%d\n", btn, click_x, click_y);
//	if (btn != MOUSE_LCLICK || click_y <= 0)
//		return (0);
	return (0);
}

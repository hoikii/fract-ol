/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:34:56 by kanlee            #+#    #+#             */
/*   Updated: 2021/05/28 14:23:49 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame.h"
#include "key.h"

int	key_pressed(int keycode, t_mlx *frame)
{
	if (keycode == KEY_ESC)
		close_win(frame);
	return (0);
}


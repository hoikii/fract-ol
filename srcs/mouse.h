/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:51:45 by kanlee            #+#    #+#             */
/*   Updated: 2021/06/08 01:23:11 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOUSE_H
# define MOUSE_H

# include "frame.h"

# define MOUSE_LCLICK 1
# define MOUSE_RCLICK 2
# define MOUSE_WHEELUP 4
# define MOUSE_WHEELDOWN 5


int mouse_press(int btn, int click_x, int click_y, t_mlx *frame);
int mouse_release(int btn, int click_x, int click_y, t_mlx *frame);
int	mouse_move(int click_x, int click_y, t_mlx *frame);

#endif

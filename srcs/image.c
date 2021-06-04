/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:20:42 by kanlee            #+#    #+#             */
/*   Updated: 2021/06/05 02:39:37 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "frame.h"
#include "../libft/libft.h"

static void	put_info(t_mlx frame)
{
	char *msg;

	mlx_put_image_to_window(frame.mlx, frame.win, frame.menu.img_ptr, 0, 0);
	msg = ft_strjoin("max_iterations: ", ft_itoa(frame.it_max));
	mlx_string_put(frame.mlx, frame.win, 10, 20, 0x00ffffff, msg);
	free(msg);
	msg = ft_strjoin("scale: ", ft_ftoa(frame.scale / (IMG_WIDTH / 3), 6));
	mlx_string_put(frame.mlx, frame.win, 10, 40, 0x00ffffff, msg);
	free(msg);
	mlx_string_put(frame.mlx, frame.win, 10, 60, 0x00ffffff, "plot range");
	msg = ft_strjoin(ft_ftoa(frame.center.x - IMG_WIDTH / frame.scale / 2, 6),
			   " <= x <= ");
	msg = ft_strjoin(msg, ft_ftoa(frame.center.x + IMG_WIDTH / frame.scale / 2, 6));
	mlx_string_put(frame.mlx, frame.win, 10, 80, 0x00ffffff, msg);
	free(msg);
}

void	img_to_window(t_mlx frame)
{

	mlx_put_image_to_window(frame.mlx, frame.win, frame.img.img_ptr, MENU_WIDTH, 0);
	put_info(frame);

}

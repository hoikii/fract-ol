/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:20:42 by kanlee            #+#    #+#             */
/*   Updated: 2021/11/21 15:48:32 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "frame.h"
#include "../libft/libft.h"

static void	put_julia_constant_ctl(t_mlx *frame)
{
	int		bg_width;
	int		bg_height;
	int		btn_width;
	t_point	ctl_center;

	bg_width = frame->julia_ctl_bg.width;
	bg_height = frame->julia_ctl_bg.height;
	ctl_center = (t_point){JULIA_CTL_PAD_LEFT + bg_width / 2,
		JULIA_CTL_PAD_TOP + bg_height / 2};
	btn_width = frame->julia_ctl_btn.width;
	mlx_put_image_to_window(frame->mlx, frame->win, frame->julia_ctl_bg.img_ptr,
		JULIA_CTL_PAD_LEFT, JULIA_CTL_PAD_TOP);
	mlx_put_image_to_window(frame->mlx, frame->win,
		frame->julia_ctl_btn.img_ptr,
		ctl_center.x + frame->julia_constant.real / JULIA_CONST_LIMIT
		* bg_width / 2 - btn_width / 2,
		ctl_center.y - frame->julia_constant.imag / JULIA_CONST_LIMIT
		* bg_height / 2 - btn_width / 2);
}

static void	str_join_put(t_mlx *frame, char *msg, char *data, int y)
{
	char	*str;

	str = ft_strjoin(msg, data);
	free(data);
	mlx_string_put(frame->mlx, frame->win, 10, y, 0x00ffffff, str);
	free(str);
}

static void	put_info(t_mlx *frame)
{
	char	*msg;

	mlx_put_image_to_window(frame->mlx, frame->win, frame->menu.img_ptr, 0, 0);
	str_join_put(frame, "max_iterations: ", ft_itoa(frame->it_max), 20);
	str_join_put(frame, "scale: ",
		ft_ftoa(frame->scale / (IMG_WIDTH / 3), 6), 40);
	str_join_put(frame, "1px = ", ft_ftoa(1 / frame->scale, 16), 60);
	str_join_put(frame, "center x: ", ft_ftoa(frame->center.x, 12), 80);
	str_join_put(frame, "center y: ", ft_ftoa(frame->center.y, 12), 100);
	if (frame->zoom_mode)
		msg = "zoom mode: follow mouse position";
	else
		msg = "zoom mode: fixed";
	mlx_string_put(frame->mlx, frame->win, 10, 120, 0x00ffffff, msg);
	mlx_string_put(frame->mlx, frame->win, 10, 160, 0x00ffffff,
		"julia constant");
	str_join_put(frame, "real part = ",
		ft_ftoa(frame->julia_constant.real, 5), 175);
	str_join_put(frame, "imaginary = ",
		ft_ftoa(frame->julia_constant.imag, 5), 190);
	if (frame->type == JULIASET)
		put_julia_constant_ctl(frame);
}

int	img_to_window(t_mlx *frame)
{
	if (frame->lbtn_pressed)
		mlx_put_image_to_window(frame->mlx, frame->win,
			frame->img_move.img_ptr, MENU_WIDTH, 0);
	else
		mlx_put_image_to_window(frame->mlx, frame->win,
			frame->img.img_ptr, MENU_WIDTH, 0);
	put_info(frame);
	return (0);
}

void	put_pxl_to_image(int x, int y, t_mlx *frame, t_color rgb)
{
	char	*imgdata;
	int		pos;
	int		color;

	color = mlx_get_color_value(frame->mlx, rgb_to_int(rgb));
	imgdata = frame->img.imgdata;
	pos = y * frame->img.size_line + x * frame->img.bpp / 8;
	*(unsigned int *)(&imgdata[pos]) = color;
}

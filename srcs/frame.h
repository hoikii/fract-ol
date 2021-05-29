/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:35:41 by kanlee            #+#    #+#             */
/*   Updated: 2021/05/29 23:35:44 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAME_H
# define FRAME_H

# include "../minilibx/mlx.h"
# include "math_utils.h"
# include "color.h"

# define SCREEN_WIDTH 600
# define SCREEN_HEIGHT 600

typedef struct	s_point {
	double	x;
	double	y;
}				t_point;

typedef struct s_img {
	void	*img_ptr;
	char	*imgdata;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct	s_mlx {
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	t_img	img;
	t_point	upperleft;
	t_point	center;
	double	scale;
	int		it_max;
} t_mlx;

int			close_win(t_mlx *param);
void		fractal_calc(t_mlx frame);
void	put_pxl_to_image(int x, int y, t_mlx frame, t_color rgb);
#endif

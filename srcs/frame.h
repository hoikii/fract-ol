/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:35:41 by kanlee            #+#    #+#             */
/*   Updated: 2021/06/07 19:10:24 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAME_H
# define FRAME_H

# ifdef BONUS
#  undef BONUS
#  define BONUS 1
# else
#  define BONUS 0
# endif

# ifndef THREADS_CNT
#  define THREADS_CNT 1
# endif

# ifdef LINUX
#  include "../minilibx-linux/mlx.h"
# else
#  include "../minilibx/mlx.h"
# endif

# include "math_utils.h"
# include "color.h"

# define IMG_WIDTH 600
# define IMG_HEIGHT 600
# define MENU_WIDTH 200

typedef enum e_fractal_type {
	MANDELBROT,
	JULIASET,
	KOCH_SNOWFLAKE
}	t_fractal_type;

typedef struct s_point {
	double	x;
	double	y;
} t_point;

typedef struct s_img {
	void	*img_ptr;
	char	*imgdata;
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
	t_img	menu;
	t_fractal_type type;
	t_point	upperleft;
	t_point	center;
	double	scale;
	int		it_max;
	t_complex	julia_constant;
	int a[100000];
} t_mlx;

typedef struct s_threads {
	int		tid;
	t_mlx	*frame;
}	t_threads;

int			close_win(t_mlx *param);
void		fractal_calc(t_mlx frame);
void	put_pxl_to_image(int x, int y, t_mlx *frame, t_color rgb);
void	img_to_window(t_mlx *frame);
void	render(t_mlx *frame);
void	mandelbrot_calc(int x, int y, t_mlx *frame);
void	julia_calc(int x, int y, t_mlx *frame);
void	koch_calc(t_mlx *frame);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:35:41 by kanlee            #+#    #+#             */
/*   Updated: 2021/05/28 14:23:58 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAME_H
# define FRAME_H

# include "../minilibx/mlx.h"

typedef struct	s_mlx {
	void	*mlx;
	void	*win;
} t_mlx;

typedef struct s_img {
	void	*img_prt;
	char	*imgdata;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

int			close_win(t_mlx *param);
#endif

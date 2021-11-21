/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:33:36 by kanlee            #+#    #+#             */
/*   Updated: 2021/11/21 17:03:11 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H

# define KEYPRESS 2
# define KEYPRESSMASK 1
# ifdef LINUX
#  define CLIENTMESSAGE 33
#  define WM_DELETE_WINDOW 3
#  define VISIBILITYNOTIFY 15
#  define KEY_ESC 65307
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_W 119
#  define KEY_Q 113
#  define KEY_Z 122
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_DOWN 65364
#  define KEY_UP 65362
#  define KEY_NP_PLUS 65451
#  define KEY_NP_MINUS 65453
#  define KEY_NP_MUL 65450
#  define KEY_NP_DIV 65455
#  define KEY_PLUS 61
#  define KEY_MINUS 45
#  define KEY_MUL 56
#  define KEY_DIV 47
#  define KEY_SPACE 32
#  define KEY_O 111
#  define KEY_C 99
#  define KEY_L 108
#  define KEY_1 49
#  define KEY_2 50
#  define KEY_3 51
#  define KEY_4 52
#  define KEY_5 53
#  define KEY_T 116
#  define KEY_COMMA 44
#  define KEY_PERIOD 46
#  define KEY_LB -1
#  define KEY_RB -1
# else
#  define DESTROYNOTIFY 17
#  define STRUCTURENOTIFYMASK 131072
#  define KEY_ESC 53
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_W 13
#  define KEY_Q 12
#  define KEY_Z 6
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
#  define KEY_UP 126
#  define KEY_NP_PLUS 69
#  define KEY_NP_MINUS 78
#  define KEY_NP_MUL 67
#  define KEY_NP_DIV 75
#  define KEY_PLUS 24
#  define KEY_MINUS 27
#  define KEY_MUL 28
#  define KEY_DIV 44
#  define KEY_SPACE 49
#  define KEY_O 31
#  define KEY_C 8
#  define KEY_L 37
#  define KEY_1 18
#  define KEY_2 19
#  define KEY_3 20
#  define KEY_4 21
#  define KEY_5 23
#  define KEY_T 17
#  define KEY_COMMA 43
#  define KEY_PERIOD 47
#  define KEY_LB 33
#  define KEY_RB 30
# endif

int	key_pressed(int keycode, t_mlx *frame);

#endif

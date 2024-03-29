NAME		= fractol
SRCDIR		= srcs/
SRCFILES	= main.c \
			  init.c \
			  key.c \
			  mouse.c \
			  utils.c \
			  math_utils.c \
			  render.c \
			  image.c \
			  image_histogram.c \
			  image_color.c \
			  color.c \
			  mandelbrot.c \
			  julia.c \
			  burningship.c \
			  mouse_julia_constant_control.c
SRCS		= $(addprefix $(SRCDIR), $(SRCFILES))
OBJS		= $(SRCS:.c=.o)
LIBFTDIR	= libft
LIBFTNAME	= ft
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

UNAME		:= $(shell uname)
ifeq ($(UNAME),Darwin)
	CFLAGS		+= -D MACOS
	LIBMLXDIR	= minilibx
	LIBMLXNAME	= mlx
	LIBMLXFILE	= libmlx.a
	LDLIBS		= -L$(LIBFTDIR) -l$(LIBFTNAME) -L$(LIBMLXDIR) -l$(LIBMLXNAME)
	LDLIBS		+= -framework OpenGL -framework AppKit
#	CFLAGS		+= -D THREADS_CNT=$(shell sysctl -n hw.ncpu)
else
	CFLAGS		+= -D LINUX
	LIBMLXDIR	= minilibx-linux
	LIBMLXNAME	= mlx
	LIBMLXFILE	= libmlx.a
	LDLIBS		= -L$(LIBFTDIR) -l$(LIBFTNAME) -L$(LIBMLXDIR) -l$(LIBMLXNAME)
	LDLIBS		+= -L/usr/lib -lm -lXext -lX11 -lpthread
#	CFLAGS		+= -D THREADS_CNT=$(shell grep -c processor /proc/cpuinfo)
endif

CCBLUE		= \033[34m
CCBLUE_BOLD	= \033[1;34m
CCEND		= \033[0m

.PHONY: all bonus leaktest cleanlib clean fclean re

all: $(NAME)

$(NAME): $(OBJS) srcs/frame.h
	@echo "$(CCBLUE) >>> make libft with bonus <<< $(CCEND)"
	@$(MAKE) bonus -C libft
	@echo "$(CCBLUE) >>> make minilibx (warning suppressed) <<< $(CCEND)"
	@$(MAKE) -C $(LIBMLXDIR) 2> /dev/null
#	cp $(LIBMLXDIR)/$(LIBMLXFILE) ./
	@echo "$(CCBLUE) >>> linking obj files.  <<< $(CCEND)"
	$(CC) $(OBJS) $(CFLAGS) $(LDLIBS) -o $(NAME)
	@echo "$(CCBLUE_BOLD) >>> make $(NAME) done!  <<< $(CCEND)"

bonus: CFLAGS += -D BONUS -D THREADS_CNT=$(shell getconf _NPROCESSORS_ONLN)
bonus: clean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

cleanlib:
	@echo "$(CCBLUE) >>> clean libft <<< $(CCEND)"
	$(MAKE) -C $(LIBFTDIR) fclean
	@echo "$(CCBLUE) >>> clean minilibx. <<< $(CCEND)"
	$(MAKE) -C $(LIBMLXDIR) clean

clean:
	@echo "$(CCBLUE) >>> clean main projects object files. <<< $(CCEND)"
	$(RM) $(OBJS)

fclean: cleanlib clean
#	@echo "$(CCBLUE) >>> clean minilibx library file <<< $(CCEND)"
#	$(RM) $(LIBMLXFILE)
	@echo "$(CCBLUE) >>> clean main project's executable. <<< $(CCEND)"
	$(RM) $(NAME)

re: fclean all

leaktest: CFLAGS += -g3 -fsanitize=address
leaktest: clean all


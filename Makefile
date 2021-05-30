NAME =		fractol
HEADERS =	fractol.h
LIBRARYS =	mlx/libmlx.a

G =			\033[38;2;154;205;50
W =			\033[38;2;255;255;255

INCLUDES =	./

FILES =		main.c

O_FILES =	$(FILES:.c=.o)

CFLAGS =	#-Wall -Wextra -Werror -O3

all:		$(NAME)

$(NAME):	$(LIBRARYS) $(O_FILES)
			@$(CC) $? $(CFLAGS) -framework OpenGL -framework AppKit -o $(NAME)
			@echo ""
			@echo "$(G);1m wwwwwwwwww   DONE!  wwwwwwwwww"
			@echo "$(W);1m PRESS  COMMAND + V  AND  ENJOY"
			@echo "$(G);1m wwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n"
			@printf %s ./$(NAME) | pbcopy

$(LIBRARYS):
			make -C mlx

%.o :		%.c $(HEADERS)
			gcc $(CFLAGS) -I $(INCLUDES) -c $< -o $@

clean:
			@rm -f $(O_FILES)

fclean:		clean
			@rm -f $(NAME)

re:			fclean all

.PHONY =	all	clean fclean re

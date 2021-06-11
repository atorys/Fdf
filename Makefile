#-------------------------NAME--------------------------/
NAME =		fdf
#------------------------SOURCES------------------------/
INCLUDES =	./

VPATH =		maparse \
			render

HEADERS =	fdf.h \
			get_next_line.h
LIBRARYS =	mlx/libmlx.a

#----------FILES
FILES =		main.c \
			map_parsing.c \
			map_drawing.c \
			drawing_utils.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_split.c

O_FILES =	$(FILES:.c=.o)

#-----ADDITIONAL
CFLAGS =	-Wall -Wextra -Werror -O3
G =			\033[38;2;154;205;50
W =			\033[38;2;255;255;255


#--------------------RULES-------------------------------/
all:		$(NAME)

$(NAME):	libs $(O_FILES) $(LIBRARYS)
			@$(CC) $(CFLAGS) $(O_FILES) $(LIBRARYS) -framework OpenGL -framework AppKit -o $(NAME)
			@echo ""
			@echo "$(G);1m wwwwwwwwww   DONE!  wwwwwwwwww"
			@echo "$(W);1m PRESS COMMAND + V  AND ADD MAP"
			@echo "$(G);1m wwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n"
			@printf %s ./$(NAME) | pbcopy

libs :
			make -C mlx/

%.o :		%.c $(HEADERS)
			gcc $(CFLAGS) -I $(INCLUDES) -c $< -o $@


#-------CLEAN
clean:
			@rm -f $(O_FILES)
			@make clean -C mlx/

fclean:		clean
			@rm -f $(NAME)

re:			fclean all

.PHONY =	all	clean fclean re

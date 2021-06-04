cmake_minimum_required(VERSION 3.17)
project(fdf C)

set(CMAKE_C_STANDARD 99)

include_directories(./)

add_executable(fdf
        Makefile
        fdf.h
        mlx/mlx.h
        mlx/mlx_new_window.h
        mlx/libmlx.a
        maparse/map_parsing.c
        main.c
        maparse/ft_split.c
        maparse/get_next_line.h
        maparse/get_next_line.c
        maparse/get_next_line_utils.c)
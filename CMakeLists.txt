cmake_minimum_required(VERSION 3.17)
project(fractol C)

set(CMAKE_C_STANDARD 99)

include_directories(./)

add_executable(fractol
        main.c
        Makefile
        fractol.h
        mlx/mlx.h
        mlx/mlx_new_window.h)
cmake_minimum_required(VERSION 4.0)
project(chapter2 C)

set(CMAKE_C_STANDARD 99)

add_executable(chapter2 issue1.c
)

add_executable(main issue1.c)
add_executable(main2 issue2.c)
add_executable(issue3 issue3.c)
add_executable(issue4 issue4.c)
add_executable(issue5 issue5.c)
add_executable(issue6 issue6.c)
add_executable(issue7 issue7.c)
add_executable(issue8 issue8.c)
add_executable(issue9 issue9.c)
add_executable(issue10 issue10.c)
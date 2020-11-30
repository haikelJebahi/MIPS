cmake_minimum_required(VERSION 3.10.2)
project(mips)
set(SRC
    Projet/main.c
   )
set(HEADER)
add_executable(mips ${SRC} ${HEADER})

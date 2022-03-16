cmake_minimum_required(VERSION 3.19)
project(MobManager C)

set(CMAKE_C_STANDARD 99)

include_directories(src headers)

add_executable(MobManager src/main.c src/enemy.c headers/enemy.h src/interface.c headers/interface.h
        src/fileManager.c headers/fileManager.h)
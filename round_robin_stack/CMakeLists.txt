cmake_minimum_required(VERSION 3.5)

project(round_robin_stack LANGUAGES C)
link_libraries("pthread")

add_executable(round_robin_stack main.c
                                    message_queue.c)

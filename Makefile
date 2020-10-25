.PHONY = all

#.SUFFICES: ;

CC = g++

CFLAGS := -Wall -Wextra
LINKERFLAG := 


all: sync_timer.out async_timer.out bind_args.out mult_bind_args.out bind_member.out


sync_timer.out: sync_timer.cpp
	${CC} $< -o $@ -lboost_system


async_timer.out: async_timer.cpp
	${CC} $< -o $@ -lboost_system


bind_args.out: bind_args.cpp
	${CC} $< -o $@ -lboost_system


mult_bind_args.out: mult_bind_args.cpp
	${CC} $< -o $@ -lboost_system


bind_member.out: bind_member.cpp
	${CC} $< -o $@ -lboost_system


clean:
	rm -rfv *.out
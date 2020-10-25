.PHONY = all

#.SUFFICES: ;

CC = g++

CFLAGS := -Wall -Wextra
LINKERFLAG := 


all: sync_timer.out async_timer.out bind_args.out mult_bind_args.out bind_member.out mult_thread.out msm_functor msm_simple


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

mult_thread.out: mult_thread.cpp
	${CC} $< -o $@ -lboost_system -lboost_thread

msm_simple.out: msm_simple.cpp
	${CC} $< -o $@

msm_functor.out: msm_functor.cpp
	${CC} $< -o $@

clean:
	rm -rfv *.out
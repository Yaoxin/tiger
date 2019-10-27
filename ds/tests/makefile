#######################################
#  cmd
GCC		= 	g++
RM		=	rm
CP		=   cp


######################################
# cflags

INCLUDE_DIR		:= -I.
INCLUDE_DIR     += -I../include

# -pg
CFLAGS 	:= $(INCLUDE_DIR) -g -DLOG_INFO -static

######################################
#  dflags
LIB_DIR		:= -L.
LIB_DIR     += -L../lib

LD_FLAGS    := -lpthread -lyx_ds -lm -lz -lrt

#######################################
#  make
TARGET     :=  test_tree
OBJS 		=  $(addsuffix .o, ${TARGET})


%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

$%.o: %.c
	gcc $(CFLAGS) -c $< -o $@


.PHONY: all
all:  ${TARGET}


${TARGET}: $(OBJS)
	g++ $(LIB_DIR) -o ${TARGET} $(OBJS) $(LD_FLAGS)


.PHONY: clean
clean:
	rm *.o ${TARGET}
#######################################
#  cmd
GCC		= 	g++
RM		=	rm
CP		=   cp

#######################################
#% 路径
OUTPUT_DIR	=	../objs
RELEASE_DIR = ../lib

######################################
# cflags
INCLUDE_DIR		:= -I.

# -pg
DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS		:= -g -ggdb3 -O0 -rdynamic -DLOG_DEBUG
else
	CFLAGS		:= -O2 -DLOG_INFO
endif
CFLAGS 	+= $(INCLUDE_DIR) -static

######################################
#  dflags
LIB_DIR		:= -L.

LD_FLAGS    := -lpthread -lm -lz -lrt

#######################################
TARGET     :=  libyx_algo.a
OBJS       =    $(OUTPUT_DIR)/sort.o        \
                ${OUTPUT_DIR}/search.o      \
                ${OUTPUT_DIR}/permutation.o \
                ${OUTPUT_DIR}/substring.o   \


$(OUTPUT_DIR)/%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

$(OUTPUT_DIR)/%.o: %.c
	gcc $(CFLAGS) -c $< -o $@



$(OUTPUT_DIR)/%.d: %.cpp
	@set -e; rm -f $@;\
	g++ -MM $(CFLAGS) $< > $@.tmp; \
	sed 's,\($*\)\.o[ :],$(OUTPUT_DIR)/\1.o $@ :,g' < $@.tmp > $@;\
	rm -f $@.tmp

$(OUTPUT_DIR)/%.d: %.c
	@set -e; rm -f $@; \
	gcc -MM $(CFLAGS) $< > $@.tmp; \
	sed 's,\($*\)\.o[ :],$(OUTPUT_DIR)/\1.o $@ :,g' < $@.tmp > $@; \
	rm -f $@.tmp


.PHONY: all
all: ${TARGET}

${TARGET}: $(OBJS)
	ar rcs $(OUTPUT_DIR)/${TARGET} $(OBJS)

######################################
.PHONY: install
install:
	${CP} *.h ../include
	${CP} $(OUTPUT_DIR)/lib*.a ${RELEASE_DIR}


#######################################
.PHONY: clean
clean:
	$(RM)  $(OUTPUT_DIR)/*.o $(OUTPUT_DIR)/*.d
	${RM} $(OUTPUT_DIR)/*.a

include $(patsubst %.cpp, $(OUTPUT_DIR)/%.d, $(wildcard *.cpp))
include $(patsubst %.c, $(OUTPUT_DIR)/%.d, $(wildcard *.c))
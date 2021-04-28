NAME=cub3D

BIN_DIR=bin
INC_DIR=inc
LIB_DIR=lib
OBJ_DIR=obj
SRC_DIR=src

SRCS=$(shell find ${SRC_DIR} -type f -name "*.c")
OBJS=${patsubst ${SRC_DIR}/%,${OBJ_DIR}/%,${SRCS:.c=.o}}
DIRS=${BIN_DIR} ${OBJ_DIR} ${dir ${OBJS}}

CFLAGS=-Werror
ifdef DEBUG
	CFLAGS=-ggdb
endif
CFLAGS+=-Wall -Wextra -I ${INC_DIR} -I minilibx
LDFLAGS=-L ${LIB_DIR} -L minilibx/ -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -lft
AR_OPTS=-rc
RM_OPTS=-rf

CC=cc
RM=rm ${RM_OPTS}
AR=ar ${AR_OPTS}

###############################################################################

.PHONY: dirs lib so re clean fclean

${NAME}: ${BIN_DIR}/${NAME}

${BIN_DIR}/${NAME}: dirs minilibx ${OBJS}
	${CC} -o ${BIN_DIR}/${NAME} ${OBJS} ${LDFLAGS}

lib: ${OBJS}
	${AR} ${BIN_DIR}/${NAME}.a ${OBJS}

so: ${OBJS}
	${CC} -shared -o ${BIN_DIR}/${NAME}.so ${OBJS}

${OBJS}: ${SRCS}
	${CC} ${CFLAGS} -c -o $@ ${patsubst ${OBJ_DIR}/%,${SRC_DIR}/%,${@:.o=.c}}

dirs:
	mkdir -p ${DIRS}

minilibx:
	${MAKE} minilibx

re: fclean ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${BIN_DIR}/${NAME}

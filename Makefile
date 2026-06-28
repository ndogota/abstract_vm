CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LDLIBS = -lm

SRC_DIR := src
INCLUDE_DIR := include
EXECUTABLE = abstractvm

SRC := 	$(SRC_DIR)/main.c      \
		$(SRC_DIR)/tools.c     \
		$(SRC_DIR)/core.c      \
		$(SRC_DIR)/linked.c    \
		$(SRC_DIR)/lines.c

OBJ := $(SRC:.c=.o)

HEADER := 	$(INCLUDE_DIR)/main.h      \
			$(INCLUDE_DIR)/tools.h     \
			$(INCLUDE_DIR)/core.h      \
			$(INCLUDE_DIR)/linked.h    \
			$(INCLUDE_DIR)/lines.h

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJ) $(LDLIBS)

# Strict warning flags are enforced here, at the compile step.
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXECUTABLE)

re: fclean all

.PHONY: all clean fclean re

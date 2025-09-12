# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbuscaro <lbuscaro@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/08 17:52:50 by lbuscaro          #+#    #+#              #
#    Updated: 2025/09/03 12:12:12 by lbuscaro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex

CC = cc
CFLAGS = -Wall -Werror -Wextra
GDB= -g
RM = rm -rf

LFT = libft/libft.a

INCLUDES_DIR = ./includes
SRC_DIR = ./src
BUILD_DIR = ./build

M_MAIN = $(SRC_DIR)/main.c
M_MAIN_OBJ = $(BUILD_DIR)/main.o

M_SRC = utils.c
M_SRC := $(addprefix $(SRC_DIR)/,$(M_SRC))
M_OBJ = $(M_SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

B_MAIN = $(SRC_DIR)/main_bonus.c
B_MAIN_OBJ = $(BUILD_DIR)/main_bonus.o

B_SRC = utils_bonus.c
B_SRC := $(addprefix $(SRC_DIR)/,$(B_SRC))
B_OBJ = $(B_SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

BONUS_STATUS = $(BUILD_DIR)/.bonus

all: $(NAME)

$(NAME): $(LFT) $(M_OBJ) $(M_MAIN_OBJ)
	$(CC) -g $(CFLAGS) $(M_OBJ) $(M_MAIN_OBJ) -Llibft -lft -o $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(BUILD_DIR)
	$(CC) -g $(CFLAGS) -Ilibft/includes -I$(INCLUDES_DIR) -c $< -o $@

$(LFT):
	make -C libft all

clean:
	$(RM) $(BUILD_DIR) outfile
	make -C libft clean
	@$(RM) $(BONUS_STATUS)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	make -C libft fclean

re: fclean all

bonus: $(BONUS_STATUS)

$(BONUS_STATUS): $(NAME) $(B_OBJ) $(B_MAIN_OBJ)
	$(CC) $(CFLAGS) $(M_OBJ) $(B_OBJ) $(B_MAIN_OBJ) -Llibft -lft -o $(BONUS_NAME)
	@mkdir -p $(BONUS_STATUS)

gdb: all
	$(CC) -g $(CFLAGS) $(M_OBJ) $(M_MAIN_OBJ) -Llibft -lft -o $(NAME)
	gdb --tui --args ./pipex infile "$(A1)" "$(A2)" outfile

run: all
	./pipex infile "$(A1)" "$(A2)" outfile

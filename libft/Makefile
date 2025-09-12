# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbuscaro <lbuscaro@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 13:30:36 by lbuscaro          #+#    #+#              #
#    Updated: 2025/04/16 15:32:42 by lbuscaro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

INCLUDES_DIR = ./includes
SRC_DIR = ./src
BUILD_DIR = ./build

SRC = ft_isalpha.c
SRC += ft_isdigit.c
SRC += ft_isalnum.c
SRC += ft_isascii.c
SRC += ft_isprint.c
SRC += ft_strlen.c
SRC += ft_memset.c
SRC += ft_bzero.c
SRC += ft_memcpy.c
SRC += ft_memmove.c
SRC += ft_strlcpy.c
SRC += ft_strlcat.c
SRC += ft_toupper.c
SRC += ft_tolower.c
SRC += ft_strchr.c
SRC += ft_strrchr.c
SRC += ft_strncmp.c
SRC += ft_memchr.c
SRC += ft_memcmp.c
SRC += ft_strnstr.c
SRC += ft_atoi.c
SRC += ft_calloc.c
SRC += ft_strdup.c
SRC += ft_substr.c
SRC += ft_strjoin.c
SRC += ft_strtrim.c
SRC += ft_split.c
SRC += ft_itoa.c
SRC += ft_strmapi.c
SRC += ft_striteri.c
SRC += ft_putchar_fd.c
SRC += ft_putstr_fd.c
SRC += ft_putendl_fd.c
SRC += ft_putnbr_fd.c
SRC += get_next_line.c
SRC += get_next_line_utils.c
SRC += ft_lstnew.c
SRC += ft_lstadd_front.c
SRC += ft_lstsize.c
SRC += ft_lstlast.c
SRC += ft_lstadd_back.c
SRC += ft_lstdelone.c
SRC += ft_lstclear.c
SRC += ft_lstiter.c
SRC += ft_lstmap.c
SRC += ft_printf.c
SRC += ft_putchar.c
SRC += ft_putstr.c
SRC += ft_putint.c
SRC += ft_putaddr.c
SRC += ft_putuint.c 

SRC := $(addprefix $(SRC_DIR)/,$(SRC))
OBJS = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c $< -o $@

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thansen <thansen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/08 12:52:17 by thansen           #+#    #+#              #
#    Updated: 2019/05/10 22:34:11 by thansen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INC_DIR = ./inc

OBJ_DIR = ./obj
OBJ_DIR_LIB = obj/libft
OBJ_DIR_PRNTF = obj/ft_printf

SRC_DIR_LIB = ./src/libft
SRC_DIR_PRNTF = ./src/ft_printf

SRC_LIB  =  ft_strlen.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_atoi.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_memcmp.c \
		ft_bzero.c \
		ft_memset.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_strdup.c \
		ft_strcpy.c \
		ft_strncpy.c \
		ft_strcat.c \
		ft_strncat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strstr.c \
		ft_strnstr.c \
		ft_strlcat.c \
		ft_memalloc.c \
		ft_memdel.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_strclr.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_itoa.c \
		ft_strsplit.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putendl.c \
		ft_putnbr.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_iswhitespace.c \
		ft_nbrlen.c \
		ft_wordcount.c \
		ft_nextword.c \
		ft_strndup.c \
		ft_lstclr.c \
		ft_realloc.c \
		ft_strshift.c \
		ft_strjoinch.c \
		ft_copyuntil.c \
		ft_strchr_safe.c \
		get_next_line.c \
		ft_strnchr.c \
		ft_abs.c \
		ft_nbrlen_base.c \
		ft_ltoa_base.c \
		ft_putstr_until.c \
		ft_chjoinstr.c \
		ft_strjoinnch.c \
		ft_nchjoinstr.c

SRC_PRNTF = ft_printf.c \
		token_processing.c \
		print_char.c \
		print_string.c \
		print_pointer.c \
		print_decimal.c \
		print_number.c \
		print_octal.c \
		print_hex.c \
		print_bhex.c \
		print_unsigned.c \
		print_double.c \
		str_adding.c \
		bin_transform.c \
		dbl_to_str.c \
		ldbl_to_str.c

OBJS_LIB = $(addprefix $(OBJ_DIR_LIB)/,$(SRC_LIB:%.c=%.o))
OBJS_PRNTF = $(addprefix $(OBJ_DIR_PRNTF)/,$(SRC_PRNTF:%.c=%.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR_LIB)
	@mkdir -p $(OBJ_DIR_PRNTF)

$(NAME): $(OBJ_DIR) $(OBJS_LIB) $(OBJS_PRNTF)
	@ar rcs $(NAME) $(OBJS_LIB) $(OBJS_PRNTF)
	@ranlib $(NAME)

$(OBJ_DIR_LIB)/%.o: $(SRC_DIR_LIB)/%.c
	@gcc -Wall -Werror -Wextra -c $< -I$(INC_DIR) -o $@

$(OBJ_DIR_PRNTF)/%.o: $(SRC_DIR_PRNTF)/%.c
	@gcc -Wall -Werror -Wextra -c $< -I$(INC_DIR) -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

norm:
	@norminette $(SRC_DIR) $(INC_DIR)

.PHONY: all clean fclean re norm

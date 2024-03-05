# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julieblaye <julieblaye@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 11:51:52 by acroue            #+#    #+#              #
#    Updated: 2024/03/05 15:35:14 by julieblaye       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Program name
NAME = minishell
TEST_PARSING = test_parsing

#	Colors
DEFAULT    = \033[0m
BLACK    = \033[0;30m
RED        = \033[0;31m
GREEN    = \033[0;32m
YELLOW    = \033[0;33m
BLUE    = \033[0;34m
PURPLE    = \033[0;35m
CYAN    = \033[0;36m
BWHITE    = \033[1;37m

# Utils
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
DEP_FLAGS = -MMD -MP
RM = rm -rf
LIB_FLAGS = --no-print-directory --silent

#	Directories
LIBS_DIR = libs
SRCS_DIR = srcs
EXEC_DIR = alexec
PARSING_DIR = jularsing
INCS_DIR = includes
OBJS_DIR = objs
LIBFT_DIR = $(LIBS_DIR)/libft

#	Files
LIBFT = $(LIBFT_DIR)/libft.a

LIB :=	$(LIBFT) \
	-lreadline

INCLUDES := $(INCS_DIR) \
	$(LIBFT_DIR)

INCLUDES_FLAGS := $(addprefix -I , $(INCLUDES))

SRC :=	$(addprefix $(PARSING_DIR)/, \
	parsing.c \
	) \
	$(addprefix $(EXEC_DIR)/, \
	exec.c \
	) \
	main.c

OBJ := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRC))
DEPS := $(patsubst %.c,$(OBJS_DIR)/%.d,$(SRC))

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(GREEN)* Assembling $(BWHITE)$@$(DEFAULT)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(INCLUDES_FLAGS) -o $@

-include %(DEPS)
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@echo "$(CYAN)- Compiling$(DEFAULT) $<"
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/$(PARSING_DIR)
	@mkdir -p $(OBJS_DIR)/$(EXEC_DIR)
	@$(CC) $(DEP_FLAGS) $(CFLAGS) $(INCLUDES_FLAGS) -c $< -o $@

clean:
	@echo "$(RED)! Removing$(DEFAULT) ${OBJS_DIR} files"
	@${RM} ${OBJS_DIR}

fclean: clean
	@echo "$(RED)! Removing$(DEFAULT) $(NAME)"
	@$(RM) $(NAME)
	@echo "$(RED)! Removing$(DEFAULT) $(TEST_PARSING)"
	@$(RM) $(TEST_PARSING)

re: fclean all

$(LIBFT):
	@echo "$(CYAN)~ Compiling$(DEFAULT) $(PURPLE)$(LIBFT_DIR)$(DEFAULT)"
	@make -C $(LIBFT_DIR) $(LIB_FLAGS)

cleanlib:
	@echo "$(RED)! Removing$(DEFAULT) $(PURPLE)$(LIBFT_DIR)$(DEFAULT)"
	@make clean -C $(LIBFT_DIR) $(LIB_FLAGS)

fcleanlib:
	@echo "$(RED)! Removing$(DEFAULT) $(PURPLE)$(LIBFT_DIR)$(DEFAULT)"
	@make fclean -C $(LIBFT_DIR) $(LIB_FLAGS)

relib: fcleanlib $(LIBFT)

cre:
	@clear
	@make re --no-print-directory

norm:
	@norminette $(SRCS_DIR) $(INCS_DIR) $(BONUS_DIR) | awk '/'Error'/ {print; found=1} END {if (!found) print "$(PURPLE)Norm O.K.$(DEFAULT)"}'
	@norminette $(LIBFT_DIR) | awk '/'Error'/ {print; found=1} END {if (!found) print "$(YELLOW)Norm libft O.K.$(DEFAULT)"}'

testparsing: $(LIBFT)
	@echo "$(YELLOW)* Assembling $(BWHITE)$(TEST_PARSING)$(DEFAULT)"
	@$(CC) $(CFLAGS) $(LIB) $(INCLUDES_FLAGS) $(SRCS_DIR)/$(PARSING_DIR)/*.c -o $(TEST_PARSING)

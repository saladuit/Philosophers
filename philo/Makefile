# **************************************************************************** #
#                                                                              #
#                                                     .--.  _                  #
#    Makefile                                        |o_o || |                 #
#                                                    |:_/ || |_ _   ___  __    #
#    By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /    #
#                                                  (|     | )|_| |_| |>  <     #
#    Created: 2022/07/07 17:49:38 by safoh        /'\_   _/`\__|\__,_/_/\_\    #
#    Updated: 2022/08/24 21:33:10 by safoh        \___)=(___/                  #
#                                                                              #
# **************************************************************************** #

include makerc/colours.mk
include makerc/config.mk

################################################################################

NAME			:=philo

CC				:=gcc
RM				:=rm -rfv
CFLAGS			=-Wall -Wextra -Werror$(if $(DEBUG), -g)\
				 $(if $(MALLOC), -g)

################################################################################
all: $(NAME)

$(NAME): SHELL :=/bin/bash

$(NAME): $(OBJS) $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ $(INCLUDE_FLAGS) -o $(NAME)
	@printf "$(BLUE_FG)$(NAME)$(RESET_COLOR) created\n"

$(MAIN_OBJ) $(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

################################################################################

clean:
	@$(RM) $(OBJS) $(MAIN_OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean
	@$(MAKE)

debug:
	@$(MAKE) DEBUG=1

rebug: fclean
	@$(MAKE) debug

re_malloc_test: fclean
	@$(MAKE) malloc_test

malloc_test: $(OBJS) $(MAIN_OBJ) $(LIBFT)
	@$(MAKE) MALLOC=1
	$(CC) $(CFLAGS) $^ -fsanitize=undefined -rdynamic -o $@ $(INCLUDE_FLAGS) -L../ft_mallocator -lmallocator

valgrind: all ## Launch valgrind
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re debug rebug valgrind malloc_test re_malloc_test

################################################################################

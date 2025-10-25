# Variables

CC= cc
CFLAGS= -Wall -Wextra -Werror -Iincludes -Ilibft
SRC= \
	src/main.c \
	src/signal.c \
	src/parsing/lexer.c \
	src/parsing/parser.c \
	src/parsing/expander.c \
	src/utils/struct.c \
	src/utils/subshell.c \
	src/utils/ast.c \
	src/utils/print.c \
	src/utils/redirect.c \
	src/utils/string.c \
	src/utils/error.c \
	src/utils/validate.c \
	src/utils/token.c \
	src/utils/type.c \
	src/utils/node.c \
	src/utils/quotes.c \
	src/utils/check_command.c \
	src/utils/close_redir.c \
	src/utils/pid_add.c \
	src/utils/last_return.c \
	src/utils/build_path.c \
	src/utils/find_path.c \
	src/utils/env.c \
	src/utils/close_fdlst.c \
	src/utils/add_var.c \
	src/execution/and_handle.c \
	src/execution/or_handle.c \
	src/execution/builtin_handler.c \
	src/execution/redirection.c \
	src/execution/heredoc.c \
	src/execution/executor.c \
	src/execution/pipe_handle.c \
	src/execution/find_heredoc.c \
	src/execution/handler.c \
	src/builtins/cd.c \
	src/builtins/env.c \
	src/builtins/exit.c \
	src/builtins/pwd.c \
	src/builtins/export.c \
	src/builtins/unset.c \
	src/builtins/echo.c \
	src/builtins/export_utils.c
	
OBJ= $(SRC:.c=.o)
NAME= minishell
LIBFT_DIR= libft
LIBFT= $(LIBFT_DIR)/libft.a
LIBRL= -lreadline

# Makeflags
MAKEFLAGS += --no-print-directory

# Colors
RED := \033[31m
GREEN := \033[32m
YELLOW := \033[33m
BLUE := \033[34m
RESET := \033[0m

# Rules
all: $(NAME)

$(LIBFT):
	@echo "📚 ${BLUE}Compiling:${RESET} libft"
	@$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(OBJ) $(LIBFT)
	@echo "💻 ${GREEN}Building:${RESET} ${NAME}"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LIBRL)

%.o: %.c
	@echo "🛠️  ${BLUE}Compiling:${RESET} $< to $@"
	@$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g -o0
debug: re
	@echo "⚠️  ${RED}Compilation mode:${RESET} debug"

clean:
	@echo "🧹 ${YELLOW}Cleaning: ${RESET}project objects"
	@rm -rf $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "🧹 ${YELLOW}Cleaning: ${RESET}libft objects"

fclean: clean
	@echo "💣 ${YELLOW}Cleaning: ${RESET}everything"
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus debug

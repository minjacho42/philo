.DEFAULT_GOAL := all
SRCS = \
		philo_atoi.c philo_alloc.c philo_init.c \
		philo_main.c philo_thread.c philo_time.c \
		philo_util.c philo_util_mutex.c
SRCS_BONUS = \

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
DEPS = $(SRCS:.c=.d)
DEPS_BONUS = $(SRCS_BONUS:.c=.d)
CC = cc -Wall -Wextra -Werror -MMD -MP -g -fsanitize=thread
NAME = philo
MANDA = .manda
BONUS = .bonus
-include $(DEPS)

all :
	@echo "PHILO : make $(NAME)"
	@make $(MANDA)

bonus :
	@echo "PHILO : make BONUS"
	@make $(BONUS)

$(NAME) : $(LIBFT) $(OBJS)
	@make $(MANDA)

$(MANDA) : $(LIBFT) $(OBJS)
	@rm -rf $(BONUS)
	@touch $(MANDA)
	@$(CC) -o $(NAME) $(OBJS)

$(BONUS) : $(LIBFT) $(OBJS_BONUS)
	@rm -rf $(MANDA)
	@touch $(BONUS)
	@$(CC) -o $(NAME) $(OBJS_BONUS)

%.o : %.c
	@$(CC) -c $<

clean :
	@echo "PHILO : make clean"
	@rm -f $(OBJS) $(DEPS) $(OBJS_BONUS) $(BONUS) $(MANDA) $(DEPS_BONUS)

fclean :
	@echo "PHILO : make fclean"
	@rm -f $(OBJS) $(NAME) $(DEPS) $(OBJS_BONUS) $(BONUS) $(MANDA) $(DEPS_BONUS)

re : fclean
	@ echo "PHILO : make re"
	@ make all

.PHONY: all clean fclean re

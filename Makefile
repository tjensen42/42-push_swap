# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 22:03:08 by tjensen           #+#    #+#              #
#    Updated: 2021/10/28 15:02:57 by tjensen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= project

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror

SRCS		:= project.c
LDLIBS		:= -lft

LIBDIRS		:= $(wildcard libs/*)
LDLIBS		:= $(addprefix -L./, $(LIBDIRS)) $(LDLIBS)
INCLUDES	:= -I./include/ $(addprefix -I./, $(addsuffix /include, $(LIBDIRS)))

SDIR		:= src
ODIR		:= obj
OBJS		:= $(addprefix $(ODIR)/, $(SRCS:.c=.o))

# COLORS
Y 			= "\033[33m"
R 			= "\033[31m"
G 			= "\033[32m"
B 			= "\033[34m"
X 			= "\033[0m"

# **************************************************************************** #
#	SYSTEM SPECIFIC SETTINGS							   					   #
# **************************************************************************** #

UNAME_S		:= $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	CFLAGS += -D LINUX -Wno-unused-result
endif

# **************************************************************************** #
#	FUNCTIONS									   							   #
# **************************************************************************** #

define MAKE_LIBS
	for DIR in $(LIBDIRS); do \
		$(MAKE) -C $$DIR $(1) --silent; \
	done
endef

# **************************************************************************** #
#	RULES																	   #
# **************************************************************************** #

.PHONY: all $(NAME) header prep clean fclean re bonus debug release libs

all: $(NAME)

$(NAME): libs header prep $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)
	@printf "=== finished\n"

$(ODIR)/%.o: $(SDIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

header:
	@printf "### $(NAME)\n"

prep:
	@mkdir -p $(ODIR)

clean: libs header
	@$(RM) -r $(ODIR)

fclean: libs header clean
	@$(RM) $(NAME)

re: header fclean all

bonus: all

debug: CFLAGS += -O0 -DDEBUG -g
debug: all

release: fclean
release: CFLAGS	+= -O2 -DNDEBUG
release: all clean

libs:
ifeq ($(MAKECMDGOALS), $(filter $(MAKECMDGOALS), clean fclean re debug release))
	@$(call MAKE_LIBS,$(MAKECMDGOALS))
else
	@$(call MAKE_LIBS,all)
endif

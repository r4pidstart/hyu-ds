%: %.c
	gcc $@.c -o $@ -Wall -Werror -Wextra -pedantic -g3 -fsanitize=address
	./$@
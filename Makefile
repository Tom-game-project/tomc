CC = cc
RM = rm

CC_VERSION = $(CC) --version
VALGRIND = valgrind
VALGRINDFLAGS := --leak-check=full --trace-children=yes --track-fds=yes --show-leak-kinds=all

RMFLAGS = -rf

CFLAGS = -Wextra -Werror -Wall
ALLOC_SRC = src/alloc/my_malloc.c
# CFLAGS_MAIN =  -Wl,--wrap=malloc
DEBUGFLAGS = -g -DDEBUG
TEST_FLAGS = -g
# TEST_FLAGS +=  -Wl,--wrap=malloc


CHAR_LIST = \
		src/list/char_list_push.c\
		src/list/char_list_pop.c\
		src/list/char_list_len.c\
		src/list/char_list_print.c\
		src/list/char_list_init.c\
		src/list/char_list_get_elem.c\
		src/list/char_list_get_ptr.c\
		src/list/char_list_insert.c\
		src/list/char_list_insert_str.c\
		src/list/char_list_get_back.c\
		src/list/char_list_clear.c\
		src/list/char_list_to_str.c\
		src/list/char_list_is_empty.c\
		src/list/char_list_cut.c\
		src/list/char_list_search.c\
		src/list/char_list_startswith.c\
		src/list/char_list_endswith.c\


STR_LIST = \
		src/list/str_list_init.c\
		src/list/str_list_get_ptr.c\
		src/list/str_list_get_back.c\
		src/list/str_list_push.c\
		src/list/str_list_pop.c\
		src/list/str_list_print.c\
		src/list/str_list_len.c\
		src/list/str_list_clear.c\
		src/list/str_list_to_str.c\
		src/list/str_list_to_array.c\
		src/list/str_list_trim.c\
		src/list/str_list_len_sum.c\
		src/list/str_list_join.c\
		src/list/str_list_split.c\
		src/list/str_list_map.c\
		src/list/str_list_search.c\
		src/list/str_list_search2.c\
		src/list/str_list_get_elem.c\
		src/list/str_list_concat.c\
		src/list/str_list_clone.c\
		src/list/str_list_cut.c\
		src/list/str_list_in.c\
		src/list/candy_cutter.c\


INT_LIST = \
		src/list/int_list_len.c\
		src/list/int_list_push.c\
		src/list/int_list_print.c\
		src/list/int_list_init.c\
		src/list/int_list_clear.c\
		src/list/int_list_pop.c\
		src/list/int_list_insert.c\


VOID_LIST = \
		src/list/void_list_init.c\
		src/list/void_list_push.c\
		src/list/void_list_clear.c\
		src/list/void_list_print.c\
		src/list/void_list_get_back.c\
		src/list/void_list_len.c\
		src/list/void_list_get_elem.c\
		src/list/void_list_insert.c\
		src/list/void_list_pop.c\
		src/list/void_list_map.c\
		src/list/void_list_search.c\
		src/list/void_list_concat.c\
		src/list/void_list_cut.c\
		src/list/void_list_sort.c\
		src/list/void_list_insert_list.c\
		src/list/void_list_filter.c\


LIST_LIST = \
		src/list/list_list_print.c\
		src/list/list_list_all_concat.c\


TEST_TOOLS_SRC = \
		src/test_tools/print_token_list.c\
		src/test_tools/print.c


TOKENIZER_SRC = \
		src/tokenizer/init_token.c\
		src/tokenizer/tokenizer.c\

LIST_SRC = \
     $(INT_LIST)\
     $(CHAR_LIST)\
     $(STR_LIST)\
     $(LIST_LIST)\
     $(VOID_LIST)\


SRC = \
      $(LIST_SRC)\
      $(TEST_TOOLS_SRC)\
      $(TOKENIZER_SRC)


MAIN = \
	src/main.c


# test rule
TEST_FILE := tests/dummy_test.c
TEST_NAME = test_


# example rule
EXAMPLE_FILE := examples/dummy_example00.c
EXAMPLE_NAME = example_

LIBFT_DIR = lib/libft
LIBFT_NAME = $(LIBFT_DIR)/libft.a
LIBFT_HEADER = $(LIBFT_DIR)/libft.h

#########


OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_FILE:.c=.o)


NAME = tomc


all: $(NAME)

debug: CFLAGS+=$(DEBUGFLAGS)
debug: $(NAME)


COMMIT_HASH = $(shell git show --format='%h' --no-patch)
BUILD_TIMESTAMP = $(shell date "+%Y\/%m\/%d-%H:%M:%S")
CC_VERSION = $(shell $(CC) --version | head -n1)


$(NAME): $(OBJ) $(LIBFT_NAME) $(MAIN)
	@cat $(MAIN) \
		| $(CC) $(CFLAGS) $(CFLAGS_MAIN)\
		-Iinclude \
		-o $(NAME) \
		$(OBJ) $(LIBFT_NAME) \
		-x c -\


$(LIBFT_NAME):
	make -C $(LIBFT_DIR)


test: cleantest debug $(OBJ) $(TEST_OBJ) $(LIBFT_NAME)
	$(CC) $(TEST_FLAGS) -Iinclude -o $(TEST_NAME) $(OBJ) $(TEST_OBJ) $(LIBFT_NAME)
	./test_


vtest: cleantest debug $(OBJ) $(TEST_OBJ) $(LIBFT_NAME)
	$(CC) $(TEST_FLAGS) -Iinclude -o $(TEST_NAME) $(OBJ) $(TEST_OBJ) $(LIBFT_NAME)
	$(VALGRIND) $(VALGRINDFLAGS) ./test_


example:
	$(CC) $(TEST_FLAGS) -o $(EXAMPLE_NAME) $(EXAMPLE_FILE)


%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@


cleantest:
	$(RM) $(RMFLAGS) $(TEST_OBJ)


clean:
	$(RM) $(RMFLAGS) $(OBJ)


fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(RMFLAGS) $(NAME)


re: fclean all

.PHONY: all test vtest clean fclean re example cleantest debug

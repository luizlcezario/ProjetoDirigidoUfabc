NAME  = compress

SRC = main.c huffman.c lz.c


all: $(NAME)

$(NAME): 
	gcc -o $(NAME) $(addprefix C/, $(SRC))


clean:
	rm -f $(NAME)

re: clean all

.PHONY: all clean re
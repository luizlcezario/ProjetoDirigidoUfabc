NAME  = compress_c

NAME2 = compress_rust

SRC = main.c huffman.c lz.c


all: $(NAME) $(NAME2)

$(NAME): 
	gcc -O3 -o $(NAME) $(addprefix C/, $(SRC))

$(NAME2):
	cd rust && cargo build --release 
	cp rust/target/release/rust $(NAME2) 

clean:
	rm -f $(NAME)
	rm -f $(NAME2)

re: clean all

.PHONY: all clean re
#ifndef Process_h
#define Process_h
#define MAX_TREE_HT 100000000
#define WINDOW_SIZE 4096
#define LOOKAHEAD_BUFFER_SIZE 15
#define MAX_TUPLES 100000000
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int offset;
    int length;
    char next_char;
} LZ77Tuple;

// Estrutura de nó para a árvore de Huffman
struct MinHeapNodeLZ77 {
    LZ77Tuple tuple;
    unsigned freq;
    struct MinHeapNodeLZ77 *left, *right;
};

// Estrutura da heap mínima
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNodeLZ77** array;
};
void lz77_compress(const char* input, LZ77Tuple* output, int* output_size);

void lz77_decompress(LZ77Tuple* tuples, int tupleCount, char* output);
LZ77Tuple* decodeHuffman(struct MinHeapNodeLZ77* root, const char* encodedStr, int* decodedSize);
void  compressWithHuffman(LZ77Tuple data[], int freq[], int size, char** codes, int tuple_count);
#endif
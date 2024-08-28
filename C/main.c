
#include "process.h"

void calculate_frequencies(LZ77Tuple* tuples, int size, int* freq) {
    for (int i = 0; i < size; i++) {
        freq[i] = 1;
        for (int j = i + 1; j < size; j++) {
            if (tuples[i].offset == tuples[j].offset &&
                tuples[i].length == tuples[j].length &&
                tuples[i].next_char == tuples[j].next_char) {
                freq[i]++;
                // Marcando a tupla duplicada como processada
                tuples[j].offset = -1;
                tuples[j].length = -1;
                tuples[j].next_char = '\0';
            }
        }
    }
}

char *generateCompress(char *input) {
    LZ77Tuple lz77_output[MAX_TUPLES];
    int lz77_output_size = 0;
    int freq[MAX_TUPLES];

    // Compressão LZ77
    lz77_compress(input, lz77_output, &lz77_output_size);

    // Array de frequências
    calculate_frequencies(lz77_output, lz77_output_size, freq);

    char codes[lz77_output_size][10];
    compressWithHuffman(lz77_output, freq, lz77_output_size, (char **)codes, lz77_output_size);

    
}


char* read_file(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    // Move o ponteiro do arquivo para o final
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Aloca memória para armazenar o conteúdo do arquivo
    char *buffer = (char*)malloc(sizeof(char) * (file_size + 1));
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    // Lê o arquivo inteiro na memória
    int result = fread(buffer, 1, file_size, file);
    if (result != file_size) {
        perror("Failed to read file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[file_size] = '\0'; // Adiciona o terminador nulo ao final
    fclose(file);
    return buffer;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        char usage[] = "abracadabra";
        generateCompress(usage);
    } else {
        char * file = read_file(argv[1]);
        generateCompress(file);
    }
    return 0;
}


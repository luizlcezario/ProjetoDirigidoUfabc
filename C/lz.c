#include "process.h"


void lz77_compress(const char* input, LZ77Tuple* output, int* output_size) {
    int input_length = strlen(input);
    int i = 0, j, k;
    int match_length, match_distance;
    *output_size = 0;

    while (i < input_length) {
        match_length = 0;
        match_distance = 0;

        // Procurar a maior correspondência dentro da janela deslizante
        for (j = (i > WINDOW_SIZE) ? i - WINDOW_SIZE : 0; j < i; j++) {
            k = 0;
            while (k < LOOKAHEAD_BUFFER_SIZE && i + k < input_length && input[j + k] == input[i + k])
                k++;
            if (k > match_length) {
                match_length = k;
                match_distance = i - j;
            }
        }

        // Gerar uma tupla (offset, length, próximo caractere)
        output[*output_size].offset = match_distance;
        output[*output_size].length = match_length;
        output[*output_size].next_char = (i + match_length < input_length) ? input[i + match_length] : '\0';
        (*output_size)++;

        i += match_length + 1;
    }
}


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

int main(int argc, char **argv) {
    if (argc != 2) {
        char usage[] = "abracadabra";
        generateCompress(usage);
    } else {
        generateCompress(argv[1]);
    }
    return 0;
}


Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc finibus ligula in erat rhoncus volutpat. Interdum et malesuada fames ac ante ipsum primis in faucibus. Morbi tempor urna metus, et scelerisque sapien scelerisque sit amet. Vivamus accumsan elementum lorem, varius lacinia nisi rutrum id. Quisque turpis ex, ultricies et vestibulum ut, accumsan vitae lacus. Donec a condimentum neque. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Aenean lobortis ultrices eros vel dapibus. In hac habitasse platea dictumst. Maecenas interdum leo at sapien venenatis, at malesuada mauris pellentesque. Integer eu facilisis mauris. Nunc pretium dapibus tellus, nec auctor mauris iaculis sit amet. Nullam eu congue sem, ac dignissim ligula. Sed tempor accumsan ipsum.

Morbi ac ornare lectus, sit amet congue mauris. Cras quis justo sed arcu semper imperdiet. Suspendisse eget euismod ante. Mauris ultrices a justo quis varius. Quisque posuere vel eros et molestie. Donec in enim mauris. Nam sit amet dapibus ligula. Praesent congue mattis nunc, eu volutpat mauris blandit vel. Mauris feugiat nunc non libero tempus, vitae egestas leo iaculis. Fusce tincidunt leo sed nisl malesuada suscipit. Cras eu lacinia dui. Mauris non tristique erat. Phasellus lectus elit, sagittis vel lobortis a, iaculis ut mi.

Nam nisl nulla, mollis id urna egestas, dignissim mattis leo. Cras laoreet faucibus dui id sollicitudin. Nunc a nulla rhoncus, congue libero vitae, iaculis arcu. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Aliquam ullamcorper est eu metus dictum semper a a velit. Nam faucibus tortor non auctor ultrices. Nunc venenatis vestibulum volutpat. Ut feugiat, nibh vel tempor elementum, elit nisi efficitur sem, quis elementum sem orci id magna.

Cras non pellentesque nisi. Nulla tortor arcu, convallis eget mi nec, cursus faucibus urna. Suspendisse ac libero id lorem facilisis interdum ac et tellus. Nunc nec tristique mauris, ut varius sapien. Praesent vitae neque quis mauris accumsan elementum. Praesent volutpat ante sed dictum pellentesque. Praesent ut porttitor arcu, nec mollis massa. Etiam hendrerit aliquet nisl, eu sollicitudin velit molestie id. Donec sem odio, varius eget erat vitae, placerat feugiat massa. Duis quis consequat mi. Mauris placerat risus sed ipsum consectetur tempus. In eros libero, iaculis in nibh sit amet, aliquet cursus elit. Sed id tortor porta, lacinia nulla et, mollis nunc. Praesent cursus a ligula quis vehicula.

Nunc nulla orci, gravida pharetra blandit ac, porttitor sit amet nunc. Aenean elit lacus, dignissim eu aliquam eget, dictum sed velit. Donec hendrerit gravida mi id bibendum. Phasellus at tellus et est pretium consequat nec in mi. Suspendisse vehicula ut nulla ac eleifend. Proin magna lorem, accumsan eu tincidunt eget, cursus eu ante. Quisque semper elit et nibh suscipit, eu venenatis nisi semper. Fusce in nulla lacus. Mauris id nisl vel nisi tempor gravida. Quisque sollicitudin suscipit orci sit amet posuere. In vitae nibh neque. Donec ut facilisis massa, interdum consequat magna. Quisque placerat est nisi, suscipit sollicitudin massa imperdiet at. 

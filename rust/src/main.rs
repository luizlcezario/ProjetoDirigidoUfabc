pub mod lz;
pub mod huffman;

fn main() {
    let args: Vec<String> = std::env::args().collect();

    if args.len() == 2 {
        compress_lz77_huffman(&args[1]);
    } else {
        let input = "abracadabra".to_string();
        compress_lz77_huffman(&input);
    }
}

fn calculate_frequencies(tuples: &mut Vec<lz::LZ77Tuple>, freq: &mut [usize]) {
    for i in 0..tuples.len() {
        freq[i] = 1;
        for j in (i + 1)..tuples.len() {
            if tuples[i].offset == tuples[j].offset &&
               tuples[i].length == tuples[j].length &&
               tuples[i].next_char == tuples[j].next_char {
                freq[i] += 1;
                // Marcando a tupla duplicada como processada
                tuples[j].offset = -1;
                tuples[j].length = -1;
                tuples[j].next_char = '\0';
            }
        }
    }
}

// Exemplo de assinatura da função compress_lz77_huffman
fn compress_lz77_huffman(input: &str) {
    // 1. Compressão LZ77
    const MAX_TUPLES: usize = 1000; // Exemplo, ajuste conforme necessário
    let mut lz77_output: Vec<lz::LZ77Tuple> = Vec::with_capacity(MAX_TUPLES);
    let mut freq: Vec<usize> = vec![0; MAX_TUPLES];
    
    let mut lz77_output_size = 0;
    lz::lz77_compress(input, &mut lz77_output, &mut lz77_output_size);

    // 2. Aplicar Huffman às tuplas geradas por LZ77
    // Vamos simplificar aqui e assumir que todos os códigos Huffman já foram gerados para cada tupla
    // Em uma aplicação real, você geraria a árvore de Huffman para as tuplas e a utilizaria para codificar
    calculate_frequencies(& mut lz77_output, &mut freq);
    let mut codes: Vec<String> = Vec::new();
    huffman::compress_with_huffman(&lz77_output, &freq, &mut codes);
}

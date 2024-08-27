

#[derive(Debug, Clone, Copy)]
pub struct LZ77Tuple {
    pub offset: i32,     // Correspondente a int em C
    pub length: i32,     // Correspondente a int em C
    pub next_char: char, // Correspondente a char em C
}

const LOOKAHEAD_BUFFER_SIZE : usize = 15;
const WINDOW_SIZE: usize =  4096;// Tamanho do buffer de busca

pub fn lz77_compress(input: &str, output: &mut Vec<LZ77Tuple>, output_size: &mut usize) {
    let input_length = input.len();
    let mut i = 0;

    *output_size = 0;

    while i < input_length {
        let mut match_length = 0;
        let mut match_distance = 0;

        // Procurar a maior correspondência dentro da janela deslizante
        let start = if i > WINDOW_SIZE { i - WINDOW_SIZE } else { 0 };
        for j in start..i {
            let mut k = 0;
            while k < LOOKAHEAD_BUFFER_SIZE && i + k < input_length && input.as_bytes()[j + k] == input.as_bytes()[i + k] {
                k += 1;
            }
            if k > match_length {
                match_length = k;
                match_distance = i - j;
            }
        }

        // Gerar uma tupla (offset, length, próximo caractere)
        let next_char = if i + match_length < input_length {
            input.as_bytes()[i + match_length] as char
        } else {
            '\0'
        };

        output.push(LZ77Tuple {
            offset: match_distance as i32,
            length: match_length as i32,
            next_char,
        });

        *output_size += 1;
        i += match_length + 1;
    }
}
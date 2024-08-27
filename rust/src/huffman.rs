use crate::lz;

const MAX_TREE_HT: usize = 100;

#[derive(Debug, Clone)]
pub struct MinHeapNodeLZ77 {
    pub tuple: lz::LZ77Tuple,    // Mesma estrutura LZ77Tuple
    pub freq: usize,           // Correspondente a unsigned em C
    pub left: Option<Box<MinHeapNodeLZ77>>,  // Ponteiro opcional para outro MinHeapNodeLZ77
    pub right: Option<Box<MinHeapNodeLZ77>>, // Ponteiro opcional para outro MinHeapNodeLZ77
}


#[derive(Debug, Clone)]
pub struct MinHeap {
    pub size: usize,                     // Correspondente a unsigned em C
    pub capacity: usize,                 // Correspondente a unsigned em C
    pub array: Vec<Box<MinHeapNodeLZ77>>, // Vetor de ponteiros para MinHeapNodeLZ77
}

fn new_node_lz77(tuple: lz::LZ77Tuple, freq: usize) -> Box<MinHeapNodeLZ77> {
    Box::new(MinHeapNodeLZ77 {
        tuple,
        freq,
        left: None,
        right: None,
    })
}

fn create_min_heap(capacity: usize) -> MinHeap {
    MinHeap {
        size: 0,
        capacity,
        array: Vec::with_capacity(capacity),
    }
}


fn min_heapify(min_heap: &mut MinHeap, idx: usize) {
    let mut smallest = idx;
    let left = 2 * idx + 1;
    let right = 2 * idx + 2;

    if left < min_heap.size && min_heap.array[left].freq < min_heap.array[smallest].freq {
        smallest = left;
    }

    if right < min_heap.size && min_heap.array[right].freq < min_heap.array[smallest].freq {
        smallest = right;
    }

    if smallest != idx {
        min_heap.array.swap(smallest, idx);
        min_heapify(min_heap, smallest);
    }
}

fn extract_min(min_heap: &mut MinHeap) -> Box<MinHeapNodeLZ77> {
    let temp = min_heap.array.swap_remove(0);
    min_heap.size -= 1;
    min_heapify(min_heap, 0);
    temp
}

fn insert_min_heap(min_heap: &mut MinHeap, min_heap_node: Box<MinHeapNodeLZ77>) {
    min_heap.size += 1;
    let mut i = min_heap.size - 1;
    while i > 0 && min_heap_node.freq < min_heap.array[(i - 1) / 2].freq {
        if i < min_heap.array.len() {
            min_heap.array[i] = min_heap.array[(i - 1) / 2].clone();
        } else {
            min_heap.array.push(min_heap.array[(i - 1) / 2].clone());
        }
        i = (i - 1) / 2;
    }
    if i < min_heap.array.len() {
        min_heap.array[i] = min_heap_node;
    } else {
        min_heap.array.push(min_heap_node);
    }
}

fn build_min_heap(min_heap: &mut MinHeap) {
    let n = min_heap.size - 1;
    for i in (0..=((n - 1) / 2)).rev() {
        min_heapify(min_heap, i);
    }
}

fn build_huffman_tree_lz77(data: &[lz::LZ77Tuple], freq: &[usize]) -> Box<MinHeapNodeLZ77> {
    let mut min_heap = create_min_heap(data.len());
    for i in 0..data.len() {
        min_heap.array.push(new_node_lz77(data[i], freq[i]));
    }
    min_heap.size = data.len();
    build_min_heap(&mut min_heap);

    while min_heap.size > 1 {
        let left = extract_min(&mut min_heap);
        let right = extract_min(&mut min_heap);

        let combined_tuple = lz::LZ77Tuple { offset: 0, length: 0, next_char: '$' };
        let mut top = new_node_lz77(combined_tuple, left.freq + right.freq);
        top.left = Some(left);
        top.right = Some(right);

        insert_min_heap(&mut min_heap, top);
    }

    extract_min(&mut min_heap)
}

pub fn compress_with_huffman(data: &[lz::LZ77Tuple], freq: &[usize], codes: &mut Vec<String>) {
    let root = build_huffman_tree_lz77(data, freq);

    let mut arr = Vec::with_capacity(MAX_TREE_HT);
    let  top = 0;

    generate_huffman_codes(&root, &mut arr, top, codes);

    for code in codes.iter() {
        print!("{}", code);
    }
    println!();
}


fn generate_huffman_codes(
    node: &Box<MinHeapNodeLZ77>,
    arr: &mut Vec<i32>,
    top: usize,
    codes: &mut Vec<String>,
) {
    if let Some(ref left) = node.left {
        arr.push(0);
        generate_huffman_codes(left, arr, top + 1, codes);
        arr.pop();
    }

    if let Some(ref right) = node.right {
        arr.push(1);
        generate_huffman_codes(right, arr, top + 1, codes);
        arr.pop();
    }

    if node.left.is_none() && node.right.is_none() {
        let code = arr.iter().map(|&bit| (bit + b'0' as i32) as u8 as char).collect::<String>();
        codes.push(code);
    }
}

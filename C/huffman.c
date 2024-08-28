
#include "process.h"
// Estrutura para armazenar as tuplas do LZ77

// Função para criar um novo nó de árvore de Huffman para LZ77
struct MinHeapNodeLZ77* newNodeLZ77(LZ77Tuple tuple, unsigned freq) {
    struct MinHeapNodeLZ77* temp = (struct MinHeapNodeLZ77*)malloc(sizeof(struct MinHeapNodeLZ77));
    temp->left = temp->right = NULL;
    temp->tuple = tuple;
    temp->freq = freq;
    return temp;
}


// Função para criar uma heap mínima
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNodeLZ77**)malloc(minHeap->capacity * sizeof(struct MinHeapNodeLZ77*));
    return minHeap;
}

// Função para trocar dois nós
void swapMinHeapNode(struct MinHeapNodeLZ77** a, struct MinHeapNodeLZ77** b) {
    struct MinHeapNodeLZ77* t = *a;
    *a = *b;
    *b = t;
}

// Função para garantir que a propriedade da heap mínima seja mantida
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Função para extrair o nó de menor frequência da heap mínima
struct MinHeapNodeLZ77* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNodeLZ77* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Função para inserir um nó na heap mínima
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNodeLZ77* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Função para construir a heap mínima a partir de um array de nós de árvore
void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// Função para construir a árvore de Huffman a partir das tuplas do LZ77
struct MinHeapNodeLZ77* buildHuffmanTreeLZ77(LZ77Tuple data[], int freq[], int size) {
    struct MinHeapNodeLZ77 *left, *right, *top;

    // Criação e construção da heap mínima (MinHeap)
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNodeLZ77(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);

    // Construção da árvore de Huffman
    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        LZ77Tuple combinedTuple = {0, 0, '$'};  // Símbolo placeholder
        top = newNodeLZ77(combinedTuple, left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    // O nó restante na heap é a raiz da árvore de Huffman
    return extractMin(minHeap);
}

// Função para gerar os códigos Huffman a partir da árvore de Huffman
void generateHuffmanCodes(struct MinHeapNodeLZ77* root, int arr[], int top, char** codes, int* index) {
    if (root->left) {
        arr[top] = 0;
        generateHuffmanCodes(root->left, arr, top + 1, codes, index);
    }

    if (root->right) {
        arr[top] = 1;
        generateHuffmanCodes(root->right, arr, top + 1, codes, index);
    }

    if (!(root->left) && !(root->right)) {
        codes[*index] = (char*)malloc(top + 1);
        for (int i = 0; i < top; ++i) {
            codes[*index][i] = arr[i] + '0';
        }
        codes[*index][top] = '\0';
        (*index)++;
    }
}

// Função para codificar o texto original usando os códigos Huffman
void compressWithHuffman(LZ77Tuple data[], int freq[], int size, char** codes, int tuple_count) {
    struct MinHeapNodeLZ77* root = buildHuffmanTreeLZ77(data, freq, size);

    int arr[MAX_TREE_HT], top = 0;
    int index = 0;
    generateHuffmanCodes(root, arr, top, codes, &index);
    // for (int i = 0; i < tuple_count; i++) {
    //     // printf("%s", codes[i]);
    // }
    // printf("\n");
}
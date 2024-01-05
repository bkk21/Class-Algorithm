#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

// Huffman tree node
struct HuffNode {
    char data;
    unsigned freq;
    struct HuffNode *left, *right;
};

// Huffman min heap
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct HuffNode **arr;
};

// create a new Huffman tree node
struct HuffNode* newNode(char data, unsigned freq) {
    struct HuffNode* node = (struct HuffNode*)malloc(sizeof(struct HuffNode));
    node->left = node->right = NULL;
    node->data = data;
    node->freq = freq;
    return node;
}

// create a new Huffman min heap
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minH = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minH->size = 0;
    minH->capacity = capacity;
    minH->arr = (struct HuffNode**)malloc(capacity * sizeof(struct HuffNode*));
    return minH;
}

// swap two Huffman min heap nodes
void swap(struct HuffNode** a, struct HuffNode** b) {
    struct HuffNode* t = *a;
    *a = *b;
    *b = t;
}

// min heapify
void minHeapify(struct MinHeap* minHeap, int p) {
    int min = p;
    int lt = 2*p + 1;
    int rt = 2*p + 2;

    if (lt < minHeap->size && minHeap->arr[lt]->freq < minHeap->arr[min]->freq)
        min = lt;

    if (rt < minHeap->size && minHeap->arr[rt]->freq < minHeap->arr[min]->freq)
        min = rt;

    if (min != p) {
        swap(&minHeap->arr[min], &minHeap->arr[p]);
        minHeapify(minHeap, min);
    }
}

// check if the size of heap is 1
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// extract minimum node from heap
struct HuffNode* extractMin(struct MinHeap* minHeap) {
    struct HuffNode* temp = minHeap->arr[0];
    minHeap->arr[0] = minHeap->arr[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// insert a new node into min heap
void insertMinHeap(struct MinHeap* minHeap, struct HuffNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->arr[(i - 1) / 2]->freq) {
        minHeap->arr[i] = minHeap->arr[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->arr[i] = minHeapNode;
}

// build Huffman tree
struct HuffNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct HuffNode *left, *right, *top;
    struct MinHeap* minHeap = createMinHeap(size);
// 주어진 문자와 빈도로 새로운 허프만 트리 노드 생성
    for (int i = 0; i < size; ++i)
        insertMinHeap(minHeap, newNode(data[i], freq[i]));

// 두 개의 최소 빈도 노드를 반복적으로 추출하고 병합하여 Huffman 트리를 구축합니다.
    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

// print Huffman codes from the root of the Huffman tree
void printCodes(struct HuffNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (!root->left && !root->right) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// Huffman coding main function
void HuffmanCodes(char data[], int freq[], int size) {
    struct HuffNode* root = buildHuffmanTree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
}




// test example
int main() {
   char data[] = {'k', 'i', 'm', 'c', 'h', 'a', 'n', 'g', 'x', '1', '0', '6', 'o', 'e', 'b', 's'};
   int  freq[] = { 2,   3,   3,   2,   4,   3,   3,   2,   1,   2,   4,   2,   1,   1,   2,   1};
   // char data[36];
    //int  freq[36] = {0,};
    char c;
    
    FILE *fp;
    fp = fopen("/etc/passwd", "r");
   /* while((c = fgetc(fp)) != EOF) {
        if ('a' <= c && c <= 'z')   freq[c - 'a']++;
        if ('0' <= c && c <= '9')   freq[26 + c - '0']++;
    }
    for (int i = 0; i < 36; i++) {
        if (i < 26) data[i] = 'a'+i;
        if (i >= 26 && i < 36)    data[i] = '0'+(i-26);
     //   printf("[%2d] %c: %d\n", i, data[i], freq[i]);
    }*/
    

    int size = sizeof(data) / sizeof(data[0]);
    HuffmanCodes(data, freq, size);
    return 0;
}

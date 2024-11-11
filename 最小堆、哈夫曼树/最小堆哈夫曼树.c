#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MTH 100
#define MC 256

// ���������Ľڵ�
// ������������С�ѽڵ�ṹ��
struct MinHeapNode {
    char data;  // �ڵ�������ַ���Ҷ�ӽڵ�ʱ���ַ����ڲ��ڵ�ʱ��'$'��
    unsigned freq;  // �ַ����ֵ�Ƶ�ʣ�ʹ���޷������ͣ�Ƶ��һ��Ϊ������
    struct MinHeapNode* left, * right;
};

// ��С��
struct MinHeap {
    unsigned size;  // ��ǰ���нڵ������
    unsigned capacity;  // �ѵ������������ڵ�����
    struct MinHeapNode** array;  // �洢�ѽڵ�����飬ÿ���ڵ���һ��ָ��
};

// ����һ���µ���С�ѽڵ�
struct MinHeapNode* createNode(char data, unsigned freq) {//�����ַ��Լ��ַ����ֵ�Ƶ��
    // �����ڴ沢��ʼ���ڵ�
    struct MinHeapNode* newNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    newNode->left = newNode->right = NULL;  // �½ڵ�û���ӽڵ�
    newNode->data = data;  // �����ַ�����
    newNode->freq = freq;  // �����ַ�Ƶ��
    return newNode;  // ���ش����Ľڵ�
}

// ����һ����С��
struct MinHeap* createMinHeap(unsigned capacity) {//����ѵ��������
    // �����ڴ沢��ʼ����С��
    struct MinHeap* minheap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minheap->size = 0;  // �ѵĴ�С��ʼ��Ϊ0
    minheap->capacity = capacity;  // ���öѵ��������
    minheap->array = (struct MinHeapNode**)malloc(minheap->capacity * sizeof(struct MinHeapNode*));  // Ϊ�ѽڵ���������ڴ�
    return minheap;  // ���ش����Ķ�
}

// ����������С�ѽڵ�
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;  // ��ʱ����ڵ�a
    *a = *b;  // ����a��b
    *b = t;  // ��ɽ���
}

// �ѻ�������ά����С�ѵ����ʣ�
void minHeapify(struct MinHeap* minHeap, int idx) {//������С���Լ���ǰ�ڵ������
    int smallest = idx;  // ���赱ǰ�ڵ�����С�ڵ�
    int left = 2 * idx + 1;  // ���ӽڵ������
    int right = 2 * idx + 2;  // ���ӽڵ������

    // ������ӽڵ�С�ڵ�ǰ�ڵ㣬�������С�ڵ�Ϊ���ӽڵ�
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq) {
        smallest = left;
    }

    // ������ӽڵ�С�ڵ�ǰ�ڵ㣬�������С�ڵ�Ϊ���ӽڵ�
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq) {
        smallest = right;
    }

    // �����С�ڵ㲻�ǵ�ǰ�ڵ㣬�򽻻��������ѻ�
    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);  // �ݹ�ѻ�
    }
}

// �����С�ѵĴ�С�Ƿ�Ϊ1
int isSizeOne(struct MinHeap* minHeap) {
    return minHeap->size == 1;  // ����ѵĴ�СΪ1������1
}

// ��ȡ��С���е���С�ڵ㣨�Ѷ��ڵ㣩
struct MinHeapNode* extractMin(struct MinHeap* minheap) {
    struct MinHeapNode* temp = minheap->array[0];  // ����Ѷ��ڵ�
    minheap->array[0] = minheap->array[minheap->size - 1];  // ���ѵ�Ԫ���Ƶ��Ѷ�
    --minheap->size;  // ���ٶѵĴ�С
    minHeapify(minheap, 0);  // �ӶѶ���ʼ�ѻ������ֶѵ�����
    return temp;  // ���ضѶ��ڵ㣨��С�ڵ㣩
}

// ����С���в���һ���½ڵ�
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;  // ���ӶѵĴ�С
    int i = minHeap->size - 1;  // �½ڵ��λ�ã��ѵף�

    // ���ڵ��ϸ������ʵ�λ��
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];  // �ϸ��ڵ�
        i = (i - 1) / 2;  // ���µ�ǰ�ڵ�λ��
    }

    minHeap->array[i] = minHeapNode;  // ���ڵ���뵽���ʵ�λ��
}

// ������С��
void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;  // ���һ���ڵ������
    int i;

    // �ӵ����ڶ��㿪ʼ���жѻ�����֤�ѵ����ʣ�
    for (i = (n - 1) / 2; i >= 0; --i) {
        minHeapify(minHeap, i);  // �������϶ѻ�
    }
}

// ��ӡ�������飨���ڹ��������룩
void printArr(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d", arr[i]);  // ��ӡ�����е�ÿһλ
    }
    printf("\n");  // ����
}

// ����Ƿ���Ҷ�ӽڵ�
int isLeaf(struct MinHeapNode* root) {
    return !(root->left) && !(root->right);  // ���û�����ӽڵ�����ӽڵ㣬����Ҷ�ӽڵ�
}

// ������������С��
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);  // ����һ���յ���С��

    // Ϊÿ���ַ������ڵ㣬�����뵽��С����
    for (int i = 0; i < size; ++i) {
        minHeap->array[i] = createNode(data[i], freq[i]);  // �����ڵ㲢��ʼ��
    }
    minHeap->size = size;  // ���öѵĴ�С
    buildMinHeap(minHeap);  // ������С�ѣ�ȷ���ѵ�����

    return minHeap;  // ���ش����õ���С��
}

// ������������
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode* left, * right, * top;

    // ������������С�ѣ�data���ַ����飬freq���ַ�Ƶ�����飬size���ַ���Ŀ
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    // �������ж��Ԫ��ʱ���ظ���ȡ������С�Ľڵ㲢�����µĸ��ڵ�
    while (!isSizeOne(minHeap)) {//������Ԫ�ز�Ϊ1��ʱ��
        // �Ӷ�����ȡƵ����С�������ڵ�
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // ����һ���½ڵ㣬��Ƶ���������ӽڵ�Ƶ��֮��
        top = createNode('$', left->freq + right->freq);
        top->left = left;  // ����С�ڵ�֮һ��Ϊ���ӽڵ�
        top->right = right;  // ����һ����С�ڵ���Ϊ���ӽڵ�

        // ���½ڵ�������
        insertMinHeap(minHeap, top);
    }

    // ���ضѶ�Ԫ�أ������������ĸ��ڵ㣩
    return extractMin(minHeap);
}

// ���ɹ��������벢�洢��codes������
void printCodes(struct MinHeapNode* root, int arr[], int top, char* codes[]) {
    // ������ӽڵ���ڣ��ݹ����ɱ���
    if (root->left) {
        arr[top] = 0;  // ���ӽڵ���0��ʾ
        printCodes(root->left, arr, top + 1, codes);
    }

    // ������ӽڵ���ڣ��ݹ����ɱ���
    if (root->right) {
        arr[top] = 1;  // ���ӽڵ���1��ʾ
        printCodes(root->right, arr, top + 1, codes);
    }

    // �����ǰ�ڵ���Ҷ�ӽڵ㣨��û���ӽڵ㣩��˵���ҵ���һ���ַ��ı���
    if (isLeaf(root)) {
        // �����ǰ�ַ��������������
        printf("%c: ", root->data);
        printArr(arr, top);

        // Ϊ���ַ����������ַ���
        codes[root->data] = (char*)malloc(top + 1);
        for (int i = 0; i < top; i++) {
            codes[root->data][i] = arr[i] + '0';  // ��0��1תΪ�ַ�
        }
        codes[root->data][top] = '\0';  // Ϊ�����ַ���������ֹ��
    }
}

// ��������������
void HuffmanCodes(char data[], int freq[], int size, char* codes[]) {
    // data: ������ַ�����
    // freq: ������ַ�Ƶ������
    // size: �����ַ�����Ĵ�С
    // codes: ����Ĺ�������������

    // ���������������������ĸ��ڵ�
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);

    // ���ڴ洢���ɵı���·����arr[]��ʾ·����top��·���ĳ���
    int arr[MTH], top = 0;

    // ���ɲ���ӡ�����ַ��Ĺ���������
    printCodes(root, arr, top, codes);
}

// ������������
void encodeData(char* input, char* output, char* codes[]) {
    // input: Ҫ����������ַ���
    // output: �洢����������ַ���
    // codes: �洢ÿ���ַ��Ĺ��������������

    printf("����������: ");

    // ���������ַ�����ʹ�ù����������ÿ���ַ����б���
    for (int i = 0; input[i] != '\0'; i++) {
        // ����Ӧ�ַ��Ĺ�����������ӵ������
        strcat(output, codes[input[i]]);
    }

    // ����������ַ���
    printf("%s\n", output);
}

// ��������
void decodeData(struct MinHeapNode* root, char* encodedData) {
    // root: ���������ĸ��ڵ�
    // encodedData: ���������ݣ���'0'��'1'��ʾ��

    printf("����������: ");

    struct MinHeapNode* current = root;

    // �����������ݣ���λ����
    for (int i = 0; encodedData[i] != '\0'; i++) {
        // ����'0'��'1'��������������������������0�����ߣ�1������
        if (encodedData[i] == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        // �������Ҷ�ӽڵ㣬˵��������һ���ַ�
        if (isLeaf(current)) {
            // ������ַ������ع��������ĸ��ڵ��������
            printf("%c", current->data);
            current = root;
        }
    }
    printf("\n");
}


// �˵�ѡ��
void menu() {
    printf("ѡ��ѡ��:\n");
    printf("1 - ������������\n");
    printf("2 - �ļ���������\n");
    printf("0 - �˳�\n");
}

// ����ͳ���ַ�Ƶ��
void calculateFrequency(char* input, char data[], int freq[], int* size) {
    int charFreq[MC] = { 0 };

    for (int i = 0; input[i] != '\0'; i++) {
        charFreq[(int)input[i]]++;
    }

    *size = 0;
    for (int i = 0; i < MC; i++) {
        if (charFreq[i] > 0) {
            data[*size] = (char)i;
            freq[*size] = charFreq[i];
            (*size)++;
        }
    }
}

int main() {
    int choice;
    char input[1000];
    char encodedData[16000] = "";
    char data[MC];
    int freq[MC];
    int size;
    char* codes[MC] = { 0 };

    while (1) {
        menu();
        printf("������ѡ��");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("������ԭʼ���ݣ�");
            scanf("%s", input);
            break;
        case 2: {
            char filename[100];
            printf("�������ļ�����");
            scanf("%s", filename);
            FILE* file = fopen(filename, "r");
            if (file == NULL) {
                printf("�޷����ļ� %s\n", filename);
                continue;
            }
            fgets(input, sizeof(input), file);
            fclose(file);
            printf("��ȡ������: %s\n", input);
            break;
        }
        case 0:
            printf("���������\n");
            exit(0);
        default:
            printf("��Чѡ��\n");
            continue;
        }
        calculateFrequency(input, data, freq, &size);
        HuffmanCodes(data, freq, size, codes);
        encodeData(input, encodedData, codes);
        struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
        decodeData(root, encodedData);
        for (int i = 0; i < MC; i++) {
            if (codes[i] != NULL) {
                free(codes[i]);
            }
        }
    }
    return 0;
}
/*
1 abababccc
0
*/
/*
2
input.txt
0
*/
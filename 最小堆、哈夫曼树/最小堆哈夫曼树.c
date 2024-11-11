#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MTH 100
#define MC 256

// 哈夫曼树的节点
// 哈夫曼树的最小堆节点结构体
struct MinHeapNode {
    char data;  // 节点包含的字符（叶子节点时是字符，内部节点时是'$'）
    unsigned freq;  // 字符出现的频率，使用无符号类型，频率一定为正整数
    struct MinHeapNode* left, * right;
};

// 最小堆
struct MinHeap {
    unsigned size;  // 当前堆中节点的数量
    unsigned capacity;  // 堆的总容量（最大节点数）
    struct MinHeapNode** array;  // 存储堆节点的数组，每个节点是一个指针
};

// 创建一个新的最小堆节点
struct MinHeapNode* createNode(char data, unsigned freq) {//传入字符以及字符出现的频率
    // 分配内存并初始化节点
    struct MinHeapNode* newNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    newNode->left = newNode->right = NULL;  // 新节点没有子节点
    newNode->data = data;  // 设置字符数据
    newNode->freq = freq;  // 设置字符频率
    return newNode;  // 返回创建的节点
}

// 创建一个最小堆
struct MinHeap* createMinHeap(unsigned capacity) {//传入堆的最大容量
    // 分配内存并初始化最小堆
    struct MinHeap* minheap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minheap->size = 0;  // 堆的大小初始化为0
    minheap->capacity = capacity;  // 设置堆的最大容量
    minheap->array = (struct MinHeapNode**)malloc(minheap->capacity * sizeof(struct MinHeapNode*));  // 为堆节点数组分配内存
    return minheap;  // 返回创建的堆
}

// 交换两个最小堆节点
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;  // 临时保存节点a
    *a = *b;  // 交换a和b
    *b = t;  // 完成交换
}

// 堆化操作（维护最小堆的性质）
void minHeapify(struct MinHeap* minHeap, int idx) {//传入最小堆以及当前节点的索引
    int smallest = idx;  // 假设当前节点是最小节点
    int left = 2 * idx + 1;  // 左子节点的索引
    int right = 2 * idx + 2;  // 右子节点的索引

    // 如果左子节点小于当前节点，则更新最小节点为左子节点
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq) {
        smallest = left;
    }

    // 如果右子节点小于当前节点，则更新最小节点为右子节点
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq) {
        smallest = right;
    }

    // 如果最小节点不是当前节点，则交换并继续堆化
    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);  // 递归堆化
    }
}

// 检查最小堆的大小是否为1
int isSizeOne(struct MinHeap* minHeap) {
    return minHeap->size == 1;  // 如果堆的大小为1，返回1
}

// 提取最小堆中的最小节点（堆顶节点）
struct MinHeapNode* extractMin(struct MinHeap* minheap) {
    struct MinHeapNode* temp = minheap->array[0];  // 保存堆顶节点
    minheap->array[0] = minheap->array[minheap->size - 1];  // 将堆底元素移到堆顶
    --minheap->size;  // 减少堆的大小
    minHeapify(minheap, 0);  // 从堆顶开始堆化，保持堆的性质
    return temp;  // 返回堆顶节点（最小节点）
}

// 向最小堆中插入一个新节点
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;  // 增加堆的大小
    int i = minHeap->size - 1;  // 新节点的位置（堆底）

    // 将节点上浮至合适的位置
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];  // 上浮节点
        i = (i - 1) / 2;  // 更新当前节点位置
    }

    minHeap->array[i] = minHeapNode;  // 将节点插入到合适的位置
}

// 构建最小堆
void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;  // 最后一个节点的索引
    int i;

    // 从倒数第二层开始进行堆化（保证堆的性质）
    for (i = (n - 1) / 2; i >= 0; --i) {
        minHeapify(minHeap, i);  // 从下往上堆化
    }
}

// 打印编码数组（用于哈夫曼编码）
void printArr(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d", arr[i]);  // 打印编码中的每一位
    }
    printf("\n");  // 换行
}

// 检查是否是叶子节点
int isLeaf(struct MinHeapNode* root) {
    return !(root->left) && !(root->right);  // 如果没有左子节点和右子节点，则是叶子节点
}

// 创建并构建最小堆
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);  // 创建一个空的最小堆

    // 为每个字符创建节点，并插入到最小堆中
    for (int i = 0; i < size; ++i) {
        minHeap->array[i] = createNode(data[i], freq[i]);  // 创建节点并初始化
    }
    minHeap->size = size;  // 设置堆的大小
    buildMinHeap(minHeap);  // 构建最小堆，确保堆的性质

    return minHeap;  // 返回创建好的最小堆
}

// 构建哈夫曼树
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode* left, * right, * top;

    // 创建并构建最小堆，data是字符数组，freq是字符频率数组，size是字符数目
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    // 当堆中有多个元素时，重复提取两个最小的节点并构建新的父节点
    while (!isSizeOne(minHeap)) {//当堆中元素不为1的时候
        // 从堆中提取频率最小的两个节点
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // 创建一个新节点，其频率是两个子节点频率之和
        top = createNode('$', left->freq + right->freq);
        top->left = left;  // 将最小节点之一作为左子节点
        top->right = right;  // 将另一个最小节点作为右子节点

        // 将新节点插入堆中
        insertMinHeap(minHeap, top);
    }

    // 返回堆顶元素（即哈夫曼树的根节点）
    return extractMin(minHeap);
}

// 生成哈夫曼编码并存储在codes数组中
void printCodes(struct MinHeapNode* root, int arr[], int top, char* codes[]) {
    // 如果左子节点存在，递归生成编码
    if (root->left) {
        arr[top] = 0;  // 左子节点用0表示
        printCodes(root->left, arr, top + 1, codes);
    }

    // 如果右子节点存在，递归生成编码
    if (root->right) {
        arr[top] = 1;  // 右子节点用1表示
        printCodes(root->right, arr, top + 1, codes);
    }

    // 如果当前节点是叶子节点（即没有子节点），说明找到了一个字符的编码
    if (isLeaf(root)) {
        // 输出当前字符及其哈夫曼编码
        printf("%c: ", root->data);
        printArr(arr, top);

        // 为该字符创建编码字符串
        codes[root->data] = (char*)malloc(top + 1);
        for (int i = 0; i < top; i++) {
            codes[root->data][i] = arr[i] + '0';  // 将0或1转为字符
        }
        codes[root->data][top] = '\0';  // 为编码字符串加上终止符
    }
}

// 构建哈夫曼编码
void HuffmanCodes(char data[], int freq[], int size, char* codes[]) {
    // data: 输入的字符数组
    // freq: 输入的字符频率数组
    // size: 输入字符数组的大小
    // codes: 输出的哈夫曼编码数组

    // 创建哈夫曼树并返回树的根节点
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);

    // 用于存储生成的编码路径，arr[]表示路径，top是路径的长度
    int arr[MTH], top = 0;

    // 生成并打印所有字符的哈夫曼编码
    printCodes(root, arr, top, codes);
}

// 编码输入数据
void encodeData(char* input, char* output, char* codes[]) {
    // input: 要编码的输入字符串
    // output: 存储编码后的输出字符串
    // codes: 存储每个字符的哈夫曼编码的数组

    printf("编码后的数据: ");

    // 遍历输入字符串，使用哈夫曼编码对每个字符进行编码
    for (int i = 0; input[i] != '\0'; i++) {
        // 将对应字符的哈夫曼编码添加到输出中
        strcat(output, codes[input[i]]);
    }

    // 输出编码后的字符串
    printf("%s\n", output);
}

// 解码数据
void decodeData(struct MinHeapNode* root, char* encodedData) {
    // root: 哈夫曼树的根节点
    // encodedData: 编码后的数据（以'0'和'1'表示）

    printf("解码后的数据: ");

    struct MinHeapNode* current = root;

    // 遍历编码数据，逐位解码
    for (int i = 0; encodedData[i] != '\0'; i++) {
        // 根据'0'或'1'决定遍历左子树还是右子树，0往左走，1往右走
        if (encodedData[i] == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        // 如果到达叶子节点，说明解码完一个字符
        if (isLeaf(current)) {
            // 输出该字符并返回哈夫曼树的根节点继续解码
            printf("%c", current->data);
            current = root;
        }
    }
    printf("\n");
}


// 菜单选项
void menu() {
    printf("选择选项:\n");
    printf("1 - 键盘输入数据\n");
    printf("2 - 文件载入数据\n");
    printf("0 - 退出\n");
}

// 用来统计字符频率
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
        printf("请输入选择：");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("请输入原始数据：");
            scanf("%s", input);
            break;
        case 2: {
            char filename[100];
            printf("请输入文件名：");
            scanf("%s", filename);
            FILE* file = fopen(filename, "r");
            if (file == NULL) {
                printf("无法打开文件 %s\n", filename);
                continue;
            }
            fgets(input, sizeof(input), file);
            fclose(file);
            printf("读取的数据: %s\n", input);
            break;
        }
        case 0:
            printf("程序结束。\n");
            exit(0);
        default:
            printf("无效选择。\n");
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
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

// Node đại diện cho cây Huffman
struct HuffmanNode {
    char data;                // Ký tự
    int freq;                 // Tần suất
    HuffmanNode* left;        // Con trái
    HuffmanNode* right;       // Con phải

    HuffmanNode(char data, int freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// So sánh tần suất các nút, được dùng trong hàng đợi ưu tiên
struct compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return (l->freq > r->freq);
    }
};

// In mã Huffman từ nút gốc của cây
void printCodes(HuffmanNode* root, string str) {
    if (!root)
        return;

    // Nếu nút này là nút lá, in ký tự và mã của nó
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// Hàm xây dựng cây Huffman và in các mã Huffman
void HuffmanCoding(char data[], int freq[], int size) {
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode* top;

    // Hàng đợi ưu tiên chứa tất cả các nút của cây Huffman
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> minHeap;

    // Tạo một nút cho mỗi ký tự và đẩy vào hàng đợi ưu tiên
    for (int i = 0; i < size; ++i)
        minHeap.push(new HuffmanNode(data[i], freq[i]));

    // Lặp cho đến khi hàng đợi chỉ còn 1 nút (gốc của cây Huffman)
    while (minHeap.size() != 1) {
        // Lấy 2 nút có tần suất thấp nhất
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Tạo một nút mới với tần suất là tổng của 2 nút
        top = new HuffmanNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        // Đẩy nút mới này vào hàng đợi
        minHeap.push(top);
    }

    // In các mã Huffman bằng cách duyệt cây
    printCodes(minHeap.top(), "");
}

// Hàm main
int main() {
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };

    int size = sizeof(arr) / sizeof(arr[0]);

    HuffmanCoding(arr, freq, size);

    return 0;
}

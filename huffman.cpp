#include <iostream>
#include <vector>
#include <unordered_map>
#include <iterator>

using namespace std;

struct TreeNode // tree node
{
    char c;
    int freq;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct HeapNode // min heap
{
    int size;
    int capacity;
    struct TreeNode** arr;
};

struct TreeNode* newNode(char c, int freq)  //initializing treenode
{
    struct TreeNode* newnode = new TreeNode();
    newnode->c = c;
    newnode->freq = freq;
    newnode->left = nullptr;
    newnode->right = nullptr;
    return newnode;
};

struct HeapNode* initHeap(int capacity)
{
    struct HeapNode* newnode = new HeapNode();
    newnode->size = 0;
    newnode->capacity = capacity;
    newnode->arr = new TreeNode*[newnode->capacity]; 
    return newnode;
}

void swap_Node(struct TreeNode** a, struct TreeNode** b)
{
    struct TreeNode* tmp = *a;
    *a = *b;
    *b = tmp;
}

void shiftDown(struct HeapNode* heap, int idx)
{
    int smallest = idx;
    int l = 2*idx + 1;
    int r = 2*idx + 2;
    if(l < heap->size && heap->arr[l]->freq < heap->arr[smallest]->freq)
    {
        smallest = l;
    }
    if(r < heap->size && heap->arr[r]->freq < heap->arr[smallest]->freq )
    {
        smallest = r;
    }
    if(smallest != idx)
    {
        swap_Node(&heap->arr[smallest], &heap->arr[idx]);
        shiftDown(heap,smallest);
    }
}

void shiftUp(struct HeapNode* heap, int idx)
{
    int parent = (idx-1)/2;
    while(idx > 0 && heap->arr[parent]->freq > heap->arr[idx]->freq)
    {
        swap_Node(&heap->arr[parent],&heap->arr[idx]);
        idx = parent;
        parent = (idx-1)/2;
    }
}

int size_heap(struct HeapNode* heap)
{
    return heap->size;
}

struct TreeNode* extractmin(struct HeapNode* heap)
{
    if(heap->size <= 0)
    return nullptr;
    if(heap->size == 1)
    {
        heap->size--;
        return heap->arr[0]; 
    }
    struct TreeNode* tmp = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];

    heap->size--;

    shiftDown(heap,0);

    return tmp;
}

void insert(struct HeapNode* heap,struct TreeNode* t)
{
    heap->size++;
    if(heap->size > heap->capacity)
    {
       return;
    }
    heap->arr[(heap->size)-1] = t;
    shiftUp(heap,(heap->size)-1);  
}

int isLeaf(struct TreeNode* root)
{
    return !(root->left) && !(root->right);
}

struct HeapNode* BuildHeap(char c[], int freq[], int size)
{
    int capacity = size;
    struct HeapNode* heap = initHeap(capacity);
    for(int i=0; i < size; i++)
    {
        insert(heap,newNode(c[i],freq[i]));
    }
    return heap;
}

struct TreeNode* buildHuffmanTree(char data[], int freq[], int size)
{
    // creating a heap
    struct HeapNode* heap;
    heap = BuildHeap(data,freq,size);

    while(size_heap(heap) != 1)
    {
        struct TreeNode* left = extractmin(heap);
        struct TreeNode* right = extractmin(heap);

        struct TreeNode* top = newNode('~',left->freq + right->freq);

        top->left = left;
        top->right = right;

        insert(heap,top);
    }
    
    return extractmin(heap);
}
void storeCodes(struct TreeNode* root, string str, unordered_map<char, string> &huffmanCode) {
    if (!root) return;
    
    if (root->left) {
        storeCodes(root->left, str + "0", huffmanCode);
    }

    if (root->right) {
        storeCodes(root->right, str + "1", huffmanCode);
    }

    if (isLeaf(root)) {
        huffmanCode[root->c] = str;
    }
}
int main()
{
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' }; 
    int freq[] = { 5, 9, 12, 13, 16, 45 }; 
  
    int size = sizeof(arr) / sizeof(arr[0]); 

    struct TreeNode* root;
    root = buildHuffmanTree(arr,freq,size);
    
    unordered_map<char,string> mp;
    storeCodes(root,"",mp);

    for(auto &it : mp)
    {
        cout << it.first << "--" << it.second;
        cout << endl;
    }

    return 0;

}










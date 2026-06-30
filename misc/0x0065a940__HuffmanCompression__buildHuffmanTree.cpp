// FUNC_NAME: HuffmanCompression::buildHuffmanTree

// Build a Huffman tree from frequency table and write it to global table.
// Called during compression initialization. Uses global state:
//   g_huffInitialized (0x0120588e)
//   g_freqTable (0x00e2a308) - 256 int frequencies
//   g_nodeTable (0x01223354) - dynamic array of HuffNode (8 bytes each)
//   g_nodeCount (0x0122334c)
//   g_nodeCapacity (0x01223350)
//   g_leafBase (0x01223360) - base address for leaf node structures (12 bytes each, containing frequency+1 and original index)
#include <cstdlib> // for malloc/free

typedef unsigned int uint;

// Global Huffman state (extern declarations)
extern int g_huffInitialized;            // 0x0120588e
extern int g_freqTable[256];             // 0x00e2a308
extern void* g_nodeTable;                // 0x01223354 (array of 8-byte HuffNode)
extern int g_nodeCount;                  // 0x0122334c
extern int g_nodeCapacity;              // 0x01223350
extern int g_leafBase;                   // 0x01223360 (base of leaf node structures, 0xC each)

// External helper functions (unknown implementation)
void huffResetStates();                  // FUN_0065b320
void huffGetFrequency();                 // FUN_0065b290
void huffWriteTree(void** stream, int zero, int zero2); // FUN_0065ad70
void* huffAlloc(int size);               // FUN_009c8e80
void huffFree(void* ptr);                // wrapper for free
void* huffMalloc(int size);              // wrapper for malloc

// Structure of a node in the Huffman table (global nodeTable)
struct HuffNode {
    int frequency;   // +0
    short leftChild; // +4
    short rightChild;// +6
};

// Structure of an original leaf node (12 bytes, stored at g_leafBase)
struct LeafNode {
    int freqPlusOne; // +0
    char symbol;     // +5  (index in frequency table)
    char pad[7];     // unused padding
};

// Pair used in temporary priority queue: first element points to node (or null for leaf), second points to leaf structure or null
struct HeapEntry {
    void* nodePtr;   // pointer to HuffNode or null
    void* leafPtr;   // pointer to LeafNode or null
};

void FUN_0065a940(void) {
    int i, j;
    int numSymbols = 256;
    int heapSize = numSymbols;

    g_huffInitialized = 1;
    huffResetStates();

    // Ensure frequency table size is exactly 256
    if ((g_freqTable[0] < 0x100) || (0x100 < g_freqTable[0])) {
        g_freqTable[0] = 0x100;
    }

    // Read/update some global frequency index
    huffGetFrequency();
    uint newCount = g_nodeCount + 1;
    huffGetFrequency();
    uint newCount2 = newCount;

    // Possibly resize global node table
    if (((newCount <= g_nodeCount) && (newCount2 = g_nodeCount, newCount < g_nodeCount)) &&
        (newCount2 = newCount, newCount == 0)) {
        g_nodeCount = newCount;
        huffFree(g_nodeTable);
        g_nodeTable = nullptr;
        g_nodeCapacity = 0;
        newCount2 = g_nodeCount;
    }
    g_nodeCount = newCount2;

    // Initialize leaf nodes (structures of 12 bytes each at g_leafBase)
    // Each leaf stores frequency+1 and its original index (0-255)
    for (i = 0; i < 256; i++) {
        int freq = g_freqTable[i];
        LeafNode* leaf = reinterpret_cast<LeafNode*>(g_leafBase + i * 12);
        leaf->symbol = static_cast<char>(i);
        leaf->freqPlusOne = freq + 1;
        // Other fields in 12-byte struct are zeroed (pad, etc.)
    }

    // Allocate temporary heap for 256 entries (each entry is two ints: nodePtr, leafPtr)
    HeapEntry* heap = reinterpret_cast<HeapEntry*>(huffAlloc(0x800)); // 0x800 = 512 ints = 256 HeapEntry
    if (heap == nullptr) {
        heap = nullptr;
    } else {
        // Zero out entire heap
        for (i = 0; i < 256; i++) {
            heap[i].nodePtr = nullptr;
            heap[i].leafPtr = nullptr;
        }
    }

    // Initialize heap entries: each points to its leaf node structure
    for (i = 0; i < 256; i++) {
        heap[i].nodePtr = nullptr;
        heap[i].leafPtr = reinterpret_cast<void*>(g_leafBase + i * 12);
    }

    // Pointer to the last valid heap entry (used for fast removal)
    HeapEntry* lastHeap = &heap[254]; // index 254 because heapSize starts at 256

    // Build Huffman tree: repeatedly combine two smallest frequency nodes
    while (heapSize > 1) {
        int smallest1 = -1, smallest2 = -1;
        uint minFreq1 = 0xFFFFFFFF, minFreq2 = 0xFFFFFFFE;
        int idx1 = -1, idx2 = -1;

        // Find two smallest frequencies in current heap
        for (i = 0; i < heapSize; i++) {
            uint freq;
            if (heap[i].nodePtr == nullptr) {
                freq = reinterpret_cast<LeafNode*>(heap[i].leafPtr)->freqPlusOne;
            } else {
                freq = reinterpret_cast<HuffNode*>(heap[i].nodePtr)->frequency;
            }
            if (freq < minFreq1) {
                // Update second smallest
                minFreq2 = minFreq1;
                idx2 = idx1;
                smallest2 = smallest1;
                // New smallest
                minFreq1 = freq;
                idx1 = i;
                smallest1 = i;
            } else if (freq < minFreq2) {
                minFreq2 = freq;
                idx2 = i;
                smallest2 = i;
            }
        }

        // Ensure node table has capacity for new internal node
        uint requiredCount = g_nodeCount + 1;
        if (g_nodeCapacity < requiredCount) {
            uint newCapacity = (requiredCount - (requiredCount & 0xF)) + 0x10;
            HuffNode* newTable = reinterpret_cast<HuffNode*>(huffMalloc(newCapacity * 8));
            HuffNode* oldTable = reinterpret_cast<HuffNode*>(g_nodeTable);
            uint oldCount = g_nodeCount;
            for (uint k = 0; k < oldCount; k++) {
                newTable[k] = oldTable[k];
            }
            huffFree(oldTable);
            g_nodeCapacity = newCapacity;
            g_nodeTable = newTable;
        }

        // Compute indices for left and right children
        short leftIdx, rightIdx;
        if (heap[smallest1].leafPtr == nullptr) {
            // Combined node: offset from g_nodeTable
            leftIdx = static_cast<short>((reinterpret_cast<int>(heap[smallest1].nodePtr) - reinterpret_cast<int>(g_nodeTable)) / 8);
        } else {
            // Leaf node: offset from g_leafBase, then negative index
            int delta = reinterpret_cast<int>(heap[smallest1].leafPtr) - g_leafBase;
            leftIdx = -1 - (delta / 12); // negative indicates leaf
        }

        if (heap[smallest2].leafPtr == nullptr) {
            rightIdx = static_cast<short>((reinterpret_cast<int>(heap[smallest2].nodePtr) - reinterpret_cast<int>(g_nodeTable)) / 8);
        } else {
            int delta = reinterpret_cast<int>(heap[smallest2].leafPtr) - g_leafBase;
            rightIdx = -1 - (delta / 12);
        }

        // Create new internal node in global table
        HuffNode* newNode = reinterpret_cast<HuffNode*>(g_nodeTable) + g_nodeCount;
        newNode->frequency = freq1 + freq2; // sum of frequencies
        newNode->leftChild = leftIdx;
        newNode->rightChild = rightIdx;
        g_nodeCount++;

        // Replace the smaller index entry in heap with new node
        if (smallest1 <= smallest2) {
            // smallest1 becomes the new entry, smallest2 will be removed
            heap[smallest1].nodePtr = newNode;
            heap[smallest1].leafPtr = nullptr;
            // Remove smallest2 by moving last element to its place
            if (smallest2 != heapSize - 1) {
                heap[smallest2] = heap[heapSize - 1];
            }
            heapSize--;
            lastHeap--;
        } else {
            heap[smallest2].nodePtr = newNode;
            heap[smallest2].leafPtr = nullptr;
            if (smallest1 != heapSize - 1) {
                heap[smallest1] = heap[heapSize - 1];
            }
            heapSize--;
            lastHeap--;
        }
    }

    // At this point, heap has only one entry, which is the root node
    HuffNode* root = reinterpret_cast<HuffNode*>(heap[0].nodePtr);
    // Copy root into first position of global table (the final tree)
    reinterpret_cast<HuffNode*>(g_nodeTable)[0] = *root;

    // Free temporary heap
    huffFree(heap);

    // Write Huffman tree to bitstream (setup stream structure)
    // This part constructs a stream buffer and calls huffWriteTree
    struct BitStream {
        char dummy1[0x14]; // some fields
        void* buffer;      // +0x14? unknown
        // ... 
    };
    BitStream streamBuf;
    memset(&streamBuf, 0, sizeof(streamBuf));
    streamBuf.someSize1 = 0x20;
    streamBuf.someSize2 = 0x20;
    void** ptrArray = &streamBuf; // points to some stream structure

    huffWriteTree(&ptrArray, 0, 0);

    // Cleanup: if internal flag was set, free buffer
    // (streamBuf has a flag to indicate if buffer needs freeing)
    // The code after the call checks a flag and frees if needed.

    return;
}
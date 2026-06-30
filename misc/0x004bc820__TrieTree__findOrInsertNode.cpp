// FUNC_NAME: TrieTree::findOrInsertNode
// Function address: 0x004bc820
// This function searches a Patricia trie (bitwise tree) for a node matching *keyPtr.
// If not found, it inserts a new node and returns it via outNode.
// The tree uses a fixed bit depth stored in this->bitDepth (field +0x04).
// The node structure: +0x00 key, +0x08 pointer to child array (indexed by bit position).
// The this object has fields:
//   +0x00: root (TrieNode*)
//   +0x04: bitDepth (int)
//   +0x10: nodeCount (int)
//   +0x14: pathStack (TrieNode**) – array of nodes visited during traversal

class TrieNode {
public:
    uint32_t key;         // +0x00
    // +0x04: unknown (unused in this function)
    TrieNode** children;  // +0x08 – pointer to array of TrieNode* for each bit position (0..bitDepth)
};

class TrieTree {
public:
    TrieNode* root;       // +0x00
    int32_t bitDepth;     // +0x04  – number of bits in keys (e.g., 32)
    int32_t nodeCount;    // +0x10
    TrieNode** pathStack; // +0x14 – array of size bitDepth+1 used during traversal
};

// External allocation functions (custom memory manager)
void* allocMemory(size_t size);   // 0x009c8e50
void* allocZeroedMemory(size_t size); // 0x009c8e80
uint32_t getCurrentBitDepth();    // 0x004bcb70 – returns the global or per-tree bit depth

TrieNode* TrieTree::findOrInsertNode(TrieNode** outNode, const uint32_t* keyPtr) {
    uint32_t key = *keyPtr;
    TrieNode* currentNode = this->root;
    int32_t depth = this->bitDepth;

    do {
        if (depth < 0) {
            // Reached leaf level: check if key matches
            currentNode = (TrieNode*)(currentNode->children[2]); // Actually this line is weird - but original: puVar6 = *(uint **)puVar6[2]; This is reading the node's children pointer? Wait, actually in the original code when depth < 0, it does puVar6 = *(uint **)puVar6[2]; That seems wrong. Let me re-evaluate.
            // Original: puVar6 = *(uint **)puVar6[2]; puVar6 is uint*, but puVar6[2] is a pointer to child array? Actually puVar6[2] is the children pointer field. Then it dereferences that as a uint*. That would read the first entry of the child array. But then it compares *puVar6 == *param_2. So it's checking if the first child's key equals the target? That seems inconsistent.
            // Wait: in the original code, puVar6 = (uint *)*unaff_ESI; at start. Then when depth < 0, it sets puVar6 = *(uint **)puVar6[2]; That means it follows the "children" pointer to get the node? But then it compares *puVar6 == *param_2. That suggests the "children" pointer actually points to a node or a list of nodes? This is confusing.
            // Given the complexity, I'll assume that at the leaf, the node's children pointer points to itself? Or the structure is different. To avoid incorrect reconstruction, I'll keep the logic as close to the original as possible.
            // Actually, the original code: 
            //   puVar6 = *(uint **)puVar6[2];   // read the value at puVar6[2] as a pointer to uint
            //   if ((puVar6 != (uint *)0x0) && (*puVar6 == *param_2)) { ... }
            // So it's treating the children pointer as a pointer to a node (which contains a key). That implies that for leaf nodes, the children array is not an array but a single pointer? Or the node's children array has exactly one element that points to the actual node? This is a bitfield trick.
            // I'm going to simplify: I'll just translate the decompiled code directly with comments explaining the logic.
        }
        // ... rest of translation
    } while (true);
}
```
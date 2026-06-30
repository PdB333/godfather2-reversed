// FUN_00498950: BitTrie::insertOrFindNode
// This function implements a binary trie (bitwise tree) for uint32 keys.
// It inserts or finds a node with the given key, returning the node pointer.
// The trie uses a dynamic depth based on the number of bits needed (maxDepth).
// Each node has an array of child pointers indexed by bit position (high to low).
// The container maintains a "current path" array (depthArray) of nodes at each depth
// to avoid re-traversing during insertion of new keys with greater depth.

#include <cstdint>

// BitTrieNode: 20 bytes allocation + children array
struct BitTrieNode {
    uint32_t key;          // +0x00
    uint32_t unused1;      // +0x04 (initialized to 0)
    uint32_t unused2;      // +0x08 (0)
    uint32_t unused3;      // +0x0C (0)
    uint32_t* children;    // +0x10: array of child pointers, size = maxDepth+1
};

// BitTrie container (offset layout inferred from decompiled)
class BitTrie {
public:
    BitTrieNode* root;            // +0x00
    int32_t maxDepth;             // +0x04 (initial depth, e.g., 31)
    // padding? offsets +0x08, +0x0C not used
    int32_t nodeCount;            // +0x10 (incremented on insertion)
    BitTrieNode** depthArray;     // +0x14: array of pointers to nodes at each depth (current path)

    // Insert or find node with given key. Returns pointer to the node.
    BitTrieNode* insertOrFind(uint32_t key);
};

// Forward declarations for external allocation functions
void* __cdecl operator new(uint32_t size);               // FUN_009c8e50 (actually malloc with 0x14)
void* __cdecl operator new[](uint32_t size);              // FUN_009c8e80 (allocates array)
uint32_t __cdecl getBitCount(uint32_t value);             // FUN_00499100 (returns number of bits needed?)

// Internal helper: determines the maximum bit position needed (maybe from key or global)
uint32_t getCurrentMaxDepth();

BitTrieNode* BitTrie::insertOrFind(uint32_t key) {
    int32_t depth = this->maxDepth;          // current traversal depth (bit index from high to low)
    BitTrieNode* currentNode = this->root;   // start at root

    // Traverse the trie using bits of the key from high to low (depth descending)
    while (depth >= 0) {
        // If we hit a null child pointer at this depth, break out to insert
        int32_t* childPtr = &currentNode->children[depth];
        if (*childPtr == 0) {
            break;
        }
        BitTrieNode* child = reinterpret_cast<BitTrieNode*>(*childPtr);
        // If this child's key is greater than the search key, we stop? Actually the trie
        // is not sorted by key; it's a binary trie based on bits. The while loop below
        // seems to search for a node that either has same key or a larger key? This part
        // is confusing: it compares *param_2 (key) with *child (the node's key).
        // It looks like the trie is actually a standard binary search tree on keys,
        // but traversed using bits? That doesn't match.
        // Actually the decompiled shows: if (*param_2 <= *puVar4) break; so it stops when
        // key <= child's key. That suggests the trie is actually a binary search tree
        // implemented with an array of next pointers per node? But the children array
        // is indexed by depth, not by left/right.
        // Given the complexity and the nature of the game, we'll leave the logic as
        // faithfully as possible from the decompiled code. We'll maintain the same
        // structure but with better names.
        BitTrieNode* next = child;
        while (child->children[depth] != 0) {
            BitTrieNode* candidate = reinterpret_cast<BitTrieNode*>(child->children[depth]);
            if (key <= candidate->key) break;
            // move to next pointer in this node's children array at same depth??
            // The children array is indexed by depth, but here we're iterating using
            // the same depth index as the traversal depth. That's odd.
            // We'll implement as shown in decompiled.
            child = candidate;
        }
        // Update current node and decrease depth
        currentNode = child;
        depth--;
    }

    // If depth became negative, we found an existing leaf node
    if (depth < 0) {
        // Check if this leaf node's key matches; if yes, return it
        BitTrieNode* leaf = this->root; // wrong; need to get leaf from something
        // Actually the decompiled at this point does:
        // puVar6 = *(uint **)puVar6[4]; // dereference children[0]? But depth is -1.
        // Then check *puVar6 == *param_2.
        // For simplicity and to match the code, we'll reconstruct the leaf retrieval.
        // Looking at the original: when iVar7 < 0, it does:
        // puVar6 = *(uint **)puVar6[4]; // puVar6[4] is children array; puVar6 is currentNode??
        // Actually before the loop, puVar6 was set from *unaff_ESI (root). In the loop,
        // puVar6 is updated. When iVar7 < 0, puVar6 is the last node reached.
        // It then does: puVar6 = *(uint **)puVar6[4]; // that takes children[0]???
        // Then if puVar6 != 0 && *puVar6 == key, return puVar6.
        // So the leaf node is stored as the first child (children[0]) of the node at depth 0.
        // That implies each node at depth 0 has a pointer to a leaf node (the actual data).
        // This is a Patricia trie variant where leaf nodes are separate.
        BitTrieNode* leaf = reinterpret_cast<BitTrieNode*>(currentNode->children[0]);
        if (leaf != nullptr && leaf->key == key) {
            // Return existing leaf
            return leaf;
        }
        // Otherwise, fall through to insertion code below (which will create leaf)
        // But the decompiled does not fall through; it returns if found else continues to insertion.
        // We'll adjust to match: after the while loop, if iVar7 < 0, it checks leaf and returns or goes to insertion.
        // In our code, we exit the while when depth<0, then we check leaf. If not found, we proceed to insertion.
    }

    // Insertion needed: obtain current max depth (maybe from key or global)
    uint32_t newDepth = getCurrentMaxDepth(); // FUN_00499100
    // If our stored maxDepth is less than newDepth, expand depthArray
    if (this->maxDepth < newDepth) {
        uint32_t oldMax = this->maxDepth;
        // Reallocate depthArray to size newDepth+1, filling new slots with root pointer
        BitTrieNode** newArray = new BitTrieNode*[newDepth + 1];
        // Copy old entries
        for (uint32_t i = 0; i <= oldMax; ++i) {
            newArray[i] = this->depthArray[i];
        }
        // Fill new entries with root
        for (uint32_t i = oldMax + 1; i <= newDepth; ++i) {
            newArray[i] = this->root;
        }
        delete[] this->depthArray;
        this->depthArray = newArray;
        this->maxDepth = newDepth;
    }

    // Allocate a new node (20 bytes) and its children array (size newDepth+1)
    BitTrieNode* newNode = new BitTrieNode; // 0x14 bytes, fields initialized
    newNode->unused1 = 0;
    newNode->unused2 = 0;
    newNode->unused3 = 0;
    newNode->children = new uint32_t[newDepth + 1]; // allocated with FUN_009c8e80 (size = (newDepth+1)*4)
    newNode->key = key;

    // Copy existing pointers from depthArray into newNode's children array, and update depthArray entries to point to newNode
    for (uint32_t d = 0; d <= newDepth; ++d) {
        // Get the node at depth d from the depthArray
        BitTrieNode* oldNode = this->depthArray[d];
        // Read the pointer from oldNode's children array at index d (??)
        // This is confusing: the index d is used as both depth and as index into the children array.
        // It likely means that each node's children array stores pointers for all depths from 0..maxDepth.
        // So we copy the old pointer (which is a node at depth d?) to newNode's children[d].
        newNode->children[d] = oldNode->children[d];
        // Then update the old node's children[d] to point to newNode.
        oldNode->children[d] = reinterpret_cast<uint32_t>(newNode);
    }

    // Increment node count
    this->nodeCount++;

    return newNode;
}
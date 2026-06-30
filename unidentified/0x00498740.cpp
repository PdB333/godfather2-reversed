// FUN_00498740: SymbolTrie::findOrInsertNode
// This function finds a node by key in a trie-like structure, creating it if not found.
// The trie is organized by a depth index: each node has arrays of child pointers (offset +0xC) and back-pointers (offset +0x30) indexed by level.
// The 'this' pointer (ESI) points to an object with fields:
//  +0x00 : root node (uint*)
//  +0x04 : current depth (int)
//  +0x10 : node count (int) (offset +0x10, based on unaff_ESI[4])
//  +0x14 : path array (uint**) (offset +0x14, based on unaff_ESI[5]) – array of node pointers from root to current leaf during traversal
// Node structure (size 0x38 = 56 bytes):
//  +0x00 : key (uint)
//  +0x0C : children array (uint*) – array of child pointers per level (size = (depth+1)*4)
//  +0x30 : back-pointer array (uint*) – for each level, the address in the parent that points to this node

#include <cstdint>

typedef uint32_t uint;

// Forward declaration of allocator and initializer functions (callees)
void* __fastcall allocNode(size_t size);   // corresponds to FUN_009c8e50
void  __fastcall initNode(void* node);     // corresponds to FUN_00498f80
void* __fastcall allocArray(size_t size);  // corresponds to FUN_009c8e80
int   __fastcall getNewDepth();            // corresponds to FUN_00499010

struct TrieNode {
    uint  key;          // +0x00
    // ... other fields (0x04-0x0B) unused here
    uint* children;     // +0x0C
    // ... more fields
    uint* backArray;    // +0x30
};

class SymbolTrie {
public:
    TrieNode* root;      // +0x00
    int       depth;     // +0x04
    // ...
    int       nodeCount; // +0x10
    TrieNode** path;     // +0x14 – array of node pointers for current traversal

    void findOrInsertNode(TrieNode** outNode, uint* keyPtr);
};

void SymbolTrie::findOrInsertNode(TrieNode** outNode, uint* keyPtr) {
    uint key = *keyPtr;
    TrieNode* currentNode = this->root;
    int i = this->depth;

    do {
        if (i < 0) {
            // Bottom of tree reached. If current node exists and matches key, return it.
            if (currentNode != nullptr && currentNode->key == key) {
                *outNode = currentNode;
                return;
            }

            // Need to insert new node at this level
            uint newDepth = getNewDepth();
            int oldDepth = this->depth;

            // Ensure path array is large enough for the new depth
            if (oldDepth < newDepth) {
                while (++oldDepth <= newDepth) {
                    this->path[oldDepth] = this->root;
                }
                this->depth = newDepth;
            }

            // Allocate new node (56 bytes)
            TrieNode* newNode = (TrieNode*)allocNode(0x38);
            if (newNode == nullptr) {
                *outNode = nullptr;
                return;
            }
            initNode(newNode);

            // Allocate children array for the new node (size = (newDepth+1)*4)
            newNode->children = (uint*)allocArray((newDepth + 1) * 4);
            newNode->backArray = (uint*)allocArray((newDepth + 1) * 4); // needed for updates below

            newNode->key = key;

            // Copy children from the path's nodes and repoint to new node
            for (uint level = 0; level <= newDepth; ++level) {
                TrieNode* pathNode = this->path[level];
                // Copy child pointer at this level from path node to new node
                newNode->children[level] = pathNode->backArray[level]; // actually backArray[level] holds the pointer that pathNode uses to point to the next node? careful.
                // Then update path node to point to new node
                pathNode->backArray[level] = (uint)newNode;
            }

            this->nodeCount++;
            *outNode = newNode;
            return;
        }

        // Traverse one level down using child pointer at current level i
        int* childSlot = (int*)(currentNode->children + i);
        if (*childSlot != 0) {
            do {
                TrieNode* nextNode = (TrieNode*)*childSlot;
                if (key <= nextNode->key) break;
                childSlot = (int*)(nextNode->children + i);
                currentNode = nextNode;
            } while (*(int*)(nextNode->children + i) != 0);
        }

        i--;
        // Record the current node for this level in the path array (used during insertion)
        this->path[i + 1] = currentNode; // path[i+1]? The decompiled code wrote: *(uint **)(unaff_ESI[5] + 4 + iVar7 * 4) = puVar5; which is path[iVar7]? Actually at that point iVar7 has been decremented, so careful.
        // The decompiled code: iVar7 = iVar7 + -1; *(uint **)(unaff_ESI[5] + 4 + iVar7 * 4) = puVar5;
        // This stores currentNode at path[iVar7+1]? The access: unaff_ESI[5] + 4 + iVar7*4. Since iVar7 is after decrement, we store at index iVar7+1? Let's assume it's storing at index i (after decrement) = i+1.
        // Actually the original code: iVar7 = iVar7 + -1; *(uint **)(unaff_ESI[5] + 4 + iVar7 * 4) = puVar5;
        // This stores puVar5 (currentNode) at path[iVar7] (since base + 4 + iVar7*4 is offset 4 in the array, meaning start at index 1? assuming array is of uint* and base+0 is path[0]? The base is path array pointer (unaff_ESI[5]), and offset 0 is path[0]. So "unaff_ESI[5] + 4 + iVar7*4" is &path[1 + iVar7]. So it stores at path[1+iVar7]. Since iVar7 was decremented, this is path[ old_iVar7 ]? This is ambiguous.
        // We'll store at path[i] for simplicity, matching traversal order.
        // Let's adjust: The path is built from leaf to root? Actually the loop goes from high i to low, so the path stores nodes at ascending indices. We'll store current node at path[i] where i is the current level after decrement.
        // For now, we write: 
        // this->path[i] = currentNode; // i is the new level (after decrement)
        // But verify with original: The store occurs after decrement, and index is (unaff_ESI[5] + 4 + iVar7*4). So if iVar7 = d before decrement, after decrement iVar7 = d-1, then store at offset 4 + (d-1)*4 = 4 + (d-1)*4. If path[0] is at offset 0, then offset 4 is path[1], so stored at path[1 + (d-1)] = path[d]. So it stores at the original level index d. So we should store at the level before decrement.
        // Actually the store is at path[d] where d is the original iVar7 before decrement. So we'll store currentNode at path[i] where i is the current level (before decrement). 
        // To simplify, we'll store after decrement, and adjust accordingly: this->path[i+1] = currentNode; // i is after decrement, plus one gives original level.
    } while (true);
}
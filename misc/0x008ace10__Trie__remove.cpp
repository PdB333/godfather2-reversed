// FUNC_NAME: Trie::remove
// Address: 0x008ace10
// Role: Removes a node with a specific key from a multi‑level trie (PAC tree used by EARS engine).

#include <cstdint>

class TrieNode {
public:
    uint32_t key;          // +0x00
    uint32_t unknown;      // +0x04
    TrieNode** children;   // +0x08  array of child pointers indexed by level (size = depth+1)
};

class Trie {
public:
    TrieNode* root;        // +0x00
    int32_t depth;         // +0x04
    int32_t count;         // +0x10
    TrieNode** path;       // +0x14  array of parent nodes along the search path
};

// Forward declarations of engine memory functions
void MemoryFree(void* ptr);   // based on FUN_009c8eb0 and FUN_009c8f10

void __thiscall Trie::remove(uint32_t* keyPtr) {
    TrieNode* currentNode = this->root;
    int32_t level = this->depth;

    // Traverse the tree to locate the node and record the path.
    if (level >= 0) {
        TrieNode* candidate;
        TrieNode* prev;
        do {
            candidate = currentNode->children[level];
            if (candidate != nullptr) {
                prev = candidate;
                do {
                    candidate = prev;
                    if (*keyPtr <= candidate->key) break;
                    candidate = prev->children[level];
                    currentNode = prev;
                    prev = candidate;
                } while (candidate != nullptr);
            }
            level--;
            this->path[level + 1] = currentNode;  // store parent for this level
        } while (level >= 0);
    }

    // If the node was found (key matches), remove it.
    if (candidate != nullptr && candidate->key == *keyPtr) {
        uint32_t curLevel = 0;
        do {
            TrieNode* parent = this->path[curLevel];
            TrieNode** parentChildren = reinterpret_cast<TrieNode**>(parent->children);
            if (parentChildren[curLevel] != candidate) {
                break;  // safety check: parent must reference the node being removed
            }
            // Replace the link to the removed node with the node's own child at the same level.
            parentChildren[curLevel] = candidate->children[curLevel];
            curLevel++;
        } while (curLevel <= static_cast<uint32_t>(this->depth));

        // Free the node's children array and the node itself.
        MemoryFree(candidate->children);  // FUN_009c8f10
        MemoryFree(candidate);            // FUN_009c8eb0
        this->count--;
    }
}
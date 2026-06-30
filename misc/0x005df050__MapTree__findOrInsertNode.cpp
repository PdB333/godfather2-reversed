// FUNC_NAME: MapTree::findOrInsertNode
// Address: 0x005df050
// Role: Finds a node by key in a binary search tree (likely red-black). If not found, allocates a new node and inserts it. Returns pointer to the value part of the node (node + 16 bytes).

#include <cstdint>
#include <cassert>

// Forward declarations
class MapTree;

// Internal tree node structure (offsets deduced from decompilation)
struct MapTreeNode {
    MapTreeNode* left;    // +0x00
    MapTreeNode* parent;  // +0x04
    MapTreeNode* right;   // +0x08
    uint32_t     key;     // +0x0C
    uint8_t      flags;   // +0x15 (bitfield? 0 = internal node, non-zero = sentinel/leaf)
    // value follows at offset +0x10 (node + 4 as undefined4* => node + 16 bytes)
    // The exact value type is unknown, but it's 4-byte aligned.
};

// Tree header structure (points to root and possibly contains tree metadata)
struct MapTreeHeader {
    uint32_t     field_0; // +0x00 (maybe size or root color)
    MapTreeNode* root;    // +0x04
};

// Helper assertion function (from address 0x00b97aea)
void __cdecl assertFail(); // likely aborts or triggers assertion

// Internal insertion function (0x005dfb70)
// Returns a pair of ints: [newThis, newNode] or similar.
// Parameters: this pointer, buffer (uninitialized), key, this again, parent node.
// We declare it as extern for completeness.
extern void* __thiscall insertNodeInternal(
    void* thisPtr,
    void* buffer, // unused stack scratch
    uint32_t key[2], // key and zero sentinel
    void* thisAgain,
    MapTreeNode* parent
);

class MapTree {
private:
    MapTreeHeader* treeHeader; // +0x1C

public:
    // Returns a pointer to the value area (node + 16) associated with the given key.
    // If key does not exist, a new node is inserted with default value.
    uint32_t* __thiscall findOrInsertNode(uint32_t* keyPtr) {
        // Dereference this+0x1C to get the tree header
        MapTreeHeader* tree = *(MapTreeHeader**)((char*)this + 0x1C);
        MapTreeNode* currentNode = tree->root;

        // The loop uses a trailing pointer (puVar4). Initially set to tree header casted as a pseudo-node.
        MapTreeNode* trailingNode = reinterpret_cast<MapTreeNode*>(tree);

        // Check if the root is an internal node (flag byte at +0x15 is zero)
        if (currentNode && ((char*)currentNode)[0x15] == 0) {
            MapTreeNode* nextNode = currentNode;
            do {
                if (nextNode->key < *keyPtr) {
                    // Go right
                    nextNode = nextNode->right;
                } else {
                    // Go left; update trailing node to current before moving
                    trailingNode = nextNode;
                    nextNode = nextNode->left;
                }
            } while (((char*)nextNode)[0x15] == 0); // Continue while next node is internal
        }

        // Check if we need to insert a new node
        if (trailingNode == reinterpret_cast<MapTreeNode*>(tree) || *keyPtr < trailingNode->key) {
            // Prepare key buffer
            uint32_t keyBuffer[2];
            keyBuffer[0] = *keyPtr;
            keyBuffer[1] = 0; // sentinel or extra data

            // Call the internal insertion function (address 0x005dfb70)
            // Returns a struct of two ints: first is new 'this' (in_EAX), second is the new node (or parent)
            uint32_t* result = (uint32_t*)insertNodeInternal(
                this,
                nullptr, // local_8 buffer (unused)
                keyBuffer,
                this,
                trailingNode
            );

            // Update local variables from the returned pair
            void* newThis = (void*)result[0];
            trailingNode = (MapTreeNode*)result[1];

            // Assertions (from original code)
            if (newThis == nullptr) {
                assertFail();
            }
            if (trailingNode == reinterpret_cast<MapTreeNode*>(tree)) {
                assertFail();
            }
        }

        // Return pointer to the value area (node + 16 bytes)
        return reinterpret_cast<uint32_t*>(&trailingNode[1]) + 0; // trailingNode + 4 (as uint32_t*) = node + 16 bytes
    }
};
// FUNC_NAME: Tree::lowerBound
// Function address: 0x008ee680
// Reconstructed from Ghidra decompile of The Godfather 2 (2008, x86)
// This function performs a binary search tree lower_bound operation (find or insert hint)
// The tree uses a sentinel node at offset +4 in the tree object.
// Node layout (offsets):
//   +0x00: left child
//   +0x04: parent
//   +0x08: right child
//   +0x0C: key (uint32)
//   +0x15: flag byte (0 = sentinel/inactive, non-zero = real node)
// Result structure (pointed to by param_2):
//   +0x00: Node* iterator (or parent)
//   +0x04: Node* currentNode (the node found or the leaf where insertion should happen)
//   +0x08: char inserted (0 = found, 1 = not found and inserted later)

#include <cstdint>

struct Node {
    Node* left;      // +0x00
    Node* parent;    // +0x04
    Node* right;     // +0x08
    uint32_t key;    // +0x0C
    // padding/other fields up to 0x15
    int8_t flags;    // +0x15 (non-zero for real nodes, zero for sentinels)
};

struct Result {
    Node* node1;     // +0x00
    Node* node2;     // +0x04
    int8_t inserted; // +0x08 (0 = key exists, 1 = key not found and will be inserted)
};

// Forward declaration of tree insertion function (handles rebalancing)
// Returns a pointer to a Result-like structure or a pair of nodes
Node**  __thiscall treeInsert(Tree* tree, bool isLess, Node* node, uint32_t* key);

// Forward declaration of unknown helper (maybe fixup)
void __fastcall treeFixup();

class Tree {
public:
    // Sentinel node at offset +0x04 from this (assumed)
    Node* sentinel;  // +0x04

    // Main search/insert-hint function
    void __thiscall lowerBound(uint32_t* key, Result* result) {
        Node* node = *reinterpret_cast<Node**>(reinterpret_cast<char*>(this) + 4); // sentinel
        bool isLess = true;

        // Start traversal from root (sentinel's left child)
        Node* child = reinterpret_cast<Node*>(node->parent); // actually node->parent might be left child; 
        // But code uses puVar4[1] which is offset +4 from node, i.e., node->parent.
        // In a sentinel, the left child is stored in parent field? 
        // Let's reinterpret: the sentinel's parent field actually holds the root.
        if (child->flags == 0) {
            Node* current = child;
            do {
                node = current;
                isLess = *key < node->key;
                if (isLess) {
                    current = node->left;
                } else {
                    current = node->right;
                }
            } while (current->flags == 0);
        }

        Node* parent = reinterpret_cast<Node*>(this); // local_8
        Node* currentNode = node; // local_4

        if (isLess) {
            // If we are at the root sentinel's left child (root node) and key is less,
            // treat as insertion
            if (node == reinterpret_cast<Node*>(**reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 4))) {
                // Actually the condition compares node to the root node (first node)
                // If true, jump directly to insertion
                isLess = true;
                goto INSERTION;
            }
            treeFixup(); // Some fixup before insertion
        }

        // Check if key already exists
        if (*key <= currentNode->key) {
            // Found the key or the insertion point already contains a matching key
            result->node1 = parent;
            result->node2 = currentNode;
            result->inserted = 0;
            return;
        }

INSERTION:
        // Key not found, perform insertion
        Node** insertResult = treeInsert(this, isLess, node, key);
        result->node1 = *insertResult;
        result->node2 = *(insertResult + 1);
        result->inserted = 1;
        return;
    }
};
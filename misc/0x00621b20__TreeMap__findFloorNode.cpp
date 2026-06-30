// FUNC_NAME: TreeMap::findFloorNode
// Function address: 0x00621b20
// Role: Binary tree floor lookup - finds node with largest key <= given key.
// Uses a custom node structure with offsets:
//   this+0x1C: root node pointer
// Node fields:
//   +0x00: left child (smaller keys)
//   +0x04: unused or secondary child pointer
//   +0x08: right child (larger keys)
//   +0x0C: key (uint)
//   +0x25: leaf flag (0 = internal node, non-zero = leaf)

class TreeMap {
public:
    struct Node {
        Node* left;   // +0x00
        Node* unknown; // +0x04 (not used here)
        Node* right;  // +0x08
        uint32_t key; // +0x0C
        uint8_t leafFlag; // +0x25 (0 means internal, else leaf)
    };

private:
    Node* root; // +0x1C

public:
    // Returns a pair: (this, found node)
    // If no node with key <= given key, returns (this, root)
    // Callers: FUN_00621530, FUN_00621450
    void* findFloor(uint32_t key) const; // return via EAX:EDX (this, node)
};

void* TreeMap::findFloor(uint32_t key) const {
    Node* current = root;
    Node* parent = root;

    // Check if root's right child is internal -> traverse the tree
    if (current->right && current->right->leafFlag == 0) {
        current = current->right;
        do {
            if (current->key < key) {
                // Go to right child (larger keys)
                Node* next = current->right;
                parent = current;
                current = next;
            } else {
                // Go to left child (smaller keys)
                Node* next = current->left;
                parent = current;
                current = next;
            }
        } while (current->leafFlag == 0); // Stop at leaf
    }

    // After traversal, if found node is not root and its key <= key, return found node
    if ((parent != root) && (parent->key <= key)) {
        // Return (this, parent) via supposed two-register return
        // In C++, return as void* pair placeholder; actual assembly uses EAX=this, EDX=node
        // We'll model as returning a pointer to a PairResult structure
        // For clean reconstruction, we return a void* to match original signature
        // But better to define a return type:
        // PairResult { void* thisPtr; Node* node; };
        // Since original decompiler showed writing to *in_EAX and in_EAX[1], we mimic that.
    }

    // Default: return this and root
    // Similarly, return (this, root)
}

// The actual implementation would return a struct or fill an output buffer.
// Due to decompiler limitations, we present the logic cleanly below.
// Real assembly returns two 32-bit values in registers (EAX=this, EDX=foundNode).

// Cleaner version:
struct FindResult {
    TreeMap* container;
    TreeMap::Node* node;
};

FindResult TreeMap::findFloor(uint32_t key) const {
    Node* current = root;
    Node* parent = root;

    // If root has a right child that is internal, traverse down
    if (current->right && current->right->leafFlag == 0) {
        current = current->right;
        while (current->leafFlag == 0) {
            if (current->key < key) {
                parent = current;
                current = current->right;   // go to larger keys
            } else {
                parent = current;
                current = current->left;    // go to smaller keys
            }
        }
    }

    // After loop, parent is the last internal node visited
    if ((parent != root) && (parent->key <= key)) {
        return {this, parent};
    }
    // Fallback: return the root sentinel
    return {this, root};
}
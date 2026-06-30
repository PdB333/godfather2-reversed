// FUNC_NAME: TreeMap::findOrInsert
// Function address: 0x00621690
// Reconstructed from Ghidra decompilation of The Godfather 2 (EARS engine)
// This function performs a binary search tree lookup and inserts if key not found.
// Returns pointer to the value associated with the key.

// Node structure (size at least 20 bytes):
// +0x00: left child pointer
// +0x04: pointer to node metadata (contains leaf flag at +0x25)
// +0x08: right child pointer
// +0x0C: key (uint)
// +0x10: value (returned as puVar4+4)

struct TreeNode {
    TreeNode* left;          // +0x00
    TreeNode* metadata;      // +0x04 (points to structure with leaf flag at offset 0x25)
    TreeNode* right;         // +0x08
    uint key;                // +0x0C
    uint value;              // +0x10 (or more data)
};

// TreeMap class (simplified)
class TreeMap {
public:
    TreeNode* root; // +0x1C (offset from this)

    // Returns pointer to the value for the given key.
    // If key not found, inserts a new node and returns its value pointer.
    uint* __thiscall findOrInsert(uint key) {
        TreeNode* current = this->root;
        TreeNode* parent = nullptr;

        // Traverse tree until we hit a leaf node
        while (current != nullptr && *(char*)((int)current->metadata + 0x25) == '\0') {
            parent = current;
            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        // If we reached root or key is less than current node's key, we need to insert
        if (parent == nullptr || key < current->key) {
            // Prepare insertion data
            struct InsertData {
                uint key;
                uint pad1[7]; // 8 dwords total? Actually local_3c is 8 bytes, then 6 more dwords? Let's approximate.
            } data;
            data.key = key;
            // Zero out the rest (local_34, uStack_30, etc.)
            memset(&data + 4, 0, sizeof(data) - 4);

            // Call insertion helper (FUN_00622110)
            // Returns a pointer to a pair (int, TreeNode*)
            int* result = FUN_00622110(this, &data, &key, this, parent);
            // Update current and parent from result
            // Note: in_EAX is overwritten by *result, and current by result[1]
            // But we need to handle the fact that in_EAX is used as this later.
            // For reconstruction, we assume the helper returns a structure.
            // Actually the decompiled code does: in_EAX = *piVar3; puVar4 = piVar3[1];
            // So we treat it as:
            int newThis = result[0];
            current = (TreeNode*)result[1];
            // The new this pointer might be the same as original? Possibly.
            // We'll ignore the this change for simplicity.
        }

        // Assertions (FUN_00b97aea likely is an error handler)
        if (this == nullptr) {
            FUN_00b97aea(); // assert(this != nullptr)
        }
        if (current == this->root) {
            FUN_00b97aea(); // assert(current != root) - shouldn't happen after insertion
        }

        // Return pointer to the value (offset +0x10 from node)
        return &current->value;
    }
};
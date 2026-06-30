// FUNC_NAME: BinarySearchTree::findNodeOrNearest
// Address: 0x004c9f20
// This function performs a binary search on the tree, returning the node where the key is less than or equal
// to the search key, or the root if none found. The result is output through a structure pointed to by EAX.
// The tree uses a header node at this+0x1C, with the actual root stored at header+0x04.
// Nodes have left child at +0x00, right child at +0x08, key at +0x0C, and a flag at +0x15 indicating
// whether the node is a sentinel (non‑zero) or real node (zero).

class BinarySearchTree;
class BSTNode {
public:
    BSTNode* left;       // +0x00
    void* data;          // +0x04 (may point to a structure with a flag at +0x15)
    BSTNode* right;      // +0x08
    unsigned int key;    // +0x0C
    // +0x15: flag (probably char) – 0 = real node, non‑zero = sentinel
};

struct BSTResult {
    BinarySearchTree* tree; // offset 0
    BSTNode* node;          // offset 4
};

class BinarySearchTree {
public:
    // +0x1C: header node (dummy)
    BSTNode* header; // actually the header is a BSTNode too, but with special structure
    // header+0x04 is the real root node pointer

    // param_1 = pointer to key, in_EAX = pointer to output BSTResult
    void findNodeOrNearest(const unsigned int* keyPtr) {
        unsigned int key = *keyPtr;
        BSTNode* current = this->header; // +0x1C
        BSTNode* lastNode = current;

        // Check if the real root exists (flag at header->data+0x15 == 0)
        if (current->data != nullptr && *(char*)((int)current->data + 0x15) == '\0') {
            BSTNode* iterNode = (BSTNode*)current->data; // actual root node
            do {
                BSTNode* nextNode;
                if (iterNode->key < key) {
                    nextNode = iterNode->right; // +0x08
                } else {
                    nextNode = iterNode->left;  // +0x00
                    lastNode = iterNode;
                }
                iterNode = nextNode;
            } while (iterNode != nullptr && *(char*)((int)iterNode + 0x15) == '\0');
        }

        // Determine result node
        BSTNode* resultNode;
        if (lastNode != this->header && lastNode->key <= key) {
            resultNode = lastNode;
        } else {
            resultNode = this->header; // actually the real root? We'll stick to header
            // In original, if fallback, resultNode = current (which was header initially)
        }

        // Output result (via hidden pointer in EAX)
        // (simulated as out parameters)
        BSTResult* out = (BSTResult*)__asm__("mov eax, ..."); // not portable, but for reconstruction
        out->tree = this;
        out->node = resultNode;
    }
};
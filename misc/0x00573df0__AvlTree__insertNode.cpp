// FUNC_NAME: AvlTree::insertNode
// Reconstructed C++ for AVL tree insertion at 0x00573df0
// Fields:
// Tree object:
//   +0x00: unknown
//   +0x04: nodeCount (int)
//   +0x08: allocator (void*)
//   +0x0C: allocationFunc (void* (*)(size_t, void*))
// Node object (0x18 bytes):
//   +0x00: height
//   +0x04: unused (always 0)
//   +0x08: left child
//   +0x0C: right child
//   +0x10: key
//   +0x14: value

int* __thiscall AvlTree::insertNode(AvlTree* this, int** root, int* key, int* value)
{
    int* node = *root;
    if (node == nullptr) {
        // Allocate new node
        void* allocator = *(void**)(this + 2); // +0x08
        if (allocator == nullptr) {
            allocator = &g_defaultAllocator; // 0x01218a14
        }
        void* (*allocFunc)(int, void*) = *(void* (**)(int, void*))(this + 3); // +0x0C
        int* newNode = (int*)allocFunc(0x18, allocator);
        if (newNode == nullptr) {
            *root = nullptr;
            *(int*)(this + 1) += 1; // nodeCount++
            return nullptr;
        }
        int* oldRoot = *root; // actually *root is 0 here
        int returnAddr = *((int*)__builtin_return_address(0)); // unaff_retaddr
        newNode[0] = 0; // height = 0
        newNode[1] = 0;
        newNode[2] = 0; // left = null
        newNode[3] = 0; // right = null
        newNode[4] = returnAddr; // key (likely pushed by caller)
        newNode[5] = (int)oldRoot; // parent = old root (0)
        *root = newNode;
        *(int*)(this + 1) += 1;
        return newNode;
    }

    int cmp = *key - *(node + 4); // compare key with node->key
    if (cmp < 0) {
        int* inserted = insertNode(this, (int**)(node + 2), key, value); // left
        if (inserted[1] == 0) {
            inserted[1] = *root; // set parent? Actually offset 4 for node? Might be a bug or different layout.
        }
        // Rebalancing: left height - right height == 2
        int* leftChild = *(int**)(*root + 2);
        int leftVal = (leftChild != nullptr) ? *leftChild : -1;
        int* rightChild = *(int**)(*root + 3);
        int rightVal = (rightChild != nullptr) ? *rightChild : -1;
        if (leftVal - rightVal == 2) {
            int* leftLeft = (leftChild != nullptr) ? *(int**)(leftChild + 2) : nullptr;
            int leftLeftVal = (leftLeft != nullptr) ? *leftLeft : -1;
            if (leftLeftVal <= *key) {
                rotateLeftRight(this, root); // double rotation
            } else {
                rotateRight(this, root);
            }
            return inserted;
        }
    } else if (cmp > 0) {
        int* inserted = insertNode(this, (int**)(node + 3), key, value); // right
        if (inserted[1] == 0) {
            inserted[1] = *root;
        }
        int* leftChild = *(int**)(*root + 2);
        int leftVal = (leftChild != nullptr) ? *leftChild : -1;
        int* rightChild = *(int**)(*root + 3);
        int rightVal = (rightChild != nullptr) ? *rightChild : -1;
        if (rightVal - leftVal == 2) {
            int* rightRight = (rightChild != nullptr) ? *(int**)(rightChild + 3) : nullptr;
            int rightRightVal = (rightRight != nullptr) ? *rightRight : -1;
            if (*key <= rightRightVal) {
                rotateRightLeft(this, root);
            } else {
                rotateLeft(this, root);
            }
            return inserted;
        }
    } else {
        // Key found, update value
        *(int*)(node + 5) = *value; // set value at +0x14
        return node;
    }

    // Fallback: should not reach but calls a balancing routine
    rebalance(this, root);
    return inserted; // note: inserted might be undefined if neither branch taken
}
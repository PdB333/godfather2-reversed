// FUNC_NAME: BSTree::insertNode

struct BSTreeNode {
    BSTreeNode* left;   // +0x00
    int          unknown; // +0x04 (might be parent or something, used as pointer in sentinel check)
    BSTreeNode* right;  // +0x08
    unsigned int key;   // +0x0C
    // ... there may be more fields, at offset 0x15 a flag byte (0 = sentinel, non-zero = real node)
};

struct BSTree {
    BSTreeNode* sentinelOrRoot; // +0x1C? Actually the function reads this pointer: param_1+0x1c -> pointer to a node
    // other fields omitted
};

struct InsertResult {
    BSTreeNode* node1;    // param_2[0]
    BSTreeNode* node2;    // param_2[1]
    char         isNew;   // param_2[2]  (0 = existing, 1 = inserted)
};

// Helper to allocate a new node (called from FUN_00623310)
BSTreeNode* allocateNewNode(unsigned int key); // Not provided

// Helper assertion (called from FUN_00624370)
void insertionError(); // Likely assertion failure

InsertResult* BSTree::insertNode(int* param_2, unsigned int* param_3) {
    BSTreeNode* current = *(BSTreeNode**)(this + 0x1C); // root or sentinel pointer
    bool isLess = true;

    // Check if the node pointed to by current->unknown (offset +0x04) is a sentinel (flag == 0)
    if (*(char*)((int)(current->unknown) + 0x15) == '\0') {
        BSTreeNode* temp = (BSTreeNode*)current->unknown; // treat unknown as pointer
        do {
            current = temp;
            isLess = *param_3 < current->key;
            if (isLess) {
                temp = current->left;
            } else {
                temp = current->right;
            }
        } while (*(char*)((int)temp + 0x15) == '\0'); // continue while child is sentinel
    }

    // Store the 'this' pointer in local variable (used later)
    int treeContainer = (int)this;

    if (isLess) {
        // If we went left from the root, and the current node is actually the root? Need to check sentinel condition
        if (current == *(BSTreeNode**)(*(int*)(this + 0x1C))) { // if current is the very first node (sentinel?) 
            // Allocate new node and insert as left child of root?
            int* newNodes = (int*)FUN_00623310(this, &treeContainer, 1, param_3);
            param_2[0] = newNodes[0];
            param_2[1] = newNodes[1];
            *(char*)&param_2[2] = 1;
            return (InsertResult*)param_2;
        }
        // Otherwise, an error condition: inserting when should be impossible?
        FUN_00624370();
    }

    if (current->key < *param_3) {
        // Key is greater than current node key, go right and allocate
        int* newNodes = (int*)FUN_00623310(this, &treeContainer, isLess, param_3);
        param_2[0] = newNodes[0];
        param_2[1] = newNodes[1];
        *(char*)&param_2[2] = 1;
        return (InsertResult*)param_2;
    }

    // Key found: return existing node
    param_2[0] = treeContainer;   // Note: This seems suspicious - storing treeContainer? But original code had param_2[0] = local_8, which is param_1 (this). So we keep that.
    param_2[1] = (int)current;
    *(char*)&param_2[2] = 0;
    return (InsertResult*)param_2;
}
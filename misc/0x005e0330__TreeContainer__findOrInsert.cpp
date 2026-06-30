// FUNC_NAME: TreeContainer::findOrInsert
struct RBTreeNode {
    RBTreeNode* left;   // +0x00
    RBTreeNode* parent; // +0x04
    RBTreeNode* right;  // +0x08
    unsigned int key;   // +0x0C
    char isNil;         // +0x15 (0 = real node, 1 = sentinel)
};

struct InsertResult {
    TreeContainer* container; // +0x00
    RBTreeNode* node;         // +0x04
    char inserted;            // +0x08 (0 = found, 1 = inserted)
};

int* FUN_005e0510(TreeContainer* container, InsertResult* result, char goLeft, unsigned int* key);
void FUN_005e1540();

InsertResult* __thiscall TreeContainer::findOrInsert(TreeContainer* this, InsertResult* result, unsigned int* keyPtr) {
    RBTreeNode* header = *(RBTreeNode**)((char*)this + 0x1C);
    RBTreeNode* cur;
    RBTreeNode* child;
    char goLeft = 1;

    if (header->parent->isNil == 0) {
        child = header->parent;
        do {
            cur = child;
            goLeft = *keyPtr < cur->key;
            if (goLeft) {
                child = cur->left;
            } else {
                child = cur->right;
            }
        } while (child->isNil == 0);
    }

    TreeContainer* container = this;

    if (goLeft) {
        if (cur == header->left) {
            int* ins = FUN_005e0510(this, &container, 1, keyPtr);
            result->container = (TreeContainer*)ins[0];
            result->node = (RBTreeNode*)ins[1];
            result->inserted = 1;
            return result;
        }
        FUN_005e1540();
    }

    if (cur->key < *keyPtr) {
        int* ins = FUN_005e0510(this, &container, goLeft, keyPtr);
        result->container = (TreeContainer*)ins[0];
        result->node = (RBTreeNode*)ins[1];
        result->inserted = 1;
        return result;
    }

    result->container = this;
    result->node = cur;
    result->inserted = 0;
    return result;
}
// FUNC_NAME: RbTree::insertKey
// This function implements a red-black tree insertion for a map/set container.
// It searches for a key, and if not found, inserts a new node.
// The tree uses a sentinel node (color byte at +0x15 == 0) to mark leaves.
// Parameters:
//   this    - pointer to tree container (header node at +0x1c)
//   result  - output struct (node pointer, bool inserted)
//   keyPtr  - pointer to key value to be inserted/found

struct RbNode {
    RbNode* left;       // +0x00
    RbNode* parent;     // +0x04
    RbNode* right;      // +0x08
    uint32_t key;       // +0x0C
    // +0x10..+0x14 padding or other data
    uint8_t color;      // +0x15 (0 = black/sentinel, non-zero = red)
};

struct InsertResult {
    RbNode* node;    // +0x00
    RbNode* parent;  // +0x04? (used internally, but stored as node? Actually output is node pointer and flag)
    uint8_t isNew;   // +0x08 (0 = existing, 1 = newly inserted)
};

InsertResult* __thiscall RbTree::insertKey(InsertResult* result, uint32_t* keyPtr)
{
    RbNode* header = *(RbNode**)(this + 0x1c);   // tree header sentinel
    bool wentLeft = true;                         // bVar4
    RbNode* current = header;                     // local_4

    if (*(uint8_t*)((int)header->parent + 0x15) == 0) {
        // Traverse from the root (header->parent) down to the insertion point
        RbNode* child = header->parent;           // puVar2
        do {
            current = child;
            wentLeft = *keyPtr < current->key;
            if (wentLeft) {
                child = current->left;
            } else {
                child = current->right;
            }
        } while (*(uint8_t*)((int)child + 0x15) == 0); // stop at sentinel
    }

    // If we went left and current is the leftmost node (header->left), insert new node
    if (wentLeft) {
        if (current == *(RbNode**)(*(int*)(this + 0x1c))) { // compare with header->left?
            RbNode* newNode = (RbNode*)FUN_005df5f0(this, &result->parent, 1, keyPtr);
            result->node = (RbNode*)(newNode[0]); // dereference? Actually likely copy from newNode
            result->node = newNode; // correct based on code: *param_2 = iVar1; param_2[1] = piVar3[1];
            result->isNew = 1;
            return result;
        }
        FUN_005e1230(); // maybe error handling or rebalance
    }

    // After traversal, decide whether key already exists or should be inserted
    if (current->key < *keyPtr) {
        RbNode* newNode = (RbNode*)FUN_005df5f0(this, &result->parent, wentLeft, keyPtr);
        result->node = newNode;
        result->isNew = 1;
    } else {
        // Key already exists
        result->node = current;
        result->parent = (RbNode*)result; // ??? this line is odd: param_2[1] = (int)local_4; *param_2 = local_8;
        result->isNew = 0;
    }

    return result;
}
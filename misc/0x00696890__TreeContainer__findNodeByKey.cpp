// FUNC_NAME: TreeContainer::findNodeByKey
// Function at 0x00696890: Performs a search in a binary tree structure, returning data associated with a key.
// This appears to be a generic tree lookup with comparison functions.
// The tree nodes have fields at +0x0C (key?) and +0x08 (parent? flags?).
// The container (this) has fields at +0x04 (root pointer) and +0x08 (empty flag).

// Note: Due to ambiguity, some variable names are inferred.
// FUN_00695f00 likely stores a "not found" result (type and data).
// FUN_00693990 checks if a node contains a specific key.
// FUN_00696630 searches for the exact node and returns its data pointer.
// FUN_004d4b20 is a comparison function (e.g., strcmp-like) on keys.

// The function takes an output buffer (param_2) that receives two 32-bit values (probably node data or handles).

void * __thiscall TreeContainer::findNodeByKey(int this, uint *outData, int validateThis, int currentNode, uint key)
{
    // this+0x08: empty flag (int)
    if (*(int *)(this + 8) == 0) {
        // Tree is empty – return "not found" with type 1 and some default value
        FUN_00695f00(outData, 1, *(int *)(this + 4), key);
        return outData;
    }

    // this+0x04: pointer to root node (dereferenced twice)
    int rootValue = **(int **)(this + 4);

    // Validation: validateThis must be 0 or equal to 'this'
    if ((validateThis == 0) || (validateThis != this)) {
        FUN_00b97aea(); // likely assertion failure
    }

    if (currentNode == rootValue) {
        // currentNode is the root
        int compareResult = FUN_004d4b20(currentNode + 0x0C); // compare key at node->keyOffset to key (implied)
        if (compareResult < 0) {
            // Node key is less than target? Return not found with type 1 and node value
            FUN_00695f00(outData, 1, currentNode, key);
            return outData;
        }
    }
    else {
        // currentNode is not root
        int actualRoot = *(int *)(this + 4);
        if ((validateThis == 0) || (validateThis != this)) {
            FUN_00b97aea();
        }
        if (currentNode == actualRoot) {
            // Now currentNode equals root (contradiction? maybe a different path)
            int compareResult2 = FUN_004d4b20(key); // compare key???
            if (compareResult2 < 0) {
                // Return not found with type 0 and value from root->next (root+8)
                FUN_00695f00(outData, 0, *(int *)(*(int *)(this + 4) + 8), key);
                return outData;
            }
        }
        else {
            // General case: compare currentNode + 0x0C to key
            int compareResult3 = FUN_004d4b20(currentNode + 0x0C);
            if (compareResult3 < 0) {
                FUN_00694060(); // some helper
                char hasKey = FUN_00693990(currentNode + 0x0C, key);
                if (hasKey) {
                    if (*(char *)(*(int *)(currentNode + 8) + 0x25) != '\0') {
                        // Node has some flag set – return type 0
                        FUN_00695f00(outData, 0, currentNode, key);
                        return outData;
                    }
                    // Return type 1
                    FUN_00695f00(outData, 1, currentNode, key);
                    return outData;
                }
            }
            // Another key check (duplicate?)
            char hasKey2 = FUN_00693990(currentNode + 0x0C, key);
            if (hasKey2) {
                // Prepare for recursion/search helper?
                int local_8 = *(int *)(this + 4);
                int local_c = this;
                FUN_006940f0(); // setup?
                char checkResult = FUN_00693b80(&local_c); // compare something
                if (checkResult == '\0') {
                    char hasKey3 = FUN_00693990(key, currentNode + 0x0C); // swapped parameters
                    if (hasKey3 == '\0') goto LAB_00696a60;
                }
                if (*(char *)(*(int *)(currentNode + 8) + 0x25) != '\0') {
                    FUN_00695f00(outData, 0, currentNode, key);
                    return outData;
                }
                FUN_00695f00(outData, 1, currentNode, key);
                return outData;
            }
        }
    }

LAB_00696a60:
    // Fallback: use a recursive/traversal function to find exact node
    void *foundNode = (void *)FUN_00696630(&local_c, key);
    *outData = *(uint *)foundNode;
    outData[1] = *(uint *)((char *)foundNode + 4);
    return outData;
}
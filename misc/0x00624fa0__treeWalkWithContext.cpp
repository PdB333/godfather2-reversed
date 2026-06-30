// FUNC_NAME: treeWalkWithContext
// Address: 0x00624fa0
// This function recursively walks a tree-like structure. 
// Each node has a vtable (offset 0), a byte flag at +5 (bit 2 tested), an integer at +6, 
// a pointer to a child list head at +8, and a next sibling pointer at +0x28.
// The function iterates over children, recursing on each, and returns an integer that is decremented as it goes up.
// The context parameters (a1, a2, a3) are passed through and used in virtual method calls.

struct TreeNode {
    void** vtable;          // +0x00
    char unknown[4];        // +0x04 (padding or other fields)
    char flags;             // +0x05
    int field6;             // +0x06
    TreeNode* firstChild;   // +0x08
    char unknown2[0x1C];    // +0x0C to +0x27
    TreeNode* nextSibling;  // +0x28
};

// Type for a virtual method at vtable index 5 (0x14/4 = 5)
// This method is called when certain conditions are met.
typedef TreeNode* (__thiscall* GetNextNodeFunc)(TreeNode* self, void* a1, void* a2, void* a3, int* outVal, int zero);

// Recursive tree walk function.
int treeWalkWithContext(void* a1, void* a2, void* a3, TreeNode* node) {
    int result = 0;
    TreeNode* currentNode = node;

    // Check if node is null
    if (currentNode != nullptr) {
        // If node has no field6, or no firstChild, or the flags bit 2 is set,
        // replace currentNode by calling a virtual method that returns the "next" node.
        if (currentNode->field6 == 0 || currentNode->firstChild == 0 || (currentNode->flags & 4) != 0) {
            GetNextNodeFunc func = (GetNextNodeFunc)(currentNode->vtable[5]); // vtable+0x14
            int localOut = 0;
            currentNode = func(currentNode, a1, a2, a3, &localOut, 0);
            result = localOut;
        }

        // If currentNode is not null and has a firstChild
        if (currentNode != nullptr && currentNode->firstChild != nullptr) {
            TreeNode* child = currentNode->firstChild;
            while (true) {
                TreeNode* nextChild = child->nextSibling; // save next before recursion
                result = treeWalkWithContext(a1, a2, a3, child);
                if (result != 0) break;
                child = nextChild;
                if (child == nullptr) return 0;
            }
            // Decrement the result (indicates traversal depth or index)
            result = result - 1;
        }
    }
    return result;
}
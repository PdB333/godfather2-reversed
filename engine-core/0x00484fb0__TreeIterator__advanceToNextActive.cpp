// FUNC_NAME: TreeIterator::advanceToNextActive
// Address: 0x00484fb0
// Reconstructed C++ from Ghidra decompile. This function advances the iterator to the next active node in a tree structure.
// The tree node structure (unknown full layout) has fields at offsets:
// +0x00: nextSibling (TreeNode*)
// +0x04: parent (TreeNode*)
// +0x08: firstChild (TreeNode*)
// +0x15: active flag (char, non-zero if active)
// The iterator stores root at +0x00 and current node at +0x04.
// Expects current node to be inactive; moves to next active node in traversal order.

class TreeIterator {
public:
    TreeNode* root;    // +0x00
    TreeNode* current; // +0x04

    void advanceToNextActive() {
        if (root == nullptr) {
            errorFunc(0x00b97aea); // Assertion failure
        }
        TreeNode* node = current; // iVar2
        if (node->active != 0) {
            errorFunc(0x00b97aea); // Assertion failure: should only call on inactive node
        }
        TreeNode* child = node->firstChild; // piVar3 = *(int**)(iVar2+8)
        if (child != nullptr && child->active != 0) {
            // First child is active: walk up parent chain until finding an active ancestor
            // that has the original current as its first child.
            node = node->parent; // iVar2 = *(int*)(iVar2+4)
            while (node->active == 0 && current == node->firstChild) {
                current = node;
                node = node->parent;
            }
            current = node;
            return;
        }
        // else: traverse the sibling chain starting from child's sibling
        // Assumes child is non-null here (no explicit null guard in decompiled code)
        char activeFlag = child->nextSibling->active; // cVar1 = *(char*)(*piVar3+0x15)
        TreeNode* scan = child->nextSibling;          // piVar4 = *(int*)*piVar3
        while (activeFlag == 0) {
            activeFlag = scan->nextSibling->active;   // *(char*)(*piVar4+0x15)
            child = scan;                              // piVar3 = piVar4
            scan = scan->nextSibling;                  // piVar4 = *(int*)*piVar4
        }
        current = child; // set to node preceding the first active sibling
    }

private:
    void errorFunc(uint32_t addr) {
        // Placeholder for FUN_00b97aea (likely an assertion abort)
    }
};
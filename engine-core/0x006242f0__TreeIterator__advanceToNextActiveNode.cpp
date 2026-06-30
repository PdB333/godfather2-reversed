// FUNC_NAME: TreeIterator::advanceToNextActiveNode
// Function address: 0x006242f0
// Reconstructed from Ghidra decompilation. This function appears to advance a tree iterator
// to the next active node based on a flag at offset 0x25. The tree node structure is inferred:
//   +0x00: Node* parent
//   +0x04: Node* nextSibling
//   +0x08: Node* firstChild
//   +0x25: char activeFlag

struct TreeNode {
    TreeNode* parent;           // +0x00
    TreeNode* nextSibling;      // +0x04
    TreeNode* firstChild;       // +0x08
    // ... other fields ...
    char activeFlag;            // +0x25
};

class TreeIterator {
public:
    int someCounter;            // +0x00 (unknown purpose)
    TreeNode* current;          // +0x04

    // Moves the iterator to the next "active" node in the tree traversal.
    // If no active node is found, calls resetFunction().
    void advanceToNextActiveNode() {
        if (someCounter == 0) {
            resetFunction(); // FUN_00b97aea – initializes or resets iterator
        }

        TreeNode* node = current;

        if (node->activeFlag == '\0') {
            // Current node not active – try to traverse upward or sideways
            TreeNode* parent = node->parent; // iVar3
            if (parent->activeFlag == '\0') {
                // Parent also not active – go deep into parent's children
                TreeNode* child = parent->firstChild; // iVar4
                while (child->activeFlag == '\0') {
                    parent = child;
                    child = child->firstChild;
                }
                current = parent; // set to the node whose child was active
                return;
            } else {
                // Parent is active, so move to next sibling
                TreeNode* sibling = node->nextSibling;
                while ((sibling->activeFlag == '\0') && (current == sibling->parent)) {
                    current = sibling;
                    sibling = sibling->nextSibling;
                }
                if (current->activeFlag != '\0') {
                    resetFunction();
                    return;
                }
                current = sibling;
            }
        } else {
            // Current node is active – move to its first child
            TreeNode* child = node->firstChild;
            current = child;
            if (child->activeFlag != '\0') {
                resetFunction();
                return;
            }
        }
    }

private:
    void resetFunction(); // Called when tree traversal needs a reset (FUN_00b97aea)
};
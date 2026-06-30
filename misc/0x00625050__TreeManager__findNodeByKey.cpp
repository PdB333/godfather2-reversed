// FUNC_NAME: TreeManager::findNodeByKey

// Function at 0x00625050: Recursive tree search by key
// Searches a binary tree-like structure (child+sibling) for a node whose virtual getKey() matches targetKey.
// Node structure:
//   +0x00: vtable pointer (has virtual int getKey())
//   +0x20: child pointer (TreeNode*)
//   +0x28: sibling pointer (TreeNode*)
// This object (TreeManager) has root node pointer at +0x04.

struct TreeNode {
    void** vtable;          // +0x00
    // +0x04..+0x1C: unknown
    TreeNode* child;        // +0x20
    TreeNode* sibling;      // +0x28

    int getKey() const {
        // Call vtable function at index 0 (first virtual)
        return reinterpret_cast<int (*)(const TreeNode*)>(vtable[0])(this);
    }
};

class TreeManager {
public:
    TreeNode* root;         // +0x04

    // __thiscall, parameter order: this (ecx), targetKey (stack), startNode (stack)
    // If startNode is null, uses this->root as starting point.
    TreeNode* findNodeByKey(int targetKey, TreeNode* startNode) {
        if (startNode == nullptr) {
            startNode = this->root;
            if (startNode == nullptr) {
                return nullptr;
            }
        }

        // Check current node's key
        if (startNode->getKey() == targetKey) {
            return startNode;
        }

        // Search through child tree
        TreeNode* childNode = startNode->child;
        if (childNode != nullptr) {
            TreeNode* result = findNodeByKey(targetKey, childNode);
            if (result != nullptr) {
                return result;
            }
        }

        // Search through sibling chain
        TreeNode* siblingNode = startNode->sibling;
        while (siblingNode != nullptr) {
            TreeNode* result = findNodeByKey(targetKey, siblingNode);
            if (result != nullptr) {
                return result;
            }
            siblingNode = siblingNode->sibling;
        }

        return nullptr;
    }
};
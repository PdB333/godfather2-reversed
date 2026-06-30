// FUNC_NAME: TreeIterator::advanceToActiveNode

// Reconstructed from 0x00623fa0 - TreeIterator: advance to next active node in inorder
// Uses threaded binary tree with parent, inorder predecessor/successor.
// Node fields: +0x00 parent, +0x04 prev (inorder), +0x08 next (inorder), +0x25 active flag.

struct TreeNode {
    TreeNode* parent;    // +0x00
    TreeNode* prev;      // +0x04 (inorder predecessor)
    TreeNode* next;      // +0x08 (inorder successor)
    // ... other data ...
    char active;         // +0x25
};

struct TreeIterator {
    TreeNode* root;      // +0x00
    TreeNode* current;   // +0x04
};

void __thiscall TreeIterator::advanceToActiveNode(void) {
    // unaff_ESI = this (TreeIterator*)
    TreeNode* cur;
    TreeNode* nextNode;
    TreeNode* prevNode;
    TreeNode* temp;
    char flag;

    if (this->root == nullptr) {
        _assertionFail(); // FUN_00b97aea
    }

    cur = this->current;
    if (!cur->active) {
        nextNode = cur->next;
        if (nextNode->active) {
            // The successor is active; move to the leftmost descendant of cur's predecessor?
            prevNode = cur->prev;
            flag = prevNode->active;
            while (flag == 0 && this->current == prevNode->next) {
                this->current = prevNode;
                prevNode = prevNode->prev;
                flag = prevNode->active;
            }
            this->current = prevNode;
            return;
        }
        // Successor is also inactive; climb parent chain from successor until an active node is found
        temp = nextNode->parent;
        while (!temp->active) {
            temp = temp->parent;
        }
        this->current = temp;
        return;
    }
    // Current node is active – should not happen (assertion)
    _assertionFail();
}
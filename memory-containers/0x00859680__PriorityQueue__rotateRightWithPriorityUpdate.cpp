// FUNC_NAME: PriorityQueue::rotateRightWithPriorityUpdate
// Address: 0x00859680
// This function performs a right rotation (left child becomes parent) in a treap-like priority tree,
// updating the priority of the affected nodes based on the max priority of their children + 1.
// Parameters: param_1 (this) -> pointer to PriorityQueue object containing mRoot
//             param_2 -> pointer to the link (e.g., &mRoot, &parent->left, &parent->right) that currently points to the old subtree root

struct PriorityNode {
    int priority;            // +0x00: heap priority (key)
    PriorityNode* parent;    // +0x04: parent node
    PriorityNode* left;      // +0x08: left child
    PriorityNode* right;     // +0x0C: right child
};

class PriorityQueue {
public:
    PriorityNode* mRoot;     // +0x00: root of the tree

    // Perform a right rotation on the subtree whose root is pointed to by nodePtr.
    // nodePtr is a pointer to the pointer that holds the current root (e.g., &mRoot or a parent's child pointer).
    // After rotation, nodePtr is updated to point to the new root (the old left child).
    // Also updates the tree's mRoot if the rotated node was the overall root.
    void __thiscall rotateRight(PriorityNode** nodePtr);
};

void __thiscall PriorityQueue::rotateRight(PriorityNode** nodePtr) {
    PriorityNode* oldRoot = *nodePtr;           // X: node being rotated down
    PriorityNode* newRoot = oldRoot->left;      // Y: node being rotated up (must be non-null)
    PriorityNode* savedParent = oldRoot->parent; // parent of the old root (may be null)

    // Step 1: Unlink newRoot from oldRoot and fix its right child
    oldRoot->left = newRoot->right;
    if (newRoot->right != nullptr) {
        newRoot->right->parent = oldRoot;
    }

    // Step 2: Attach oldRoot as right child of newRoot
    newRoot->right = oldRoot;
    oldRoot->parent = newRoot;

    // Step 3: Update priorities using heap property: priority = max(child priorities) + 1
    // For oldRoot (now child of newRoot)
    int leftPriority = (oldRoot->left != nullptr) ? oldRoot->left->priority : -1;
    int rightPriority = (oldRoot->right != nullptr) ? oldRoot->right->priority : -1;
    oldRoot->priority = (leftPriority > rightPriority ? leftPriority : rightPriority) + 1;

    // For newRoot
    leftPriority = (newRoot->left != nullptr) ? newRoot->left->priority : -1;
    rightPriority = (newRoot->right != nullptr) ? newRoot->right->priority : -1;
    newRoot->priority = (leftPriority > rightPriority ? leftPriority : rightPriority) + 1;

    // Step 4: Fix the parent link of newRoot
    newRoot->parent = savedParent;

    // Step 5: Update the link that pointed to oldRoot to now point to newRoot
    if (savedParent != nullptr) {
        // Determine whether oldRoot was the left or right child of its parent
        if (savedParent->left == oldRoot) {
            savedParent->left = newRoot;
        } else { // must be right child
            savedParent->right = newRoot;
        }
        // Update the node pointer passed in (nodePtr) to the new root (already done below)
    } else {
        // newRoot is the new overall root, update the class member
        this->mRoot = newRoot;
    }

    // Always update the pointer passed in (nodePtr) to reflect the new subtree root
    *nodePtr = newRoot;
}
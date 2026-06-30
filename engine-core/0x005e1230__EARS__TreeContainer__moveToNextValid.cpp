// FUNC_NAME: EARS::TreeContainer::moveToNextValid

// Reconstructed from address 0x005e1230.
// Advances the internal iterator to the next "valid" node in the tree.
// The tree uses an intrusive structure with nodes containing:
//   +0x00: Node* left (or prev)
//   +0x04: Node* right (or next)
//   +0x08: Node* parent (or another cross-link)
//   +0x15: bool isValid (flag, 0 = invalid/free, non-zero = valid/occupied)
// Container object (this) has:
//   +0x00: Node* root (or sentinel, zero means empty)
//   +0x04: Node* currentNode (iterator position)

void __thiscall EARS::TreeContainer::moveToNextValid(void)
{
    bool bIsValid;
    Node* currentNode;
    Node* tempNode;
    Node* childNode;

    // If the tree is empty, reset the container (e.g., set currentNode to end marker)
    if (this->root == 0) {
        this->resetContainer();
    }

    currentNode = this->currentNode;  // This->+0x04

    if (!currentNode->isValid) {  // +0x15 == 0
        // Current node is invalid; find the next valid node
        tempNode = currentNode->left;  // *currentNode (first int = left pointer)

        if (!tempNode->isValid) {
            // Left child is also invalid; follow right children of left subtree
            childNode = tempNode->right;  // tempNode->+0x08
            bIsValid = childNode->right->isValid;  // Next node after childNode

            while (!bIsValid) {
                bIsValid = childNode->right->isValid;
                tempNode = childNode;
                childNode = childNode->right;
            }
            this->currentNode = tempNode;
            return;
        }
        else {
            // Left child is valid; move to right sibling and follow until we find an invalid node or loop back
            currentNode = currentNode->right;  // currentNode->+0x04
            bIsValid = currentNode->isValid;

            while (!bIsValid && this->currentNode == currentNode->left) {
                this->currentNode = currentNode;
                currentNode = currentNode->right;
                bIsValid = currentNode->isValid;
            }

            if (this->currentNode->isValid) {
                // Reached a valid node unexpectedly – reset
                this->resetContainer();
                return;
            }
            this->currentNode = currentNode;
        }
    }
    else {
        // Current node is valid; move to its parent (or the node at +0x08)
        tempNode = currentNode->parent;  // currentNode->+0x08
        this->currentNode = tempNode;
        if (tempNode->isValid != '\0') {
            // Parent is also valid – reset (likely end of traversal)
            this->resetContainer();
            return;
        }
    }
}
// FUNC_NAME: ContainerIterator::nextValidNode
// Function at 0x004cab50 - Advances iterator to next valid node in a linked tree structure
// Node structure (size >= 0x18): 
//   +0x00: Node* pNext (linked list next)
//   +0x04: Node* pChild (or sibling in traversal order)
//   +0x08: Node* pParent (or right child)
//   +0x15: byte bValid (1 = valid, 0 = invalid/placeholder)
// Iterator fields:
//   +0x00: Node* pRoot (sentinel/root, checked for null)
//   +0x04: Node* pCurrent (current node)

void ContainerIterator::nextValidNode(void) {
    Node* currentNode;   // iVar2, current node from iterator
    Node* parentOrRight; // piVar3, from offset +8 of node
    Node* nextNode;      // piVar4, for linked list traversal
    char validFlag;

    // Verify root is not null
    if (this->pRoot == 0) {
        FUN_00b97aea(); // likely exception/assert
    }

    currentNode = this->pCurrent;
    // Expect current node to be invalid (flag zero); if valid, assert
    if (currentNode->bValid == 0) {
        parentOrRight = *(Node**)((char*)currentNode + 8); // Node* at +8 (parent or right child)
        if (parentOrRight->bValid != 0) {
            // Right subtree exists and is valid: go to leftmost child
            // Use offset +4 as child pointer
            currentNode = *(Node**)((char*)currentNode + 4); // Next child/sibling
            validFlag = currentNode->bValid;
            // Descend until find a valid node or parent changes
            while ((validFlag == 0) && (this->pCurrent == *(Node**)((char*)currentNode + 8))) {
                this->pCurrent = currentNode;
                currentNode = *(Node**)((char*)currentNode + 4);
                validFlag = currentNode->bValid;
            }
            this->pCurrent = currentNode;
            return;
        }
        
        // Right subtree is invalid: follow linked list at offset 0 to find next valid node
        validFlag = parentOrRight->bValid; // should be zero
        // Start from parentOrRight, traverse linked list (offset 0 is next)
        nextNode = (Node*)*(int*)parentOrRight; // pNext
        while (validFlag == 0) {
            validFlag = nextNode->bValid;
            parentOrRight = nextNode;
            nextNode = (Node*)*(int*)nextNode; // follow pNext
        }
        this->pCurrent = parentOrRight;
        return;
    }
    
    // Current node is valid - assert (should not happen)
    FUN_00b97aea();
    return;
}
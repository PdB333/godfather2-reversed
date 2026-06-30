// FUNC_NAME: Node::replaceOrInsertAfter
// Function at 0x005f5c60
// Inserts this node after the given target node, or updates its value if already associated with that node.
// Node structure:
//   +0x00 keyNode (Node*) - the node after which this node is inserted (or null if head?)
//   +0x04 next (Node*) - linked list next pointer
//   +0x08 value (int)
void __thiscall Node::replaceOrInsertAfter(Node* targetNode, int newValue)
{
    // If this node's key already points to targetNode, just update the value
    if (this->keyNode == targetNode) {
        this->value = newValue;
        return;
    }

    // If this node has a current key (i.e., is linked), remove it from its current list
    if (this->keyNode != nullptr) {
        FUN_004daf90(this);  // unlink/cleanup the node from its previous position
    }

    // Set the new key (the node after which this will be inserted)
    this->keyNode = targetNode;

    // If targetNode is valid, insert this node directly after it
    if (targetNode != nullptr) {
        this->next = targetNode->next;       // point to the node after target
        targetNode->next = this;             // target now points to this node
    }

    // Update the stored value
    this->value = newValue;
}
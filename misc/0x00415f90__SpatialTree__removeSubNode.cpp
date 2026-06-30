// FUNC_NAME: SpatialTree::removeSubNode
void __thiscall SpatialTree::removeSubNode(int* nodeArray, int x, int y, int depth, Node* nodeToRemove) {
    int childXIndex, childYIndex, childIndex;
    Node* childNode;

    // Decrement some temporary count in the node array (maybe temp node count)
    nodeArray[1]--;

    // Compute child indices based on coordinates and depth
    int shift = depth * 4;
    childXIndex = (x >> shift) & 0xF;  // 4 bits per level (16 children per node)
    childYIndex = (y >> shift) & 0xF;
    childIndex = childXIndex * 16 + childYIndex + 2;  // +2 because indices 0 and 1 are counts

    childNode = (Node*)nodeArray[childIndex];

    if (depth != 0) {
        // Recurse into the child node with adjusted coordinates and lower depth
        int childX = x - (childXIndex << shift);
        int childY = y - (childYIndex << shift);
        removeSubNode(childNode, childX, childY, depth - 1, nodeToRemove);

        // After recursion, check if child node has zero references and needs to be freed
        if (childNode->refCount == 0) {
            // Call release method on the allocator (this->allocator->release)
            (this->allocator->vtable->release)(childNode, 0);
            this->rootNode = nullptr;
            nodeArray[0]--;  // Decrement total node count
        }
        return;
    }

    // Leaf node removal: unlink from doubly linked list
    if (nodeToRemove->next != nullptr) {
        nodeToRemove->next->prev = nodeToRemove->prev;
    }
    if (nodeToRemove->prev == nullptr) {
        // If no previous, this node was the head of its list; update the parent's child slot
        nodeArray[childIndex] = (int)nodeToRemove->next;
    } else {
        nodeToRemove->prev->next = nodeToRemove->next;
    }
    nodeArray[0]--;  // Decrement total node count
}
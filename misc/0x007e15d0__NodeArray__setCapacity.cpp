// FUNC_NAME: NodeArray::setCapacity
void __thiscall NodeArray::setCapacity(int newCapacity)
{
    if (this->capacity >= newCapacity) {
        return; // Already large enough
    }

    // Allocate new block of nodes (each node is 8 bytes: object pointer + next pointer)
    Node* newNodes = (Node*)operator new(newCapacity * sizeof(Node));

    if (this->nodes != nullptr) {
        // Copy existing nodes to new array, adjusting object back‑pointers
        for (uint i = 0; i < this->count; i++) {
            Node* oldNode = &this->nodes[i];
            Node* newNode = &newNodes[i];

            void* obj = oldNode->object;          // +0x00
            newNode->object = obj;
            newNode->next = nullptr;              // +0x04

            if (obj != nullptr) {
                // The object (at +0x04) holds a pointer to its current node;
                // relocate it to point to the new node, and preserve the old link.
                newNode->next = *(Node**)((byte*)obj + 4);   // save old next pointer
                *(Node**)((byte*)obj + 4) = newNode;         // object now points to new node
            }

            // Destroy the old node (likely removes it from any internal list)
            nodeDestroy(oldNode);
        }

        operator delete(this->nodes); // Free old node array
    }

    this->nodes = newNodes;
    this->capacity = newCapacity;
}
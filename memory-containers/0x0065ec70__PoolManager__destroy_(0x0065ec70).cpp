// FUNC_NAME: PoolManager::destroy (0x0065ec70)
// Destructor/cleanup: frees TLS, critical section, handle, three buffers, then clears a linked list of nodes.
void PoolManager::destroy(void) {
    // Step 1: Set vtable to original class vtable (PTR_LAB_00e43500) – likely the derived class vtable
    this->vtable = &PTR_LAB_00e43500;

    // Free the TLS index stored at offset 0x4C (0x13 * 4)
    TlsFree(this->tlsIndex); // +0x4C

    // Delete critical section at offset 0x34 (0xD * 4)
    DeleteCriticalSection(&this->criticalSection); // +0x34

    // Close handle at offset 0x30 (0xC * 4) – likely an event or thread handle
    CloseHandle(this->handle); // +0x30

    // Free three previously allocated buffers
    free(this->buffer1); // +0x2C (offset 0xB)
    free(this->buffer2); // +0x20 (offset 0x8)
    free(this->buffer3); // +0x14 (offset 0x5)

    // Step 2: Change vtable to another vtable (PTR_LAB_00e42de4) – likely base class vtable
    this->vtable = &PTR_LAB_00e42de4;

    // Clear linked list starting at offset 0x04 (head pointer)
    Node* currentNode = this->head; // +0x04
    while (currentNode != nullptr) {
        Node* nextNode = currentNode->next; // each node: next at offset 0x08
        // Clear the three fields of the node (offsets 0x00, 0x04, 0x08)
        currentNode->field0 = 0;
        currentNode->field4 = 0;
        currentNode->next = nullptr;
        currentNode = nextNode;
    }
}
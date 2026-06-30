// FUN_NAME: ObjectManager::releaseUnreferencedObjects
void __thiscall ObjectManager::releaseUnreferencedObjects(int typeId, int context) {
    Node* currentNode = reinterpret_cast<Node*>(this->currentNode); // +0x04
    Node* endNode = reinterpret_cast<Node*>(this->endNode);         // +0x0c

    while (currentNode != endNode) {
        SubObject* subObject = currentNode->subListHead; // +0x20
        SubObject* subListTail = currentNode->subListTail; // +0x28

        while (subObject != subListTail) {
            SubObject* nextSubObject = subObject->next; // +0x10 (offset 0x40)
            int type = subObject->typeId; // +0x49, stored as int
            int adjustedType;
            if (type == 0) {
                adjustedType = 0;
            } else {
                adjustedType = type - 4;
            }

            if ((adjustedType == typeId) && (subObject->resourcePtr != 0)) {
                // Context contains a resource lock identifier at +0xa0
                acquireResourceLock(*(int*)(context + 0xa0)); // FUN_0066df80
                if (*(int*)(subObject->resourcePtr + 0x10) == 0) { // Check if resource reference count is zero
                    releaseResourceLock(); // FUN_0066dfe0

                    // Remove subObject from the linked list (prev at +0x44, next at +0x40)
                    subObject->prev->next = subObject->next; // *(subObject->prev + 0x40) = subObject->next
                    subObject->next->prev = subObject->prev; // *(subObject->next + 0x44) = subObject->prev

                    // Call virtual destructor (vtable+4)
                    void (*destructor)(void*) = reinterpret_cast<void (*)(void*)>(subObject->vtable[1]); // *( *subObject + 4 )
                    destructor(subObject);

                    // Insert into free list at manager offset +0x37c08
                    subObject->next = reinterpret_cast<SubObject*>(this->freeListHead); // +0x37c08
                    this->freeListHead = subObject;
                }
            }
            subObject = nextSubObject;
        }
        currentNode = currentNode->next; // +0x2c
    }
}
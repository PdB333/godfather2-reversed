// FUNC_NAME: EARS::GenericCollection::~GenericCollection
void EARS::GenericCollection::~GenericCollection()
{
    // vtable table pointers for destructor phase
    *this->vtablePtr = &PTR_LAB_00e43124; // Switch vtable to destructor phase 1
    
    // Free allocated buffer at offset +0x0C
    if (this->allocatedBuffer != 0) {
        FUN_00663460(this->allocatedBuffer);
        free(this->allocatedBuffer);
    }
    
    // Release first ref-counted object at offset +0x18
    int* refObj1 = (int*)this->refCountedObj1; // +0x18
    if (refObj1 != 0) {
        int* refCount1 = refObj1 + 2; // ref count at +0x08
        *refCount1 = *refCount1 - 1;
        if (*refCount1 == 0) {
            // vtable+8 is destructor of the ref-counted object
            (*(void (**)(void))(*refObj1 + 8))();
        }
    }
    
    // Release second ref-counted object at offset +0x1C
    int* refObj2 = (int*)this->refCountedObj2; // +0x1C
    if (refObj2 != 0) {
        int* refCount2 = refObj2 + 2; // ref count at +0x08
        *refCount2 = *refCount2 - 1;
        if (*refCount2 == 0) {
            (*(void (**)(void))(*refObj2 + 8))();
        }
    }
    
    // Switch vtable to final destructor phase
    *this->vtablePtr = &PTR_LAB_00e42de4;
    
    // Clear the linked list of 12-byte nodes starting at head (+0x04)
    Node* currentNode = (Node*)this->listHead; // +0x04
    while (currentNode != 0) {
        Node* nextNode = (Node*)currentNode->next; // offset +0x08
        currentNode->field0 = 0; // +0x00
        currentNode->field4 = 0; // +0x04
        currentNode->next = 0;   // +0x08
        currentNode = nextNode;
    }
    return;
}
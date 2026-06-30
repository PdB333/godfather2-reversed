// FUNC_NAME: ObjectList::processAll

struct ListNode {
    void* data; // +0x00: pointer to associated object
    // Unknown fields at +0x04 to +0x0C (may be padding or additional data)
    ListNode** nextRef; // +0x10: pointer to a pointer that holds the address of the next node
};

struct ListHead {
    // Unknown fields (not used directly)
    ListNode** headRef; // +0x10: pointer to a pointer that holds the address of the first node
};

struct ObjectList {
    int active; // +0x00: non‑zero enables processing
    ListHead* listHead; // +0x04: pointer to the list head structure
};

// Forward declarations of called functions
int processObject(void** objPtr);   // FUN_004986e0 – returns an integer (possibly a pointer offset)
void cleanupObject(void* ptr);      // FUN_00497ba0 – performs cleanup on the given pointer

void ObjectList::processAll() {
    if (this->active == 0) {
        return;
    }

    ListNode* current = nullptr;
    if (this->listHead != nullptr) {
        // Dereference headRef to get the first node
        current = *(this->listHead->headRef);
    }

    while (current != nullptr) {
        // Extract the object pointer from the current node
        void* obj = current->data;
        int result = processObject(&obj); // result may be a pointer or an offset

        if (result != 0 && (result + 8) != 0) {
            cleanupObject((void*)(result + 8));
        }

        // Advance to the next node using the double indirection at offset 0x10
        current = *((ListNode**)(*(int*)((char*)current + 16)));
    }
}
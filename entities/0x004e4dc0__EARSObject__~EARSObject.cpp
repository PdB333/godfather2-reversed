// FUNC_NAME: EARSObject::~EARSObject
// Destructor: sets sentinel vtable, unlinks from global active list, and optionally deallocates memory.
// Global list manager is at fixed offset (DAT_01206880 + 0x14). This function removes the object from a doubly linked list
// whose node pointers are at offsets +0x10 (next) and +0x14 (prev).

class EARSObject {
public:
    void* vtable;                // +0x00: virtual function table
    // ... other members ...
    void* listNodeNext;          // +0x10: pointer to next node in the global active list
    void* listNodePrev;          // +0x14: pointer to previous node in the global active list
};

// External memory deallocation function (likely operator delete)
extern void* operatorDelete(EARSObject* ptr);

// Global list head pointer (located at DAT_01206880 + 0x14)
// This points to a pointer to the head node of the active object list.
extern int* g_listHead;  // Actually *(DAT_01206880 + 0x14) is an int**; simplified for readability

EARSObject* __thiscall EARSObject::~EARSObject(EARSObject* this, uint8_t deallocFlag) {
    // Set vtable to a sentinel / "destroyed" vtable
    this->vtable = reinterpret_cast<void*>(0x00e37110);  // PTR_FUN_00e37110

    // If the object is currently linked in the global list, unlink it.
    if (this->listNodeNext != nullptr) {
        // Get pointer to the list head storage location
        int* listPtr = reinterpret_cast<int*>(DAT_01206880 + 0x14);  // piVar2
        // The list head is a pointer to a node; we treat its contents as a pointer to a pointer for vtable assignment
        // Set the vtable of the node pointed to by the current head to a sentinel value.
        *reinterpret_cast<void***>(*listPtr) = reinterpret_cast<void**>(0x01123be8); // PTR_LAB_01123be8
        // Advance the list pointer by 4 bytes (to the next field of the head node)
        *listPtr += 1;  // Skip over first pointer (vtable)
        // Store this object's next pointer into the head's next field
        *reinterpret_cast<int*>(*listPtr) = reinterpret_cast<int>(this->listNodeNext);
        // Advance again to the prev field of the head node
        *listPtr += 1;
        // Store this object's prev pointer into the head's prev field
        *reinterpret_cast<int*>(*listPtr) = reinterpret_cast<int>(this->listNodePrev);
        // Reset the object's list pointers
        this->listNodeNext = nullptr;
        this->listNodePrev = nullptr;
    }
    // Note: The original code also set param_1[5] (listNodePrev) to 0 after the if block,
    // but that is already covered above.

    // If the low bit of deallocFlag is set, deallocate the memory.
    if ((deallocFlag & 1) != 0) {
        operatorDelete(this);  // FUN_009c8eb0
    }

    return this;
}
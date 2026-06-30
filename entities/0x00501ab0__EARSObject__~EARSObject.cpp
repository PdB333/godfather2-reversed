// FUNC_NAME: EARSObject::~EARSObject
void __thiscall EARSObject::~EARSObject(EARSObject* this) {
    // Offset +0x00: vtable pointer
    // Offset +0x14: resource pointer 1 (e.g., some allocated block)
    // Offset +0x18: resource pointer 2
    // Global DAT_012068e8 points to a memory manager structure; +0x14 is a free list head pointer

    int* pResource1 = reinterpret_cast<int*>(this->field_0x14);   // param_1[5]
    this->vtable = &PTR_FUN_00e37e0c;     // Set base vtable

    if (pResource1 != nullptr) {
        // Free resource 1 via custom allocator (push onto free list)
        int** ppListHead = reinterpret_cast<int**>(DAT_012068e8 + 0x14); // address of list head
        *ppListHead = reinterpret_cast<int*>(&PTR_LAB_01124ba8);       // store marker vtable
        (*ppListHead)++;                                                // advance list pointer
        **ppListHead = reinterpret_cast<int>(pResource1);               // store resource address
        (*ppListHead)++;                                                // advance again
        this->field_0x14 = 0;                                           // clear pointer
    }

    int* pResource2 = reinterpret_cast<int*>(this->field_0x18);   // param_1[6]
    if (pResource2 != nullptr) {
        int** ppListHead = reinterpret_cast<int**>(DAT_012068e8 + 0x14);
        *ppListHead = reinterpret_cast<int*>(&PTR_LAB_01124ba8);
        (*ppListHead)++;
        **ppListHead = reinterpret_cast<int>(pResource2);
        (*ppListHead)++;
        this->field_0x18 = 0;
    }

    this->vtable = &PTR_LAB_00e37304;     // Switch to final vtable (post-destruction)
}
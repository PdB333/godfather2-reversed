// FUNC_NAME: EARSObject::~EARSObject

void __fastcall EARSObject::~EARSObject(EARSObject* this)
{
    // Set vtable to base class (or sentinel) for first stage of destruction
    this->vtable = &BASE_VTABLE_0; // PTR_FUN_00e37d00

    // Check if resource handle at offset 0x44 is valid, release if so
    if (this->m_resourceHandle != 0) { // offset +0x44
        ResourceManager::release(1); // FUN_004eba30(1)
    }

    // Set vtable to another base (likely derived's base after cleanup)
    this->vtable = &BASE_VTABLE_1; // PTR_FUN_00e37110

    // Access global object list pointer (DAT_01206880 + 0x14)
    int* listPtr = (int*)(DAT_01206880 + 0x14); // offset to list head pointer

    // If the object has a next pointer (offset +0x10), remove from linked list
    if (this->m_next != 0) { // param_1[4] at offset +0x10
        // Insert sentinel at current list head
        **(undefined4**)listPtr = &LIST_SENTINEL; // PTR_LAB_01123be8
        // Advance list head by 4 bytes
        *listPtr = *listPtr + 4;
        // Store the object's next pointer into the advanced position
        *(int*)*listPtr = this->m_next;
        // Advance list head again
        *listPtr = *listPtr + 4;
        // Clear the object's next and previous (offset +0x10 and +0x14)
        this->m_next = 0;
        this->m_prev = 0;
    }
    return;
}
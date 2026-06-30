// FUNC_NAME: GameManager::~GameManager
void __fastcall GameManager::~GameManager(void* this) // 0x00453a70
{
    int* it;
    int* child;
    int* obj;

    // Set vtable to destructor vtable (likely to mark as destroyed)
    *(int**)this = &PTR_DTOR_VTABLE_00e31890; // +0x00 vtable
    *(int**)((char*)this + 4) = &PTR_DTOR_LABEL_00e31898; // +0x04

    // Begin cleanup sequence (probably lock or notify)
    FUN_00453f70();

    // Iterate through child linked list at offset 0x20
    it = *(int**)((char*)this + 0x20); // +0x20 m_pChildrenHead
    while (it != 0) {
        // Check if child is still active (bit 1 of flag at +0x30)
        if (((*(uint*)((char*)it + 0x30) >> 1) & 1) == 0) {
            // If child has a callback object at +0x40, call its function at vtable+0x34
            obj = *(int**)((char*)it + 0x40);
            if (obj != 0) {
                (*(void (**)(void))(*obj + 0x34))();
            }
            // Call additional cleanup function
            FUN_00454030();
        }
        // Move to next child (next pointer at +0x34)
        it = *(int**)((char*)it + 0x34);
    }

    // Another cleanup step
    FUN_00453f70();

    // Destroy global static object (DAT_01206940)
    FUN_004086d0(&DAT_01206940);

    // Handle m_pObject1A at offset 0x68
    obj = *(int**)((char*)this + 0x68); // +0x68
    if (obj != 0) {
        // Set its vtable to a cleanup vtable
        *(int**)obj = &PTR_DTOR_ALT_VTABLE_00e31850;
        // If it has a valid pointer at +0x04, call its function with arg 1
        if (*(int*)((char*)obj + 4) != 0) {
            (*(void (**)(int))(**(int**)*(int*)((char*)obj + 4)))(1);
        }
        // Free the object memory
        FUN_009c8eb0(obj);
    }

    // Handle m_pChildObject at offset 0x14 (calls its destructor)
    obj = *(int**)((char*)this + 0x14); // +0x14
    if (obj != 0) {
        (*(void (**)(int))(*obj + 4))(1); // Destructor (vtable+4)
    }

    // Remove this object from a global linked list (DAT_01218014 is head node)
    if (DAT_01218014 != 0) {
        if (DAT_01218018 == 0) {
            *(int*)(DAT_01218014 + 4) = DAT_0121801c;
        } else {
            *(int*)(DAT_01218018 + 8) = DAT_0121801c;
        }
        if (DAT_0121801c != 0) {
            *(int*)(DAT_0121801c + 4) = DAT_01218018;
        }
    }
    DAT_01218014 = 0; // Clear global head

    // Destroy objects at offsets 0x5C and 0x58
    obj = *(int**)((char*)this + 0x5C); // +0x5C
    if (obj != 0) {
        (*(void (**)(int))(*obj + 4))(1);
    }
    obj = *(int**)((char*)this + 0x58); // +0x58
    if (obj != 0) {
        (*(void (**)(int))(*obj + 4))(1);
    }

    // Free various buffer allocations
    if (*(int*)((char*)this + 0x4C) != 0) { // +0x4C
        FUN_009c8f10(*(int*)((char*)this + 0x4C));
    }
    if (*(int*)((char*)this + 0x40) != 0) { // +0x40
        FUN_009c8f10(*(int*)((char*)this + 0x40));
    }
    if (*(int*)((char*)this + 0x34) != 0) { // +0x34
        FUN_009c8f10(*(int*)((char*)this + 0x34));
    }
    if (*(int*)((char*)this + 0x28) != 0) { // +0x28
        FUN_009c8f10(*(int*)((char*)this + 0x28));
    }

    // Unlink m_pChildObject from its doubly linked list using stored prev/next pointers
    obj = *(int**)((char*)this + 0x14); // +0x14 (same as before, after destructor call)
    if (obj != 0) {
        int* prev = *(int**)((char*)this + 0x18); // +0x18
        int* next = *(int**)((char*)this + 0x1C); // +0x1C
        if (prev == 0) {
            *(int**)((char*)obj + 4) = next;
        } else {
            *(int**)((char*)prev + 8) = next;
        }
        if (next != 0) {
            *(int**)((char*)next + 4) = prev;
        }
    }

    // Final cleanup steps
    FUN_004083d0();
    *(int**)this = &PTR_LAB_00e318a8; // Overwrite vtable to a final label
    DAT_0122344c = 0; // Clear global flag
    return;
}
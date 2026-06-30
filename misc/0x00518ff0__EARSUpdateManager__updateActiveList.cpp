// FUNC_NAME: EARSUpdateManager::updateActiveList
// Address: 0x00518ff0
// Iterates over an intrusive linked list of updatable objects (head at this+0x10),
// calling virtual method at vtable+0xC for objects whose flags & 3 == 0.

// Forward declaration of the object type embedded in the list
struct UpdateableObject {
    int** vtable;                    // +0x00
    unsigned char flags;             // +0x04 (low 2 bits control update eligibility)
    // ... other members ...
    UpdateableObject* next;          // +0xC4 (piVar1[0x31])
};

// __thiscall
void FUN_00518ff0(void* param_1)
{
    // Get head of list from manager's offset 0x10
    UpdateableObject* pObj = *(UpdateableObject**)((char*)this + 0x10);

    while (pObj != nullptr) {
        // Only update if the low 2 bits of the flags byte are clear
        if ((pObj->flags & 3) == 0) {
            // Call virtual method at vtable index 3 (offset 0xC)
            // Signature: void __thiscall method(void* param_1)
            typedef void (__thiscall *UpdateFunc)(void*);
            ((UpdateFunc)pObj->vtable[3])(param_1);
        }
        pObj = pObj->next; // traverse via embedded next pointer at +0xC4
    }
}
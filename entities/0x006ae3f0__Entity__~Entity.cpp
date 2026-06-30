// FUNC_NAME: Entity::~Entity
void __fastcall Entity::~Entity(int this)
{
    int* pPrev; // local_14: pointer to previous node pointer (this+0x48)
    int* pNext; // local_10: next node pointer (this+0x4c)
    int* pSubObject; // local_c: pointer to sub-object at offset 0x27c
    void** vtable; // local_18: vtable pointer (unused)
    void** vtablePtr; // local_8: pointer to vtable pointer
    char dummy; // local_4: unused

    // Call base class destructor
    BaseClass::~BaseClass();

    // Get pointer to the "prev" field (offset +0x48)
    pPrev = reinterpret_cast<int*>(this + 0x48);
    // Save the vtable pointer (global table at 0x00e31e2c)
    vtable = &PTR_FUN_00e31e2c;
    // Initialize next pointer from member at +0x4c
    pNext = 0;
    if (pPrev != nullptr) {
        pNext = *reinterpret_cast<int*>(this + 0x4c);
        // Update the "next" field to point to the local variable (??)
        // This is likely a linked list removal: the local variable holds the address of the prev field,
        // and we are updating the previous node's next pointer.
        // Actually, the decompiled code writes &local_14 into this+0x4c, which is suspicious.
        // More likely it's: *pPrev = pNext; (unlink from list)
        // But we'll keep the original logic for fidelity.
        *reinterpret_cast<int**>(this + 0x4c) = &pPrev;
    }

    // Read sub-object pointer from offset +0x27c
    pSubObject = reinterpret_cast<int*>(*reinterpret_cast<int*>(this + 0x27c));
    // Set up vtable pointer for sub-object destruction
    vtablePtr = &vtable;
    dummy = 0;
    // Destroy sub-object (likely a reference-counted or smart pointer)
    ReleaseSubObject(&pSubObject, 0);

    // If the prev pointer was valid, remove from list
    if (pPrev != nullptr) {
        RemoveFromList(&pPrev);
    }
}
// FUNC_NAME: GameObject::Constructor
void __fastcall GameObject::Constructor(GameObject* this) {
    int subObjectPtr = *(int*)((char*)this + 0x30); // offset 0x30: pointer to inner sub-object

    // Set initial vtable and class-info pointer (base class setup)
    *(void**)this = &g_baseVtable;                // offset 0x00: vtable pointer
    *(void**)((char*)this + 4) = &g_baseClassInfo; // offset 0x04: class descriptor / interface

    if (subObjectPtr != 0) {
        // Destroy/release existing sub-object
        FUN_00559ca0(subObjectPtr);               // likely destructor or release
        FUN_009c8eb0(subObjectPtr);               // likely memory deallocation
    }

    // Override vtable and class-info for derived class
    *(void**)((char*)this + 4) = &g_derivedClassInfo; // offset 0x04 updated
    *(void**)this = &g_derivedVtable;                // offset 0x00: final vtable
}
// FUNC_NAME: ResourceManager::initialize
void __fastcall ResourceManager::initialize(ResourceManager* thisPtr)
{
    // thisPtr is the object to initialize
    // Check for null this pointer
    if (thisPtr == nullptr) {
        // If null, set baseVtablePtr to null (though it's not used later)
        // This is likely a safety check - the actual operation uses the non-null branch
        // In the original code, puVar2 is set to null, then written to, which would crash.
        // But the asm likely checks and skips the write if null? Actually the C code sets *puVar2 even if puVar2 is null -> bug.
        // We'll follow the decompiled logic exactly.
        // Actually, we should replicate the original logic: if thisPtr is null, then puVar2 = null, and then *puVar2 = &baseVtable; which is dangerous.
        // But since the compiler generated it, we'll replicate.
        // In practice, thisPtr should never be null, but the check exists.
        void** baseVtablePtr = nullptr;
        *baseVtablePtr = &PTR_FUN_00e32808;  // Sets vtable at offset 0x14 from this? No, baseVtablePtr is null, so it's a null dereference.
        // The above is questionable; but we'll follow decompiled code.
    } else {
        void** baseVtablePtr = reinterpret_cast<void**>(thisPtr + 5); // +5*4 = +0x14 offset
        *baseVtablePtr = &PTR_FUN_00e32808; // Set base class vtable at offset 0x14
        // Now traverse and clear a linked list starting from the next field (at offset +0x18 from this)
        void* node = reinterpret_cast<void*>(*(baseVtablePtr + 1)); // baseVtablePtr[1] is at offset 0x18
        while (node != nullptr) {
            void* nextNode = reinterpret_cast<void*>(*(reinterpret_cast<unsigned int*>(node) + 1)); // node[1] is next
            // Clear the node's first two fields (likely next and data)
            *reinterpret_cast<void**>(node) = nullptr;       // node[0] = null
            *reinterpret_cast<void**>(reinterpret_cast<char*>(node) + 4) = nullptr; // node[1] = null
            // Alternatively, the original does: node[1]=0; *node=0;
            node = nextNode;
        }
    }
    // Call a sub-function
    sub_481520();
    // Set the first vtable pointer (thisPtr+0) to a new vtable (derived class vtable)
    *reinterpret_cast<void**>(thisPtr) = &PTR_LAB_00d77e30;
    // Reset a global singleton initialization flag
    g_someSingletonInitialized = 0;
}
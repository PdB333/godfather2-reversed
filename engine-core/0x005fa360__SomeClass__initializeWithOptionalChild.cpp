// FUNC_NAME: SomeClass::initializeWithOptionalChild

void SomeClass::initializeWithOptionalChild(void* this, int param_2) {
    // vtable offsets:
    // +0x00: unknown (not used here)
    // +0x04: setChild(?, int) – called with (param_2, 0) when param_2 is non-null
    // +0x08: preInit() – called first
    // +0x0C: finalize() – called at end

    // Store 'this' for later use (decompiler artifact for EDI register)
    void* localThis = this;

    // Call the virtual pre-initialization routine
    (*(void (**)(void))(*((int*)this) + 8))();  // vtable[2] call

    if (param_2 != 0) {
        // Create or allocate a child object using param_2 as input
        int childObj = FUN_004265d0(param_2, localThis); // likely allocateChild(param_2, this)
        // Store the child object at offset +4 (e.g., m_child pointer)
        *((int*)localThis + 1) = childObj;

        // Attach the child with a flag of 0
        (*(void (**)(int, int))(*((int*)this) + 4))(param_2, 0);  // vtable[1] call: setChild(param_2, 0)

        // Finalize initialization
        (*(void (**)(void))(*((int*)this) + 12))();  // vtable[3] call
        return;
    }

    // No child: set child pointer to null
    *((int*)localThis + 1) = 0;

    // Finalize initialization
    (*(void (**)(void))(*((int*)this) + 12))();  // vtable[3] call
    return;
}
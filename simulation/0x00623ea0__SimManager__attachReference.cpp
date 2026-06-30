// FUNC_NAME: SimManager::attachReference
// Address: 0x00623ea0
// This function attaches an external reference (param_2) to a manager object (this).
// It allocates or retrieves a new internal object, stores backpointers, and calls
// virtual lifecycle methods. Offsets: +0x0C = backpointer to manager, +0x10 = reference handle.

void __thiscall SimManager::attachReference(int param_2) {
    // Save the manager pointer (this) for later use
    int* manager = this;

    // Call virtual function at vtable offset 0x8 (likely allocateObject or create)
    // This returns a pointer to a newly allocated internal object.
    int* newObject = (int*)this->vtable[2](this);

    int refValue;
    if (param_2 == 0) {
        refValue = 0;
    } else {
        // Compute reference value from external param and manager
        refValue = someFunction1(param_2, (int)manager);  // FUN_004265d0
    }
    // Register or initialize using the computed reference
    someFunction2((int)manager, refValue);                // FUN_006241d0

    // Store a backpointer to the manager in the new object at +0x0C
    *(int**)(newObject + 0x0C) = manager;

    // Call the same virtual function again (possibly a different overload with no args)
    this->vtable[2]();

    if (param_2 != 0) {
        // Recompute reference using the stored backpointer
        refValue = someFunction1(param_2, *(int*)(newObject + 0x0C));
        // Store the final reference handle at +0x10
        *(int*)(newObject + 0x10) = refValue;
        // Call vtable[1] (offset +0x4) with two arguments (param_2, 0)
        this->vtable[1](param_2, 0);
        // Call vtable[3] (offset +0xC) with no arguments
        this->vtable[3]();
    } else {
        // No external reference: set handle to 0
        *(int*)(newObject + 0x10) = 0;
        // Call vtable[3] (offset +0xC) with no arguments
        this->vtable[3]();
    }
}
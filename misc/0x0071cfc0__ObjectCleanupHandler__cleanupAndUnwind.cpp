// FUNC_NAME: ObjectCleanupHandler::cleanupAndUnwind

// Reconstructed from decompilation of FUN_0071cfc0 (x86, __thiscall)
// This function appears to be a compiler-generated handler for object cleanup during stack unwinding.
// It checks if an object's vtable matches an expected vtable stored in `this` at offset +0x14,
// and if so, calls the object's virtual destructor (with flag 0 = no delete) and a global cleanup.
// It then saves the current frame pointer into the output parameter and returns it,
// presumably to set up a longjmp target for exception handling.

undefined4 * __thiscall ObjectCleanupHandler::cleanupAndUnwind(int this, undefined4 *objectPtrPtr) {
    int *cleanupFlagPtr;
    undefined4 *objectVtable; // first pointer in the object (vtable)
    undefined4 savedFramePointer;

    objectVtable = *(undefined4 **)*objectPtrPtr;          // get object vtable
    cleanupFlagPtr = (int *)(this + 0x14);                 // +0x14: stored expected vtable pointer
    if ((objectVtable == *(undefined4 **)(this + 0x14)) && (*cleanupFlagPtr != 0)) {
        // If the object's vtable matches the expected one and it's not null,
        // call the object's virtual destructor with flag=0 (only destruct, no delete)
        // and then clear the stored vtable pointer.
        FUN_004daf90(cleanupFlagPtr);                      // likely destroys the object or frees memory
        *cleanupFlagPtr = 0;                               // clear the stored vtable
    }

    // Call the first virtual function on the object (typically scalar deleting destructor) with flag 0
    (**(code **)*objectVtable)(0);
    
    // Call a class-specific global cleanup function (second entry in a static vtable)
    (**(code **)(*DAT_0112ad34 + 4))(objectVtable, 0);     // DAT_0112ad34: global vtable for cleanup
    
    // Set up the "previous frame" pointer for exception handling
    FUN_0071cda0(&savedFramePointer, objectPtrPtr);        // saves current stack frame into objectPtrPtr?
    
    *objectPtrPtr = savedFramePointer;                     // store old EBP into output
    return objectPtrPtr;                                   // return pointer to the stored frame
}
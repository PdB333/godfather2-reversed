// FUNC_NAME: SomeComponent::updateState
void SomeComponent::updateState()
{
    // Call common initialization routine
    FUN_005a72f0();

    // Check if the 'initialized' flag at offset +0x02 is zero
    if ((*(short *)(this + 2) == 0) && 
        // Try to allocate/create a new object (returns non-zero on success)
        (void *newObject = FUN_005a76c0(), newObject != nullptr))
    {
        // Call a setup routine for the new object
        FUN_005ba710();

        // Invoke a global function pointer (likely a memory allocator or audio system) 
        // with the new object and a size/ID of 0x4c
        (*DAT_0119caf8)(newObject, 0x4c);
    }
}
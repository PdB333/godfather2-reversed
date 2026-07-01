// FUNC_NAME: Fiber::resumeContext
void __fastcall Fiber::resumeContext(int this) {
    // this is a Fiber object (likely from EARS::Fiber)
    int fiberData = *(int *)(this + 0x5c); // +0x5c: pointer to fiber data block
    if (fiberData != 0) {
        // Check if this fiber is being entered for the first time (state flag)
        if (*(int *)(fiberData + 0x18) == 0) {
            // First entry: save the current execution context onto a stack
            uint *savedState = 0;
            if (fiberData != 0) {
                // Save the previous context pointer (next in linked list)
                savedState = *(uint *)(fiberData + 4);
                // Set the fiber's context pointer to the local variable (new context)
                *(int **)(fiberData + 4) = &savedState;
            }
            // Push the fiber data onto the context stack
            int prevFiber = fiberData;
            // Call the low-level yield function that suspends this fiber and switches to the next
            FUN_00823f80(); // likely Fiber::yield() or context switch
        }
        // Update the sub-context object (e.g., a thread or coroutine slot)
        int *subContext = *(int **)(fiberData + 0x1c);
        subContext[3] = *(int *)(this + 100); // +0x64: some value to set
        subContext[4] |= 1; // set bit 0 of flags
        subContext[2] = *(int *)(fiberData + 0x20); // copy another field

        // Prepare a jump buffer or context address for the next switch
        uint *jumpBuffer = (uint *)0x8242c2; // constant, likely a global or function pointer
        uint savedState = (uint)jumpBuffer; // store it
        FUN_004df5c0(); // invoke a function that uses the savedState (maybe longjmp or resume)

        // Clear the "first time" flag on the fiber data
        *(uint *)(fiberData + 0x24) &= 0xfffffffe; // clear bit 0
    }
}
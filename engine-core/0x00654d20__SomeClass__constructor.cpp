// FUNC_NAME: SomeClass::constructor
// Address: 0x00654d20
// Role: Constructor that calls the actual init function and conditionally deletes the object if the allocation flag is set.

undefined4 __thiscall SomeClass::constructor(SomeClass* this, byte allocationFlag)
{
    // Call the actual initialization routine
    SomeClass::init(this);
    
    // If the object was heap-allocated (flag bit 0 set), delete it on failure? 
    // Actually, this pattern is often used for placement new: if the flag indicates that the object was allocated with new,
    // then if construction fails, it deletes itself. But here it always calls init first, then conditionally deletes.
    // This might be a constructor that handles both stack and heap allocation.
    if ((allocationFlag & 1) != 0) {
        // Free the memory (operator delete or custom deallocator)
        FUN_009c8eb0(this);
    }
    return this;
}
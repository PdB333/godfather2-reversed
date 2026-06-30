// FUNC_NAME: EARSObjectConstructor
// Function at 0x006bbeb0: Base constructor with optional memory initialization (size 0x130)
undefined4 __thiscall EARSObjectConstructor(undefined4 this, byte flags)
{
    // Call base class constructor
    BaseConstructor();
    if ((flags & 1) != 0)
    {
        // If flags bit 0 is set, initialize object memory (size 0x130 bytes)
        InitializeObjectMemory(this, 0x130);
    }
    return this;
}
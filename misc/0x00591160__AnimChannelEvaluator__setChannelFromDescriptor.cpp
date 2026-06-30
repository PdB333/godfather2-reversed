// FUNC_NAME: AnimChannelEvaluator::setChannelFromDescriptor
void __fastcall AnimChannelEvaluator::setChannelFromDescriptor(int unusedThis, float value)
{
    // This function uses register-passed pointers: eax = descriptor, esi = arrayHandle
    // descriptor: byte at offset 0 = channel type (masked 0x3f), short at offset 2 = array index
    // arrayHandle: +0 = float* array, +4 = uint32 array size
    
    // Access registers via inline assembly or compiler-specific extensions
    // For portability, we define the function as taking the registers as parameters
    // but Ghidra shows they are passed in eax/esi.
    // In reality, this is a custom calling convention used internally.
    
    void* descriptor; // in eax
    int* arrayHandle; // in esi
    // These would be set by the caller
    
    float result = g_defaultChannelValue; // DAT_00e2b1a4
    
    uint8 channelType = *(uint8*)descriptor & 0x3F;
    if (channelType < 0x23)
    {
        // Function table at DAT_0103b050 with 0x23 entries
        EvaluatorFunc evaluator = g_evaluatorTable[channelType];
        result = (float)evaluator(value);
    }
    
    int16 index = *(int16*)((uint8*)descriptor + 2);
    if ((uint32)arrayHandle[1] <= (uint32)index)
    {
        uint32 dummyErrorCode = 0;
        handleOutOfBoundsError(&dummyErrorCode); // FUN_00591c00
    }
    
    // Write result to the array
    ((float*)arrayHandle[0])[index] = result;
}
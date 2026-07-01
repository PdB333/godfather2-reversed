// FUNC_NAME: StackAllocator::allocateBlock
void __thiscall StackAllocator::allocateBlock(void* param_2)
{
    int* stackPtr = *(int**)(this + 0x18); // +0x18: current stack pointer
    int firstVal = *stackPtr;                // index or size
    int secondVal = stackPtr[1];             // alignment or size
    stackPtr += 2;                           // consume metadata
    *(int**)(this + 0x18) = stackPtr;

    // Align current position to a multiple of secondVal (must be a power of two)
    uint alignedBase = ((uint)stackPtr + secondVal + 7) & ~(secondVal - 1);

    // Compute object address: firstVal * 0x30 offset from aligned base
    int* objAddr = (int*)(firstVal * 0x30 + alignedBase);
    *(int**)(this + 0x18) = objAddr;

    int firstWord = *objAddr;                // vtable or type identifier
    *(int**)(this + 0x18) = objAddr + 1;     // advance past first word

    // Build 64-bit argument: high = firstVal, low = alignedBase if firstVal != 0 else 0
    long long combined = ((long long)firstVal << 32) | ((firstVal != 0) ? alignedBase : 0);

    // Call the function with (combined, secondVal, firstWord)
    ((void(__thiscall*)(long long, int, int))(*(int*)param_2))(this, combined, secondVal, firstWord);
}
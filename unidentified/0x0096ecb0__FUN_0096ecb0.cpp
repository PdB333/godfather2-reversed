// FUNC_NAME: UnknownClass::~UnknownClass (destructor with deallocation flag)
int __thiscall UnknownClass::~UnknownClass(void* thisPtr, byte deallocFlag)
{
    // Call base destructor (likely at 0x96abb0)
    BaseClass::~BaseClass(thisPtr);

    // Release reference on resource at offset +0x6c
    releaseRef(*(void**)((char*)thisPtr + 0x6c));

    // If sub-object at +0x58 exists, release its sub-resource (+8) and destroy it
    void* subObj = *(void**)((char*)thisPtr + 0x58);
    if (subObj != (void*)0x0)
    {
        releaseRef(*(void**)((char*)subObj + 8)); // Sub-object resource at +0x08
        destroySubObject(subObj);                  // Called via 0x9c8eb0
    }

    // Release reference on resource at offset +0x4c
    if (*(void**)((char*)thisPtr + 0x4c) != (void*)0x0)
    {
        releaseRef(*(void**)((char*)thisPtr + 0x4c));
    }

    // Final engine cleanup (likely frees small allocations or resets state)
    finalCleanup(); // FUN_005c16e0

    // If deallocation flag (bit 0) is set, free the memory
    if ((deallocFlag & 1) != 0)
    {
        operatorDelete(thisPtr); // FUN_005c4480
    }

    return (int)thisPtr;
}
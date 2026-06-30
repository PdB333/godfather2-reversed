// FUNC_NAME: EARSObject::destroy
int __thiscall EARSObject::destroy(void* thisPtr, byte deallocateFlag)
{
    // +0x0C: pointer to child/owned object that needs cleanup
    void* childObj = *(void**)((char*)thisPtr + 0x0C);
    if (childObj != 0) {
        // +0x18: function pointer to cleanup procedure (often destructor or release)
        void (__thiscall* cleanupFunc)(void*) = *(void (__thiscall**)(void*))((char*)thisPtr + 0x18);
        cleanupFunc(childObj);
    }
    // If bit 0 of flag is set, deallocate memory for this object
    if ((deallocateFlag & 1) != 0) {
        FUN_009c8eb0(thisPtr); // likely operator delete or custom deallocation
    }
    return (int)thisPtr; // return self for chaining
}
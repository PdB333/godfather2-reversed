// FUNC_NAME: ReleaseFunctionPointerArray
void __fastcall ReleaseFunctionPointerArray(int* param_1)
{
    // param_1 points to a struct:
    // +0x00: pointer to array of function pointers (each 0x20 bytes? but we treat as void*)
    // +0x04: count (size - 1, i.e., last index)
    int count = param_1[1];
    void** array = (void**)(*param_1);

    // Call each function pointer with argument 0, from last to first
    while (count >= 0)
    {
        // Each slot is a function pointer at offset count * 0x20? 
        // Actually observed loop uses index * 0x20, indicating each element is 0x20 bytes
        // We'll cast the function pointer type accordingly
        typedef void (__cdecl *CallbackFunc)(int);
        CallbackFunc func = *(CallbackFunc*)((char*)array + count * 0x20);
        func(0);
        count--;
    }

    // Free the array memory
    if (array != nullptr)
    {
        FUN_009c8f10(array); // Deallocation function (likely operator delete or free)
    }
}
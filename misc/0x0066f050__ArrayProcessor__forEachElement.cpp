// FUNC_NAME: ArrayProcessor::forEachElement
void __thiscall ArrayProcessor::forEachElement(int *thisPtr, int *array, int count, int extraParam)
{
    // Calls virtual method at vtable offset 0x10 (index 4) for each pointer in the array
    // Virtual method signature: void (void *element, int extraParam, int zero)
    for (int i = 0; i < count; ++i)
    {
        void *element = (void *)array[i];
        // vtable lookup and call
        (**(void (__thiscall **)(void *, int, int))(*thisPtr + 0x10))(element, extraParam, 0);
    }
}
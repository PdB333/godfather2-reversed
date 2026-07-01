// FUNC_NAME: ObjectArray::destroyAll
// Function at 0x0091f7d0: Destroys all objects in an array and frees the buffer.
// The array stores elements of size 0x28, each containing an object pointer at +0x04
// and a destructor function pointer at +0x10.
void __thiscall ObjectArray::destroyAll(int* thisPtr)
{
    int count = thisPtr[1] - 1; // Number of elements (stored at offset +0x04)
    if (count >= 0)
    {
        int elementOffset = count * 0x28; // Offset from buffer start to current element
        do
        {
            // Get object pointer from element (offset +0x04)
            int* objPtr = *(int**)(elementOffset + 4 + thisPtr[0]);
            if (objPtr != nullptr)
            {
                // Call destructor function pointer from element (offset +0x10)
                // The destructor is a function that takes the object pointer as argument
                void (*destructor)(int*) = *(void (**)(int*))(elementOffset + thisPtr[0] + 0x10);
                destructor(objPtr);
            }
            count--;
            elementOffset -= 0x28;
        } while (count >= 0);
    }

    // Free the buffer (pointer at offset +0x00)
    if (thisPtr[0] != 0)
    {
        FUN_009c8f10(thisPtr[0]); // Deallocation function (likely operator delete or custom free)
    }
}
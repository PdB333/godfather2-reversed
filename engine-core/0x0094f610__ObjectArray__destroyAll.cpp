// FUNC_NAME: ObjectArray::destroyAll

void __fastcall ObjectArray::destroyAll(int *thisPtr)
{
    int *arrayStart = *thisPtr; // Dereference this to get array pointer (member)
    if (arrayStart != 0) {
        int count = *(int *)(arrayStart - 4); // Count stored in 4-byte header before array
        int *elementIter = arrayStart + count * 0x14; // Past last element

        // Iterate backwards over elements (each 0x14 bytes)
        for (int i = count - 1; i >= 0; i--) {
            elementIter -= 0x14; // Move to current element
            int *objectPtr = *(int **)elementIter; // +0x00: pointer to object
            if (objectPtr != 0) {
                // +0x0C: function pointer (destructor)
                typedef void (*DestructorFunc)(int *);
                DestructorFunc destructor = *(DestructorFunc *)(elementIter + 12);
                destructor(objectPtr);
            }
        }

        // Free the entire allocation (header + array)
        FUN_009c8f10(arrayStart - 4); // deallocateArrayBlock
    }
}
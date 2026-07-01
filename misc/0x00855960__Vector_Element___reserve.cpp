// FUNC_NAME: Vector<Element>::reserve
void __thiscall Vector<Element>::reserve(int* thisPtr, uint newCapacity) {
    if ((uint)thisPtr[2] < newCapacity) {
        // Allocate new array of elements (size = 0x2c per element)
        int* newData = (int*)FUN_009c8e80(newCapacity * 0x2c); // custom alloc

        if (thisPtr[0] != 0) {
            uint elemCount = thisPtr[1];
            if (elemCount != 0) {
                // Loop: move elements from old array to new
                for (uint i = 0; i < elemCount; i++) {
                    // Old element pointer (relative to old base)
                    __int64* oldElemBase = (__int64*)(thisPtr[0] + i * 0x2c);
                    // New element pointer (first 14 bytes copied raw)
                    char* newElemStart = (char*)newData + i * 0x2c + 0xd; // offset 0xd in new element

                    // Copy first 14 bytes: 2 int64 + int + 2 bytes
                    *(__int64*)(newElemStart - 0xd) = oldElemBase[0];
                    *(int*)(newElemStart - 5) = *(int*)((int*)oldElemBase + 1);
                    *(char*)(newElemStart - 1) = *((char*)oldElemBase + 0xc);
                    *(char*)(newElemStart) = *((char*)oldElemBase + 0xd);

                    // Copy the referenced object (at offset +0x10 in element)
                    int* oldRefPtr = (int*)((int*)oldElemBase + 2); // offset 0x10
                    FUN_00854270(oldRefPtr); // moves inner data to new location

                    // Release reference from old element
                    if (*oldRefPtr != 0) {
                        int* refCountPtr = (int*)(*(int*)(oldRefPtr + 1) + 4); // +4 inside ref counted object?
                        *refCountPtr = *refCountPtr - 1;
                        if (*((int**)oldRefPtr)[1] == 0) {
                            (**(code**)(*(int**)oldRefPtr + 4))(); // call destructor
                        }
                        *oldRefPtr = 0;
                    }
                }
            }
            // Free old array
            FUN_009c8f10(thisPtr[0]);
        }

        // Update members
        thisPtr[0] = (int)newData;
        thisPtr[2] = newCapacity;
    }
}
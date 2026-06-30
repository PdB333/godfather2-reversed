// FUNC_NAME: DynamicArray::operator=
// Function address: 0x0060f680
// Role: Assignment operator for a dynamic array of structures (element size 0x14, with sub-object pointer at offset +8)

extern void* allocate(int size);           // 0x009c8e80
extern void deallocate(void* ptr);         // 0x009c8f10
extern void copyElementSubObject(void* dst, void* src); // 0x006099f0 – deep-copy sub-object at element offset +8

// Dynamic array structure:
// +0 : int* data
// +4 : int size
// +8 : int capacity
// Element (0x14 bytes):
// +0 : int field0
// +4 : int field4
// +8 : void* subObject
// Remaining 12 bytes are padding/unknown

int* __thiscall DynamicArray::operator=(int* thisPtr, int* otherPtr)
{
    if (thisPtr == otherPtr) {
        return thisPtr;
    }

    int* thisData = reinterpret_cast<int*>(thisPtr[0]);
    int thisSize = thisPtr[1];
    int otherSize = otherPtr[1];
    int otherDataBase = otherPtr[0];

    // Destroy current elements
    for (int i = thisSize - 1; i >= 0; i--) {
        int* elem = reinterpret_cast<int*>(reinterpret_cast<int>(thisData) + i * 0x14);
        if (elem[2] != 0) { // subObject pointer at offset +8
            deallocate(reinterpret_cast<void*>(elem[2]));
        }
    }

    // Reallocate if capacity is insufficient
    if (thisPtr[2] < otherSize) {
        deallocate(reinterpret_cast<void*>(thisPtr[0]));
        thisPtr[2] = otherSize;
        if (otherSize == 0) {
            thisPtr[0] = 0;
        } else {
            thisPtr[0] = reinterpret_cast<int>(allocate(otherSize * 0x14));
        }
    }

    // Copy elements from other to this
    int newData = thisPtr[0];
    for (unsigned int j = 0; j < static_cast<unsigned int>(otherSize); j++) {
        int* destElem = reinterpret_cast<int*>(newData + j * 0x14);
        int* srcElem = reinterpret_cast<int*>(otherDataBase + j * 0x14);

        // Copy first two ints (8 bytes)
        destElem[0] = srcElem[0];
        destElem[1] = srcElem[1];

        // Deep-copy sub-object (at offset +8)
        copyElementSubObject(reinterpret_cast<void*>(&destElem[2]), reinterpret_cast<void*>(&srcElem[2]));
    }

    thisPtr[1] = otherSize;
    return thisPtr;
}
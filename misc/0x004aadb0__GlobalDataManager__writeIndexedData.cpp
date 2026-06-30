// FUNC_NAME: GlobalDataManager::writeIndexedData
// Address: 0x004aadb0
// Writes a value into a global data structure indexed by an offset stored at this+0x18.
// The target address is derived from thread-local storage (FS:[0x2C]) with multiple indirections.

void __thiscall GlobalDataManager::writeIndexedData(void* this, int value)
{
    int* basePtr;      // P1 from FS:[0x2C]
    int x;             // *basePtr
    int* ptr;          // (x + 8)
    int y;             // *ptr
    int index;         // this->offset_0x18
    int* target;       // final write address

    // Thread-local storage access (equivalent to __readfsdword(0x2C))
    basePtr = (int*)__readfsdword(0x2C);
    x = *basePtr;                     // First dereference
    ptr = (int*)(x + 8);              // +8 offset
    y = *ptr;                         // Second dereference
    index = *(int*)(this + 0x18);     // Index from object (offset +0x18)
    target = (int*)(y + 0x6C + index); // Base +0x6C plus index
    *target = value;                  // Write the value
}
// FUNC_NAME: CountedPointerOwner::setCountedPointer
// Address: 0x00549cf0
// Role: Assigns a new intrusive counted pointer to the member at offset 0xC0, releasing the old one.
// The counted object structure:
//   +0x00: vtable pointer (first entry is release function)
//   +0x04: short refCountFlag (non-zero if object uses reference counting)
//   +0x06: short referenceCount
// When the old pointer's reference count reaches zero, the vtable's release function is called with argument 1.

void __thiscall CountedPointerOwner::setCountedPointer(void* newPtr)
{
    void* oldPtr = *(void**)(this + 0xC0);  // old counted pointer
    if (oldPtr == newPtr) {
        return;
    }

    if (oldPtr != nullptr) {
        short* refCountFlag = (short*)((char*)oldPtr + 4);
        if (*refCountFlag != 0) {
            short* refCount = (short*)((char*)oldPtr + 6);
            *refCount -= 1;
            if (*refCount == 0) {
                // Call the first virtual function (release/destructor) with argument 1
                void** vtable = *(void***)oldPtr;
                void (*releaseFunc)(void*, int) = (void (*)(void*, int))vtable[0];
                releaseFunc(oldPtr, 1);
            }
        }
    }

    // Assign new pointer
    *(void**)(this + 0xC0) = newPtr;

    // Increment reference count on new pointer if it uses ref counting
    if (newPtr != nullptr) {
        short* refCountFlag = (short*)((char*)newPtr + 4);
        if (*refCountFlag != 0) {
            short* refCount = (short*)((char*)newPtr + 6);
            *refCount += 1;
        }
    }
}
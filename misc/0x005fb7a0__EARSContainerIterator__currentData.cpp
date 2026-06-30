// FUNC_NAME: EARSContainerIterator::currentData
// Address: 0x005fb7a0
// Role: Returns a pointer to the data at offset 8 from the current element.
// The iterator structure (passed as `this` via ecx) contains:
//   +0x00: mContainer - pointer to the container base
//   +0x04: mCurrent   - pointer to the current element
// The container has a pointer to the end at offset 0x18.
// Assertions: mContainer non-null, mCurrent not equal to end pointer.

#include <cassert>

struct EARSContainerIterator {
    void* mContainer; // +0x00
    void* mCurrent;   // +0x04

    void* currentData() {
        // Assert container pointer is valid
        if (mContainer == nullptr) {
            assert(!"Container pointer is null");
        }
        // Assert we are not past the end of the container
        void* endPtr = *reinterpret_cast<void**>(static_cast<char*>(mContainer) + 0x18);
        if (mCurrent == endPtr) {
            assert(!"Attempt to dereference past end of container");
        }
        // Return pointer to the data at offset 8 inside the current element
        return static_cast<char*>(mCurrent) + 8;
    }
};
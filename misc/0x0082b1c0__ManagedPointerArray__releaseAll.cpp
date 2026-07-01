// FUNC_NAME: ManagedPointerArray::releaseAll
// Function address: 0x0082b1c0
// This function releases all elements in an array of smart pointers, then frees the array itself.
// It first sets the vtable to a cleanup vtable (PTR_FUN_00d7381c), then iterates over the array
// calling the first vtable entry of each object with argument 1 (presumably a release method).
// Finally, it frees the array memory via FUN_009c8f10 (likely operator delete[] or custom dealloc).

class ManagedPointerArray {
public:
    uint* vtable;      // +0x00
    int field_0x04;    // +0x04 (unused in this function)
    void** array;      // +0x08
    uint count;        // +0x0C

    void releaseAll() {
        // Switch to cleanup vtable (likely a "null" or empty vtable to avoid double deletion)
        vtable = (uint*)&PTR_FUN_00d7381c;

        // Call release() on each non-null object (first vtable entry, argument = 1)
        if (count != 0) {
            for (uint i = 0; i < count; i++) {
                void* obj = array[i];
                if (obj != nullptr) {
                    // Call function at vtable[0] with parameter 1 (e.g., Release(1))
                    (*(void(__thiscall**)(int))(*static_cast<uint*>(obj)))(1);
                }
            }
        }

        // Free the array memory
        if (array != nullptr) {
            FUN_009c8f10(array); // custom deallocation
        }
    }
};
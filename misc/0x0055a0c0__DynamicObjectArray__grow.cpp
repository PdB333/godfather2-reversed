// FUNC_NAME: DynamicObjectArray::grow
void DynamicObjectArray::grow(uint newCapacity)
{
    // Offset layout:
    // +0x00: array pointer (int*)
    // +0x04: count (int)
    // +0x08: capacity (int)
    // +0x0C: allocator pointer (AllocatorBase*)
    // +0x10: allocator vtable (int**)

    if (newCapacity <= (uint)this->capacity) {
        return;
    }

    AllocatorBase* allocator = this->allocator;
    if (allocator == nullptr) {
        allocator = &g_defaultAllocator;  // 0x01218a14
    }

    // Allocate new block: each element is 0x70 bytes
    int* newArray = static_cast<int*>(allocator->vtable->allocate(newCapacity * 0x70, allocator));

    if (this->array != nullptr) {
        uint copyCount = this->count;  // param_1[1]
        int* src = this->array;
        int* dst = newArray;

        for (uint i = 0; i < copyCount; ++i) {
            // Copy element (size 0x70) – actual copy constructor if any
            if (dst != nullptr) {
                FUN_005567b0();  // Likely copy construct element from src to dst
            }

            // Handle reference-counted sub-object at offset +0x40
            int* refPtr = reinterpret_cast<int*>(src[0x40 / sizeof(int)]);  // src[8]?
            if (refPtr != nullptr) {
                FUN_00557020();  // Possibly release reference? 
                short* refCount = reinterpret_cast<short*>(refPtr + 1);     // +4 offset? Actually +6 from base
                refCount[3] = refCount[3] - 1;  // Decrement ref count at offset 6? (short)
                if (refCount[3] == 0) {
                    // Call virtual destructor of the referenced object
                    (*(void (__thiscall**)(int))refPtr[0])(1);
                }
                src[8] = 0;  // Clear the pointer
            }

            src += 0x70 / sizeof(int);
            dst += 0x70 / sizeof(int);
        }

        // Deallocate old array
        allocator->vtable->deallocate(this->array, 0);
    }

    this->array = newArray;
    this->capacity = newCapacity;
}
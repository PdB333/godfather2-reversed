// FUNC_NAME: Vector::reserve

// Address: 0x005d98b0
// Reconstructed C++ for EA EARS engine vector grow/reserve function.
// This is a member function of a container class (likely EA::Container::Vector)
// that manages elements of size 0x28 (40 bytes) using a custom allocator.
// The container layout (offsets from this):
//   +0x00: vtable pointer
//   +0x04: allocator pointer (or null for default)
//   +0x08: begin pointer (data start)
//   +0x0C: end pointer (one past last constructed element)
//   +0x10: capacity end pointer (one past allocated memory)
// Element size = 0x28 = 40 bytes

void Vector::reserve(uint newCapacity)
{
    int iVar1;
    uint capacity;
    undefined4 *allocatorPtr;
    int iVar5;
    int iVar4;
    undefined4 *tempAlloc;
    int oldBegin;
    undefined4 local_c;
    undefined4 local_8;
    uint local_4;

    // Sanity check: newCapacity must be less than 0x6666667 (about 107 million)
    if (newCapacity < 0x6666667) {
        // Calculate current capacity (number of elements that fit in allocated memory)
        if (this->begin == 0) {
            capacity = 0;
        } else {
            capacity = (this->capacityEnd - this->begin) / 0x28;
        }

        // Only grow if new capacity exceeds current capacity
        if (capacity < newCapacity) {
            allocatorPtr = (undefined4 *)this->allocator;
            if (allocatorPtr == (undefined4 *)0x0) {
                // If no custom allocator, use stack temporary (for callbacks)
                local_c = 0;
                local_8 = 0;
                local_4 = 0;
                tempAlloc = &local_c;
            } else {
                tempAlloc = allocatorPtr;
            }

            // Call vtable function at offset 0: allocate memory
            // Signature: void* allocate(size_t size, void* allocator)
            iVar4 = (*(code **)this->vtable[0])(newCapacity * 0x28, tempAlloc);

            // Validate current size within bounds
            if ((uint)this->end < (uint)this->begin) {
                FUN_00b97aea(); // assertion failed
            }

            local_4 = (uint)this->begin;
            if ((uint)this->end < local_4) {
                FUN_00b97aea(); // assertion failed
            }

            // Round down begin to 256-byte alignment? (mask 0xffffff00)
            local_4 = local_4 & 0xffffff00;

            // Copy/move existing elements to new buffer
            FUN_005dab00((uint)this->begin, local_4, local_4); // memmove or element copy

            oldBegin = (int)this->begin;
            if (oldBegin == 0) {
                iVar5 = 0;
                oldBegin = newCapacity * 0x28; // oldBegin reused as new allocation size
            } else {
                // Number of constructed elements
                iVar5 = (this->end - oldBegin) / 0x28;
                // Destroy existing elements by calling vtable function at offset 4
                // Signature: void destroy(void* begin, size_t size)
                (**(code **)(this->vtable[4]))(oldBegin, ((this->capacityEnd - oldBegin) / 0x28) * 0x28);
            }

            // Update container pointers
            this->capacityEnd = (int)(oldBegin + iVar4); // oldBegin is re-used as new allocation size
            this->end = iVar4 + iVar5 * 0x28;
            this->begin = iVar4;
        }
        return;
    }

    // If newCapacity is too large, call error handler
    FUN_005d9ed0(); // probably assert or out-of-memory
    return;
}
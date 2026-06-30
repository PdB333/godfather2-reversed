// Function address: 0x00463b90
// Role: Reserves capacity for a dynamic array (EADynamicArray::reserve)
// __thiscall: 'this' passed in ESI (register parameter)
// Struct offsets: +0x00 data (void*), +0x04 count (int), +0x08 capacity (int),
//                  +0x0C allocatorContext (void*), +0x10 allocatorVTable (AllocatorVTable*)

void EADynamicArray::reserve(uint newCapacity)
{
    // Only grow; shrink is not handled
    if (newCapacity > this->capacity) {
        // Use custom allocator context if available, otherwise fall back to global default
        void* context = (this->allocatorContext != nullptr) ? this->allocatorContext : &gDefaultAllocator;

        // Each element is 12 bytes; allocate new block
        void* newData = this->allocatorVTable->allocate(newCapacity * 12, context);

        // Copy existing elements (count unaffected by this operation)
        if (this->data != nullptr) {
            for (uint i = 0; i < this->count; i++) {
                // Copy the 12‑byte element as two parts: 8 bytes then 4 bytes
                uint8_t* src = (uint8_t*)this->data + i * 12;
                uint8_t* dst = (uint8_t*)newData + i * 12;
                *(uint64_t*)dst = *(uint64_t*)src;
                *(uint32_t*)(dst + 8) = *(uint32_t*)(src + 8);
            }
            // Deallocate the old buffer (second parameter is 0, likely unused)
            this->allocatorVTable->deallocate(this->data, 0);
        }

        // Update container state
        this->data = newData;
        this->capacity = newCapacity;
    }
}
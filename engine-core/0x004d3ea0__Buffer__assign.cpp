// FUNC_NAME: Buffer::assign
// Function address: 0x004d3ea0
// Role: Assigns a buffer of given size with data from param_2. Reallocates if needed.
// Structure offsets:
// +0x00: char* m_data
// +0x04: int m_size
// +0x08: int m_capacity
// +0x0C: void (*m_deallocator)(char*)

int* __thiscall Buffer::assign(int* this, void* data, uint size)
{
    if (size != 0) {
        if ((uint)this[2] <= size) {
            if (this[0] != 0) {
                // Call the deallocator on old data
                ((void (*)(char*))this[3])((char*)this[0]);
            }
            // Allocate new buffer (size+1) using the allocator function
            int* newData = FUN_009c8e50(size + 1);
            this[0] = (int)newData;
            this[2] = size;
            this[3] = (int)&thunk_FUN_009c8eb0; // set deallocator to free routine
        }
        // Copy data into buffer
        _memcpy((void*)this[0], data, size);
        *(char*)((int)this[0] + size) = 0; // null-terminate
        this[1] = size;
        return this;
    }
    // Size is zero
    this[1] = 0;
    if ((char*)this[0] != (char*)0x0) {
        *(char*)this[0] = '\0'; // set first byte to null (does not deallocate)
    }
    return this;
}
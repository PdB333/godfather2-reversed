// FUNC_NAME: DynamicArray::removeByKey (0x004639e0)
// Removes the first element whose key (first int) matches the given value.
// If the array becomes empty, the allocated buffer is freed via the allocator's vtable.

class DynamicArray
{
public:
    // Offsets relative to `this`:
    // +0x00: vtable pointer (if any) – not used here
    // +0x0c: int* m_data         – pointer to array of 12-byte elements
    // +0x10: int  m_size         – number of elements
    // +0x14: int  m_capacity     – capacity (reset on deallocation)
    // +0x1c: IAllocator* m_alloc – allocator object with virtual deallocate at vtable+4

    void __thiscall removeByKey(int key)
    {
        if (this->m_size == 0)
            return;

        int* current = this->m_data;
        for (unsigned int i = 0; i < this->m_size; ++i, current += 3)
        {
            // Each element is 3 ints (12 bytes); first int is the key.
            if (*current == key)
            {
                // Shift subsequent elements left to fill the gap
                if (i < this->m_size - 1)
                {
                    int byteOffset = i * 12;
                    do
                    {
                        // Copy 8 bytes (2 ints) as a uint64_t and then the remaining 4 bytes
                        *(uint64_t*)(this->m_data + byteOffset) =
                            *(uint64_t*)(this->m_data + 12 + byteOffset);
                        *(int*)((uint64_t*)(this->m_data + byteOffset) + 2) =
                            *(int*)((uint8_t*)this->m_data + byteOffset + 20);
                        ++i;
                        byteOffset += 12;
                    } while (i < this->m_size - 1);
                }
                --this->m_size;

                // If the array is now empty, free the buffer via the custom allocator
                if (this->m_size == 0)
                {
                    // Allocator vtable index 1 (offset +4): void deallocate(void* ptr, int flag)
                    void (*deallocate)(void*, int) = 
                        (void (*)(void*, int))(*static_cast<int**>(this->m_alloc) + 1);
                    deallocate(this->m_data, 0);
                    this->m_data     = nullptr;
                    this->m_capacity = 0;
                    this->m_size     = 0;
                }
                break;
            }
        }
    }

private:
    // Data members (inferred offsets)
    int*       m_data;      // +0x0c
    int        m_size;      // +0x10
    int        m_capacity;  // +0x14
    void*      m_alloc;     // +0x1c   (pointer to allocator object)
};
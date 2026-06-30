// FUNC_NAME: PacketBuffer::addDataEntry
// Address: 0x0065d730
// Role: Adds a data chunk (pointer + size) to a circular buffer of entries, allocating memory via a polymorphic allocator.
// Note: The caller passes source pointer (unaff_retaddr) and size (unaff_EDI) in registers (ECX/EDX?).
// The buffer manager at +0x04 manages an array of 8-byte entries ({void* data; size_t size}).
// The allocator at +0x08 has a vtable; first function returns a newly allocated buffer of the given size.

void PacketBuffer::addDataEntry(void* source, size_t size)
{
    BufferManager* mgr = this->m_pBufferManager;
    IAllocator* alloc = this->m_pAllocator;

    // Acquire lock (likely a mutex or critical section)
    this->lock();

    // Check if there is room in the circular buffer and the allocator is valid
    if (mgr->m_writeCount < mgr->m_capacity && alloc != nullptr)
    {
        // Allocate memory for the data copy using the allocator's virtual function (operator new)
        void* dst = alloc->alloc(size); // equivalent to (**(code **)alloc->vtable)();

        // Copy the source data into the newly allocated buffer
        memcpy(dst, source, size);

        // Compute the actual slot index in the circular buffer
        // Index = (m_readIndex + m_writeCount) % m_capacity
        BufferEntry* entries = mgr->m_pEntries;
        int slotIndex = mgr->m_readIndex + mgr->m_writeCount;
        if (mgr->m_capacity <= slotIndex) {
            slotIndex -= mgr->m_capacity;
        }

        // Store the allocated pointer and size into the slot
        entries[slotIndex].data = dst;
        entries[slotIndex].size = size;

        // Increment the write count (number of entries written)
        mgr->m_writeCount++;
    }

    // Release lock (implicit, or called by unlock counterpart)
    return;
}

// Helper structures (not part of the function, but for context)

struct BufferEntry {
    void* data;     // +0x00
    size_t size;    // +0x04
};

struct BufferManager {  // at offset +0x04 in PacketBuffer
    BufferEntry* m_pEntries; // +0x00: base pointer to array of BufferEntry
    int m_capacity;         // +0x04: number of slots in the circular buffer
    int m_readIndex;        // +0x08: index of the oldest entry
    int m_writeCount;       // +0x0C: number of entries currently stored (write position = (m_readIndex + m_writeCount) % m_capacity)
};

class IAllocator {
public:
    virtual void* alloc(size_t size) = 0; // vtable[0]
};

class PacketBuffer {
public:
    // +0x00: possibly vtable?
    BufferManager* m_pBufferManager; // +0x04
    IAllocator* m_pAllocator;        // +0x08
    // Additional members may follow
private:
    void lock(); // calls FUN_0065dda0 (assumed to be a lock)
};
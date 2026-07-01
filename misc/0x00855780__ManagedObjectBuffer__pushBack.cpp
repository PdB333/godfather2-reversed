// FUNC_NAME: ManagedObjectBuffer::pushBack

// Function at 0x00855780 - Adds a managed object to a fixed-size (15) circular buffer.
// If the buffer is not full, the current write slot is checked for an existing object,
// which is cleaned up (function pointer reset, ref count decremented, flag bit 1 cleared).
// If the buffer is full, an external function provides an index to overwrite (likely eviction).
// Always increments reference count on the new object and advances write pointer modulo 15.
// Returns 1 if the write pointer wraps from 14 to 0, otherwise 0.

#include <cstdint>

// External helper functions
// FUN_00854000 - returns an index (0-14) when buffer is full
int __stdcall getExternalIndex();
// FUN_007075e0 - manages reference count: op==0 release, op==1 retain
void __fastcall refCountUpdate(int op);

// Global cleanup function pointer (address 0x00707620)
extern void* __cleanupFunc; 

// Partial definition for objects stored in the buffer
struct ManagedObject {
    // ... other members ...
    void* m_funcPtr;       // +0x158 - cleanup/destructor function pointer
    uint32_t m_flags;      // +0x1D0 - bit1 cleared on replacement
};

class ManagedObjectBuffer {
public:
    int pushBack(ManagedObject* newObj);
    
private:
    int m_currentWriteIndex;       // +0x04
    int m_elementCount;            // +0x08
    ManagedObject* m_elements[15]; // +0x0C
};

int ManagedObjectBuffer::pushBack(ManagedObject* newObj) {
    if (m_elementCount < 15) {
        // Buffer not full: possibly overwrite existing object at current index
        ManagedObject* oldObj = m_elements[m_currentWriteIndex];
        if (oldObj) {
            // Clean up old object before replacing
            oldObj->m_funcPtr = &__cleanupFunc; // 0x00707620
            refCountUpdate(0);                    // decrement reference count
            oldObj->m_flags &= ~2U;               // clear bit 1 (mask 0xFFFFFFFD)
        }
    } else {
        // Buffer full: get an index from external system (random/eviction)
        m_currentWriteIndex = getExternalIndex();
    }

    // Store new object and retain it
    m_elements[m_currentWriteIndex] = newObj;
    refCountUpdate(1); // increment reference count

    // Update state and advance write index
    m_elementCount++;
    int prevIndex = m_currentWriteIndex;
    m_currentWriteIndex = (prevIndex + 1) % 15;

    // Return 1 if we wrapped (prevIndex was 14), else 0
    return (prevIndex + 1) / 15;
}
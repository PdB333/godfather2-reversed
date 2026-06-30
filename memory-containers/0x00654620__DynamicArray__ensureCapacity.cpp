// FUNC_NAME: DynamicArray::ensureCapacity

// Reallocates internal buffer to accommodate at least newCapacity elements (each 20 bytes).
// Only grows, never shrinks. Rounds capacity up to next multiple of 0x10 elements.
// Updates global memory tracker before freeing old buffer.

#include <cstdint>
#include <cstdlib>

// External functions (from Ghidra)
extern "C" void* __cdecl _malloc(size_t size);
extern "C" void  __cdecl _free(void* ptr);
extern "C" void  __fastcall FUN_00654690(void* dst, const void* src, size_t count); // likely memcpy

// Global memory tracker – total allocated memory for DynamicArray instances?
extern int32_t g_globalMemoryTracker;

class DynamicArray {
public:
    int32_t m_allocatedSize;     // +0x00: size of allocated buffer in bytes (or element count)
    int32_t m_capacity;          // +0x04: maximum number of elements that fit in buffer
    void*   m_buffer;            // +0x08: pointer to element data (each element = 0x14 bytes)

    // __fastcall: ecx = this, edx = newCapacity
    void __fastcall ensureCapacity(uint32_t newCapacity);
};

void __fastcall DynamicArray::ensureCapacity(uint32_t newCapacity) {
    // Only grow if requested capacity is greater than current capacity
    if (newCapacity > m_capacity) {
        // Round up capacity to next multiple of 16 elements
        uint32_t roundedCapacity = newCapacity + (0x10 - (newCapacity & 0x0F));
        // Allocate new buffer (0x14 bytes per element)
        void* newBuffer = _malloc(roundedCapacity * 0x14);

        // Copy old data to new buffer
        // FUN_00654690 is probably memcpy(dst, src, count) – uses fastcall
        FUN_00654690(newBuffer, m_buffer, m_allocatedSize); // copy entire previous allocation

        // Update global tracker before freeing old buffer
        if (m_allocatedSize != 0) {
            g_globalMemoryTracker -= m_allocatedSize;
        }

        // Free the old buffer
        _free(m_buffer);

        // Point to newly allocated buffer
        m_buffer = newBuffer;
        // Update capacity
        m_capacity = roundedCapacity;
        // Note: m_allocatedSize is NOT updated here – may be updated elsewhere or intentionally left stale
    }
}
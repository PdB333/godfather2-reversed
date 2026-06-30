// FUNC_NAME: DynamicArray::Reserve

#include <cstdint>

// Forward declarations
class DynamicArray;

// Allocator functions (reconstructed)
namespace Allocator {
    void* Allocate(uint32_t size);   // FUN_009c8e80
    void Free(void* ptr);            // FUN_009c8f10
}

// Element structure (size 0x34 = 52 bytes)
// Offsets:
// +0x00: unknown (4 bytes)
// +0x04: unknown (4 bytes)
// +0x08: unknown (4 bytes)
// +0x0C: pData1 (4 bytes)
// +0x10: unknown (4 bytes)
// +0x14: unknown (4 bytes)
// +0x18: pData2 (4 bytes)
// +0x1C: unknown (4 bytes)
// +0x20: unknown (4 bytes)
// +0x24: pData3 (4 bytes)
// +0x28: unknown (4 bytes)
// +0x2C: unknown (4 bytes)
// +0x30: unknown (4 bytes)
struct Element {
    uint8_t pad[0x0C];
    void* pData1;      // +0x0C
    uint8_t pad2[0x0C];
    void* pData2;      // +0x18
    uint8_t pad3[0x0C];
    void* pData3;      // +0x24
    uint8_t pad4[0x10];
};

// Dynamic array container (custom, not standard vector)
// Offsets:
// +0x00: m_pBuffer (Element*)
// +0x04: m_nCount (uint32_t)
// +0x08: m_nCapacity (uint32_t)
struct DynamicArray {
    Element* m_pBuffer;   // +0x00
    uint32_t m_nCount;    // +0x04
    uint32_t m_nCapacity; // +0x08

    // Reconstruct the method
    void Reserve(uint32_t newCapacity);
};

// Element cleanup function (FUN_004bc5b0)
// Called on each old element before freeing sub-resources.
// Presumably releases internal pointers (may set them to zero).
void ElementCleanup(Element* elem); // FUN_004bc5b0

// Implementation
void DynamicArray::Reserve(uint32_t newCapacity) {
    // Only grow; never shrink
    if (m_nCapacity < newCapacity) {
        // Allocate new buffer for newCapacity elements
        Element* newBuffer = static_cast<Element*>(Allocator::Allocate(newCapacity * sizeof(Element)));

        // Destroy existing elements and free their sub-allocations
        uint32_t i = 0;
        Element* src = m_pBuffer;
        Element* dst = newBuffer;
        if (m_nCount != 0) {
            do {
                // Cleanup the element (may release owned memory)
                if (newBuffer != nullptr) {
                    ElementCleanup(src); // FUN_004bc5b0
                }

                // Free the three sub-pointers (offsets +0x24, +0x18, +0x0C)
                if (src->pData3 != nullptr) {
                    Allocator::Free(src->pData3);
                }
                if (src->pData2 != nullptr) {
                    Allocator::Free(src->pData2);
                }
                if (src->pData1 != nullptr) {
                    Allocator::Free(src->pData1);
                }

                i++;
                src++;  // advance by sizeof(Element) (0x34)
                dst++;
            } while (i < m_nCount);
        }

        // Free old buffer
        if (m_pBuffer != nullptr) {
            Allocator::Free(m_pBuffer);
        }

        // Assign new buffer and update capacity
        m_pBuffer = newBuffer;
        m_nCapacity = newCapacity;

        // Note: m_nCount remains unchanged. This is intentional:
        // the caller must ensure the array is empty before calling Reserve,
        // or the elements are reconstructed after the call.
    }
}
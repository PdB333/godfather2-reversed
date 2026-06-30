// FUNC_NAME: Array::reserveCapacity
// Address: 0x00463260
// Role: Increases capacity of a dynamic array (vector-like container) with element size 0x28 (40 bytes).
// Each element has a pointer at offset +0x18 that is deep-copied and the original freed during reallocation.

#include <cstddef>
#include <cstdint>

// Forward declaration of internal element type (size 0x28)
struct ArrayElement {
    uint8_t data[0x28];
    static constexpr std::size_t kDataSize = 0x28;
    static constexpr std::size_t kInternalPtrOffset = 0x18; // pointer to heap-allocated sub-object
};

// Array header (pointed to by unaff_EDI)
// Layout:
//   +0x00: int*     pBuffer   - pointer to array of ArrayElement
//   +0x04: uint32_t count     - number of elements currently stored
//   +0x08: uint32_t capacity  - allocated capacity (in elements)
struct ArrayHeader {
    ArrayElement* buffer;
    uint32_t count;
    uint32_t capacity;
};

// External function: allocate memory (malloc/new[] equivalent)
void* __cdecl allocateMemory(size_t size);

// External function: deallocate memory (free/delete[] equivalent)
void  __cdecl freeMemory(void* ptr);

// External function: deep-copy an element from source to destination,
// including the internal pointer at offset +0x18 (makes a new copy).
void __thiscall copyElement(ArrayElement* dest, const ArrayElement* src);

// Member function: reserve capacity (only grows if newCapacity > current capacity)
void __thiscall Array::reserveCapacity(uint32_t newCapacity)
{
    // Access the array header via implicit 'this' (EDI register in original assembly)
    ArrayHeader* header = reinterpret_cast<ArrayHeader*>(this);

    // Only grow if requested capacity is larger than current
    if (header->capacity >= newCapacity)
        return;

    // Allocate new buffer: newCapacity elements of size 0x28
    ArrayElement* newBuffer = reinterpret_cast<ArrayElement*>(
        allocateMemory(newCapacity * ArrayElement::kDataSize)
    );

    uint32_t elementOffset = 0; // offset in bytes for current element index
    if (header->buffer != nullptr) {
        uint32_t idx = 0;
        ArrayElement* destPtr = newBuffer;
        if (header->count != 0) {
            do {
                // Pointer to source element in old buffer
                const ArrayElement* srcElement = header->buffer + idx;
                // Copy element from old buffer to new buffer (deep copy of internal pointer)
                if (destPtr != nullptr) {
                    copyElement(destPtr, srcElement);
                }
                // Free the internal pointer of the source element (at offset +0x18)
                int* internalPtr = *(reinterpret_cast<int*>(
                    reinterpret_cast<uint8_t*>(srcElement) + ArrayElement::kInternalPtrOffset
                ));
                if (internalPtr != nullptr) {
                    freeMemory(internalPtr);
                }
                idx++;
                elementOffset += ArrayElement::kDataSize;
                destPtr++;
            } while (idx < header->count);
        }
        // Free the old buffer
        freeMemory(header->buffer);
    }

    // Update header
    header->buffer = newBuffer;
    header->capacity = newCapacity;
}
// FUNC_NAME: ResizableArray::reserve

#include <cstdint>

// Constants
static const int ELEMENT_SIZE = 0x14c;  // 332 bytes per element
static const int COPY_SIZE     = 0x140; // first 320 bytes of element are copied

// External allocations and destructor (addresses known from decompile)
extern void* __cdecl allocateMemory(size_t size);           // 0x009c8e80
extern void  __cdecl freeMemory(void* ptr);                 // 0x009c8f10
extern void  __cdecl elementTailDestructor(void* element);  // 0x0060faa0 – destroys data at element + 0x140
extern void  __cdecl debugCheck();                          // 0x00609aa0

// Element structure (inferred from copy pattern)
struct Element {
    int32_t  field0;          // +0x00
    int32_t  field4;          // +0x04
    int32_t  field8;          // +0x08
    uint8_t  byteAtC;        // +0x0C (single byte)
    uint8_t  bulkData[0x130]; // +0x10 (304 bytes)
    // +0x140 to +0x14B – tail managed by destructor
};

// Resizable array of fixed‑size elements
struct ResizableArray {
    uint8_t* data;      // +0x00: pointer to element buffer
    uint32_t size;      // +0x04: number of live elements
    uint32_t capacity;  // +0x08: allocated element capacity

    // Ensure at least newCapacity slots are available
    void reserve(uint32_t newCapacity) {
        if (capacity < newCapacity) {
            // Allocate new buffer
            uint8_t* newData = (uint8_t*)allocateMemory(newCapacity * ELEMENT_SIZE);

            if (data != nullptr && size != 0) {
                // Copy each existing element to the new buffer
                for (uint32_t i = 0; i < size; i++) {
                    Element* srcElem = (Element*)(data + i * ELEMENT_SIZE);
                    Element* dstElem = (Element*)(newData + i * ELEMENT_SIZE);

                    // Copy first part of the element (0x140 bytes)
                    dstElem->field0    = srcElem->field0;
                    dstElem->field4    = srcElem->field4;
                    dstElem->field8    = srcElem->field8;
                    dstElem->byteAtC   = srcElem->byteAtC;
                    // Copy the bulk data array (0x130 bytes)
                    for (int j = 0; j < 0x4c; j++) {  // 0x4c * 4 = 0x130
                        ((uint32_t*)dstElem->bulkData)[j] = ((uint32_t*)srcElem->bulkData)[j];
                    }

                    // Destroy the tail portion of the old element
                    elementTailDestructor((uint8_t*)srcElem + 0x140);
                    debugCheck();
                }

                // Release old buffer
                freeMemory(data);
            }

            // Update fields
            data = newData;
            capacity = newCapacity;
        }
    }
};